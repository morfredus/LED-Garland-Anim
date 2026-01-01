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