/**
 * @file garland_control.cpp
 * @brief Implémentation du contrôle des animations de guirlande
 * @version 0.5.1
 * @date 2025-12-10
 */

#include "garland_control.h"

// =============================================================================
// VARIABLES GLOBALES
// =============================================================================

static GarlandAnimation currentAnimation = ANIM_FADE_ALTERNATE;  // Démarre avec animation par défaut
static GarlandMode currentMode = MODE_PERMANENT;
static unsigned long animationStartTime = 0;
static unsigned long motionDetectedTime = 0;
static bool garlandEnabled = true;

// Paramètres d'animation
static uint8_t brightnessA = 0;
static uint8_t brightnessB = 0;
static float animationPhase = 0.0;

// =============================================================================
// NOMS DES ANIMATIONS ET MODES
// =============================================================================

static const char* animationNames[] = {
    "Eteint",
    "Fade Alterne",
    "Clignotement",
    "Pulsation",
    "Respiration",
    "Auto"
};

static const char* modeNames[] = {
    "Permanent",
    "Detection"
};

// =============================================================================
// FONCTIONS DE CONTRÔLE TB6612FNG
// =============================================================================

/**
 * @brief Configure le sens de circulation du courant
 * @param direction 0=Off, 1=Sens A (forward), 2=Sens B (backward), 3=Brake
 */
static void setDirection(uint8_t direction) {
    switch(direction) {
        case 0: // Off
            digitalWrite(PIN_TB6612_AIN1, LOW);
            digitalWrite(PIN_TB6612_AIN2, LOW);
            break;
        case 1: // Sens A (Forward)
            digitalWrite(PIN_TB6612_AIN1, HIGH);
            digitalWrite(PIN_TB6612_AIN2, LOW);
            break;
        case 2: // Sens B (Backward)
            digitalWrite(PIN_TB6612_AIN1, LOW);
            digitalWrite(PIN_TB6612_AIN2, HIGH);
            break;
        case 3: // Brake (court-circuit)
            digitalWrite(PIN_TB6612_AIN1, HIGH);
            digitalWrite(PIN_TB6612_AIN2, HIGH);
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

// =============================================================================
// FONCTIONS PUBLIQUES
// =============================================================================

void setupGarland() {
    LOG_PRINTLN("--- Initialisation guirlande ---");
    
    // Configuration des pins TB6612FNG
    pinMode(PIN_TB6612_PWMA, OUTPUT);
    pinMode(PIN_TB6612_AIN1, OUTPUT);
    pinMode(PIN_TB6612_AIN2, OUTPUT);
    pinMode(PIN_TB6612_STBY, OUTPUT);
    
    // Configuration PWM
    ledcSetup(GARLAND_PWM_CHANNEL, GARLAND_PWM_FREQUENCY, GARLAND_PWM_RESOLUTION);
    ledcAttachPin(PIN_TB6612_PWMA, GARLAND_PWM_CHANNEL);
    
    // Activation du module (sortie de standby)
    digitalWrite(PIN_TB6612_STBY, HIGH);
    
    // Configuration des capteurs
    pinMode(PIN_PIR_SENSOR, INPUT);
    pinMode(PIN_LDR_SENSOR, INPUT);
    
    // Initialisation
    garlandOff();
    animationStartTime = millis();
    
    LOG_PRINTLN("✓ Guirlande initialisée");
}

void updateGarland() {
    // Gestion des modes
    bool shouldBeOn = false;
    
    switch (currentMode) {
        case MODE_PERMANENT:
            shouldBeOn = true;
            break;
            
        case MODE_MOTION_TRIGGER:
            if (isMotionDetected()) {
                motionDetectedTime = millis();
            }
            shouldBeOn = (millis() - motionDetectedTime < MOTION_TRIGGER_DURATION);
            break;
    }
    
    // Si doit être éteint, éteindre et retourner
    if (!shouldBeOn || currentAnimation == ANIM_OFF) {
        garlandOff();
        garlandEnabled = false;
        return;
    }
    
    garlandEnabled = true;
    
    // Mode automatique : changer d'animation toutes les 30 secondes
    if (currentAnimation == ANIM_AUTO) {
        unsigned long elapsed = millis() - animationStartTime;
        if (elapsed > 30000) {
            static uint8_t autoAnimIndex = 1;
            autoAnimIndex++;
            if (autoAnimIndex >= ANIM_AUTO) {
                autoAnimIndex = 1;
            }
            currentAnimation = (GarlandAnimation)autoAnimIndex;
            animationStartTime = millis();
            LOG_PRINTF("Mode Auto: Animation %s\n", animationNames[autoAnimIndex]);
        }
    }
    
    // Exécution de l'animation
    switch (currentAnimation) {
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
        default:
            break;
    }
    
    // Libérer le CPU pour les tâches WiFi et éviter watchdog timer reset
    yield();
}

void setGarlandAnimation(GarlandAnimation animation) {
    currentAnimation = animation;
    animationStartTime = millis();
    LOG_PRINTF("Animation changée: %s\n", animationNames[animation]);
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

void setGarlandMode(GarlandMode mode) {
    currentMode = mode;
    LOG_PRINTF("Mode changé: %s\n", modeNames[mode]);
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

bool isMotionDetected() {
    return digitalRead(PIN_PIR_SENSOR) == HIGH;
}

int getLightLevel() {
    return analogRead(PIN_LDR_SENSOR);
}

bool isAnimationActive() {
    return (currentAnimation != ANIM_OFF) && garlandEnabled;
}
