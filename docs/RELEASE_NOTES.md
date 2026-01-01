# Release Notes - LED-Garland-Anim

Complete version history for the LED-Garland-Anim project.

---

# [1.11.2] – 2026-01-01

### Fixed (PATCH - Coordinate System Correction)

**Matrix Coordinate Mapping System**
- Fixed incorrect zigzag indexing pattern in 8x8 NeoPixel matrix
- Implemented uniform linear indexing (all rows 0-7 go left→right)
- Corrects pixel positioning and visual distortions in all 38 matrix animations
- Modified `xy()` function to use simple linear mapping: `return y * 8 + x;`

### Technical
- All rows now follow the same left-to-right pattern
- Coordinate specification: Row N = pixels (N×8) to (N×8+7)
- Ensures proper alignment of animations with physical LED layout

---

# [1.11.1] – 2026-01-01

### Fixed (PATCH - Synchronization)

**Matrix Auto Mode Interval Synchronization**
- Matrix auto mode now shares the same interval as garland auto mode
- Single UI control adjusts animation duration for both simultaneously
- Both modules call `getAutoAnimationIntervalMs()` for synchronized timing
- Default: 30 seconds (configurable from 5s to 5 minutes via web UI)

---

# [1.11.0] – 2026-01-01

### Added (MINOR - New Features + Major Animation Improvements)

**NEW FEATURE: Auto Mode for Matrix**
- Automatic cycling through all matrix animations
- Synchronized interval with garland auto mode
- Never uses OFF state - continuous animation display

**Detection Mode Logic Fixes**
- MODE_MOTION_TRIGGER: Matrix now correctly turns back on when motion detected
- Fixed critical bug where matrix remained off after timeout
- Preserves animation and brightness settings during motion detection cycles

**Animation Quality Improvements** (14 animations fixed)
- Candy Cane: Realistic diagonal hook with rotating red/white stripes
- Clock: Real-time second hand, clockwise rotation, proper hour markers
- Bunny: Added blinking eyes
- Flower: Recognizable blooming 8-petal flower
- Meteor: Full diagonal matrix coverage
- Santa: Improved facial features (hat, eyes, nose, beard)
- Gift: Clear box with ribbon and bow
- Snowflake: Heartbeat pulse effect
- Rainbow Wave: True sine wave motion
- Plasma: Enhanced visual clarity
- Radar: Improved blip persistence

### Removed
- Icicles animation completely removed

---

# [1.10.0] – 2026-01-01

### Added (MINOR - New Animations + UX Improvements)

**New Matrix Animations:**
- **Campfire**: Realistic fire simulation with heat propagation algorithm (64-cell heat map, upward/lateral diffusion, red→orange→yellow→white gradient)
- **Radar**: Military-style green radar sweep with blips (rotating sweep line, fading trail, concentric grid, random target blips)

**Animation Redesign:**
- **Stocking (Christmas)**: Completely redrawn for better recognition
  - Clear stocking shape with white cuff, red body, green stripe, gold sparkle
  - Realistic pendulum swing animation
  - Now easily identifiable as Christmas stocking

### Changed

- **Web UI: No More Page Reloads (CRITICAL UX FIX)**
  - Removed all `location.reload()` calls - no more white flash
  - Implemented AJAX-only updates for smooth transitions
  - New functions: `updateCurrentAnimation()`, `updateCurrentMode()`, `updateCurrentMatrix()`
  - Instant visual feedback without page refresh

### Technical
- Total Animations: 37 → 39 (Campfire + Radar)
- Updated enum, animation names array, switch cases
- JavaScript DOM updates without page reload
- Radio button CSS classes update instantly

---

# [1.9.0] – 2026-01-01

### Changed (MINOR - UI Improvements)

**Web Interface Modernization:**
- **Radio Buttons Replace Dropdowns**: All selections now use radio button grids (Matrix: 37, Modes: 3, Garland: 11)
- **Responsive 2-Column Layout**: 2 columns on wide screens, 1 column on narrow (<600px)
- **Instant Selection**: Removed all "Apply" buttons - changes apply immediately via `onchange` events
- **Enhanced Visual Feedback**: Selected items highlighted with green background/border, hover effects
- **Faster Messages**: Reduced display time from 3s to 2.5s

