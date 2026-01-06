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
    html += "<div class='container'>";
    html += "<div class='header'><h1>🎄 LED Garland Dashboard</h1></div>";
    
    // --- Carte Animations Guirlande ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>🎨 Animations de la guirlande";
    html += "<span style='float:right;font-size:0.85em;color:#43a047;font-weight:normal'>Actuelle : <span id='current-anim'>" + String(getGarlandAnimationName()) + "</span></span>";
    html += "</div>";
    html += "<div id='param-message' style='visibility:hidden;margin-bottom:10px;padding:8px;border-radius:6px;background:#e8f5e9;color:#1b5e20;text-align:center;font-weight:bold;'></div>";
    html += "<div class='radio-grid'>";
    for (int i = 0; i < ANIM_COUNT; i++) {
        bool isSelected = (i == (int)getGarlandAnimation());
        html += "<div class='radio-item" + String(isSelected ? " selected" : "") + "'>";
        html += "<input type='radio' id='anim" + String(i) + "' name='garlandAnim' value='" + String(i) + "' onclick='changeAnimation(" + String(i) + ")'" + String(isSelected ? " checked" : "") + ">";
        html += "<label for='anim" + String(i) + "'>" + String(getGarlandAnimationNameById(i)) + "</label>";
        html += "</div>";
    }
    html += "</div></div>";

    // --- Carte Modes de fonctionnement ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>⚙️ Mode de fonctionnement</div>";
    html += "<div class='radio-grid'>";
    for (int i = 0; i < MODE_COUNT; i++) {
        bool isSelected = (i == (int)getGarlandMode());
        html += "<div class='radio-item" + String(isSelected ? " selected" : "") + "'>";
        html += "<input type='radio' id='mode" + String(i) + "' name='garlandMode' value='" + String(i) + "' onclick='changeMode(" + String(i) + ")'" + String(isSelected ? " checked" : "") + ">";
        html += "<label for='mode" + String(i) + "'>" + String(getGarlandModeNameById(i)) + "</label>";
        html += "</div>";
    }
    html += "</div>";
    
    // Paramètres pour mode AUTO
    html += "<div style='margin-top:15px;'>"; 
    html += "<label class='section-label'>⏱️ Intervalle auto (secondes):</label>";
    html += "<div style='display:flex;gap:8px;align-items:center;'>"; 
    html += "<input type='number' id='auto-interval-seconds' value='" + String(getAutoAnimationIntervalMs() / 1000) + "' min='1' max='300' style='flex:1'>"; 
    html += "<button class='apply' onclick='applyAutoInterval()'>Appliquer</button>";
    html += "</div>";
    html += "<div id='auto-interval-message' style='visibility:hidden;margin-top:8px;padding:6px;border-radius:4px;background:#e8f5e9;color:#1b5e20;font-size:12px;text-align:center;font-weight:bold;'></div>";
    html += "</div>";
    
    // Paramètres pour mode MOTION
    html += "<div style='margin-top:15px;'>"; 
    html += "<label class='section-label'>🎯 Durée détection mouvement (secondes):</label>";
    html += "<div style='display:flex;gap:8px;align-items:center;'>";
    html += "<input type='number' id='motion-duration-seconds' value='" + String(getMotionTriggerDurationMs() / 1000) + "' min='1' max='300' style='flex:1'>";
    html += "<button class='apply' onclick='applyMotionDuration()'>Appliquer</button>";
    html += "</div>";
    html += "<div id='motion-duration-message' style='visibility:hidden;margin-top:8px;padding:6px;border-radius:4px;background:#e8f5e9;color:#1b5e20;font-size:12px;text-align:center;font-weight:bold;'></div>";
    html += "</div>";
    html += "</div>";

    // --- Carte Matrice 8x8 ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>🔲 Matrice LED 8x8";
    html += "<span style='float:right;font-size:0.85em;color:#43a047;font-weight:normal'>Actuelle : <span id='current-matrix'>" + String(getMatrix8x8AnimationName()) + "</span></span>";
    html += "</div>";
    html += "<div id='matrix-message' style='visibility:hidden;margin-bottom:10px;padding:8px;border-radius:6px;background:#e8f5e9;color:#1b5e20;text-align:center;font-weight:bold;'></div>";
    html += "<div class='radio-grid'>";
    for (int i = 0; i < MATRIX_ANIM_COUNT; i++) {
        bool isSelected = (i == (int)getMatrix8x8Animation());
        html += "<div class='radio-item" + String(isSelected ? " selected" : "") + "'>";
        html += "<input type='radio' id='matrixAnim" + String(i) + "' name='matrixAnim' value='" + String(i) + "' onclick='changeMatrixAnimation(" + String(i) + ")'" + String(isSelected ? " checked" : "") + ">";
        html += "<label for='matrixAnim" + String(i) + "'>" + String(getMatrix8x8AnimationNameById(i)) + "</label>";
        html += "</div>";
    }
    html += "</div>";
    
    // Contrôle de luminosité matrice
    html += "<div style='margin-top:15px;'>";
    html += "<label class='section-label'>💡 Luminosité : <span id='brightnessValue'>" + String(getMatrix8x8Brightness()) + "</span></label>";
    html += "<div style='display:flex;gap:8px;align-items:center;'>";
    html += "<input type='range' id='matrixBrightness' min='0' max='255' value='" + String(getMatrix8x8Brightness()) + "' oninput='updateBrightnessValue(this.value)' style='flex:1'>";
    html += "<button class='apply' onclick='applyMatrixBrightness()'>Appliquer</button>";
    html += "</div>";
    html += "<div id='matrix-brightness-message' style='visibility:hidden;margin-top:8px;padding:6px;border-radius:4px;background:#e8f5e9;color:#1b5e20;font-size:12px;text-align:center;font-weight:bold;'></div>";
    html += "</div>";
    html += "</div>";

    // --- Carte Mode d'affichage LCD ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>📺 Mode d'affichage LCD</div>";
    html += "<div class='radio-grid'>";
    for (int i = 0; i < DISPLAY_MODE_COUNT; i++) {
        bool isSelected = (i == (int)getDisplayMode());
        html += "<div class='radio-item" + String(isSelected ? " selected" : "") + "'>";
        html += "<input type='radio' id='displayMode" + String(i) + "' name='displayMode' value='" + String(i) + "' onclick='changeDisplayMode(" + String(i) + ")'" + String(isSelected ? " checked" : "") + ">";
        html += "<label for='displayMode" + String(i) + "'>" + String(getDisplayModeNameById(i)) + "</label>";
        html += "</div>";
    }
    html += "</div></div>";

    // --- Carte Sauvegarde/Chargement ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>💾 Sauvegarde et restauration</div>";
    html += "<div id='save-message' style='visibility:hidden;margin-bottom:10px;padding:8px;border-radius:6px;background:#e8f5e9;color:#1b5e20;text-align:center;font-weight:bold;'></div>";
    html += "<div style='display:flex;gap:10px;flex-wrap:wrap;'>";
    html += "<button onclick='saveConfig()' style='flex:1'>💾 Sauvegarder la config</button>";
    html += "<button onclick='loadConfig()' style='flex:1;background:linear-gradient(135deg,#43a047,#66bb6a)'>📂 Charger la config</button>";
    html += "<button onclick='eraseConfig()' class='danger' style='flex:1'>🗑️ Effacer la config</button>";
    html += "</div></div>";

    // --- Carte Informations Système ---
    html += "<div class='card'><div class='card-title'>ℹ️ Informations Système</div>";
    html += "<div class='card-item'><span class='card-label'>Chip ID:</span><span class='card-value'>" + String(chipId, HEX) + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>Flash:</span><span class='card-value'>" + String(flashSize / 1024) + " KB @ " + String(flashSpeed) + " MHz</span></div>";
    html += "<div class='card-item'><span class='card-label'>Heap:</span><span class='card-value'>" + String(heapSize / 1024) + " KB (" + String(freeHeap / 1024) + " KB libres)</span></div>";
    html += "<div class='card-item'><span class='card-label'>PSRAM:</span><span class='card-value'>" + String(psramSize / 1024) + " KB (" + String(freePsram / 1024) + " KB libres)</span></div>";
    html += "<div class='card-item'><span class='card-label'>CPU:</span><span class='card-value'>" + String(cpuFreq) + " MHz</span></div>";
    html += "</div>";

    // --- Carte WiFi ---
    html += "<div class='card'>";
    html += "<div class='card-title'>📶 Réseau WiFi</div>";
    html += "<div class='card-item'><span class='card-label'>SSID:</span><span class='card-value'>" + WiFi.SSID() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>IP:</span><span class='card-value mono'>" + WiFi.localIP().toString() + "</span></div>";
    html += "<div class='card-item'><span class='card-label'>mDNS:</span><span class='card-value mono'>" + String(getDeviceName()) + ".local</span></div>";
    html += "</div>";
    
    // --- Carte Nom d'appareil ---
    html += "<div class='card card-full'>";
    html += "<div class='card-title'>🏷️ Nom d'appareil (mDNS)</div>";
    html += "<div id='device-name-message' style='visibility:hidden;margin-bottom:10px;padding:8px;border-radius:6px;background:#e8f5e9;color:#1b5e20;text-align:center;font-weight:bold;'></div>";
    html += "<div style='display:flex;gap:10px;align-items:center;'>";
    html += "<input type='text' id='deviceNameInput' value='" + String(getDeviceName()) + "' placeholder='Nom unique' maxlength='32' style='flex:1;padding:10px;border:2px solid #ddd;border-radius:8px;font-size:14px;'>";
    html += "<button onclick='applyDeviceName()' class='apply'>Appliquer</button>";
    html += "</div>";
    html += "<div style='margin-top:8px;font-size:12px;color:#666;'>Accès via : http://<span id='deviceNamePreview'>" + String(getDeviceName()) + "</span>.local</div>";
    html += "<div style='margin-top:4px;font-size:11px;color:#999;'>Caractères autorisés : a-z, A-Z, 0-9, tiret (-) et underscore (_)</div>";
    html += "</div>";

    // --- BOUTONS D'ACTION ---
    html += "<div style='position:relative;'>";
    html += "<div class='actions'>";
    html += "<button onclick='location.reload()'>🔄 Actualiser</button>";
    html += "<button onclick='window.location.href=\"/update\"' style='background:linear-gradient(135deg,#667eea 0%,#764ba2 100%)'>⬆️ Mise à jour OTA</button>";
    html += "<button id='reboot-btn' class='danger' onclick='rebootDevice()'>🔴 Redémarrer</button>";
    html += "</div>";
    html += "<div id='reboot-message' style='display:none;position:absolute;top:0;right:0;padding:10px 15px;border-radius:8px;background:#fff3cd;color:#856404;border:1px solid #ffc107;max-width:350px;box-shadow:0 2px 8px rgba(0,0,0,0.1);'></div>";
    html += "</div>";
    
    // --- SCRIPT JAVASCRIPT ---
    html += "<script>";
    html += "function showParamMessage(msg) { var el = document.getElementById('param-message'); el.textContent = msg; el.style.visibility = 'visible'; setTimeout(() => { el.style.visibility = 'hidden'; el.textContent = ''; }, 2500); }";
    html += "function showMatrixMessage(msg) { var el = document.getElementById('matrix-message'); el.textContent = msg; el.style.visibility = 'visible'; setTimeout(() => { el.style.visibility = 'hidden'; el.textContent = ''; }, 2500); }";
    html += "function showMessage(msg) { var el = document.getElementById('save-message'); el.textContent = msg; el.style.visibility = 'visible'; setTimeout(() => { el.style.visibility = 'hidden'; el.textContent = ''; }, 3000); }";
    
    html += "function updateCurrentAnimation(animName) {";
    html += "  var el = document.getElementById('current-anim');";
    html += "  if (el) { el.textContent = animName; }";
    html += "  var items = document.querySelectorAll('[name=\"garlandAnim\"]');";
    html += "  items.forEach(item => { var parent = item.parentElement; parent.classList.remove('selected'); if (item.checked) parent.classList.add('selected'); });";
    html += "}";
    
    html += "function changeAnimation(id) {";
    html += "  var radio = document.getElementById('anim' + id);";
    html += "  var animName = radio.nextElementSibling.textContent;";
    html += "  fetch('/animation?id=' + id).then(() => { showParamMessage('✓ Animation changée : ' + animName); updateCurrentAnimation(animName); });";
    html += "}";
    
    html += "function updateCurrentMode(modeName) {";
    html += "  var items = document.querySelectorAll('[name=\"garlandMode\"]');";
    html += "  items.forEach(item => { var parent = item.parentElement; parent.classList.remove('selected'); if (item.checked) parent.classList.add('selected'); });";
    html += "}";
    
    html += "function changeMode(id) {";
    html += "  var radio = document.getElementById('mode' + id);";
    html += "  var modeName = radio.nextElementSibling.textContent;";
    html += "  fetch('/mode?id=' + id).then(() => { showParamMessage('✓ Mode changé : ' + modeName); updateCurrentMode(modeName); });";
    html += "}";
    

    
    html += "function updateCurrentMatrix(animName) {";
    html += "  var el = document.getElementById('current-matrix');";
    html += "  if (el) { el.textContent = animName; }";
    html += "  var items = document.querySelectorAll('[name=\"matrixAnim\"]');";
    html += "  items.forEach(item => { var parent = item.parentElement; parent.classList.remove('selected'); if (item.checked) parent.classList.add('selected'); });";
    html += "}";
    
    html += "function changeMatrixAnimation(id) {";
    html += "  var radio = document.getElementById('matrixAnim' + id);";
    html += "  var animName = radio.nextElementSibling.textContent;";
    html += "  fetch('/matrix_animation?id=' + id).then(() => { showMatrixMessage('✓ Animation changée : ' + animName); updateCurrentMatrix(animName); });";
    html += "}";
    
    html += "function updateBrightnessValue(val) { document.getElementById('brightnessValue').textContent = val; }";
    html += "function applyMatrixBrightness() { var val = document.getElementById('matrixBrightness').value; var msg = document.getElementById('matrix-brightness-message'); msg.textContent = '✓ Luminosité : ' + val; msg.style.visibility = 'visible'; setTimeout(() => { msg.style.visibility = 'hidden'; }, 3000); fetch('/matrix_brightness?value=' + val); }";
    
    html += "function applyAutoInterval() { var val = document.getElementById('auto-interval-seconds').value; var msg = document.getElementById('auto-interval-message'); if (val < 1 || val > 300) { msg.textContent = '❌ Valeur invalide'; msg.style.background = '#ffebee'; msg.style.color = '#c62828'; } else { msg.textContent = '✓ Intervalle : ' + val + 's'; msg.style.background = '#e8f5e9'; msg.style.color = '#1b5e20'; fetch('/auto_interval?ms=' + (val * 1000)); } msg.style.visibility = 'visible'; setTimeout(() => { msg.style.visibility = 'hidden'; }, 3000); }";
    
    html += "function applyMotionDuration() { var val = document.getElementById('motion-duration-seconds').value; var msg = document.getElementById('motion-duration-message'); if (val < 1 || val > 300) { msg.textContent = '❌ Valeur invalide'; msg.style.background = '#ffebee'; msg.style.color = '#c62828'; } else { msg.textContent = '✓ Durée : ' + val + 's'; msg.style.background = '#e8f5e9'; msg.style.color = '#1b5e20'; fetch('/motion_duration?ms=' + (val * 1000)); } msg.style.visibility = 'visible'; setTimeout(() => { msg.style.visibility = 'hidden'; }, 3000); }";
    
    html += "function changeDisplayMode(id) { var radio = document.getElementById('displayMode' + id); var dispName = radio.nextElementSibling.textContent; fetch('/display_mode?id=' + id).then(() => { showParamMessage('✓ Affichage changé : ' + dispName); }); }";
    
    html += "function showDeviceNameMessage(msg, isError) { var el = document.getElementById('device-name-message'); el.textContent = msg; el.style.visibility = 'visible'; el.style.background = isError ? '#ffebee' : '#e8f5e9'; el.style.color = isError ? '#c62828' : '#1b5e20'; setTimeout(() => { el.style.visibility = 'hidden'; el.textContent = ''; }, isError ? 5000 : 3000); }";
    
    html += "function applyDeviceName() {";
    html += "  var name = document.getElementById('deviceNameInput').value.trim();";
    html += "  if (name === '') { showDeviceNameMessage('❌ Le nom ne peut pas être vide', true); return; }";
    html += "  var validNameRegex = /^[a-zA-Z0-9_-]+$/;";
    html += "  if (!validNameRegex.test(name)) { showDeviceNameMessage('❌ Caractères invalides (a-z, A-Z, 0-9, - et _)', true); return; }";
    html += "  if (name.startsWith('-') || name.endsWith('-')) { showDeviceNameMessage('❌ Le nom ne peut pas commencer ou finir par un tiret', true); return; }";
    html += "  fetch('/device_name?name=' + encodeURIComponent(name), { method: 'POST' })";
    html += "    .then(r => r.text())";
    html += "    .then(msg => {";
    html += "      if (msg.includes('invalide')) { showDeviceNameMessage('❌ ' + msg, true); }";
    html += "      else { showDeviceNameMessage('✓ ' + msg); document.getElementById('deviceNamePreview').textContent = name; }";
    html += "    })";
    html += "    .catch(err => showDeviceNameMessage('❌ Erreur de connexion', true));";
    html += "}";
    
    html += "document.getElementById('deviceNameInput').addEventListener('input', function() {";
    html += "  document.getElementById('deviceNamePreview').textContent = this.value || 'garland';";
    html += "});";
    
    html += "function saveConfig() { fetch('/save').then(() => showMessage('✓ Configuration sauvegardée')); }";
    html += "function loadConfig() { fetch('/load').then(() => { showMessage('✓ Configuration chargée'); setTimeout(() => location.reload(), 1500); }); }";
    html += "function eraseConfig() { if(confirm('Effacer la configuration sauvegardée ?')) { fetch('/erase').then(() => showMessage('✓ Configuration effacée')); } }";
    
    html += "var rebootConfirmed = false;";
    html += "function rebootDevice() {";
    html += "  if (!rebootConfirmed) {";
    html += "    rebootConfirmed = true;";
    html += "    document.getElementById('reboot-btn').textContent = '⚠️ Cliquer à nouveau pour confirmer';";
    html += "    document.getElementById('reboot-message').textContent = '⚠️ Cliquer à nouveau sur le bouton pour confirmer le redémarrage';";
    html += "    document.getElementById('reboot-message').style.display = 'block';";
    html += "    setTimeout(() => { rebootConfirmed = false; document.getElementById('reboot-btn').textContent = '🔴 Redémarrer'; document.getElementById('reboot-message').style.display = 'none'; }, 5000);";
    html += "  } else {";
    html += "    fetch('/reboot').then(() => { document.getElementById('reboot-message').textContent = '✅ Redémarrage en cours...'; document.getElementById('reboot-message').style.background = '#d4edda'; document.getElementById('reboot-message').style.color = '#155724'; document.getElementById('reboot-message').style.borderColor = '#c3e6cb'; });";
    html += "  }";
    html += "}";
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
    html += "📍 <strong>Emplacement :</strong> <code>.pio/build/esp32devkitc/firmware.bin</code>";
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
