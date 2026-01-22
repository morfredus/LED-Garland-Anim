

# User Guide - LED-Garland-Anim v5.3.0

*This document is valid from version 5.3.0.*

## Supported Platforms
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32-C3 HW-675 (OLED)
- ESP32-S3 Mini (esp32s3_mini)

Complete user guide for the LED-Garland-Anim LED garland and 8x8 matrix animation controller (ESP32, OLED SSD1306 128x64 only).

**Document version: v5.3.0 (2026-01-22)**

---

## Table of Contents

1. [First Startup](#first-startup)
2. [Physical Controls](#physical-controls)
3. [Web Interface](#web-interface)
4. [OLED Display](#oled-display)
5. [Operating Modes](#operating-modes)
6. [Garland Animations](#garland-animations)
7. [Matrix Animations](#matrix-animations)
8. [Motion Sensor Auto-Detection](#motion-sensor-auto-detection)
9. [Configuration Persistence](#configuration-persistence)
10. [OTA Updates](#ota-updates)
11. [Troubleshooting](#troubleshooting)

---

## First Startup

### What to Expect
1. **OLED SSD1306** displays "Connecting to WiFi..."
2. **LED_BUILTIN** blinks blue during WiFi connection
3. After connection, **IP address** displayed for 3 seconds
4. **Garland** plays a 10-second intro animation (Fade Alternate), then switches to saved animation/mode
5. **8x8 Matrix** starts with saved animation
6. **LED_BUILTIN** turns green when ready

### Note Your IP Address
Write down the IP address shown on the OLED screen or check your router's DHCP list. You'll need it to access the web interface.

Example: `192.168.1.100`

---

## Physical Controls

### Button Locations
- **BUTTON_BOOT**: GPIO 0 (on board)
- **BUTTON_1**: GPIO 16 (animation change)
- **BUTTON_2**: GPIO 17 (mode change)

### Button Functions
- **BUTTON_1 (GPIO 16)**: Cycle through garland animations
- **BUTTON_2 (GPIO 17)**: Cycle through operating modes
- **BUTTON_BOOT (GPIO 0)**: Reserved for boot/programming

---

## Web Interface

### Features
- **Radio Button Grids**: All selections use intuitive radio buttons (no dropdowns)
- **Responsive Layout**: 2 columns on desktop, 1 column on mobile (<600px)
- **Instant Updates**: No "Apply" buttons - changes apply immediately
- **Visual Feedback**: Selected items highlighted in green, inline confirmation messages

### Access
- Open browser and navigate to the IP address shown on OLED
- Example: `http://192.168.1.100`

### Dashboard Sections

#### 1. Garland Parameters Card
- **Animation Selection**: 11 animations (radio buttons, 2 columns)
- **Mode Selection**: 3 operating modes (radio buttons)
- **Auto Mode Interval**: Duration of each animation in Auto mode (5-300 seconds)
- **Motion Detection Duration**: How long lights stay on after motion (5-600 seconds)
- **Actions**: Save, Restore, Erase configuration buttons

#### 2. 8x8 NeoPixel Matrix Card
- **Animation Selection**: 39 festive animations (radio buttons, 2 columns)
- **Brightness Control**: Slider (0-255) with live preview
- **Current Animation Display**: Shows active animation name

#### 3. WiFi Network Card
- **SSID**: Network name
- **IP Address**: Current device IP

#### 4. Action Buttons
- **Refresh**: Reload page data
- **OTA Update**: Upload new firmware via browser
- **Reboot**: Restart ESP32 (requires double-click confirmation)

---

## OLED Display

### Specifications
- **Type**: SSD1306 128x64 (JMD0.96D-1)
- **Interface**: I2C (SDA=4, SCL=5, address 0x3C)
- **Resolution**: 128×64 pixels, monochrome

### Display Information
- **Boot Screen**: Project name, version, WiFi connection progress
- **Status Screen**: Shows Program name, Version, SSID, IP address, and mDNS (`*.local`)
- **Info Frame**: Mode, WiFi SSID, IP, mDNS, current garland and matrix animation names
- **Animation Zone**: Real-time animation status and system messages

---

## Operating Modes

The system offers 3 operating modes:

### 1. Permanent Mode (MODE_PERMANENT)
- **Garland**: Always on
- **Matrix**: Always on
- **Use Case**: Continuous decoration, indoor display
- **Power**: Higher consumption (both devices always active)

### 2. Motion Detection - All (MODE_MOTION_TRIGGER)
- **Garland**: Activates on motion detection
- **Matrix**: Activates on motion detection (synchronized with garland)
- **Duration**: Stays on for configured time after last motion (default: 30 seconds)
- **Use Case**: Energy-saving mode for hallways, entryways
- **Power**: Lower consumption (devices sleep when no motion)

### 3. Motion Detection - Garland Only (MODE_MOTION_MATRIX_INDEPENDENT)
- **Garland**: Activates on motion detection
- **Matrix**: Always on (independent of motion)
- **Use Case**: Matrix provides ambient light, garland activates for special effect
- **Power**: Medium consumption (matrix always on, garland on-demand)

### Mode Indicators
- **Web Interface**: Current mode shown with radio button selection
- **OLED Display**: Mode displayed in status bar
- **LED_BUILTIN**: Green when ready, blue during WiFi connection

---

## Garland Animations

**Total: 11 animations**

| # | Name | Description |
|---|------|-------------|
| 0 | **Off** | Garland disabled |
| 1 | **Fade Alternate** | Smooth fading between two LED sets |
| 2 | **Blink Alternate** | Fast blinking alternation |
| 3 | **Pulse** | Synchronized pulsing effect |
| 4 | **Breathing** | Slow breathing effect (inhale/exhale) |
| 5 | **Strobe** | Rapid strobe light effect |
| 6 | **Heartbeat** | Double-beat heartbeat pattern |
| 7 | **Wave** | Traveling wave effect |
| 8 | **Sparkle** | Random sparkle effect |
| 9 | **Meteor** | Meteor shower effect |
| 10 | **Auto** | Automatically cycles through all animations |

### Auto Mode Behavior
- Cycles through animations 1-9 (excluding Off and Auto itself)
- Default interval: 30 seconds per animation
- Configurable: 5-300 seconds via web interface
- Works in all operating modes

### Garland & Matrix Auto Modes Are Independent
The **garland** and **matrix** have **separate Auto mode intervals**:

- **Garland Auto Mode**: Uses "Auto Mode Interval" setting in web interface
- **Matrix Auto Mode**: Uses "Matrix Animation Interval" setting in web interface
- Both can run simultaneously with different animation cycle durations
- Each interval is saved independently and restored on restart

**Example:** Garland cycles every 20 seconds while matrix cycles every 45 seconds.

---

## Matrix Animations

**Total: 39 animations** (8x8 NeoPixel WS2812B-64 matrix)

See the web interface for the full list and live preview.

---

## Motion Sensor Auto-Detection

### Supported Sensors (GPIO 35)

- **PIR Sensor (HC-SR501)**: Idle LOW, motion HIGH
- **Doppler Radar (RCWL-0516)**: Idle HIGH, motion LOW (inverted logic)

### Auto-Detection Feature
The firmware automatically detects which sensor type is connected:
1. Reads initial state on startup
2. Determines sensor type (PIR or Radar)
3. Adapts detection logic accordingly
4. **No configuration required** - plug and play

### Wiring
Connect sensor to GPIO 35 (see [docs/PIR_SENSOR_SETUP.md](PIR_SENSOR_SETUP.md) and [docs/RADAR_SENSOR_SETUP.md](RADAR_SENSOR_SETUP.md))

---

## Configuration Persistence

All settings are saved to ESP32's NVS (Non-Volatile Storage):

**Garland Settings:**
- Current animation
- Operating mode
- Auto mode interval (ms)
- Motion detection duration (ms)

**Matrix Settings:**
- Current animation
- Brightness level

### How It Works
- **On Startup**: Loads last saved configuration (or defaults if none)
- **On Change**: Automatically saves when changed via web interface
- **Persistence**: Survives reboots and power cycles
- **No User Action**: Fully automatic

---

## OTA Updates

### Web-Based OTA (Recommended)
See detailed guide: [docs/OTA_UPDATE.md](OTA_UPDATE.md)

1. Click "OTA Update" button on dashboard
2. Select compiled `.bin` file
3. Click "Upload Firmware" (requires double-click confirmation)
4. Wait for progress bar to complete
5. Device reboots automatically with new firmware

**Firmware Location**: `.pio/build/esp32devkitc/firmware.bin` (after PlatformIO build)

### PlatformIO OTA (Alternative)
```bash
pio run -e esp32devkitc -t upload --upload-port 192.168.1.100
```
Replace IP with your device's address.

---

## Troubleshooting

For detailed troubleshooting, see [TROUBLESHOOTING.md](TROUBLESHOOTING.md)

### Common Issues

**WiFi Not Connecting**
- Check WiFi credentials in `include/wifi_config.h`
- Verify router is powered on and in range
- Check serial monitor for connection logs

**Matrix Not Working**
- Verify matrix data pin connection
- Check 5V power supply (adequate current for 64 LEDs)
- Test different animations to isolate issue

**Motion Sensor Not Triggering**
- Verify GPIO 35 connection
- Check sensor power (3.3V or 5V depending on sensor)
- Adjust sensitivity on PIR sensor
- Test in different location (avoid heat sources)

**Web Interface Not Loading**
- Verify device IP address on OLED
- Check if device and computer are on same network
- Try different browser
- Disable VPN/proxy

---

**End of User Guide**
**Version: v5.3.0 (2026-01-22)**
