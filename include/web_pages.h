#ifndef WEB_PAGES_H
#define WEB_PAGES_H

/**
 * @file web_pages.h
 * @brief Génération des pages HTML pour l'interface web
 * @version 0.8.0
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
    html += "<meta charset=\"utf-8\">";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<title>" + String(PROJECT_NAME) + "</title>";
    html += "<link rel=\"icon\" href=\"data:image/x-icon;,\">"; // favicon vide pour éviter 404
    html += "<style>" + String(WEB_STYLES) + "</style>";
    html += "</head><body>";
    html += "<div class='container'>";
    
    // --- HEADER ---
    html += "<div class='header'>";
    html += "<h1>" + String(PROJECT_NAME) + "</h1>";
    html += "<p>Version " + String(PROJECT_VERSION) + "</p>";
    html += "</div>";
    
    html += "<div class='cards-grid'>";

    // --- Carte unique: Paramètres Guirlande ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>🎄 Paramètres Guirlande <span style='float:right;font-size:0.9em;color:#1b5e20;'>En cours: <span id='current-anim' class='mono'>" + String(getGarlandAnimationName()) + "</span></span></div>";
    // Animation
    html += "<div class='card-item'><span class='card-label'>Animation:</span>";
    html += "<select id='animSelect' style='width:55%;padding:8px;border-radius:8px;border:1px solid #ddd;'>";
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
            case ANIM_STROBE: html += "Strobe"; break;
            case ANIM_HEARTBEAT: html += "Heartbeat"; break;
            case ANIM_WAVE: html += "Wave"; break;
            case ANIM_SPARKLE: html += "Sparkle"; break;
            case ANIM_METEOR: html += "Meteor"; break;
            case ANIM_AUTO: html += "Auto"; break;
        }
        html += "</option>";
    }
    html += "</select>";
    html += "<button onclick='changeAnimation()' style='margin-left:10px;padding:8px 12px;background:#667eea;color:white;border:none;border-radius:8px;cursor:pointer;'>Appliquer</button>";
    html += "</div>";

    // Mode
    html += "<div class='card-item'><span class='card-label'>Mode:</span>";
    html += "<select id='modeSelect' style='width:55%;padding:8px;border-radius:8px;border:1px solid #ddd;'>";
    for (int i = 0; i < MODE_COUNT; i++) {
        html += "<option value='" + String(i) + "'";
        if (i == (int)getGarlandMode()) html += " selected";
        html += ">";
        switch(i) {
            case MODE_PERMANENT: html += "Permanent"; break;
            case MODE_MOTION_TRIGGER: html += "Détection"; break;
        }
        html += "</option>";
    }
    html += "</select>";
    html += "<button onclick='changeMode()' style='margin-left:10px;padding:8px 12px;background:#f093fb;color:white;border:none;border-radius:8px;cursor:pointer;'>Appliquer</button>";
    html += "</div>";

    // Durées (saisies en secondes avec bouton de validation)
    html += "<div class='card-item'><span class='card-label'>Durée d'une animation (mode Auto) :</span>";
    html += "<input type='number' id='auto-interval-seconds' min='5' max='300' step='5' value='" + String(getAutoAnimationIntervalMs() / 1000) + "'> secondes ";
    html += "<button class='apply' onclick=\"applyAutoInterval()\">Valider</button></div>";
    html += "<div class='card-item'><span class='card-label'>Durée d'allumage après détection :</span>";
    html += "<input type='number' id='motion-duration-seconds' min='5' max='600' step='5' value='" + String(getMotionTriggerDurationMs() / 1000) + "'> secondes ";
    html += "<button class='apply' onclick=\"applyMotionDuration()\">Valider</button></div>";
    
    // Note explicative
    html += "<div style='margin-top:12px;padding:10px;background:#fffde7;border-left:4px solid #fbc02d;font-size:0.9em;color:#555;'>";
    html += "💡 <strong>Mode Détection + Auto :</strong> Les animations cyclent toutes les <strong>" + String(getAutoAnimationIntervalMs() / 1000) + "s</strong> ";
    html += "pendant la durée d'allumage (<strong>" + String(getMotionTriggerDurationMs() / 1000) + "s</strong>). ";
    html += "Ex: 30s/animation × 60s détection = 2 animations affichées.";
    html += "</div>";

    // Actions de persistance
    html += "<div class='actions'>";
    html += "<button onclick=\"fetch('/save')\">💾 Sauvegarder</button>";
    html += "<button onclick=\"fetch('/load').then(()=>location.reload())\">🔄 Restaurer</button>";
    html += "<button class='danger' onclick=\"if(confirm('Effacer la sauvegarde ?')) fetch('/erase')\">🗑️ Effacer</button>";
    html += "</div>";
    html += "</div>"; // card
    
    // --- Carte WiFi minimaliste ---
    html += "<div class='card'>";
    html += "<div class='card-title'>📶 Réseau WiFi</div>";
    html += "<div class='card-item'><span class='card-label'>SSID:</span><span class='card-value'>" + WiFi.SSID() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>IP:</span><span class='card-value mono'>" + WiFi.localIP().toString() + "</span></div>";
    html += "</div>";
    
    // Fin des cartes
    
    
    // --- BOUTONS D'ACTION ---
    html += "<div class='actions'>";
    html += "<button onclick='location.reload()'>🔄 Actualiser</button>";
    html += "<button class='danger' onclick=\"if(confirm('Redémarrer l\\'ESP32 ?')){fetch('/reboot').then(function(){setTimeout(function(){location.reload();},2000);});}\">🔴 Redémarrer</button>";
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
    html += "function applyAutoInterval() { var s = document.getElementById('auto-interval-seconds').value; var ms = Math.round(s*1000); fetch('/auto_interval?ms=' + ms); }";
    html += "function applyMotionDuration() { var s = document.getElementById('motion-duration-seconds').value; var ms = Math.round(s*1000); fetch('/motion_duration?ms=' + ms); }";
    // Mise à jour périodique du statut pour afficher l'animation en cours
    html += "function refreshStatus(){ fetch('/status').then(r=>r.json()).then(j=>{ var el=document.getElementById('current-anim'); if(el){ el.textContent=j.animation; } }); }";
    html += "setInterval(refreshStatus, 2000);";
    html += "document.addEventListener('DOMContentLoaded', refreshStatus);";
    html += "</script>";
    
    html += "</div></body></html>";
    
    return html;
}

#endif // WEB_PAGES_H
