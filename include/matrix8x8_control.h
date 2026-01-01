/**
 * @file matrix8x8_control.h
 * @brief Control for 8x8 NeoPixel WS2812B-64 matrix with festive animations
 * @version 1.6.0
 * @date 2026-01-01
 *
 * Module for managing animations on an 8x8 NeoPixel matrix.
 * Features festive holiday-themed animations including star, meteor, Christmas tree, etc.
 */

#ifndef MATRIX8X8_CONTROL_H
#define MATRIX8X8_CONTROL_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "board_config.h"
#include "config.h"
#include <nvs_flash.h>
#include <nvs.h>

// =============================================================================
// CONSTANTS
// =============================================================================

#define NVS_NAMESPACE_MATRIX "matrix8x8"  ///< NVS namespace for matrix persistence

/**
 * @enum Matrix8x8Animation
 * @brief Available animations for 8x8 NeoPixel matrix
 */
enum Matrix8x8Animation {
    MATRIX_ANIM_OFF = 0,        ///< Matrix off
    MATRIX_ANIM_STAR,           ///< Twinkling star
    MATRIX_ANIM_METEOR,         ///< Meteor shower
    MATRIX_ANIM_SHOOTING_STAR,  ///< Shooting star
    MATRIX_ANIM_SANTA,          ///< Santa Claus silhouette
    MATRIX_ANIM_TREE,           ///< Christmas tree
    MATRIX_ANIM_BELL,           ///< Ringing bell
    MATRIX_ANIM_SNOW,           ///< Falling snow
    MATRIX_ANIM_GIFT,           ///< Gift box
    MATRIX_ANIM_CANDLE,         ///< Flickering candle
    MATRIX_ANIM_SNOWFLAKE,      ///< Rotating snowflake
    MATRIX_ANIM_COUNT           ///< Total number of animations
};

// =============================================================================
// FUNCTION PROTOTYPES
// =============================================================================

/**
 * @brief Initialize the 8x8 NeoPixel matrix
 *
 * Configures GPIO pin and starts the NeoPixel library.
 * Loads saved settings from NVS and starts the sparkling star animation.
 */
void setupMatrix8x8();

/**
 * @brief Main update loop for matrix animations
 *
 * Must be called regularly in loop() to update the current animation.
 */
void updateMatrix8x8();

/**
 * @brief Set the current matrix animation
 * @param animation The animation to display
 */
void setMatrix8x8Animation(Matrix8x8Animation animation);

/**
 * @brief Get the current matrix animation
 * @return Current animation ID
 */
Matrix8x8Animation getMatrix8x8Animation();

/**
 * @brief Get the name of the current animation
 * @return Animation name string
 */
const char* getMatrix8x8AnimationName();

/**
 * @brief Get animation name by ID
 * @param id Animation ID (0..MATRIX_ANIM_COUNT-1)
 * @return Animation name or "?" if out of bounds
 */
const char* getMatrix8x8AnimationNameById(int id);

/**
 * @brief Cycle to the next animation
 */
void nextMatrix8x8Animation();

/**
 * @brief Turn off the matrix completely
 */
void matrix8x8Off();

/**
 * @brief Set matrix brightness
 * @param brightness Brightness value (0-255)
 */
void setMatrix8x8Brightness(uint8_t brightness);

/**
 * @brief Get current matrix brightness
 * @return Current brightness (0-255)
 */
uint8_t getMatrix8x8Brightness();

/**
 * @brief Load matrix settings from NVS
 */
void loadMatrix8x8Settings();

/**
 * @brief Save matrix settings to NVS
 */
void saveMatrix8x8Settings();

/**
 * @brief Check if matrix animation is active
 * @return true if animation is running (not OFF)
 */
bool isMatrix8x8Active();

#endif // MATRIX8X8_CONTROL_H
