#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

/**
 * @file web_interface.h
 * @brief Gestion de l'interface web et des handlers du serveur
 * @version 1.1.0
 * 
 * Module dédié à la gestion des routes HTTP et handlers du serveur web.
 * Contient les callbacks pour les différents endpoints de l'API web.
 */

#include "web_pages.h"
#include "garland_control.h"
#include "display.h"

// Déclaration du serveur web (défini dans main.cpp)
extern WebServer server;

/**
 * @brief Handler pour la page d'accueil (GET /)
 * Génère et envoie le tableau de bord avec toutes les informations système
 */
void handleRoot() {
    // Récupération des informations techniques
    uint32_t chipId = 0;
    for(int i=0; i<17; i=i+8) {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    
    uint32_t flashSize = ESP.getFlashChipSize();
    uint32_t flashSpeed = ESP.getFlashChipSpeed() / 1000000;
    uint32_t heapSize = ESP.getHeapSize();
    uint32_t freeHeap = ESP.getFreeHeap();
    uint32_t psramSize = ESP.getPsramSize();
    uint32_t freePsram = ESP.getFreePsram();
    uint32_t cpuFreq = ESP.getCpuFreqMHz();
    
    // Génération de la page HTML
    String html = generateDashboardPage(
        chipId, flashSize, flashSpeed,
        heapSize, freeHeap,
        psramSize, freePsram,
        cpuFreq
    );
    
    server.send(200, "text/html", html);
    LOG_PRINTLN("Page web servie");
}

/**
 * @brief Handler pour le redémarrage (GET /reboot)
 * Redémarre l'ESP32 après confirmation
 */
void handleReboot() {
    server.send(200, "text/plain", "Redémarrage en cours...");
    LOG_PRINTLN("Redémarrage demandé via web");
    delay(1000);
    ESP.restart();
}

/**
 * @brief Handler pour changer l'animation (GET /animation?id=X)
 */
void handleSetAnimation() {
    if (server.hasArg("id")) {
        int animId = server.arg("id").toInt();
        if (animId >= 0 && animId < ANIM_COUNT) {
            setGarlandAnimation((GarlandAnimation)animId);

            // Mise à jour de l'écran ST7789 après changement
            displayMainScreen(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName());

            server.send(200, "text/plain", "Animation changée");
        } else {
            server.send(400, "text/plain", "ID animation invalide");
        }
    } else {
        server.send(400, "text/plain", "Paramètre manquant");
    }
}

/**
 * @brief Handler pour changer le mode (GET /mode?id=X)
 */
void handleSetMode() {
    if (server.hasArg("id")) {
        int modeId = server.arg("id").toInt();
        if (modeId >= 0 && modeId < MODE_COUNT) {
            setGarlandMode((GarlandMode)modeId);

            // Mise à jour de l'écran ST7789 après changement
            displayMainScreen(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName());

            server.send(200, "text/plain", "Mode changé");
        } else {
            server.send(400, "text/plain", "ID mode invalide");
        }
    } else {
        server.send(400, "text/plain", "Paramètre manquant");
    }
}

/**
 * @brief Handler pour récupérer l'état de la guirlande (GET /status)
 */
void handleStatus() {
    String json = "{";
    json += "\"animation\":\"" + String(getGarlandAnimationName()) + "\",";
    json += "\"animation_id\":" + String((int)getGarlandAnimation()) + ",";
    json += "\"mode\":\"" + String(getGarlandModeName()) + "\",";
    json += "\"mode_id\":" + String((int)getGarlandMode()) + ",";
    json += "\"motion_detected\":" + String(isMotionDetected() ? "true" : "false") + ",";
    json += "\"auto_interval_ms\":" + String(getAutoAnimationIntervalMs()) + ",";
    json += "\"motion_duration_ms\":" + String(getMotionTriggerDurationMs()) + ",";
    json += "\"ip\":\"" + WiFi.localIP().toString() + "\"";
    json += "}";
    server.send(200, "application/json", json);
}

/**
 * @brief Handler pour changer l'intervalle du mode AUTO (GET /auto_interval?ms=X)
 */
void handleSetAutoInterval() {
    if (server.hasArg("ms")) {
        unsigned long val = server.arg("ms").toInt();
        setAutoAnimationIntervalMs(val);
        server.send(200, "text/plain", "Auto interval updated");
    } else {
        server.send(400, "text/plain", "Paramètre manquant");
    }
}

/**
 * @brief Handler pour changer la durée de déclenchement mouvement (GET /motion_duration?ms=X)
 */
void handleSetMotionDuration() {
    if (server.hasArg("ms")) {
        unsigned long val = server.arg("ms").toInt();
        setMotionTriggerDurationMs(val);
        server.send(200, "text/plain", "Motion duration updated");
    } else {
        server.send(400, "text/plain", "Paramètre manquant");
    }
}

/** Sauvegarde manuelle des paramètres en NVS */
void handleSaveSettings() {
    saveGarlandSettings();
    server.send(200, "text/plain", "Paramètres sauvegardés");
}

/** Recharge les paramètres depuis NVS */
void handleLoadSettings() {
    loadGarlandSettings();
    server.send(200, "text/plain", "Paramètres rechargés");
}

/** Efface l'espace NVS de l'application */
void handleEraseSettings() {
    // Efface tout NVS (global). Alternative: ouvrir handle et effacer clés.
    nvs_flash_erase();
    nvs_flash_init();
    server.send(200, "text/plain", "Sauvegarde effacée");
}

/**
 * @brief Handler pour les pages non trouvées (404)
 */
void handleNotFound() {
    server.send(404, "text/plain", "Page non trouvée");
}

/**
 * @brief Initialise les routes du serveur web
 * À appeler dans setup() après la connexion WiFi
 */
void setupWebServer() {
    server.on("/", handleRoot);
    server.on("/reboot", handleReboot);
    server.on("/animation", handleSetAnimation);
    server.on("/mode", handleSetMode);
    server.on("/auto_interval", handleSetAutoInterval);
    server.on("/motion_duration", handleSetMotionDuration);
    server.on("/save", handleSaveSettings);
    server.on("/load", handleLoadSettings);
    server.on("/erase", handleEraseSettings);
    server.on("/status", handleStatus);
    server.onNotFound(handleNotFound);
    server.begin();
    LOG_PRINTLN("Serveur web démarré sur http://" + WiFi.localIP().toString());
}

#endif // WEB_INTERFACE_H
