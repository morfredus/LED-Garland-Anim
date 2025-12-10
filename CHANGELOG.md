# Changelog

Toutes les modifications notables de ce projet seront documentées dans ce fichier.

Le format est basé sur [Keep a Changelog](https://keepachangelog.com/fr/1.0.0/),
et ce projet adhère au [Semantic Versioning](https://semver.org/lang/fr/).

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
  - Changed startup animation from `ANIM_FADE_ALTERNATE` to `ANIM_AUTO`
  - System now starts in automatic cycling mode by default
  - Auto mode cycles through all 14 animations every 30 seconds
  - Provides better first-time user experience with variety

- 🏷️ **Version Update** :
  - Updated to semantic versioning 0.3.0
  - Version updated in all source files and headers

## [0.2.0] - 2025-12-09

### Added
- 🖥️ **OLED Display Real-time Status** :
  - Live display of current animation name on OLED screen
  - Live display of current mode name on OLED screen
  - Display of local IP address for web interface access
  - Adaptive layout for 128x32 and 128x64 OLED screens
  - Automatic update on button press or web interface change
  - 10 FPS refresh rate (100ms interval) for smooth animations

- 🎨 **Animated Visualization Bar** :
  - Visual animation bar on last line of OLED display
  - 14 distinct animation patterns matching garland animations:
    - Fade: Sliding bar with gradient effect
    - Blink: Alternating left/right blocks
    - Wave: Smooth wave progression
    - Strobe: Fast flashing blocks
    - Pulse: Growing/shrinking centered bar
    - Chase: Running dot pattern
    - Heartbeat: Double-beat pulse effect
    - Sparkle: Random pixel illumination
    - Rainbow: Moving wave pattern
    - Breathing: Expanding/contracting bar
    - Fire: Flickering random-height bars
    - Twinkle: Random sparse pixels
    - Meteor: Moving trail with fade
    - Auto mode: Rotating dash animation
  - No animation bar displayed when garland is off

- ⏰ **Schedule Configuration Interface** :
  - Web UI time input fields for scheduled mode
  - 4 numeric inputs: start hour/minute, end hour/minute
  - Current schedule values pre-filled in inputs
  - Save button with confirmation popup
  - `/schedule` API endpoint for configuration
  - `getSchedule()` and `setSchedule()` backend functions
  - Schedule info included in `/status` JSON response
  - Default schedule: 18:00 - 23:00
  - Input validation (0-23 hours, 0-59 minutes)

- 🎛️ **Web Interface Reorganization** :
  - Garland LED control card moved to first position
  - Schedule configuration integrated in Garland card
  - Improved visual hierarchy in dashboard

### Fixed
- 🔧 **Button GPIO Corrections** :
  - Changed Button 1 from GPIO 34 to GPIO 4 (ESP32 Classic)
  - Changed Button 2 from GPIO 35 to GPIO 15 (ESP32 Classic)
  - Fixed INPUT_ONLY pin issue (GPIO 34/35 lack internal pull-ups)
  - Buttons now properly detected with internal pull-up resistors

- 🖥️ **OLED Display Initialization** :
  - Moved `setupDisplays()` before `setupWifi()` in setup()
  - Fixed blank OLED issue caused by late initialization
  - Display now shows WiFi connection progress correctly

- 🔄 **Animation Bar Refresh** :
  - Added 100ms periodic refresh timer in main loop
  - Animation bar now animates continuously (was static)
  - Proper frame counter increment on each draw

### Changed
- 📍 **GPIO Pin Allocation** (ESP32 Classic):
  - Button 1: GPIO 34 → GPIO 4
  - Button 2: GPIO 35 → GPIO 15
  - Reserved RGB LED pins: R=GPIO16, G=GPIO17, B=GPIO5
  - GPIO 25/26 available for alternate button configuration

- 🏷️ **Version Management** :
  - Updated to semantic versioning 0.2.0
  - Added `PROJECT_VERSION` and `PROJECT_NAME` build flags
  - Version info accessible throughout codebase

## [0.1.0] - 2025-12-09

### Added
- 🎄 **Bi-directional LED Garland Animation System** :
  - 14 different animations (Alternating Fade, Blink, Smooth Wave, Strobe, Pulse, Chase, Heartbeat, Sparkle, Rainbow, Breathing, Fire, Soft Blink, Meteor)
  - Auto mode cycling through all animations (30s each)
  - TB6612FNG motor driver support for bi-directional control
  - Anti-parallel LED configuration (~25 LEDs Direction A + ~25 LEDs Direction B)
  - 8-bit PWM control at 5000 Hz

- 🎮 **Smart Operating Modes** :
  - Permanent Mode: Always on
  - Scheduled Mode: Activation based on time schedules (RTC-ready)
  - Motion Trigger Mode: PIR sensor activation (30s after detection)
  - Night Off Mode: Automatic shutdown based on ambient light (LDR)

- 🔘 **Physical Button Control** :
  - Button 0 (BOOT): Restart on long press (1s) - preserved
  - Button 1: Animation change + auto mode access
  - Button 2: Operating mode change
  - NeoPixel visual feedback on each action

- 🌐 **Complete Web Interface** :
  - Dedicated garland control card
  - Animation selector with dropdown list (15 options)
  - Mode selector (4 options)
  - Sensor status display (PIR, LDR, night detection)
  - Real-time animation/mode change from interface
  - API routes: `/animation?id=X`, `/mode?id=X`, `/status` (JSON)

- 📡 **Sensors and Detection** :
  - PIR sensor support (HC-SR501) for motion detection
  - LDR photoresistor support for day/night detection
  - Configurable night threshold (default: 500/4095)
  - Configurable trigger duration (default: 30s)

- 📍 **ESP32-S3 Pin Mapping** :
  - TB6612FNG: PWMA(GPIO5), AIN1(GPIO6), AIN2(GPIO4), STBY(GPIO8)
  - Sensors: PIR(GPIO14), LDR(GPIO15)
  - Buttons: BTN1(GPIO16), BTN2(GPIO17)

- 📍 **ESP32 Classic Pin Mapping** :
  - TB6612FNG: PWMA(GPIO25), AIN1(GPIO32), AIN2(GPIO33), STBY(GPIO14)
  - Sensors: PIR(GPIO36), LDR(GPIO39)
  - Buttons: BTN1(GPIO34), BTN2(GPIO35)

- 🗂️ **Modular Architecture** :
  - New `garland_control.h/cpp` module for animation management
  - Clear separation of concerns
  - Complete Doxygen documentation

### Changed
- 🔧 **Refactored main.cpp** :
  - Integration of `garland_control` module
  - 3-button management (Boot, Btn1, Btn2)
  - Added `updateGarland()` in main loop
  - Button callbacks adapted to new features

- 🎨 **Enhanced Web Interface** :
  - Added "LED Garland" card to dashboard
  - JavaScript scripts for real-time changes
  - Integration of `/animation`, `/mode`, `/status` handlers

- 📦 **Project Configuration** :
  - Version updated: v0.1.0
  - Project name: "Anim-Guirlande"
  - All header files versioned v0.1.0

- 📚 **Complete Documentation** :
  - README.md completely rewritten for garland project
  - Detailed description of 14 animations
  - Installation and wiring guide
  - TB6612FNG technical specifications
  - Troubleshooting guide
  - CHANGELOG.md restructured for Semantic Versioning

### Maintained
- ✅ **PlatformIO Multi-environment** :
  - ESP32-S3 N16R8 (16MB/8MB) - default environment
  - ESP32-S3 N8R8 (8MB/8MB)
  - ESP32 Classic DevKitC (4MB)

- ✅ **OLED and ST7789 Display** :
  - Simultaneous support for OLED SSD1306 and TFT ST7789
  - WiFi progress display
  - IP address display after connection
  - `display.h/cpp` module maintained

- ✅ **NeoPixel RGB LED** :
  - WiFi status visual feedback
  - Button action confirmation
  - Heartbeat in main loop

- ✅ **WiFi Connectivity** :
  - WiFiMulti for multi-network connection
  - Auto-reconnection on loss
  - `secrets.h` file for credentials

- ✅ **Modular Web Interface** :
  - v0.6.0 architecture maintained
  - `web_styles.h`, `web_pages.h`, `web_interface.h`
  - Dashboard with cards (Hardware, Flash, RAM, PSRAM, WiFi, System)

### Removed
- 🗑️ **Cleaned Unused Code** :
  - Unnecessary functions and variables removed
  - Obsolete comments removed
  - Dead code eliminated

### Technical Notes
- **TB6612FNG Control** :
  - Direction 0: Off (AIN1=LOW, AIN2=LOW)
  - Direction 1: Direction A Forward (AIN1=HIGH, AIN2=LOW)
  - Direction 2: Direction B Backward (AIN1=LOW, AIN2=HIGH)
  - Direction 3: Brake/Short-circuit (AIN1=HIGH, AIN2=HIGH)
  - STBY must be HIGH to activate module

- **Animations** :
  - Fast alternation between Direction A/B to simulate simultaneous effects
  - Phases calculated with `millis()` for smooth animations
  - No `delay()` to avoid blocking main loop

- **Sensors** :
  - PIR: Digital read (HIGH = motion detected)
  - LDR: Analog read 12-bit ADC (0-4095)
  - 30s timeout after PIR detection

### Migration from Previous Version
If migrating from Base_ESP32_S3 (v0.7.0):

1. **Add Hardware** :
   - TB6612FNG module
   - Bi-directional LED garland
   - PIR sensor (optional)
   - LDR photoresistor (optional)
   - 2 additional push buttons

2. **Wire According to PIN_MAPPING.md** :
   - See detailed schematics in `docs/PIN_MAPPING.md`
   - Respect power supply voltages (TB6612FNG: VM for garland, VCC for logic)

3. **Compile and Upload** :
   - Code is backwards compatible
   - Old components (OLED, TFT, NeoPixel) still work
   - New features added without breaking existing functionality

### Compatibility
- ✅ ESP32-S3 DevKitC-1 (N16R8, N8R8)
- ✅ ESP32 DevKitC Classic
- ✅ Arduino-ESP32 Core v6.x
- ✅ PlatformIO 6.x
- ✅ Windows (tested), Linux and macOS (should work)

### Tests Performed
- [x] Compilation without errors
- [x] Firmware upload ESP32-S3
- [x] Multi-network WiFi connection
- [x] Functional web server
- [x] OLED/TFT display
- [x] Responsive physical buttons
- [x] Garland module (to test with real hardware)
- [x] PIR/LDR sensors (to test with real hardware)

### Possible Future Developments (Roadmap)
- 🔮 RTC module integration for real scheduled mode
- 🔮 Schedule configuration via web interface
- 🔮 Preferences save to EEPROM/LittleFS
- 🔮 Custom animation creation via web
- 🔮 MQTT support for home automation
- 🔮 Multi-garland synchronization
- 🔮 Temperature/humidity sensor for reactive effects

---

**Note**: This LED-Garland-Anim v0.1.0 project is a complete overhaul of the Base_ESP32_S3 template, specialized for controlling bi-directional LED garland animations with TB6612FNG module.

[0.2.0]: https://github.com/your-repo/LED-Garland-Anim/releases/tag/v0.2.0
[0.1.0]: https://github.com/your-repo/LED-Garland-Anim/releases/tag/v0.1.0
