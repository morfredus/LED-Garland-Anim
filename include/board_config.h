// ---
// Changelog :
// #4 (2025-12-31) : Détection automatique du capteur de mouvement (PIR ou RCWL-0516), code et documentation adaptés, version 1.2.0
// ---
/**
 * @file board_config.h
 * @brief Mapping optimisé pour ESP32 IdeaSpark (Écran 1.14" intégré)
 * @version 1.11.3
 * @date 2026-01-01
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <Arduino.h>

#ifdef TARGET_ESP32S3_MINI
// ============================================================================
// Configuration matérielle — ESP32‑S3 Mini Zero
// Pins accessibles uniquement (gauche + droite)
// ============================================================================

#define BOARD_NAME "ESP32-S3 Mini Zero Garland"

// ============================================================================
// Configuration matérielle — ESP32‑S3 Mini Zero
// Pins accessibles uniquement (gauche + droite)
// ============================================================================

// ---------------------------------------------------------------------------
// Bouton et LED système
// ---------------------------------------------------------------------------
#define BUTTON_BOOT    0     ///< Bouton BOOT intégré (GPIO 0)
#ifndef LED_BUILTIN
#define LED_BUILTIN 8
#endif



// ---------------------------------------------------------------------------
// Bus I2C (périphériques externes)
// Pins accessibles et propres
// ---------------------------------------------------------------------------
#define I2C_SDA       4      ///< SDA
#define I2C_SCL       5      ///< SCL

// ---------------------------------------------------------------------------
// Module TB6612FNG (Pilotage Guirlande)
// Pins alignés côté droit (10–13)
// ---------------------------------------------------------------------------
#define TB6612_PWMA   10     ///< PWM pour intensité
#define TB6612_AIN1   11     ///< Direction A (Pin 1)
#define TB6612_AIN2   12     ///< Direction A (Pin 2)
#define TB6612_STBY   13     ///< Standby (HIGH = actif)

// ---------------------------------------------------------------------------
// Capteur de mouvement (PIR / RCWL-0516)
// ---------------------------------------------------------------------------
#define MOTION_SENSOR_PIN  7   ///< Entrée capteur (GPIO7)

// ---------------------------------------------------------------------------
// Boutons utilisateur externes
// ---------------------------------------------------------------------------
#define BUTTON_1      8      ///< Bouton 1 (GPIO8)
#define BUTTON_2      9      ///< Bouton 2 (GPIO9)

// ---------------------------------------------------------------------------
// Matrice NeoPixel 8x8 WS2812B-64
// ---------------------------------------------------------------------------
#define MATRIX8X8_PIN        7    ///< Data pin NeoPixel (GPIO7)
#define MATRIX8X8_NUMPIXELS  64


#else
// ============================================================================
// Configuration matérielle pour ESP32 IdeaSpark (LCD 1.14" ST7789)
// ============================================================================
#define BOARD_NAME "ESP32 IdeaSpark 1.14 LCD"

// Bouton et LED système
#define BUTTON_BOOT    0   ///< Bouton BOOT intégré (GPIO 0)
#define LED_BUILTIN    2   ///< LED bleue intégrée (Attention: Partagée avec LCD_DC)



// Bus I2C (périphériques externes)
#define I2C_SDA  21
#define I2C_SCL  22

// Module TB6612FNG (Pilotage Guirlande)
#define TB6612_PWMA  12   ///< PWM pour intensité
#define TB6612_AIN1  25   ///< Direction A (Pin 1)
#define TB6612_AIN2  33   ///< Direction A (Pin 2)
#define TB6612_STBY  14   ///< Standby (HIGH = actif)

// Capteur de mouvement (PIR ou RCWL-0516)
#define MOTION_SENSOR_PIN   35   ///< Entrée capteur de mouvement (PIR ou RCWL-0516)

// Boutons utilisateur externes
#define BUTTON_1     16   ///< Bouton 1 (ex: Changement animation)
#define BUTTON_2     17   ///< Bouton 2 (ex: Changement mode)

// Matrice NeoPixel 8x8 WS2812B-64
#define MATRIX8X8_PIN        27   ///< Data pin for 8x8 NeoPixel matrix (WS2812B-64)
#define MATRIX8X8_NUMPIXELS  64   ///< Number of pixels in 8x8 matrix

#endif // TARGET_ESP32S3_MINI

#endif // BOARD_CONFIG_H
