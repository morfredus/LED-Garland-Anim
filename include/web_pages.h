#ifndef WEB_PAGES_H
#define WEB_PAGES_H

/**
 * @file web_pages.h
 * @brief Génération des pages HTML pour l'interface web
 * @version 1.1.0
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
    html += "<button onclick='window.location.href=\"/update\"' style='background:linear-gradient(135deg,#667eea 0%,#764ba2 100%)'>⬆️ Mise à jour OTA</button>";
    html += "<button class='danger' onclick='if(confirm(\"Redémarrer l'ESP32 ?\")) fetch(\"/reboot\")'>🔴 Redémarrer</button>";
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

/**
 * @brief Génère la page HTML pour la mise à jour OTA du firmware
 * @return String contenant le HTML complet de la page OTA
 */
String generateOTAPage() {
    String html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='utf-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Mise à jour OTA - " + String(PROJECT_NAME) + "</title>";
    html += "<style>" + String(WEB_STYLES);

    // Styles additionnels pour la page OTA
    html += ".ota-container { max-width: 600px; margin: 0 auto; padding: 20px; }";
    html += ".file-input-wrapper { position: relative; margin: 20px 0; }";
    html += ".file-input { display: none; }";
    html += ".file-label { display: inline-block; padding: 12px 24px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; border-radius: 8px; cursor: pointer; font-weight: bold; transition: transform 0.2s; }";
    html += ".file-label:hover { transform: translateY(-2px); box-shadow: 0 4px 12px rgba(102, 126, 234, 0.4); }";
    html += ".file-name { margin-top: 10px; padding: 10px; background: #f5f5f5; border-radius: 8px; font-family: monospace; color: #333; min-height: 20px; }";
    html += ".upload-btn { width: 100%; padding: 14px; background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%); color: white; border: none; border-radius: 8px; font-size: 16px; font-weight: bold; cursor: pointer; margin-top: 20px; transition: transform 0.2s; }";
    html += ".upload-btn:hover { transform: translateY(-2px); box-shadow: 0 4px 12px rgba(240, 147, 251, 0.4); }";
    html += ".upload-btn:disabled { background: #ccc; cursor: not-allowed; transform: none; }";
    html += ".progress-container { display: none; margin-top: 20px; }";
    html += ".progress-bar { width: 100%; height: 30px; background: #f0f0f0; border-radius: 15px; overflow: hidden; }";
    html += ".progress-fill { height: 100%; background: linear-gradient(90deg, #4facfe 0%, #00f2fe 100%); transition: width 0.3s; }";
    html += ".progress-text { text-align: center; margin-top: 10px; font-weight: bold; color: #333; }";
    html += ".status-message { margin-top: 20px; padding: 15px; border-radius: 8px; display: none; }";
    html += ".status-success { background: #d4edda; color: #155724; border: 1px solid #c3e6cb; }";
    html += ".status-error { background: #f8d7da; color: #721c24; border: 1px solid #f5c6cb; }";
    html += ".warning-box { background: #fff3cd; border-left: 4px solid #ffc107; padding: 15px; margin: 20px 0; border-radius: 4px; }";
    html += ".info-box { background: #d1ecf1; border-left: 4px solid #17a2b8; padding: 15px; margin: 20px 0; border-radius: 4px; }";
    html += ".back-btn { display: inline-block; margin-top: 20px; padding: 10px 20px; background: #6c757d; color: white; text-decoration: none; border-radius: 8px; }";
    html += ".back-btn:hover { background: #5a6268; }";
    html += "</style>";
    html += "</head><body>";
    html += "<div class='container'>";

    // Header
    html += "<div class='header'>";
    html += "<h1>🔄 Mise à jour OTA</h1>";
    html += "<p>" + String(PROJECT_NAME) + " v" + String(PROJECT_VERSION) + "</p>";
    html += "</div>";

    html += "<div class='ota-container'>";

    // Carte d'information
    html += "<div class='card'>";
    html += "<div class='card-title'>📦 Téléverser un nouveau firmware</div>";

    // Zone d'avertissement
    html += "<div class='warning-box'>";
    html += "⚠️ <strong>Attention :</strong> Ne débranchez pas l'appareil pendant la mise à jour. ";
    html += "L'interruption du processus pourrait rendre l'appareil inutilisable.";
    html += "</div>";

    // Zone d'information
    html += "<div class='info-box'>";
    html += "ℹ️ <strong>Fichier requis :</strong> firmware.bin (compilé avec PlatformIO)<br>";
    html += "📍 <strong>Emplacement :</strong> <code>.pio/build/esp32devkitc/firmware.bin</code>";
    html += "</div>";

    // Formulaire d'upload
    html += "<form id='uploadForm' enctype='multipart/form-data'>";
    html += "<div class='file-input-wrapper'>";
    html += "<input type='file' id='fileInput' name='update' accept='.bin' class='file-input' required>";
    html += "<label for='fileInput' class='file-label'>📁 Sélectionner un fichier .bin</label>";
    html += "<div class='file-name' id='fileName'>Aucun fichier sélectionné</div>";
    html += "</div>";
    html += "<button type='submit' id='uploadBtn' class='upload-btn'>🚀 Lancer la mise à jour</button>";
    html += "</form>";

    // Barre de progression
    html += "<div class='progress-container' id='progressContainer'>";
    html += "<div class='progress-bar'><div class='progress-fill' id='progressFill'></div></div>";
    html += "<div class='progress-text' id='progressText'>0%</div>";
    html += "</div>";

    // Message de statut
    html += "<div class='status-message' id='statusMessage'></div>";

    html += "</div>"; // card

    // Bouton retour
    html += "<a href='/' class='back-btn'>← Retour au tableau de bord</a>";

    html += "</div>"; // ota-container

    // JavaScript
    html += "<script>";
    html += "const fileInput = document.getElementById('fileInput');";
    html += "const fileName = document.getElementById('fileName');";
    html += "const uploadForm = document.getElementById('uploadForm');";
    html += "const uploadBtn = document.getElementById('uploadBtn');";
    html += "const progressContainer = document.getElementById('progressContainer');";
    html += "const progressFill = document.getElementById('progressFill');";
    html += "const progressText = document.getElementById('progressText');";
    html += "const statusMessage = document.getElementById('statusMessage');";

    // Afficher le nom du fichier sélectionné
    html += "fileInput.addEventListener('change', function() {";
    html += "  if (this.files.length > 0) {";
    html += "    const file = this.files[0];";
    html += "    fileName.textContent = file.name + ' (' + (file.size / 1024).toFixed(2) + ' KB)';";
    html += "  } else {";
    html += "    fileName.textContent = 'Aucun fichier sélectionné';";
    html += "  }";
    html += "});";

    // Gérer l'upload
    html += "uploadForm.addEventListener('submit', function(e) {";
    html += "  e.preventDefault();";
    html += "  if (fileInput.files.length === 0) {";
    html += "    alert('Veuillez sélectionner un fichier .bin');";
    html += "    return;";
    html += "  }";
    html += "  const file = fileInput.files[0];";
    html += "  if (!file.name.endsWith('.bin')) {";
    html += "    alert('Le fichier doit avoir l\\'extension .bin');";
    html += "    return;";
    html += "  }";
    html += "  if (!confirm('Êtes-vous sûr de vouloir mettre à jour le firmware ?\\nL\\'appareil redémarrera automatiquement.')) {";
    html += "    return;";
    html += "  }";
    html += "  uploadBtn.disabled = true;";
    html += "  fileInput.disabled = true;";
    html += "  progressContainer.style.display = 'block';";
    html += "  statusMessage.style.display = 'none';";

    html += "  const xhr = new XMLHttpRequest();";
    html += "  xhr.upload.addEventListener('progress', function(e) {";
    html += "    if (e.lengthComputable) {";
    html += "      const percent = Math.round((e.loaded / e.total) * 100);";
    html += "      progressFill.style.width = percent + '%';";
    html += "      progressText.textContent = percent + '%';";
    html += "    }";
    html += "  });";

    html += "  xhr.addEventListener('load', function() {";
    html += "    if (xhr.status === 200) {";
    html += "      statusMessage.className = 'status-message status-success';";
    html += "      statusMessage.textContent = '✅ Mise à jour réussie ! Redémarrage en cours...';";
    html += "      statusMessage.style.display = 'block';";
    html += "      setTimeout(function() {";
    html += "        window.location.href = '/';";
    html += "      }, 5000);";
    html += "    } else {";
    html += "      statusMessage.className = 'status-message status-error';";
    html += "      statusMessage.textContent = '❌ Erreur : ' + xhr.responseText;";
    html += "      statusMessage.style.display = 'block';";
    html += "      uploadBtn.disabled = false;";
    html += "      fileInput.disabled = false;";
    html += "    }";
    html += "  });";

    html += "  xhr.addEventListener('error', function() {";
    html += "    statusMessage.className = 'status-message status-error';";
    html += "    statusMessage.textContent = '❌ Erreur de connexion lors de l\\'upload';";
    html += "    statusMessage.style.display = 'block';";
    html += "    uploadBtn.disabled = false;";
    html += "    fileInput.disabled = false;";
    html += "  });";

    html += "  const formData = new FormData();";
    html += "  formData.append('update', file);";
    html += "  xhr.open('POST', '/update');";
    html += "  xhr.send(formData);";
    html += "});";
    html += "</script>";

    html += "</div></body></html>";

    return html;
}

#endif // WEB_PAGES_H
