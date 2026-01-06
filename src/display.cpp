/**
 * @file display.cpp
 * @brief Implémentation du module de gestion de l'écran ST7789
 * @version 5.0.0
 * @date 2026-01-06
 */

#include "display.h"
#include "config.h"
#include "garland_control.h"

#ifdef HAS_ST7789
// --- Affichage selon le mode d'écran sélectionné ---
/**
 * @brief Affiche l'écran selon le mode d'affichage sélectionné
 * @param ssid Nom du réseau WiFi
 * @param ip Adresse IP
 * @param modeName Nom du mode courant
 * @param animationName Nom de l'animation courante
 */
void displayScreenByMode(const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName) {
    DisplayMode mode = getDisplayMode();
    switch (mode) {
        case DISPLAY_MODE_ANIMATED:
            digitalWrite(LCD_BLK, HIGH);
            displayMainScreen(ssid, ip, modeName, animationName, matrixAnimationName);
            break;
        case DISPLAY_MODE_STATIC: {
            digitalWrite(LCD_BLK, HIGH);

            const String versionStr = "v" + String(PROJECT_VERSION);
            const String ssidStr = (ssid != nullptr && strlen(ssid) > 0) ? String(ssid) : String("Offline");
            const String ipStr = ip.toString();
            const String mdnsStr = String(getDeviceName()) + ".local";

            display.setTextWrap(false);

            auto centerText = [&](const String& text, int16_t y, uint8_t size, uint16_t color) {
                int16_t x1, y1; uint16_t w, h;
                display.setTextSize(size);
                display.getTextBounds(text.c_str(), 0, 0, &x1, &y1, &w, &h);
                const int16_t cx = (ST7789_WIDTH - w) / 2;
                display.setCursor(cx, y);
                display.setTextColor(color);
                display.println(text);
            };

            auto drawSparkle = [&](int x, int y, uint16_t color) {
                display.drawPixel(x, y, color);
                display.drawFastHLine(x - 2, y, 5, color);
                display.drawFastVLine(x, y - 2, 5, color);
                display.drawLine(x - 2, y - 2, x + 2, y + 2, color);
                display.drawLine(x - 2, y + 2, x + 2, y - 2, color);
            };

            auto drawFestiveGarland = [&](int yBase) {
                int prevX = 12;
                int prevY = yBase;
                for (int i = 0; i <= 12; i++) {
                    const int x = 12 + i * 18;
                    const int y = yBase + (int)(sin(i * 0.7f) * 6);
                    display.drawLine(prevX, prevY, x, y, COLOR_GREEN);
                    const uint16_t bulbColor = (i % 3 == 0) ? COLOR_YELLOW : (i % 3 == 1 ? COLOR_MAGENTA : COLOR_CYAN);
                    display.fillCircle(x, y, 4, bulbColor);
                    display.drawCircle(x, y, 5, COLOR_WHITE);
                    prevX = x;
                    prevY = y;
                }
            };

            auto drawInfoRow = [&](int x, int y, const char* label, String value, uint16_t accentColor) {
                if (value.length() > 20) {
                    value = value.substring(0, 19) + "...";
                }
                display.setTextSize(1);
                display.setTextColor(accentColor);
                display.setCursor(x, y);
                display.print(label);
                display.setTextColor(COLOR_WHITE);
                display.setCursor(x + 74, y);
                display.println(value);
            };

            // Fond texturé
            const uint16_t deepNight = display.color565(5, 12, 24);
            const uint16_t stripe = display.color565(8, 28, 48);
            display.fillScreen(deepNight);
            for (int y = 0; y < ST7789_HEIGHT; y += 8) {
                display.drawFastHLine(0, y, ST7789_WIDTH, stripe);
            }

            // Cadre principal
            display.drawRoundRect(4, 4, ST7789_WIDTH - 8, ST7789_HEIGHT - 8, 12, COLOR_CYAN);
            display.drawRoundRect(9, 9, ST7789_WIDTH - 18, ST7789_HEIGHT - 18, 10, COLOR_PURPLE);
            drawSparkle(18, 18, COLOR_YELLOW);
            drawSparkle(ST7789_WIDTH - 18, 18, COLOR_ORANGE);
            drawSparkle(18, ST7789_HEIGHT - 18, COLOR_CYAN);
            drawSparkle(ST7789_WIDTH - 18, ST7789_HEIGHT - 18, COLOR_GREEN);

            // En-tête festif
            const int headerY = 16;
            display.fillRoundRect(14, headerY, ST7789_WIDTH - 28, 70, 12, display.color565(22, 62, 118));
            display.drawRoundRect(14, headerY, ST7789_WIDTH - 28, 70, 12, COLOR_YELLOW);
            centerText(PROJECT_NAME, headerY + 12, 2, COLOR_WHITE);
            centerText(versionStr, headerY + 40, 1, COLOR_CYAN);

            drawFestiveGarland(headerY + 82);

            // Carte info réseau
            const int panelX = 18;
            const int panelY = headerY + 96;
            const int panelW = ST7789_WIDTH - 36;
            const int panelH = 182;
            display.fillRoundRect(panelX, panelY, panelW, panelH, 14, display.color565(10, 22, 42));
            display.drawRoundRect(panelX, panelY, panelW, panelH, 14, COLOR_GREEN);
            display.drawRoundRect(panelX + 3, panelY + 3, panelW - 6, panelH - 6, 12, COLOR_ORANGE);
            centerText("Festive Network Card", panelY + 12, 1, COLOR_YELLOW);

            int rowY = panelY + 32;
            drawInfoRow(panelX + 16, rowY, "SSID", ssidStr, COLOR_YELLOW); rowY += 32;
            drawInfoRow(panelX + 16, rowY, "IP", ipStr, COLOR_CYAN); rowY += 32;
            drawInfoRow(panelX + 16, rowY, "mDNS", mdnsStr, COLOR_ORANGE);

            // Bandeau décoratif bas
            drawFestiveGarland(panelY + panelH - 18);
            centerText("Ready to sparkle!", panelY + panelH - 36, 1, COLOR_GREEN);

            display.setTextWrap(true);
            break;
        }
        case DISPLAY_MODE_OFF:
            // Éteint : efface d'abord puis coupe le rétroéclairage
            display.fillScreen(COLOR_BLACK);
            digitalWrite(LCD_BLK, LOW); // coupe le rétroéclairage
            break;
        default:
            digitalWrite(LCD_BLK, HIGH);
            displayMainScreen(ssid, ip, modeName, animationName, matrixAnimationName);
            break;
    }
}

