
/**
 * @file main.cpp
 * @brief Point d'entrée principal du projet LED-Garland-Anim
 * @version 5.2.0
 * @date 2026-01-07
 *
 * OTA support: ArduinoOTA (upload firmware over WiFi) + Web OTA (Update.h)
 */
#include <ArduinoOTA.h>

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebServer.h>
#include <OneButton.h>
#include <nvs_flash.h>
#include <nvs.h>
#include <ESPmDNS.h>

#include "config.h"
#include "board_config.h"
#include "secrets.h"
#include "web_interface.h"

#include "garland_control.h"
#include "matrix8x8_control.h"

// --- OBJETS ---
WiFiMulti wifiMulti;
WebServer server(80);
OneButton btnBoot(BUTTON_BOOT, true);    // Bouton 0 : Reboot en appui long
OneButton btn1(BUTTON_1, true);          // Bouton 1 : Changement animation guirlande
OneButton btn2(BUTTON_2, true);          // Bouton 2 : Changement animation matrice
OneButton btn3(BUTTON_3, true);          // Bouton 3 : Changement de mode

// Affichage OLED
#include "display_oled.h"
// --- VARIABLES GLOBALES ---
unsigned long previousMillis = 0;
const long interval = 1000;      // Vitesse du clignotement Heartbeat
bool ledState = false;

// Variables pour l'animation ST7789
unsigned long lastDisplayUpdate = 0;
const long displayUpdateInterval = 200;  // Mise à jour animation ST7789 toutes les 200ms (allège la charge SPI)

// --- CALLBACKS BOUTONS ---

// Bouton Boot : Appui Long = Redémarrage
void handleBootLongPress() {
    LOG_PRINTLN(">> APPUI LONG BOOT détecté ! Redémarrage...");

    // Affichage OLED : reboot (optionnel)

    delay(1000); // Pause pour afficher le message
    ESP.restart();
}

// Bouton 1 : Changement d'animation guirlande
void handleBtn1Click() {
    nextGarlandAnimation();
    LOG_PRINTF("[CHANGE] - Garland - %s (button)\n", getGarlandAnimationName());
    String mDnsStr = String(getDeviceName()) + ".local";
    displayScreenByMode(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName(), getMatrix8x8AnimationName(), mDnsStr.c_str());
}

// Bouton 2 : Changement d'animation matrice
void handleBtn2Click() {
    nextMatrix8x8Animation();
    LOG_PRINTF("[CHANGE] - Matrix - %s (button)\n", getMatrix8x8AnimationName());
    String mDnsStr = String(getDeviceName()) + ".local";
    displayScreenByMode(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName(), getMatrix8x8AnimationName(), mDnsStr.c_str());
}

// Bouton 3 : Changement de mode
void handleBtn3Click() {
    nextGarlandMode();
    LOG_PRINTF("[CHANGE] - Mode - %s (button)\n", getGarlandModeName());
    String mDnsStr = String(getDeviceName()) + ".local";
    displayScreenByMode(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName(), getMatrix8x8AnimationName(), mDnsStr.c_str());
}

// --- FONCTIONS WIFI ---
void setupWifi() {
    LOG_PRINTLN("--- Démarrage WiFiMulti ---");
    int numNetworks = WIFI_NETWORKS_COUNT;

    for (int i = 0; i < numNetworks; i++) {
        wifiMulti.addAP(WIFI_NETWORKS[i][0], WIFI_NETWORKS[i][1]);
    }

    LOG_PRINT("Connexion WiFi en cours...");

    // Affichage initial sur l'écran
    displayBootScreen(PROJECT_NAME, PROJECT_VERSION, 0);

    // Tentatives de connexion avec affichage de la progression
    int attempts = 0;
    const int maxAttempts = 20;

    while(wifiMulti.run() != WL_CONNECTED && attempts < maxAttempts) {
        delay(500);
        attempts++;
        int progress = (attempts * 100) / maxAttempts;

        // Mise à jour de la progression sur l'écran
        displayBootScreen(PROJECT_NAME, PROJECT_VERSION, progress);

        LOG_PRINT(".");
    }

    if(wifiMulti.run() == WL_CONNECTED) {
        LOG_PRINTLN(" OK !");
        LOG_PRINT("SSID: "); LOG_PRINTLN(WiFi.SSID());
        LOG_PRINT("IP: "); LOG_PRINTLN(WiFi.localIP());

        // Affichage de l'écran principal avec toutes les infos
        String mDnsStr = String(getDeviceName()) + ".local";
        displayScreenByMode(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName(), getMatrix8x8AnimationName(), mDnsStr.c_str());

        delay(2000); // Pause pour laisser voir l'écran
    } else {
        LOG_PRINTLN(" Echec !");
        // Afficher message d'échec sur l'écran (optionnel, à personnaliser pour OLED)
    }
}

