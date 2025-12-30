/**
 * @file garland_control.h
 * @brief Contrôle des animations de guirlande LED bi-directionnelle
 * @version 0.8.0
 * @date 2025-12-13
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

// =============================================================================
// CONSTANTES D'ANIMATION
// =============================================================================

#define NVS_NAMESPACE "garland"  ///< Espace de noms NVS pour la persistence

/**
 * @enum GuirlandeAnimation
 * @brief Types d'animations disponibles pour la guirlande monochrome 2 fils
 */
enum GuirlandeAnimation {
    G_ANIM_OFF = 0,           ///< Guirlande éteinte
    G_ANIM_FADE_ALTERNATE,    ///< Fade alterné entre Sens A et B
    G_ANIM_BLINK_ALTERNATE,   ///< Clignotement alterné
    G_ANIM_PULSE,             ///< Pulsation simultanée
    G_ANIM_BREATHING,         ///< Respiration lente
    G_ANIM_STROBE,            ///< Flash stroboscopique rapide
    G_ANIM_HEARTBEAT,         ///< Double pulsation (battement de cœur)
    G_ANIM_WAVE,              ///< Vague sinusoïdale fluide
    G_ANIM_SPARKLE,           ///< Scintillement aléatoire
    G_ANIM_METEOR,            ///< Traînée lumineuse avec estompage
    G_ANIM_AUTO,              ///< Mode automatique (cycle toutes les animations)
    G_ANIM_COUNT              ///< Nombre total d'animations
};

/**
 * @enum GuirlandeMode
 * @brief Modes de fonctionnement de la guirlande
 */
enum GuirlandeMode {
    G_MODE_PERMANENT = 0,     ///< Toujours allumé
    G_MODE_MOTION_TRIGGER,    ///< Déclenchement par détection de mouvement
    G_MODE_COUNT              ///< Nombre total de modes
};

// Aliases pour compatibilité avec l'ancienne API
typedef GuirlandeAnimation GarlandAnimation;
typedef GuirlandeMode GarlandMode;
#define ANIM_OFF G_ANIM_OFF
#define ANIM_FADE_ALTERNATE G_ANIM_FADE_ALTERNATE
#define ANIM_BLINK_ALTERNATE G_ANIM_BLINK_ALTERNATE
#define ANIM_PULSE G_ANIM_PULSE
#define ANIM_BREATHING G_ANIM_BREATHING
#define ANIM_STROBE G_ANIM_STROBE
#define ANIM_HEARTBEAT G_ANIM_HEARTBEAT
#define ANIM_WAVE G_ANIM_WAVE
#define ANIM_SPARKLE G_ANIM_SPARKLE
#define ANIM_METEOR G_ANIM_METEOR
#define ANIM_AUTO G_ANIM_AUTO
#define ANIM_COUNT G_ANIM_COUNT
#define MODE_PERMANENT G_MODE_PERMANENT
#define MODE_MOTION_TRIGGER G_MODE_MOTION_TRIGGER
#define MODE_COUNT G_MODE_COUNT

// =============================================================================
// CONFIGURATION
// =============================================================================

#define GARLAND_PWM_FREQUENCY  5000      ///< Fréquence PWM en Hz
#define GARLAND_PWM_RESOLUTION 8         ///< Résolution PWM (8 bits = 0-255)
#define GARLAND_PWM_CHANNEL    0         ///< Canal PWM pour le TB6612FNG

#define MOTION_TRIGGER_DURATION 30000    ///< Durée d'allumage après détection (ms)

// =============================================================================
// PROTOTYPES DE FONCTIONS
// =============================================================================

