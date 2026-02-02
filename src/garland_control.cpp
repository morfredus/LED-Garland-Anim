/**
 * @file garland_control.cpp
 * @brief Implémentation du contrôle des animations de guirlande
 * @version 5.6.4
 * @date 2026-02-02
 */

#include "garland_control.h"
#include <nvs_flash.h>
#include <nvs.h>

// =============================================================================
// VARIABLES GLOBALES
// =============================================================================

static GarlandAnimation currentAnimation = ANIM_FADE_ALTERNATE;  // Animation sélectionnée (pour affichage)
static GarlandAnimation activeAnimation = ANIM_FADE_ALTERNATE;   // Animation réellement exécutée
static GarlandAnimation savedAnimation = ANIM_FADE_ALTERNATE;    // Animation sauvegardée à restaurer après intro
static GarlandMode currentMode = MODE_PERMANENT;
static GarlandMode savedMode = MODE_PERMANENT;                    // Mode sauvegardé à restaurer après intro
static unsigned long animationStartTime = 0;
static unsigned long bootTime = 0;                                // Temps du démarrage pour gérer l'intro
static unsigned long motionDetectedTime = 0;
static unsigned long autoAnimationIntervalMs = DEFAULT_GARLAND_ANIM_INTERVAL;   // Intervalle entre changements en mode AUTO
static unsigned long motionTriggerDurationMs = MOTION_TRIGGER_DEFAULT; // Durée d'allumage après détection
static bool garlandEnabled = true;
static bool autoModeActive = false;  // Flag pour suivre si le mode AUTO est actif
static bool lastMotionState = false;  // État précédent du capteur PIR pour détecter les fronts
static bool introAnimationActive = true; // Flag pour suivre si l'animation d'intro est active

// Paramètres d'animation
static uint8_t brightnessA = 0;
static uint8_t brightnessB = 0;
static float animationPhase = 0.0;

// Type de capteur de mouvement détecté
static MotionSensorType motionSensorType = MOTION_SENSOR_UNKNOWN;

// Mode d'affichage de l'écran LCD
static DisplayMode currentDisplayMode = DEFAULT_DISPLAY_MODE;

// Nom d'appareil pour mDNS
static char deviceName[MAX_DEVICE_NAME_LEN + 1] = DEFAULT_DEVICE_NAME;

// =============================================================================
// FONCTIONS DE GESTION DU NOM D'APPAREIL
// =============================================================================

const char* getDeviceName() {
    return deviceName;
}

bool isValidDeviceName(const char* name) {
    if (!name) return false;
    
    size_t len = strlen(name);
    if (len == 0 || len > MAX_DEVICE_NAME_LEN) return false;
    
    // Vérifier que le nom contient uniquement des caractères alphanumériques, tirets et underscores
    for (size_t i = 0; i < len; i++) {
        char c = name[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
              (c >= '0' && c <= '9') || c == '-' || c == '_')) {
            return false;
        }
    }
    
    // Le nom ne doit pas commencer ou finir par un tiret
    if (name[0] == '-' || name[len - 1] == '-') return false;
    
    return true;
}

bool setDeviceName(const char* name) {
    if (!isValidDeviceName(name)) {
        LOG_PRINTLN("✗ Nom d'appareil invalide");
        return false;
    }
    
    strncpy(deviceName, name, MAX_DEVICE_NAME_LEN);
    deviceName[MAX_DEVICE_NAME_LEN] = '\0';
    
    saveDeviceNameToNVS();
    LOG_PRINTF("✓ Nom d'appareil défini: %s\n", deviceName);
    
    return true;
}

void loadDeviceNameFromNVS() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err == ESP_OK) {
        size_t len = MAX_DEVICE_NAME_LEN + 1;
        err = nvs_get_str(handle, "device_name", deviceName, &len);
        if (err == ESP_OK) {
            LOG_PRINTF("✓ Nom d'appareil restauré: %s\n", deviceName);
        } else {
            // Si aucun nom sauvegardé, utiliser le nom par défaut
            strncpy(deviceName, DEFAULT_DEVICE_NAME, MAX_DEVICE_NAME_LEN);
            deviceName[MAX_DEVICE_NAME_LEN] = '\0';
        }
        nvs_close(handle);
    } else {
        // Si erreur NVS, utiliser le nom par défaut
        strncpy(deviceName, DEFAULT_DEVICE_NAME, MAX_DEVICE_NAME_LEN);
        deviceName[MAX_DEVICE_NAME_LEN] = '\0';
    }
}

