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

// --- Configuration Affichages ---
// ST7789 actif par défaut sauf pour la cible HW-675 (ESP32-C3 + OLED)
#if !defined(TARGET_ESP32C3_HW675)
    #define HAS_ST7789
#endif

// Dimensions ST7789 (IdeaSpark 1.14")
#ifdef HAS_ST7789
    #define ST7789_WIDTH     240   // Largeur de l'écran 1.14" (135x240)
    #define ST7789_HEIGHT    320   // Hauteur de l'écran 1.14"
    #define ST7789_ROTATION  0     // Rotation de l'écran (0, 1, 2, 3)
#endif

// Couleurs de base pour ST7789 (RGB565)
#define COLOR_BLACK      0x0000
#define COLOR_WHITE      0xFFFF
#define COLOR_RED        0xF800
#define COLOR_GREEN      0x07E0
#define COLOR_BLUE       0x001F
#define COLOR_YELLOW     0xFFE0
#define COLOR_CYAN       0x07FF
#define COLOR_MAGENTA    0xF81F
#define COLOR_PURPLE     0x8010
#define COLOR_ORANGE     0xFD20

#define DEFAULT_DISPLAY_MODE DISPLAY_MODE_ANIMATED // Mode d'affichage par défaut (animé/statique/éteint)

#ifndef DISPLAY_MODE_ENUM
#define DISPLAY_MODE_ENUM
/**
 * @enum DisplayMode
 * @brief Modes d'affichage de l'écran LCD
 */
enum DisplayMode {
    DISPLAY_MODE_ANIMATED = 0,   // Animations actuelles
    DISPLAY_MODE_STATIC,         // Affichage fixe (nom, version, SSID, IP)
    DISPLAY_MODE_OFF,            // Écran complètement éteint (backlight + contenu)
    DISPLAY_MODE_COUNT
};
#endif
#endif
