# LED-Garland-Anim

**Version 1.0.0** - Bi-directional LED Garland Animation Controller for ESP32 IdeaSpark

Control a 2-wire garland with anti-parallel LEDs via TB6612FNG motor driver module. Features 11 spectacular animations with vibrant LCD visualizations, Auto mode with instant start, 2 smart operating modes, integrated ST7789 1.14" color display, web interface, and physical button controls.

[🇫🇷 Version française](README_FR.md) | [📝 Changelog](CHANGELOG.md) | [📚 Documentation](docs/) | [📋 Release Notes](docs/RELEASE_NOTES.md)

---

## 🎯 Version 1.0.0 - ESP32 IdeaSpark Platform

This major release focuses exclusively on the **ESP32 IdeaSpark** board with integrated **ST7789 1.14" LCD display** (135×240 pixels). All ESP32-S3 and legacy display support (OLED/TFT) has been removed for a streamlined, modern platform.

### 🆕 What's New in v1.0.0
- ✨ **Modern ST7789 LCD Interface** - Vibrant color display with smooth animations
- 🎨 **11 Animated Visualizations** - Each animation has its unique visual representation
- 📱 **WiFi Network Display** - SSID and IP always visible on main screen
- 🐛 **Motion Detection Fix** - Edge-triggered timer now works correctly
- 🔧 **Simplified Platform** - ESP32 IdeaSpark only, 15% code reduction

---

## ✨ Key Features

### 🎄 11 Spectacular Garland Animations
- **Off**: Garland disabled (red "OFF" text)
- **Alternating Fade**: Smooth transition with yellow/blue gradient bars
- **Blink Alternate**: Fast alternation between Direction A and B
- **Pulse**: Simultaneous beat with growing purple circle
- **Breathing**: Slow intensity rise/fall with cyan fade
- **Strobe**: Rapid stroboscopic white flashes
- **Heartbeat**: Double-beat red pulsation (♥️ BOM-bom...)
- **Wave**: Smooth cyan sinusoidal wave
- **Sparkle**: 15 random twinkling yellow dots
- **Meteor**: Orange/yellow trailing light effect
- **Auto Mode**: Cycles through all animations (30s each) with dual orbiting circles

### 🎮 2 Smart Operating Modes
- **Permanent**: Always on (default at startup)
- **Motion Trigger**: PIR sensor activation (30s after motion detection with edge detection)

### 🖥️ ST7789 1.14" LCD Display (135×240 pixels)
- **Boot Screen**: Project name, version, WiFi connection progress bar
- **Main Screen**:
  - Application name and version (centered)
  - WiFi network info (SSID + IP address)
  - Current mode and animation names
  - Large animated visualization zone (234×57 pixels)
- **11 Distinct Visual Animations**: Smooth, colorful, modern effects at 10 FPS
- **Professional UI**: Cyan separators, color-coded labels, optimized layout

### 🌐 Web Interface
- **Complete Dashboard**: System info, memory, WiFi stats
- **Garland Control**: Animation and mode selection (2 modes, 11 animations incl. Auto)
- **Sensor Visualization**: PIR motion status
- **Remote Actions**: Refresh and restart
- **Real-time Updates**: Display updates via web interface

### 🔘 Physical Controls
- **Button BOOT (GPIO 0)**: Restart on long press (1s)
- **Button 1 (GPIO 16)**: Animation change + auto mode access
- **Button 2 (GPIO 17)**: Operating mode change

### 🔧 Technical Features
- **Single Platform**: ESP32 IdeaSpark 1.14" LCD only
- **WiFiMulti**: Automatic connection to multiple networks
- **TB6612FNG Module**: Bi-directional garland control (PWM 0-255, 5000 Hz)
- **PIR Sensor**: HC-SR501 motion detection with edge triggering
- **Persistent Settings**: NVS storage for mode, animation, and durations
- **Optimized Code**: 15% reduction from multi-platform v0.x.x

---

## 📋 Requirements

### Software
- **PlatformIO** (VS Code extension or CLI recommended)
- **Python 3.x** (for PlatformIO)
- **Git** (for version control)

