## [0.9.0] - 2025-12-30

### 🚮 Remove ESP32-S3 environments
- Removed esp32s3_n16r8 and esp32s3_n8r8 environments from platformio.ini
- Only esp32devkitc (ESP32 Classic) environment is kept and maintained
- Version and documentation synchronized
## [0.7.0] - 2025-12-30

### 🖥️ LCD ST7789 & new buttons (ESP32 Classic)
- Added LCD_ST7789 pin definitions (LCD_MOSI, LCD_SCLK, LCD_CS, LCD_DC, LCD_RST, LCD_BLK) for ESP32 Classic environment
- Changed user button pins: BUTTON_1 = GPIO 16, BUTTON_2 = GPIO 17
- Documented and numbered changes in board_config.h and PIN_MAPPING.md

# Changelog

Toutes les modifications notables de ce projet seront documentées dans ce fichier.

Le format est basé sur [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
et ce projet adhère au [Semantic Versioning](https://semver.org/).

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
- ⚡ **Simplified Main Loop**: Removed Telegram polling throttling code
- 📉 **Reduced Memory**: Flash usage reduced from 79.3% to 75.9% (~45 KB saved)
- 🎯 **Animation Startup**: Changed default animation from `ANIM_AUTO` to `ANIM_FADE_ALTERNATE`
  - Guirlande now lights up **immediately** on boot instead of waiting 30 seconds

### Performance
- ✅ System stable - no freeze observed after Telegram removal
- ✅ All 6 animations working smoothly
- ✅ Web interface responsive
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
  - Changed startup animation from `ANIM