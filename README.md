
# LEDGarland
**Version: 5.6.4** (2026-02-02)  
*This documentation is valid from version 5.6.4.*


Controller for bi-directional LED garland and 8x8 NeoPixel matrix animation on **ESP32 Classic** (IdeaSpark/DevKitC), **ESP32 Wroom (DevKit V1)**, **ESP32-S3 Mini**, **ESP32-S3 Super Mini** — all platforms support **OLED SSD1306 (I2C)** if connected (see per-board pins in the Pin Mapping guide). PIR/RCWL-0516 auto-detection, **modern web interface with instant save**, responsive layout, flash-free AJAX updates, web-based OTA updates, **mDNS support for easy access via unique device name**, physical controls: BOOT + 1 user button (see below), 11 garland animations, multiple festive matrix animations, dual independent control, smart modes, persistent configuration, automatic startup animations.

## ✨ What's New in v5.2.0

1. **ESP32-C3 HW-675 support (MINOR)** - New hardware platform with OLED 0.42" (72×40 px) display
2. **Universal OLED display** - IP + Mode display on OLED SSD1306 (I2C), available on all platforms if connected
3. **BOOT button functionality** - Mode cycling (click) and system reboot (long-press)
4. **I2C diagnostics** - Automatic device detection on startup
5. **Multi-board compatibility** - Seamless support for ESP32 Classic and ESP32-C3 architectures

See [CHANGELOG.md](./CHANGELOG.md) for older releases.

## ✨ What's New in v3.0.0

### 💥 Complete Web UI Card Reorganization (BREAKING CHANGE)
- **New navigation flow** - Card order completely restructured for better UX
- **Animations prioritized** - Garland and Matrix animations now at top (most frequently accessed)
- **3-zone Mode card** - Mode + screen mode side-by-side, all parameters below in unified section
- **Integrated screen mode** - Screen display mode now part of Mode card (removed separate card)
- **Consolidated parameters** - All temporal parameters + matrix brightness in one place
- **Reduced scrolling** - More compact layout with logical grouping

### 📋 New Card Order (v3.0.0)
1. 🎄 **Animations Guirlande** - All garland animations (was Card 2)
2. 🎨 **Matrice 8x8** - All matrix animations (was Card 3)
3. 🎯 **Mode de fonctionnement** - 3-zone layout:
   - Zone A (left): Mode selection (Auto/Manuel/Détection)
   - Zone B (right): screen display mode (was separate Card 4)
   - Zone C (below): All temporal parameters + matrix brightness
4. ℹ️ **Système & Réseau** - System and network information
5. 🏷️ **Nom d'appareil** - Device name configuration

### 🎨 Enhanced Mode Card Design
**Side-by-Side Layout** (CSS Grid):
- **Left Half**: Operating mode selection (Auto | Manuel | Détection mouvement)
- **Right Half**: screen display mode (Animated + matrix | animation only | screen off)
- **Full Width Below**: All temporal parameters (motion duration, garland interval, matrix interval) + matrix brightness

**Benefits**:
- All configuration in one place
- Reduced vertical scrolling
- Better visual hierarchy
- Logical parameter grouping

---

## Previous Releases

### v2.0.0 (2026-01-06) - Complete UI Overhaul
- **Instant save on all controls** - No more "Apply" buttons! Changes take effect immediately
- **Modern slider controls** - All time intervals use range sliders with real-time value display
- **Centralized notifications** - Fixed notification bar at top for all confirmations
- **Logical grouping** - All temporal parameters grouped in "Mode de fonctionnement" card
- **Critical Bug Fixes**:
  1. **Screen off mode** - Display now properly clears pixels before cutting backlight
  2. **Matrix auto-start** - Auto mode now correctly activates on boot with saved settings

---

## 1. Required Hardware




### Supported Hardware Platforms

- **ESP32 Classic (IdeaSpark/DevKitC)**
- **ESP32 Wroom (DevKit V1)**
- **ESP32-S3 Mini** (esp32s3_mini)
- **ESP32-S3 Super Mini** (esp32s3_supermini)

> 📌 **OLED SSD1306 (I2C) display is supported on all platforms if connected. See per-board I2C pins in the Pin Mapping guide.**


#### Required Components (all platforms)
- **TB6612FNG dual H-bridge driver**
- **2-wire LED garland** (anti-parallel LEDs, ~50 LEDs)
- **8x8 NeoPixel Matrix WS2812B-64** (64 addressable RGB LEDs)
- **Motion sensor**: PIR HC-SR501 or RCWL-0516 (auto-detected)
- **OLED SSD1306 (I2C) display** (optional but supported on all platforms; see per-board pins)
- **Suitable power supply** for the garland and matrix (5V recommended for NeoPixels)


