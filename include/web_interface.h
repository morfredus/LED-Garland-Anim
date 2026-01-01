#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

/**
 * @file web_interface.h
 * @brief Gestion de l'interface web et des handlers du serveur
 * @version 1.10.0
 *
 * Module dédié à la gestion des routes HTTP et handlers du serveur web.
 * Contient les callbacks pour les différents endpoints de l'API web.
 */

#include <Update.h>
#include "web_pages.h"
#include "garland_control.h"
#include "matrix8x8_control.h"
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
    json += "\"matrix_animation\":\"" + String(getMatrix8x8AnimationName()) + "\",";
    json += "\"matrix_animation_id\":" + String((int)getMatrix8x8Animation()) + ",";
    json += "\"matrix_brightness\":" + String(getMatrix8x8Brightness()) + ",";
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
    saveMatrix8x8Settings();
    server.send(200, "text/plain", "Paramètres sauvegardés (guirlande + matrice)");
}

/** Recharge les paramètres depuis NVS */
void handleLoadSettings() {
    loadGarlandSettings();
    loadMatrix8x8Settings();
    server.send(200, "text/plain", "Paramètres rechargés (guirlande + matrice)");
}

/** Efface l'espace NVS de l'application */
void handleEraseSettings() {
    // Efface tout NVS (global). Alternative: ouvrir handle et effacer clés.
    nvs_flash_erase();
    nvs_flash_init();
    server.send(200, "text/plain", "Sauvegarde effacée");
}

/**
 * @brief Handler pour changer l'animation de la matrice 8x8 (GET /matrix_animation?id=X)
 */
/**
 * @note FIX #9: Added debug logging to trace API calls
 */
void handleSetMatrix8x8Animation() {
    LOG_PRINTLN("[WEB] handleSetMatrix8x8Animation() called");
    if (server.hasArg("id")) {
        int animId = server.arg("id").toInt();
        LOG_PRINTF("[WEB] Animation ID requested: %d\n", animId);
        if (animId >= 0 && animId < MATRIX_ANIM_COUNT) {
            setMatrix8x8Animation((Matrix8x8Animation)animId);
            server.send(200, "text/plain", "Matrix animation changed");
            LOG_PRINTLN("[WEB] Response sent: 200 OK");
        } else {
            LOG_PRINTF("[WEB] ERROR: Invalid animation ID: %d (max: %d)\n", animId, MATRIX_ANIM_COUNT - 1);
            server.send(400, "text/plain", "Invalid animation ID");
        }
    } else {
        LOG_PRINTLN("[WEB] ERROR: Missing 'id' parameter");
        server.send(400, "text/plain", "Missing parameter");
    }
}

/**
 * @brief Handler pour changer la luminosité de la matrice 8x8 (GET /matrix_brightness?value=X)
 * @note FIX #10: Added debug logging to trace API calls
 */
void handleSetMatrix8x8Brightness() {
    LOG_PRINTLN("[WEB] handleSetMatrix8x8Brightness() called");
    if (server.hasArg("value")) {
        int brightness = server.arg("value").toInt();
        LOG_PRINTF("[WEB] Brightness value requested: %d\n", brightness);
        if (brightness >= 0 && brightness <= 255) {
            setMatrix8x8Brightness((uint8_t)brightness);
            server.send(200, "text/plain", "Matrix brightness changed");
            LOG_PRINTLN("[WEB] Response sent: 200 OK");
        } else {
            LOG_PRINTF("[WEB] ERROR: Brightness out of range: %d\n", brightness);
            server.send(400, "text/plain", "Brightness out of range (0-255)");
        }
    } else {
        LOG_PRINTLN("[WEB] ERROR: Missing 'value' parameter");
        server.send(400, "text/plain", "Missing parameter");
    }
}

/**
 * @brief Handler pour la page de mise à jour OTA (GET /update)
 * Affiche la page d'upload du firmware
 */
void handleOTAPage() {
    String html = generateOTAPage();
    server.send(200, "text/html", html);
}

/**
 * @brief Handler pour l'upload du firmware OTA (POST /update)
 * Gère le téléversement du fichier .bin et la mise à jour du firmware
 */
