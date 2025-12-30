int getActiveGuirlandeAnimation(void);
#ifdef __cplusplus
extern "C" {
#endif
int getActiveGarlandAnimation(void);
int getGarlandAnimationInt(void);
int getGarlandModeInt(void);
#ifdef __cplusplus
}
#endif

// Fonctions natives C++ (pour le code C++)
#ifdef __cplusplus
GuirlandeAnimation getGuirlandeAnimation();
GuirlandeMode getGuirlandeMode();
#endif
// Pour affichage du graphe de l'animation active en mode AUTO
#ifdef __cplusplus
extern "C" {
#endif
int getActiveGuirlandeAnimation(void);
GuirlandeAnimation getGuirlandeAnimation(void);
GuirlandeMode getGuirlandeMode(void);
#ifdef __cplusplus
}
#endif
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

enum GarlandMode {
    MODE_PERMANENT = 0,     ///< Toujours allumé
    MODE_MOTION_TRIGGER,    ///< Déclenchement par détection de mouvement
    MODE_COUNT              ///< Nombre total de modes
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

// =============================================================================
// CONFIGURATION
// =============================================================================

#define GARLAND_PWM_FREQUENCY  5000      ///< Fréquence PWM en Hz
#define GARLAND_PWM_RESOLUTION 8         ///< Résolution PWM (8 bits = 0-255)
#define GARLAND_PWM_CHANNEL    0         ///< Canal PWM pour le TB6612FNG

#define MOTION_TRIGGER_DURATION 30000    ///< Durée d'allumage après détection (ms)

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
 * Initialise également les capteurs PIR et LDR.
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

void setGuirlandeMode(GuirlandeMode mode);

/**
 * @brief Récupère le mode de fonctionnement actuel
 * @return Mode actuel
 */
GuirlandeMode getGuirlandeMode();

/**
 * @brief Récupère le nom du mode actuel
 * @return Nom du mode en cours
 */
const char* getGuirlandeModeName();

/**
 * @brief Récupère le nom d'un mode par son identifiant
 * @param id Identifiant (0..G_MODE_COUNT-1)
 * @return Nom ou "?" si hors bornes
 */
const char* getGuirlandeModeNameById(int id);


/**
 * @brief Passe à l'animation suivante
 */
void nextGuirlandeAnimation();

/**
 * @brief Passe au mode suivant
 */
void nextGuirlandeMode();

/**
 * @brief Éteint complètement la guirlande
 */
void guirlandeOff();

/**
 * @brief Vérifie si un mouvement est détecté
 * @return true si mouvement détecté, false sinon
 */
bool isMotionDetected();

/**
/**
 * @brief Récupère la valeur brute du capteur de luminosité
 * @return Valeur ADC du LDR (0-4095 pour ESP32)
 */
int getLightLevel();

/**
 * @brief Indique si une animation est actuellement active (non OFF et guirlande activée)
 * @return true si animation active, false sinon
 */
bool isAnimationActive();
#endif // GARLAND_CONTROL_H
