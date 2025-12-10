/**
 * @file display.cpp
 * @brief Implémentation du module de gestion des écrans
 * @version 0.5.1
 * @date 2025-12-10
 */

#include "display.h"

// --- INSTANCIATION DES OBJETS ---
#ifdef HAS_OLED
    Adafruit_SSD1306 display_oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
    // Variable globale pour l'animation
    static uint8_t animFrame = 0;
#endif

#ifdef HAS_ST7789
    Adafruit_ST7789 display_tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
#endif

// =============================================================================
// FONCTIONS PUBLIQUES - INTERFACE UNIFIÉE
// =============================================================================

void setupDisplays() {
    LOG_PRINTLN("--- Initialisation des écrans ---");
    
    #ifdef HAS_OLED
        if (setupOled()) {
            LOG_PRINTLN("✓ OLED initialisé");
        } else {
            LOG_PRINTLN("✗ OLED non détecté");
        }
    #endif
    
    #ifdef HAS_ST7789
        if (setupST7789()) {
            LOG_PRINTLN("✓ ST7789 initialisé");
        } else {
            LOG_PRINTLN("✗ ST7789 non détecté");
        }
    #endif
}

void displayStartup(const char* projectName, const char* projectVersion) {
    #ifdef HAS_OLED
        display_oled.clearDisplay();
        display_oled.setTextSize(1);
        display_oled.setTextColor(SSD1306_WHITE);
        display_oled.setCursor(0, 0);
        display_oled.println(projectName);
        display_oled.println("v" + String(projectVersion));
        display_oled.display();
    #endif
    
    #ifdef HAS_ST7789
        displayST7789Startup(projectName, projectVersion);
    #endif
}

void displayWifiProgress(int progress) {
    #ifdef HAS_OLED
        updateOledStatus("Connexion WiFi...", progress);
    #endif
    
    #ifdef HAS_ST7789
        displayST7789Progress(progress);
    #endif
}

void displayWifiConnected(const char* ssid, IPAddress ip) {
    #ifdef HAS_OLED
        updateOledConnected(ssid, ip);
    #endif
    
    #ifdef HAS_ST7789
        displayST7789Connected(ssid, ip);
    #endif
}

void displayWifiFailed() {
    #ifdef HAS_OLED
        updateOledStatus("WiFi: Echec", 100);
    #endif
    
    #ifdef HAS_ST7789
        displayST7789Failed();
    #endif
}

void displayAnimationMode(IPAddress ip) {
    // Forward declaration - la fonction sera appellée de main.cpp
    // qui a accès à getGarlandAnimationName() et getGarlandModeName()
    // Pour cela, on crée un wrapper qui sera appelé depuis main.cpp
    // Voir main.cpp pour l'appel réel après connexion WiFi
}

// =============================================================================
// FONCTIONS INTERNES - OLED
// =============================================================================

#ifdef HAS_OLED
bool setupOled() {
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    
    if (!display_oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        return false;
    }
    
    display_oled.clearDisplay();
    display_oled.display();
    return true;
}

void updateOledStatus(const char* status, int progress) {
    display_oled.clearDisplay();
    display_oled.setTextSize(1);
    display_oled.setCursor(0, 0);
    
    // Adaptation du contenu selon la hauteur disponible
    if (OLED_HEIGHT >= 64) {
        // Écran 128x64 : affichage complet
        display_oled.println(PROJECT_NAME);
        display_oled.println("v" + String(PROJECT_VERSION));
        display_oled.println();
    }
    // Pour 128x32, on saute directement au statut
    
    // Statut
    display_oled.println(status);
    
    // Barre de progression si demandée
    if (progress >= 0 && progress <= 100) {
        int barY = (OLED_HEIGHT >= 64) ? 40 : 20;  // Position adaptée
        int barWidth = (OLED_WIDTH - 4) * progress / 100;
        display_oled.drawRect(0, barY, OLED_WIDTH, 10, SSD1306_WHITE);
        display_oled.fillRect(2, barY + 2, barWidth, 6, SSD1306_WHITE);
        display_oled.setCursor(0, barY + 12);
        display_oled.print(progress);
        display_oled.println("%");
    }
    
    display_oled.display();
}

