// ---
// Changelog :
// #4 (2025-12-31) : Détection automatique du capteur de mouvement (PIR ou RCWL-0516), code et documentation adaptés, version 1.2.0
// ---
/**
 * @file board_config.h
 * @brief Mapping optimisé pour ESP32 IdeaSpark (Écran 1.14" intégré)
 * @version 1.8.0
 * @date 2026-01-01
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <Arduino.h>

#define BOARD_NAME "ESP32 IdeaSpark 1.14 LCD"

// ============================================================================
// BOUTON ET LED SYSTÈME
// ============================================================================
#define BUTTON_BOOT    0   ///< Bouton BOOT intégré (GPIO 0)
#define LED_BUILTIN    2   ///< LED bleue intégrée (Attention: Partagée avec LCD_DC)

// ============================================================================
// ÉCRAN LCD INTÉGRÉ (ST7789)
// Ces pins sont câblées en interne sur le PCB de l'IdeaSpark
// ============================================================================
/** @{ */
#define LCD_MOSI 23   ///< SDA (Données SPI)
#define LCD_SCLK 18   ///< SCL (Horloge SPI)
#define LCD_CS   15   ///< Chip Select
#define LCD_DC    2   ///< Data/Command (Aussi relié à la LED bleue)
#define LCD_RST   4   ///< Reset
#define LCD_BLK  32   ///< Backlight (Rétroéclairage - DOIT être à HIGH pour voir l'image)
/** @} */

// ============================================================================
// BUS I2C (Pour périphériques externes)
// ============================================================================
#define I2C_SDA  21
#define I2C_SCL  22

// ============================================================================
// MODULE TB6612FNG (Pilotage Guirlande)
// ============================================================================
/**
 * @note AIN1 déplacé sur GPIO 25 pour éviter le conflit avec le rétroéclairage LCD (32)
 */
#define TB6612_PWMA  12   ///< PWM pour intensité
#define TB6612_AIN1  25   ///< Direction A (Pin 1)
#define TB6612_AIN2  33   ///< Direction A (Pin 2)
#define TB6612_STBY  14   ///< Standby (HIGH = actif)

// ============================================================================
// CAPTEUR DE MOUVEMENT (PIR ou RCWL-0516)
// ============================================================================
#define MOTION_SENSOR_PIN   35   ///< Entrée capteur de mouvement (PIR ou RCWL-0516)

// ============================================================================
// BOUTONS UTILISATEUR EXTERNES
// ============================================================================
#define BUTTON_1     16   ///< Bouton 1 (ex: Changement animation)
#define BUTTON_2     17   ///< Bouton 2 (ex: Changement mode)

// ============================================================================
// MATRICE NEOPIXEL 8x8 WS2812B-64
// ============================================================================
#define MATRIX8X8_PIN        32   ///< Data pin for 8x8 NeoPixel matrix (WS2812B-64)
#define MATRIX8X8_NUMPIXELS  64   ///< Number of pixels in 8x8 matrix

#endif // BOARD_CONFIG_H