### Main pinout summary (ESP32 Classic)
```
TB6612FNG (Garland):
   PWMA  → GPIO 12
   AIN1  → GPIO 25
   AIN2  → GPIO 33
   STBY  → GPIO 14
8x8 NeoPixel Matrix:
   DATA  → GPIO 27
MOTION_SENSOR_PIN (PIR/RCWL-0516) → GPIO 35
OLED I2C:
   SDA   → GPIO 21
   SCL   → GPIO 22
BTN1     → GPIO 16 (User button)
BOOT     → GPIO 0  (Boot/Reset)
```

### Main pinout summary (ESP32 Wroom)
```
TB6612FNG (Garland):
   PWMA  → GPIO 12
   AIN1  → GPIO 25
   AIN2  → GPIO 33
   STBY  → GPIO 14
8x8 NeoPixel Matrix:
   DATA  → GPIO 27
MOTION_SENSOR_PIN (PIR/RCWL-0516) → GPIO 35
OLED I2C:
   SDA   → GPIO 21
   SCL   → GPIO 22
BTN1     → GPIO 16 (User button)
BOOT     → GPIO 0  (Boot/Reset)
```

### Main pinout summary (ESP32-S3 Mini / Super Mini)
```
TB6612FNG (Garland):
   PWMA  → GPIO 10
   AIN1  → GPIO 11
   AIN2  → GPIO 12
   STBY  → GPIO 13
8x8 NeoPixel Matrix:
   DATA  → GPIO 7
MOTION_SENSOR_PIN (PIR/RCWL-0516) → GPIO 2
OLED I2C:
   SDA   → GPIO 4
   SCL   → GPIO 5
BTN1     → GPIO 8 (User button)
BOOT     → GPIO 0  (Boot/Reset)
```

---

## 2. Key Features

- **Dual LED Control**: 2-wire LED garland + 8x8 NeoPixel matrix with independent control
- **Animations**: 11 for the garland + multiple festive animations for the 8x8 matrix
- **Physical Controls (since v5.3.4):**
   - **BOOT button (GPIO 0):** Long press = reboot (unchanged)
   - **User button (GPIO 16):**
      - 1 click = next garland animation
      - 2 clicks = next matrix animation
      - long press = change global mode
- **3 Display Modes (OLED):**
   - **Animated**: OLED info screen (project name, version, IP, mode, animations)
   - **Static**: Same information shown without animation
   - **Off**: Display fully off
- **Display Mode Selection**:
   - Selectable live from the web UI (radio buttons)
   - Default value set in `config.h`
   - Persistent (saved in NVS, restored at boot)
   - Immediate effect, no reboot required
- **37 Matrix Animations** organized by theme:
   - **Original (10)**: Star, Meteor, Shooting Star, Santa, Tree, Bell, Snow, Gift, Candle, Snowflake
   - **Christmas (10)**: Candy Cane, Wreath, Stocking, Reindeer, Gingerbread, Hot Cocoa, Fireplace, Icicles, Northern Lights, Presents
   - **New Year (7)**: Fireworks, Champagne, Countdown, Confetti, Clock, Party Popper, Disco Ball
   - **Easter (4)**: Easter Egg, Bunny, Chick, Flowers
   - **Modern/Abstract (6)**: Rainbow Wave, Sparkle Rain, Plasma, Matrix Rain, Spiral, Heart, Stars Field
   - **Radar (1)**: Realistic radar sweep with green ray, fading trail, and red blips triggered by the sweep (max 2-4 per turn, never close together, fade out smoothly)
- **Matrix Brightness Control**: Independent brightness adjustment (0-255) for the matrix
- **Startup Animation**: Sparkling star animation on matrix at boot
- **3 Smart Operating Modes**: Permanent (both always on), Motion Trigger (both follow motion), Motion Independent (garland follows motion, matrix always on)
- Auto-detection of PIR HC-SR501 or RCWL-0516
- OLED SSD1306 display (128x64 or 128x32 via config)
- Full-featured web interface with matrix controls
- **Web-based OTA firmware updates** (new in v1.4.0)
- Physical button controls
- Persistent configuration (NVS) for both garland and matrix
- OTA updates (ArduinoOTA + Web)

---

## 3. Software Prerequisites

- **PlatformIO** (VS Code extension or CLI)
- **Python 3.x**
- **Git**

---

## 4. Installation

