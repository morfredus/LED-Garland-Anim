/**
 * @file display.cpp
 * @brief Implémentation du module de gestion de l'écran ST7789
 * @version 0.9.1
 * @date 2025-12-30
 */

#include "display.h"

#ifdef HAS_ST7789

// =============================================================================
// INSTANCIATION DE L'OBJET DISPLAY
// =============================================================================
Adafruit_ST7789 display = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);

// =============================================================================
// VARIABLES INTERNES
// =============================================================================
static uint8_t animFrame = 0;  // Frame d'animation pour les effets visuels

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

void displayMainScreen(const char* ssid, IPAddress ip, const char* modeName, const char* animationName) {
    display.fillScreen(COLOR_BLACK);

    // --- EN-TÊTE : Nom + Version ---
    display.setTextSize(1);
    display.setTextColor(COLOR_CYAN);
    display.setCursor(5, 5);
    display.print(PROJECT_NAME);
    display.print(" v");
    display.println(PROJECT_VERSION);

    // --- LIGNE DE SÉPARATION ---
    display.drawLine(0, 18, ST7789_WIDTH, 18, COLOR_CYAN);

    // --- SSID + IP ---
    display.setTextSize(1);
    display.setTextColor(COLOR_YELLOW);
    display.setCursor(5, 25);
    display.print("SSID: ");
    display.setTextColor(COLOR_WHITE);
    display.println(ssid);

    display.setTextColor(COLOR_YELLOW);
    display.setCursor(5, 38);
    display.print("IP: ");
    display.setTextColor(COLOR_WHITE);
    display.println(ip);

    // --- LIGNE DE SÉPARATION ---
    display.drawLine(0, 52, ST7789_WIDTH, 52, COLOR_CYAN);

    // --- MODE ---
    display.setTextSize(1);
    display.setTextColor(COLOR_MAGENTA);
    display.setCursor(5, 58);
    display.print("Mode: ");
    display.setTextColor(COLOR_WHITE);
    display.println(modeName);

    // --- ANIMATION ---
    display.setTextColor(COLOR_ORANGE);
    display.setCursor(5, 71);
    display.print("Anim: ");
    display.setTextColor(COLOR_WHITE);
    display.println(animationName);

    // --- LIGNE DE SÉPARATION ---
    display.drawLine(0, 85, ST7789_WIDTH, 85, COLOR_CYAN);

    // --- ZONE GRAPHIQUE D'ANIMATION ---
    // Rectangle de la zone d'animation
    display.drawRect(5, 90, ST7789_WIDTH - 10, ST7789_HEIGHT - 95, COLOR_WHITE);

    // Affichage visuel de l'animation
    updateAnimationVisual(animationName);
}

