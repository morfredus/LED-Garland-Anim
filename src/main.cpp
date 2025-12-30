// ---
// Changelog :
// #3 (2025-12-30) : Harmonisation LCD ST7789 unique, suppression TFT/ILI9341, OLED secours, cohérence affichage
// ---
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <OneButton.h>
#include <nvs_flash.h>
#include <nvs.h>

#include "config.h"
#include "board_config.h"
#include "secrets.h"
#include "web_interface.h"
#include "display.h"
#include "garland_control.h"
// #include "telegram_control.h"  // DÉSACTIVÉ - Cause de freeze

// --- OBJETS ---
WiFiMulti wifiMulti;
WebServer server(80);
OneButton btnBoot(BUTTON_BOOT, true);    // Bouton 0 : Reboot en appui long
OneButton btn1(BUTTON_1, true);          // Bouton 1 : Changement animation
OneButton btn2(BUTTON_2, true);          // Bouton 2 : Changement mode

#ifdef HAS_NEOPIXEL
    Adafruit_NeoPixel pixels(NEOPIXEL_NUM, NEOPIXEL, NEO_GRB + NEO_KHZ800);
#endif

// --- VARIABLES GLOBALES ---
unsigned long previousMillis = 0;
const long interval = 1000;      // Vitesse du clignotement Heartbeat
bool ledState = false;

//

// --- FONCTIONS SERVEUR WEB (DÉLÉGUÉES AUX MODULES) ---
// Les fonctions handleRoot(), handleReboot(), handleNotFound() et setupWebServer()
// sont maintenant définies dans web_interface.h
// Voir : include/web_interface.h

// Les fonctions d'affichage sont maintenant dans display.h / display.cpp

// --- CALLBACKS BOUTONS ---

// Bouton Boot : Appui Long = Redémarrage
void handleBootLongPress() {
    LOG_PRINTLN(">> APPUI LONG BOOT détecté ! Redémarrage...");
    
    #ifdef HAS_NEOPIXEL
        pixels.setPixelColor(0, pixels.Color(255, 0, 255)); // Flash Violet pour confirmer
        pixels.show();
    #endif
    display_lcd.fillScreen(COLOR_BLACK);
    display_lcd.setTextSize(3);
    display_lcd.setTextColor(COLOR_RED);
    display_lcd.setCursor(50, 100);
    display_lcd.println("REBOOT...");
    delay(1000); // Pause pour afficher le message
    ESP.restart();
}

// Bouton 1 : Changement d'animation
void handleBtn1Click() {
    #ifdef HAS_NEOPIXEL
        pixels.setPixelColor(0, pixels.Color(0, 255, 255)); // Cyan
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, pixels.Color(0, 50, 0)); // Retour vert
        pixels.show();
    #endif
    // Changement d'animation
    nextGuirlandeAnimation();
    // Rafraîchir l'affichage LCD après changement d'animation
    displayLCDConnected(WiFi.SSID().c_str(), WiFi.localIP());
}


// Bouton 2 : Changement de mode
void handleBtn2Click() {
    #ifdef HAS_NEOPIXEL
        pixels.setPixelColor(0, pixels.Color(255, 255, 0)); // Jaune
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, pixels.Color(0, 50, 0)); // Retour vert
        pixels.show();
    #endif
    // Changement de mode
    nextGuirlandeMode();
    // Rafraîchir l'affichage LCD après changement de mode
    displayLCDConnected(WiFi.SSID().c_str(), WiFi.localIP());
}