// =============================================================================
// INSTANCIATION DE L'OBJET DISPLAY
// =============================================================================
Adafruit_ST7789 display = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);

// =============================================================================
// VARIABLES INTERNES
// =============================================================================
static uint8_t animFrame = 0;  // Frame d'animation pour les effets visuels

struct AnimationViewport {
    int x;
    int y;
    int w;
    int h;
    bool initialized;
};

static AnimationViewport animViewport = {3, 74, ST7789_WIDTH - 6, ST7789_HEIGHT - 78, false};

static void setAnimationViewport(int x, int y, int w, int h) {
    animViewport.x = x;
    animViewport.y = y;
    animViewport.w = w;
    animViewport.h = h;
    animViewport.initialized = true;
}

// =============================================================================
// FONCTIONS PUBLIQUES
// =============================================================================

void setupDisplay() {
    LOG_PRINTLN("--- Initialisation écran ST7789 ---");

    // Configuration du rétroéclairage (IMPORTANT : doit être HIGH pour voir l'image)
    pinMode(LCD_BLK, OUTPUT);
    digitalWrite(LCD_BLK, HIGH);

    // Initialisation de l'écran ST7789
    display.init(ST7789_WIDTH, ST7789_HEIGHT);
    display.setRotation(ST7789_ROTATION);
    display.fillScreen(COLOR_BLACK);

    LOG_PRINTLN("✓ ST7789 initialisé");
}