void saveDeviceNameToNVS() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err == ESP_OK) {
        nvs_set_str(handle, "device_name", deviceName);
        nvs_commit(handle);
        nvs_close(handle);
        LOG_PRINTLN("✓ Nom d'appareil sauvegardé en NVS");
    } else {
        LOG_PRINTLN("✗ Erreur lors de la sauvegarde du nom d'appareil");
    }
}

// =============================================================================
// FONCTIONS DE MODE D'AFFICHAGE
// =============================================================================

DisplayMode getDisplayMode() {
    return currentDisplayMode;
}

void setDisplayMode(DisplayMode mode) {
    currentDisplayMode = mode;
    saveDisplayModeToNVS();
}

const char* getDisplayModeName() {
    switch (currentDisplayMode) {
        case DISPLAY_MODE_ANIMATED: return "Animé";
        case DISPLAY_MODE_STATIC:   return "Statique";
        case DISPLAY_MODE_OFF:      return "Éteint";
        default: return "Inconnu";
    }
}

const char* getDisplayModeNameById(int id) {
    switch ((DisplayMode)id) {
        case DISPLAY_MODE_ANIMATED: return "Animé";
        case DISPLAY_MODE_STATIC:   return "Statique";
        case DISPLAY_MODE_OFF:      return "Éteint";
        default: return "Inconnu";
    }
}

void loadDisplayModeFromNVS() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err == ESP_OK) {
        int32_t mode = 0;
        err = nvs_get_i32(handle, "display_mode", &mode);
        if (err == ESP_OK && mode >= 0 && mode < DISPLAY_MODE_COUNT) {
            currentDisplayMode = (DisplayMode)mode;
        }
        nvs_close(handle);
    }
}

void saveDisplayModeToNVS() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err == ESP_OK) {
        nvs_set_i32(handle, "display_mode", (int32_t)currentDisplayMode);
        nvs_commit(handle);
        nvs_close(handle);
    }
}

MotionSensorType getMotionSensorType() {
    return motionSensorType;
}

// =============================================================================
// NOMS DES ANIMATIONS ET MODES
// =============================================================================

static const char* animationNames[] = {
    "Off",
    "Fade Alt",
    "Blink",
    "Pulse",
    "Breath",
    "Strobe",
    "Heartbeat",
    "Wave",
    "Sparkle",
    "Meteor",
    "Auto"
};

static const char* modeNames[] = {
    "Permanent",
    "Detection (tout)",
    "Detection (guirlande)"
};

// =============================================================================
// FONCTIONS DE PERSISTANCE NVS
// =============================================================================

/**
 * @brief Charge les paramètres sauvegardés depuis NVS
 */
void loadGarlandSettings() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    
    if (err != ESP_OK) {
        LOG_PRINTLN("⚠ NVS non initialisé ou espace vide");
        // Charger le nom d'appareil par défaut même si NVS échoue
        loadDeviceNameFromNVS();
        return;
    }
    
    // Charger le mode
    uint8_t mode = 0;
    if (nvs_get_u8(handle, "mode", &mode) == ESP_OK && mode < MODE_COUNT) {
        currentMode = (GarlandMode)mode;
        savedMode = currentMode;  // Synchroniser l'état de démarrage
        LOG_PRINTF("[RESTORE] - Mode - %s\n", modeNames[currentMode]);
    }

    // Charger l'animation
    uint8_t anim = (uint8_t)ANIM_FADE_ALTERNATE;
    if (nvs_get_u8(handle, "animation", &anim) == ESP_OK) {
        savedAnimation = (GarlandAnimation)anim;
        currentAnimation = savedAnimation;
        activeAnimation = currentAnimation;
        LOG_PRINTF("[RESTORE] - Garland - %s\n", animationNames[currentAnimation]);
    }
    
    // Charger l'intervalle AUTO
    uint32_t autoInterval = 30000;
    if (nvs_get_u32(handle, "autoInterval", &autoInterval) == ESP_OK) {
        autoAnimationIntervalMs = autoInterval;
        LOG_PRINTF("Intervalle AUTO restauré: %lu ms\n", autoAnimationIntervalMs);
    }
    
    // Charger la durée de détection mouvement
    uint32_t motionDuration = MOTION_TRIGGER_DURATION;
    if (nvs_get_u32(handle, "motionDuration", &motionDuration) == ESP_OK) {
        motionTriggerDurationMs = motionDuration;
        LOG_PRINTF("Durée mouvement restaurée: %lu ms\n", motionTriggerDurationMs);
    }
    
    nvs_close(handle);
    
    // Charger le nom d'appareil
    loadDeviceNameFromNVS();

    // Charger le mode d'affichage LCD
    loadDisplayModeFromNVS();
}

