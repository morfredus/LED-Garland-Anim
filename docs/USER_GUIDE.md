# User Guide - LED-Garland-Anim v5.0.0

Complete user guide for the LED-Garland-Anim LED garland and 8x8 matrix animation controller (ESP32 IdeaSpark + ST7789).

**Document version: v5.0.0 (2026-01-06)**

---

## Table of Contents

1. [First Startup](#first-startup)
2. [Physical Controls](#physical-controls)
3. [Web Interface](#web-interface)
4. [ST7789 LCD Display](#st7789-lcd-display)
5. [Operating Modes](#operating-modes)
6. [Garland Animations](#garland-animations)
7. [Matrix Animations](#matrix-animations)
8. [Motion Sensor Auto-Detection](#motion-sensor-auto-detection)
9. [Configuration Persistence](#configuration-persistence)
10. [Daily Usage](#daily-usage)
11. [OTA Updates](#ota-updates)
12. [Troubleshooting](#troubleshooting)

---

## First Startup

### What to Expect
1. **ST7789 LCD** displays "Connecting to WiFi..."
2. **LED_BUILTIN** blinks blue during WiFi connection
3. After connection, **IP address** displayed for 3 seconds
4. **Garland** plays a 10-second intro animation (Fade Alternate), then switches to saved animation/mode
5. **8x8 Matrix** starts with saved animation
6. **LED_BUILTIN** turns green when ready

### Note Your IP Address
Write down the IP address shown on the LCD screen or check your router's DHCP list. You'll need it to access the web interface.

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

### Modern UI Features (v1.11.3+)
- **Radio Button Grids**: All selections use intuitive radio buttons (no dropdowns)
- **Responsive Layout**: 2 columns on desktop, 1 column on mobile (<600px)
- **Instant Updates**: No "Apply" buttons - changes apply immediately
- **Flash-Free Experience**: No page reloads when changing animations/modes (v1.11.3)
- **Visual Feedback**: Selected items highlighted in green, inline confirmation messages

### Access
- Open browser and navigate to the IP address shown on LCD
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

## ST7789 LCD Display

### Specifications
- **Size**: 1.14" diagonal
- **Resolution**: 135×240 pixels
- **Colors**: Full RGB (65K colors)

### Display Information
- **Boot Screen**: Project name, version, WiFi connection progress
- **Static Screen**: Festive dashboard with ribbon frame showing Program name, Version, SSID, IP address, and mDNS (`*.local`)
- **Animated Screen (v5.0.0)**:
  - Same festive look as Static: textured background, ribbon frames, sparkles, twin garlands
  - Info card with Mode, Garland animation, Matrix animation, SSID, and IP
  - **Reduced mini animation window** (“Mini show”) framed separately to prioritize text and decorations
  - Real-time animation refresh (~10 FPS) inside the compact window
- **11 Animated Visualizations**: One for each garland animation

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
- **LCD Display**: Mode displayed in status bar
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

---

## Matrix Animations

**Total: 39 animations** (8x8 NeoPixel WS2812B-64 matrix)

### Categories

#### Original Animations (11)
- **Off**: Matrix disabled
- **Star**: Twinkling star effect
- **Meteor**: Meteor shower
- **Shooting Star**: Single shooting star across screen
- **Santa**: Santa Claus silhouette
- **Tree**: Christmas tree with lights
- **Bell**: Ringing bell animation
- **Snow**: Falling snowflakes
- **Gift**: Wrapped gift box
- **Candle**: Flickering candle flame (redesigned in v1.11.3)
- **Snowflake**: Rotating snowflake pattern

#### Christmas Animations (10)
- **Candy Cane**: Rotating red/white striped candy cane
- **Wreath**: Christmas wreath with bow
- **Stocking**: Hanging Christmas stocking (redesigned in v1.11.3)
- **Reindeer**: Reindeer silhouette with blinking nose
- **Gingerbread**: Gingerbread man with smile
- **Hot Cocoa**: Steaming mug of hot chocolate
- **Fireplace**: Flickering fireplace flames
- **Icicles**: Hanging icicles with dripping water
- **Northern Lights**: Aurora borealis effect
- **Presents**: Stack of wrapped presents

#### New Year Animations (7)
- **Fireworks**: Colorful firework bursts
- **Champagne**: Rising bubbles in champagne glass
- **Countdown**: 3-2-1 countdown display (redesigned in v1.11.3)
- **Confetti**: Falling colorful confetti
- **Clock**: Analog clock face with moving hands (fixed in v1.11.3)
- **Party Popper**: Exploding party popper
- **Disco Ball**: Rotating disco ball with reflections

#### Easter Animations (4)
- **Easter Egg**: Decorated Easter egg with patterns
- **Bunny**: Hopping bunny animation
- **Chick**: Hatching baby chick
- **Flowers**: Blooming spring flowers

#### Modern/Abstract Animations (7)
- **Rainbow Wave**: Flowing rainbow wave pattern
- **Sparkle Rain**: Falling sparkles (fixed in v1.11.3)
- **Plasma**: Colorful plasma effect
- **Matrix Rain**: Digital Matrix-style falling characters (fixed in v1.11.3)
- **Spiral**: Rotating spiral pattern
- **Heart**: Pulsing heart shape
- **Stars Field**: Twinkling starfield
- **Campfire**: Realistic fire simulation (NEW in v1.11.3)
- **Radar**: Military green radar sweep (NEW in v1.11.3)

### Matrix Brightness Control
- **Range**: 0-255
- **Default**: 128 (50%)
- **Adjustment**: Web interface slider with live preview
- **Persistence**: Brightness setting saved to NVS

---

## Motion Sensor Auto-Detection

### Supported Sensors (GPIO 35)

#### PIR Sensor (HC-SR501)
- **Idle State**: LOW
- **Motion Detected**: HIGH
- **Range**: 3-7 meters (adjustable)
- **Delay**: 0.3-200 seconds (adjustable)
- **Angle**: ~110 degrees

#### Doppler Radar (RCWL-0516)
- **Idle State**: HIGH
- **Motion Detected**: LOW (inverted logic)
- **Range**: 5-7 meters
- **Delay**: ~2 seconds
- **Angle**: 360 degrees (omnidirectional)
- **Advantage**: Works through walls/glass

### Auto-Detection Feature (v1.11.3+)
The firmware automatically detects which sensor type is connected:
1. Reads initial state on startup
2. Determines sensor type (PIR or Radar)
3. Adapts detection logic accordingly
4. **No configuration required** - plug and play

### Wiring
Connect sensor to GPIO 35 (see [docs/PIR_SENSOR_SETUP.md](PIR_SENSOR_SETUP.md) and [docs/RADAR_SENSOR_SETUP.md](RADAR_SENSOR_SETUP.md))

---

## Configuration Persistence

### NVS (Non-Volatile Storage)
The system automatically saves all settings to ESP32's NVS:

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

### Manual Control (Web Interface)

---
2. Select "Permanent" mode
3. Choose desired animations (garland + matrix)
4. Both devices stay on all day

#### Evening: Switch to Motion Detection
1. Select "Detection (tout)" or "Detection (guirlande)" mode
2. Set motion duration (e.g., 60 seconds)
3. Devices activate automatically when you enter room
4. Energy saved when room is empty

#### Changing Animations
- **Web Interface**: Click desired animation radio button → instant change
- **Physical Buttons**: Press BUTTON_1 to cycle through garland animations
- **Auto Mode**: Set "Auto" animation for automatic cycling

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
- Verify GPIO 32 connection
- Check 5V power supply (adequate current for 64 LEDs)
- Test different animations to isolate issue

**Motion Sensor Not Triggering**
- Verify GPIO 35 connection
- Check sensor power (3.3V or 5V depending on sensor)
- Adjust sensitivity on PIR sensor
- Test in different location (avoid heat sources)

**Web Interface Not Loading**
- Verify device IP address on LCD
- Check if device and computer are on same network
- Try different browser
- Disable VPN/proxy

---

**End of User Guide**
**Version: v5.0.0 (2026-01-06)**