void updateOledConnected(const char* ssid, IPAddress ip) {
    display_oled.clearDisplay();
    display_oled.setTextSize(1);
    display_oled.setCursor(0, 0);
    
    // Adaptation du contenu selon la hauteur disponible
    if (OLED_HEIGHT >= 64) {
        // Écran 128x64 : affichage complet
        display_oled.println(PROJECT_NAME);
        display_oled.println("v" + String(PROJECT_VERSION));
        display_oled.println();
        display_oled.println("WiFi:");
        display_oled.println(ssid);
        display_oled.println();
        display_oled.print("IP: ");
        display_oled.println(ip);
    } else {
        // Écran 128x32 : affichage minimal
        display_oled.println("WiFi OK");
        display_oled.println(ssid);
        display_oled.println();
        display_oled.print("IP: ");
        display_oled.println(ip);
    }
    
    display_oled.display();
}
#endif

// =============================================================================
// FONCTION PUBLIQUE - MISE À JOUR ANIMATION/MODE (disponible même sans OLED)
// =============================================================================

void updateOledAnimationStatus(const char* animationName, const char* modeName, IPAddress ip) {
    #ifdef HAS_OLED
        display_oled.clearDisplay();
        display_oled.setTextSize(1);
        display_oled.setCursor(0, 0);
        
        // Adaptation du contenu selon la hauteur disponible
        if (OLED_HEIGHT >= 64) {
            // Écran 128x64 : affichage complet
            display_oled.println(PROJECT_NAME);
            display_oled.println("v" + String(PROJECT_VERSION));
            display_oled.println();
            
            // IP
            if (ip != IPAddress(0, 0, 0, 0)) {
                display_oled.print("IP: ");
                display_oled.println(ip);
            }
            
            // Animation
            display_oled.print("Anim: ");
            display_oled.println(animationName);
            
            // Mode
            display_oled.print("Mode: ");
            display_oled.println(modeName);
            
            // Animation visuelle sur la dernière ligne (ligne 7)
            drawAnimationBar(animationName);
        } else {
            // Écran 128x32 : affichage minimal (IP + Mode + Animation)
            // IP
            if (ip != IPAddress(0, 0, 0, 0)) {
                display_oled.print("IP: ");
                display_oled.println(ip);
            }
            
            // Mode (inversé avec Animation)
            display_oled.print("M: ");
            display_oled.println(modeName);
            
            // Animation (inversé avec Mode)
            display_oled.print("A: ");
            display_oled.println(animationName);
            
            // Animation visuelle sur la dernière ligne
            drawAnimationBar(animationName);
        }
        
        display_oled.display();
    #endif
    // Si HAS_OLED n'est pas défini, la fonction ne fait rien
}

// =============================================================================
// FONCTION INTERNE - ANIMATION VISUELLE
// =============================================================================

#ifdef HAS_OLED
/**
 * @brief Dessine une barre d'animation visuelle selon l'animation en cours
 * @param animationName Nom de l'animation
 */
