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

// --- Configuration OLED (SSD1306) ---
// Décommenter pour activer l'affichage OLED
#define HAS_OLED
#define OLED_WIDTH       128
#define OLED_HEIGHT      32   // 64 pour 128x64, 32 pour 128x32
#define OLED_ADDR        0x3C  // Adresse I2C standard (0x3D sur certains modèles)
#define OLED_RESET       -1    // Pas de pin de reset (-1)

// --- Configuration ST7789 (TFT couleur) ---
// Décommenter pour activer l'affichage ST7789
#define HAS_ST7789
#define ST7789_WIDTH     240   // Largeur de l'écran en pixels
#define ST7789_HEIGHT    240   // Hauteur de l'écran (240 pour carré, 135 pour rectangulaire)
#define ST7789_ROTATION  2     // Rotation de l'écran (0, 1, 2, 3)

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

#endif