/**
 * @brief Sauvegarde les paramètres actuels en NVS
 */
void saveGarlandSettings() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    
    if (err != ESP_OK) {
        LOG_PRINTLN("✗ Erreur: impossible d'ouvrir NVS");
        return;
    }
    
    // Sauvegarder le mode
    nvs_set_u8(handle, "mode", (uint8_t)currentMode);
    
    // Sauvegarder l'animation
    nvs_set_u8(handle, "animation", (uint8_t)currentAnimation);
    
    // Sauvegarder les durées
    nvs_set_u32(handle, "autoInterval", autoAnimationIntervalMs);
    nvs_set_u32(handle, "motionDuration", motionTriggerDurationMs);
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK) {
        LOG_PRINTLN("✓ Paramètres sauvegardés en NVS");
    } else {
        LOG_PRINTLN("✗ Erreur lors de la sauvegarde NVS");
    }
}

// FONCTIONS DE CONTRÔLE TB6612FNG
// =============================================================================

/**
 * @brief Configure le sens de circulation du courant
 * @param direction 0=Off, 1=Sens A (forward), 2=Sens B (backward), 3=Brake
 */
static void setDirection(uint8_t direction) {
    switch(direction) {
        case 0: // Off
            digitalWrite(TB6612_AIN1, LOW);
            digitalWrite(TB6612_AIN2, LOW);
            break;
        case 1: // Sens A (Forward)
            digitalWrite(TB6612_AIN1, HIGH);
            digitalWrite(TB6612_AIN2, LOW);
            break;
        case 2: // Sens B (Backward)
            digitalWrite(TB6612_AIN1, LOW);
            digitalWrite(TB6612_AIN2, HIGH);
            break;
        case 3: // Brake (court-circuit)
            digitalWrite(TB6612_AIN1, HIGH);
            digitalWrite(TB6612_AIN2, HIGH);
            break;
    }
}

/**
 * @brief Définit l'intensité lumineuse via PWM
 * @param intensity Intensité (0-255)
 */
static void setIntensity(uint8_t intensity) {
    ledcWrite(GARLAND_PWM_CHANNEL, intensity);
}

/**
 * @brief Allume uniquement le Sens A avec une intensité donnée
 * @param intensity Intensité (0-255)
 */
static void setSenseA(uint8_t intensity) {
    setDirection(1);
    setIntensity(intensity);
}

/**
 * @brief Allume uniquement le Sens B avec une intensité donnée
 * @param intensity Intensité (0-255)
 */
static void setSenseB(uint8_t intensity) {
    setDirection(2);
    setIntensity(intensity);
}

// =============================================================================
// ANIMATIONS
// =============================================================================

/**
 * @brief Animation : Fade alterné entre Sens A et B
 */
static void animateFadeAlternate() {
    unsigned long elapsed = millis() - animationStartTime;
    float phase = (elapsed % 4000) / 4000.0; // Cycle de 4 secondes
    
    if (phase < 0.5) {
        // Phase A : Fade in/out du Sens A
        float subPhase = phase * 2.0;
        brightnessA = (subPhase < 0.5) ? (uint8_t)(subPhase * 2.0 * 255) : (uint8_t)((1.0 - (subPhase - 0.5) * 2.0) * 255);
        setSenseA(brightnessA);
    } else {
        // Phase B : Fade in/out du Sens B
        float subPhase = (phase - 0.5) * 2.0;
        brightnessB = (subPhase < 0.5) ? (uint8_t)(subPhase * 2.0 * 255) : (uint8_t)((1.0 - (subPhase - 0.5) * 2.0) * 255);
        setSenseB(brightnessB);
    }
}

/**
 * @brief Animation : Clignotement alterné
 */
static void animateBlinkAlternate() {
    unsigned long elapsed = millis() - animationStartTime;
    uint16_t cycleTime = elapsed % 1000; // Cycle de 1 seconde
    
    if (cycleTime < 500) {
        setSenseA(255);
    } else {
        setSenseB(255);
    }
}