1. Clone the project
   ```bash
   git clone <your-repo>
   cd LED-Garland-Anim
   ```
2. Configure `include/secrets.h` (WiFi)
3. In `platformio.ini`, choose your environment:
   - `esp32devkitc`: ESP32 Classic (4MB Flash)
   - `esp32wroom`: ESP32 Wroom (DevKit V1)
   - `esp32s3_mini`: ESP32-S3 Mini
   - `esp32s3_supermini`: ESP32-S3 Super Mini
4. Wire the components as shown above
5. Build and upload
   ```bash
   # For ESP32 Classic:
   pio run -e esp32devkitc
   pio run -e esp32devkitc -t upload
   
   # For ESP32-S3 Mini:
   pio run -e esp32s3_mini
   pio run -e esp32s3_mini -t upload

   # For ESP32-S3 Super Mini:
   pio run -e esp32s3_supermini
   pio run -e esp32s3_supermini -t upload
   
   # Monitor serial output:
   pio device monitor
   ```

### 4.1. Choosing USB or OTA Upload

You can choose the upload method (USB or OTA) at each upload without editing platformio.ini:

- **USB upload (serial):**
   - Make sure `upload_protocol` is not set in platformio.ini (or is commented out)
   - Use:
      ```bash
      pio run -e esp32devkitc -t upload
      ```
   - PlatformIO will auto-detect the serial port (e.g. COM8)

- **OTA upload (WiFi):**
   - Use:
      ```bash
      pio run -e esp32devkitc -t upload --upload-port 192.168.x.x
      ```
   - Replace `192.168.x.x` with your ESP32's IP address
   - PlatformIO will automatically use OTA for this upload
   - ⚠️ **Note:** PlatformIO will show a warning:
     > We have just detected `upload_port` as IP address or host name of ESP device. `upload_protocol` is switched to `espota`.
     This is normal and does not require any change in your configuration.

**Tip:** Do not set `upload_protocol = espota` globally. Use the `--upload-port` option for OTA uploads only when needed.

---

## 5. Web Interface and Network Access

### 5.1. Accessing the Web Interface

The device can be accessed in **two ways**:

1. **Via IP Address** (traditional):
   ```
   http://192.168.x.x
   ```
   Find your ESP32's IP address in:
   - Serial monitor output
   - OLED display (if connected)
   - Your router's connected devices list

2. **Via mDNS Name** (recommended) 🆕:
   ```
   http://garland.local
   ```
   - No need to memorize IP addresses!
   - Works on most devices (Windows 10+, macOS, Linux, iOS, Android)
   - **Default name**: `garland` (customizable)

### 5.2. Customizing the Device Name

You can change the mDNS device name directly from the web interface:

1. Access the web interface (`http://garland.local` or `http://[IP]`)
2. Scroll to **"🏷️ Device Name (mDNS)"** section
3. Enter your desired name (alphanumeric, dash, underscore, max 32 chars)
4. Click **"Apply"**
5. Your device is now accessible at `http://[your-name].local`

**Examples:**
- `christmas-lights.local`
- `living-room-led.local`
- `xmas-tree.local`

**Configuration saved automatically** in non-volatile memory (NVS).


### 5.3. Web Interface Features

- **Web Interface**
   - Modern UI with radio button grids for all selections
   - Responsive layout (2 columns desktop, 1 column mobile)
   - Instant updates, no page reloads
   - **Display Mode**: Select between Animated, Static, Off (immediate effect)
   - **Device Name Configuration**: Change mDNS name on the fly
   - All settings (animation, mode, display mode, durations, device name) are persistent and restored at boot
   - Network info visible in the dashboard (SSID, IP, mDNS)
   - Save/Restore/Erase configuration actions
   - **OLED display**: project name, version, IP, mode, and current animations

---

## 6. Firmware Updates (OTA)

The firmware supports **two OTA update methods**:

### 6.1. Web-based OTA Update (New in v1.4.0) ⭐

**The simplest and recommended method!**

1. Compile your firmware with PlatformIO:
   ```bash
   pio run -e esp32devkitc
   ```

2. Access the ESP32's web interface: `http://[ESP32_IP]`

3. Click the **"⬆️ OTA Update"** button on the dashboard

4. On the update page:
   - Click **"📁 Select .bin file"**
   - Navigate to `.pio/build/esp32devkitc/firmware.bin`
   - Click **"🚀 Start Update"**

5. Progress is displayed in real-time:
   - Progress bar in the browser
   - Status messages (success/failure)

6. The ESP32 reboots automatically after a successful update