void handleOTAUpload() {
    HTTPUpload& upload = server.upload();

    if (upload.status == UPLOAD_FILE_START) {
        LOG_PRINTF("[OTA] Update Start: %s\n", upload.filename.c_str());

        // Affichage sur l'écran ST7789
        #ifdef HAS_ST7789
            display.fillScreen(COLOR_BLACK);
            display.setTextSize(2);
            display.setTextColor(COLOR_CYAN);
            display.setCursor(10, 60);
            display.println("MISE A JOUR");
            display.setCursor(10, 90);
            display.println("OTA...");
        #endif

        // Démarrer la mise à jour (taille 0 = utiliser tout l'espace disponible)
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
            LOG_PRINTLN("[OTA] Error: Not enough space");
            Update.printError(Serial);
        }
    }
    else if (upload.status == UPLOAD_FILE_WRITE) {
        // Écrire les données du firmware
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
            LOG_PRINTLN("[OTA] Error: Write failed");
            Update.printError(Serial);
        } else {
            // Affichage de la progression
            size_t progress = Update.progress();
            size_t total = Update.size();
            if (total > 0) {
                int percent = (progress * 100) / total;
                LOG_PRINTF("[OTA] Progress: %d%%\n", percent);

                #ifdef HAS_ST7789
                    // Barre de progression
                    int barWidth = 115;
                    int barX = 10;
                    int barY = 120;
                    int barHeight = 20;
                    int fillWidth = (barWidth * percent) / 100;

                    display.fillRect(barX, barY, barWidth, barHeight, COLOR_BLACK);
                    display.drawRect(barX, barY, barWidth, barHeight, COLOR_WHITE);
                    display.fillRect(barX + 2, barY + 2, fillWidth - 4, barHeight - 4, COLOR_GREEN);

                    display.fillRect(10, 150, 115, 30, COLOR_BLACK);
                    display.setCursor(40, 155);
                    display.setTextSize(3);
                    display.setTextColor(COLOR_YELLOW);
                    display.printf("%d%%", percent);
                #endif
            }
        }
    }
    else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) {
            LOG_PRINTF("[OTA] Update Success: %u bytes\n", upload.totalSize);

            #ifdef HAS_ST7789
                display.fillScreen(COLOR_BLACK);
                display.setTextSize(2);
                display.setTextColor(COLOR_GREEN);
                display.setCursor(10, 100);
                display.println("REUSSI!");
                display.setCursor(10, 130);
                display.println("Redemarrage");
            #endif
        } else {
            LOG_PRINTLN("[OTA] Update Failed");
            Update.printError(Serial);

            #ifdef HAS_ST7789
                display.fillScreen(COLOR_BLACK);
                display.setTextSize(2);
                display.setTextColor(COLOR_RED);
                display.setCursor(10, 100);
                display.println("ECHEC!");
            #endif
        }
    }
}

/**
 * @brief Handler appelé après la fin de l'upload OTA
 * Envoie la réponse finale et redémarre l'ESP32
 */
void handleOTAUploadComplete() {
    if (Update.hasError()) {
        String error = "Update Failed: ";
        error += Update.errorString();
        server.send(500, "text/plain", error);
        LOG_PRINTF("[OTA] Error: %s\n", error.c_str());
    } else {
        server.send(200, "text/plain", "Update Success! Rebooting...");
        LOG_PRINTLN("[OTA] Success! Rebooting...");
        delay(1000);
        ESP.restart();
    }
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

    // Routes pour la matrice 8x8
    server.on("/matrix_animation", handleSetMatrix8x8Animation);
    server.on("/matrix_brightness", handleSetMatrix8x8Brightness);

    // Routes OTA
    server.on("/update", HTTP_GET, handleOTAPage);
    server.on("/update", HTTP_POST, handleOTAUploadComplete, handleOTAUpload);

    server.onNotFound(handleNotFound);
    server.begin();
    LOG_PRINTLN("Serveur web démarré sur http://" + WiFi.localIP().toString());
}

#endif // WEB_INTERFACE_H
