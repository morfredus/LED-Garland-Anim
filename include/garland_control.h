/**
 * @file garland_control.h
 * @brief Contrôle des animations de guirlande LED bi-directionnelle
 * @version 1.12.0
 * @date 2026-01-01
 *
 * Module de gestion des animations pour guirlande LED à 2 fils avec LEDs en anti-parallèle.
 * Utilise le module TB6612FNG pour contrôler la direction du courant et l'intensité lumineuse.
 */

#ifndef GARLAND_CONTROL_H
#define GARLAND_CONTROL_H

#include <Arduino.h>
#include "board_config.h"
#include "config.h"
#include <nvs_flash.h>
#include <nvs.h>

// Mode d'affichage de l'écran LCD
DisplayMode getDisplayMode();
void setDisplayMode(DisplayMode mode);
const char* getDisplayModeName();
const char* getDisplayModeNameById(int id);
void loadDisplayModeFromNVS();
void saveDisplayModeToNVS();

// =============================================================================
// CONSTANTES D'ANIMATION
// =============================================================================

#define NVS_NAMESPACE "garland"  ///< Espace de noms NVS pour la persistence

/**
 * @enum GarlandAnimation
 * @brief Types d'animations disponibles pour la guirlande monochrome 2 fils
 */
enum GarlandAnimation {
    ANIM_OFF = 0,           ///< Guirlande éteinte
    ANIM_FADE_ALTERNATE,    ///< Fade alterné entre Sens A et B
    ANIM_BLINK_ALTERNATE,   ///< Clignotement alterné
    ANIM_PULSE,             ///< Pulsation simultanée
    ANIM_BREATHING,         ///< Respiration lente
    ANIM_STROBE,            ///< Flash stroboscopique rapide
    ANIM_HEARTBEAT,         ///< Double pulsation (battement de cœur)
    ANIM_WAVE,              ///< Vague sinusoïdale fluide
    ANIM_SPARKLE,           ///< Scintillement aléatoire
    ANIM_METEOR,            ///< Traînée lumineuse avec estompage
    ANIM_AUTO,              ///< Mode automatique (cycle toutes les animations)
    ANIM_COUNT              ///< Nombre total d'animations
};

/**
 * @enum GarlandMode
 * @brief Modes de fonctionnement de la guirlande
 */
enum GarlandMode {
    MODE_PERMANENT = 0,              ///< Guirlande et matrice toujours allumées
    MODE_MOTION_TRIGGER,             ///< Guirlande ET matrice déclenchées par détection
    MODE_MOTION_MATRIX_INDEPENDENT,  ///< Guirlande déclenchée par détection, matrice toujours allumée
    MODE_COUNT                       ///< Nombre total de modes
};

// =============================================================================
// CONFIGURATION
// =============================================================================

#define GARLAND_PWM_FREQUENCY  5000      ///< Fréquence PWM en Hz
#define GARLAND_PWM_RESOLUTION 8         ///< Résolution PWM (8 bits = 0-255)
#define GARLAND_PWM_CHANNEL    0         ///< Canal PWM pour le TB6612FNG

#define MOTION_TRIGGER_DURATION 30000    ///< Durée d'allumage après détection (ms)
#define INTRO_ANIMATION_DURATION 10000   ///< Durée de l'animation d'intro au démarrage (ms)

// Durées configurables (exposées via l'interface Web)
unsigned long getAutoAnimationIntervalMs();
void setAutoAnimationIntervalMs(unsigned long ms);
unsigned long getMotionTriggerDurationMs();
void setMotionTriggerDurationMs(unsigned long ms);

// Sauvegarde/restauration NVS
/**
 * @brief Charge les paramètres sauvegardés (mode, animation, durées) depuis NVS
 */
void loadGarlandSettings();

/**
 * @brief Sauvegarde les paramètres actuels en NVS
 */
void saveGarlandSettings();

// =============================================================================
// PROTOTYPES DE FONCTIONS
// =============================================================================