**Advantages:**
- ✅ Intuitive graphical interface
- ✅ No PlatformIO commands needed
- ✅ Works from any browser (PC, smartphone, tablet)
- ✅ Real-time progress display
- ✅ Automatic file validation

**⚠️ Important:** Do not unplug the device during the update!

### 6.2. OTA Update via ArduinoOTA (PlatformIO)

**Traditional method for developers:**

1. Connect the ESP32 to WiFi
2. In PlatformIO, use:
   ```bash
   pio run -e esp32devkitc -t upload --upload-port [ESP32_IP]
   ```
3. The device appears as `LED-Garland-Anim.local`
4. The device reboots automatically after the update

**Security note:** OTA is enabled only when the ESP32 is connected to WiFi.

---
## 7. Advanced Configuration

In `include/config.h`:
```cpp
// #define HAS_OLED_U8G2   // Comment to disable OLED
```
In `include/garland_control.h`:
```cpp
#define MOTION_TRIGGER_DURATION 30000  // Duration in ms after detection
```

---

## 8. Technical Specifications

- LED garland: 2 wires, anti-parallel LEDs, 8-bit PWM 5kHz
- TB6612FNG: dual H-bridge, direction/intensity control
- Sensors: PIR (LOW idle, HIGH detection), RCWL-0516 (HIGH idle, LOW detection)
- Display: OLED SSD1306 (I2C), 128x64 or 128x32 (configurable)
- Memory: 4MB Flash, ~500KB RAM
- WiFi: 2.4GHz, auto-reconnect, integrated web server

---

## 9. Troubleshooting

- Check wiring, power supply, WiFi configuration
- See [docs/TROUBLESHOOTING.md](docs/TROUBLESHOOTING.md)

---

## 10. Versions

**Current Version: v5.6.4** (2026-02-02)
See [CHANGELOG.md](./CHANGELOG.md)

---

## 11. Documentation

- [User Guide](docs/USER_GUIDE.md)
- [Technical Architecture](docs/ARCHITECTURE.md)
- [Pin Mapping](docs/PIN_MAPPING.md)
- [Troubleshooting](docs/TROUBLESHOOTING.md)
- [Release Notes](docs/RELEASE_NOTES.md)

---

## 12. Contributing

1. Fork the project
2. Create a branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -m 'Add feature'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

---

## 13. License

This project is provided as-is for educational and personal use.

---

## 14. Author

ESP32 project for bi-directional LED garlands with advanced animations and smart modes.

---

## 15. Acknowledgements

- PlatformIO team
- Adafruit (NeoPixel, U8g2 libraries)
- ESP32 community
- TB6612FNG module

### OLED Display
- Shows project name and version
- Shows IP address
- Shows mode and current animations

See [docs/PIN_MAPPING.md](docs/PIN_MAPPING.md) for wiring details.

---

## 📁 Project Structure

```
Anim-Guirlande/
├── include/
│   ├── board_config.h        # ESP32/S3 pin mapping
│   ├── config.h              # General configuration
│   ├── secrets.h             # WiFi networks credentials
│   ├── display_oled.h        # OLED display management
│   ├── garland_control.h     # Garland control and animations
│   ├── web_interface.h       # HTTP handlers
│   ├── web_pages.h           # HTML generator
│   └── web_styles.h          # CSS styles
├── src/
│   ├── main.cpp              # Entry point
│   ├── display_oled.cpp      # OLED display implementation
│   └── garland_control.cpp   # Animation implementation
├── docs/
│   ├── PIN_MAPPING.md        # Connection schematics
│   ├── ARCHITECTURE.md       # Technical documentation
│   ├── USER_GUIDE.md         # User guide
│   └── TROUBLESHOOTING.md    # Troubleshooting guide
├── platformio.ini            # PlatformIO configuration
├── README.md                 # This file
├── README_FR.md              # French version
├── CHANGELOG.md              # Version history (English)
└── CHANGELOG_FR.md           # Version history (French)
```

---

## 🔧 Advanced Configuration

### Disable Displays
In `include/config.h`:
```cpp
// #define HAS_OLED_U8G2   // Comment to disable OLED
```

### Adjust Motion Detection Duration
In `include/garland_control.h`:
```cpp
#define MOTION_TRIGGER_DURATION 30000  // Duration in ms after detection
```

---

## 📊 Technical Specifications

### LED Garland
- Type: 2-wire with anti-parallel LEDs
- Configuration: ~25 LEDs Direction A + ~25 LEDs Direction B
- Control: 8-bit PWM (0-255) at 5000 Hz
- Module: TB6612FNG (dual H-bridge)

