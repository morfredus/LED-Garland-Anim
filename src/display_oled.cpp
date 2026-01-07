/**
 * @file display_oled.cpp
 * @brief Implémentation de l'affichage OLED (U8g2 SSD1306 72x40) pour ESP32-C3 HW-675
 * @version 5.2.0
 * @date 2026-01-07
 * 
 * GESTION DES MODES D'AFFICHAGE:
 * 1. DISPLAY_MODE_ANIMATED (0) - Affichage actif avec IP + Mode
 * 2. DISPLAY_MODE_STATIC (1)   - Affichage actif avec IP + Mode (identique pour OLED)
 * 3. DISPLAY_MODE_OFF (2)      - Écran complètement éteint (setPowerSave(1))
 */

#include <Arduino.h>
#include "display.h"
#include "config.h"
#include "board_config.h"
#include "garland_control.h"

#ifdef HAS_OLED_U8G2

#include <U8g2lib.h>
#include <Wire.h>

// Initialisation OLED 0.42" (72x40) via I2C matériel
// Pour HW_I2C, ne PAS passer SCL/SDA au constructeur, juste rotation et reset
static U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

static void i2cScan() {
    LOG_PRINTLN("[I2C] Scanning bus...");
    uint8_t found = 0;
    for (uint8_t addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            found++;
            LOG_PRINTF("[I2C] Device at 0x%02X\n", addr);
        }
    }
    if (found == 0) LOG_PRINTLN("[I2C] No devices found");
}

static void drawHeader(const char* projectName, const char* projectVersion) {
    u8g2.setFont(u8g2_font_04b_03_tr);
    u8g2.drawStr(0, 8, projectName);
    // Version à droite
    char vbuf[16];
    snprintf(vbuf, sizeof(vbuf), "v%s", projectVersion);
    int w = u8g2.getStrWidth(vbuf);
    u8g2.drawStr(OLED_WIDTH - w, 8, vbuf);
}

static void drawInfoLine(const char* label, const String& value, uint8_t y) {
    u8g2.setFont(u8g2_font_04b_03_tr);
    u8g2.drawStr(0, y, label);
    // Valeur à droite (tronquée si besoin)
    String v = value;
    while (u8g2.getStrWidth(v.c_str()) > (OLED_WIDTH - 22) && v.length() > 0) {
        v.remove(v.length() - 1);
    }
    int w = u8g2.getStrWidth(v.c_str());
    u8g2.drawStr(OLED_WIDTH - w, y, v.c_str());
}

void setupDisplay() {
    LOG_PRINTLN("[OLED] Initializing I2C...");
    Wire.begin(I2C_SDA, I2C_SCL);
    delay(100);
    LOG_PRINTLN("[OLED] I2C started");
    
    i2cScan();
    
    LOG_PRINTLN("[OLED] Initializing U8g2...");
    u8g2.begin();
    u8g2.setPowerSave(0);
    u8g2.setContrast(255);
    LOG_PRINTLN("[OLED] U8g2 initialized");

    // Écran de test immédiat pour valider l'affichage
    u8g2.clearBuffer();
    u8g2.drawFrame(0, 0, OLED_WIDTH, OLED_HEIGHT);
    u8g2.setFont(u8g2_font_04b_03_tr);
    u8g2.drawStr(2, 12, "OLED OK");
    u8g2.drawStr(2, 24, "Init...");
    u8g2.sendBuffer();
    LOG_PRINTLN("[OLED] Test screen displayed");
}

void displayBootScreen(const char* projectName, const char* projectVersion, int wifiProgress) {
    u8g2.clearBuffer();
    u8g2.drawFrame(0, 0, OLED_WIDTH, OLED_HEIGHT);
    drawHeader(projectName, projectVersion);

    // Barre de progression WiFi optionnelle
    if (wifiProgress >= 0 && wifiProgress <= 100) {
        const uint8_t barY = OLED_HEIGHT - 8;
        const uint8_t barW = OLED_WIDTH - 8;
        u8g2.drawFrame(4, barY, barW, 4);
        uint8_t fill = (uint8_t)((barW - 2) * wifiProgress / 100);
        if (fill > 0) u8g2.drawBox(5, barY + 1, fill, 2);
    }
    u8g2.sendBuffer();
}

void displayMainScreen(const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName, const char* mDnsName) {
    (void)ssid; (void)animationName; (void)matrixAnimationName; (void)mDnsName;
    LOG_PRINTLN("[OLED] displayMainScreen start");
    
    u8g2.clearBuffer();
    yield();
    
    // Affichage simplifié: juste IP et Mode sur 72x40
    u8g2.setFont(u8g2_font_5x7_tr);
    
    // IP en haut
    String ipStr = ip.toString();
    u8g2.drawStr(2, 10, "IP:");
    u8g2.drawStr(2, 20, ipStr.c_str());
    yield();
    
    // Mode en bas
    String modeStr = (modeName != nullptr) ? String(modeName) : String("OK");
    // Tronquer le mode si trop long
    while (u8g2.getStrWidth(modeStr.c_str()) > (OLED_WIDTH - 4) && modeStr.length() > 0) {
        modeStr.remove(modeStr.length() - 1);
    }
    u8g2.drawStr(2, 35, modeStr.c_str());
    yield();

    u8g2.sendBuffer();
    LOG_PRINTLN("[OLED] displayMainScreen done");
}

void displayScreenByMode(const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName, const char* mDnsName) {
    DisplayMode mode = getDisplayMode();
    LOG_PRINTF("[OLED] displayScreenByMode called - mode=%d\n", (int)mode);
    
    switch (mode) {
        case DISPLAY_MODE_ANIMATED:
        case DISPLAY_MODE_STATIC:
            // Pour OLED 72x40, les modes animé et statique sont identiques (pas assez d'espace pour animations)
            LOG_PRINTLN("[OLED] Mode ANIMATED/STATIC - Activating display");
            u8g2.setPowerSave(0);  // Rallumer l'OLED si éteint
            displayMainScreen(ssid, ip, modeName, animationName, matrixAnimationName, mDnsName);
            break;
            
        case DISPLAY_MODE_OFF:
            // Éteindre complètement l'OLED
            LOG_PRINTLN("[OLED] Mode OFF - Turning off display");
            u8g2.clearBuffer();    // Effacer le buffer d'abord
            u8g2.sendBuffer();     // Envoyer le buffer vide
            u8g2.setPowerSave(1);  // Mettre en veille (éteint l'écran)
            break;
            
        default:
            LOG_PRINTLN("[OLED] Unknown display mode - defaulting to ON");
            u8g2.setPowerSave(0);
            displayMainScreen(ssid, ip, modeName, animationName, matrixAnimationName, mDnsName);
            break;
    }
    
    LOG_PRINTLN("[OLED] displayScreenByMode done");
}

void updateAnimationVisual(const char* animationName, bool hasMatrix) {
    (void)animationName; (void)hasMatrix;
    // Pour OLED 72x40, pas d'animation lourde: rien à faire.
}

#endif // HAS_OLED_U8G2
