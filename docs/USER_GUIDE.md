## Saving and Restoring Configuration (NVS)

The system uses ESP32's NVS (Non-Volatile Storage) to automatically save and restore user settings:

- **Mode** (permanent or motion-triggered)
- **Current animation**
- **Auto mode interval**
- **Motion trigger duration**

**How it works:**
- On startup, the system loads the last saved configuration if available; otherwise, it uses default values.
- Any change made via the web interface or buttons is saved immediately.
- Settings are persistent across reboots and power cycles.

**No user action is required**: configuration is managed automatically.
# User Guide - LED-Garland-Anim v1.2.1
## 🚦 Motion Sensor Auto-Detection (v1.2.1)

Starting from version 1.2.1, the system automatically detects whether a PIR sensor (HC-SR501) or a Doppler radar sensor (RCWL-0516) is connected to GPIO 35:
- **PIR**: LOW when idle, HIGH when motion detected
- **RCWL-0516**: HIGH when idle, LOW when motion detected

The firmware adapts detection logic accordingly. No configuration is required—just connect your preferred sensor to GPIO 35.

See docs/PIR_SENSOR_SETUP.md and docs/RADAR_SENSOR_SETUP.md for wiring and adjustment details.

Complete user guide for the LED-Garland-Anim LED garland animation controller (ESP32 IdeaSpark + ST7789).

---

## Table of Contents

1. [First Startup](#first-startup)
2. [Physical Controls](#physical-controls)
3. [Web Interface](#web-interface)
4. [ST7789 LCD Display](#st7789-lcd-display)
5. [Operating Modes](#operating-modes)
6. [Animations](#animations)
7. [Daily Usage](#daily-usage)
8. [Troubleshooting](#troubleshooting)
9. [OTA Updates](#ota-updates)

## OTA Updates

See the detailed OTA update guide: [docs/OTA_UPDATE.md](OTA_UPDATE.md)

From v1.3.0, the firmware supports OTA (Over-the-Air) updates using ArduinoOTA.

**How to use:**
1. Connect the ESP32 to WiFi.
2. In PlatformIO or Arduino IDE, select "Upload using OTA" (the device appears as `LED-Garland-Anim.local`).
3. The device will reboot automatically after a successful upload.

**Security note:** OTA is enabled only when the ESP32 is connected to WiFi.

---

## First Startup

### What to Expect
1. **ST7789 LCD** displays "Connecting to WiFi..."
2. **LED_BUILTIN** blinks blue during WiFi connection
3. After connection, **IP address** displayed for 3 seconds
4. **Garland** plays a 10-second intro animation (Fade Alternate), then switches to saved animation/mode
5. **LED_BUILTIN** turns green when ready

### Note Your IP Address
Write down the IP address shown on the LCD screen or check your router's DHCP list. You'll need it to access the web interface.

Example: `192.168.1.100`

---

## Physical Controls

### Button Locations
- **BUTTON_BOOT**: GPIO 0 (on board)
- **BUTTON_1**: GPIO 16 (animation change)
- **BUTTON_2**: GPIO 17 (mode change)

---

## Web Interface
- Access via IP address shown on LCD
- Dashboard: system info, memory, WiFi
- Garland control: animation/mode selection
- Sensor visualization

---

## ST7789 LCD Display
- 1.14" 135x240px color display
- Modern boot screen: project name, version, WiFi progress
- Main UI: centered headers, compact info, large animation zone
- 11 animated visualizations (one per animation)
- Real-time updates at 10 FPS

---

## Operating Modes
- **Permanent**: Always on (default)
- **Motion Trigger**: PIR sensor activation (30s after motion)

---

## Animations
- Off, Fade Alternate, Blink Alternate, Pulse, Breathing, Strobe, Heartbeat, Wave, Sparkle, Meteor, Auto (cycles all)

---

## Daily Usage
- Change animation/mode with buttons or web interface
- Monitor status on LCD and web dashboard

---

## Troubleshooting
See [TROUBLESHOOTING.md](TROUBLESHOOTING.md) for help.

---

**Document version: v1.5.3 (2025-12-31)**
