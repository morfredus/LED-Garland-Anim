# LED-Garland-Anim

**Version 0.2.0** - Bi-directional LED Garland Animation Controller for ESP32/ESP32-S3

Control a 2-wire garland with anti-parallel LEDs via TB6612FNG motor driver module. Features 14 animations, 4 smart operating modes, OLED display with animated visualization, web interface with schedule configuration, and physical button controls.

[🇫🇷 Version française](README_FR.md) | [📝 Changelog](CHANGELOG.md) | [📚 Documentation](docs/)

---

## ✨ Key Features

### 🎄 14 Garland Animations
- **Alternating Fade**: Smooth transition between both LED directions
- **Blink**: Fast alternation between Direction A and B
- **Smooth Wave**: Fluid wave effect
- **Strobe**: Fast alternating flash
- **Pulse**: Simultaneous beat of both directions
- **Chase**: Racing effect between LEDs
- **Heartbeat**: Characteristic double pulse
- **Sparkle**: Random twinkling
- **Rainbow**: Simulated multicolor wave
- **Breathing**: Slow intensity rise/fall
- **Fire**: Flame effect simulation
- **Soft Blink**: Sinusoidal transition
- **Meteor**: Fading light trail
- **Auto Mode**: Cycle through all animations (30s each)

### 🎮 4 Smart Operating Modes
- **Permanent**: Always on
- **Scheduled**: Activation based on time schedules (with web configuration)
- **Motion Trigger**: PIR sensor activation (30s after detection)
- **Night Off**: Automatic shutdown based on ambient light (LDR)

### 🖥️ OLED Real-time Display
- Live display of current animation and mode names
- Local IP address for web access
- Animated visualization bar (14 distinct patterns)
- Adaptive layout for 128x32 and 128x64 screens
- 10 FPS refresh rate for smooth animations

### 🌐 Web Interface
- **Complete Dashboard**: System info, memory, WiFi stats
- **Garland Control**: Animation and mode selection
- **Schedule Configuration**: Set start/end times for scheduled mode
- **Sensor Visualization**: PIR status, light level, night detection
- **Remote Actions**: Refresh and restart

### 🔘 Physical Controls
- **Button 0 (BOOT)**: Restart on long press (1s)
- **Button 1**: Animation change + auto mode access
- **Button 2**: Operating mode change

### 📱 Display & Feedback
- **OLED SSD1306 Support**: WiFi progress, IP, real-time info
- **TFT ST7789 Support**: High-resolution color display
- **NeoPixel RGB LED**: Visual status feedback
- **Multi-display**: OLED and TFT simultaneously

### 🔌 Supported Hardware
- **Multi-Board**: ESP32-S3 (N16R8, N8R8) and ESP32 Classic (DevKitC)
- **WiFiMulti**: Automatic connection to multiple networks
- **TB6612FNG Module**: Bi-directional garland control
- **PIR Sensor**: HC-SR501 motion detection (optional)
- **LDR Photoresistor**: Day/night detection (optional)

---

## 📋 Requirements

### Software
- **PlatformIO** (VS Code extension or CLI)
- **Python 3.x** (for PlatformIO)
- **Git** (for version control)

### Hardware
- **ESP32-S3 DevKitC-1** or **ESP32 DevKitC** board
- **TB6612FNG** module (dual H-bridge motor controller)
- 2-wire LED garland (anti-parallel LEDs, ~50 LEDs total)
- **PIR HC-SR501** sensor (optional)
- **LDR** photoresistor + 10kΩ resistor (optional)
- **OLED SSD1306** 128x32 or 128x64 display (optional)
- **TFT ST7789** 240x240 display (optional)
- **NeoPixel RGB LED** WS2812B (optional)
- Suitable power supply for garland (check voltage/current)

---

## 🛠️ Installation

### 1. Clone the Project
```bash
git clone <your-repo>
cd Anim-Guirlande
```

### 2. Create `secrets.h` File
The `include/secrets.h` file is ignored by Git. Create it manually:

```cpp
// include/secrets.h
#ifndef SECRETS_H
#define SECRETS_H

const char* WIFI_NETWORKS[][2] = {
    {"Home_SSID", "Password123"},
    {"Office_SSID", "Password456"},
    {"Phone_Hotspot", "12345678"}
};

#endif
```

### 3. Configure PlatformIO
Modify build paths in `platformio.ini` (optional):

```ini
build_dir       = C:/pio_builds/LED-Garland-Anim/build
build_cache_dir = C:/pio_builds/LED-Garland-Anim/cache
```