void drawAnimationBar(const char* animationName) {
    int lastY = OLED_HEIGHT - 8;  // Dernière ligne (8 pixels de hauteur pour le texte)
    
    // Afficher points fixes si animation OFF
    if (strcmp(animationName, "Eteint") == 0) {
        // Affiche 3 points fixes au bas de l'écran
        display_oled.fillCircle(OLED_WIDTH / 4, lastY + 3, 1, SSD1306_WHITE);
        display_oled.fillCircle(OLED_WIDTH / 2, lastY + 3, 1, SSD1306_WHITE);
        display_oled.fillCircle(3 * OLED_WIDTH / 4, lastY + 3, 1, SSD1306_WHITE);
        return;
    }
    
    // Incrémenter le frame à chaque appel (mis à jour toutes les 100ms depuis main.cpp)
    animFrame = (animFrame + 1) % 256;
    
    // Animations visuelles selon le type
    if (strcmp(animationName, "Fade Alterne") == 0) {
        // Barre progressant d'un côté à l'autre
        int barWidth = 20;
        int pos = (animFrame % 4) * 20;
        display_oled.fillRect(pos, lastY, barWidth, 6, SSD1306_WHITE);
        display_oled.fillRect((pos + 30) % OLED_WIDTH, lastY, barWidth, 6, SSD1306_WHITE);
    } 
    else if (strcmp(animationName, "Clignotement") == 0) {
        // Clignotement du rectangle
        if (animFrame % 2 == 0) {
            display_oled.fillRect(0, lastY, OLED_WIDTH, 6, SSD1306_WHITE);
        } else {
            display_oled.drawRect(0, lastY, OLED_WIDTH, 6, SSD1306_WHITE);
        }
    } 
    else if (strcmp(animationName, "Onde Douce") == 0) {
        // Onde sinusoïdale simple
        for (int x = 0; x < OLED_WIDTH; x += 4) {
            int waveY = lastY + 2 + (int)(2 * sin((x + animFrame * 4) * 0.1));
            display_oled.drawPixel(x, waveY, SSD1306_WHITE);
        }
    } 
    else if (strcmp(animationName, "Stroboscope") == 0) {
        // Lignes intermittentes
        if (animFrame < 4) {
            for (int x = 0; x < OLED_WIDTH; x += 8) {
                display_oled.fillRect(x, lastY, 4, 6, SSD1306_WHITE);
            }
        }
    } 
    else if (strcmp(animationName, "Pulsation") == 0) {
        // Pulsation du centre vers les bords
        int size = (animFrame % 4) + 2;
        int centerX = OLED_WIDTH / 2;
        display_oled.fillRect(centerX - size, lastY + 1, size * 2, 4, SSD1306_WHITE);
    } 
    else if (strcmp(animationName, "Poursuite") == 0) {
        // Point qui se déplace
        int pos = (animFrame * 16) % OLED_WIDTH;
        display_oled.fillRect(pos, lastY + 1, 8, 4, SSD1306_WHITE);
    } 
    else if (strcmp(animationName, "Battement") == 0) {
        // Deux points qui clignotent alternativement
        if (animFrame % 2 == 0) {
            display_oled.fillRect(20, lastY + 1, 8, 4, SSD1306_WHITE);
        } else {
            display_oled.fillRect(100, lastY + 1, 8, 4, SSD1306_WHITE);
        }
    } 
    else if (strcmp(animationName, "Scintillement") == 0) {
        // Points aléatoires
        for (int i = 0; i < 8; i++) {
            int x = (animFrame * 16 + i * 16) % OLED_WIDTH;
            if ((animFrame + i) % 2 == 0) {
                display_oled.drawPixel(x, lastY + 3, SSD1306_WHITE);
            }
        }
    } 
    else if (strcmp(animationName, "Arc-en-ciel") == 0) {
        // Gradient simulé
        for (int x = 0; x < OLED_WIDTH; x += 2) {
            int offset = (x + animFrame * 2) % OLED_WIDTH;
            if ((offset / 16) % 2 == 0) {
                display_oled.drawPixel(x, lastY + 2, SSD1306_WHITE);
            }
        }
    } 
    else if (strcmp(animationName, "Respiration") == 0) {
        // Barre qui grossit et rétrécit
        int width = 40 + (int)(30 * sin(animFrame * 0.785));
        int x = (OLED_WIDTH - width) / 2;
        display_oled.fillRect(x, lastY + 1, width, 4, SSD1306_WHITE);
    } 
    else if (strcmp(animationName, "Feu") == 0) {
        // Motif de feu (pointillés qui montent)
        for (int i = 0; i < 8; i++) {
            int x = i * 16;
            if ((i + animFrame) % 3 == 0) {
                display_oled.drawPixel(x, lastY + 2, SSD1306_WHITE);
                display_oled.drawPixel(x + 2, lastY + 1, SSD1306_WHITE);
            }
        }
    } 
    else if (strcmp(animationName, "Clignotement Doux") == 0) {
        // Barre qui s'estompe
        int brightness = (animFrame % 4);
        for (int x = 0; x < OLED_WIDTH; x += 4) {
            if (brightness > 1) {
                display_oled.drawPixel(x, lastY + 3, SSD1306_WHITE);
            }
        }
    } 
    else if (strcmp(animationName, "Meteore") == 0) {
        // Traînée qui se déplace
        int pos = (animFrame * 20) % OLED_WIDTH;
        display_oled.fillRect(pos - 8, lastY + 2, 12, 2, SSD1306_WHITE);
        display_oled.drawPixel(pos, lastY + 1, SSD1306_WHITE);
    } 
    else {
        // Animation par défaut : barre simple
        display_oled.drawRect(0, lastY, OLED_WIDTH, 6, SSD1306_WHITE);
    }
}
#endif

