#ifndef WEB_PAGES_H
#define WEB_PAGES_H

/**
 * @file web_pages.h
 * @brief Génération des pages HTML pour l'interface web
 * @version 0.6.3
 * 
 * Module dédié à la génération du contenu HTML de l'interface web.
 * Contient les fonctions pour construire les différentes cartes et sections.
 */

#include "web_styles.h"
#include "garland_control.h"

/**
 * @brief Génère la page HTML complète du tableau de bord
 * @param chipId Identifiant unique du chip ESP32
 * @param flashSize Taille de la mémoire flash en bytes
 * @param flashSpeed Vitesse de la flash en MHz
 * @param heapSize Taille du heap total en bytes
 * @param freeHeap Heap libre en bytes
 * @param psramSize Taille PSRAM en bytes (0 si non présent)
 * @param freePsram PSRAM libre en bytes
 * @param cpuFreq Fréquence CPU en MHz
 * @return String contenant le HTML complet
 */
String generateDashboardPage(
    uint32_t chipId,
    uint32_t flashSize,
    uint32_t flashSpeed,
    uint32_t heapSize,
    uint32_t freeHeap,
    uint32_t psramSize,
    uint32_t freePsram,
    uint32_t cpuFreq
) {
    String html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='utf-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>" + String(PROJECT_NAME) + "</title>";
    html += "<style>" + String(WEB_STYLES) + "</style>";
    html += "</head><body>";
    html += "<div class='container'>";
    
    // --- HEADER ---
    html += "<div class='header'>";
    html += "<h1>" + String(PROJECT_NAME) + "</h1>";
    html += "<p>Version " + String(PROJECT_VERSION) + "</p>";
    html += "</div>";
    
    html += "<div class='cards-grid'>";
    
    // --- CARTE 1: Guirlande LED (EN PREMIER, PLEINE LARGEUR) ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>🎄 LED Garland</div>";
    html += "<div class='card-item'><span class='card-label'>Animation:</span><span class='card-value'>" + String(getGarlandAnimationName()) + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>Mode:</span><span class='card-value'>" + String(getGarlandModeName()) + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>Motion:</span><span class='card-value'>" + String(isMotionDetected() ? "Detected" : "None") + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>Brightness:</span><span class='card-value'>" + String(getLightLevel()) + " / 4095</span></div>";
    
    // Sélecteur d'animation
    html += "<div style='margin-top:15px;'>";
    html += "<label style='display:block;margin-bottom:5px;font-weight:600;'>Change Animation:</label>";
    html += "<select id='animSelect' style='width:100%;padding:8px;border-radius:8px;border:1px solid #ddd;'>";
    for (int i = 0; i < ANIM_COUNT; i++) {
        html += "<option value='" + String(i) + "'";
        if (i == (int)getGarlandAnimation()) html += " selected";
        html += ">";
        switch(i) {
            case ANIM_OFF: html += "Off"; break;
            case ANIM_FADE_ALTERNATE: html += "Fade Alternate"; break;
            case ANIM_BLINK_ALTERNATE: html += "Blink Alternate"; break;
            case ANIM_PULSE: html += "Pulse"; break;
            case ANIM_BREATHING: html += "Breathing"; break;
            case ANIM_STROBE: html += "⚡ Strobe"; break;
            case ANIM_HEARTBEAT: html += "❤️ Heartbeat"; break;
            case ANIM_WAVE: html += "🌊 Wave"; break;
            case ANIM_SPARKLE: html += "✨ Sparkle"; break;
            case ANIM_METEOR: html += "☄️ Meteor"; break;
            case ANIM_AUTO: html += "Auto Mode"; break;
        }
        html += "</option>";
    }
    html += "</select>";
    html += "<button onclick='changeAnimation()' style='margin-top:10px;width:100%;padding:10px;background:linear-gradient(135deg,#667eea,#764ba2);color:white;border:none;border-radius:8px;cursor:pointer;'>Apply</button>";
    html += "</div>";
    
    // Sélecteur de mode
    html += "<div style='margin-top:15px;'>";
    html += "<label style='display:block;margin-bottom:5px;font-weight:600;'>Change Mode:</label>";
    html += "<select id='modeSelect' style='width:100%;padding:8px;border-radius:8px;border:1px solid #ddd;'>";
    for (int i = 0; i < MODE_COUNT; i++) {
        html += "<option value='" + String(i) + "'";
        if (i == (int)getGarlandMode()) html += " selected";
        html += ">";
        switch(i) {
            case MODE_PERMANENT: html += "Permanent"; break;
            case MODE_MOTION_TRIGGER: html += "Motion Trigger"; break;
        }
        html += "</option>";
    }
    html += "</select>";
    html += "<button onclick='changeMode()' style='margin-top:10px;width:100%;padding:10px;background:linear-gradient(135deg,#f093fb,#f5576c);color:white;border:none;border-radius:8px;cursor:pointer;'>Apply</button>";
    html += "</div>";
    
    // --- CARTE 2: Matériel ---
    html += "<div class='card'>";
    html += "<div class='card-title'>⚡ Hardware</div>";
    html += "<div class='card-item'><span class='card-label'>Board:</span><span class='card-value'>" + String(BOARD_NAME) + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>Chip ID:</span><span class='card-value mono'>0x" + String(chipId, HEX) + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>SDK:</span><span class='card-value'>" + String(ESP.getSdkVersion()) + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>CPU:</span><span class='card-value'>" + String(cpuFreq) + " MHz (2 cores)</span></div>";
    html += "</div>";
    
    // --- CARTE 2: Mémoire Flash ---
    html += "<div class='card'>";
    html += "<div class='card-title'>💾 Flash</div>";
    html += "<div class='card-item'><span class='card-label'>Size:</span><span class='card-value'>" + String(flashSize / (1024 * 1024)) + " MB</span></div>";
    html += "<div class='card-item'><span class='card-label'>Speed:</span><span class='card-value'>" + String(flashSpeed) + " MHz</span></div>";
    html += "<div class='card-item'><span class='card-label'>Mode:</span><span class='card-value'>QIO</span></div>";
    html += "</div>";
    
    // --- CARTE 3: RAM (Heap) ---
    html += "<div class='card'>";
    html += "<div class='card-title'>📊 RAM (Heap)</div>";
    uint32_t heapUsed = heapSize - freeHeap;
    float heapPercent = (float)heapUsed / heapSize * 100;
    html += "<div class='card-item'><span class='card-label'>Total:</span><span class='card-value'>" + String(heapSize / 1024) + " KB</span></div>";
    html += "<div class='card-item'><span class='card-label'>Free:</span><span class='card-value'>" + String(freeHeap / 1024) + " KB</span></div>";
    html += "<div class='progress-container'>";
    html += "<div class='progress-label'><span>Usage</span><span>" + String(heapPercent, 1) + "%</span></div>";
    html += "<div class='progress-bar'><div class='progress-fill' style='width:" + String(heapPercent) + "%;'></div></div>";
    html += "</div></div>";
    
    // --- CARTE 4: PSRAM (si disponible) ---
    if(psramSize > 0) {
        uint32_t psramUsed = psramSize - freePsram;
        float psramPercent = (float)psramUsed / psramSize * 100;
        html += "<div class='card'>";
        html += "<div class='card-title'>🔋 PSRAM</div>";
        html += "<div class='card-item'><span class='card-label'>Total:</span><span class='card-value'>" + String(psramSize / (1024 * 1024)) + " MB</span></div>";
        html += "<div class='card-item'><span class='card-label'>Free:</span><span class='card-value'>" + String(freePsram / 1024) + " KB</span></div>";
        html += "<div class='progress-container'>";
        html += "<div class='progress-label'><span>Usage</span><span>" + String(psramPercent, 1) + "%</span></div>";
        html += "<div class='progress-bar'><div class='progress-fill' style='width:" + String(psramPercent) + "%;'></div></div>";
        html += "</div></div>";
    }
    
    // --- CARTE 5: WiFi ---
    html += "<div class='card'>";
    html += "<div class='card-title'>📶 WiFi Network</div>";
    html += "<div class='card-item'><span class='card-label'>SSID:</span><span class='card-value'>" + WiFi.SSID() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>IP:</span><span class='card-value mono'>" + WiFi.localIP().toString() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>MAC:</span><span class='card-value mono'>" + WiFi.macAddress() + "</span></div>";
    int rssi = WiFi.RSSI();
    int signalPercent = (rssi + 100) * 2;
    signalPercent = (signalPercent > 100) ? 100 : (signalPercent < 0) ? 0 : signalPercent;
    html += "<div class='card-item'><span class='card-label'>Signal:</span><span class='card-value'>" + String(rssi) + " dBm</span></div>";
    html += "<div class='progress-container'>";
    html += "<div class='progress-label'><span>Signal Strength</span><span>" + String(signalPercent) + "%</span></div>";
    html += "<div class='progress-bar'><div class='progress-fill' style='width:" + String(signalPercent) + "%;'></div></div>";
    html += "</div></div>";
    
    // --- CARTE 6: Système ---
    html += "<div class='card'>";
    html += "<div class='card-title'>⏱️ System</div>";
    unsigned long uptime = millis() / 1000;
    unsigned long hours = uptime / 3600;
    unsigned long minutes = (uptime % 3600) / 60;
    unsigned long seconds = uptime % 60;
    html += "<div class='card-item'><span class='card-label'>Uptime:</span><span class='card-value'>" + String(hours) + "h " + String(minutes) + "m " + String(seconds) + "s</span></div>";
    html += "<div class='card-item'><span class='card-label'>Temperature:</span><span class='card-value'>" + String(temperatureRead(), 1) + " °C</span></div>";
    html += "</div>";
    
    html += "</div>";  // Fin de la carte Système
    
    // --- CARTE 7: Réseau Détaillé ---
    html += "<div class='card'>";
    html += "<div class='card-title'>🔗 Network Details</div>";
    html += "<div class='card-item'><span class='card-label'>Subnet Mask:</span><span class='card-value mono'>" + WiFi.subnetMask().toString() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>Gateway:</span><span class='card-value mono'>" + WiFi.gatewayIP().toString() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>DNS:</span><span class='card-value mono'>" + WiFi.dnsIP().toString() + "</span></div>";
    html += "</div>";
    
    // --- BOUTONS D'ACTION ---
    html += "<div class='actions'>";
    html += "<button onclick='location.reload()'>🔄 Refresh</button>";
    html += "<button class='danger' onclick='if(confirm(\"Are you sure you want to reboot?\")) fetch(\"/reboot\")'>🔴 Reboot</button>";
    html += "</div>";
    
    // --- SCRIPT JAVASCRIPT ---
    html += "<script>";
    html += "function changeAnimation() {";
    html += "  var id = document.getElementById('animSelect').value;";
    html += "  fetch('/animation?id=' + id).then(() => setTimeout(() => location.reload(), 500));";
    html += "}";
    html += "function changeMode() {";
    html += "  var id = document.getElementById('modeSelect').value;";
    html += "  fetch('/mode?id=' + id).then(() => setTimeout(() => location.reload(), 500));";
    html += "}";
    html += "</script>";
    
    html += "</div></body></html>";
    
    return html;
}

#endif // WEB_PAGES_H
