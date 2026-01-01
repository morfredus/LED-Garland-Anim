#ifndef WEB_PAGES_H
#define WEB_PAGES_H

/**
 * @file web_pages.h
 * @brief Génération des pages HTML pour l'interface web
 * @version 1.8.0
 *
 * Module dédié à la génération du contenu HTML de l'interface web.
 * Contient les fonctions pour construire les différentes cartes et sections.
 */

#include "web_styles.h"
#include "garland_control.h"
#include "matrix8x8_control.h"

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

    // Zone de message inline pour animation/mode
    html += "<div id='param-message' style='display:none;margin-bottom:12px;padding:10px;border-radius:8px;background:#d4edda;color:#155724;border:1px solid #c3e6cb;'></div>";

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

    // Zone de message de confirmation inline
    html += "<div id='save-message' style='display:none;margin-top:12px;padding:10px;border-radius:8px;background:#d4edda;color:#155724;border:1px solid #c3e6cb;'></div>";

    // Actions de persistance
    html += "<div class='actions'>";
    html += "<button onclick=\"saveSettings()\">💾 Sauvegarder</button>";
    html += "<button onclick=\"loadSettings()\">🔄 Restaurer</button>";
    html += "<button class='danger' onclick=\"eraseSettings()\">🗑️ Effacer</button>";
    html += "</div>";
    html += "</div>"; // card

    // --- Carte Matrice 8x8 NeoPixel ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>✨ Matrice 8x8 NeoPixel <span style='float:right;font-size:0.9em;color:#7b1fa2;'>En cours: <span id='current-matrix' class='mono'>" + String(getMatrix8x8AnimationName()) + "</span></span></div>";

    // Zone de message inline pour matrix
    html += "<div id='matrix-message' style='display:none;margin-bottom:12px;padding:10px;border-radius:8px;background:#d4edda;color:#155724;border:1px solid #c3e6cb;'></div>";

    // Animation selection
    html += "<div class='card-item'><span class='card-label'>Animation:</span>";
    html += "<select id='matrixAnimSelect' style='width:55%;padding:8px;border-radius:8px;border:1px solid #ddd;'>";
    for (int i = 0; i < MATRIX_ANIM_COUNT; i++) {
        html += "<option value='" + String(i) + "'";
        if (i == (int)getMatrix8x8Animation()) html += " selected";
        html += ">" + String(getMatrix8x8AnimationNameById(i)) + "</option>";
    }
    html += "</select>";
    html += "<button onclick='changeMatrixAnimation()' style='margin-left:10px;padding:8px 12px;background:#7b1fa2;color:white;border:none;border-radius:8px;cursor:pointer;'>Appliquer</button>";
    html += "</div>";

    // Brightness control
    html += "<div class='card-item'><span class='card-label'>Luminosité:</span>";
    html += "<input type='range' id='matrixBrightness' min='0' max='255' value='" + String(getMatrix8x8Brightness()) + "' style='width:55%;' oninput='updateBrightnessValue(this.value)'> ";
    html += "<span id='brightnessValue' style='display:inline-block;width:50px;'>" + String(getMatrix8x8Brightness()) + "</span> ";
    html += "<button class='apply' onclick='applyMatrixBrightness()'>Valider</button>";
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
    html += "<div style='position:relative;'>";

    // Boutons
    html += "<div class='actions'>";
    html += "<button onclick='location.reload()'>🔄 Actualiser</button>";
    html += "<button onclick='window.location.href=\"/update\"' style='background:linear-gradient(135deg,#667eea 0%,#764ba2 100%)'>⬆️ Mise à jour OTA</button>";
    html += "<button id='reboot-btn' class='danger' onclick='rebootDevice()'>🔴 Redémarrer</button>";
    html += "</div>";

    // Zone de message de confirmation pour le reboot - positionnée à droite en absolu
    html += "<div id='reboot-message' style='display:none;position:absolute;top:0;right:0;padding:10px 15px;border-radius:8px;background:#fff3cd;color:#856404;border:1px solid #ffc107;max-width:350px;box-shadow:0 2px 8px rgba(0,0,0,0.1);'></div>";

    html += "</div>"; // fin du container position relative
    
    // --- SCRIPT JAVASCRIPT ---
    html += "<script>";

    // Fonction pour afficher les messages de paramètres
    html += "function showParamMessage(msg) { var el = document.getElementById('param-message'); el.textContent = msg; el.style.display = 'block'; setTimeout(() => { el.style.display = 'none'; }, 3000); }";

    html += "function changeAnimation() {";
    html += "  var id = document.getElementById('animSelect').value;";
    html += "  var select = document.getElementById('animSelect');";
    html += "  var animName = select.options[select.selectedIndex].text;";
    html += "  fetch('/animation?id=' + id).then(() => { showParamMessage('✓ Animation changée : ' + animName); setTimeout(() => location.reload(), 1000); });";
    html += "}";
    html += "function changeMode() {";
    html += "  var id = document.getElementById('modeSelect').value;";
    html += "  var select = document.getElementById('modeSelect');";
    html += "  var modeName = select.options[select.selectedIndex].text;";
    html += "  fetch('/mode?id=' + id).then(() => { showParamMessage('✓ Mode changé : ' + modeName); setTimeout(() => location.reload(), 1000); });";
    html += "}";
    html += "function applyAutoInterval() { var s = document.getElementById('auto-interval-seconds').value; var ms = Math.round(s*1000); fetch('/auto_interval?ms=' + ms); }";
    html += "function applyMotionDuration() { var s = document.getElementById('motion-duration-seconds').value; var ms = Math.round(s*1000); fetch('/motion_duration?ms=' + ms); }";

    // Fonctions pour la matrice 8x8
    html += "function showMatrixMessage(msg) { var el = document.getElementById('matrix-message'); el.textContent = msg; el.style.display = 'block'; setTimeout(() => { el.style.display = 'none'; }, 3000); }";
    html += "function changeMatrixAnimation() {";
    html += "  var id = document.getElementById('matrixAnimSelect').value;";
    html += "  var select = document.getElementById('matrixAnimSelect');";
    html += "  var animName = select.options[select.selectedIndex].text;";
    html += "  fetch('/matrix_animation?id=' + id).then(() => { showMatrixMessage('✓ Animation changée : ' + animName); setTimeout(() => location.reload(), 1000); });";
    html += "}";
    html += "function updateBrightnessValue(val) { document.getElementById('brightnessValue').textContent = val; }";
    html += "function applyMatrixBrightness() {";
    html += "  var val = document.getElementById('matrixBrightness').value;";
    html += "  fetch('/matrix_brightness?value=' + val).then(() => showMatrixMessage('✓ Luminosité changée : ' + val));";
    html += "}";

    // Fonctions pour save/load/erase avec messages inline
    html += "function showMessage(msg) { var el = document.getElementById('save-message'); el.textContent = msg; el.style.display = 'block'; setTimeout(() => { el.style.display = 'none'; }, 3000); }";
    html += "function saveSettings() { fetch('/save').then(() => showMessage('✓ Sauvegarde effectuée.')); }";
    html += "function loadSettings() { fetch('/load').then(() => { showMessage('✓ Paramètres restaurés.'); setTimeout(() => location.reload(), 1000); }); }";
    html += "function eraseSettings() { fetch('/erase').then(() => showMessage('✓ Sauvegarde effacée.')); }";

    // Double validation pour le reboot
    html += "var rebootConfirmed = false;";
    html += "function rebootDevice() {";
    html += "  if (!rebootConfirmed) {";
    html += "    rebootConfirmed = true;";
    html += "    var msg = document.getElementById('reboot-message');";
    html += "    msg.textContent = '⚠️ Cliquez à nouveau sur Redémarrer pour confirmer';";
    html += "    msg.style.display = 'block';";
    html += "    document.getElementById('reboot-btn').style.background = 'linear-gradient(135deg, #f5576c 0%, #c0392b 100%)';";
    html += "    setTimeout(() => { rebootConfirmed = false; msg.style.display = 'none'; document.getElementById('reboot-btn').style.background = ''; }, 5000);";
    html += "  } else {";
    html += "    fetch('/reboot');";
    html += "    var msg = document.getElementById('reboot-message');";
    html += "    msg.textContent = '🔄 Redémarrage en cours...';";
    html += "    msg.style.background = '#d4edda';";
    html += "    msg.style.color = '#155724';";
    html += "    msg.style.borderColor = '#c3e6cb';";
    html += "  }";
    html += "}";

    // Mise à jour périodique du statut pour afficher l'animation en cours
    html += "function refreshStatus(){ fetch('/status').then(r=>r.json()).then(j=>{ ";
    html += "var el=document.getElementById('current-anim'); if(el){ el.textContent=j.animation; } ";
    html += "var mel=document.getElementById('current-matrix'); if(mel){ mel.textContent=j.matrix_animation; } ";
    html += "}); }";
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
    html += "<button type='button' id='uploadBtn' class='upload-btn' onclick='handleUpload()'>🚀 Lancer la mise à jour</button>";
    html += "</form>";

    // Message de confirmation pour double-clic OTA
    html += "<div id='ota-confirm-message' style='display:none;margin-top:15px;padding:12px;border-radius:8px;background:#fff3cd;color:#856404;border:1px solid #ffc107;text-align:center;'></div>";

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

    // Validation et upload avec double confirmation
    html += "var uploadConfirmed = false;";
    html += "function handleUpload() {";
    html += "  if (fileInput.files.length === 0) {";
    html += "    statusMessage.className = 'status-message status-error';";
    html += "    statusMessage.textContent = '❌ Veuillez sélectionner un fichier .bin';";
    html += "    statusMessage.style.display = 'block';";
    html += "    return;";
    html += "  }";
    html += "  const file = fileInput.files[0];";
    html += "  if (!file.name.endsWith('.bin')) {";
    html += "    statusMessage.className = 'status-message status-error';";
    html += "    statusMessage.textContent = '❌ Le fichier doit avoir l\\'extension .bin';";
    html += "    statusMessage.style.display = 'block';";
    html += "    return;";
    html += "  }";
    html += "  if (!uploadConfirmed) {";
    html += "    uploadConfirmed = true;";
    html += "    uploadBtn.textContent = '⚠️ Cliquer à nouveau pour confirmer la mise à jour';";
    html += "    uploadBtn.style.background = 'linear-gradient(135deg, #f5576c 0%, #c0392b 100%)';";
    html += "    var msg = document.getElementById('ota-confirm-message');";
    html += "    msg.textContent = '⚠️ Attention : L\\'appareil redémarrera automatiquement après la mise à jour';";
    html += "    msg.style.display = 'block';";
    html += "    setTimeout(() => { uploadConfirmed = false; uploadBtn.textContent = '🚀 Lancer la mise à jour'; uploadBtn.style.background = ''; msg.style.display = 'none'; }, 5000);";
    html += "    return;";
    html += "  }";
    html += "  startUpload(file);";
    html += "}";
    html += "function startUpload(file) {";
    html += "  uploadBtn.disabled = true;";
    html += "  fileInput.disabled = true;";
    html += "  progressContainer.style.display = 'block';";
    html += "  statusMessage.style.display = 'none';";
    html += "  document.getElementById('ota-confirm-message').style.display = 'none';";

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
    html += "}";
    html += "</script>";

    html += "</div></body></html>";

    return html;
}

#endif // WEB_PAGES_H