### Fixed
- **BUGFIX #8**: Missing 3rd mode (MODE_MOTION_MATRIX_INDEPENDENT) now displays correctly in web UI

### Technical
- 8 new CSS classes for radio buttons and responsive grid
- Replaced `<select>` with `<div class='radio-grid'>` + radio inputs
- JavaScript functions accept ID parameter directly
- Compact UI despite 51 total radio buttons
- Mobile-optimized single-column layout

---

# [1.8.1] – 2026-01-01

### Fixed (PATCH - Bug Fixes Only)

**7 Numbered Bug Fixes:**
- **BUGFIX #1**: Matrix Rain - Reduced fade (220→245) to keep bottom rows visible
- **BUGFIX #2**: Clock - Reversed rotation direction (now clockwise)
- **BUGFIX #3**: Countdown - Redrawn digits 3, 2, 1 for better clarity
- **BUGFIX #4**: Icicles - Added all 8 icicles with animated water drops
- **BUGFIX #5**: Candle - Base widened to 4px, flame narrowed to 2px with flicker
- **BUGFIX #6**: Bell - Bell stays fixed, only clapper swings
- **BUGFIX #7**: Web UI Layout - Reserved space with `visibility:hidden` prevents button displacement

---

# [1.8.0] – 2026-01-01

### Added
- **New Mode**: MODE_MOTION_MATRIX_INDEPENDENT (garland motion-triggered, matrix always on)
- **Matrix Synchronization**: Matrix follows garland state in MODE_MOTION_TRIGGER
- **Enhanced Mode Labels**: "Permanent", "Detection (tout)", "Detection (guirlande)"

### Fixed (CRITICAL)
- **GPIO Pin Mapping**: Restored matrix GPIO from 13 back to 32 (correct pin)
- **Animation Timing Bugs**: Fixed 8 animations using broken `elapsed % N == 0` timing
  - Affected: Meteor, Shooting Star, Snow, Champagne, Confetti, Sparkle Rain, Matrix Rain, Stars Field
  - Solution: Threshold-based timing with static `lastUpdate` variables

---

# [1.7.0] – 2026-01-01

### Added

**27 New Matrix Animations** (total: 37)

**Christmas (10):**
- Candy Cane, Wreath, Stocking, Reindeer, Gingerbread Man
- Hot Cocoa, Fireplace, Icicles, Northern Lights, Presents Stack

**New Year (7):**
- Fireworks, Champagne Bubbles, Countdown 3-2-1, Confetti
- Clock, Party Popper, Disco Ball

**Easter (4):**
- Easter Egg, Hopping Bunny, Hatching Chick, Spring Flowers

**Modern/Abstract (6):**
- Rainbow Wave, Sparkle Rain, Plasma Effect, Matrix Digital Rain
- Rotating Spiral, Pulsing Heart, Twinkling Stars Field

---

# [1.6.0] – 2026-01-01

### Added
- **8x8 NeoPixel Matrix Support**: WS2812B-64 matrix on GPIO 32
- **10 Matrix Animations**: Star, Meteor, Shooting Star, Santa, Tree, Bell, Snow, Gift, Candle, Snowflake
- **Dual Independent Control**: Garland and matrix operate independently
- **Matrix Settings**: Animation selection, brightness control (0-255)
- **NVS Persistence**: Matrix settings saved/restored automatically
- **Web UI Integration**: Matrix controls added to dashboard

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
- Version 1.11.2 (SEMVER - MINOR)

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
- Version 1.11.2 (SEMVER)
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
- Version 1.11.2 (SEMVER)

---
# [1.2.2] – 2025-12-31

### Changed
- Complete harmonization and logical reorganization of README.md and README_FR.md (structure, clarity, deduplication)
- Definitive removal of ESP32-S3 and legacy environment references
- All documentation and guides reviewed for logical order and user clarity
- Version, changelog, and release notes updated