### 4. Select Environment
Choose your board in `platformio.ini`:
- `esp32s3_n16r8`: ESP32-S3 with 16MB Flash / 8MB PSRAM (default)
- `esp32s3_n8r8`: ESP32-S3 with 8MB Flash / 8MB PSRAM
- `esp32devkitc`: ESP32 Classic (4MB Flash)

### 5. Wire Components
Consult **[docs/PIN_MAPPING.md](./docs/PIN_MAPPING.md)** for detailed connection schematics.

#### ESP32-S3 Pin Summary:
```
TB6612FNG:
  PWMA  → GPIO 5
  AIN1  → GPIO 6
  AIN2  → GPIO 4
  STBY  → GPIO 8

Sensors:
  PIR   → GPIO 14
  LDR   → GPIO 15 (ADC)

Buttons:
  BTN1  → GPIO 16
  BTN2  → GPIO 17

Displays:
  OLED SDA → GPIO 21
  OLED SCL → GPIO 22
```

#### ESP32 Classic Pin Summary:
```
TB6612FNG:
  PWMA  → GPIO 25
  AIN1  → GPIO 32
  AIN2  → GPIO 33
  STBY  → GPIO 14

Sensors:
  PIR   → GPIO 36
  LDR   → GPIO 39 (ADC)

Buttons:
  BTN1  → GPIO 4
  BTN2  → GPIO 15

Displays:
  OLED SDA → GPIO 21
  OLED SCL → GPIO 22
```

### 6. Compile and Upload
```bash
# Build
pio run -e esp32s3_n16r8

# Upload
pio run -e esp32s3_n16r8 -t upload

# Serial Monitor
pio device monitor
```

---

## 📡 Usage

### Startup
1. Garland starts with **Alternating Fade** animation in **Permanent** mode
2. OLED/TFT display shows WiFi connection progress
3. Once connected, IP address is displayed for 3 seconds
4. Access web interface: `http://[ESP32_IP]`

### Physical Controls
- **Button 1**: Cycle through animations (or enter auto mode)
- **Button 2**: Change operating mode
- **BOOT Button (long press)**: Restart ESP32

### Web Interface
- **Animation Selector**: Choose from 15 animations
- **Mode Selector**: Switch between 4 operating modes
- **Schedule Configuration**: Set start/end times for scheduled mode
- **Refresh Button**: Update system information
- **Restart Button**: Remote restart

### OLED Display
- Shows current animation name
- Shows current operating mode
- Shows IP address
- Animated visualization bar at bottom (14 distinct patterns)

---

## 📁 Project Structure

```
Anim-Guirlande/
├── include/
│   ├── board_config.h        # ESP32/S3 pin mapping
│   ├── config.h              # General configuration
│   ├── secrets.h             # WiFi credentials (not versioned)
│   ├── display.h             # OLED/TFT display management
│   ├── garland_control.h     # Garland control and animations
│   ├── web_interface.h       # HTTP handlers
│   ├── web_pages.h           # HTML generator
│   └── web_styles.h          # CSS styles
├── src/
│   ├── main.cpp              # Entry point
│   ├── display.cpp           # Display implementation
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
// #define HAS_OLED        // Comment to disable
// #define HAS_ST7789      // Comment to disable
```

### Adjust Motion Detection Duration
In `include/garland_control.h`:
```cpp
#define MOTION_TRIGGER_DURATION 30000  // Duration in ms after detection
```

### Adjust Night Threshold
In `include/garland_control.h`:
```cpp
#define NIGHT_THRESHOLD 500  // ADC value (0-4095), lower = darker
```

### Change Schedule Default Times
In `src/garland_control.cpp`:
```cpp
static uint8_t scheduleStartHour = 18;    // Start hour (0-23)
static uint8_t scheduleStartMinute = 0;   // Start minute (0-59)
static uint8_t scheduleEndHour = 23;      // End hour (0-23)
static uint8_t scheduleEndMinute = 0;     // End minute (0-59)
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
- **LDR**: 12-bit analog (0-4095)

### Memory (ESP32-S3 N16R8)
- Flash: 16 MB (huge_app partition)
- PSRAM: 8 MB (80 MHz Octal)
- RAM: ~500 KB (heap + PSRAM)

### WiFi
- Multi-network automatic (WiFiMulti)
- Auto-reconnect on loss
- Web server on port 80

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

**Current Version: v0.2.0** (2025-12-09)

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

* Adafruit pour les bibliothèques GFX, NeoPixel, OLED et ST7789
* PlatformIO pour l'environnement de développement
* Communauté ESP32 pour le support et documentation

---

**Projet Anim-Guirlande v0.1.0** - Animations de guirlande LED avec ESP32 🎄✨