/**
 * @brief Animation : Pulsation simultanée (alterner rapidement entre A et B)
 */
static void animatePulse() {
    unsigned long elapsed = millis() - animationStartTime;
    uint16_t cycleTime = elapsed % 2000;
    float phase = cycleTime / 2000.0;
    
    uint8_t brightness = (phase < 0.5) ? (uint8_t)(phase * 2.0 * 255) : (uint8_t)((1.0 - (phase - 0.5) * 2.0) * 255);
    
    // Alterner rapidement pour donner l'illusion de simultanéité
    if ((elapsed / 10) % 2 == 0) {
        setSenseA(brightness);
    } else {
        setSenseB(brightness);
    }
}

/**
 * @brief Animation : Respiration lente (alterner rapidement entre A et B)
 */
static void animateBreathing() {
    unsigned long elapsed = millis() - animationStartTime;
    uint16_t cycleTime = elapsed % 4000;
    float phase = cycleTime / 4000.0;
    
    uint8_t brightness = (uint8_t)((1.0 - cos(phase * 2.0 * PI)) / 2.0 * 255);
    
    if ((elapsed / 10) % 2 == 0) {
        setSenseA(brightness);
    } else {
        setSenseB(brightness);
    }
}

/**
 * @brief Animation : Strobe - Flash stroboscopique rapide
 */
static void animateStrobe() {
    unsigned long elapsed = millis() - animationStartTime;
    uint16_t cycleTime = elapsed % 200;  // Cycle de 200ms
    
    // Flash très court (50ms) puis noir
    if (cycleTime < 50) {
        // Alterner A et B à chaque flash
        if ((elapsed / 200) % 2 == 0) {
            setSenseA(255);
        } else {
            setSenseB(255);
        }
    } else {
        garlandOff();
    }
}

/**
 * @brief Animation : Heartbeat - Double pulsation (battement de cœur)
 */
static void animateHeartbeat() {
    unsigned long elapsed = millis() - animationStartTime;
    uint16_t cycleTime = elapsed % 1500;  // Cycle de 1.5 secondes
    
    uint8_t brightness = 0;
    
    // Premier battement (0-200ms)
    if (cycleTime < 100) {
        brightness = (uint8_t)(cycleTime * 255 / 100);
    } else if (cycleTime < 200) {
        brightness = (uint8_t)((200 - cycleTime) * 255 / 100);
    }
    // Deuxième battement (250-450ms)
    else if (cycleTime < 350) {
        brightness = (uint8_t)((cycleTime - 250) * 255 / 100);
    } else if (cycleTime < 450) {
        brightness = (uint8_t)((450 - cycleTime) * 255 / 100);
    }
    // Pause jusqu'à la fin du cycle
    
    // Alterner rapidement pour illuminer les deux sens
    if ((elapsed / 10) % 2 == 0) {
        setSenseA(brightness);
    } else {
        setSenseB(brightness);
    }
}

/**
 * @brief Animation : Wave - Vague sinusoïdale fluide
 */
static void animateWave() {
    unsigned long elapsed = millis() - animationStartTime;
    float time = elapsed / 1000.0;  // Temps en secondes
    
    // Calcul d'une onde sinusoïdale qui va de -1 à +1
    float wave = sin(time * 2.0);  // Période de π secondes
    
    // Mapper la vague sur les deux sens
    if (wave > 0) {
        // Sens A : proportionnel à wave (0 → 1)
        setSenseA((uint8_t)(wave * 255));
    } else {
        // Sens B : proportionnel à -wave (0 → 1)
        setSenseB((uint8_t)(-wave * 255));
    }
}

/**
 * @brief Animation : Sparkle - Scintillement aléatoire
 */
static void animateSparkle() {
    unsigned long elapsed = millis() - animationStartTime;
    
    // Changer aléatoirement toutes les 50ms
    if (elapsed % 50 < 5) {
        uint8_t randomBrightness = random(100, 255);
        
        // 50% de chance pour chaque sens
        if (random(0, 2) == 0) {
            setSenseA(randomBrightness);
        } else {
            setSenseB(randomBrightness);
        }
    }
}

/**
 * @brief Animation : Meteor - Traînée lumineuse avec estompage
 */