// --- SETUP ---
void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    
    #ifdef TARGET_ESP32C3_HW675
        // ESP32-C3 USB CDC nécessite un délai plus long et attente explicite
        delay(2000);
        while (!Serial && millis() < 3000) {
            delay(10);
        }
        Serial.println();
        Serial.println("==========================================");
        Serial.println("ESP32-C3 HW-675 - LED Garland Controller");
        Serial.println("==========================================");
        Serial.flush();
    #else
        delay(1000); // Wait for Serial USB
    #endif

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
    btn3.attachClick(handleBtn3Click);

    // Sur HW-675 (ESP32-C3), utiliser le bouton BOOT (GPIO9) pour changer de mode en simple clic
    // et conserver l'appui long pour reboot.
    #ifdef TARGET_ESP32C3_HW675
        btnBoot.attachClick(handleBtn2Click);
    #endif

    // Initialisation de l'affichage OLED AVANT WiFi pour afficher la progression
    setupDisplay();
    displayBootScreen(PROJECT_NAME, PROJECT_VERSION, -1);

    // Initialisation de la guirlande
    setupGarland();

    // Initialisation de la matrice 8x8 NeoPixel
    setupMatrix8x8();

    // Chargement de la configuration sauvegardée (mode, animation, durées) depuis NVS
    // Si aucune sauvegarde, valeurs par défaut utilisées
    loadGarlandSettings();

    // Connexion WiFi (affiche la progression sur l'écran)
    setupWifi();

    // Init LED Builtin (si existante)
    #ifdef LED_BUILTIN
        pinMode(LED_BUILTIN, OUTPUT);
    #endif

    // OTA: configuration et démarrage si WiFi OK
    if(WiFi.status() == WL_CONNECTED) {
        // Démarrage mDNS avec le nom d'appareil configuré
        const char* deviceName = getDeviceName();
        if (MDNS.begin(deviceName)) {
            LOG_PRINTF("✓ mDNS démarré : %s.local\n", deviceName);
            MDNS.addService("http", "tcp", 80);
        } else {
            LOG_PRINTLN("✗ Erreur démarrage mDNS");
        }
        
        ArduinoOTA.setHostname(deviceName);
        ArduinoOTA.onStart([]() {
            LOG_PRINTLN("[OTA] Start updating...");
        });
        ArduinoOTA.onEnd([]() {
            LOG_PRINTLN("[OTA] Update finished!");
        });
        ArduinoOTA.onError([](ota_error_t error) {
            LOG_PRINTF("[OTA] Error[%u]\n", error);
        });
        ArduinoOTA.begin();
        setupWebServer();
    }
}

// --- LOOP (DOIT TOURNER VITE) ---
void loop() {
    // 1. Surveillance Boutons (CRITIQUE : doit être appelé tout le temps)
    btnBoot.tick();
    btn1.tick();
    btn2.tick();
    btn3.tick();

    // 2. Mise à jour de l'animation de guirlande
    updateGarland();

    // 2b. Mise à jour de l'animation de la matrice 8x8
    updateMatrix8x8();

    // 3. Gestion Serveur Web (non-bloquant)
    server.handleClient();

    // 4. OTA (doit être appelé souvent)
    ArduinoOTA.handle();

    // 5. Libération CPU (CRITIQUE pour watchdog)
    yield();

    // 6. Heartbeat Non-Bloquant (remplace delay)
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Clignotement du heartbeat
        ledState = !ledState;

        // Action visuelle selon la carte
        #ifdef LED_BUILTIN
            digitalWrite(LED_BUILTIN, ledState);
        #endif
    }

    // 7. Rafraîchissement de l'animation OLED (uniquement si mode animé)
    if (currentMillis - lastDisplayUpdate >= displayUpdateInterval) {
        lastDisplayUpdate = currentMillis;
        if (WiFi.status() == WL_CONNECTED && getDisplayMode() == DISPLAY_MODE_ANIMATED) {
            const bool hasMatrix = getMatrix8x8AnimationName() != nullptr;
            updateAnimationVisual(getGarlandAnimationName(), hasMatrix);
        }
    }
}
