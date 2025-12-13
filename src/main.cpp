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
OneButton btnBoot(PIN_BUTTON_BOOT, true);    // Bouton 0 : Reboot en appui long
OneButton btn1(PIN_BUTTON_1, true);          // Bouton 1 : Changement animation
OneButton btn2(PIN_BUTTON_2, true);          // Bouton 2 : Changement mode

#ifdef HAS_NEOPIXEL
    Adafruit_NeoPixel pixels(NEOPIXEL_NUM, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
#endif

// --- VARIABLES GLOBALES ---
unsigned long previousMillis = 0;
const long interval = 1000;      // Vitesse du clignotement Heartbeat
bool ledState = false;

// Variables pour l'animation OLED
unsigned long lastOledAnimUpdate = 0;
const long oledAnimInterval = 100;  // Mise à jour animation OLED toutes les 100ms
const char* lastDisplayedAnim = "";
const char* lastDisplayedMode = "";

// --- FONCTIONS SERVEUR WEB (DÉLÉGUÉES AUX MODULES) ---
// Les fonctions handleRoot(), handleReboot(), handleNotFound() et setupWebServer()
// sont maintenant définies dans web_interface.h
// Voir : include/web_interface.h

// Les fonctions d'affichage OLED et ST7789 sont maintenant dans display.h / display.cpp

// --- CALLBACKS BOUTONS ---

// Bouton Boot : Appui Long = Redémarrage
void handleBootLongPress() {
    LOG_PRINTLN(">> APPUI LONG BOOT détecté ! Redémarrage...");
    
    #ifdef HAS_NEOPIXEL
        pixels.setPixelColor(0, pixels.Color(255, 0, 255)); // Flash Violet pour confirmer
        pixels.show();
    #endif
    
    #if defined(HAS_OLED) || defined(HAS_ST7789)
        // Afficher message de redémarrage sur les écrans
        #ifdef HAS_OLED
            display_oled.clearDisplay();
            display_oled.setTextSize(2);
            display_oled.setCursor(0, 15);
            display_oled.println("REBOOT...");
            display_oled.display();
        #endif
        #ifdef HAS_ST7789
            display_tft.fillScreen(COLOR_BLACK);
            display_tft.setTextSize(3);
            display_tft.setTextColor(COLOR_RED);
            display_tft.setCursor(50, 100);
            display_tft.println("REBOOT...");
        #endif
    #endif
    
    delay(1000); // Pause pour afficher le message
    ESP.restart();
}

// Bouton 1 : Changement d'animation
void handleBtn1Click() {
    nextGarlandAnimation();
    LOG_PRINTF(">> Bouton 1 : Animation changée -> %s\n", getGarlandAnimationName());
    
    // Mise à jour OLED
    #ifdef HAS_OLED
        updateOledAnimationStatus(getGarlandAnimationName(), getGarlandModeName(), WiFi.localIP());
    #endif
    
    #ifdef HAS_NEOPIXEL
        pixels.setPixelColor(0, pixels.Color(0, 255, 255)); // Cyan
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, pixels.Color(0, 50, 0)); // Retour vert
        pixels.show();
    #endif
}

// Bouton 2 : Changement de mode
void handleBtn2Click() {
    nextGarlandMode();
    LOG_PRINTF(">> Bouton 2 : Mode changé -> %s\n", getGarlandModeName());
    
    // Mise à jour OLED
    #ifdef HAS_OLED
        updateOledAnimationStatus(getGarlandAnimationName(), getGarlandModeName(), WiFi.localIP());
    #endif
    
    #ifdef HAS_NEOPIXEL
        pixels.setPixelColor(0, pixels.Color(255, 255, 0)); // Jaune
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, pixels.Color(0, 50, 0)); // Retour vert
        pixels.show();
    #endif
}

