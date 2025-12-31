# Pin Connection Guide - LED-Garland-Anim v1.2.1

> 📌 **Beginner's Guide**: This document explains how to physically connect components to your ESP32 IdeaSpark board for the LED-Garland-Anim project.

## 🎯 Table of Contents
- [Pin Connection Guide - LED-Garland-Anim v1.2.1](#pin-connection-guide---led-garland-anim-v121)
  - [🎯 Table of Contents](#-table-of-contents)
  - [ESP32 IdeaSpark Board](#esp32-ideaspark-board)
    - [📋 Pin Summary Table](#-pin-summary-table)
    - [🎨 LCD ST7789 Connection Schematic](#-lcd-st7789-connection-schematic)
    - [🎄 TB6612FNG + Garland Connection Schematic](#-tb6612fng--garland-connection-schematic)
  - [⚠️ Compatible ESP32 + ST7789](#️-compatible-esp32--st7789)
  - [Beginner Tips](#beginner-tips)

---

## ESP32 IdeaSpark Board

### 📋 Pin Summary Table

| Component         | Signal      | GPIO Pin | Description                | Notes                       |
|-------------------|------------|----------|----------------------------|-----------------------------|
| **BUTTON_BOOT**   | Button     | GPIO 0   | Integrated button on board | Already present             |
| **BUTTON_1**      | Button     | GPIO 16  | External button            | Animation change            |
| **BUTTON_2**      | Button     | GPIO 17  | External button            | Mode change                 |
| **LED_BUILTIN**   | LED        | GPIO 2   | Integrated blue LED        | Visual heartbeat            |
| **I2C_SDA**       | SDA        | GPIO 21  | I2C Data                   | For future expansion        |
| **I2C_SCL**       | SCL        | GPIO 22  | I2C Clock                  | For future expansion        |
| **LCD ST7789**    | MOSI       | GPIO 23  | SPI Data                   | LCD_MOSI                    |
| **LCD ST7789**    | SCLK       | GPIO 18  | SPI Clock                  | LCD_SCLK                    |
| **LCD ST7789**    | CS         | GPIO 15  | Chip Select                | LCD_CS                      |
| **LCD ST7789**    | DC         | GPIO 2   | Data/Command               | LCD_DC                      |
| **LCD ST7789**    | RST        | GPIO 4   | Reset                      | LCD_RST                     |
| **LCD ST7789**    | BLK        | GPIO 32  | Backlight                  | LCD_BLK                     |
| **TB6612_PWMA**   | PWMA       | GPIO 12  | PWM Direction A            | Light intensity control      |
| **TB6612_AIN1**   | AIN1       | GPIO 25  | Direction bit 1            | Current direction control    |
| **TB6612_AIN2**   | AIN2       | GPIO 33  | Direction bit 2            | Current direction control    |
| **TB6612_STBY**   | STBY       | GPIO 14  | Standby                    | Module activation (HIGH)    |
| **MOTION_SENSOR_PIN** | OUT        | GPIO 35  | Motion sensor (PIR or RCWL-0516, auto-detected) | See docs for details |

### 🎨 LCD ST7789 Connection Schematic

```
ESP32 IdeaSpark      LCD ST7789
┌─────────┐        ┌──────────┐
│ GPIO 23 ├───────►│ MOSI     │
│ GPIO 18 ├───────►│ SCLK     │
│ GPIO 15 ├───────►│ CS       │
│ GPIO 2  ├───────►│ DC       │
│ GPIO 4  ├───────►│ RST      │
│ GPIO 32 ├───────►│ BLK      │
│   3V3   ├───────►│ VCC      │
│   GND   ├───────►│ GND      │
└─────────┘        └──────────┘
```

### 🎄 TB6612FNG + Garland Connection Schematic

```
ESP32 IdeaSpark      TB6612FNG              LED Garland
┌─────────┐        ┌──────────┐           ┌──────────┐
│ GPIO 12 ├───────►│ PWMA     │           │          │
│ GPIO 25 ├───────►│ AIN1     │           │          │
│ GPIO 33 ├───────►│ AIN2     │           │          │
│ GPIO 14 ├───────►│ STBY     │           │          │
│   3V3   ├───────►│ VCC      │           │          │
│   GND   ├───────►│ GND      ├──────────►│ GND (-)  │
│         │    ┌──►│ VM       │           │          │
│         │    │   │ AO1      ├──────────►│ Wire 1   │
│         │    │   │ AO2      ├──────────►│ Wire 2   │
└─────────┘    │   └──────────┘           └──────────┘
              │
       External Power
       (5V-15V)
       ┌──────┐
       │  +   ├──────┘
       │  -   ├────────────────────────────►Common GND
       └──────┘
```

## ⚠️ Compatible ESP32 + ST7789

You may use any ESP32 board with a compatible ST7789 display, but you must respect the default pin mapping above for full compatibility.

---

## Beginner Tips

- Always disconnect power before wiring
- Check polarity: VCC = positive, GND = negative
- ESP32 = 3.3V logic (not 5V on GPIO!)
- TB6612FNG can supply required current (max 1.2A)
- Use suitable power supply for VM (not ESP32 USB)
- All grounds (GND) must be connected together
- No short circuit between VCC and GND
- GPIO pins must match code (`board_config.h`)
- External power must have correct voltage (5-15V for VM)
- Cables properly inserted (no loose connections)
- Buttons correctly oriented

---

**Document version: v1.5.3 (2025-12-31)**
