# Pin Connection Guide - LED-Garland-Anim v5.6.4

*This document is valid from version 5.6.4.*

## Supported Platforms
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32 Wroom (DevKit V1)
- ESP32-S3 Mini (esp32s3_mini)
- ESP32-S3 Super Mini (esp32s3_supermini)

> 📌 **OLED SSD1306 (I2C)** is supported on all platforms if connected.
> 📌 **OLED Rotation**: Configurable via `OLED_ROTATION` in config.h (U8G2_R0, U8G2_R1, U8G2_R2, U8G2_R3)

---

## Key Pin Mapping (per board)

| Board | I2C SDA / SCL | TB6612 PWMA / AIN1 / AIN2 / STBY | Matrix DATA | Motion Sensor | User Button (BUTTON_1) | BOOT |
|---|---|---|---|---|---|---|
| ESP32 Classic | GPIO21 / GPIO22 | GPIO12 / GPIO25 / GPIO33 / GPIO14 | GPIO27 | GPIO35 | GPIO16 | GPIO0 |
| ESP32 Wroom | GPIO21 / GPIO22 | GPIO12 / GPIO25 / GPIO33 / GPIO14 | GPIO27 | GPIO35 | GPIO16 | GPIO0 |
| ESP32-S3 Mini / Super Mini | GPIO4 / GPIO5 | GPIO10 / GPIO11 / GPIO12 / GPIO13 | GPIO7 | GPIO2 | GPIO8 | GPIO0 |

---

## Physical Button Controls

The firmware uses a **single user button** (BUTTON_1) plus the built-in BOOT button:

| Button | Action | Function |
|--------|--------|----------|
| **BUTTON_1** | 1 click | Next garland animation |
| **BUTTON_1** | 2 clicks | Next matrix animation |
| **BUTTON_1** | Long press | Change operating mode |
| **BOOT** | Long press | System reboot |

---

## Notes
- On ESP32-S3 Mini / Super Mini, the motion sensor uses GPIO2 and the matrix uses GPIO7.
- See board_config.h for the authoritative mapping.