// --- FONCTIONS WIFI ---
void setupWifi() {
    LOG_PRINTLN("--- Démarrage WiFiMulti ---");
    int numNetworks = WIFI_NETWORKS_COUNT;
    
    for (int i = 0; i < numNetworks; i++) {
        wifiMulti.addAP(WIFI_NETWORKS[i][0], WIFI_NETWORKS[i][1]);
    }

    LOG_PRINT("Connexion WiFi en cours...");
    
    // Affichage initial sur les écrans
    displayWifiProgress(0);
    
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
        
        // Mise à jour de la progression sur les écrans
        displayWifiProgress(progress);
        
        LOG_PRINT(".");
    }
    
    if(wifiMulti.run() == WL_CONNECTED) {
        LOG_PRINTLN(" OK !");
        LOG_PRINT("SSID: "); LOG_PRINTLN(WiFi.SSID());
        LOG_PRINT("IP: "); LOG_PRINTLN(WiFi.localIP());
        
        // Affichage des infos de connexion sur les écrans
        displayWifiConnected(WiFi.SSID().c_str(), WiFi.localIP());
        
        // Affichage OLED de l'animation et du mode après connexion
        #ifdef HAS_OLED
            delay(2000); // Pause pour laisser voir l'info WiFi
            updateOledAnimationStatus(getGarlandAnimationName(), getGarlandModeName(), WiFi.localIP());
        #endif
        
        #ifdef HAS_NEOPIXEL
            pixels.setPixelColor(0, pixels.Color(0, 50, 0)); // Vert
            pixels.show();
        #endif

        // Notification Telegram de connexion WiFi (DÉSACTIVÉE)
        // sendTelegramStatus(WiFi.SSID().c_str(), WiFi.localIP());
    } else {
        LOG_PRINTLN(" Echec !");
        displayWifiFailed();
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
    displayStartup(PROJECT_NAME, PROJECT_VERSION);

    // Initialisation de la guirlande
    setupGarland();

    // Connexion WiFi (affiche la progression sur les écrans)
    setupWifi();

    // Init NeoPixel
    #ifdef HAS_NEOPIXEL
        pixels.begin();
        pixels.setBrightness(30);
        pixels.clear();
        pixels.show();
    #endif

    // Init LED Builtin (si existante)
    #ifdef PIN_LED_BUILTIN
        pinMode(PIN_LED_BUILTIN, OUTPUT);
    #endif
    
    // Démarrage Serveur Web
    if(WiFi.status() == WL_CONNECTED) {
        setupWebServer();
        // setupTelegramBot();  // DÉSACTIVÉ
        // sendTelegramStatus(WiFi.SSID().c_str(), WiFi.localIP());  // DÉSACTIVÉ
    }
}

// --- LOOP (DOIT TOURNER VITE) ---
void loop() {
    // 1. Surveillance Boutons (CRITIQUE : doit être appelé tout le temps)
    btnBoot.tick();
    btn1.tick();
    btn2.tick();

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
    
    // 6. Heartbeat Non-Bloquant (remplace delay)
    unsigned long currentMillis = millis();    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        
        // Clignotement du heartbeat
        ledState = !ledState;
        
        // Action visuelle selon la carte
        #ifdef PIN_LED_BUILTIN
            digitalWrite(PIN_LED_BUILTIN, ledState);
        #endif

        #ifdef HAS_NEOPIXEL
            // Petit battement de coeur : vert si connecté, rouge sinon
            if(wifiMulti.run() == WL_CONNECTED) {
                pixels.setPixelColor(0, ledState ? pixels.Color(0, 50, 0) : pixels.Color(0, 10, 0)); // Vert fort / Vert faible
            } else {
                pixels.setPixelColor(0, ledState ? pixels.Color(50, 0, 0) : pixels.Color(10, 0, 0)); // Rouge fort / faible
            }
            pixels.show();
        #endif
    }
    
    // 6. Rafraîchissement de l'animation OLED
    #ifdef HAS_OLED
        if (currentMillis - lastOledAnimUpdate >= oledAnimInterval) {
            lastOledAnimUpdate = currentMillis;
            // Redessiner l'écran avec la barre d'animation mise à jour
            if (WiFi.status() == WL_CONNECTED) {
                if (isAnimationActive()) {
                    updateOledAnimationStatus(getGarlandAnimationName(), getGarlandModeName(), WiFi.localIP());
                } else {
                    // Si pas d'animation active : afficher points fixes
                    displayOledSleepMode();
                }
            }
        }
    #endif
}