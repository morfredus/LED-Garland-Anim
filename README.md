pio run -e esp32s3_n16r8 -t upload

---
# LED-Garland-Anim

**Version: 1.2.2** (2025-12-31)

Controller for bi-directional LED garland animation on ESP32 Classic (IdeaSpark/DevKitC) with ST7789 display, auto-detection of PIR/RCWL-0516, web interface, physical buttons, 11 animations, smart modes, persistent configuration.

---

## 1. Required Hardware

- **ESP32 Classic board (IdeaSpark/DevKitC)**
- **TB6612FNG dual H-bridge driver**
- **2-wire LED garland** (anti-parallel LEDs, ~50 LEDs)
- **Motion sensor**: PIR HC-SR501 or RCWL-0516 (auto-detected)
- **TFT ST7789 display** (optional)
- **RGB NeoPixel LED** WS2812B (optional)
- **Suitable power supply** for the garland

### Main pinout summary (ESP32 Classic)
TB6612FNG :
  PWMA  → GPIO 12
  AIN1  → GPIO 25
  AIN2  → GPIO 33
  STBY  → GPIO 14
MOTION_SENSOR_PIN (PIR/RCWL-0516) → GPIO 35
LCD_MOSI → GPIO 23
LCD_SCLK → GPIO 18
LCD_CS   → GPIO 15
LCD_DC   → GPIO 2
LCD_RST  → GPIO 4
LCD_BLK  → GPIO 32
BTN1     → GPIO 16
BTN2     → GPIO 17

---

## 2. Key Features

- Control a 2-wire LED garland with ESP32 Classic
- 11 spectacular animations
- 2 smart operating modes (Permanent, Motion Trigger)
- Auto-detection of PIR HC-SR501 or RCWL-0516
- Color ST7789 display (optional)
- Full-featured web interface
- Physical button controls
- Persistent configuration (NVS)
- OTA updates

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
3. In `platformio.ini`, use only:
   - `esp32devkitc`: ESP32 Classic (4MB Flash)
4. Wire the components as shown above
5. Build and upload
   ```bash
   pio run -e esp32devkitc
   pio run -e esp32devkitc -t upload
   pio device monitor
   ```

---

## 5. Usage

### Startup
1. The garland starts in **Auto** animation and **Permanent** mode
2. The display shows WiFi progress then the IP address
3. Web access: `http://[ESP32_IP]`

### Physical controls
- **Button 1**: Next animation / auto mode
- **Button 2**: Change mode
- **BOOT button**: Restart (long press)

### Web interface
- Dashboard, animation/mode selection, sensor visualization, remote actions

### Telegram bot (optional)
- Commands `/anim`, `/mode`, `/nextanim`, `/nextmode`, `/status`, `/list`

---


## 6. OTA Updates (Over-the-Air)

Starting from v1.3.0, the firmware supports OTA updates using ArduinoOTA.

**How to use:**
1. Connect the ESP32 to WiFi (see above).
2. In PlatformIO or Arduino IDE, select "Upload using OTA" (the device appears as `LED-Garland-Anim.local`).
3. The device will reboot automatically after a successful upload.

**Security note:** OTA is enabled only when the ESP32 is connected to WiFi.

---
## 7. Advanced Configuration

In `include/config.h`:
```cpp
// #define HAS_OLED        // Comment to disable
// #define HAS_ST7789      // Comment to disable
```
In `include/garland_control.h`:
```cpp
#define MOTION_TRIGGER_DURATION 30000  // Duration in ms after detection
```

---

## 7. Technical Specifications

- LED garland: 2 wires, anti-parallel LEDs, 8-bit PWM 5kHz
- TB6612FNG: dual H-bridge, direction/intensity control
- Sensors: PIR (LOW idle, HIGH detection), RCWL-0516 (HIGH idle, LOW detection)
- Display: ST7789 1.14" 135x240px (optional)
- Memory: 4MB Flash, ~500KB RAM
- WiFi: 2.4GHz, auto-reconnect, integrated web server

---

## 8. Troubleshooting

- Check wiring, power supply, WiFi configuration
- See [docs/TROUBLESHOOTING.md](docs/TROUBLESHOOTING.md)

---

## 9. Versions

**Current Version: v1.2.2** (2025-12-31)
See [CHANGELOG.md](./CHANGELOG.md)

---

## 10. Documentation

- [User Guide](docs/USER_GUIDE.md)
- [Technical Architecture](docs/ARCHITECTURE.md)
- [Pin Mapping](docs/PIN_MAPPING.md)
- [Troubleshooting](docs/TROUBLESHOOTING.md)
- [Release Notes](docs/RELEASE_NOTES.md)

---

## 11. Contributing

1. Fork the project
2. Create a branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -m 'Add feature'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

---

## 12. License

This project is provided as-is for educational and personal use.

---

## 13. Author

ESP32 project for bi-directional LED garlands with advanced animations and smart modes.

---

## 14. Acknowledgements

- PlatformIO team
- Adafruit (GFX, NeoPixel, ST7789 libraries)
- ESP32 community
- TB6612FNG module
  - `/mode <id|name>` (e.g. `/mode 1`, `/mode detect`)
  - `/nextanim`, `/nextmode`
  - `/liste` (lists all modes and animations with IDs)

### OLED Display
- Shows current animation name
- Shows IP address
- Animated visualization bar at bottom (14 distinct patterns)

You can use either the ESP32 IdeaSpark board (recommended) or any ESP32 board with a compatible ST7789 display. You must respect the default pin mapping:
- LCD_MOSI 23
- LCD_SCLK 18
- LCD_DC    2
- LCD_RST   4
- LCD_BLK  32

See [docs/PIN_MAPPING.md](docs/PIN_MAPPING.md) for details.

---

## 📁 Project Structure

```
Anim-Guirlande/
├── include/
│   ├── board_config.h        # ESP32/S3 pin mapping
│   ├── config.h              # General configuration
│   ├── secrets.h             # WiFi networks + Telegram credentials
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

**Current Version: v1.2.1** (2025-12-31)

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