---
# [1.2.1] – 2025-12-31

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
# Release Notes – LED-Garland-Anim v1.11.2

## [1.2.0] – 2025-12-31

### Added
- Automatic detection of motion sensor type (PIR HC-SR501 or RCWL-0516 Doppler radar) on GPIO 35
- New technical documentation for RCWL-0516 (EN/FR)
- All user and technical documentation updated for v1.11.2 (EN/FR)

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

See CHANGELOG.md for detailed commit history.
# Release Notes – LED-Garland-Anim v1.11.2

## [1.2.0] – 2025-12-31

### Added
- Automatic detection of motion sensor type (PIR HC-SR501 or Doppler radar RCWL-0516) on GPIO 35
- New technical documentation for RCWL-0516 (EN/FR)
- All user and technical documentation updated for v1.11.2 (EN/FR)

### Changed
- Pin mapping: PIR_SENSOR replaced by MOTION_SENSOR_PIN (GPIO 35)
- All references to LDR/photoresistor removed (feature deprecated)
- Documentation and pin tables now reflect only supported hardware
- Troubleshooting and guides updated for new sensor logic

### Fixed
- Consistency of documentation (EN/FR)
- Version numbers and dates in all docs

### Removed
- All code and documentation related to LDR/photoresistor
- Legacy display and board support (now ESP32 Classic + ST7789 only)

---

See CHANGELOG.md for detailed commit history.
## [1.1.0] - 2024-06-XX

### Added
- Automatic save/restore of user configuration (mode, animation, intervals) using NVS. Settings persist across reboots and power cycles.
# Release Notes - Version 1.11.2

**Release Date:** December 30, 2025

## 🎉 Major Release: ESP32 IdeaSpark Platform Unification

Version 1.11.2 represents a complete platform modernization, focusing exclusively on the ESP32 IdeaSpark board with integrated 1.14" ST7789 LCD display.

---

## ♻️ What’s New in 1.1.0

- All LDR/photoresistor references removed (project is now PIR-only)
- All documentation (EN + FR) fully rewritten and updated for hardware, wiring, configuration, and usage
- Version numbers updated everywhere (SEMVER)
- Full consistency between code, documentation, and hardware mapping

---

## 🌟 Highlights

### Modern ST7789 Display System
- **Beautiful Boot Screen**: Project name, version, and WiFi connection progress
- **Optimized Main UI**: Centered headers, compact info, 20% larger animation zone
- **11 Animated Visualizations**: Smooth, colorful animations for each garland mode
- **Professional Design**: Rounded rectangles, vibrant gradients, modern aesthetics

### Platform Simplification
- **Single Target**: ESP32 IdeaSpark 1.14" LCD only
- **Removed**: All ESP32-S3 environments and legacy display code (OLED/TFT/ILI9341)
- **Cleaner Codebase**: 15% code reduction, simplified architecture

### Critical Fixes
- **Motion Detection Timer**: Now properly stops animations after configured duration
- **Edge Detection**: Rising edge triggering prevents continuous timer resets
- **Display Layout**: Optimized to fit perfectly on 135×240 screen

---

## 🔑 Key Changes

### Added
- Complete ST7789 display module with boot and main screens
- ESP32 IdeaSpark board configuration with optimized pin mapping
- 11 distinct animated visualizations with vibrant colors
- Real-time animation updates at 10 FPS

### Changed
- Unified to single ESP32 platform (removed ESP32-S3 support)
- Modernized display architecture with simplified API
- Optimized UI layout for maximum animation zone
- Updated all display calls throughout codebase

### Fixed
- Motion detection timer with edge detection logic
- Build errors (LDR sensor, display includes, function signatures)
- Display layout clipping issues

### Removed
- All OLED (SSD1306) display code and configuration
- All TFT and ILI9341 display code
- ESP32-S3 environments and multi-board complexity
- LDR sensor support

---