static void animateMeteor() {
    unsigned long elapsed = millis() - animationStartTime;
    uint16_t cycleTime = elapsed % 2000;  // Cycle de 2 secondes
    float progress = cycleTime / 2000.0;
    
    // Traînée qui traverse de A vers B
    if (progress < 0.5) {
        // Phase A : montée rapide
        uint8_t brightness = (uint8_t)(progress * 2.0 * 255);
        setSenseA(brightness);
    } else {
        // Phase B : montée A qui s'estompe + montée B
        uint8_t brightnessA = (uint8_t)((1.0 - progress) * 2.0 * 255);
        uint8_t brightnessB = (uint8_t)((progress - 0.5) * 2.0 * 255);
        
        // Alterner rapidement pour créer l'illusion de traînée
        if ((elapsed / 20) % 2 == 0) {
            setSenseA(brightnessA);
        } else {
            setSenseB(brightnessB);
        }
    }
}

// =============================================================================
// FONCTIONS PUBLIQUES
// =============================================================================

void setupGarland() {
    LOG_PRINTLN("--- Initialisation guirlande ---");
    
    // Charger les paramètres sauvegardés depuis NVS
    loadGarlandSettings();
    
    // Configuration des pins TB6612FNG
    pinMode(TB6612_PWMA, OUTPUT);
    pinMode(TB6612_AIN1, OUTPUT);
    pinMode(TB6612_AIN2, OUTPUT);
    pinMode(TB6612_STBY, OUTPUT);
    
    // Configuration PWM
    ledcSetup(GARLAND_PWM_CHANNEL, GARLAND_PWM_FREQUENCY, GARLAND_PWM_RESOLUTION);
    ledcAttachPin(TB6612_PWMA, GARLAND_PWM_CHANNEL);
    
    // Activation du module (sortie de standby)
    digitalWrite(TB6612_STBY, HIGH);
    

    // Configuration du capteur de mouvement (PIR ou RCWL-0516)
    pinMode(MOTION_SENSOR_PIN, INPUT);

    // Détection automatique du type de capteur :
    // PIR : LOW au repos, HIGH sur détection
    // RCWL-0516 : HIGH au repos, LOW sur détection
    delay(100); // Laisser le capteur s'initialiser
    int sensorIdle = digitalRead(MOTION_SENSOR_PIN);
    if (sensorIdle == LOW) {
        motionSensorType = MOTION_SENSOR_PIR;
        LOG_PRINTLN("Capteur de mouvement détecté : PIR");
    } else {
        motionSensorType = MOTION_SENSOR_RCWL;
        LOG_PRINTLN("Capteur de mouvement détecté : RCWL-0516");
    }

    // Initialisation
    animationStartTime = millis();
    bootTime = millis();

    // Démarrer immédiatement l'animation d'introduction
    introAnimationActive = true;
    activeAnimation = ANIM_FADE_ALTERNATE;  // Animation d'intro par défaut
    garlandEnabled = true;

    // Forcer le mode permanent pendant l'intro pour que l'animation démarre immédiatement
    currentMode = MODE_PERMANENT;

    LOG_PRINTF("[INTRO] - Garland - %s (%lu ms)\n", animationNames[activeAnimation], INTRO_ANIMATION_DURATION);
    LOG_PRINTF("[INTRO] - Garland - Next: %s\n", animationNames[savedAnimation]);
    LOG_PRINTF("[INTRO] - Mode - Next: %s\n", modeNames[savedMode]);
}

