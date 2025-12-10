# Changelog

Toutes les modifications notables de ce projet seront documentées dans ce fichier.

Le format est basé sur [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
et ce projet adhère au [Semantic Versioning](https://semver.org/).

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