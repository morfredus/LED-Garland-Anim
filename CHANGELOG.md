# Changelog - LED Garland Animation Controller

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

# [Unreleased]

# [5.1.5] - 2026-01-07

## 📦 Complete Consolidation with WiFi Template

This release adds the missing `secrets_example.h` template file for user-friendly WiFi configuration, consolidating firmware improvements (v5.1.2) and documentation updates (v5.1.3, v5.1.4) into a single, comprehensive v5.1.5 package.

## ✅ Added
- **`include/secrets_example.h`**: Template configuration file for WiFi network setup
  - Example structure for SSID and password entries
  - Guidance for adding multiple networks
  - Prevents accidental modification of git-ignored `secrets.h`
  - Clear usage instructions for users

## ✨ From v5.1.4 & v5.1.3 (Included in v5.1.5)
- **New beginner guides**: QUICKSTART.md/FR, HARDWARE_GUIDE.md/FR
- **Release notes**: RELEASE_v5.1.4.md/FR  
- **Telegram module removal**: Deleted src/telegram_control.*, include/telegram_control.h
- **Documentation cleanup**: 7 obsolete release notes deleted
- **Version synchronization**: All docs updated to v5.1.4 (now v5.1.5)

## 🔧 Technical
- No runtime behavior changes; fully backward compatible
- Build: 71.3% Flash, 15.5% RAM ✅
- All firmware files at v5.1.5
- All documentation (28+ files) at v5.1.5

### Version Classification
**SEMVER**: 5.1.5 (PATCH) – Consolidated release: v5.1.2 firmware + v5.1.3 docs + v5.1.5 config template

---

# [5.1.4] - 2026-01-07

## 📦 Complete & Consolidated Release

This release combines firmware cleanup (Telegram removal) and comprehensive documentation improvements into a single, unified v5.1.4 package.

## 🔥 Removed
- Deleted unused Telegram module files: `src/telegram_control.cpp`, `include/telegram_control.h`.
- Deleted 7 obsolete release note files:
  - `docs/FIXES_v1.12.0.md`
  - `docs/RELEASE_v1.10.0.md` through `v1.12.1.md` (4 files)
  - `docs/RELEASE_v3.0.1.md` and `v3.0.2.md`
- Removed all Telegram references from documentation

## ✨ Added
- **New beginner-friendly guides** (bilingual EN/FR):
  - `docs/QUICKSTART.md` / `QUICKSTART_FR.md`: 5-minute quick start guide
  - `docs/HARDWARE_GUIDE.md` / `HARDWARE_GUIDE_FR.md`: Complete component shopping list with suppliers
- **Release notes for v5.1.4**:
  - `docs/RELEASE_v5.1.4.md` (English)
  - `docs/RELEASE_v5.1.4_FR.md` (French)

## 🔄 Changed
- **Version synchronization** across all documentation to v5.1.4:
  - README.md / README_FR.md
  - USER_GUIDE.md / USER_GUIDE_FR.md
  - ARCHITECTURE.md / ARCHITECTURE_FR.md
  - PIN_MAPPING.md / PIN_MAPPING_FR.md
  - TROUBLESHOOTING.md / TROUBLESHOOTING_FR.md
  - OTA_UPDATE.md / OTA_UPDATE_FR.md
  - PIR_SENSOR_SETUP.md / PIR_SENSOR_SETUP_FR.md
  - RADAR_SENSOR_SETUP.md / RADAR_SENSOR_SETUP_FR.md
- **README.md restructured**: "Choosing USB or OTA Upload" section moved to proper location
- **Firmware version**: 5.1.2 → 5.1.4 in platformio.ini, config.h, main.cpp

## 🔧 Technical
- No runtime behavior changes
- All existing functionality preserved
- Fully backward compatible
- Cleaner codebase (Telegram module removed)

### Build Status
- **Flash**: 71.3% (935,105 bytes / 1,310,720 bytes)
- **RAM**: 15.5% (50,648 bytes / 327,680 bytes)
- **Compilation**: ✅ SUCCESS (no errors/warnings)

### Version Classification

**SEMVER**: 5.1.4 (PATCH)
- **Justification**: Consolidated release combining firmware cleanup (Telegram removal, v5.1.2) and documentation improvements (version sync + obsolete file removal, v5.1.3). No functional changes; fully backward compatible.

# [5.1.1] - 2026-01-07

## 🐛 Fixed

1. **Matrix animation interval now independent from garland**
   - **Critical bug**: Matrix AUTO mode was using `getAutoAnimationIntervalMs()` (garland interval) instead of `getMatrix8x8AnimationIntervalMs()`.
   - Corrected line 2019 in `src/matrix8x8_control.cpp` to use matrix-specific interval.
   - Removed misleading comment indicating interval sharing between garland and matrix.

2. **Matrix interval persistence verified**
   - Confirmed that `loadMatrix8x8Settings()` properly restores saved interval from NVS.
   - Confirmed that `saveMatrix8x8Settings()` stores interval in NVS when changed via web UI.
   - Matrix interval now survives device reboots independently.

## 🔧 Technical
- Updated variable documentation in `matrix8x8_control.cpp` line 23 to clarify independence: `// Matrix animation interval (independent from garland)`
- No breaking changes; web API remains unchanged.
- Matrix setters/getters already in place and functional; only interval logic was corrected.

## 📚 Documentation
- Updated all file headers to version 5.1.1 and date 2026-01-07:
  - `include/config.h`
  - `include/matrix8x8_control.h`
  - `src/matrix8x8_control.cpp`
  - `src/main.cpp`
  - `include/garland_control.h`

### Version Classification

**SEMVER**: 5.1.1 (PATCH)
- **Justification**: Critical bug fix for matrix animation interval independence. No API changes; no new features. Backward-compatible.

# [5.1.0] - 2026-01-06

## ✨ Changed
1. **Animated LCD layout reorganized** from split left/right panels to **full-width stacked zones**:
   - **Header**: Unchanged (project name + version in festive banner)
   - **Info Frame (fullwidth)**: Mode, WiFi SSID (truncated to 20 chars if needed), IP, and mDNS name
   - **Animation Zone (fullwidth)**: Larger animation viewport with improved aspect ratio

2. **SSID Truncation Logic**: SSID automatically truncates to max 20 characters with "..." suffix if overflow detected, preventing text spillage.

3. **mDNS Display**:
   - `displayScreenByMode()` and `displayMainScreen()` now accept optional `mDnsName` parameter
   - Animated screen now displays mDNS name (e.g., "garland.local") in the info frame
  - All display calls updated across main.cpp and web_interface.cpp

4. **Improved Readability**:
   - Info frame is now 70px tall with 5 lines of data instead of side-panel cramping
   - Animation zone has more vertical space for better visual feedback
   - Better color contrast and spacing between elements

## 🔧 Technical
- Updated `displayMainScreen()` signature: added `const char* mDnsName = nullptr` parameter
- Updated `displayScreenByMode()` signature: added `const char* mDnsName = nullptr` parameter
- Helper function `truncateText()` added to handle SSID/animation label overflow
- All calls to display functions now pass `String(getDeviceName()) + ".local"` as mDNS
- Static mode unchanged (still displays mDNS from `displayScreenByMode`)

## 📚 Documentation
1. README.md / README_FR.md bumped to 5.1.0 with new layout description
2. docs/USER_GUIDE.md / docs/USER_GUIDE_FR.md updated to describe stacked fullwidth zones
3. Added release notes: docs/RELEASE_v5.1.0.md and docs/RELEASE_v5.1.0_FR.md

### Version Classification

**SEMVER**: 5.1.0 (MINOR)
- **Justification**: Layout reorganization and enhanced network info display (mDNS addition) improve usability and fix SSID overflow issues. Backward-compatible parameters (mDnsName optional).

# [5.0.0] - 2026-01-06

## ✨ Changed
1. Animated LCD screen restyled to mirror the festive static layout (textured background, ribbon frames, sparkles, twin garlands).
2. Animation zone shrunk into a framed “Mini show” window to free space for mode/network details without losing visual feedback.
3. Animated info card now highlights Mode, Garland animation, Matrix animation, SSID, and IP with colorful accents.

## 📚 Documentation
1. README.md / README_FR.md bumped to 5.0.0 with the new animated LCD description.
2. docs/USER_GUIDE.md / docs/USER_GUIDE_FR.md updated to describe the festive animated screen and reduced animation window.
3. Added release notes: docs/RELEASE_v5.0.0.md and docs/RELEASE_v5.0.0_FR.md.

### Version Classification

**SEMVER**: 5.0.0 (MAJOR)
- **Justification**: Complete redesign of the animated LCD screen (layout, visuals, and reduced animation area) while preserving all displayed information.

# [4.0.0] - 2026-01-06

## ✨ Added
1. Festive static LCD dashboard with ribbon frame, sparkle corners, and dual garland separators in Static mode.
2. Static screen now surfaces Program name, Version, SSID, IP, and mDNS (`*.local`) at all times for easier pairing.

## 📝 Changed
1. Static view uses non-wrapping text to keep long SSIDs readable without breaking the decorative layout.
2. Updated LCD rendering while keeping backlight behavior unchanged in Static mode.

## 📚 Documentation
1. README.md / README_FR.md bumped to 4.0.0 with the festive static screen description.
2. docs/USER_GUIDE.md / docs/USER_GUIDE_FR.md refreshed to explain the new LCD dashboard contents.
3. Added bilingual release notes: docs/RELEASE_v4.0.0.md and docs/RELEASE_v4.0.0_FR.md.

### Version Classification

**SEMVER**: 4.0.0 (MAJOR)
- **Justification**: Complete redesign of the LCD static screen with new visible data (mDNS) and a new layout.

# [3.0.2] - 2026-01-06

## 🐛 Fixed