void updateGarland() {
    // Throttle global to avoid monopolizing loop while keeping animations smooth
    static unsigned long lastUpdate = 0;
    unsigned long now = millis();
    if (now - lastUpdate < 10) {
        return;
    }
    lastUpdate = now;

    // Vérifier si l'animation d'intro est terminée
    if (introAnimationActive) {
        unsigned long elapsed = millis() - bootTime;
        if (elapsed >= INTRO_ANIMATION_DURATION) {
            // L'animation d'intro est terminée, basculer vers le mode/animation sauvegardés
            introAnimationActive = false;
            currentMode = savedMode;
            currentAnimation = savedAnimation;

            // Configurer l'animation active selon le mode sauvegardé
            if (savedAnimation == ANIM_AUTO) {
                autoModeActive = true;
                activeAnimation = ANIM_FADE_ALTERNATE;
            } else {
                autoModeActive = false;
                activeAnimation = savedAnimation;
            }

            animationStartTime = millis();

            // Initialiser motionDetectedTime dans le passé pour le mode détection
            if (savedMode == MODE_MOTION_TRIGGER) {
                motionDetectedTime = 0 - motionTriggerDurationMs - 1000;
            }

            LOG_PRINTF("[INTRO-END] - Garland - %s | Mode: %s\n", animationNames[currentAnimation], modeNames[currentMode]);
        }
    }

    // Gestion des modes
    bool shouldBeOn = false;

    switch (currentMode) {
        case MODE_PERMANENT:
            shouldBeOn = true;
            break;

        case MODE_MOTION_TRIGGER:
        case MODE_MOTION_MATRIX_INDEPENDENT:
            // Détecter seulement les fronts montants (nouveau mouvement)
            bool currentMotionState = isMotionDetected();
            if (currentMotionState && !lastMotionState) {
                // Front montant détecté : nouveau mouvement
                motionDetectedTime = millis();
                LOG_PRINTLN("🔔 Mouvement détecté ! Timer activé.");
            }
            lastMotionState = currentMotionState;

            // Vérifier si on est dans la fenêtre de temps après détection
            unsigned long elapsed = millis() - motionDetectedTime;
            shouldBeOn = (elapsed < motionTriggerDurationMs);

            // Log pour debug (toutes les 5 secondes)
            static unsigned long lastLogTime = 0;
            if (millis() - lastLogTime > 5000) {
                lastLogTime = millis();
                const char* modeDesc = (currentMode == MODE_MOTION_TRIGGER) ?
                    "Detection (tout)" : "Detection (guirlande)";
                LOG_PRINTF("Mode %s: Guirlande %s (temps écoulé: %lu ms / %lu ms)\n",
                    modeDesc, shouldBeOn ? "ON" : "OFF", elapsed, motionTriggerDurationMs);
            }
            break;
    }

    // Si doit être éteint, éteindre et retourner
    // IMPORTANT: Tester activeAnimation (celle en cours) et non currentAnimation (celle sélectionnée)
    if (!shouldBeOn || activeAnimation == ANIM_OFF) {
        garlandOff();
        garlandEnabled = false;
        return;
    }
    
    garlandEnabled = true;
    
    // Mode automatique : changer d'animation toutes les 30 secondes
    if (autoModeActive) {
        unsigned long elapsed = millis() - animationStartTime;
        if (elapsed > autoAnimationIntervalMs) {
            uint8_t nextAnim = (uint8_t)activeAnimation + 1;
            // Boucler entre ANIM_FADE_ALTERNATE (1) et ANIM_METEOR (9), avant ANIM_AUTO (10)
            if (nextAnim >= ANIM_AUTO) {
                nextAnim = ANIM_FADE_ALTERNATE;
            }
            activeAnimation = (GarlandAnimation)nextAnim;
            animationStartTime = millis();
            LOG_PRINTF("Mode Auto: Animation %s\n", animationNames[nextAnim]);
        }
    }
    
    // Exécution de l'animation (utiliser activeAnimation)
    switch (activeAnimation) {
        case ANIM_OFF:
            garlandOff();
            break;
        case ANIM_FADE_ALTERNATE:
            animateFadeAlternate();
            break;
        case ANIM_BLINK_ALTERNATE:
            animateBlinkAlternate();
            break;
        case ANIM_PULSE:
            animatePulse();
            break;
        case ANIM_BREATHING:
            animateBreathing();
            break;
        case ANIM_STROBE:
            animateStrobe();
            break;
        case ANIM_HEARTBEAT:
            animateHeartbeat();
            break;
        case ANIM_WAVE:
            animateWave();
            break;
        case ANIM_SPARKLE:
            animateSparkle();
            break;
        case ANIM_METEOR:
            animateMeteor();
            break;
        default:
            break;
    }
    
    // Libérer le CPU pour les tâches WiFi et éviter watchdog timer reset
    yield();
}

