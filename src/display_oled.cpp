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
#include "config.h"
#include "board_config.h"
#include "garland_control.h"
#include "display_oled.h"


#include <U8g2lib.h>
#include <Wire.h>

// Initialisation OLED JMD0.96D-1 (SSD1306 128x64) via I2C matériel
static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

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
    // Ligne 1 : nom projet (gauche), version (droite, décalée d'1px vers le bas)
    u8g2.setFont(u8g2_font_6x12_tr);
        int projW = u8g2.getStrWidth(projectName);
        u8g2.drawStr((OLED_WIDTH - projW) / 2, 12, projectName);
        // Ligne 2 : version (centré, décalée d'1px vers le bas)
        char vbuf[16];
        snprintf(vbuf, sizeof(vbuf), "v%s", projectVersion);
        int verW = u8g2.getStrWidth(vbuf);
        u8g2.drawStr((OLED_WIDTH - verW) / 2, 23, vbuf); // 12+11=23, comme l'écran principal

    // Barre de progression WiFi (centrée)
    if (wifiProgress >= 0 && wifiProgress <= 100) {
        const uint8_t barW = OLED_WIDTH - 32;
        const uint8_t barH = 10;
        const uint8_t barX = 16;
        const uint8_t barY = OLED_HEIGHT/2 - barH/2 + 8;
        u8g2.drawFrame(barX, barY, barW, barH);
        uint8_t fill = (uint8_t)((barW - 2) * wifiProgress / 100);
        if (fill > 0) u8g2.drawBox(barX + 1, barY + 1, fill, barH - 2);
    }
    u8g2.sendBuffer();
}

void displayMainScreen(const char* projectName, const char* projectVersion, const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName, const char* mDnsName) {
    (void)ssid; (void)mDnsName;
    u8g2.clearBuffer();
    // 1. Nom projet (centré, police standard)
    u8g2.setFont(u8g2_font_6x12_tr);
    int projW = u8g2.getStrWidth(projectName);
    u8g2.drawStr((OLED_WIDTH - projW) / 2, 10, projectName);

    // 2. Version (centré, police très petite)
    char vbuf[16];
    snprintf(vbuf, sizeof(vbuf), "v%s", projectVersion);
    u8g2.setFont(u8g2_font_04b_03_tr); // plus petit
    int verW = u8g2.getStrWidth(vbuf);
    u8g2.drawStr((OLED_WIDTH - verW) / 2, 16, vbuf);

    // 3. IP (centré, police plus grande)
    u8g2.setFont(u8g2_font_6x12_tr); // police lisible et disponible
    String ipStr = ip.toString();
    // Tronquer l'IP si trop longue
    while (u8g2.getStrWidth(ipStr.c_str()) > OLED_WIDTH && ipStr.length() > 0) {
        ipStr.remove(ipStr.length() - 1);
    }
    int ipW = u8g2.getStrWidth(ipStr.c_str());
    u8g2.drawStr((OLED_WIDTH - ipW) / 2, 30, ipStr.c_str());

    // 4. Infos : titres à gauche, valeurs à droite, troncature si besoin
    u8g2.setFont(u8g2_font_5x8_tr);
    uint8_t y = 40;
    const uint8_t xLabel = 5; // Décalage de 5px pour les entêtes
    const char* sep = ": ";
    if (animationName && strlen(animationName) > 0) {
        String label = "Gui";
        String value = String(animationName);
        String full = label + sep + value;
        // Tronquer la valeur si trop longue
        while (u8g2.getStrWidth(full.c_str()) > (OLED_WIDTH - xLabel) && value.length() > 0) {
            value.remove(value.length() - 1);
            full = label + sep + value;
        }
        u8g2.drawStr(xLabel, y, full.c_str());
        y += 8;
    }
    if (matrixAnimationName && strlen(matrixAnimationName) > 0) {
        String label = "8x8";
        String value = String(matrixAnimationName);
        String full = label + sep + value;
        while (u8g2.getStrWidth(full.c_str()) > (OLED_WIDTH - xLabel) && value.length() > 0) {
            value.remove(value.length() - 1);
            full = label + sep + value;
        }
        u8g2.drawStr(xLabel, y, full.c_str());
        y += 8;
    }
    if (modeName && strlen(modeName) > 0) {
        String label = "Mode";
        String value = String(modeName);
        String full = label + sep + value;
        while (u8g2.getStrWidth(full.c_str()) > (OLED_WIDTH - xLabel) && value.length() > 0) {
            value.remove(value.length() - 1);
            full = label + sep + value;
        }
        u8g2.drawStr(xLabel, y, full.c_str());
    }

    u8g2.sendBuffer();
    /*
     * OLED UI aesthetic improvements:
     * 1. Version font reduced (u8g2_font_04b_03_tr)
     * 2. IP font increased (u8g2_font_7x14B_1x2_tr, truncated if needed)
     * 3. Info lines (Gui, 8x8, Mode): left-aligned title, right-aligned value, truncated if needed
     * 4. All changes documented and numbered in code
     */
}

void displayScreenByMode(const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName, const char* mDnsName) {
    DisplayMode mode = getDisplayMode();
    if (mode == DISPLAY_MODE_OFF) {
        u8g2.clearBuffer();
        u8g2.sendBuffer();
        u8g2.setPowerSave(1);
        return;
    }
    u8g2.setPowerSave(0);
    displayMainScreen(PROJECT_NAME, PROJECT_VERSION, ssid, ip, modeName, animationName, matrixAnimationName, mDnsName);
}

void updateAnimationVisual(const char* animationName, bool hasMatrix) {
    (void)animationName; (void)hasMatrix;
    // Pour OLED 72x40, pas d'animation lourde: rien à faire.
}


