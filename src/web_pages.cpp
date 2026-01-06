#include <WiFi.h>
#include <Arduino.h>
#include "web_pages.h"

String generateDashboardPage(uint32_t chipId, uint32_t flashSize, uint32_t flashSpeed, uint32_t heapSize, uint32_t freeHeap, uint32_t psramSize, uint32_t freePsram, uint32_t cpuFreq) {
    String html;
    html += "<!DOCTYPE html><html><head>";
    html += "<meta charset='utf-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>LED Garland Dashboard</title>";
    html += "<style>";
    html += String(WEB_STYLES);
    html += "</style></head><body>";
    
    // --- Barre de notification fixe (sans décalage de contenu) ---
    html += "<div id='notification-bar' class='hidden'>";
    html += "<div id='notification-content' class='notification-content success'></div>";
    html += "</div>";
    
    html += "<div class='container'>";
    html += "<div class='header'><h1>🎄 LED Garland Control v5.0.0</h1>";
    html += "<div class='view-toggle'><span class='toggle-label'>Mode compact</span><label class='switch'><input type='checkbox' id='compactToggle'><span class='slider'></span></label></div></div>";
    
    // ============================================================================
    // CARTE 1 : ANIMATIONS GUIRLANDE (EN PREMIER)
    // ============================================================================
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>🎨 Animations de la guirlande";
    html += "<span style='float:right;font-size:0.85em;color:#43a047;font-weight:normal'>● <span id='current-anim'>" + String(getGarlandAnimationName()) + "</span></span>";
    html += "</div>";
    html += "<div class='radio-grid'>";
    for (int i = 0; i < ANIM_COUNT; i++) {
        bool isSelected = (i == (int)getGarlandAnimation());
        html += "<div class='radio-item" + String(isSelected ? " selected" : "") + "'>";
        html += "<input type='radio' id='anim" + String(i) + "' name='garlandAnim' value='" + String(i) + "' onchange='changeAnimation(" + String(i) + ")'" + String(isSelected ? " checked" : "") + ">";
        html += "<label for='anim" + String(i) + "'>" + String(getGarlandAnimationNameById(i)) + "</label>";
        html += "</div>";
    }
    html += "</div></div>";

    // ============================================================================
    // CARTE 2 : MATRICE 8x8 (EN DEUXIÈME)
    // ============================================================================
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>🔲 Matrice LED 8x8";
    html += "<span style='float:right;font-size:0.85em;color:#43a047;font-weight:normal'>● <span id='current-matrix'>" + String(getMatrix8x8AnimationName()) + "</span></span>";
    html += "</div>";
    html += "<div class='radio-grid'>";
    for (int i = 0; i < MATRIX_ANIM_COUNT; i++) {
        bool isSelected = (i == (int)getMatrix8x8Animation());
        html += "<div class='radio-item" + String(isSelected ? " selected" : "") + "'>";
        html += "<input type='radio' id='matrixAnim" + String(i) + "' name='matrixAnim' value='" + String(i) + "' onchange='changeMatrixAnimation(" + String(i) + ")'" + String(isSelected ? " checked" : "") + ">";
        html += "<label for='matrixAnim" + String(i) + "'>" + String(getMatrix8x8AnimationNameById(i)) + "</label>";
        html += "</div>";
    }
    html += "</div></div>";

    // ============================================================================
    // CARTE 3 : MODE DE FONCTIONNEMENT (RÉORGANISÉ EN 3 ZONES)
    // ============================================================================
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>⚙️ Mode de fonctionnement</div>";
    
    // Zone supérieure : Mode (gauche) + LCD (droite) côte à côte
    html += "<div style='display:grid;grid-template-columns:1fr 1fr;gap:15px;margin-bottom:20px;'>"; 
    
    // ZONE A : Sélection du mode (moitié gauche)
    html += "<div>";
    html += "<div style='font-weight:bold;margin-bottom:10px;color:#1b5e20;font-size:14px;'>🎯 Mode actif</div>";
    html += "<div style='display:flex;flex-direction:column;gap:8px;'>";
    for (int i = 0; i < MODE_COUNT; i++) {
        bool isSelected = (i == (int)getGarlandMode());
        html += "<div class='radio-item" + String(isSelected ? " selected" : "") + "' style='margin:0;'>";
        html += "<input type='radio' id='mode" + String(i) + "' name='garlandMode' value='" + String(i) + "' onchange='changeMode(" + String(i) + ")'" + String(isSelected ? " checked" : "") + ">";
        html += "<label for='mode" + String(i) + "'>" + String(getGarlandModeNameById(i)) + "</label>";
        html += "</div>";
    }
    html += "</div></div>";
    
    // ZONE B : Mode d'affichage LCD (moitié droite)
    html += "<div>";
    html += "<div style='font-weight:bold;margin-bottom:10px;color:#1b5e20;font-size:14px;'>📺 Affichage LCD</div>";
    html += "<div style='display:flex;flex-direction:column;gap:8px;'>";
    for (int i = 0; i < DISPLAY_MODE_COUNT; i++) {
        bool isSelected = (i == (int)getDisplayMode());
        html += "<div class='radio-item" + String(isSelected ? " selected" : "") + "' style='margin:0;'>";
        html += "<input type='radio' id='displayMode" + String(i) + "' name='displayMode' value='" + String(i) + "' onchange='changeDisplayMode(" + String(i) + ")'" + String(isSelected ? " checked" : "") + ">";
        html += "<label for='displayMode" + String(i) + "'>" + String(getDisplayModeNameById(i)) + "</label>";
        html += "</div>";
    }
    html += "</div></div>";
    
    html += "</div>"; // Fin grille 2 colonnes
    
    // ZONE C : Paramètres temporels + Luminosité (toute la largeur en dessous)
    html += "<div style='padding:15px;background:#f8f9fa;border-radius:8px;'>";
    html += "<div style='font-weight:bold;margin-bottom:15px;color:#333;font-size:14px;'>📊 Paramètres temporels</div>";
    
    // 1. Durée détection mouvement
    html += "<div style='margin-bottom:15px;'>"; 
    html += "<label class='section-label'>🎯 Durée après détection mouvement (secondes) :</label>";
    html += "<input type='range' id='motion-duration-seconds' value='" + String(getMotionTriggerDurationMs() / 1000) + "' min='5' max='600' step='5' oninput='updateIntervalDisplay(this, \"motion-duration-value\")' onchange='applyMotionDuration(this.value)' style='width:100%;margin-top:5px;'>";
    html += "<div style='text-align:center;margin-top:5px;font-weight:bold;color:#43a047;'><span id='motion-duration-value'>" + String(getMotionTriggerDurationMs() / 1000) + "</span> secondes</div>";
    html += "</div>";
    
    // 2. Intervalle guirlande AUTO
    html += "<div style='margin-bottom:15px;'>"; 
    html += "<label class='section-label'>⏱️ Intervalle changement guirlande (secondes) :</label>";
    html += "<input type='range' id='auto-interval-seconds' value='" + String(getAutoAnimationIntervalMs() / 1000) + "' min='5' max='300' step='5' oninput='updateIntervalDisplay(this, \"auto-interval-value\")' onchange='applyAutoInterval(this.value)' style='width:100%;margin-top:5px;'>"; 
    html += "<div style='text-align:center;margin-top:5px;font-weight:bold;color:#43a047;'><span id='auto-interval-value'>" + String(getAutoAnimationIntervalMs() / 1000) + "</span> secondes</div>";
    html += "</div>";
    
    // 3. Intervalle matrice
    html += "<div style='margin-bottom:15px;'>";
    html += "<label class='section-label'>🔲 Intervalle changement matrice (secondes) :</label>";
    html += "<input type='range' id='matrix-interval-seconds' value='" + String(getMatrix8x8AnimationIntervalMs() / 1000) + "' min='5' max='300' step='5' oninput='updateIntervalDisplay(this, \"matrix-interval-value\")' onchange='applyMatrixInterval(this.value)' style='width:100%;margin-top:5px;'>";
    html += "<div style='text-align:center;margin-top:5px;font-weight:bold;color:#43a047;'><span id='matrix-interval-value'>" + String(getMatrix8x8AnimationIntervalMs() / 1000) + "</span> secondes</div>";
    html += "</div>";
    
    // 4. Luminosité matrice
    html += "<div>";
    html += "<label class='section-label'>💡 Luminosité matrice : <span id='brightnessValue' style='color:#43a047;font-weight:bold;'>" + String(getMatrix8x8Brightness()) + "</span></label>";
    html += "<input type='range' id='matrixBrightness' min='0' max='255' value='" + String(getMatrix8x8Brightness()) + "' oninput='updateBrightnessValue(this.value)' onchange='applyMatrixBrightness(this.value)' style='width:100%;margin-top:5px;'>";
    html += "</div>";
    
    html += "</div></div>"; // Fin zone paramètres + fin carte Mode
    html += "<div style='display:grid;grid-template-columns:repeat(auto-fit,minmax(300px,1fr));gap:15px;'>";
    
    // Infos Système
    html += "<div class='card'><div class='card-title'>ℹ️ Système</div>";
    html += "<div class='card-item'><span class='card-label'>Chip:</span><span class='card-value'>" + String(chipId, HEX) + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>Flash:</span><span class='card-value'>" + String(flashSize / 1024) + " KB</span></div>";
    html += "<div class='card-item'><span class='card-label'>RAM libre:</span><span class='card-value'>" + String(freeHeap / 1024) + " KB</span></div>";
    html += "<div class='card-item'><span class='card-label'>CPU:</span><span class='card-value'>" + String(cpuFreq) + " MHz</span></div>";
    html += "</div>";

    // WiFi
    html += "<div class='card'>";
    html += "<div class='card-title'>📶 Réseau</div>";
    html += "<div class='card-item'><span class='card-label'>SSID:</span><span class='card-value'>" + WiFi.SSID() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>IP:</span><span class='card-value mono'>" + WiFi.localIP().toString() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>mDNS:</span><span class='card-value mono'>" + String(getDeviceName()) + ".local</span></div>";
    html += "</div>";
    html += "</div>";
    
    // ============================================================================
    // CARTE 5 : NOM D'APPAREIL
    // ============================================================================
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>🏷️ Nom d'appareil (mDNS)</div>";
    html += "<div style='display:flex;gap:10px;align-items:center;flex-wrap:wrap;'>";
    html += "<input type='text' id='deviceNameInput' value='" + String(getDeviceName()) + "' placeholder='Nom unique' maxlength='32' style='flex:1;min-width:200px;padding:12px;border:2px solid #ddd;border-radius:8px;font-size:14px;'>";
    html += "<button onclick='applyDeviceName()' style='padding:12px 24px;background:linear-gradient(135deg,#667eea,#764ba2);color:white;border:none;border-radius:8px;font-weight:bold;cursor:pointer;'>✓ Appliquer</button>";
    html += "</div>";
    html += "<div style='margin-top:8px;font-size:12px;color:#666;'>Accès : http://<span id='deviceNamePreview'>" + String(getDeviceName()) + "</span>.local</div>";
    html += "</div>";

    // ============================================================================
    // ACTIONS PRINCIPALES
    // ============================================================================
    html += "<div class='actions'>";
    html += "<button onclick='location.reload()' style='background:linear-gradient(135deg,#4facfe,#00f2fe);'>🔄 Actualiser</button>";
    html += "<button onclick='window.location.href=\"/update\"' style='background:linear-gradient(135deg,#667eea,#764ba2);'>⬆️ Mise à jour OTA</button>";
    html += "<button id='reboot-btn' class='danger' onclick='rebootDevice()'>🔴 Redémarrer</button>";
    html += "</div>";
    html += "<div id='reboot-message' style='display:none;margin-top:10px;padding:12px;border-radius:8px;background:#fff3cd;color:#856404;text-align:center;'></div>";
    
    // ============================================================================
    // JAVASCRIPT - SAUVEGARDE INSTANTANÉE
    // ============================================================================
    html += "<script>";
    html += "function showNotification(msg, isError=false) { var bar = document.getElementById('notification-bar'); var content = document.getElementById('notification-content'); content.textContent = msg; content.className = 'notification-content ' + (isError ? 'error' : 'success'); bar.classList.remove('hidden'); setTimeout(() => { bar.classList.add('hidden'); }, 3000); }";
    
    // Helper pour mettre à jour affichage valeur slider
    html += "function updateIntervalDisplay(slider, spanId) { document.getElementById(spanId).textContent = slider.value; }";
    
    // Animations guirlande - SAUVEGARDE INSTANTANÉE
    html += "function changeAnimation(id) {";
    html += "  var radio = document.getElementById('anim' + id);";
    html += "  var animName = radio.nextElementSibling.textContent;";
    html += "  fetch('/animation?id=' + id);";
    html += "  showNotification('✓ ' + animName);";
    html += "  document.getElementById('current-anim').textContent = animName;";
    html += "  document.querySelectorAll('[name=\"garlandAnim\"]').forEach(item => { item.parentElement.classList.remove('selected'); if(item.checked) item.parentElement.classList.add('selected'); });";
    html += "}";
    
    // Modes - SAUVEGARDE INSTANTANÉE
    html += "function changeMode(id) {";
    html += "  var radio = document.getElementById('mode' + id);";
    html += "  var modeName = radio.nextElementSibling.textContent;";
    html += "  fetch('/mode?id=' + id);";
    html += "  showNotification('✓ Mode : ' + modeName);";
    html += "  document.querySelectorAll('[name=\"garlandMode\"]').forEach(item => { item.parentElement.classList.remove('selected'); if(item.checked) item.parentElement.classList.add('selected'); });";
    html += "}";
    
    // Intervalles - SAUVEGARDE INSTANTANÉE
    html += "function applyAutoInterval(val) { fetch('/auto_interval?ms=' + (val * 1000)); showNotification('✓ Intervalle guirlande : ' + val + 's'); }";
    html += "function applyMotionDuration(val) { fetch('/motion_duration?ms=' + (val * 1000)); showNotification('✓ Durée mouvement : ' + val + 's'); }";
    html += "function applyMatrixInterval(val) { fetch('/matrix_interval?ms=' + (val * 1000)); showNotification('✓ Intervalle matrice : ' + val + 's'); }";
    
    // Matrice - SAUVEGARDE INSTANTANÉE
    html += "function changeMatrixAnimation(id) {";
    html += "  var radio = document.getElementById('matrixAnim' + id);";
    html += "  var animName = radio.nextElementSibling.textContent;";
    html += "  fetch('/matrix_animation?id=' + id);";
    html += "  showNotification('✓ ' + animName);";
    html += "  document.getElementById('current-matrix').textContent = animName;";
    html += "  document.querySelectorAll('[name=\"matrixAnim\"]').forEach(item => { item.parentElement.classList.remove('selected'); if(item.checked) item.parentElement.classList.add('selected'); });";
    html += "}";
    html += "function updateBrightnessValue(val) { document.getElementById('brightnessValue').textContent = val; }";
    html += "function applyMatrixBrightness(val) { fetch('/matrix_brightness?value=' + val); showNotification('✓ Luminosité : ' + val); }";
    
    // Mode affichage - SAUVEGARDE INSTANTANÉE
    html += "function changeDisplayMode(id) {";
    html += "  var radio = document.getElementById('displayMode' + id);";
    html += "  var dispName = radio.nextElementSibling.textContent;";
    html += "  fetch('/display_mode?id=' + id);";
    html += "  showNotification('✓ Affichage : ' + dispName);";
    html += "  document.querySelectorAll('[name=\"displayMode\"]').forEach(item => { item.parentElement.classList.remove('selected'); if(item.checked) item.parentElement.classList.add('selected'); });";
    html += "}";
    
    // Nom d'appareil
    html += "function applyDeviceName() {";
    html += "  var name = document.getElementById('deviceNameInput').value.trim();";
    html += "  if (name === '') { showNotification('❌ Nom vide', true); return; }";
    html += "  if (!/^[a-zA-Z0-9_-]+$/.test(name)) { showNotification('❌ Caractères invalides', true); return; }";
    html += "  fetch('/device_name?name=' + encodeURIComponent(name), { method: 'POST' })";
    html += "    .then(r => r.text())";
    html += "    .then(msg => { showNotification(msg.includes('invalide') ? '❌ ' + msg : '✓ ' + msg, msg.includes('invalide')); if(!msg.includes('invalide')) document.getElementById('deviceNamePreview').textContent = name; })";
    html += "    .catch(() => showNotification('❌ Erreur', true));";
    html += "}";
    html += "document.getElementById('deviceNameInput').addEventListener('input', function() { document.getElementById('deviceNamePreview').textContent = this.value || 'garland'; });";
    
    // Redémarrage
    html += "var rebootConfirmed = false;";
    html += "function rebootDevice() {";
    html += "  if (!rebootConfirmed) {";
    html += "    rebootConfirmed = true;";
    html += "    document.getElementById('reboot-btn').textContent = '⚠️ Confirmer redémarrage';";
    html += "    document.getElementById('reboot-message').textContent = '⚠️ Cliquez à nouveau pour confirmer';";
    html += "    document.getElementById('reboot-message').style.display = 'block';";
    html += "    setTimeout(() => { rebootConfirmed = false; document.getElementById('reboot-btn').textContent = '🔴 Redémarrer'; document.getElementById('reboot-message').style.display = 'none'; }, 5000);";
    html += "  } else {";
    html += "    fetch('/reboot'); document.getElementById('reboot-message').textContent = '✅ Redémarrage...'; document.getElementById('reboot-message').style.background = '#d4edda'; document.getElementById('reboot-message').style.color = '#155724';";
    html += "  }";
    html += "}";

    // Mode compact (toggle CSS overrides)
    html += "function applyCompactMode(enabled) { document.body.classList.toggle('compact-mode', enabled); localStorage.setItem('compactMode', enabled ? '1' : '0'); }";
    html += "document.addEventListener('DOMContentLoaded', function() { var toggle = document.getElementById('compactToggle'); if (!toggle) return; var saved = localStorage.getItem('compactMode') === '1'; toggle.checked = saved; applyCompactMode(saved); toggle.addEventListener('change', function() { applyCompactMode(this.checked); }); });";
    html += "</script>";
    
    html += "</div></body></html>";
    return html;
}

