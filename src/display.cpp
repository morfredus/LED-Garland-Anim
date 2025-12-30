/**
 * @file display.cpp
 * @brief Implémentation du module de gestion de l'écran LCD ST7789
 * @version 0.9.1
 * @date 2025-12-30
 * Changement #3 (2025-12-30) : Suppression du support TFT/ILI9341, LCD ST7789 unique, OLED secours, harmonisation des fonctions
 */

#include <Arduino.h>
#include "display.h"
#include "garland_control.h"

#include <Wire.h>
// Plus de support OLED, uniquement LCD ST7789
// Plus de code OLED : tout le support a été supprimé.


// Déclaration de l'instance globale LCD (doit correspondre à l'extern de display.h)
Adafruit_ST7789 display_lcd = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);

// =============================================================================
// FONCTIONS PUBLIQUES - INTERFACE UNIFIÉE
// =============================================================================

void setupDisplays() {
    LOG_PRINTLN("--- Initialisation des écrans ---");
    setupLCD();
}


// =============================================================================
// FONCTIONS INTERNES - LCD ST7789 (remplace TFT)
// =============================================================================


// Changement #3 (2025-12-30) : Suppression du support TFT, LCD ST7789 unique
bool setupLCD() {
    pinMode(LCD_BLK, OUTPUT);
    digitalWrite(LCD_BLK, HIGH); // Allume le rétroéclairage
    display_lcd.init(LCD_WIDTH, LCD_HEIGHT);
    display_lcd.setRotation(LCD_ROTATION); // 1 = portrait 135x240 (USB à gauche)
    display_lcd.fillScreen(COLOR_BLACK);
    return true;
}