### Hardware
- **ESP32 IdeaSpark 1.14" LCD** board (with integrated ST7789 display)
- **TB6612FNG** module (dual H-bridge motor controller)
- 2-wire LED garland (anti-parallel LEDs, ~50 LEDs total)
- **PIR HC-SR501** sensor (for motion trigger mode)
- 2x **Push buttons** (for user controls)
- Suitable power supply:
  - ESP32: 5V via USB-C (500mA+)
  - TB6612FNG: 5-15V external (1-2A depending on garland)

### Not Supported in v1.0.0
- ❌ ESP32-S3 boards (removed)
- ❌ OLED displays (SSD1306)
- ❌ Other TFT displays (ILI9341, etc.)
- ❌ LDR light sensor

---

## 🛠️ Installation

### 1. Clone the Project
```bash
git clone https://github.com/your-username/LED-Garland-Anim.git
cd LED-Garland-Anim
```

### 2. Configure `include/secrets.h`
Create or edit `include/secrets.h` to set your WiFi networks:

```cpp
#ifndef SECRETS_H
#define SECRETS_H

// WiFi networks (will connect to first available)
const char* WIFI_NETWORKS[][2] = {
    {"YourSSID1", "YourPassword1"},
    {"YourSSID2", "YourPassword2"},
    {nullptr, nullptr}  // Terminator
};

// Optional: Telegram bot (if using telegram_control.cpp)
#define TELEGRAM_BOT_TOKEN "your_bot_token"
#define TELEGRAM_CHAT_ID "your_chat_id"

#endif
```

### 3. Hardware Wiring

Consult **[docs/PIN_MAPPING.md](./docs/PIN_MAPPING.md)** for detailed connection schematics.

#### ESP32 IdeaSpark Pin Summary:
```
LCD ST7789 (Integrated on PCB):
  MOSI  → GPIO 23
  SCLK  → GPIO 18
  CS    → GPIO 15
  DC    → GPIO 2
  RST   → GPIO 4
  BLK   → GPIO 32  ⚠️ MUST BE HIGH

TB6612FNG Motor Driver:
  PWMA  → GPIO 12
  AIN1  → GPIO 25
  AIN2  → GPIO 33
  STBY  → GPIO 14

Sensors:
  PIR   → GPIO 35 (input-only pin)

Buttons:
  BTN1  → GPIO 16
  BTN2  → GPIO 17
  BOOT  → GPIO 0 (integrated)

I2C (available for expansion):
  SDA   → GPIO 21
  SCL   → GPIO 22
```

**⚠️ Critical**: GPIO 32 (LCD_BLK) must be set HIGH to see the display!

### 4. Compile and Upload

```bash
# Build for ESP32 IdeaSpark (only supported platform)
pio run -e esp32devkitc

# Upload to board
pio run -e esp32devkitc -t upload

# Monitor serial output
pio device monitor
```

**Note**: The default environment is `esp32devkitc` configured for ESP32 IdeaSpark.

---

## 📡 Usage

### Startup Sequence
1. **Boot Screen**: Displays project name, version, and WiFi connection progress
2. **WiFi Connection**: Connects to first available network from secrets.h
3. **Main Screen**: Shows WiFi info (SSID + IP), mode, animation, and visual
4. **Telegram Notification**: Sends startup message with network details (if configured)
5. **Web Interface**: Available at `http://[ESP32_IP]`

### Physical Controls
- **Button 1 (GPIO 16)**:
  - Short press: Next animation
  - Cycles through: Off → Fade → Blink → Pulse → Breathing → Strobe → Heartbeat → Wave → Sparkle → Meteor → Auto → Off...
- **Button 2 (GPIO 17)**:
  - Short press: Next mode
  - Cycles through: Permanent → Motion Trigger → Permanent...
- **BOOT Button (GPIO 0)**:
  - Long press (1s): Restart ESP32

### Web Interface
Navigate to `http://[ESP32_IP]` for:
- **Dashboard**: System information (free memory, uptime, WiFi signal)
- **Garland Control**: Select animation (11 options) and mode (2 options)
- **Sensor Status**: PIR motion sensor state
- **Actions**: Refresh data or restart device