/**
 * @brief Initialise le module TB6612FNG et les capteurs
 * 
 * Configure les pins GPIO et le PWM pour contrôler la guirlande.
 * Initialise le capteur PIR.
 */
void setupGarland();

/**
 * @brief Boucle principale de mise à jour des animations
 * 
 * Doit être appelée régulièrement dans loop() pour actualiser
 * l'animation en cours et gérer les modes de fonctionnement.
 */
void updateGarland();

/**
 * @brief Change l'animation actuelle
 * @param animation Nouvelle animation à afficher
 */
void setGarlandAnimation(GarlandAnimation animation);

/**
 * @brief Récupère l'animation actuelle
 * @return Animation en cours
 */
GarlandAnimation getGarlandAnimation();

/**
 * @brief Récupère le nom de l'animation actuelle
 * @return Nom de l'animation en cours
 */
const char* getGarlandAnimationName();

/**
 * @brief Récupère le nom d'une animation par son identifiant
 * @param id Identifiant (0..ANIM_COUNT-1)
 * @return Nom ou "?" si hors bornes
 */
const char* getGarlandAnimationNameById(int id);

/**
 * @brief Change le mode de fonctionnement
 * @param mode Nouveau mode
 */
void setGarlandMode(GarlandMode mode);

/**
 * @brief Récupère le mode de fonctionnement actuel
 * @return Mode actuel
 */
GarlandMode getGarlandMode();

/**
 * @brief Récupère le nom du mode actuel
 * @return Nom du mode en cours
 */
const char* getGarlandModeName();

/**
 * @brief Récupère le nom d'un mode par son identifiant
 * @param id Identifiant (0..MODE_COUNT-1)
 * @return Nom ou "?" si hors bornes
 */
const char* getGarlandModeNameById(int id);

/**
 * @brief Passe à l'animation suivante
 */
void nextGarlandAnimation();

/**
 * @brief Passe au mode suivant
 */
void nextGarlandMode();

/**
 * @brief Éteint complètement la guirlande
 */
void garlandOff();

/**
 * @enum MotionSensorType
 * @brief Type de capteur de mouvement détecté
 */
enum MotionSensorType {
    MOTION_SENSOR_PIR = 0,
    MOTION_SENSOR_RCWL,
    MOTION_SENSOR_UNKNOWN
};

/**
 * @brief Retourne le type de capteur de mouvement détecté (PIR ou RCWL-0516)
 */
MotionSensorType getMotionSensorType();

/**
 * @brief Vérifie si un mouvement est détecté (PIR ou RCWL-0516)
 * @return true si mouvement détecté, false sinon
 */
bool isMotionDetected();

/**


/**
 * @brief Indique si une animation est actuellement active (non OFF et guirlande activée)
 * @return true si animation active, false sinon
 */
bool isAnimationActive();

/**
 * @brief Indique si la guirlande doit être allumée selon le mode actuel
 * @return true si la guirlande doit être allumée, false sinon
 */
bool isGarlandEnabled();

// =============================================================================
// GESTION DU NOM D'APPAREIL (mDNS)
// =============================================================================

/**
 * @brief Récupère le nom d'appareil configuré
 * @return Pointeur vers le nom d'appareil (chaîne constante)
 */
const char* getDeviceName();

/**
 * @brief Définit un nouveau nom d'appareil et le sauvegarde en NVS
 * @param name Nouveau nom d'appareil (max 32 caractères, alphanumérique et tiret uniquement)
 * @return true si le nom est valide et a été sauvegardé, false sinon
 */
bool setDeviceName(const char* name);

/**
 * @brief Charge le nom d'appareil depuis NVS
 */
void loadDeviceNameFromNVS();

/**
 * @brief Sauvegarde le nom d'appareil en NVS
 */
void saveDeviceNameToNVS();

/**
 * @brief Valide un nom d'appareil (alphanumérique et tiret uniquement, max 32 caractères)
 * @param name Nom à valider
 * @return true si le nom est valide, false sinon
 */
bool isValidDeviceName(const char* name);

#endif // GARLAND_CONTROL_H