### TB6612FNG Control Logic
- Direction 0 (Off): AIN1=LOW, AIN2=LOW
- Direction 1 (Forward A): AIN1=HIGH, AIN2=LOW
- Direction 2 (Backward B): AIN1=LOW, AIN2=HIGH
- Direction 3 (Brake): AIN1=HIGH, AIN2=HIGH
- STBY must be HIGH to enable

### Sensors
- **PIR**: Digital signal (HIGH = motion detected)

### Memory (ESP32-S3 N16R8)
- Flash: 16 MB (huge_app partition)
- PSRAM: 8 MB (80 MHz Octal)
- RAM: ~500 KB (heap + PSRAM)

### WiFi
- Multi-network automatic (WiFiMulti)
- Auto-reconnect on loss
- Web server on port 80

---

## 🚀 Startup Behavior

At boot, the system initializes with:
- **Animation Mode**: `AUTO` - Cycles through all 14 animations (30 seconds each)
- **Operating Mode**: `PERMANENT` - Garland always on
- **Display**: Shows animation name and IP address on OLED

Change these defaults in `src/garland_control.cpp`:
```cpp
static GarlandAnimation currentAnimation = ANIM_AUTO;    // Change to any animation
static GarlandMode currentMode = MODE_PERMANENT;         // Or MODE_MOTION_TRIGGER
```

---

## 🐛 Troubleshooting

### Garland Doesn't Light Up
- Check TB6612FNG wiring (VCC, GND, VM)
- Ensure STBY is HIGH
- Test with simple animation (e.g., Blink)
- Verify power supply voltage/current

### PIR Sensor Detects Continuously
- Adjust sensitivity (potentiometer on module)
- Check PIR delay timeout setting
- Move away from heat sources

### ESP32 Doesn't Connect to WiFi
- Verify `secrets.h` (correct SSID and password)
- Ensure 2.4 GHz WiFi (not 5 GHz)
- Check serial monitor for errors
- Try moving closer to router

### OLED Screen Black
- Check I2C address (0x3C or 0x3D)
- Test with I2C scanner
- Verify SDA/SCL connections
- Check 3.3V power supply

### Buttons Don't Respond
- Verify GPIO pins are not INPUT_ONLY
- Check pull-up configuration
- Test with multimeter
- Ensure proper grounding

---

## 📝 Versions

**Current Version: v5.6.4** (2026-02-02)

See [CHANGELOG.md](./CHANGELOG.md) for complete history.

---

## 📚 Documentation

- **[README_FR.md](./README_FR.md)** - French version
- **[CHANGELOG.md](./CHANGELOG.md)** - Version history (English)
- **[CHANGELOG_FR.md](./CHANGELOG_FR.md)** - Version history (French)
- **[docs/PIN_MAPPING.md](./docs/PIN_MAPPING.md)** - Detailed connection schematics
- **[docs/ARCHITECTURE.md](./docs/ARCHITECTURE.md)** - Code architecture
- **[docs/USER_GUIDE.md](./docs/USER_GUIDE.md)** - Complete user guide
- **[docs/TROUBLESHOOTING.md](./docs/TROUBLESHOOTING.md)** - Detailed troubleshooting

---

## 🤝 Contributing

Contributions are welcome! Please:
1. Fork the project
2. Create a branch (`git checkout -b feature/improvement`)
3. Commit changes (`git commit -m 'Add feature'`)
4. Push to branch (`git push origin feature/improvement`)
5. Open a Pull Request

---

## 📄 License

This project is provided as-is for educational and personal use.

---

## 👤 Author

Created as a specialized ESP32 project for controlling bi-directional LED garlands with advanced animations and smart operating modes.

---

## 🙏 Acknowledgments

- PlatformIO team for the excellent development platform
- Adafruit for display and sensor libraries
- ESP32 community for Arduino framework support
- TB6612FNG module for reliable motor/LED control

## 📄 Licence

Ce projet est libre d'utilisation pour projets personnels et éducatifs.

## ✨ Remerciements

* Adafruit pour les bibliothèques NeoPixel et U8g2
* PlatformIO pour l'environnement de développement
* Communauté ESP32 pour le support et documentation

---

**Projet Anim-Guirlande v5.6.4** - Animations de guirlande LED avec ESP32 🎄✨
## 🌍 Internationalization & Language Policy

As of version 5.3.3, all user-facing and log messages in the codebase are in English only (except *_FR.md documentation files). This ensures full internationalization and easier maintenance for all users and contributors. See the [CHANGELOG](CHANGELOG.md) for details.