### Main LCD Display
```
┌──────────────────────────────┐
│ LED-Garland-Anim    (center) │  ← App name
│ v1.0.0              (center) │  ← Version
├──────────────────────────────┤
│ Mode: Permanent              │  ← Current mode
│ Anim: Fade Alterne           │  ← Current animation
├──────────────────────────────┤
│ SSID: MyWiFi                 │  ← WiFi network
│ IP: 192.168.1.100            │  ← IP address
├──────────────────────────────┤
│ ┌──────────────────────────┐ │
│ │  [Animated Visual]       │ │  ← 234×57px animation zone
│ └──────────────────────────┘ │
└──────────────────────────────┘
```

Each animation has its own unique visual:
- **Fade Alternate**: Yellow/blue gradient bars
- **Pulse**: Growing/shrinking purple circle
- **Heartbeat**: Red double-pulse effect
- **Auto**: Green text with orbiting circles
- And 7 more...

---

## 📊 Pin Mapping Changes (v1.0.0)

| Signal | Old (v0.x) | New (v1.0.0) | Reason |
|--------|-----------|--------------|---------|
| TB6612_AIN1 | GPIO 32 | **GPIO 25** | GPIO 32 needed for LCD backlight |
| PIR_SENSOR | GPIO 14 | **GPIO 35** | GPIO 35 is input-only (optimal for sensors) |
| LDR_SENSOR | GPIO 15 | **Removed** | Light sensor not used in v1.0.0 |

**Complete mapping**: See [docs/PIN_MAPPING.md](./docs/PIN_MAPPING.md)

---

## 🔧 Configuration

### Animation Duration (Auto Mode)
Default: 30 seconds per animation

Change via web interface or edit in `include/garland_control.h`:
```cpp
#define AUTO_MODE_INTERVAL 30000  // milliseconds
```

### Motion Detection Duration
Default: 30 seconds after motion detected

Change via web interface or edit in `include/garland_control.h`:
```cpp
#define MOTION_TRIGGER_DURATION 30000  // milliseconds
```

### Display Backlight
The LCD backlight is controlled by GPIO 32 and set HIGH automatically in `setupDisplay()`. To adjust:

```cpp
pinMode(LCD_BLK, OUTPUT);
digitalWrite(LCD_BLK, HIGH);  // ON (required to see display)
// digitalWrite(LCD_BLK, LOW);  // OFF (screen goes dark)
```

---

## 📁 Project Structure

```
LED-Garland-Anim/
├── include/
│   ├── board_config.h        # ESP32 IdeaSpark pin mapping
│   ├── config.h              # General configuration (ST7789, colors)
│   ├── secrets.h             # WiFi networks (user-created)
│   ├── display.h             # ST7789 display management
│   ├── garland_control.h     # Garland animations & modes
│   ├── web_interface.h       # HTTP handlers
│   ├── web_pages.h           # HTML generator
│   └── telegram_control.h    # Telegram bot (optional)
├── src/
│   ├── main.cpp              # Entry point
│   ├── display.cpp           # Display implementation
│   ├── garland_control.cpp   # Animation logic
│   └── telegram_control.cpp  # Telegram bot implementation
├── docs/
│   ├── PIN_MAPPING.md        # Complete wiring guide
│   ├── ARCHITECTURE.md       # Technical documentation
│   ├── USER_GUIDE.md         # User manual
│   ├── TROUBLESHOOTING.md    # Common issues & solutions
│   ├── RELEASE_NOTES.md      # v1.0.0 release highlights
│   └── *_FR.md               # French versions
├── platformio.ini            # PlatformIO configuration
├── CHANGELOG.md              # Version history
└── README.md                 # This file
```

---

## 🐛 Troubleshooting

### LCD Display is Black
1. **Check backlight**: GPIO 32 (LCD_BLK) must be HIGH
2. **Verify wiring**: SPI pins (MOSI, SCLK, CS, DC, RST)
3. **Power supply**: Ensure 3.3V is stable
4. **Test code**:
```cpp
pinMode(LCD_BLK, OUTPUT);
digitalWrite(LCD_BLK, HIGH);
display.fillScreen(ST77XX_WHITE);  // Should show white screen
```

