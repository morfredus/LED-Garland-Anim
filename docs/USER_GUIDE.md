# User Guide - LED-Garland-Anim v0.6.4

Complete user guide for the LED-Garland-Anim LED garland animation controller.

---

## Table of Contents

1. [First Startup](#first-startup)
2. [Physical Controls](#physical-controls)
3. [Web Interface](#web-interface)
4. [OLED Display](#oled-display)
5. [Operating Modes](#operating-modes)
6. [Animations](#animations)
7. [Schedule Configuration](#schedule-configuration)
8. [Daily Usage](#daily-usage)
9. [Troubleshooting](#troubleshooting)

---

## First Startup

### What to Expect
1. **OLED Screen** displays "Connecting to WiFi..."
2. **NeoPixel LED** blinks blue during WiFi connection
3. After connection, **IP address** displayed for 3 seconds
4. **Garland** starts with Alternating Fade animation in Permanent mode
5. **NeoPixel LED** turns green when ready

### Note Your IP Address
Write down the IP address shown on the OLED screen or check your router's DHCP list. You'll need it to access the web interface.

Example: `192.168.1.100`

---

## Physical Controls

### Button Locations

#### ESP32-S3
- **Button 0 (BOOT)**: Integrated on board
- **Button 1**: GPIO 16 (external button)
- **Button 2**: GPIO 17 (external button)

#### ESP32 Classic
- **Button 0 (BOOT)**: Integrated on board
- **Button 1**: GPIO 4 (external button)
- **Button 2**: GPIO 16 (external button)

### Button Functions

#### Button 1 - Animation Control
- **Short press**: Cycle to next animation
- **Sequence**: Fade → Blink → Wave → ... → Auto Mode → (restart)
- **Visual feedback**: NeoPixel flashes purple

#### Button 2 - Mode Control
- **Short press**: Cycle to next operating mode
- **Sequence**: Permanent → Motion Trigger → (restart)
- **Visual feedback**: NeoPixel flashes cyan

#### Button 0 (BOOT) - Restart
- **Long press (1 second)**: Restart ESP32
- **Visual feedback**: NeoPixel turns red
- **Use case**: Error recovery or applying configuration changes

---

## Web Interface

### Configurable durations & persistence
- AUTO mode interval (ms): adjustable from the main card, saved to NVS and restored on reboot.
- Motion-off duration (ms): adjustable, saved to NVS and restored on reboot.
- API endpoints: `GET /auto_interval?ms=<millis>` and `GET /motion_duration?ms=<millis>`.
- Status (`GET /status`): includes `auto_interval_ms` and `motion_duration_ms`.

### Accessing the Interface
1. Open a web browser on phone/computer
2. Enter ESP32 IP address: `http://[YOUR_IP]`
3. Dashboard loads automatically

### Dashboard Cards

#### 1. LED Garland Card (First Position)
**Animation Selector**
- Dropdown menu with 15 options
- Current animation highlighted
- Click "Apply" to change

**Mode Selector**
- 2 operating modes (Permanent, Motion Trigger)
- Current mode highlighted
- Click "Apply" to change

**Schedule Configuration**
- Removed since v0.5.1 (modes simplified to 2). No schedule UI in current build.

**Sensor Status**
- Motion detected: Yes/No
- Light level: 0-4095
- Night detected: Yes/No

#### 2. Hardware Card
- Board name (ESP32-S3 / ESP32 Classic)
- Chip ID (unique identifier)
- SDK version
- CPU frequency (MHz)

#### 3. Flash Memory Card
- Total size (MB)
- Speed (MHz)
- Mode (QIO/DIO)

#### 4. RAM (Heap) Card
- Total size (KB)
- Free memory (KB)
- Usage percentage with progress bar

#### 5. PSRAM Card (if available)
- Total size (MB)
- Free memory (KB)
- Usage percentage with progress bar

#### 6. WiFi Network Card
- Connected SSID
- IP address
- MAC address
- Signal strength (dBm and %)

#### 7. System Card
- Uptime (hours, minutes, seconds)
- CPU temperature (°C)

#### 8. Network Details Card
- Subnet mask
- Gateway IP
- DNS server IP

### Action Buttons
- **🔄 Refresh**: Reload page with updated data
- **🔴 Restart**: Restart ESP32 (asks for confirmation)

---

## OLED Display

### Screen Layout

#### 128x64 Screen (Large)
```
┌────────────────────────────┐
│ Animation: Fade            │  Line 1: Current animation
│ Mode: Permanent            │  Line 2: Current mode
│ IP: 192.168.1.100          │  Line 3: IP address
│ [████▒▒▒▒░░░░░░░░░]       │  Line 4: Animated bar
└────────────────────────────┘
```

#### 128x32 Screen (Small)
```
┌────────────────────────────┐
│ Fade / Permanent           │  Line 1: Animation + Mode
│ 192.168.1.100              │  Line 2: IP address
│ [████▒▒▒▒░░░░░░░░░]       │  Line 3: Animated bar
└────────────────────────────┘
```

### Animation Bar Patterns

Each animation has a unique visualization on the OLED:

- **Off**: Empty bar
- **Fade Alternate**: Sliding bar with gradient
- **Blink Alternate**: Alternating left/right blocks
- **Pulse**: Growing/shrinking centered bar
- **Breathing**: Expanding/contracting bar
- **Strobe**: Rapid alternating flashes
- **Heartbeat**: Characteristic double-beat pulse
- **Wave**: Smooth sinusoidal wave
- **Sparkle**: Random blinking pixels
- **Meteor**: Moving trail with fade
- **Auto**: Rotating dash (indicates cycling mode with instant start)

**When No Animation is Active** (v0.4.0+):
- Display shows 3 fixed dots at the bottom of screen
- Indicates system is running but animation is off
- Still updates when animation restarts
- Reduces unnecessary screen flickering

**Note**: During night mode, OLED shows minimal dots in center and backlight is off.

---

## Operating Modes

### 1. Permanent Mode
**Behavior**: Garland always on with selected animation

**Use cases**:
- Continuous decoration
- Testing animations
- Events and parties

**Activation**:
- Button 2 until "Permanent" displays
- Web interface: Select "Permanent" mode

### 2. Motion Trigger Mode
**Behavior**: Activates for 30 seconds after motion detection (PIR)

**Prerequisite**: PIR sensor connected

**Use cases**:
- Entrance decoration
- Corridor lighting
- Interactive displays

**Trigger duration**: 30 seconds (configurable in code via `MOTION_TRIGGER_DURATION`)

**Notes**:
- Only 2 modes exist in v0.6.3 (Permanent, Motion Trigger). Scheduled and Night modes were removed.
- Consider adding debounce if using noisy PIR modules.

## Animations

### Animation Descriptions

#### 1. Alternating Fade
Smooth crossfade between LED Direction A and B. Creates gentle pulsing effect.

**Duration**: ~3 seconds per cycle  
**Effect**: Calming, subtle

#### 2. Blink
Fast alternation between both LED directions.

**Duration**: 500ms per direction  
**Effect**: Energetic, eye-catching

#### 3. Smooth Wave
Simulates a wave traveling through the garland with sinusoidal intensity.

**Duration**: ~2 seconds per wave  
**Effect**: Fluid, dynamic

#### 4. Strobe
Rapid alternating flashes between directions.

**Duration**: 100ms per flash  
**Effect**: Intense, party atmosphere

#### 5. Pulse
Both directions pulse together with synchronized intensity.

**Duration**: ~2 seconds per pulse  
**Effect**: Heartbeat-like, rhythmic

#### 6. Chase
Creates illusion of LEDs chasing each other.

**Duration**: 50ms steps  
**Effect**: Racing, playful

#### 7. Heartbeat
Double-pulse pattern mimicking a heartbeat.

**Duration**: Thump-THUMP pattern with pause  
**Effect**: Organic, alive

#### 8. Sparkle
Random intensity changes create a twinkling effect.

**Duration**: Continuous random  
**Effect**: Starry, magical

#### 9. Rainbow
Simulates rainbow colors via fast alternation and modulation.

**Duration**: ~4 seconds per cycle  
**Effect**: Colorful, festive

#### 10. Breathing
Slow, smooth rise and fall of intensity.

**Duration**: ~4 seconds per breath  
**Effect**: Meditative, relaxing

#### 11. Fire
Random flickering imitating candle or flames.

**Duration**: Continuous random  
**Effect**: Warm, cozy

#### 12. Soft Blink
Gentle sinusoidal fade in and out.

**Duration**: ~1.5 seconds per blink  
**Effect**: Soft, romantic

#### 13. Meteor
Creates a light trail effect like a meteor shower.

**Duration**: 50ms steps with fade  
**Effect**: Dynamic, celestial

#### 14. Auto Mode
Automatically cycles through all 13 animations.

**Duration**: 30 seconds per animation  
**Effect**: Variety, showcase mode

---

### 2. Motion Trigger Mode
**Behavior**: Activates for 30 seconds after motion detection (PIR)

**Prerequisite**: PIR sensor connected

**Use cases**:
- Entrance decoration
- Corridor lighting
- Interactive displays

**Trigger duration**: 30 seconds (configurable in code via `MOTION_TRIGGER_DURATION`)

**Notes**:
- Only 2 modes exist in v0.6.3 (Permanent, Motion Trigger). Scheduled and Night modes were removed.
- Consider adding debounce if using noisy PIR modules.

---

## Daily Usage

### Morning Routine
1. Check current status on OLED
2. Use Button 1 to change animation if desired
3. Leave in Permanent or Motion Trigger based on need

### Evening Routine
1. Choose Permanent (always on) or Motion Trigger
2. Web interface to verify operation
3. Adjust animation via buttons, web, or Telegram

### Leaving Home
1. Set to Motion Trigger to reduce usage (no motion = off)
2. Or leave in Permanent if desired
3. Check web interface or Telegram if needed

### Quick Troubleshooting Actions
- **Garland not working**: Press Button 1 to cycle animations
- **Wrong mode**: Press Button 2 to change mode
- **System stuck**: Long press BOOT button to restart
- **Lost IP**: Check OLED screen or router DHCP list

---

## Troubleshooting

For detailed troubleshooting guide, see [TROUBLESHOOTING.md](./TROUBLESHOOTING.md).

### Common Issues

#### Garland Doesn't Light Up
**Solutions**:
1. Check TB6612FNG wiring
2. Ensure STBY pin is HIGH
3. Test with Blink animation
4. Verify power supply

#### Blank OLED Screen
**Solutions**:
1. Check I2C address (0x3C or 0x3D)
2. Verify SDA/SCL connections
3. Test with I2C scanner
4. Check 3.3V power supply

#### WiFi Won't Connect
**Solutions**:
1. Verify `secrets.h` credentials
2. Ensure 2.4 GHz WiFi (not 5 GHz)
3. Move closer to router
4. Check serial monitor

---

**Version**: 0.6.0  
**Last Updated**: 2025-12-10  
**Next**: [Troubleshooting Guide](./TROUBLESHOOTING.md)
