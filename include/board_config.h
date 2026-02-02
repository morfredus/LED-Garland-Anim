/**
 * @file board_config.h
 * @brief Configuration materielle multi-cartes (ESP32-S3 Super Mini, ESP32 Wroom)
 * @version 5.6.5
 * @date 2026-02-02
 *
 * Cartes supportees :
 * - ESP32-S3 Super Mini (TARGET_ESP32S3_MINI) - Carte par defaut
 * - ESP32 Wroom DevKit V1 (TARGET_ESP32_WROOM)
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <Arduino.h>

// ============================================================================
// ESP32-S3 Super Mini
// ============================================================================
#ifdef TARGET_ESP32S3_MINI

#define BOARD_NAME "ESP32-S3 Super Mini"

// ---------------------------------------------------------------------------
// Bouton et LED systeme
// ---------------------------------------------------------------------------
#define BUTTON_BOOT    0     ///< Bouton BOOT integre (GPIO 0)
#ifndef LED_BUILTIN
#define LED_BUILTIN    8     ///< LED integree (GPIO 8)
#endif

// ---------------------------------------------------------------------------
// Bus I2C (OLED SSD1306)
// ---------------------------------------------------------------------------
#define I2C_SDA        4     ///< SDA (GPIO 4)
#define I2C_SCL        5     ///< SCL (GPIO 5)

// ---------------------------------------------------------------------------
// Module TB6612FNG (Pilotage Guirlande)
// ---------------------------------------------------------------------------
#define TB6612_PWMA   10     ///< PWM pour intensite (GPIO 10)
#define TB6612_AIN1   11     ///< Direction A Pin 1 (GPIO 11)
#define TB6612_AIN2   12     ///< Direction A Pin 2 (GPIO 12)
#define TB6612_STBY   13     ///< Standby - HIGH = actif (GPIO 13)

// ---------------------------------------------------------------------------
// Capteur de mouvement (PIR / RCWL-0516)
// ---------------------------------------------------------------------------
#define MOTION_SENSOR_PIN  2 ///< Entree capteur de mouvement (GPIO 2)

// ---------------------------------------------------------------------------
// Bouton utilisateur
// ---------------------------------------------------------------------------
#define BUTTON_1       8     ///< Bouton utilisateur (GPIO 8)

// ---------------------------------------------------------------------------
// Matrice NeoPixel 8x8 WS2812B-64
// ---------------------------------------------------------------------------
#define MATRIX8X8_PIN        7    ///< Data pin NeoPixel (GPIO 7)
#define MATRIX8X8_NUMPIXELS  64   ///< Nombre de pixels (8x8)

// ============================================================================
// ESP32 Wroom DevKit V1
// ============================================================================
#elif defined(TARGET_ESP32_WROOM)

#define BOARD_NAME "ESP32 Wroom DevKit V1"

// ---------------------------------------------------------------------------
// Bouton et LED systeme
// ---------------------------------------------------------------------------
#define BUTTON_BOOT    0     ///< Bouton BOOT integre (GPIO 0)
#define LED_BUILTIN    2     ///< LED integree (GPIO 2)

// ---------------------------------------------------------------------------
// Bus I2C (OLED SSD1306)
// ---------------------------------------------------------------------------
#define I2C_SDA       21     ///< SDA (GPIO 21)
#define I2C_SCL       22     ///< SCL (GPIO 22)

// ---------------------------------------------------------------------------
// Module TB6612FNG (Pilotage Guirlande)
// ---------------------------------------------------------------------------
#define TB6612_PWMA   12     ///< PWM pour intensite (GPIO 12)
#define TB6612_AIN1   25     ///< Direction A Pin 1 (GPIO 25)
#define TB6612_AIN2   33     ///< Direction A Pin 2 (GPIO 33)
#define TB6612_STBY   14     ///< Standby - HIGH = actif (GPIO 14)

// ---------------------------------------------------------------------------
// Capteur de mouvement (PIR / RCWL-0516)
// ---------------------------------------------------------------------------
#define MOTION_SENSOR_PIN  35 ///< Entree capteur de mouvement (GPIO 35)

// ---------------------------------------------------------------------------
// Bouton utilisateur
// ---------------------------------------------------------------------------
#define BUTTON_1      16     ///< Bouton utilisateur (GPIO 16)

// ---------------------------------------------------------------------------
// Matrice NeoPixel 8x8 WS2812B-64
// ---------------------------------------------------------------------------
#define MATRIX8X8_PIN        27   ///< Data pin NeoPixel (GPIO 27)
#define MATRIX8X8_NUMPIXELS  64   ///< Nombre de pixels (8x8)

#else
// ============================================================================
// Erreur : Aucune carte cible definie
// ============================================================================
#error "Aucune carte cible definie. Utilisez TARGET_ESP32S3_MINI ou TARGET_ESP32_WROOM dans platformio.ini"

#endif // TARGET_ESP32S3_MINI / TARGET_ESP32_WROOM

#endif // BOARD_CONFIG_H