#ifdef __cplusplus
extern "C" {
#endif

// Durées configurables (exposées via l'interface Web)
unsigned long getAutoAnimationIntervalMs(void);
void setAutoAnimationIntervalMs(unsigned long ms);
unsigned long getMotionTriggerDurationMs(void);
void setMotionTriggerDurationMs(unsigned long ms);

// Sauvegarde/restauration NVS
void loadGarlandSettings(void);
void saveGarlandSettings(void);

// Fonctions d'initialisation et mise à jour
void setupGarland(void);
void updateGarland(void);

// Fonctions pour récupérer l'animation/mode actif sous forme d'entier (pour LCD display)
int getActiveGuirlandeAnimation(void);
int getGuirlandeAnimationInt(void);
int getGuirlandeModeInt(void);

#ifdef __cplusplus
}
#endif

// Fonctions C++ natives
#ifdef __cplusplus

/**
 * @brief Change l'animation actuelle
 * @param animation Nouvelle animation à afficher
 */
void setGuirlandeAnimation(GuirlandeAnimation animation);

/**
 * @brief Récupère l'animation actuelle
 * @return Animation en cours
 */
GuirlandeAnimation getGuirlandeAnimation(void);

/**
 * @brief Récupère le nom de l'animation actuelle
 * @return Nom de l'animation en cours
 */
const char* getGuirlandeAnimationName(void);

/**
 * @brief Récupère le nom d'une animation par son identifiant
 * @param id Identifiant (0..G_ANIM_COUNT-1)
 * @return Nom ou "?" si hors bornes
 */
const char* getGuirlandeAnimationNameById(int id);

/**
 * @brief Change le mode de fonctionnement
 * @param mode Nouveau mode
 */
void setGuirlandeMode(GuirlandeMode mode);

/**
 * @brief Récupère le mode de fonctionnement actuel
 * @return Mode actuel
 */
GuirlandeMode getGuirlandeMode(void);

/**
 * @brief Récupère le nom du mode actuel
 * @return Nom du mode en cours
 */
const char* getGuirlandeModeName(void);

/**
 * @brief Récupère le nom d'un mode par son identifiant
 * @param id Identifiant (0..G_MODE_COUNT-1)
 * @return Nom ou "?" si hors bornes
 */
const char* getGuirlandeModeNameById(int id);

/**
 * @brief Passe à l'animation suivante
 */
void nextGuirlandeAnimation(void);

/**
 * @brief Passe au mode suivant
 */
void nextGuirlandeMode(void);

/**
 * @brief Éteint complètement la guirlande
 */
void guirlandeOff(void);

/**
 * @brief Vérifie si un mouvement est détecté
 * @return true si mouvement détecté, false sinon
 */
bool isMotionDetected(void);

/**
 * @brief Récupère la valeur brute du capteur de luminosité
 * @return Valeur ADC du LDR (0-4095 pour ESP32)
 */
int getLightLevel(void);

/**
 * @brief Indique si une animation est actuellement active (non OFF et guirlande activée)
 * @return true si animation active, false sinon
 */
bool isAnimationActive(void);

// Aliases pour compatibilité avec l'ancienne API "Garland"
inline void setGarlandAnimation(GarlandAnimation animation) { setGuirlandeAnimation(animation); }
inline GarlandAnimation getGarlandAnimation(void) { return getGuirlandeAnimation(); }
inline const char* getGarlandAnimationName(void) { return getGuirlandeAnimationName(); }
inline const char* getGarlandAnimationNameById(int id) { return getGuirlandeAnimationNameById(id); }
inline void setGarlandMode(GarlandMode mode) { setGuirlandeMode(mode); }
inline GarlandMode getGarlandMode(void) { return getGuirlandeMode(); }
inline const char* getGarlandModeName(void) { return getGuirlandeModeName(); }
inline const char* getGarlandModeNameById(int id) { return getGuirlandeModeNameById(id); }
inline void nextGarlandAnimation(void) { nextGuirlandeAnimation(); }
inline void nextGarlandMode(void) { nextGuirlandeMode(); }
inline void garlandOff(void) { guirlandeOff(); }

#endif // __cplusplus

#endif // GARLAND_CONTROL_H