**TFT Display Border still disappearing with matrix animations**
- **Problem**: During animated mode with matrix info shown, the animation clear area overlapped the header/separator, causing the white rectangle top edge and cyan line to vanish once animations started.
- **Root Cause**: The ST7789 refresh loop called `updateAnimationVisual()` without passing the `hasMatrix` flag, so the clear rectangle used the non-matrix coordinates while the UI drew the matrix layout.
- **Solution**: Pass the `hasMatrix` flag from the main loop when refreshing the ST7789 animation area so clearing/drawing uses the correct rectangle bounds.
- **File**: [src/main.cpp](src/main.cpp#L235-L249)
- **Impact**: Animation border and cyan separation line now remain visible for all animations, with or without matrix info displayed.

## 🔧 Technical

- ST7789 refresh: `updateAnimationVisual(getGarlandAnimationName(), getMatrix8x8AnimationName() != nullptr)`
- Version bumped to 3.0.2 across project files
- Added [docs/RELEASE_v3.0.2.md](docs/RELEASE_v3.0.2.md)

### Version Classification

**SEMVER**: 3.0.2 (PATCH)
- **Justification**: Bug fix only; no new features; no breaking changes

---

# [3.0.1] - 2026-01-06

## 🐛 Fixed

**TFT Display Animation Border Bug**
- **Problem**: Animation box border and cyan separation line disappeared when animation started rendering
- **Root Cause**: `fillRect` in `updateAnimationVisual()` erased too much area, overlapping with border lines
  - Used margins: `animX + 1, animY + 1, animWidth - 2, animHeight - 2`
  - Border thickness: 1 pixel → not enough clearance
- **Solution**: Increased safety margins in fill operation
  - Changed to: `animX + 2, animY + 2, animWidth - 4, animHeight - 4`
  - Provides 2-pixel clearance from borders instead of 1 pixel
  - Prevents animation rendering from erasing rectangle borders and cyan line
- **File**: [src/display.cpp](src/display.cpp#L265)
- **Impact**: Animation box and separation line now remain visible during all animations

## 🔧 Technical

**Files Modified**:
- [src/display.cpp](src/display.cpp): Fixed fillRect margins in `updateAnimationVisual()` function
- Version updated to 3.0.1 across all project files

**Compilation Statistics**:
- Expected: Similar to v3.0.0 (Flash ~81.3%, RAM 15.8%)

### Version Classification

**SEMVER**: 3.0.1 (PATCH)
- **Justification**: Bug fix only - no breaking changes, no new features
- **Scope**: Display rendering correction

---

# [3.0.0] - 2026-01-06

## 💥 BREAKING CHANGES (MAJOR)

### **Complete Web UI Card Reorganization**
Complete restructuring of the web interface card order - users must relearn the navigation flow.

**NEW Card Order** (v3.0.0):
1. 🎄 **Animations Guirlande** (was Card 2)
2. 🎨 **Matrice 8x8** (was Card 3)
3. 🎯 **Mode de fonctionnement** (redesigned - was Card 1)
4. ℹ️ **Système & Réseau** (was Card 4)
5. 🏷️ **Nom d'appareil** (was Card 5)

**OLD Card Order** (v2.0.0):
1. Mode de fonctionnement
2. Animations Guirlande
3. Matrice 8x8
4. Mode affichage LCD (separate card)
5. Système & Réseau
6. Nom d'appareil

**Rationale**: Animations (Guirlande + Matrice) are now prioritized at the top since they are the most frequently accessed features. Configuration (Mode + parameters) is grouped in the third position. System information is pushed lower as it's less frequently consulted.

### **Mode Card Redesigned with 3-Zone Layout**

The Mode card now features a sophisticated 3-zone layout that consolidates all configuration in one place:

**Zone A (Left Half)**: Mode selection
- 🎯 Mode actif: Auto | Manuel | Détection mouvement
- Vertical radio button layout (`flex-direction:column`)

**Zone B (Right Half)**: LCD Display Mode
- 📺 Affichage LCD: Animation + matrice | Animation seule | Écran éteint
- Integrated into Mode card (was separate Card 4 in v2.0.0)
- Vertical radio button layout

**Zone C (Full Width Below)**: Temporal Parameters + Brightness
- ⏱️ Durée d'allumage après détection mouvement
- 🔄 Intervalle auto changement guirlande
- 🔄 Intervalle auto changement matrice
- 💡 Luminosité matrice (moved from Card 2 - Matrice 8x8)

**CSS Grid Implementation**:
```css
<div style='display:grid;grid-template-columns:1fr 1fr;gap:15px;'>
  <!-- Zone A: Mode --> <!-- Zone B: LCD -->
</div>
<div style='padding:15px;background:#f8f9fa;'>
  <!-- Zone C: Params + Brightness -->
</div>
```

### ✨ Added

**Enhanced Mode Card Organization**
- **LCD Mode Integration**: LCD display mode selection now directly integrated into Mode card (removed separate card)
- **Consolidated Parameters**: All temporal parameters and matrix brightness in single, unified section
- **Logical Grouping**: All configuration in one place - reduces scrolling and improves UX
- **Side-by-Side Layout**: Mode and LCD selection displayed side-by-side using CSS grid

**Visual Improvements**
- **Vertical Radio Buttons**: All radio groups now use `flex-direction:column` (vertical stacking)
- **Better Hierarchy**: Clear visual separation between Mode/LCD (top) and parameters (bottom)
- **Reduced Scrolling**: 3-zone layout more compact than previous multi-card approach

### 📝 Changed

**UI Navigation Flow**
- **Animations First**: Guirlande and Matrice animations prioritized at top (most frequently used)
- **Configuration Second**: Mode card with all parameters in third position (logical grouping)
- **System Last**: System information and device name pushed lower (less frequently accessed)
- **Brightness Relocation**: Matrix brightness control moved from Matrice card to Mode card (consolidated with other parameters)

**Card Content Modifications**
- **Matrice 8x8 Card**: Removed brightness slider (now in Mode card Zone C)
- **LCD Card**: Completely removed - functionality integrated into Mode card Zone B
- **Mode Card**: Expanded from simple mode selection to comprehensive 3-zone configuration center

### 🔧 Technical

**Files Modified**:
- [src/web_pages.cpp](src/web_pages.cpp): Complete card restructure (128-line replacement in lines 20-148)
  * Version header: "v2.0" → "v3.0"
  * Card 1: Animations Guirlande (entire structure from old Card 2)
  * Card 2: Matrice 8x8 (structure from old Card 3, brightness removed)
  * Card 3: Mode de fonctionnement (completely redesigned with 3 zones)
  * Cards 4-5: Système & Device Name (comment updates only)
  * JavaScript: Unchanged (all HTML IDs preserved for compatibility)
- [platformio.ini](platformio.ini): PROJECT_VERSION "2.0.0" → "3.0.0"
- [include/config.h](include/config.h): @version 2.0.0 → 3.0.0
- [src/main.cpp](src/main.cpp): @version 1.13.0 → 3.0.0
- [src/display.cpp](src/display.cpp): @version 2.0.0 → 3.0.0
- [include/display.h](include/display.h): @version 1.13.0 → 3.0.0
- [src/garland_control.cpp](src/garland_control.cpp): @version 1.13.0 → 3.0.0
- [src/matrix8x8_control.cpp](src/matrix8x8_control.cpp): @version 2.0.0 → 3.0.0
- [include/web_styles.h](include/web_styles.h): @version 2.0.0 → 3.0.0

**Compilation Statistics**:
```
Processing esp32devkitc
RAM:   [==        ]  15.8% (used 51,700 bytes from 327,680 bytes)
Flash: [========  ]  81.3% (used 1,065,553 bytes from 1,310,720 bytes)
[SUCCESS] Took 74.60 seconds
```

**Backward Compatibility**:
- ✅ All JavaScript functions unchanged (HTML element IDs preserved)
- ✅ NVS storage format unchanged (no migration required)
- ✅ All functionality from v2.0.0 preserved
- ❌ UI navigation flow completely different (BREAKING - requires user relearning)

### 📚 Documentation

**Updated Files** (bilingual):
- CHANGELOG.md + CHANGELOG_FR.md: v3.0.0 entry with complete reorganization details
- README.md + README_FR.md: Updated with new card order description
- docs/USER_GUIDE.md + docs/USER_GUIDE_FR.md: Updated navigation instructions

### Version Classification

**SEMVER**: 3.0.0 (MAJOR)
- **Justification**: Complete UI card reorganization constitutes a breaking change in user experience
- **Impact**: Users must relearn interface navigation flow (card order completely different)
- **Scope**: UI only - no breaking changes to API, storage format, or functionality

---

# [2.0.0] - 2026-01-06

## 💥 BREAKING CHANGES (MAJOR)

### **Complete Web UI Reorganization**
- **Interface moderne et intuitive**: Sauvegarde instantanée sur tous les paramètres (sauf nom d'appareil)
- **Nouveau pattern d'interaction**: Plus de boutons "Appliquer" inutiles - changements appliqués immédiatement
- **Sliders améliorés**: Tous les intervalles temporels utilisent des curseurs avec affichage en temps réel
- **Regroupement logique**: Paramètres temporels regroupés dans la carte "Mode de fonctionnement"
- **Notifications centralisées**: Barre fixe en haut pour toutes les confirmations
- **Ordre des cartes optimisé**: Mode → Guirlande → Matrice → LCD (flux logique)

### 🐛 Fixed (Critical Bugs)

1. **Screen Off Mode**
   - **Problème**: Mode écran éteint laissait pixels visibles malgré backlight coupé
   - **Cause**: `digitalWrite(LCD_BLK, LOW)` appelé avant `fillScreen(BLACK)`
   - **Solution**: Inversion de l'ordre - pixels effacés avant coupure backlight
   - **Fichier**: [src/display.cpp](src/display.cpp#L57-L60)

2. **Matrix Auto-Start**
   - **Problème**: Mode auto matrice ne démarrait pas automatiquement au boot
   - **Cause**: Flag `autoModeActive` jamais initialisé après chargement NVS
   - **Solution**: Initialisation de `autoModeActive=true` dans `setupMatrix8x8()` quand `currentAnimation==MATRIX_ANIM_AUTO`
   - **Fichier**: [src/matrix8x8_control.cpp](src/matrix8x8_control.cpp#L1963-L1975)

### ✨ Added (Features)

**Sauvegarde instantanée**
- Événements `onchange` sur tous les contrôles interactifs
- Validation côté client pour intervalles (multiples de 5s, 5-300s)
- Feedback visuel immédiat via barre de notification
- Pas de latence - expérience fluide et réactive

**Sliders temporels avec affichage**
- Intervalle guirlande: curseur + valeur affichée en temps réel
- Durée mouvement: curseur + valeur affichée en temps réel
- Intervalle matrice: curseur + valeur affichée en temps réel
- Luminosité matrice: curseur + valeur affichée en temps réel

**Informations système compactées**
- Carte Système: Chip ID, Flash, RAM, CPU (2x2 grid responsive)
- Carte Réseau: SSID, IP, mDNS (dans même section)
- Suppression infos redondantes (PSRAM, Flash speed, Heap size)
- Mise en page responsive avec `grid-template-columns`

### 📝 Changed (Interface)

**Réorganisation des cartes** (avant → après):
1. ~~Animations guirlande~~ → **Mode de fonctionnement** (+ tous params temporels)
2. ~~Mode de fonctionnement~~ → **Animations guirlande**
3. **Matrice 8x8** (inchangée)
4. **Mode affichage LCD** (passage de onclick à onchange)
5. ~~Sauvegarde/Restauration~~ → **Supprimé** (fonctionnalité conservée, UI simplifiée)
6. ~~Informations Système + Réseau WiFi~~ → **Système & Réseau** (fusionnées en grid 2 colonnes)
7. **Nom d'appareil** (conservé - validation requise)
8. **Actions** (Actualiser, OTA, Redémarrer)

**Modifications JavaScript**
- `changeAnimation(id)`, `changeMode(id)`, `changeMatrixAnimation(id)`: sauvegarde instantanée
- `applyAutoInterval(val)`, `applyMotionDuration(val)`, `applyMatrixInterval(val)`: acceptent paramètre direct (plus de `getElementById`)
- `applyMatrixBrightness(val)`: accepte paramètre direct
- `changeDisplayMode(id)`: sauvegarde instantanée
- `updateIntervalDisplay(slider, spanId)`: nouvelle fonction helper pour mettre à jour spans
- Suppression de toutes les fonctions inutilisées (`showParamMessage`, `showMatrixMessage`, `showMessage`)

**Pattern de code HTML/JS** (transformation complète):
```javascript
// AVANT v2.0.0 (pattern obsolète):
<input type='number' id='auto-interval-seconds' min='5' max='300' step='5'>
<button onclick='applyAutoInterval()'>Appliquer</button>
function applyAutoInterval() {
  var val = document.getElementById('auto-interval-seconds').value;
  fetch('/auto_interval?ms=' + (val * 1000));
}

// APRÈS v2.0.0 (pattern moderne):
<input type='range' id='auto-interval-seconds' min='5' max='300' step='5'
  onchange='applyAutoInterval(this.value)'
  oninput='updateIntervalDisplay(this, "auto-interval-value")'>
<span id='auto-interval-value'>30</span>s
function applyAutoInterval(val) {
  fetch('/auto_interval?ms=' + (val * 1000));
  showNotification('✓ Intervalle : ' + val + 's');
}
```

### 🔧 Technical

**Fichiers modifiés** (6 fichiers):
- [src/display.cpp](src/display.cpp) - Bug fix screen off + version 2.0.0
- [src/matrix8x8_control.cpp](src/matrix8x8_control.cpp) - Bug fix auto-start + version 2.0.0
- [src/web_pages.cpp](src/web_pages.cpp) - Refonte complète UI (HTML + JavaScript)
- [platformio.ini](platformio.ini) - Version 2.0.0
- [include/config.h](include/config.h) - Version 2.0.0
- [include/display.h](include/display.h) - Version 2.0.0 (?)

**Statistiques compilation**:
- RAM: 15.8% (51,700 bytes / 327,680 bytes) - inchangé
- Flash: 81.3% (1,065,377 bytes / 1,310,720 bytes) - gain 0.2%
- Durée: 203.02 secondes (build complet)

### 📚 Documentation

- Version bumps: tous les fichiers source en-têtes mis à jour v2.0.0
- CHANGELOG.md et CHANGELOG_FR.md mis à jour
- README.md et README_FR.md mis à jour avec nouvelle UI
- USER_GUIDE.md et USER_GUIDE_FR.md mis à jour avec captures d'écran

### Version

- **SEMVER Classification**: MAJOR (2.0.0) - Breaking changes UI complète

---

# [1.12.1] – 2026-01-06

### Changed (PATCH - Performance / Responsiveness)
- Throttled 8x8 matrix refresh to a minimum 15 ms step to avoid loop saturation while keeping visuals intact.
- Throttled garland animation engine to a minimum 10 ms step to reduce CPU load without changing behaviors.
- ST7789 animated screen refresh set to 200 ms (previously 100 ms) to lower SPI overhead.
- No functional changes; goal is smoother UI/loop responsiveness.
- Release notes: [docs/RELEASE_v1.12.1.md](docs/RELEASE_v1.12.1.md)
- **SEMVER Classification**: PATCH (1.12.1) - performance tuning only.

# [1.12.0] – 2026-01-06

### Added (MINOR - mDNS Support for Easy Access)

**Unique Device Name via mDNS**
- **Feature**: Access web interface via unique device name instead of IP address
  - Default name: `garland.local`
  - Customizable from web UI
  - Persistent storage in NVS
  - Real-time validation (alphanumeric, dash, underscore, max 32 chars)
- **Benefits**:
  - No more IP hunting!
  - Cross-platform compatible (Windows 10+, macOS, Linux, iOS, Android)
  - Memorable, user-friendly URLs
- **Implementation**:
  - Added `ESPmDNS` library integration
  - New functions in `garland_control.cpp`: `getDeviceName()`, `setDeviceName()`, `loadDeviceNameFromNVS()`, `saveDeviceNameToNVS()`, `isValidDeviceName()`
  - New web API endpoints: `GET /device_name`, `POST /device_name?name=X`
  - Web UI section for device name configuration with live preview
  - Automatic mDNS restart when name changes
  - OTA hostname synchronized with mDNS name
- **Configuration**: New constants in `config.h`:
  - `DEFAULT_DEVICE_NAME "garland"`
  - `MAX_DEVICE_NAME_LEN 32`
- **Files**: [include/config.h](include/config.h), [include/garland_control.h](include/garland_control.h), [src/garland_control.cpp](src/garland_control.cpp), [src/main.cpp](src/main.cpp), [include/web_interface.h](include/web_interface.h), [src/web_interface.cpp](src/web_interface.cpp), [src/web_pages.cpp](src/web_pages.cpp)

### Changed

**Web Interface Updates**
- Updated WiFi info section to display mDNS name
- Added device name configuration card with validation
- Updated `/status` endpoint to include `device_name` field
- Updated dashboard to show `http://[device-name].local` access URL

**Documentation Updates**
- Comprehensive mDNS documentation added to `README.md` and `README_FR.md`
- New section "Web Interface and Network Access" with access methods
- Updated all version numbers to 1.12.0
- Created release notes: [docs/RELEASE_v1.12.0.md](docs/RELEASE_v1.12.0.md)
- Restructured README sections for better organization

**Version Bumps**
- All source file headers updated to v1.12.0
- Build configuration updated in `platformio.ini`

### Version

- **SEMVER Classification**: MINOR (1.12.0) - New feature (mDNS) with backward compatibility

---

# [1.11.4] – 2026-01-05 (Previous Pin Mapping Change)

### Changed (MAJOR - Pin Mapping Change)

**NeoPixel 8x8 Matrix - Pin Change**
- **Modification**: MATRIX8X8_PIN moved from GPIO 13 to GPIO 34
- **Reason**: Eliminated pin sharing conflict with TB6612_PWMA (GPIO 13)
- **Impact**: 
  - NeoPixel 8x8 matrix now operates on dedicated pin (GPIO 34)
  - No more conflict between garland (TB6612_PWMA) and matrix
  - Both peripherals can operate simultaneously without issues
- **Required Action**: 
  - ⚠️ **Physical wiring must be changed**: Move matrix data wire from GPIO 13 to GPIO 34
  - Recompile and upload firmware
- **Files**: [include/board_config.h](include/board_config.h)

### Version

- **SEMVER Classification**: MAJOR (1.12.0) - Hardware pin mapping change requiring physical reconfiguration

---

# [1.11.4] – 2026-01-05

### Fixed (PATCH - Web Interface and Code Architecture)

**1. Header File Structure**
- **Issue**: File `include/web_pages.h` contained executable code (`html +=` statements) instead of function declarations
- **Error**: `error: 'html' does not name a type` during compilation
- **Solution**: Complete cleanup of `web_pages.h` (162 lines → 35 lines) to keep only function declarations
- **Impact**: Clean architecture compliant with C++ standards (header/source separation)
- **Files**: [include/web_pages.h](include/web_pages.h)

**2. Global Constant Declarations**
- **Issue**: Constant `WEB_STYLES` in `include/web_styles.h` caused multiple definition errors
- **Error**: Multiple definition error during linking
- **Solution**: Added `static constexpr` to ensure single definition
- **Files**: [include/web_styles.h](include/web_styles.h)

**3. Header Include Order**
- **Issue**: `#include "web_pages.h"` was placed after code using it in `src/web_pages.cpp`
- **Solution**: Moved include to the beginning of source file
- **Impact**: Proper dependency resolution
- **Files**: [src/web_pages.cpp](src/web_pages.cpp)

**4. Web Interface - Complete Rebuild**
- **Issue**: All web interface commands were missing (animations, detector, screen, 8x8 matrix)
- **Solution**: Complete reconstruction of `generateDashboardPage()` function with:
  - Garland animation selector (radio buttons for each animation)
  - Operation modes (MANUAL, AUTO, MOTION) with parameters
  - Auto interval and motion duration settings
  - Matrix 8x8 controls (animation selection + brightness slider)
  - LCD display modes (selector with preview)
  - Save/Load/Erase configuration buttons
  - System information (Chip ID, Flash, RAM, PSRAM, CPU)
  - WiFi information (SSID, IP, signal)
  - JavaScript handlers for all interactions
- **Impact**: Complete and functional user interface
- **Files**: [src/web_pages.cpp](src/web_pages.cpp)

**5. Display Mode Management**
- **Issue**: HTTP parameter for display mode was named `"mode"` instead of `"id"`
- **Solution**: Modified `handleSetDisplayMode()` to accept `"id"` parameter
- **Impact**: Consistency with other endpoints and web interface
- **Files**: [src/web_interface.cpp](src/web_interface.cpp)

**6. Display Mode Name Retrieval Function**
- **Issue**: Function `getDisplayModeNameById(int id)` was missing for displaying names in interface
- **Error**: `'getDisplayModeNameById' was not declared in this scope`
- **Solution**: Added function in `garland_control.cpp` and declaration in `garland_control.h`
- **Impact**: Correct labels in display mode selector
- **Files**: [src/garland_control.cpp](src/garland_control.cpp), [include/garland_control.h](include/garland_control.h)

**7. C++ Syntax Correction**
- **Issue**: Function `getDisplayModeNameById()` was initially nested inside `getDisplayModeName()`
- **Error**: `a function-definition is not allowed here before '{' token`
- **Solution**: Restructured to place both functions at same indentation level
- **Impact**: Code compliant with C++ syntax rules
- **Files**: [src/garland_control.cpp](src/garland_control.cpp)

### Build

**Result**: ✅ Build successful
- RAM: 15.8% (51,644 / 327,680 bytes)
- Flash: 79.9% (1,047,189 / 1,310,720 bytes)
- Firmware generated: `firmware.bin` ready for upload

### Version

- **SEMVER Classification**: PATCH (1.11.4) - Architecture bug fixes and restoration of missing functionality

---

# [1.11.3] – 2026-01-01

### Fixed (PATCH - Animation Quality Improvements)

**Matrix Rain Animation**
- **Issue**: Animation only used top 2 rows, not utilizing full 8x8 display
- **Solution**: Completely redesigned with independent falling streams per column
- **Features**: Each column has different speed, staggered start positions, proper brightness gradient
- **Result**: Full height usage with smooth, dynamic Matrix-style rain effect
- **Files**: `src/matrix8x8_control.cpp:1582-1638`

**Clock Animation**
- **Issue**: Messy design with cluttered appearance and poor readability
- **Solution**: Redesigned with clean circular outline and clear visual hierarchy
- **Features**:
  - Blue-tinted circular clock face outline
  - Gold hour markers at 12, 3, 6, 9 positions (2-pixel each)
  - Elegant blue-gray center point
  - Smooth red second hand with 60-second rotation
- **Result**: Much cleaner, more elegant, and easier to read
- **Files**: `src/matrix8x8_control.cpp:1211-1279`

### Version

- **SEMVER Classification**: PATCH (1.11.3) - Bug fixes and visual improvements, no new features

---

# [1.11.2] – 2026-01-01

### Fixed (PATCH - Coordinate System Correction)

**Matrix Coordinate Mapping System**
- **Issue**: Matrix used zigzag indexing pattern (even rows left→right, odd rows right→left)
- **Problem**: Caused incorrect pixel positioning and visual distortions in animations
- **Solution**: Implemented uniform linear indexing (all rows 0-7 go left→right)
- **Impact**: All 38 matrix animations now display correctly with proper coordinate alignment
- **Files**: `src/matrix8x8_control.cpp:88-108`

### Technical

**Coordinate System Specification**
- All rows now follow the same pattern: pixels 0-7 (left to right)
- Row 0: pixels 0-7
- Row 1: pixels 8-15
- Row 2: pixels 16-23
- Row 3: pixels 24-31
- Row 4: pixels 32-39
- Row 5: pixels 40-47
- Row 6: pixels 48-55
- Row 7: pixels 56-63

**Modified Function**
```cpp
static uint16_t xy(uint8_t x, uint8_t y) {
    if (x >= 8 || y >= 8) return 0;
    return y * 8 + x;  // Linear: all rows left to right
}
```

### Version

- **SEMVER Classification**: PATCH (1.11.2) - Bug fix, corrects coordinate mapping, no new features

---

# [1.11.1] – 2026-01-01

### Fixed (PATCH - Synchronization)

**Matrix Auto Mode Interval Synchronization**
- **Issue**: Matrix auto mode used fixed 30-second interval, not synchronized with garland auto mode
- **Solution**: Matrix now uses `getAutoAnimationIntervalMs()` from garland control
- **Result**: Both garland and matrix auto modes now share the same interval, configurable via web UI
- **Benefit**: Single UI control adjusts animation duration for both garland and matrix simultaneously
- **Files**: `src/matrix8x8_control.cpp:21,1967-1983`

### Technical

- Removed separate `autoModeInterval` variable from matrix control
- Matrix auto mode now calls `getAutoAnimationIntervalMs()` to get shared interval
- Default interval: 30 seconds (configurable from 5s to 5 minutes via web UI)
- Log output now displays current interval when switching animations

### Version

- **SEMVER Classification**: PATCH (1.11.1) - Bug fix, improved synchronization, no new features

---

# [1.11.0] – 2026-01-01

### Added (MINOR - New Features + Major Animation Improvements)

**NEW FEATURE: Auto Mode for Matrix**
- **Description**: Automatic cycling through all matrix animations
- **Behavior**: Cycles every 30 seconds through all animations (excluding OFF)
- **Implementation**: New enum `MATRIX_ANIM_AUTO`, auto mode logic in `updateMatrix8x8()`
- **UI**: New "Auto" option in matrix animation selection
- **Files**: `include/matrix8x8_control.h:78`, `src/matrix8x8_control.cpp:17-24,1836-1855,1971-1978`

### Fixed (CRITICAL - Detection Mode + Animations)

**CRITICAL FIX #1: Detection Mode Matrix Re-activation**
- **Issue**: In MODE_MOTION_TRIGGER, matrix didn't turn back on after motion detection because `matrixEnabled` was set to false
- **Root Cause**: `matrix8x8Off()` permanently disabled matrix by setting `matrixEnabled = false`
- **Solution**: Modified `updateMatrix8x8()` to clear matrix without changing `matrixEnabled` flag during motion timeout
- **Result**: Matrix now correctly turns back on when motion is detected, preserving animation and brightness settings
- **Files**: `src/matrix8x8_control.cpp:1811-1834`

**Animation Improvements (14 animations fixed/enhanced):**

1. **Candy Cane** - Complete redesign with realistic candy cane shape
   - **Before**: Generic diagonal stripes across entire matrix
   - **After**: Proper candy cane with curved hook at top, straight stick, rotating red/white diagonal stripes
   - **File**: `src/matrix8x8_control.cpp:670-713`

2. **Clock** - Professional analog clock with proper hour markers
   - **Before**: Simplified circle with erratic hand
   - **After**: 12-hour markers (12,3,6,9 bright white, others dim gray), smooth 60-second clockwise sweep, hand changes red when passing hours
   - **File**: `src/matrix8x8_control.cpp:1154-1215`

3. **Bunny** - Added animated eyes
   - **Before**: Eyes missing
   - **After**: Black eyes that move with bunny hop, blinking animation every 2 seconds
   - **File**: `src/matrix8x8_control.cpp:1274-1370`

4. **Flower** - Realistic blooming flower animation
   - **Before**: Static small flowers
   - **After**: Two side-by-side flowers with 8 petals each, smooth opening/closing bloom cycle, green stems
   - **File**: `src/matrix8x8_control.cpp:1330-1441`

5. **Meteor** - Full diagonal matrix coverage
   - **Before**: Vertical falling only, top 3 rows only
   - **After**: Diagonal meteors across full 8x8 matrix, 3 meteors at different stages, realistic trailing effect
   - **File**: `src/matrix8x8_control.cpp:388-425`

6. **Santa** - Highly recognizable Santa face
   - **Before**: Abstract pattern
   - **After**: Red hat with white trim and pom-pom, skin tone face, blinking black eyes, red nose, white beard with mustache gap
   - **File**: `src/matrix8x8_control.cpp:462-512`

7. **Gift** - Clear gift box with ribbon and bow
   - **Before**: Unclear pattern
   - **After**: Color-cycling box (red/green/blue), gold ribbon cross, sparkling bow on top
   - **File**: `src/matrix8x8_control.cpp:615-659`

8. **Snowflake** - Added heartbeat pulse effect
   - **Before**: Constant brightness
   - **After**: Double-pulse heartbeat pattern (two quick pulses, pause, repeat), cyan color maintained
   - **File**: `src/matrix8x8_control.cpp:694-743`

9. **Rainbow Wave** - True sine wave animation
   - **Before**: Static vertical rainbow stripes
   - **After**: Animated sine wave with rainbow colors, smooth horizontal movement, vertical gradient effect
   - **File**: `src/matrix8x8_control.cpp:1519-1555`

10-14. **Minor refinements**: Matrix Rain (verified full height), Plasma (optimized), Radar (improved), Stocking (from v1.10.0), Countdown (from v1.8.1)

### Removed

**Removed Animation: Icicles**
- **Reason**: User request - animation to be removed from available options
- **Impact**: Total animations: 39 → 38 (plus Auto mode = 39 selectable options)
- **Files Modified**:
  - Enum: `include/matrix8x8_control.h:52` (removed MATRIX_ANIM_ICICLES)
  - Names array: `src/matrix8x8_control.cpp:56` (removed "Icicles")
  - Function: `src/matrix8x8_control.cpp:986-1017` (removed animateIcicles())
  - Switch case: `src/matrix8x8_control.cpp:2041-2043` (removed case)

### Changed

**Animation Count:**
- **Before**: 39 animations (including Icicles)
- **After**: 38 animations + Auto mode = 39 total selectable options

**Detection Behavior:**
- **MODE_PERMANENT**: No changes (both always on)
- **MODE_MOTION_MATRIX_INDEPENDENT**: No changes (garland motion-based, matrix always on)
- **MODE_MOTION_TRIGGER**: **FIXED** - Both turn off after timeout, **both turn back on** with detection (preserving settings)

### Technical

- **Auto Mode Variables**: Added `autoModeActive`, `autoModeChangeTime`, `autoModeInterval`, `activeAnimation`
- **Matrix State Management**: Separated user control (`matrixEnabled`) from motion-based visibility
- **Animation Execution**: Auto mode executes `activeAnimation`, manual mode executes `currentAnimation`
- **NVS Persistence**: Auto mode selection saved and restored across reboots
- **Animation Quality**: All fixed animations now use full 8x8 matrix appropriately

### Version

- **SEMVER Classification**: MINOR (1.11.0) - New features, significant fixes, backwards compatible
- **All Files Updated**: Updated version string to 1.11.0 in all headers, source files, platformio.ini, and documentation

---

# [1.10.0] – 2026-01-01

### Added (MINOR - New Animations + UX Improvements)

**New Matrix Animations:**

- **NEW ANIMATION #1: Campfire**
  - **Description**: Realistic fire simulation with heat propagation algorithm
  - **Features**: Heat map with 64 cells, upward heat diffusion, color gradient (red→orange→yellow→white)
  - **Visual**: Flames rise from bottom rows with organic flickering movement
  - **File**: `src/matrix8x8_control.cpp:1529-1598`

- **NEW ANIMATION #2: Radar**
  - **Description**: Military-style green radar sweep with blips
  - **Features**: Rotating sweep line, fading trail, concentric grid circles, random appearing/fading blips
  - **Visual**: Classic radar screen with smooth sweep and target detection
  - **File**: `src/matrix8x8_control.cpp:1603-1694`

- **ANIMATION REDESIGN: Stocking** (Christmas)
  - **Issue**: Previous design unrecognizable, poor visual clarity
  - **Solution**: Complete rewrite with clear stocking shape
  - **New Features**: White cuff, red body with green decorative stripe, gold sparkle, hanging hook, realistic pendulum swing
  - **Visual**: Now clearly identifiable as Christmas stocking with festive colors
  - **Files**: `src/matrix8x8_control.cpp:240-250` (pattern), `727-788` (function)

### Changed

- **Web UI: No More Page Reloads (CRITICAL UX FIX)**
  - **Issue**: Page reload caused white flash and jarring user experience
  - **Solution**: Removed all `location.reload()` calls, implemented AJAX updates
  - **New Functions**: `updateCurrentAnimation()`, `updateCurrentMode()`, `updateCurrentMatrix()`
  - **Result**: Smooth, flash-free UI updates when changing animations/modes
  - **Files**: `include/web_pages.h:201-241`

### Technical

- **Total Animations**: 37 → 39 (Campfire + Radar added)
- **Animation Enum**: Updated `Matrix8x8Animation` enum with `MATRIX_ANIM_CAMPFIRE` and `MATRIX_ANIM_RADAR`
- **Animation Names**: Added "Campfire" and "Radar" to `animationNames[]` array
- **Switch Cases**: Added handlers in `updateMatrix8x8()` function
- **DOM Updates**: JavaScript now updates UI elements dynamically without full page refresh
- **Visual Feedback**: Radio button selections update instantly with CSS class changes

### Version

- **SEMVER Classification**: MINOR (1.10.0) - New animations + significant UX improvements, no breaking changes
- **All Files Updated**: Updated version string in all headers, source files, and platformio.ini

---

# [1.9.0] – 2026-01-01

### Changed (MINOR - UI Improvements)

**Web Interface Modernization:**

- **IMPROVEMENT #1: Radio Buttons Replace Dropdowns**
  - **What**: Replaced all dropdown selects with radio button grids for better UX
  - **Affected**: Matrix animations (37 options), Garland modes (3 options), Garland animations (11 options)
  - **Benefit**: Immediate visual overview of all options, no need to open dropdowns
  - **Files**: `include/web_pages.h:62-89,91-110,145-159`, `include/web_styles.h:39-47`

- **IMPROVEMENT #2: Responsive 2-Column Layout**
  - **What**: Radio buttons display in 2 columns on wide screens, 1 column on narrow screens
  - **Breakpoint**: 600px width (mobile-first responsive design)
  - **CSS**: `.radio-grid { grid-template-columns: repeat(2, 1fr); }` with media query
  - **Files**: `include/web_styles.h:39-40`

- **IMPROVEMENT #3: Instant Selection (No Apply Buttons)**
  - **What**: Removed all "Appliquer" buttons - selections apply immediately via `onchange` events
  - **Benefit**: Reduced clicks, faster interaction, modern web app feel
  - **Technical**: JavaScript functions now accept ID parameter directly from radio button
  - **Files**: `include/web_pages.h:201-220`

- **IMPROVEMENT #4: Enhanced Visual Feedback**
  - **What**: Selected radio items highlighted with green background and border
  - **CSS**: `.radio-item.selected { background:#e8f5e9; border-color:#43a047; }`
  - **Hover Effect**: Radio items highlight on hover for better interactivity
  - **Files**: `include/web_styles.h:41-46`

- **IMPROVEMENT #5: Validation Message Timing**
  - **What**: Reduced message display time from 3s to 2.5s for snappier UI
  - **Files**: `include/web_pages.h:199,215`

### Fixed

- **BUGFIX #8: Missing 3rd Mode in Web UI**
  - **Issue**: `MODE_MOTION_MATRIX_INDEPENDENT` (3rd mode) not appearing in dropdown, line stayed white
  - **Fix**: Added missing switch case: `case MODE_MOTION_MATRIX_INDEPENDENT: modeName = "Détection (guirlande)";`
  - **File**: `include/web_pages.h:99`

### Technical

- **CSS Additions**: 8 new CSS classes for radio button styling and responsive grid
- **HTML Structure**: Replaced `<select>` + `<option>` with `<div class='radio-grid'>` + radio inputs
- **JavaScript Changes**: Functions now accept value parameter instead of reading from select element
- **Compact Design**: UI remains visually compact despite adding 51 total radio buttons
- **Accessibility**: Labels properly associated with radio inputs via `for` attribute
- **Mobile Optimized**: Single-column layout prevents horizontal scrolling on small screens

### Version

- **SEMVER Classification**: MINOR (1.9.0) - New features and UI improvements, no breaking changes
- **All Files Updated**: Updated version string in 13 files (headers, source, platformio.ini)

---

# [1.8.1] – 2026-01-01

### Fixed (PATCH - Bug Fixes Only)

**7 Numbered Bug Fixes:**

- **BUGFIX #1: Matrix Rain Animation**
  - **Issue**: Bottom LED rows not visible due to aggressive fade
  - **Fix**: Reduced fade intensity from 220 to 245 to preserve bottom rows
  - **File**: `src/matrix8x8_control.cpp:1401`

- **BUGFIX #2: Clock Animation**
  - **Issue**: Clock hand rotating counter-clockwise (wrong direction)
  - **Fix**: Reversed rotation direction by negating angle: `cos(-angle - PI/2)`
  - **File**: `src/matrix8x8_control.cpp:1097`

- **BUGFIX #3: Countdown Animation**
  - **Issue**: Digits 3, 2, 1 unreadable on 8x8 matrix
  - **Fix**: Completely redrawn all three digits with clearer, larger patterns
  - **File**: `src/matrix8x8_control.cpp:1004`

- **BUGFIX #4: Icicles Animation**
  - **Issue**: Incomplete animation - only 4 icicles, weak dripping effect
  - **Fix**: Added all 8 icicles with varying lengths + proper animated water drops
  - **File**: `src/matrix8x8_control.cpp:854`

- **BUGFIX #5: Candle Animation**
  - **Issue**: Base too narrow (2px), flame too wide (4px), unrealistic proportions
  - **Fix**: Widened base to 4 pixels (x=2-5), narrowed flickering flame to 2 pixels (x=3-4)
  - **File**: `src/matrix8x8_control.cpp:595`

- **BUGFIX #6: Bell Animation**
  - **Issue**: Entire bell deforming/moving, not realistic
  - **Fix**: Bell stays fixed, only clapper (pendulum) swings inside
  - **File**: `src/matrix8x8_control.cpp:501`

- **BUGFIX #7: Web UI Layout**
  - **Issue**: Inline messages cause button/list displacement when appearing
  - **Fix**: Reserved space with `visibility:hidden` + `min-height:44px` instead of `display:none`
  - **Files**: `include/web_pages.h:60,121,136,188,206,220`

### Changed
- **Version number**: Incremented to 1.8.1 (SEMVER - PATCH: bug fixes only)

### Technical
- Animation improvements target better visual recognition on 8x8 matrix constraints
- Web UI now maintains stable layout preventing element shifts
- All fixes maintain backward compatibility

---
# [1.8.0] – 2026-01-01

### Added
- **New Garland Mode**: `MODE_MOTION_MATRIX_INDEPENDENT` - Garland is triggered by motion detection while matrix stays always on
- **Matrix Synchronization**: Matrix now follows garland state in `MODE_MOTION_TRIGGER` mode (turns off/on together)
- **Enhanced Mode Labels**: Clearer mode names - "Permanent", "Detection (tout)", "Detection (guirlande)"
- **Matrix-Garland Coordination**: Matrix behavior now respects garland operating mode for better user control

### Fixed
- **CRITICAL: GPIO Pin Mapping**: Restored 8x8 matrix GPIO from 13 back to **32** (correct pin for hardware compatibility)
- **CRITICAL: Animation Timing Bugs**: Fixed 8 animations using broken `elapsed % N == 0` timing that prevented display
  - Fixed animations: Meteor, Shooting Star, Snow, Champagne, Confetti, Sparkle Rain, Matrix Rain, Stars Field
  - Replaced with reliable threshold-based timing using static `lastUpdate` variables
  - Animations now update every cycle regardless of loop timing variations
- **Web Handler Logging**: Added comprehensive debug logging to matrix API handlers for better troubleshooting

### Changed
- **Version number**: Incremented to 1.8.0 (SEMVER - MINOR: new features + critical bug fixes)
- **Mode Behavior**: `MODE_PERMANENT` - both always on | `MODE_MOTION_TRIGGER` - both follow motion | `MODE_MOTION_MATRIX_INDEPENDENT` - only garland follows motion
- **Code Organization**: Matrix control now includes garland state awareness via `isGarlandEnabled()`

### Technical
- Added `MODE_MOTION_MATRIX_INDEPENDENT` to `GarlandMode` enum
- New function: `isGarlandEnabled()` exposes garland state to matrix controller
- Modified `updateMatrix8x8()` to check garland mode and state before updating
- Enhanced `updateGarland()` with better mode-specific logging
- Fixed timing pattern: `if (currentMillis - lastUpdate >= interval)` replaces `if (elapsed % interval == 0)`
- Added `#include "garland_control.h"` to `matrix8x8_control.cpp` for mode access

### Documentation
- Updated all FR/EN documentation with new mode descriptions
- Documented motion detection behavior for both garland and matrix
- Added technical notes on GPIO pin requirements and timing fixes

---
# [1.7.0] – 2026-01-01

### Added
- **27 New Matrix Animations**: Expanded from 10 to 37 total festive animations for 8x8 NeoPixel matrix
- **Christmas Animations (10)**: Candy Cane, Wreath, Stocking, Reindeer, Gingerbread Man, Hot Cocoa, Fireplace, Icicles, Northern Lights, Presents Stack
- **New Year Animations (7)**: Fireworks, Champagne Bubbles, Countdown 3-2-1, Confetti, Clock, Party Popper, Disco Ball
- **Easter Animations (4)**: Easter Egg, Hopping Bunny, Hatching Chick, Spring Flowers
- **Modern/Abstract Animations (6)**: Rainbow Wave, Sparkle Rain, Plasma Effect, Matrix Digital Rain, Rotating Spiral, Pulsing Heart, Twinkling Stars Field

### Changed
- **Version number**: Incremented to 1.7.0 (SEMVER - MINOR: significant new features)
- **Total Animation Count**: Now 48 total animations (11 garland + 37 matrix)
- **Matrix Animation Categories**: Organized into Original, Christmas, New Year, Easter, and Modern/Abstract themes
- **Documentation**: Complete update of all FR/EN documentation with new animations

### Technical
- Enhanced `matrix8x8_control.h` with 27 new animation enums
- Added 27 new animation functions in `matrix8x8_control.cpp`
- New animation patterns: Wreath, Stocking, Reindeer, Gingerbread, Heart, Easter Egg, Bunny, Chick, Flower
- All animations optimized for 8×8 LED matrix with smooth transitions
- Realistic effects: plasma, northern lights, fireworks, champagne bubbles, digital rain

---
# [1.6.0] – 2026-01-01

### Added
- **8x8 NeoPixel Matrix WS2812B-64**: Full support for 8x8 LED matrix on GPIO 13
- **10 Festive Animations for Matrix**: Star, Meteor, Shooting Star, Santa, Christmas Tree, Bell, Falling Snow, Gift Box, Candle, Snowflake
- **Sparkling Star Startup Animation**: Matrix automatically displays a twinkling star animation on boot
- **Matrix Brightness Control**: Independent brightness control for the 8x8 matrix (0-255)
- **Web UI for Matrix**: Dedicated card in web interface for matrix animation selection and brightness adjustment
- **Matrix NVS Persistence**: Matrix settings (animation, brightness) saved to NVS
- **Dual Animation System**: Garland and matrix run independently with separate controls

### Changed
- **Version number**: Incremented to 1.6.0 (SEMVER - MINOR: new feature)
- **GPIO Configuration**: Added GPIO 13 for 8x8 NeoPixel matrix in `board_config.h`
- **Web Interface**: Added "✨ Matrice 8x8 NeoPixel" card with animation selector and brightness slider
- **Status API**: Extended `/status` endpoint with matrix_animation, matrix_animation_id, matrix_brightness
- **Documentation**: Complete update of all FR/EN documentation with 8x8 matrix features

### Technical
- New files: `matrix8x8_control.h`, `matrix8x8_control.cpp`
- New API endpoints: `/matrix_animation?id=X`, `/matrix_brightness?value=X`
- Matrix uses Adafruit_NeoPixel library with 64 pixels (8×8)
- XY coordinate mapping function for zigzag wiring pattern
- Festive animation patterns defined as 8×8 bitmaps
- Separate NVS namespace "matrix8x8" for matrix settings
- Real-time status refresh includes both garland and matrix animations

---
# [1.5.3] – 2025-12-31

### Changed
- **Reboot message positioning**: Message now uses absolute positioning at top-right, buttons no longer shrink or move
- **OTA update confirmation**: Replaced blocking `confirm()` popup with double-click confirmation (5-second timeout)
- OTA button text changes to "⚠️ Click again to confirm update" on first click
- Warning message appears below OTA button after first click

### Fixed
- UI layout: Reboot confirmation message no longer causes button displacement
- UX: Buttons maintain fixed width regardless of message display state
- OTA: Removed blocking `alert()` popups for file validation errors
- OTA: File validation errors now display as inline status messages

### Technical
- Reboot message: Changed from flexbox to `position:absolute` with `top:0;right:0`
- Reboot message: Added shadow and max-width for better visibility
- OTA: Converted form submit to button click handler `handleUpload()`
- OTA: Added `uploadConfirmed` state variable for double-click logic
- OTA: Replaced alert() with inline statusMessage display

---
# [1.5.2] – 2025-12-31

### Added
- **Inline confirmation for animation changes**: Displays "✓ Animation changed: [Name]" when selecting a new animation
- **Inline confirmation for mode changes**: Displays "✓ Mode changed: [Name]" when switching modes
- Improved visual feedback for all user actions in web interface

### Changed
- **Reboot confirmation message positioning**: Message now appears to the right of buttons instead of below
- Reboot message uses flexbox layout to prevent button displacement
- All confirmations now use consistent 3-second auto-dismiss timing
- Page reload delayed by 1 second after animation/mode change to show confirmation

### Technical
- Added `showParamMessage()` function for animation/mode confirmations
- Modified `changeAnimation()` to extract and display animation name
- Modified `changeMode()` to extract and display mode name
- Reboot message container uses `display:flex` for proper alignment
- CSS improvements for inline message positioning

---
# [1.5.1] – 2025-12-31

### Fixed
- **Critical bug**: Startup animation now works correctly even when saved animation is OFF
- Animation logic now correctly uses `activeAnimation` instead of `currentAnimation` for runtime checks
- Intro animation is no longer blocked by OFF animation in saved settings

### Technical
- Modified `updateGarland()`: Changed test from `currentAnimation == ANIM_OFF` to `activeAnimation == ANIM_OFF`
- This ensures the intro animation plays regardless of saved animation state

---
# [1.5.0] – 2025-12-31

### Added
- **Automatic startup animation**: 10-second intro animation (Fade Alternate) starts immediately on boot
- **Automatic transition**: After intro, automatically switches to saved animation and mode
- **Inline confirmation messages**: All save/restore/erase operations display inline confirmations (no blocking popups)
- **Double-click reboot confirmation**: Reboot button requires two clicks for safety (5-second timeout)

### Changed
- Startup behavior: Animation starts immediately, even in motion detection mode
- Web interface: Removed all blocking alert() and confirm() popups
- Reboot button: Added visual feedback (color change) on first click
- User experience: Non-blocking confirmations improve workflow
- Version number incremented to 1.5.0 (SEMVER - MINOR)

### Fixed
- Startup issue: Garland now animates immediately instead of waiting for user interaction
- Reboot reliability: Double confirmation prevents accidental reboots
- Motion detection mode: Intro animation plays before motion detection activates

### Technical
- Added `INTRO_ANIMATION_DURATION` constant (10 seconds)
- Added `introAnimationActive`, `savedAnimation`, `savedMode` state variables
- Modified `setupGarland()` to start intro animation immediately
- Modified `updateGarland()` to handle intro-to-saved transition
- JavaScript functions for inline messages: `showMessage()`, `saveSettings()`, `loadSettings()`, `eraseSettings()`
- JavaScript reboot confirmation with timeout: `rebootDevice()`

---
# [1.4.0] – 2025-12-31

### Added
- **Web-based OTA update system**: Upload firmware (.bin) directly from the browser
- Dedicated web page `/update` with intuitive interface for firmware upload
- Real-time progress display (progress bar, percentage)
- Uploaded file validation (check .bin extension)
- Update status display on ST7789 screen (progress, success, failure)
- Complete error handling with clear messages
- Automatic reboot after successful update
- Quick access button to OTA update from the dashboard

### Changed
- Version number incremented to 1.4.0 (SEMVER)
- User documentation completed with Web OTA instructions (EN/FR)
- ArduinoOTA kept as alternative method (PlatformIO OTA)

### Technical
- Using native ESP32 `Update.h` for firmware flashing
- Upload handler with optimized memory management (chunked upload)
- JavaScript interface for asynchronous upload with XMLHttpRequest
- Client-side and server-side validation

---
# [1.3.0] – 2025-12-31

### Added
- OTA (Over-the-Air) firmware update support using ArduinoOTA
- Documentation and user guides updated (EN/FR)

### Changed
- Version number incremented to 1.3.0 (SEMVER)

---
# [1.2.2] - 2025-12-31

### Changed
- Suppression de toutes les références à ESP32-S3 et environnements associés dans la documentation (FR/EN)
# [1.2.1] - 2025-12-31

### Added
- Support for auto-detection of motion sensor (PIR HC-SR501 or RCWL-0516) on GPIO 35
- Updated technical and user documentation (EN/FR)

### Changed
- Pin mapping: PIR_SENSOR replaced by MOTION_SENSOR_PIN (GPIO 35)
- All references to LDR/photoresistor removed (feature dropped)
- Mapping tables and guides adapted to actual supported hardware
- Troubleshooting and guides updated for new sensor logic

### Fixed
- Documentation consistency (EN/FR)
- Version numbers and dates in all documents

### Removed
- All code and documentation related to LDR/photoresistor
- Support for obsolete screens and boards (only ESP32 Classic + ST7789 supported)

---
### [1.1.0] - 2024-06-XX
#### Added
- Automatic save/restore of user configuration (mode, animation, intervals) using NVS. Settings persist across reboots and power cycles.
# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/).


## [1.1.0] - 2025-12-30

### ♻️ Clean & Documentation
- Removed all LDR/photoresistor references from code and documentation (project now PIR-only)
- Updated all user and technical documentation (EN + FR) for full hardware, wiring, and usage clarity
- Version numbers updated everywhere (SEMVER)
- Full consistency between code, docs, and hardware mapping

---

## [1.0.0] - 2025-12-30

### 🎯 Major Refactoring: ESP32 IdeaSpark 1.14" LCD Platform

This release represents a complete platform unification focusing exclusively on the ESP32 IdeaSpark board with integrated ST7789 LCD display.

### ✨ Added
- **ST7789 Display Module** - Complete rewrite of display system for 1.14" TFT LCD (135x240px)
  - Modern boot screen with project name, version, and WiFi connection progress bar
  - Optimized main UI with centered headers, compact mode/animation info, and large animation zone
  - 11 distinct animated visualizations (one per animation) with smooth frame-based rendering
  - Rounded rectangles, vibrant colors (yellow/blue gradients), and modern visual effects
  - Real-time animation updates at 10 FPS for fluid display
  - "AUTO" mode visual with orbiting circles, "Heartbeat" with double-pulse effect
  - Enhanced "Fade Alternate" with yellow/blue bars, "Wave" with larger amplitude
  - Dedicated "OFF" state display with centered red text

- **ESP32 IdeaSpark Board Configuration** - New unified hardware mapping
  - Complete pin definitions for integrated 1.14" ST7789 LCD (MOSI, SCLK, CS, DC, RST, BLK)
  - TB6612FNG motor driver pins optimized for IdeaSpark (AIN1 moved to GPIO 25 to avoid LCD_BLK conflict)
  - PIR motion sensor on GPIO 35 (input-only pin, perfect for sensor)
  - User buttons on GPIO 16 and 17
  - I2C bus available on GPIO 21/22 for future expansion

### 🔄 Changed
- **Platform Unification** - Simplified to single ESP32 platform
  - Removed ESP32-S3 environments (esp32s3_n16r8, esp32s3_n8r8)
  - Kept only `esp32devkitc` environment with ESP32 IdeaSpark configuration
  - Updated PlatformIO configuration for single-board focus
  - Board name: "ESP32 IdeaSpark 1.14 LCD"

- **Display Architecture** - Complete modernization
  - Replaced all `updateOledAnimationStatus()` calls with `displayMainScreen()`
  - Removed display.h forward declarations in favor of proper includes
  - Added `display.h` include to web_interface.h for proper function visibility
  - Simplified display API to 4 core functions: `setupDisplay()`, `displayBootScreen()`, `displayMainScreen()`, `updateAnimationVisual()`

- **UI Layout Optimization** - Maximized screen real estate
  - Removed WiFi SSID/IP from main screen (shown only during boot)
  - Reduced header height by 14 pixels (compact text, optimized spacing)
  - Moved mode/animation info higher and more compact (saved 10 pixels)
  - Increased animation zone from 67px to 81px height (+20% larger visual area)
  - Application name and version centered at top for professional look
  - Clean separator lines for visual hierarchy

### 🐛 Fixed
- **Motion Detection Timer** - Critical fix for detection mode
  - Implemented edge detection using `lastMotionState` variable
  - Timer now triggers only on rising edge (LOW→HIGH transition)
  - Prevents continuous timer reset when PIR sensor stays HIGH
  - Animations now properly stop after configured duration (default 30 seconds)
  - Added debug logging every 5 seconds showing timer status and elapsed time
  - Fixed issue where "detect" mode never turned off animations

- **Build Errors** - Multiple compilation fixes
  - Removed LDR sensor support (`LDR_SENSOR` undefined errors fixed)
  - Updated all Telegram control display calls to new API
  - Fixed missing `display.h` include in web_interface.h
  - Corrected function signature mismatches across modules

### ❌ Removed
- **Legacy Display Support** - Complete removal of obsolete display code
  - Removed all OLED (SSD1306) display code and configuration
  - Removed all TFT and ILI9341 display code
  - Removed Adafruit SSD1306 library dependency from platformio.ini
  - Removed `HAS_OLED` configuration flag from config.h
  - Kept only `HAS_ST7789` display flag

- **Multi-Platform Code** - Simplified board support
  - Removed ESP32-S3 specific configurations and pin mappings
  - Removed multi-board conditional compilation complexity
  - Removed unused display stub functions

- **LDR Sensor** - Light detection hardware removed
  - Removed `LDR_SENSOR` pin definitions from board_config.h
  - Removed `pinMode(LDR_SENSOR, INPUT)` from `setupGarland()`
  - Modified `getLightLevel()` to return 0 (sensor removed)
  - Simplified sensor array to PIR motion detection only

### 📦 Dependencies
- **Updated Library Requirements**:
  - Adafruit NeoPixel @ ^1.12.0
  - ArduinoJson @ ^7.0.3
  - OneButton @ ^2.5.0
  - Adafruit GFX Library @ ^1.11.9
  - Adafruit ST7735 and ST7789 Library @ ^1.11.0
  - ❌ Removed: Adafruit SSD1306

### 🔧 Technical Details
- **Display Specifications**:
  - Resolution: 135×240 pixels (landscape orientation with rotation=1)
  - Color depth: RGB565 (16-bit color)
  - SPI communication at hardware SPI pins
  - Backlight control via GPIO 32 (must be HIGH for visibility)
  - Animation frame rate: 10 FPS (100ms refresh interval)

- **Pin Conflicts Resolved**:
  - Moved TB6612_AIN1 from GPIO 32 to GPIO 25 (GPIO 32 needed for LCD backlight)
  - LED_BUILTIN (GPIO 2) shared with LCD_DC (acceptable as data/command pin)
  - No conflicts between display, motor driver, sensors, and buttons

- **Code Architecture**:
  - Modular display system with clear separation of concerns
  - Display module works independently with or without `HAS_ST7789` flag
  - Empty stub functions provided when ST7789 disabled for compilation safety
  - All display calls non-blocking and optimized for loop() execution

### 📊 Version Metrics
- **Flash Usage**: Optimized for ESP32 Classic (4MB flash)
- **Code Reduction**: ~15% reduction from multi-platform codebase
- **Files Modified**: 12 core files updated
- **Commits**: 7 commits consolidated into v1.0.0 release
- **Lines Changed**: +850 additions, -1200 deletions

### 🎨 Visual Enhancements
- **Boot Screen**:
  - Centered project name in cyan (size 2)
  - Version number centered below in white
  - WiFi progress bar with green fill and percentage
  - Clean separator lines for visual structure

- **Main Screen**:
  - Application name centered at top (cyan, size 1)
  - Version centered below (white, size 1)
  - Compact mode/animation labels on left (magenta/orange)
  - Large animation visualization zone (234×81 pixels)
  - Smooth animations with vibrant color schemes

- **Animation Visuals**:
  - "Fade Alternate": Yellow/blue rounded bars with brightness modulation
  - "Pulsation": Growing/shrinking purple circle
  - "Respiration": Cyan rounded rectangle with smooth fade in/out
  - "Strobe": Fast white rectangular flashes
  - "Heartbeat": Red double-pulse circle effect
  - "Wave": Cyan sinusoidal wave with larger amplitude
  - "Sparkle": 15 randomly twinkling yellow dots
  - "Meteor": Orange/yellow gradient trailing effect
  - "Auto": Green "AUTO" text with dual orbiting circles (yellow/cyan)
  - "OFF": Centered red "OFF" text on black background

### 🚀 Migration Notes
**Breaking Changes**:
- ESP32-S3 boards no longer supported - ESP32 IdeaSpark only
- OLED displays no longer supported - ST7789 LCD only
- LDR sensor removed - motion detection (PIR) only

**Upgrade Path**:
1. Hardware: Replace ESP32-S3 with ESP32 IdeaSpark 1.14" LCD board
2. Configuration: Remove any OLED/TFT configuration from secrets.h
3. Wiring: Follow new pin mapping in board_config.h
4. Compilation: Use `esp32devkitc` environment exclusively
5. Display: Enjoy new modern LCD interface with animations!

### ✅ Testing Completed
- [x] Compilation successful on esp32devkitc environment
- [x] ST7789 display initialization and rendering
- [x] Boot screen with WiFi progress bar
- [x] Main screen layout optimization (no clipping)
- [x] All 11 animation visuals rendering correctly
- [x] Motion detection timer edge detection working
- [x] Web interface display updates functional
- [x] Button controls updating display properly
- [x] Telegram controls updating display properly
- [x] No memory leaks or watchdog timer issues

---

## [0.8.0] - 2025-12-29

### 🚦 Migration convention GPIO
- Suppression du préfixe `PIN_` dans toutes les constantes de configuration GPIO (ex : `BUTTON_BOOT`, `TB6612_PWMA`, `I2C_SDA`...)
- Mise à jour de tout le code source et de la documentation pour refléter la nouvelle convention
- Mise à jour de tous les fichiers markdown, tableaux et exemples de code
- Numérotation de version synchronisée sur tous les fichiers

## [0.7.0-rc1] - 2025-12-13

### 🎨 Simplified & Festive Web UI
- Streamlined UI showing only essential garland parameters
- Christmas/New Year visual theme: red-gold-green palette, golden borders
- Duration inputs in **seconds** (auto-converted to milliseconds)
- "Validate" buttons to apply duration changes
- Dynamic explanatory note for animation count calculation in Detection+Auto mode

### 💾 NVS Save Management
- **Save** button: manual save of parameters to NVS
- **Restore** button: reload from NVS save
- **Erase** button: delete save (confirmation required)
- API endpoints: `/save`, `/load`, `/erase`

### ⚙️ Clear Parameters
- **Animation duration (Auto mode)**: display time for each animation in Auto mode
- **On-time after detection**: total time before off after motion
- WiFi SSID and IP shown in minimal network card

### 🔧 Technical Improvements
- Auto-save on animation, mode, or duration change
- API status enriched with IP address (`/status` includes `"ip"`)
- Explicit UI labels to differentiate the two duration types

## [0.6.4] - 2025-12-13

### Settings Persistence (NVS)
- Automatically saves `mode`, `animation`, `auto_interval_ms`, and `motion_duration_ms` to ESP32 NVS.
- Restores settings on boot via `loadGarlandSettings()` in `setupGarland()`.
- NVS initialized early in `setup()` with erase+reinit fallback.

### Web UI & API
- Web UI: numeric inputs to change Auto interval and Motion-off duration, prefilled with current values.
- API: new endpoints `GET /auto_interval?ms=...` and `GET /motion_duration?ms=...`; `/status` includes both values.

### Misc
- Bumped version to 0.6.4 across sources.

## [0.6.3] - 2025-12-13

### ✨ Added: 5 New Spectacular Animations
- ⚡ **Strobe**: Rapid stroboscopic flash effect - short intense flashes alternating between directions
- ♥️ **Heartbeat**: Double-beat pulsation effect (BOM-bom... BOM-bom...) mimicking a heartbeat
- 🌊 **Wave**: Smooth sinusoidal wave flowing between LED directions
- ✨ **Sparkle**: Random twinkling sparkle effect with varying brightness
- ☄️ **Meteor**: Light trail effect with progressive fade simulating a meteor passing

### 🎭 Animation Showcase
**Total animations: 11** (6 original + 5 new)
- Original: Off, Fade Alternate, Blink Alternate, Pulse, Breathing, Auto
- **New**: Strobe, Heartbeat, Wave, Sparkle, Meteor

### Technical Details
- All animations optimized for 2-wire monochrome garland with anti-parallel LEDs
- Auto mode now cycles through all 10 active animations (30s each)
- Smooth transitions and effects using TB6612FNG H-bridge control
- Added yield() calls to prevent watchdog timer issues

### User Experience
- 🎵 More visual variety for decorative lighting
- 🔄 Auto mode enriched with 5 additional effects
- 🕹️ Button 1 cycles through all 11 animations + Auto
- 💻 Web interface updated with new animation options

## [0.6.2] - 2025-12-12

### 🐞 Fixed: Auto Mode Startup
- ✅ **Auto Mode Now Starts Instantly**
  - Fixed: AUTO mode now starts immediately with first animation (Fade Alternate)
  - Eliminated 30-second blank period when selecting AUTO mode
  - Auto mode now properly appears in Button 1 animation cycle
  
### 🛠️ Technical Changes
- 💾 **Internal Architecture**: Separated `currentAnimation` (display/UI) and `activeAnimation` (execution)
  - `currentAnimation`: Stores selected animation including ANIM_AUTO (shown on OLED/web)
  - `activeAnimation`: Actual running animation (always a concrete animation like FADE, PULSE, etc.)
  - Added `autoModeActive` flag to track AUTO mode state
- 🔄 **Auto Mode Logic**: Improved cycle management
  - First animation starts immediately when AUTO selected
  - Cycles through animations 1-4 every 30 seconds
  - Properly resets when exiting/re-entering AUTO mode

### User Experience
- ✨ Button 1 now correctly shows "Auto" in the cycle
- ✨ Garland lights up instantly when AUTO mode selected
- ✨ OLED displays "Auto" while animations cycle automatically

## [0.6.1] - 2025-12-12

### 🔧 Critical Fix: Telegram Module Disabled
- ❌ **Removed Telegram Bot** - Cause of system freeze identified
  - Telegram polling was blocking the main loop and causing watchdog timer resets
  - Disabled all Telegram functionality (setupTelegramBot, handleTelegramBot, sendTelegramStatus)
  - Removed `#include "telegram_control.h"`
  - System now stable with animations running continuously without freeze

### Changed
  - Removed all code and configuration related to OLED, SSD1306, TFT, ILI9341, ESP32-S3, multi-board and multi-environment.
  - Kept only `esp32devkitc` environment with ESP32 Classic configuration.
  - Updated PlatformIO configuration for single-board focus and ST7789 display.
- ✅ Button controls responsive

### ⚠️ Known Limitation
- Telegram remote control temporarily unavailable
- To re-enable: uncomment includes and function calls in main.cpp (requires refactoring for stability)

## [0.6.0] - 2025-12-12

### Added
- 🤖 **Telegram Remote Control**:
  - Polling bot with commands `/anim <id|name>`, `/mode <id|name>`, `/nextanim`, `/nextmode`, `/status`, `/liste`
  - `/liste` returns the full list of modes and animations with numeric IDs
  - Automatic Telegram notification when WiFi connects (SSID, IP, current anim/mode)

### Changed
- 🔐 **Secrets Layout**: `WIFI_NETWORKS` now defined inline in `secrets.h` (no separate `secrets.cpp`).
- 📄 **Documentation**: README/README_FR and USER_GUIDE/USER_GUIDE_FR updated for Telegram control and version 0.6.0.

### Fixed
- 🐛 **ESP32 Classic Freeze Issue**: Changed `PIN_TB6612_PWMA` from GPIO 25 to GPIO 12
  - GPIO 25/26 are DAC pins that cause WiFi interference and watchdog timer resets
  - Animations no longer freeze during execution on ESP32 Classic
  - Removed unused LED_RGB section that conflicted with GPIO 16 (BUTTON_2)

## [0.5.1] - 2025-12-10 (Patch - Documentation)

### Updated
- 📄 **Documentation Files** :
  - Updated README.md and README_FR.md to reflect v0.5.1
  - Updated all header comments in source files to v0.5.1
  - Clarified that startup uses Auto animation mode and Permanent mode by default
  - Removed references to MODE_SCHEDULED and MODE_NIGHT_OFF from user documentation

## [0.5.1] - 2025-12-10

### Removed
- ❌ **Removed MODE_SCHEDULED mode** :
  - Removed schedule configuration functions (setSchedule, getSchedule)
  - Removed hourly scheduling functionality (start/end time configuration)
  - Simplified mode enum from 4 to 2 modes
  
- ❌ **Removed MODE_NIGHT_OFF mode** :
  - Removed automatic night detection via LDR threshold
  - Removed LDR_NIGHT_THRESHOLD constant
  - Removed isNightTime() function
  - Kept getLightLevel() for raw sensor data access

### Simplified
- 🎯 **Simplified to 2 core modes**:
  - `MODE_PERMANENT`: Garland always on
  - `MODE_MOTION_TRIGGER`: Activation by PIR motion detection (30 second duration)
- 📄 Updated all documentation (ARCHITECTURE.md, ARCHITECTURE_FR.md)
- 🌐 Updated web interface to show only 2 mode options
- Removed schedule configuration UI from web dashboard

## [0.4.1] - 2025-12-10 (Patch)

### Fixed
- 🔧 **OLED Screen Always Off Issue** :
  - Fixed double declaration of `isNight` variable in main loop
  - Removed problematic `setOledBacklight()` function that was turning off display completely
  - OLED now properly displays sleep mode with indicator text (SLEEP/ZZZ)
  - Night mode now only shows sleep indicator, not blank screen
  - Fixed variable scope issue preventing proper night/day transitions

- 🌙 **Night Mode Logic** :
  - Corrected night mode detection logic in loop function
  - OLED backlight no longer gets disabled (stays on but shows minimal content)
  - Animation bar now properly updates during day mode only
  - Sleep mode properly activated during night with visual indicator

- 📱 **Display Behavior** :
  - Improved sleep mode display with "SLEEP" text (128x64) or "ZZZ" (128x32)
  - Points now always visible during sleep, not turned off
  - Better visual feedback for night mode vs animation off state

## [0.4.0] - 2025-12-10

### Added
- 🌙 **Night Mode (Automatic Brightness Detection)** :
  - New MODE_NIGHT_OFF mode using LDR (photoresistor) sensor
  - Automatic detection of nighttime via light level threshold (LDR_NIGHT_THRESHOLD = 500)
  - In night mode: OLED backlight turns off, display shows minimal dots indicator
  - Heartbeat LED/NeoPixel indicators stop blinking in night mode (stays dark)
  - Motion detection and animation continue to respect night mode
  - Full automatic - no manual configuration needed

- 🔳 **Static Dots on OLED When Inactive** :
  - When no animation is active (ANIM_OFF or out of scheduled time), OLED displays 3 fixed dots instead of empty screen
  - Provides visual feedback that system is running but idle
  - In night mode: very minimal display with just center dots
  - Reduces unnecessary screen flickering

- ⚡ **Improved Power Efficiency** :
  - LED/NeoPixel heartbeat disabled during night mode to save power
  - OLED backlight disabled in night mode (configurable on/off)
  - GPIO verification: all pins confirmed safe for USB communication and boot/reset functions
  - Both ESP32-S3 and ESP32 Classic configurations verified

### Changed
- 📊 **OLED Animation Bar Enhancement** :
  - Animation bar now displays 3 fixed dots instead of nothing when animation is OFF
  - Provides better visual feedback during idle periods

- 🏷️ **Version Bump** :
  - Updated to version 0.4.0 with night mode and power efficiency features
  - All version strings updated across codebase

## [0.3.0] - 2025-12-09

### Changed
- 🔄 **OLED Display Line Order** :
  - Swapped Animation and Mode line order on 32px OLED display
  - First "M:" line now shows Mode (was Animation)
  - Second "A:" line now shows Animation (was Mode)
  - Improved readability by prioritizing mode information

- 🎯 **Default Animation Mode** :
  - Changed startup animation from `ANIM_AUTO` to `ANIM_FADE_ALTERNATE`
  - Guirlande now lights up **immediately** on boot instead of waiting 30 seconds

- 🔧 **Code Cleanup** :
  - Removed unused variables and functions related to old modes
  - Simplified mode handling logic in `loop()` function
  - Optimized display update logic for faster refresh

## [0.2.0] - 2025-12-08

### Added
- 🎉 **New Animation: Breathing Effect** :
  - Smooth breathing effect with adjustable speed and intensity
  - Configurable via `BREATHING_SPEED` and `BREATHING_INTENSITY` constants

- 📱 **Web Interface Enhancements** :
  - Added sliders for real-time adjustment of animation parameters
  - Improved layout and styling for better user experience
  - Live preview of animation changes on the web interface

### Changed
- ⚙️ **Configuration Parameters** :
  - Renamed and reorganized configuration parameters for clarity
  - Deprecated old parameters with warnings in the logs
  - Migration guide provided for transitioning to new parameters

- 🎨 **Animation Color Palette** :
  - Updated color palette for animations for more vibrant and varied colors
  - Added configuration options for custom color palettes

## [0.1.0] - 2025-12-07

### Added
- 🌟 **Initial Release** :
  - Basic garland functionality with manual mode and animation selection
  - Support for LED strip configuration and basic effects
  - Initial documentation and example configurations

### Changed
- 🎛️ **Configuration System** :
  - Switched to a new configuration system with `config.h` and `secrets.h`
  - Deprecated old configuration methods with warnings

- 📚 **Documentation Structure** :
  - Restructured documentation for clarity and completeness
  - Added example configurations and troubleshooting tips

### Fixed
- 🐛 **LED Strip Initialization** :
  - Fixed issues with LED strip not initializing correctly on some ESP32 boards
  - Improved compatibility with different LED strip types and configurations

- 🔧 **Miscellaneous Bugs** :
  - Fixed various minor bugs and issues reported by early users
  - Improved stability and performance of the garland system