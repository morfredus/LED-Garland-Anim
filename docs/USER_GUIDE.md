# User Guide - LED-Garland-Anim v1.0.0

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

---

## First Startup

### What to Expect
1. **ST7789 LCD** displays "Connecting to WiFi..."
2. **LED_BUILTIN** blinks blue during WiFi connection
3. After connection, **IP address** displayed for 3 seconds
4. **Garland** starts with Alternating Fade animation in Permanent mode
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

**Document version: v1.0.0 (2025-12-30)**
