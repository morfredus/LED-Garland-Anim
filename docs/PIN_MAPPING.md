# Pin Connection Guide - LED-Garland-Anim v5.3.1

*This document is valid from version 5.3.1.*


## Supported Platforms
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32 Wroom
- ESP32-C3 HW-675
- ESP32-S3 Mini (esp32s3_mini)

> 📌 **OLED SSD1306 (I2C) display is supported on all platforms if connected to SDA/SCL**


# Pin Connection Guide - LED-Garland-Anim v5.3.0

*This document is valid from version 5.3.0.*

## Supported Platforms
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32-C3 HW-675 (OLED)
- ESP32-S3 Mini (esp32s3_mini)

> 📌 **Beginner's Guide**: This document explains how to physically connect components to your ESP32 board for the LED-Garland-Anim project.

## 🎯 Table of Contents
- [OLED SSD1306 128x64 Display](#oled-ssd1306-128x64-display)
- [Other Peripherals](#other-peripherals)
- [Detailed Connection Schematics](#detailed-connection-schematics)
- [Beginner Tips](#beginner-tips)

---

## OLED SSD1306 Display (I2C)

The OLED SSD1306 (I2C) display is supported on all platforms. Recommended wiring:
- **SDA**: GPIO 4 (default)
- **SCL**: GPIO 5 (default)
Power the display with 3.3V or 5V depending on your module. Default I2C address is usually `0x3C`.
---

## Other Peripherals

Refer to the user guide for the full mapping of buttons, matrix, garland, and motion sensor.

---

## Detailed Connection Schematics


### OLED SSD1306 I2C Wiring

```
ESP32 Board         OLED SSD1306 (I2C)
┌─────────┐        ┌───────────────┐
│ GPIO 4  ├───────►│ SDA           │
│ GPIO 5  ├───────►│ SCL           │
│   3V3   ├───────►│ VCC           │
│   GND   ├───────►│ GND           │
└─────────┘        └───────────────┘
```

### NeoPixel 8x8 Matrix Connection Schematic

```
ESP32 Board         WS2812B 8x8 Matrix
│ GPIO 27 ├───────►│ DIN      │
│   5V    ├───────►│ VCC      │ (External power supply recommended)
│   GND   ├───────►│ GND      │
└─────────┘        └──────────┘
```

---

**Document version: v1.14.0 (2026-01-22)**