String generateOTAPage() {
    String html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='utf-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Mise à jour OTA - " + String(PROJECT_NAME) + "</title>";
    html += "<style>" + String(WEB_STYLES);
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
    html += "<div class='header'>";
    html += "<h1>🔄 Mise à jour OTA</h1>";
    html += "<p>" + String(PROJECT_NAME) + " v" + String(PROJECT_VERSION) + "</p>";
    html += "</div>";
    html += "<div class='ota-container'>";
    html += "<div class='card'>";
    html += "<div class='card-title'>📦 Téléverser un nouveau firmware</div>";
    html += "<div class='warning-box'>";
    html += "⚠️ <strong>Attention :</strong> Ne débranchez pas l'appareil pendant la mise à jour. ";
    html += "L'interruption du processus pourrait rendre l'appareil inutilisable.";
    html += "</div>";
    html += "<div class='info-box'>";
    html += "ℹ️ <strong>Fichier requis :</strong> firmware.bin (compilé avec PlatformIO)<br>";
    html += "📍 <strong>Emplacement :</strong> <code>.pio/LED-Garland-Anim/build/esp32devkitc/firmware.bin</code>";
    html += "</div>";
    html += "<form id='uploadForm' enctype='multipart/form-data'>";
    html += "<div class='file-input-wrapper'>";
    html += "<input type='file' id='fileInput' name='update' accept='.bin' class='file-input' required>";
    html += "<label for='fileInput' class='file-label'>📁 Sélectionner un fichier .bin</label>";
    html += "<div class='file-name' id='fileName'>Aucun fichier sélectionné</div>";
    html += "</div>";
    html += "<button type='button' id='uploadBtn' class='upload-btn' onclick='handleUpload()'>🚀 Lancer la mise à jour</button>";
    html += "</form>";
    html += "<div id='ota-confirm-message' style='display:none;margin-top:15px;padding:12px;border-radius:8px;background:#fff3cd;color:#856404;border:1px solid #ffc107;text-align:center;'></div>";
    html += "<div class='progress-container' id='progressContainer'>";
    html += "<div class='progress-bar'><div class='progress-fill' id='progressFill'></div></div>";
    html += "<div class='progress-text' id='progressText'>0%</div>";
    html += "</div>";
    html += "<div class='status-message' id='statusMessage'></div>";
    html += "</div>";
    html += "<a href='/' class='back-btn'>← Retour au tableau de bord</a>";
    html += "</div>";
    html += "<script>";
    html += "const fileInput = document.getElementById('fileInput');";
    html += "const fileName = document.getElementById('fileName');";
    html += "const uploadForm = document.getElementById('uploadForm');";
    html += "const uploadBtn = document.getElementById('uploadBtn');";
    html += "const progressContainer = document.getElementById('progressContainer');";
    html += "const progressFill = document.getElementById('progressFill');";
    html += "const progressText = document.getElementById('progressText');";
    html += "const statusMessage = document.getElementById('statusMessage');";
    html += "fileInput.addEventListener('change', function() {";
    html += "  if (this.files.length > 0) {";
    html += "    const file = this.files[0];";
    html += "    fileName.textContent = file.name + ' (' + (file.size / 1024).toFixed(2) + ' KB)';";
    html += "  } else {";
    html += "    fileName.textContent = 'Aucun fichier sélectionné';";
    html += "  }";
    html += "});";
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