void updateAnimationVisual(const char* animationName) {
    // Zone d'animation : X=5, Y=90, Width=ST7789_WIDTH-10, Height=ST7789_HEIGHT-95
    int animX = 5;
    int animY = 90;
    int animWidth = ST7789_WIDTH - 10;
    int animHeight = ST7789_HEIGHT - 95;

    // Effacer la zone d'animation (garder le rectangle)
    display.fillRect(animX + 1, animY + 1, animWidth - 2, animHeight - 2, COLOR_BLACK);

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

    // Incrémenter le frame à chaque appel
    animFrame = (animFrame + 1) % 256;

    int centerX = animX + animWidth / 2;
    int centerY = animY + animHeight / 2;

    // Animations visuelles selon le type
    if (strcmp(animationName, "Fade Alterne") == 0) {
        // Deux barres qui s'alternent
        int barHeight = animHeight / 3;
        int barY1 = animY + barHeight / 2;
        int barY2 = animY + animHeight - barHeight - barHeight / 2;

        int brightness1 = (animFrame < 128) ? animFrame * 2 : (255 - animFrame) * 2;
        int brightness2 = 255 - brightness1;

        // Map brightness to color intensity (simple grayscale approximation)
        uint16_t color1 = display.color565(brightness1, brightness1, brightness1);
        uint16_t color2 = display.color565(brightness2, brightness2, brightness2);

        display.fillRect(animX + 10, barY1, animWidth - 20, barHeight, color1);
        display.fillRect(animX + 10, barY2, animWidth - 20, barHeight, color2);
    }
    else if (strcmp(animationName, "Clignotement") == 0) {
        // Rectangle qui clignote
        if (animFrame < 128) {
            display.fillRect(animX + 10, animY + 10, animWidth - 20, animHeight - 20, COLOR_YELLOW);
        }
    }
    else if (strcmp(animationName, "Pulsation") == 0) {
        // Cercle qui grossit et rétrécit
        int radius = 10 + (animFrame % 40);
        display.fillCircle(centerX, centerY, radius, COLOR_PURPLE);
    }
    else if (strcmp(animationName, "Respiration") == 0) {
        // Rectangle avec fade in/out
        int brightness = (animFrame < 128) ? animFrame * 2 : (255 - animFrame) * 2;
        uint16_t color = display.color565(0, brightness, brightness);
        display.fillRect(animX + 10, animY + 10, animWidth - 20, animHeight - 20, color);
    }
    else if (strcmp(animationName, "Strobe") == 0) {
        // Flash stroboscopique
        if (animFrame % 20 < 3) {
            display.fillRect(animX + 10, animY + 10, animWidth - 20, animHeight - 20, COLOR_WHITE);
        }
    }
    else if (strcmp(animationName, "Battement Coeur") == 0) {
        // Double pulsation
        if ((animFrame % 60 < 15) || (animFrame % 60 >= 20 && animFrame % 60 < 35)) {
            display.fillCircle(centerX, centerY, 20, COLOR_RED);
        }
    }
    else if (strcmp(animationName, "Vague") == 0) {
        // Onde sinusoïdale
        for (int x = 0; x < animWidth - 2; x += 3) {
            int y = centerY + (int)(20 * sin((x + animFrame * 2) * 0.1));
            if (y >= animY + 1 && y < animY + animHeight - 1) {
                display.fillCircle(animX + 1 + x, y, 2, COLOR_CYAN);
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
        // Traînée qui se déplace
        int tailLength = 40;
        int pos = (animFrame * 2) % (animWidth + tailLength);

        for (int i = 0; i < tailLength; i++) {
            int x = animX + pos - i;
            if (x >= animX + 1 && x < animX + animWidth - 1) {
                int brightness = 255 - (i * 255 / tailLength);
                uint16_t color = display.color565(brightness, brightness / 2, 0);
                display.drawFastVLine(x, animY + 10, animHeight - 20, color);
            }
        }
    }
    else if (strcmp(animationName, "Auto") == 0) {
        // Afficher "AUTO" avec une animation de rotation
        display.setTextSize(2);
        display.setTextColor(COLOR_GREEN);
        int16_t x1, y1;
        uint16_t w, h;
        display.getTextBounds("AUTO", 0, 0, &x1, &y1, &w, &h);
        int textX = centerX - w / 2;
        int textY = centerY - h / 2;
        display.setCursor(textX, textY);
        display.println("AUTO");

        // Cercle tournant autour
        float angle = animFrame * 0.05;
        int circleX = centerX + (int)(30 * cos(angle));
        int circleY = centerY + (int)(30 * sin(angle));
        display.fillCircle(circleX, circleY, 3, COLOR_YELLOW);
    }
    else {
        // Animation par défaut : barre horizontale
        display.fillRect(animX + 10, centerY - 10, animWidth - 20, 20, COLOR_WHITE);
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

void displayMainScreen(const char* ssid, IPAddress ip, const char* modeName, const char* animationName) {
    // Rien
}

void updateAnimationVisual(const char* animationName) {
    // Rien
}

#endif