// --- FONCTIONS WIFI ---
void setupWifi() {
    LOG_PRINTLN("--- Démarrage WiFiMulti ---");
    int numNetworks = WIFI_NETWORKS_COUNT;
    
    for (int i = 0; i < numNetworks; i++) {
        wifiMulti.addAP(WIFI_NETWORKS[i][0], WIFI_NETWORKS[i][1]);
    }

    LOG_PRINT("Connexion WiFi en cours...");
    
    // Affichage initial sur l'écran LCD
    displayLCDProgress(0);
    
    #ifdef HAS_NEOPIXEL
        pixels.setPixelColor(0, pixels.Color(50, 50, 0)); // Jaune
        pixels.show();
    #endif

    // Tentatives de connexion avec affichage de la progression
    int attempts = 0;
    const int maxAttempts = 20;
    
    while(wifiMulti.run() != WL_CONNECTED && attempts < maxAttempts) {
        delay(500);
        attempts++;
        int progress = (attempts * 100) / maxAttempts;
        
        // Mise à jour de la progression sur l'écran LCD
        displayLCDProgress(progress);
        
        LOG_PRINT(".");
    }
    
    if(wifiMulti.run() == WL_CONNECTED) {
        LOG_PRINTLN(" OK !");
        LOG_PRINT("SSID: "); LOG_PRINTLN(WiFi.SSID());
        LOG_PRINT("IP: "); LOG_PRINTLN(WiFi.localIP());
        displayLCDConnected(WiFi.SSID().c_str(), WiFi.localIP());
        #ifdef HAS_NEOPIXEL
            pixels.setPixelColor(0, pixels.Color(0, 50, 0)); // Vert
            pixels.show();
        #endif
        // Notification Telegram de connexion WiFi (DÉSACTIVÉE)
        // sendTelegramStatus(WiFi.SSID().c_str(), WiFi.localIP());
    } else {
        LOG_PRINTLN(" Echec !");
        displayLCDFailed();
    }
}

// --- SETUP ---
void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(1000); // Wait for Serial USB
    
    // Initialiser NVS pour la persistence
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }
    
    // Config Boutons
    btnBoot.attachLongPressStart(handleBootLongPress);
    btnBoot.setPressMs(1000); // Durée pour considérer un appui long (ms)
    
    btn1.attachClick(handleBtn1Click);
    btn2.attachClick(handleBtn2Click);

    // Initialisation des affichages (OLED et/ou ST7789) - AVANT WiFi pour afficher la progression
    setupDisplays();
    displayLCDStartup(PROJECT_NAME, PROJECT_VERSION);

    // Initialisation de la guirlande
    setupGarland();


    // Connexion WiFi (affiche la progression sur l'écran LCD)
    setupWifi();

    // Démarrage du serveur web
    setupWebServer();

    // Init NeoPixel
    #ifdef HAS_NEOPIXEL
        pixels.begin();
        pixels.setBrightness(30);
        pixels.clear();
        pixels.show();
    #endif

        // Init LED Builtin (si existante)
        #ifdef LED_BUILTIN
            pinMode(LED_BUILTIN, OUTPUT);
        #endif
    

    // 2. Mise à jour de l'animation de guirlande
    updateGarland();

    // 3. Gestion Serveur Web (non-bloquant)
    server.handleClient();

    // 4. Commandes Telegram (DÉSACTIVÉES - Cause de freeze)
    // static unsigned long lastTelegramCheck = 0;
    // if (millis() - lastTelegramCheck > 500) {  // Check Telegram max toutes les 500ms
    //     lastTelegramCheck = millis();
    //     handleTelegramBot();
    // }

    // 5. Libération CPU (CRITIQUE pour watchdog)
    yield();
    
    // 6. Heartbeat déplacé dans loop()
}

void loop() {
    // Gestion Serveur Web (non-bloquant)
    server.handleClient();
    // Mise à jour de la guirlande
    updateGarland();

    // Rafraîchissement du graphe d'animation LCD (zone dédiée)
    #ifdef HAS_LCD
    drawAnimationGraph(12, 162, LCD_WIDTH-24, 36);
    #endif

    // Tick boutons physiques (OneButton)
    btnBoot.tick();
    btn1.tick();
    btn2.tick();

    // Heartbeat LED/NeoPixel
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        ledState = !ledState;
        #ifdef LED_BUILTIN
            digitalWrite(LED_BUILTIN, ledState);
        #endif
        #ifdef HAS_NEOPIXEL
            if(wifiMulti.run() == WL_CONNECTED) {
                pixels.setPixelColor(0, ledState ? pixels.Color(0, 50, 0) : pixels.Color(0, 10, 0));
            } else {
                pixels.setPixelColor(0, ledState ? pixels.Color(50, 0, 0) : pixels.Color(10, 0, 0));
            }
            pixels.show();
        #endif
    }
    yield();
}