// =============================================================================
// FONCTIONS INTERNES - ST7789
// =============================================================================

#ifdef HAS_ST7789
bool setupST7789() {
    // Configuration du backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH); // Allume le rétroéclairage
    
    // Initialisation du TFT
    display_tft.init(ST7789_WIDTH, ST7789_HEIGHT);
    display_tft.setRotation(ST7789_ROTATION);
    display_tft.fillScreen(COLOR_BLACK);
    
    return true; // ST7789 ne retourne pas d'erreur, on suppose qu'il est présent
}

void displayST7789Startup(const char* projectName, const char* projectVersion) {
    display_tft.fillScreen(COLOR_BLACK);
    display_tft.setTextColor(COLOR_CYAN);
    display_tft.setTextSize(3);
    
    // Calcul du centrage horizontal pour le nom du projet
    int16_t x1, y1;
    uint16_t w, h;
    display_tft.getTextBounds(projectName, 0, 0, &x1, &y1, &w, &h);
    int centerX = (ST7789_WIDTH - w) / 2;
    
    display_tft.setCursor(centerX, 80);
    display_tft.println(projectName);
    
    // Version
    display_tft.setTextSize(2);
    display_tft.setTextColor(COLOR_WHITE);
    String versionStr = "v" + String(projectVersion);
    display_tft.getTextBounds(versionStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (ST7789_WIDTH - w) / 2;
    display_tft.setCursor(centerX, 120);
    display_tft.println(versionStr);
}

void displayST7789Progress(int progress) {
    // Zone pour le texte de statut
    display_tft.fillRect(0, 40, ST7789_WIDTH, 30, COLOR_BLACK);
    display_tft.setTextSize(2);
    display_tft.setTextColor(COLOR_YELLOW);
    
    int16_t x1, y1;
    uint16_t w, h;
    display_tft.getTextBounds("Connexion WiFi...", 0, 0, &x1, &y1, &w, &h);
    int centerX = (ST7789_WIDTH - w) / 2;
    display_tft.setCursor(centerX, 50);
    display_tft.println("Connexion WiFi...");
    
    // Barre de progression
    int barWidth = ST7789_WIDTH - 40;
    int barHeight = 30;
    int barX = 20;
    int barY = 160;
    
    // Efface la zone de la barre
    display_tft.fillRect(barX - 2, barY - 2, barWidth + 4, barHeight + 20, COLOR_BLACK);
    
    // Contour de la barre
    display_tft.drawRect(barX, barY, barWidth, barHeight, COLOR_WHITE);
    
    // Remplissage de la progression
    int fillWidth = (barWidth - 4) * progress / 100;
    if (fillWidth > 0) {
        display_tft.fillRect(barX + 2, barY + 2, fillWidth, barHeight - 4, COLOR_GREEN);
    }
    
    // Pourcentage
    display_tft.setTextSize(2);
    display_tft.setTextColor(COLOR_WHITE);
    String percentStr = String(progress) + "%";
    display_tft.getTextBounds(percentStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (ST7789_WIDTH - w) / 2;
    display_tft.setCursor(centerX, barY + barHeight + 5);
    display_tft.println(percentStr);
}

void displayST7789Connected(const char* ssid, IPAddress ip) {
    display_tft.fillScreen(COLOR_BLACK);
    
    // Titre
    display_tft.setTextSize(2);
    display_tft.setTextColor(COLOR_CYAN);
    int16_t x1, y1;
    uint16_t w, h;
    display_tft.getTextBounds(PROJECT_NAME, 0, 0, &x1, &y1, &w, &h);
    int centerX = (ST7789_WIDTH - w) / 2;
    display_tft.setCursor(centerX, 20);
    display_tft.println(PROJECT_NAME);
    
    // Version
    display_tft.setTextSize(1);
    display_tft.setTextColor(COLOR_WHITE);
    String versionStr = "v" + String(PROJECT_VERSION);
    display_tft.getTextBounds(versionStr.c_str(), 0, 0, &x1, &y1, &w, &h);
    centerX = (ST7789_WIDTH - w) / 2;
    display_tft.setCursor(centerX, 45);
    display_tft.println(versionStr);
    
    // Ligne de séparation
    display_tft.drawLine(20, 60, ST7789_WIDTH - 20, 60, COLOR_CYAN);
    
    // WiFi connecté
    display_tft.setTextSize(2);
    display_tft.setTextColor(COLOR_GREEN);
    display_tft.setCursor(20, 80);
    display_tft.println("WiFi Connecte");
    
    // SSID
    display_tft.setTextSize(1);
    display_tft.setTextColor(COLOR_YELLOW);
    display_tft.setCursor(20, 110);
    display_tft.println("Reseau:");
    display_tft.setTextColor(COLOR_WHITE);
    display_tft.setCursor(20, 125);
    display_tft.println(ssid);
    
    // Adresse IP
    display_tft.setTextColor(COLOR_YELLOW);
    display_tft.setCursor(20, 150);
    display_tft.println("Adresse IP:");
    display_tft.setTextColor(COLOR_WHITE);
    display_tft.setTextSize(2);
    display_tft.setCursor(20, 170);
    display_tft.println(ip);
}

void displayST7789Failed() {
    display_tft.fillScreen(COLOR_BLACK);
    
    display_tft.setTextSize(3);
    display_tft.setTextColor(COLOR_RED);
    
    int16_t x1, y1;
    uint16_t w, h;
    display_tft.getTextBounds("ERREUR", 0, 0, &x1, &y1, &w, &h);
    int centerX = (ST7789_WIDTH - w) / 2;
    
    display_tft.setCursor(centerX, 80);
    display_tft.println("ERREUR");
    
    display_tft.setTextSize(2);
    display_tft.setTextColor(COLOR_WHITE);
    display_tft.getTextBounds("WiFi Echec", 0, 0, &x1, &y1, &w, &h);
    centerX = (ST7789_WIDTH - w) / 2;
    display_tft.setCursor(centerX, 120);
    display_tft.println("WiFi Echec");
}
#endif

// =============================================================================
// GESTION MODE NUIT
// =============================================================================

void displayOledSleepMode() {
    #ifdef HAS_OLED
        display_oled.clearDisplay();
        display_oled.setTextSize(1);
        display_oled.setTextColor(SSD1306_WHITE);
        
        // Affiche seulement 3-4 points fixes au centre selon la hauteur
        if (OLED_HEIGHT >= 64) {
            // Écran 128x64 : points au centre avec texte "Sleep" au-dessus
            display_oled.setCursor(55, 10);
            display_oled.println("SLEEP");
            
            // Points au centre
            display_oled.fillCircle(40, 32, 2, SSD1306_WHITE);
            display_oled.fillCircle(64, 32, 2, SSD1306_WHITE);
            display_oled.fillCircle(88, 32, 2, SSD1306_WHITE);
        } else {
            // Écran 128x32 : points plus petits au centre
            display_oled.setCursor(45, 2);
            display_oled.println("ZZZ");
            
            display_oled.fillCircle(42, 16, 1, SSD1306_WHITE);
            display_oled.fillCircle(64, 16, 1, SSD1306_WHITE);
            display_oled.fillCircle(86, 16, 1, SSD1306_WHITE);
        }
        
        display_oled.display();
    #endif
}