void displayLCDStartup(const char* projectName, const char* projectVersion) {
    display_lcd.fillScreen(COLOR_BLACK);
    int16_t x1, y1;
    uint16_t w, h;

    // Nom du projet (centré, taille 2)
    display_lcd.setTextSize(2);
    display_lcd.setTextColor(COLOR_CYAN);
    display_lcd.getTextBounds(projectName, 0, 0, &x1, &y1, &w, &h);
    int centerX = (LCD_WIDTH - w) / 2;
    display_lcd.setCursor(centerX, 12 - y1);
    display_lcd.println(projectName);

    // Version (centré, taille 1)
    display_lcd.setTextSize(1);
    display_lcd.setTextColor(COLOR_WHITE);
    String versionStr = "v" + String(projectVersion);
    display_lcd.getTextBounds(versionStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (LCD_WIDTH - w) / 2;
    display_lcd.setCursor(centerX, 32);
    display_lcd.println(versionStr);

    // Message de connexion WiFi (centré)
    display_lcd.setTextSize(1);
    display_lcd.setTextColor(COLOR_YELLOW);
    const char* wifiMsg = "Connexion WiFi...";
    display_lcd.getTextBounds(wifiMsg, 0, 0, &x1, &y1, &w, &h);
    centerX = (LCD_WIDTH - w) / 2;
    display_lcd.setCursor(centerX, 54);
    display_lcd.println(wifiMsg);
}

void displayLCDConnected(const char* ssid, IPAddress ip) {
    display_lcd.fillScreen(COLOR_BLACK);
    int16_t x1, y1;
    uint16_t w, h;

    // Titre projet (centré, taille 2, verticalement mieux centré)
    display_lcd.setTextSize(2);
    display_lcd.setTextColor(COLOR_CYAN);
    display_lcd.getTextBounds(PROJECT_NAME, 0, 0, &x1, &y1, &w, &h);
    int centerX = (LCD_WIDTH - w) / 2 - x1;
    int centerY = 4 - y1;
    display_lcd.setCursor(centerX, centerY);
    display_lcd.println(PROJECT_NAME);

    // Version (centré, taille 1)
    display_lcd.setTextSize(1);
    display_lcd.setTextColor(COLOR_WHITE);
    String versionStr = "v" + String(PROJECT_VERSION);
    display_lcd.getTextBounds(versionStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (LCD_WIDTH - w) / 2 - x1;
    display_lcd.setCursor(centerX, centerY + h + 2);
    display_lcd.println(versionStr);


    // SSID + IP sur la même ligne (centré, taille 1)
    String ssidIpStr = String(ssid) + "  |  " + ip.toString();
    display_lcd.setTextColor(COLOR_YELLOW);
    display_lcd.getTextBounds(ssidIpStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (LCD_WIDTH - w) / 2 - x1;
    display_lcd.setCursor(centerX, centerY + h + 18);
    display_lcd.println(ssidIpStr);

    // Remonter les infos : tout de suite sous SSID+IP
    int yInfo = centerY + h + 32;
    // Mode (centré, sauf si AUTO)
    int mode = (int)getGuirlandeMode();
    String modeStr = "Mode: " + String(getGuirlandeModeName());
    if (mode != 2) { // 2 = MODE_AUTO
        display_lcd.setTextColor(COLOR_YELLOW);
        display_lcd.setTextSize(1);
        display_lcd.getTextBounds(modeStr.c_str(), 0, 0, &x1, &y1, &w, &h);
        centerX = (LCD_WIDTH - w) / 2;
        display_lcd.setCursor(centerX, yInfo);
        display_lcd.println(modeStr);
        yInfo += 14;
    } else {
        // En mode AUTO, afficher "Mode: Auto" centré
        display_lcd.setTextColor(COLOR_YELLOW);
        display_lcd.setTextSize(1);
        display_lcd.getTextBounds("Mode: Auto", 0, 0, &x1, &y1, &w, &h);
        centerX = (LCD_WIDTH - w) / 2;
        display_lcd.setCursor(centerX, yInfo);
        display_lcd.println("Mode: Auto");
        yInfo += 14;
    }

    // Animation (centré, sauf si mode AUTO)
    int anim = (int)getGuirlandeAnimation();
    if (mode != 2) {
        const char* animLabel = "Anim: ";
        String animStr = String(animLabel) + String(getGuirlandeAnimationName());
        display_lcd.setTextColor(COLOR_GREEN);
        display_lcd.getTextBounds(animStr.c_str(), 0, 0, &x1, &y1, &w, &h);
        centerX = (LCD_WIDTH - w) / 2;
        display_lcd.setCursor(centerX, yInfo);
        display_lcd.println(animStr);
        yInfo += 14;
    } else {
        // En mode AUTO, ne rien afficher pour l'animation
        yInfo += 0;
    }

    // Séparateur (remonté)
    display_lcd.drawLine(6, yInfo, LCD_WIDTH-6, yInfo, COLOR_CYAN);
    yInfo += 8;

    // Zone pour le graphe d'animation (centrée en bas, rectangle bien visible)
    int graphW = LCD_WIDTH - 20;
    int graphH = 38;
    int graphX = (LCD_WIDTH - graphW) / 2;
    int graphY = LCD_HEIGHT - graphH - 8;
    display_lcd.drawRect(graphX, graphY, graphW, graphH, COLOR_WHITE);
    drawAnimationGraph(graphX+2, graphY+2, graphW-4, graphH-4);
}

// Dessine un graphe d'animation selon l'animation courante
void drawAnimationGraph(int x, int y, int w, int h) {
    // En mode AUTO, afficher le graphe de l'animation active réelle
    int anim = getGuirlandeAnimationInt();
    int mode = getGuirlandeModeInt();
    // En mode AUTO, afficher le graphe de l'animation active réelle
    if (mode == 2 /* G_MODE_AUTO */) {
        anim = getActiveGuirlandeAnimation();
    }
    display_lcd.fillRect(x, y, w, h, COLOR_BLACK);
    // Correction : ne pas dessiner sur la ligne du bas du rectangle (h-2 -> h-3)
    switch (anim) {
        case 0: // ANIM_OFF
            // Rien
            break;
        case 1: // ANIM_FADE_ALTERNATE
            // Sinusoïde alternée
            for (int i = 0; i < w; ++i) {
                float phase = (float)i / w * 2 * PI;
                int v = (int)((sin(phase) * 0.5 + 0.5) * (h-4));
                display_lcd.drawPixel(x+i, y+h-3-v, COLOR_CYAN);
            }
            break;
        case 2: // ANIM_BLINK_ALTERNATE
            // Carré alterné
            for (int i = 0; i < w; ++i) {
                int v = (i < w/2) ? h-4 : 0;
                display_lcd.drawLine(x+i, y+h-3, x+i, y+h-3-v, COLOR_YELLOW);
            }
            break;
        case 3: // ANIM_PULSE
            // Triangle
            for (int i = 0; i < w; ++i) {
                float phase = (float)i / w;
                int v = (phase < 0.5) ? (int)(phase*2*(h-4)) : (int)((1.0-(phase-0.5)*2)*(h-4));
                display_lcd.drawPixel(x+i, y+h-3-v, COLOR_GREEN);
            }
            break;
        case 4: // ANIM_BREATHING
            // Sinusoïde douce
            for (int i = 0; i < w; ++i) {
                float phase = (float)i / w * 2 * PI;
                int v = (int)(((1.0 - cos(phase)) / 2.0) * (h-4));
                display_lcd.drawPixel(x+i, y+h-3-v, COLOR_BLUE);
            }
            break;
        case 5: // ANIM_STROBE
            // Impulsions courtes
            for (int i = 0; i < w; ++i) {
                int v = (i%20 < 4) ? h-4 : 0;
                display_lcd.drawLine(x+i, y+h-3, x+i, y+h-3-v, COLOR_WHITE);
            }
            break;
        case 6: // ANIM_HEARTBEAT
            // Double impulsion
            for (int i = 0; i < w; ++i) {
                float t = (float)i / w;
                int v = 0;
                if (t < 0.13) v = (int)(t/0.13*(h-4));
                else if (t < 0.26) v = (int)((1.0-(t-0.13)/0.13)*(h-4));
                else if (t < 0.33) v = 0;
                else if (t < 0.46) v = (int)((t-0.33)/0.13*(h-4));
                else if (t < 0.59) v = (int)((1.0-(t-0.46)/0.13)*(h-4));
                display_lcd.drawPixel(x+i, y+h-3-v, COLOR_RED);
            }
            break;
        case 7: // ANIM_WAVE
            // Sinusoïde rapide
            for (int i = 0; i < w; ++i) {
                float phase = (float)i / w * 4 * PI;
                int v = (int)((sin(phase) * 0.5 + 0.5) * (h-4));
                display_lcd.drawPixel(x+i, y+h-3-v, COLOR_CYAN);
            }
            break;
        case 8: // ANIM_SPARKLE
            // Points aléatoires
            for (int i = 0; i < w; i += 4) {
                int v = random(0, h-4);
                display_lcd.drawPixel(x+i, y+h-3-v, COLOR_YELLOW);
            }
            break;
        case 9: // ANIM_METEOR
            // Traînée
            for (int i = 0; i < w; ++i) {
                float t = (float)i / w;
                int v = (t < 0.5) ? (int)(t*2*(h-4)) : (int)((1.0-(t-0.5)*2)*(h-4));
                display_lcd.drawPixel(x+i, y+h-3-v, COLOR_WHITE);
            }
            break;
        case 10: // ANIM_AUTO
            // En mode AUTO, on affiche le graphe de l'animation réelle (déjà géré plus haut)
            break;
        default:
            break;
    }
}

void displayLCDProgress(int progress) {
    display_lcd.fillRect(0, 40, LCD_WIDTH, 30, COLOR_BLACK);
    display_lcd.setTextSize(2);
    display_lcd.setTextColor(COLOR_YELLOW);
    int16_t x1, y1;
    uint16_t w, h;
    display_lcd.getTextBounds("Connexion WiFi...", 0, 0, &x1, &y1, &w, &h);
    int centerX = (LCD_WIDTH - w) / 2;
    display_lcd.setCursor(centerX, 50);
    display_lcd.println("Connexion WiFi...");
    int barWidth = LCD_WIDTH - 40;
    int barHeight = 30;
    int barX = 20;
    int barY = 160;
    display_lcd.fillRect(barX - 2, barY - 2, barWidth + 4, barHeight + 20, COLOR_BLACK);
    display_lcd.drawRect(barX, barY, barWidth, barHeight, COLOR_WHITE);
    int fillWidth = (barWidth - 4) * progress / 100;
    if (fillWidth > 0) {
        display_lcd.fillRect(barX + 2, barY + 2, fillWidth, barHeight - 4, COLOR_GREEN);
    }
    display_lcd.setTextSize(2);
    display_lcd.setTextColor(COLOR_WHITE);
    String percentStr = String(progress) + "%";
    display_lcd.getTextBounds(percentStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (LCD_WIDTH - w) / 2;
    display_lcd.setCursor(centerX, barY + barHeight + 5);
    display_lcd.println(percentStr);
}


void displayLCDFailed() {
    display_lcd.fillScreen(COLOR_BLACK);
    display_lcd.setTextSize(3);
    display_lcd.setTextColor(COLOR_RED);
    int16_t x1, y1;
    uint16_t w, h;
    display_lcd.getTextBounds("ERREUR", 0, 0, &x1, &y1, &w, &h);
    int centerX = (LCD_WIDTH - w) / 2;
    display_lcd.setCursor(centerX, 80);
    display_lcd.println("ERREUR");
    display_lcd.setTextSize(2);
    display_lcd.setTextColor(COLOR_WHITE);
    display_lcd.getTextBounds("WiFi Echec", 0, 0, &x1, &y1, &w, &h);
    centerX = (LCD_WIDTH - w) / 2;
    display_lcd.setCursor(centerX, 120);
    display_lcd.println("WiFi Echec");
}


