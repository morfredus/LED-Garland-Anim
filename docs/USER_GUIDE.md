# User Guide - LED-Garland-Anim v0.4.0

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
- **Button 2**: GPIO 15 (external button)

### Button Functions

#### Button 1 - Animation Control
- **Short press**: Cycle to next animation
- **Sequence**: Fade → Blink → Wave → ... → Auto Mode → (restart)
- **Visual feedback**: NeoPixel flashes purple

#### Button 2 - Mode Control
- **Short press**: Cycle to next operating mode
- **Sequence**: Permanent → Scheduled → Motion Trigger → Night Off → (restart)
- **Visual feedback**: NeoPixel flashes cyan

#### Button 0 (BOOT) - Restart
- **Long press (1 second)**: Restart ESP32
- **Visual feedback**: NeoPixel turns red
- **Use case**: Error recovery or applying configuration changes

---

## Web Interface

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
- 4 operating modes
- Current mode highlighted
- Click "Apply" to change

**Schedule Configuration** (v0.2.0+)
- Start time: Hour and Minute inputs
- End time: Hour and Minute inputs
- Click "Save Schedule" to apply
- Confirmation popup appears

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

- **Fade**: Sliding bar with gradient
- **Blink**: Alternating left/right blocks
- **Wave**: Smooth wave progression
- **Strobe**: Fast flashing blocks
- **Pulse**: Growing/shrinking centered bar
- **Chase**: Running dot pattern
- **Heartbeat**: Double-beat pulse
- **Sparkle**: Random pixels
- **Rainbow**: Moving wave
- **Breathing**: Expanding/contracting bar
- **Fire**: Flickering random-height bars
- **Twinkle**: Random sparse pixels
- **Meteor**: Moving trail with fade
- **Auto**: Rotating dash (indicates cycling mode)

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

### 2. Scheduled Mode (v0.2.0+)
**Behavior**: Garland activates only during configured time window

**Configuration**:
1. Access web interface
2. Scroll to "Schedule Configuration" section
3. Set start time (hour and minute)
4. Set end time (hour and minute)
5. Click "Save Schedule"

**Default schedule**: 18:00 - 23:00

**Use cases**:
- Automatic evening decoration (6 PM - 11 PM)
- Energy saving
- Unattended operation

**Important**: Requires accurate system time. Consider adding RTC module for power-loss resilience.

### 3. Motion Trigger Mode
**Behavior**: Activates for 30 seconds after motion detection

**Prerequisite**: PIR sensor connected

**Use cases**:
- Entrance decoration
- Corridor lighting
- Interactive displays

**Trigger duration**: 30 seconds (configurable in code)

**Sensor**: PIR HC-SR501 module
- Detection range: ~7 meters
- Detection angle: ~120°
- Adjustable sensitivity and delay

### 4. Night Off Mode
**Behavior**: Automatically turns off when ambient light is low (night time)

**Prerequisite**: LDR photoresistor connected

**Features** (v0.4.0+):
- **Automatic detection**: Uses light sensor to detect nighttime
- **OLED backlight off**: Screen saves power in night mode
- **LED indicators silent**: Blue LED and NeoPixel stop blinking
- **Minimal display**: OLED shows 3 fixed dots instead of animation
- **No manual setup**: Fully automatic based on light level
- **Night threshold**: 500/4095 ADC units (configurable)
  - Lower value = darker environment needed to trigger
  - Typical: 300-600 depending on ambient lighting

**Use cases**:
- Daytime decoration only
- Automatic night shutdown
- Light-reactive displays
- Power-saving mode during sleep hours

**When Night Mode Activates**:
1. OLED backlight dims to off
2. Animation stops (garland LEDs still respond to motion if set)
3. Heartbeat LED/NeoPixel stops blinking
4. Screen shows minimal dots to indicate system is still running

**When Light Returns**:
1. OLED backlight automatically turns on
2. Normal display resumes
3. Heartbeat LED/NeoPixel resumes blinking
4. Animation continues (if in active mode)

---

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

## Schedule Configuration

### Web Interface Setup (v0.2.0+)

1. **Access Web Interface**
   - Navigate to `http://[ESP32_IP]`
   - Scroll to "LED Garland" card

2. **Locate Schedule Section**
   - Below mode selector
   - Title "⏰ Schedule Configuration"

3. **Set Start Time**
   - Enter start hour (0-23)
   - Enter start minute (0-59)
   - Example: 18:00 for 6 PM

4. **Set End Time**
   - Enter end hour (0-23)
   - Enter end minute (0-59)
   - Example: 23:00 for 11 PM

5. **Save Configuration**
   - Click "💾 Save Schedule" button
   - Confirmation popup appears
   - Page reloads with new values

### Common Schedules

**Evening Decoration** (Default)
- Start: 18:00 (6 PM)
- End: 23:00 (11 PM)
- Usage: Automatic evening ambiance

**All Night**
- Start: 18:00 (6 PM)
- End: 06:00 (6 AM)
- Usage: Extended nighttime decoration

**Daytime Only**
- Start: 08:00 (8 AM)
- End: 18:00 (6 PM)
- Usage: Business hours, shop displays

**Short Event**
- Start: 19:00 (7 PM)
- End: 21:00 (9 PM)
- Usage: Dinners, specific events

### Verification
After saving, check:
- Schedule values updated in fields
- Garland behaves according to schedule
- Verify system time if issues

---

## Daily Usage

### Morning Routine
1. Check current status on OLED
2. No action needed in Scheduled/Motion modes
3. Use Button 1 to change animation if desired

### Evening Routine
1. Scheduled mode activates automatically
2. Web interface to verify operation
3. Adjust schedule if needed

### Leaving Home
1. Set to Scheduled mode for automatic control
2. Or turn off by setting to Motion Trigger (no motion = off)
3. Check web interface remotely if on same network

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

**Version**: 0.2.0  
**Last Updated**: 2025-12-09  
**Next**: [Troubleshooting Guide](./TROUBLESHOOTING.md)