void setGarlandAnimation(GarlandAnimation animation) {
    // Désactiver l'animation d'intro si l'utilisateur change manuellement l'animation
    if (introAnimationActive) {
        introAnimationActive = false;
        LOG_PRINTLN("Animation d'intro interrompue par changement manuel");
    }

    currentAnimation = animation;  // Toujours mettre à jour pour l'affichage
    savedAnimation = animation;    // Mettre à jour aussi la sauvegarde

    // Si on passe en mode AUTO, démarrer immédiatement avec la première animation
    if (animation == ANIM_AUTO) {
        autoModeActive = true;
        activeAnimation = ANIM_FADE_ALTERNATE;  // Première animation
        animationStartTime = millis();
        LOG_PRINTF("[AUTO] - Garland - %s (auto mode started)\n", animationNames[ANIM_FADE_ALTERNATE]);
    } else {
        autoModeActive = false;  // Désactiver le mode AUTO
        activeAnimation = animation;  // Animation active = animation sélectionnée
        animationStartTime = millis();
        LOG_PRINTF("[CHANGE] - Garland - %s\n", animationNames[animation]);
    }
    // Sauvegarder automatiquement
    saveGarlandSettings();
}

GarlandAnimation getGarlandAnimation() {
    return currentAnimation;
}

const char* getGarlandAnimationName() {
    return animationNames[currentAnimation];
}

const char* getGarlandAnimationNameById(int id) {
    if (id >= 0 && id < ANIM_COUNT) {
        return animationNames[id];
    }
    return "?";
}

GarlandAnimation getActiveAnimation() {
    return activeAnimation;
}

// ============================================================================
// PARAMÈTRES CONFIGURABLES (Durées)
// ============================================================================

unsigned long getAutoAnimationIntervalMs() {
    return autoAnimationIntervalMs;
}

void setAutoAnimationIntervalMs(unsigned long ms) {
    // Clamp pour éviter des valeurs absurdes : 5s à 5 minutes
    ms = constrain(ms, 5000UL, 300000UL);
    autoAnimationIntervalMs = ms;
    // Réinitialiser le timer pour appliquer immédiatement le nouveau cycle
    animationStartTime = millis();
    // Sauvegarder automatiquement
    saveGarlandSettings();
}

unsigned long getMotionTriggerDurationMs() {
    return motionTriggerDurationMs;
}

void setMotionTriggerDurationMs(unsigned long ms) {
    // Clamp : 5s à 10 minutes
    ms = constrain(ms, 5000UL, 600000UL);
    motionTriggerDurationMs = ms;
    // Sauvegarder automatiquement
    saveGarlandSettings();
}

void setGarlandMode(GarlandMode mode) {
    // Désactiver l'animation d'intro si l'utilisateur change manuellement le mode
    if (introAnimationActive) {
        introAnimationActive = false;
        LOG_PRINTLN("Animation d'intro interrompue par changement manuel de mode");
    }

    currentMode = mode;
    savedMode = mode;  // Mettre à jour aussi la sauvegarde
    LOG_PRINTF("Mode changé: %s\n", modeNames[mode]);
    // Sauvegarder automatiquement
    saveGarlandSettings();
}

GarlandMode getGarlandMode() {
    return currentMode;
}

const char* getGarlandModeName() {
    return modeNames[currentMode];
}

const char* getGarlandModeNameById(int id) {
    if (id >= 0 && id < MODE_COUNT) {
        return modeNames[id];
    }
    return "?";
}

void nextGarlandAnimation() {
    uint8_t next = (uint8_t)currentAnimation + 1;
    if (next >= ANIM_COUNT) {
        next = 0;
    }
    setGarlandAnimation((GarlandAnimation)next);
}

void nextGarlandMode() {
    uint8_t next = (uint8_t)currentMode + 1;
    if (next >= MODE_COUNT) {
        next = 0;
    }
    setGarlandMode((GarlandMode)next);
}

void garlandOff() {
    setDirection(0);
    setIntensity(0);
}


// Détection de mouvement compatible PIR et RCWL-0516
bool isMotionDetected() {
    int val = digitalRead(MOTION_SENSOR_PIN);
    if (motionSensorType == MOTION_SENSOR_PIR) {
        // PIR : HIGH = mouvement
        return val == HIGH;
    } else if (motionSensorType == MOTION_SENSOR_RCWL) {
        // RCWL-0516 : LOW = mouvement
        return val == LOW;
    } else {
        // Par défaut, comportement PIR
        return val == HIGH;
    }
}

int getLightLevel() {
    // LDR sensor removed - return default value
    return 0;
}

bool isAnimationActive() {
    return (currentAnimation != ANIM_OFF) && garlandEnabled;
}

bool isGarlandEnabled() {
    return garlandEnabled;
}
