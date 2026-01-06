/**
 * @file display.cpp
 * @brief Implémentation du module de gestion de l'écran ST7789
 * @version 2.0.0
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
            displayMainScreen(ssid, ip, modeName, animationName, matrixAnimationName);
            break;
        case DISPLAY_MODE_STATIC: {
            // Affichage statique : nom projet, version, SSID, IP uniquement
            display.fillScreen(COLOR_BLACK);
            int16_t x1, y1; uint16_t w, h;
            int centerX;
            display.setTextSize(2);
            display.setTextColor(COLOR_CYAN);
            display.getTextBounds(PROJECT_NAME, 0, 0, &x1, &y1, &w, &h);
            centerX = (ST7789_WIDTH - w) / 2;
            display.setCursor(centerX, 20);
            display.println(PROJECT_NAME);
            display.setTextSize(1);
            display.setTextColor(COLOR_WHITE);
            String versionStr = "v" + String(PROJECT_VERSION);
            display.getTextBounds(versionStr.c_str(), 0, 0, &x1, &y1, &w, &h);
            centerX = (ST7789_WIDTH - w) / 2;
            display.setCursor(centerX, 45);
            display.println(versionStr);
            display.setTextColor(COLOR_YELLOW);
            display.setCursor(10, 80);
            display.print("SSID: ");
            display.setTextColor(COLOR_WHITE);
            display.println(ssid);
            display.setTextColor(COLOR_GREEN);
            display.setCursor(10, 100);
            display.print("IP: ");
            display.setTextColor(COLOR_WHITE);
            display.println(ip.toString().c_str());
            break;
        }
        case DISPLAY_MODE_OFF:
            // Éteint : efface d'abord puis coupe le rétroéclairage
            display.fillScreen(COLOR_BLACK);
            digitalWrite(LCD_BLK, LOW); // coupe le rétroéclairage
            break;
        default:
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
    display.fillScreen(COLOR_BLACK);

    int16_t x1, y1;
    uint16_t w, h;

    // --- NOM DE L'APPLICATION (ligne 1, centré) ---
    display.setTextSize(1);
    display.setTextColor(COLOR_CYAN);
    display.getTextBounds(PROJECT_NAME, 0, 0, &x1, &y1, &w, &h);
    int centerX = (ST7789_WIDTH - w) / 2;
    display.setCursor(centerX, 2);
    display.println(PROJECT_NAME);

    // --- VERSION (ligne 2, centrée) ---
    String versionStr = "v" + String(PROJECT_VERSION);
    display.setTextColor(COLOR_WHITE);
    display.getTextBounds(versionStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (ST7789_WIDTH - w) / 2;
    display.setCursor(centerX, 12);
    display.println(versionStr);

    // --- LIGNE DE SÉPARATION 1 ---
    display.drawLine(0, 22, ST7789_WIDTH, 22, COLOR_CYAN);

    // --- MODE + ANIMATION GUIRLANDE (compact) ---
    display.setTextSize(1);
    display.setTextColor(COLOR_MAGENTA);
    display.setCursor(3, 26);
    display.print("Mode:");
    display.setTextColor(COLOR_WHITE);
    display.setCursor(35, 26);
    display.println(modeName);

    display.setTextColor(COLOR_ORANGE);
    display.setCursor(3, 36);
    display.print("Anim:");
    display.setTextColor(COLOR_WHITE);
    display.setCursor(35, 36);
    display.println(animationName);

    // --- AFFICHER L'ANIMATION MATRICE SI DISPONIBLE ---
    if (matrixAnimationName != nullptr) {
        display.setTextColor(COLOR_RED);
        display.setCursor(3, 46);
        display.print("Matrix:");
        display.setTextColor(COLOR_WHITE);
        display.setCursor(40, 46);
        display.println(matrixAnimationName);
        // Décaler le reste de l'écran vers le bas
        display.drawLine(0, 56, ST7789_WIDTH, 56, COLOR_CYAN);
        display.setTextSize(1);
        display.setTextColor(COLOR_YELLOW);
        display.setCursor(3, 60);
        display.print("SSID:");
        display.setTextColor(COLOR_WHITE);
        display.setCursor(35, 60);
        display.println(ssid);
        display.setTextColor(COLOR_GREEN);
        display.setCursor(3, 70);
        display.print("IP:");
        display.setTextColor(COLOR_WHITE);
        display.setCursor(35, 70);
        display.println(ip.toString().c_str());
        display.drawLine(0, 80, ST7789_WIDTH, 80, COLOR_CYAN);
    } else {
        // --- LIGNE DE SÉPARATION 2 ---
        display.drawLine(0, 46, ST7789_WIDTH, 46, COLOR_CYAN);

        // --- RÉSEAU WiFi : SSID + IP ---
        display.setTextSize(1);
        display.setTextColor(COLOR_YELLOW);
        display.setCursor(3, 50);
        display.print("SSID:");
        display.setTextColor(COLOR_WHITE);
        display.setCursor(35, 50);
        display.println(ssid);

        display.setTextColor(COLOR_GREEN);
        display.setCursor(3, 60);
        display.print("IP:");
        display.setTextColor(COLOR_WHITE);
        display.setCursor(35, 60);
        display.println(ip.toString().c_str());

        // --- LIGNE DE SÉPARATION 3 ---
        display.drawLine(0, 70, ST7789_WIDTH, 70, COLOR_CYAN);
    }

    // --- ZONE GRAPHIQUE D'ANIMATION (réduite pour ligne matrice) ---
    // Rectangle de la zone d'animation ajusté pour 3 lignes de texte
    int rectY = matrixAnimationName != nullptr ? 84 : 73;
    int rectHeight = matrixAnimationName != nullptr ? ST7789_HEIGHT - 88 : ST7789_HEIGHT - 76;
    display.drawRect(2, rectY, ST7789_WIDTH - 4, rectHeight, COLOR_WHITE);

    // Affichage visuel de l'animation
    updateAnimationVisual(animationName, matrixAnimationName != nullptr);
}

void updateAnimationVisual(const char* animationName, bool hasMatrix) {
    // Zone d'animation ajustée selon présence ligne matrice
    int animX = 3;
    int animY = hasMatrix ? 85 : 74;
    int animWidth = ST7789_WIDTH - 6;  // 240 - 6 = 234
    int animHeight = hasMatrix ? ST7789_HEIGHT - 90 : ST7789_HEIGHT - 78;  // Hauteur réduite si matrice affichée

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

