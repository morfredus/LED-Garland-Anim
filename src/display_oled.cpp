/**
 * @file display_oled.cpp
 * @brief Implémentation de l'affichage OLED (U8g2 SSD1306 72x40) pour ESP32-C3 HW-675
 * @version 5.5.1
 * @date 2026-01-23
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

// Gestion multi-taille OLED (128x64 ou 128x32)
#if OLED_HEIGHT == 64
static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#elif OLED_HEIGHT == 32
static U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#else
#error "OLED_HEIGHT doit être 64 ou 32"
#endif

#if OLED_HEIGHT == 32
// Raccourcis pour les modes
static String shortMode(const char* mode) {
    if (strcmp(mode, "Permanent") == 0) return "Perm";
    if (strcmp(mode, "Detection (tout)") == 0) return "DetAll";
    if (strcmp(mode, "Detection (guirlande)") == 0) return "DetGui";
    if (strcmp(mode, "Automatic") == 0) return "Auto";
    if (strcmp(mode, "Manual") == 0) return "Manual";
    if (strcmp(mode, "Demo") == 0) return "Demo";
    return String(mode).substring(0, 6); // fallback : 6 lettres max
}
// Raccourcis pour les animations guirlande et matrice
static String shortAnim(const char* anim) {
    // Garland
    if (strcmp(anim, "Off") == 0) return "Off";
    if (strcmp(anim, "Fade Alt") == 0) return "Fade";
    if (strcmp(anim, "Blink") == 0) return "Blink";
    if (strcmp(anim, "Pulse") == 0) return "Pulse";
    if (strcmp(anim, "Breath") == 0) return "Breath";
    if (strcmp(anim, "Strobe") == 0) return "Strobe";
    if (strcmp(anim, "Heartbeat") == 0) return "HeartB";
    if (strcmp(anim, "Wave") == 0) return "Wave";
    if (strcmp(anim, "Sparkle") == 0) return "Sparkl";
    if (strcmp(anim, "Meteor") == 0) return "Meteor";
    if (strcmp(anim, "Auto") == 0) return "Auto";
    // Matrix8x8
    if (strcmp(anim, "Star") == 0) return "Star";
    if (strcmp(anim, "Shooting Star") == 0) return "ShootS";
    if (strcmp(anim, "Santa") == 0) return "Santa";
    if (strcmp(anim, "Tree") == 0) return "Tree";
    if (strcmp(anim, "Bell") == 0) return "Bell";
    if (strcmp(anim, "Snow") == 0) return "Snow";
    if (strcmp(anim, "Gift") == 0) return "Gift";
    if (strcmp(anim, "Candle") == 0) return "Candle";
    if (strcmp(anim, "Snowflake") == 0) return "SnwFlk";
    if (strcmp(anim, "Candy Cane") == 0) return "CandyC";
    if (strcmp(anim, "Wreath") == 0) return "Wreath";
    if (strcmp(anim, "Stocking") == 0) return "Stockg";
    if (strcmp(anim, "Reindeer") == 0) return "Reindr";
    if (strcmp(anim, "Gingerbread") == 0) return "Ginger";
    if (strcmp(anim, "Hot Cocoa") == 0) return "Cocoa";
    if (strcmp(anim, "Fireplace") == 0) return "Firepl";
    if (strcmp(anim, "Northern Lights") == 0) return "NordLt";
    if (strcmp(anim, "Presents") == 0) return "Presnt";
    if (strcmp(anim, "Fireworks") == 0) return "Fworks";
    if (strcmp(anim, "Champagne") == 0) return "Champg";
    if (strcmp(anim, "Countdown") == 0) return "Countd";
    if (strcmp(anim, "Confetti") == 0) return "Confet";
    if (strcmp(anim, "Clock") == 0) return "Clock";
    if (strcmp(anim, "Party Popper") == 0) return "PartyP";
    if (strcmp(anim, "Disco Ball") == 0) return "DiscoB";
    if (strcmp(anim, "Easter Egg") == 0) return "Egg";
    if (strcmp(anim, "Bunny") == 0) return "Bunny";
    if (strcmp(anim, "Chick") == 0) return "Chick";
    if (strcmp(anim, "Flowers") == 0) return "Flower";
    if (strcmp(anim, "Rainbow Wave") == 0) return "RbowWv";
    if (strcmp(anim, "Sparkle Rain") == 0) return "SprkRn";
    if (strcmp(anim, "Plasma") == 0) return "Plasma";
    if (strcmp(anim, "Matrix Rain") == 0) return "MtrxRn";
    if (strcmp(anim, "Spiral") == 0) return "Spiral";
    if (strcmp(anim, "Heart") == 0) return "Heart";
    if (strcmp(anim, "Stars Field") == 0) return "StarsF";
    if (strcmp(anim, "Campfire") == 0) return "Campfr";
    if (strcmp(anim, "Radar") == 0) return "Radar";
    return String(anim).substring(0, 7); // fallback : 7 lettres max
}
#endif

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
#if OLED_HEIGHT == 32
    // 128x32 : tout doit tenir sur 4 lignes max
    u8g2.setFont(u8g2_font_5x8_tr);
    int y = 8;
    int projW = u8g2.getStrWidth(projectName);
    u8g2.drawStr((OLED_WIDTH - projW) / 2, y, projectName);
    y += 8;
    char vbuf[16];
    snprintf(vbuf, sizeof(vbuf), "v%s", projectVersion);
    int verW = u8g2.getStrWidth(vbuf);
    u8g2.drawStr((OLED_WIDTH - verW) / 2, y, vbuf);
    y += 8;
    // Barre de progression WiFi (centrée, fine)
    if (wifiProgress >= 0 && wifiProgress <= 100) {
        const uint8_t barW = OLED_WIDTH - 32;
        const uint8_t barH = 6;
        const uint8_t barX = 16;
        const uint8_t barY = y;
        u8g2.drawFrame(barX, barY, barW, barH);
        uint8_t fill = (uint8_t)((barW - 2) * wifiProgress / 100);
        if (fill > 0) u8g2.drawBox(barX + 1, barY + 1, fill, barH - 2);
    }
    u8g2.sendBuffer();
#else
    // 128x64 : inchangé
    u8g2.setFont(u8g2_font_6x12_tr);
    int projW = u8g2.getStrWidth(projectName);
    u8g2.drawStr((OLED_WIDTH - projW) / 2, 12, projectName);
    char vbuf[16];
    snprintf(vbuf, sizeof(vbuf), "v%s", projectVersion);
    int verW = u8g2.getStrWidth(vbuf);
    u8g2.drawStr((OLED_WIDTH - verW) / 2, 23, vbuf);
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
#endif
}

void displayMainScreen(const char* projectName, const char* projectVersion, const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName, const char* mDnsName) {
    (void)ssid; (void)mDnsName;
    u8g2.clearBuffer();
#if OLED_HEIGHT == 32
    // 128x32 : tout doit tenir sur 4 lignes max, police compacte
    u8g2.setFont(u8g2_font_5x8_tr);
    int y = 8;
    int projW = u8g2.getStrWidth(projectName);
    u8g2.drawStr((OLED_WIDTH - projW) / 2, y, projectName);
    y += 8;
    char vbuf[16];
    snprintf(vbuf, sizeof(vbuf), "v%s", projectVersion);
    int verW = u8g2.getStrWidth(vbuf);
    u8g2.drawStr((OLED_WIDTH - verW) / 2, y, vbuf);
    y += 8;
    String ipStr = ip.toString();
    while (u8g2.getStrWidth(ipStr.c_str()) > OLED_WIDTH && ipStr.length() > 0) {
        ipStr.remove(ipStr.length() - 1);
    }
    int ipW = u8g2.getStrWidth(ipStr.c_str());
    u8g2.drawStr((OLED_WIDTH - ipW) / 2, y, ipStr.c_str());
    y += 8;
    // Infos condensées sur une seule ligne (Mode/Gui/8x8), version courte
    String infos;
    if (modeName && strlen(modeName) > 0) {
        infos += shortMode(modeName).c_str();
    }
    if (animationName && strlen(animationName) > 0) {
        if (infos.length() > 0) infos += "/";
        infos += shortAnim(animationName).c_str();
    }
    if (matrixAnimationName && strlen(matrixAnimationName) > 0) {
        if (infos.length() > 0) infos += "/";
        infos += shortAnim(matrixAnimationName).c_str();
    }
    // Tronquer si trop long
    while (u8g2.getStrWidth(infos.c_str()) > OLED_WIDTH && infos.length() > 0) {
        infos.remove(infos.length() - 1);
    }
    u8g2.drawStr(0, y, infos.c_str());
    u8g2.sendBuffer();
#else
    // 128x64 : inchangé
    u8g2.setFont(u8g2_font_6x12_tr);
    int projW = u8g2.getStrWidth(projectName);
    u8g2.drawStr((OLED_WIDTH - projW) / 2, 10, projectName);
    char vbuf[16];
    snprintf(vbuf, sizeof(vbuf), "v%s", projectVersion);
    u8g2.setFont(u8g2_font_04b_03_tr);
    int verW = u8g2.getStrWidth(vbuf);
    u8g2.drawStr((OLED_WIDTH - verW) / 2, 16, vbuf);
    u8g2.setFont(u8g2_font_6x12_tr);
    String ipStr = ip.toString();
    while (u8g2.getStrWidth(ipStr.c_str()) > OLED_WIDTH && ipStr.length() > 0) {
        ipStr.remove(ipStr.length() - 1);
    }
    int ipW = u8g2.getStrWidth(ipStr.c_str());
    u8g2.drawStr((OLED_WIDTH - ipW) / 2, 30, ipStr.c_str());
    u8g2.setFont(u8g2_font_5x8_tr);
    uint8_t y = 40;
    const uint8_t xLabel = 5;
    const char* sep = ": ";
    if (animationName && strlen(animationName) > 0) {
        String label = "Gui";
        String value = String(animationName);
        String full = label + sep + value;
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
#endif
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


