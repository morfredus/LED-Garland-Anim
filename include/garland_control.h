/**
 * @file garland_control.h
 * @brief Contrôle des animations de guirlande LED bi-directionnelle
 * @version 0.5.1
 * @date 2025-12-10
 * 
 * Module de gestion des animations pour guirlande LED à 2 fils avec LEDs en anti-parallèle.
 * Utilise le module TB6612FNG pour contrôler la direction du courant et l'intensité lumineuse.
 */

#ifndef GARLAND_CONTROL_H
#define GARLAND_CONTROL_H

#include <Arduino.h>
#include "board_config.h"
#include "config.h"

// =============================================================================
// CONSTANTES D'ANIMATION
// =============================================================================

/**
 * @enum GarlandAnimation
 * @brief Types d'animations disponibles pour la guirlande
 */
enum GarlandAnimation {
    ANIM_OFF = 0,           ///< Guirlande éteinte
    ANIM_FADE_ALTERNATE,    ///< Fade alterné entre Sens A et B
    ANIM_BLINK_ALTERNATE,   ///< Clignotement alterné
    ANIM_SMOOTH_WAVE,       ///< Onde douce
    ANIM_STROBE,            ///< Effet stroboscope
    ANIM_PULSE,             ///< Pulsation simultanée
    ANIM_CHASE,             ///< Effet de poursuite
    ANIM_HEARTBEAT,         ///< Battement de coeur
    ANIM_SPARKLE,           ///< Scintillement aléatoire
    ANIM_RAINBOW_WAVE,      ///< Vague arc-en-ciel
    ANIM_BREATHING,         ///< Respiration lente
    ANIM_FIRE,              ///< Effet feu
    ANIM_TWINKLE,           ///< Clignotement doux
    ANIM_METEOR,            ///< Effet météore
    ANIM_AUTO,              ///< Mode automatique (toutes les animations)
    ANIM_COUNT              ///< Nombre total d'animations
};

/**
 * @enum GarlandMode
 * @brief Modes de fonctionnement de la guirlande
 */
enum GarlandMode {
    MODE_PERMANENT = 0,     ///< Toujours allumé
    MODE_MOTION_TRIGGER,    ///< Déclenchement par détection de mouvement
    MODE_COUNT              ///< Nombre total de modes
};

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