## 📦 Hardware Requirements

**Supported Board:**
- **ESP32 IdeaSpark 1.14" LCD** (ESP32 Classic with integrated ST7789 display)

**Components:**
- TB6612FNG motor driver module
- PIR motion sensor (HC-SR501)
- Two user buttons (GPIO 16, 17)
- 2-wire LED garland with anti-parallel LEDs

---

## 🚀 Quick Start

### 1. Hardware Setup
Use the ESP32 IdeaSpark board with integrated 1.14" ST7789 LCD display.

### 2. PlatformIO Environment
```ini
[platformio]
default_envs = esp32devkitc
```

### 3. Compile & Upload
```bash
pio run -e esp32devkitc -t upload
```

### 4. Enjoy!
Experience the modern LCD interface with smooth animations!

---

## ⚠️ Breaking Changes

### No Longer Supported
- ❌ ESP32-S3 boards (esp32s3_n16r8, esp32s3_n8r8)
- ❌ OLED displays (SSD1306)
- ❌ TFT/ILI9341 displays
- ❌ LDR light sensor

### Migration Required
If upgrading from v0.x.x:
1. Replace hardware with ESP32 IdeaSpark 1.14" LCD board
2. Remove OLED/TFT configuration from secrets.h
3. Follow new pin mapping in `include/board_config.h`
4. Use `esp32devkitc` environment exclusively

---

## 🎨 Display Features

### Boot Screen
- Centered project name and version
- WiFi connection progress bar with percentage
- Clean, professional design

### Main Screen
- Application name and version at top (centered)
- Compact mode and animation info
- Large animation visualization zone (234×81 pixels)
- 11 unique animated patterns:
  - **Fade Alternate**: Yellow/blue gradient bars
  - **Pulsation**: Growing/shrinking purple circle
  - **Respiration**: Smooth cyan fade in/out
  - **Strobe**: Fast white flashes
  - **Heartbeat**: Red double-pulse effect
  - **Wave**: Cyan sinusoidal wave
  - **Sparkle**: Twinkling yellow dots
  - **Meteor**: Orange/yellow trailing effect
  - **Auto**: Green text with orbiting circles
  - **OFF**: Centered red "OFF" text
  - And more!

---

## 🐛 Bug Fixes

### Motion Detection Timer
- **Issue**: Animations wouldn't stop after configured duration
- **Fix**: Implemented edge detection (rising edge triggering only)
- **Result**: Timer starts on motion detection and properly expires

### Display Layout
- **Issue**: Animation rectangle cut off at bottom of screen
- **Fix**: Optimized layout, removed unnecessary WiFi/IP info
- **Result**: 20% larger animation zone, perfect screen fit

---

## 📊 Technical Specifications

- **Display**: 135×240 pixels, RGB565 color, SPI communication
- **Refresh Rate**: 10 FPS for smooth animations
- **Platform**: ESP32 Classic (4MB Flash)
- **Code Reduction**: ~15% smaller codebase
- **Files Modified**: 12 core files
- **Commits**: 7 consolidated commits

---

## 🔗 Resources

- **Changelog**: See [CHANGELOG.md](CHANGELOG.md) for complete history
- **French Version**: [CHANGELOG_FR.md](CHANGELOG_FR.md)
- **Pin Mapping**: `include/board_config.h`
- **Configuration**: `include/config.h`

---

## ✅ Tested & Verified

- ✅ Compilation on esp32devkitc environment
- ✅ ST7789 display rendering
- ✅ All 11 animation visuals
- ✅ Motion detection timer
- ✅ Web interface integration
- ✅ Button controls
- ✅ Telegram integration
- ✅ Stable operation (no watchdog issues)

---

## 🙏 Thank You

Thank you for using LED-Garland-Anim! This v1.11.2 release brings a modern, focused platform with beautiful visual animations.

For issues, questions, or contributions, please visit the project repository.

---

**LED-Garland-Anim v1.11.2** - Modern LED Garland Controller for ESP32 IdeaSpark 🎄✨
