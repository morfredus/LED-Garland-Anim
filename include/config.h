// ---
// Changelog :
// #3 (2025-12-30) : Harmonisation LCD ST7789 unique, suppression TFT/ILI9341, OLED secours, macros LCD
// ---
#ifndef CONFIG_H
#define CONFIG_H

// --- Configuration Globale ---
#define SERIAL_BAUD_RATE 115200
#define WIFI_TIMEOUT_MS  10000 // 10 secondes pour tenter la connexion

// Debug : Décommenter pour voir les logs détaillés
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


// --- Configuration LCD ST7789 (remplace TFT) ---
// Décommenter pour activer l'affichage LCD ST7789
#define HAS_LCD
#define LCD_WIDTH     135   // Largeur de l'écran en pixels (portrait)
#define LCD_HEIGHT    240   // Hauteur de l'écran (portrait)
#define LCD_ROTATION  1     // Rotation de l'écran (0, 1, 2, 3)

// Couleurs de base pour LCD ST7789 (RGB565)
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

// Changement #3 (2025-12-30) : Suppression du support TFT, LCD ST7789 unique

#endif