### Garland Doesn't Light Up
1. **TB6612FNG STBY**: Must be HIGH to enable module
2. **External power**: Check 5-15V supply on VM pin
3. **Common GND**: Verify GND connection between ESP32 and TB6612FNG
4. **Test animation**: Try "Pulse" (simple, easy to debug)

### Motion Detection Not Working
1. **PIR sensitivity**: Adjust potentiometer on HC-SR501
2. **Power**: Ensure PIR has 5V supply
3. **Timer issue**: Check serial monitor for debug logs (every 5s)
4. **Pin**: Verify GPIO 35 connection (input-only pin)

### WiFi Won't Connect
1. **secrets.h**: Verify SSID and password
2. **2.4GHz**: ESP32 only supports 2.4GHz WiFi (not 5GHz)
3. **Serial monitor**: Check connection attempts and errors
4. **Signal**: Move closer to router

### Buttons Don't Respond
1. **Wiring**: Check connection to GND
2. **Pull-up**: Internal pull-ups enabled in software
3. **Test**: Should read 3.3V when not pressed, 0V when pressed
4. **GPIO**: Ensure correct pins (16, 17, 0)

For more solutions, see [docs/TROUBLESHOOTING.md](./docs/TROUBLESHOOTING.md)

---

## 📊 Technical Specifications

### Display
- **Model**: ST7789 TFT LCD 1.14"
- **Resolution**: 135×240 pixels
- **Color**: RGB565 (16-bit, 65K colors)
- **Interface**: Hardware SPI
- **Refresh Rate**: 10 FPS for animations
- **Orientation**: Landscape (rotation = 1)

### LED Garland Control
- **Type**: 2-wire with anti-parallel LEDs
- **Configuration**: ~25 LEDs per direction (50 total)
- **Controller**: TB6612FNG dual H-bridge
- **PWM**: 8-bit (0-255) at 5000 Hz
- **Directions**: Forward (A), Reverse (B), Off, Brake

### Memory & Performance
- **Flash**: 4MB (ESP32 Classic)
- **RAM**: ~320KB
- **Free Heap**: ~200KB typical
- **Code Size**: ~800KB compiled
- **CPU**: 240 MHz dual-core

### Power Consumption
- **ESP32 + LCD**: ~150mA @ 5V (USB)
- **LED Garland**: Variable (depends on brightness and power supply)
- **Total**: Recommend 2A @ 5V supply for safety

---

## 🚀 Roadmap / Future Ideas

- 🔮 Additional animation effects
- 🔮 MQTT integration for home automation
- 🔮 Multi-garland synchronization
- 🔮 Temperature/humidity sensor reactive effects
- 🔮 Music reactive mode (microphone input)
- 🔮 Custom animation editor via web interface

---

## 📝 Version History

**Current**: v1.0.0 (2025-12-30)

See [CHANGELOG.md](./CHANGELOG.md) for complete version history.

Major versions:
- **v1.0.0** (2025-12-30): ESP32 IdeaSpark platform, ST7789 LCD, WiFi display
- **v0.8.0** (2025-12-29): GPIO naming convention update
- **v0.7.0** (2025-12-30): LCD ST7789 and button pin updates
- **v0.6.3** (2025-12-13): 5 new animations (Strobe, Heartbeat, Wave, Sparkle, Meteor)
- **v0.1.0** (2025-12-09): Initial release with garland control

---

## 🤝 Contributing

Contributions are welcome! Please:
1. Fork the project
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -m 'Add feature'`)
4. Push to branch (`git push origin feature/improvement`)
5. Open a Pull Request

---

## 📄 License

This project is provided as-is for educational and personal use.

---

## 🙏 Acknowledgments

- **Adafruit** - GFX, NeoPixel, and ST7789 libraries
- **PlatformIO** - Excellent development platform
- **ESP32 Community** - Arduino framework support
- **Toshiba** - TB6612FNG motor driver IC

---

**LED-Garland-Anim v1.0.0** - Modern LED Garland Controller for ESP32 IdeaSpark 🎄✨