void displayBootScreen(const char* projectName, const char* projectVersion, int wifiProgress) {
    display.fillScreen(COLOR_BLACK);

    // --- EN-TÊTE : Nom du projet ---
    display.setTextSize(2);
    display.setTextColor(COLOR_CYAN);

    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(projectName, 0, 0, &x1, &y1, &w, &h);
    int centerX = (ST7789_WIDTH - w) / 2;
    display.setCursor(centerX, 20);
    display.println(projectName);

    // --- VERSION ---
    display.setTextSize(1);
    display.setTextColor(COLOR_WHITE);
    String versionStr = "v" + String(projectVersion);
    display.getTextBounds(versionStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (ST7789_WIDTH - w) / 2;
    display.setCursor(centerX, 45);
    display.println(versionStr);

    // --- LIGNE DE SÉPARATION ---
    display.drawLine(10, 65, ST7789_WIDTH - 10, 65, COLOR_CYAN);

    // --- PROGRESSION WIFI ---
    if (wifiProgress >= 0 && wifiProgress <= 100) {
        display.setTextSize(1);
        display.setTextColor(COLOR_YELLOW);
        display.setCursor(10, 80);
        display.println("Connexion WiFi...");

        // Barre de progression
        int barWidth = ST7789_WIDTH - 20;
        int barHeight = 20;
        int barX = 10;
        int barY = 100;

        // Contour de la barre
        display.drawRect(barX, barY, barWidth, barHeight, COLOR_WHITE);

        // Remplissage de la progression
        int fillWidth = (barWidth - 4) * wifiProgress / 100;
        if (fillWidth > 0) {
            display.fillRect(barX + 2, barY + 2, fillWidth, barHeight - 4, COLOR_GREEN);
        }

        // Pourcentage
        display.setTextColor(COLOR_WHITE);
        String percentStr = String(wifiProgress) + "%";
        display.getTextBounds(percentStr.c_str(), 0, 0, &x1, &y1, &w, &h);
        centerX = (ST7789_WIDTH - w) / 2;
        display.setCursor(centerX, barY + barHeight + 8);
        display.println(percentStr);
    }
}

void displayMainScreen(const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName) {
    const uint16_t deepNight = display.color565(5, 12, 24);
    const uint16_t stripe = display.color565(8, 28, 48);
    const uint16_t panelDark = display.color565(10, 22, 42);
    const uint16_t panelBright = display.color565(22, 62, 118);

    display.setTextWrap(false);

    // Fond texturé façon écran statique
    display.fillScreen(deepNight);
    for (int y = 0; y < ST7789_HEIGHT; y += 8) {
        display.drawFastHLine(0, y, ST7789_WIDTH, stripe);
    }

    // Cadres principaux
    display.drawRoundRect(4, 4, ST7789_WIDTH - 8, ST7789_HEIGHT - 8, 12, COLOR_CYAN);
    display.drawRoundRect(9, 9, ST7789_WIDTH - 18, ST7789_HEIGHT - 18, 10, COLOR_PURPLE);

    auto drawSparkle = [&](int x, int y, uint16_t color) {
        display.drawPixel(x, y, color);
        display.drawFastHLine(x - 2, y, 5, color);
        display.drawFastVLine(x, y - 2, 5, color);
        display.drawLine(x - 2, y - 2, x + 2, y + 2, color);
        display.drawLine(x - 2, y + 2, x + 2, y - 2, color);
    };

    auto drawFestiveGarland = [&](int yBase) {
        int prevX = 12;
        int prevY = yBase;
        for (int i = 0; i <= 12; i++) {
            const int x = 12 + i * 18;
            const int y = yBase + (int)(sin(i * 0.7f) * 6);
            display.drawLine(prevX, prevY, x, y, COLOR_GREEN);
            const uint16_t bulbColor = (i % 3 == 0) ? COLOR_YELLOW : (i % 3 == 1 ? COLOR_MAGENTA : COLOR_CYAN);
            display.fillCircle(x, y, 3, bulbColor);
            display.drawCircle(x, y, 4, COLOR_WHITE);
            prevX = x;
            prevY = y;
        }
    };

    auto centerText = [&](const String& text, int16_t y, uint8_t size, uint16_t color) {
        int16_t x1, y1; uint16_t w, h;
        display.setTextSize(size);
        display.getTextBounds(text.c_str(), 0, 0, &x1, &y1, &w, &h);
        const int16_t cx = (ST7789_WIDTH - w) / 2;
        display.setCursor(cx, y);
        display.setTextColor(color);
        display.println(text);
    };

    // En-tête festif
    const int headerY = 14;
    display.fillRoundRect(14, headerY, ST7789_WIDTH - 28, 58, 12, panelBright);
    display.drawRoundRect(14, headerY, ST7789_WIDTH - 28, 58, 12, COLOR_YELLOW);
    centerText(PROJECT_NAME, headerY + 6, 2, COLOR_WHITE);
    centerText("v" + String(PROJECT_VERSION), headerY + 34, 1, COLOR_CYAN);

    // Décors
    drawSparkle(18, 18, COLOR_YELLOW);
    drawSparkle(ST7789_WIDTH - 18, 18, COLOR_ORANGE);
    drawSparkle(18, ST7789_HEIGHT - 18, COLOR_CYAN);
    drawSparkle(ST7789_WIDTH - 18, ST7789_HEIGHT - 18, COLOR_GREEN);
    drawFestiveGarland(headerY + 64);

    // Cartes info et mini-animation
    const int margin = 8;
    const int infoX = margin;
    const int infoY = headerY + 74;
    const int infoW = 128;
    const int infoH = 170;

    const int animPanelX = infoX + infoW + 8;
    const int animPanelW = ST7789_WIDTH - animPanelX - margin;
    const int animPanelY = infoY;
    const int animPanelH = 128;

    // Panneau info (mode + réseau)
    display.fillRoundRect(infoX, infoY, infoW, infoH, 12, panelDark);
    display.drawRoundRect(infoX, infoY, infoW, infoH, 12, COLOR_GREEN);
    display.drawRoundRect(infoX + 3, infoY + 3, infoW - 6, infoH - 6, 10, COLOR_ORANGE);

    display.setTextSize(1);
    display.setTextColor(COLOR_YELLOW);
    display.setCursor(infoX + 10, infoY + 10);
    display.println("Mode");
    display.setTextColor(COLOR_WHITE);
    display.setCursor(infoX + 10, infoY + 22);
    display.println(modeName);

    display.setTextColor(COLOR_ORANGE);
    display.setCursor(infoX + 10, infoY + 38);
    display.println("Anim guirlande");
    display.setTextColor(COLOR_WHITE);
    display.setCursor(infoX + 10, infoY + 50);
    display.println(animationName);

    display.setTextColor(COLOR_RED);
    display.setCursor(infoX + 10, infoY + 66);
    display.println("Anim matrice");
    display.setTextColor(COLOR_WHITE);
    display.setCursor(infoX + 10, infoY + 78);
    display.println(matrixAnimationName != nullptr ? matrixAnimationName : "--");

    display.drawFastHLine(infoX + 8, infoY + 94, infoW - 16, COLOR_CYAN);

    display.setTextColor(COLOR_YELLOW);
    display.setCursor(infoX + 10, infoY + 104);
    display.print("SSID: ");
    display.setTextColor(COLOR_WHITE);
    display.println(ssid);

    display.setTextColor(COLOR_GREEN);
    display.setCursor(infoX + 10, infoY + 120);
    display.print("IP:   ");
    display.setTextColor(COLOR_WHITE);
    display.println(ip.toString().c_str());

    // Panneau mini-animation (réduit)
    display.fillRoundRect(animPanelX, animPanelY, animPanelW, animPanelH, 12, panelDark);
    display.drawRoundRect(animPanelX, animPanelY, animPanelW, animPanelH, 12, COLOR_CYAN);
    display.drawRoundRect(animPanelX + 2, animPanelY + 2, animPanelW - 4, animPanelH - 4, 10, COLOR_MAGENTA);

    display.setTextColor(COLOR_YELLOW);
    display.setCursor(animPanelX + 8, animPanelY + 6);
    display.println("Mini show");

    // Zone d'animation fortement réduite
    const int animAreaX = animPanelX + 6;
    const int animAreaY = animPanelY + 20;
    const int animAreaW = animPanelW - 12;
    const int animAreaH = animPanelH - 30; // réduit pour laisser place aux décors

    display.drawRoundRect(animAreaX, animAreaY, animAreaW, animAreaH, 8, COLOR_WHITE);
    display.drawRoundRect(animAreaX + 2, animAreaY + 2, animAreaW - 4, animAreaH - 4, 6, COLOR_CYAN);

    // Décorations autour de la zone
    drawSparkle(animAreaX + 4, animAreaY + 4, COLOR_YELLOW);
    drawSparkle(animAreaX + animAreaW - 6, animAreaY + 4, COLOR_ORANGE);
    drawSparkle(animAreaX + 4, animAreaY + animAreaH - 6, COLOR_CYAN);
    drawSparkle(animAreaX + animAreaW - 6, animAreaY + animAreaH - 6, COLOR_GREEN);

    // Mémoriser la nouvelle fenêtre d'animation pour les rafraîchissements
    setAnimationViewport(animAreaX + 2, animAreaY + 2, animAreaW - 4, animAreaH - 4);

    // Affichage visuel de l'animation dans la zone réduite
    updateAnimationVisual(animationName, matrixAnimationName != nullptr);

    display.setTextWrap(true);
}

void updateAnimationVisual(const char* animationName, bool hasMatrix) {
    // Utiliser la fenêtre mémorisée (ou fallback si non initialisée)
    int animX = animViewport.initialized ? animViewport.x : 3;
    int animY = animViewport.initialized ? animViewport.y : (hasMatrix ? 85 : 74);
    int animWidth = animViewport.initialized ? animViewport.w : (ST7789_WIDTH - 6);
    int animHeight = animViewport.initialized ? animViewport.h : (hasMatrix ? ST7789_HEIGHT - 90 : ST7789_HEIGHT - 78);

    // Effacer la zone d'animation réduite tout en préservant les cadres
    display.fillRect(animX, animY, animWidth, animHeight, COLOR_BLACK);

    // Animation "Éteint" : afficher seulement le texte
    if (strcmp(animationName, "Eteint") == 0) {
        display.setTextSize(2);
        display.setTextColor(COLOR_RED);
        int16_t x1, y1;
        uint16_t w, h;
        display.getTextBounds("OFF", 0, 0, &x1, &y1, &w, &h);
        int centerX = animX + (animWidth - w) / 2;
        int centerY = animY + (animHeight - h) / 2;
        display.setCursor(centerX, centerY);
        display.println("OFF");
        return;
    }


// --- Affichage selon le mode d'écran sélectionné ---
    // Incrémenter le frame à chaque appel
    animFrame = (animFrame + 1) % 256;

    int centerX = animX + animWidth / 2;
    int centerY = animY + animHeight / 2;

    // Animations visuelles selon le type
    if (strcmp(animationName, "Fade Alterne") == 0) {
        // Deux barres horizontales qui s'alternent (amélioration visuelle)
        int barHeight = animHeight / 3;
        int barY1 = animY + barHeight / 2;
        int barY2 = animY + animHeight - barHeight - barHeight / 2;

        int brightness1 = (animFrame < 128) ? animFrame * 2 : (255 - animFrame) * 2;
        int brightness2 = 255 - brightness1;

        // Couleurs plus vives (jaune/bleu au lieu de grayscale)
        uint16_t color1 = display.color565(brightness1, brightness1, 0);  // Jaune
        uint16_t color2 = display.color565(0, 0, brightness2);  // Bleu

        display.fillRoundRect(animX + 5, barY1, animWidth - 10, barHeight, 4, color1);
        display.fillRoundRect(animX + 5, barY2, animWidth - 10, barHeight, 4, color2);
    }
    else if (strcmp(animationName, "Clignotement") == 0) {
        // Rectangle qui clignote avec coins arrondis
        if (animFrame < 128) {
            display.fillRoundRect(animX + 5, animY + 5, animWidth - 10, animHeight - 10, 8, COLOR_YELLOW);
        }
    }
    else if (strcmp(animationName, "Pulsation") == 0) {
        // Cercle qui grossit et rétrécit (plus grand rayon)
        int maxRadius = min(animWidth, animHeight) / 2 - 10;
        int radius = 5 + ((animFrame * maxRadius) / 128) % maxRadius;
        display.fillCircle(centerX, centerY, radius, COLOR_PURPLE);
    }
    else if (strcmp(animationName, "Respiration") == 0) {
        // Rectangle avec fade in/out (couleur cyan plus douce)
        int brightness = (animFrame < 128) ? animFrame * 2 : (255 - animFrame) * 2;
        uint16_t color = display.color565(0, brightness, brightness);
        display.fillRoundRect(animX + 5, animY + 5, animWidth - 10, animHeight - 10, 8, color);
    }
    else if (strcmp(animationName, "Strobe") == 0) {
        // Flash stroboscopique
        if (animFrame % 20 < 3) {
            display.fillRoundRect(animX + 5, animY + 5, animWidth - 10, animHeight - 10, 8, COLOR_WHITE);
        }
    }
    else if (strcmp(animationName, "Battement Coeur") == 0) {
        // Double pulsation (plus grande et plus visible)
        int beat = animFrame % 60;
        int radius = 0;

        if (beat < 10) {
            radius = (beat * 3);  // Premier battement : montée rapide
        } else if (beat < 15) {
            radius = ((15 - beat) * 3);  // Premier battement : descente
        } else if (beat >= 20 && beat < 30) {
            radius = ((beat - 20) * 3);  // Deuxième battement : montée
        } else if (beat >= 30 && beat < 35) {
            radius = ((35 - beat) * 3);  // Deuxième battement : descente
        }

        if (radius > 0) {
            display.fillCircle(centerX, centerY, radius, COLOR_RED);
        }
    }
    else if (strcmp(animationName, "Vague") == 0) {
        // Onde sinusoïdale fluide (plus grande amplitude)
        for (int x = 0; x < animWidth - 4; x += 2) {
            int amplitude = animHeight / 3;
            int y = centerY + (int)(amplitude * sin((x + animFrame * 3) * 0.08));
            if (y >= animY + 2 && y < animY + animHeight - 2) {
                display.fillCircle(animX + 2 + x, y, 3, COLOR_CYAN);
            }
        }
    }
    else if (strcmp(animationName, "Scintillement") == 0) {
        // Points aléatoires qui scintillent
        for (int i = 0; i < 15; i++) {
            int x = animX + 5 + (animFrame * 7 + i * 13) % (animWidth - 10);
            int y = animY + 5 + (animFrame * 11 + i * 17) % (animHeight - 10);
            if ((animFrame + i) % 3 == 0) {
                display.fillCircle(x, y, 2, COLOR_YELLOW);
            }
        }
    }
    else if (strcmp(animationName, "Meteore") == 0) {
        // Traînée qui se déplace (amélioration visuelle)
        int tailLength = 60;
        int pos = (animFrame * 3) % (animWidth + tailLength);

        for (int i = 0; i < tailLength; i++) {
            int x = animX + pos - i;
            if (x >= animX + 2 && x < animX + animWidth - 2) {
                int brightness = 255 - (i * 255 / tailLength);
                uint16_t color = display.color565(brightness, brightness / 2, 0);  // Orange/jaune
                display.drawFastVLine(x, animY + 5, animHeight - 10, color);
            }
        }
    }
    else if (strcmp(animationName, "Auto") == 0) {
        // Afficher "AUTO" centré avec cercles tournants
        display.setTextSize(3);
        display.setTextColor(COLOR_GREEN);
        int16_t x1, y1;
        uint16_t w, h;
        display.getTextBounds("AUTO", 0, 0, &x1, &y1, &w, &h);
        int textX = centerX - w / 2;
        int textY = centerY - h / 2;
        display.setCursor(textX, textY);
        display.println("AUTO");

        // Deux cercles tournants en orbite
        float angle1 = animFrame * 0.08;
        float angle2 = angle1 + PI;
        int orbitRadius = 40;

        int circleX1 = centerX + (int)(orbitRadius * cos(angle1));
        int circleY1 = centerY + (int)(orbitRadius * sin(angle1));
        int circleX2 = centerX + (int)(orbitRadius * cos(angle2));
        int circleY2 = centerY + (int)(orbitRadius * sin(angle2));

        display.fillCircle(circleX1, circleY1, 4, COLOR_YELLOW);
        display.fillCircle(circleX2, circleY2, 4, COLOR_CYAN);
    }
    else {
        // Animation par défaut : barre horizontale avec coins arrondis
        display.fillRoundRect(animX + 10, centerY - 10, animWidth - 20, 20, 5, COLOR_WHITE);
    }
}

#else

// =============================================================================
// STUBS VIDES SI ST7789 N'EST PAS ACTIVÉ
// =============================================================================
void setupDisplay() {
    LOG_PRINTLN("⚠ Écran ST7789 désactivé (HAS_ST7789 non défini)");
}

void displayBootScreen(const char* projectName, const char* projectVersion, int wifiProgress) {
    // Rien
}

void displayMainScreen(const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName) {
    // Rien
}

void updateAnimationVisual(const char* animationName) {
    // Rien
}


#endif

