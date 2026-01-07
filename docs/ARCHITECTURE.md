### Configuration Persistence (NVS)

The configuration (mode, animation, intervals) is stored in ESP32's NVS using the `loadGarlandSettings()` and `saveGarlandSettings()` functions (see `garland_control.cpp`).

- On boot, `loadGarlandSettings()` is called after hardware setup to restore the last saved state.
- Any change via UI or button triggers `saveGarlandSettings()`.
- If NVS is empty or corrupted, defaults are used and saved.

This ensures user settings are always restored after a reboot or power loss.
# 📚 Architecture - LED-Garland-Anim v5.1.5

## 🎯 Overview

LED-Garland-Anim v1.13.0 is now unified for the ESP32 IdeaSpark board with integrated ST7789 LCD (1.14").
- **Web Interface**: Remote control and configuration
- **Local Display**: ST7789 LCD (no OLED/TFT/ILI9341)
- **Physical Control**: Buttons for animation/mode changes
- **Smart Modes**: Automatic management based on sensors
- **TB6612FNG Module**: Bi-directional garland control
- **Motion Sensor Auto-Detection**: PIR (HC-SR501) or Doppler radar (RCWL-0516) auto-detected on GPIO 35

## Modular Structure

### 1. Garland Control Module (`garland_control.h/cpp`)

**Responsibility**: Animation and operating mode management

```cpp
#include "garland_control.h"

// Main functions:
void setupGarland();                           // Initialization
void updateGarland();                          // Update (called in loop)
void setGarlandAnimation(GarlandAnimation);    // Change animation
void setGarlandMode(GarlandMode);              // Change mode
const char* getGarlandAnimationName();         // Current animation name
const char* getGarlandModeName();              // Current mode name

// GPIO naming convention:
// BUTTON_BOOT, BUTTON_1, BUTTON_2, I2C_SDA, I2C_SCL, TB6612_PWMA, TB6612_AIN1, TB6612_AIN2, TB6612_STBY, MOTION_SENSOR_PIN, LED_BUILTIN
```

**Animations (11 types)**:
- `ANIM_OFF`: Garland disabled
- `ANIM_FADE_ALTERNATE`: Smooth transition between direction A and B
- `ANIM_BLINK_ALTERNATE`: Fast alternation between direction A and B
- `ANIM_PULSE`: Simultaneous pulsation
- `ANIM_BREATHING`: Slow breathing
- `ANIM_STROBE`: Rapid stroboscopic flash
- `ANIM_HEARTBEAT`: Double-beat pulsation (heartbeat)
- `ANIM_WAVE`: Sinusoidal wave
- `ANIM_SPARKLE`: Random sparkle
- `ANIM_METEOR`: Meteor trail
- `ANIM_AUTO`: Cycles all animations

## Hardware Mapping

See [PIN_MAPPING.md](PIN_MAPPING.md) for full details. Only ESP32 IdeaSpark + ST7789 is supported.

## Display System

- ST7789 LCD (135x240px)
- Modern boot screen: project name, version, WiFi progress
- Main UI: centered headers, compact info, large animation zone
- 11 animated visualizations (one per animation)
- Real-time updates at 10 FPS

## Sensors & Buttons

- Motion sensor (PIR or RCWL-0516, GPIO 35, auto-detected)
- User buttons (GPIO 16/17)
- TB6612FNG driver (PWM, direction, standby)

## Web Interface

- Dashboard: system info, memory, WiFi
- Garland control: animation/mode selection
- Sensor visualization

## Versioning

- This document: v1.13.0 (2026-01-06)
- See CHANGELOG.md for details
