/**
 * @file config.h
 * @brief Configuration globale du projet
 * @version 5.2.0
 * @date 2026-01-07
 */

#ifndef CONFIG_H
#define CONFIG_H

// --- Configuration Globale ---
#define SERIAL_BAUD_RATE 115200
#define WIFI_TIMEOUT_MS  10000 // 10 secondes pour tenter la connexion

// --- Configuration mDNS (Nom unique d'accès) ---
#define DEFAULT_DEVICE_NAME "garland"  // Nom par défaut pour mDNS (ex: garland.local)
#define MAX_DEVICE_NAME_LEN 32         // Longueur maximale du nom d'appareil

// --- Configuration Durées d'animations (en millisecondes) ---
#define DEFAULT_GARLAND_ANIM_INTERVAL 30000  // Intervalle par défaut guirlande (mode AUTO)
#define DEFAULT_MATRIX_ANIM_INTERVAL 30000   // Intervalle par défaut matrice (mode AUTO)
#define MOTION_TRIGGER_DEFAULT 30000         // Durée d'allumage après détection mouvement
#define MIN_ANIMATION_INTERVAL 5000          // Minimum : 5 secondes
#define MAX_ANIMATION_INTERVAL 300000        // Maximum : 5 minutes

// Debug : Décommenter pour voir les logs détaillées
#define ENABLE_DEBUG_LOG

#ifdef ENABLE_DEBUG_LOG
    #define LOG_PRINT(...) Serial.print(__VA_ARGS__)
    #define LOG_PRINTLN(...) Serial.println(__VA_ARGS__)
    #define LOG_PRINTF(...) Serial.printf(__VA_ARGS__)
#else
    #define LOG_PRINT(...)
    #define LOG_PRINTLN(...)
    #define LOG_PRINTF(...)
#endif

// --- Configuration Affichage OLED uniquement ---
#define HAS_OLED_U8G2

// Dimensions OLED JMD0.96D-1 (128x64)
#define OLED_WIDTH  128
#define OLED_HEIGHT 64

#define DEFAULT_DISPLAY_MODE DISPLAY_MODE_ANIMATED // Mode d'affichage par défaut (animé/statique/éteint)

#ifndef DISPLAY_MODE_ENUM
#define DISPLAY_MODE_ENUM
/**
 * @enum DisplayMode
 * @brief Modes d'affichage de l'écran OLED
 */
enum DisplayMode {
    DISPLAY_MODE_ANIMATED = 0,   // Affichage animé (IP + Mode)
    DISPLAY_MODE_STATIC,         // Affichage statique (identique OLED)
    DISPLAY_MODE_OFF,            // Écran complètement éteint
    DISPLAY_MODE_COUNT
};
#endif
#endif
