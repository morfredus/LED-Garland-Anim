
# Pin Connection Guide - LED-Garland-Anim v5.2.1

*This document is valid from version 5.2.1.*

## Supported Platforms
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32-C3 HW-675 (OLED)
- ESP32-S3 Mini (esp32s3_mini)

> 📌 **Beginner's Guide**: This document explains how to physically connect components to your ESP32 board for the LED-Garland-Anim project.

## 🎯 Table of Contents
- [ESP32 IdeaSpark Board (Classic)](#esp32-ideaspark-board-classic)
- [ESP32-C3 HW-675 Board (NEW in v5.2.0)](#esp32-c3-hw-675-board-new-in-v520)
- [Detailed Connection Schematics](#detailed-connection-schematics)
- [Beginner Tips](#beginner-tips)

---

## ESP32 IdeaSpark Board (Classic)

### 📋 Pin Summary Table

| Component         | Signal      | GPIO Pin | Description                | Notes                       |
|-------------------|------------|----------|----------------------------|-----------------------------|
| **BUTTON_BOOT**   | Button     | GPIO 0   | Integrated button on board | Already present             |
| **BUTTON_1**      | Button     | GPIO 16  | External button            | Animation change            |
| **BUTTON_2**      | Button     | GPIO 17  | External button            | Mode change                 |
| **LED_BUILTIN**   | LED        | GPIO 2   | Integrated blue LED        | ⚠️ Shared with LCD_DC       |
| **I2C_SDA**       | SDA        | GPIO 21  | I2C Data                   | For future expansion        |
| **I2C_SCL**       | SCL        | GPIO 22  | I2C Clock                  | For future expansion        |
| **LCD ST7789**    | MOSI       | GPIO 23  | SPI Data                   | LCD_MOSI                    |
| **LCD ST7789**    | SCLK       | GPIO 18  | SPI Clock                  | LCD_SCLK                    |
| **LCD ST7789**    | CS         | GPIO 15  | Chip Select                | LCD_CS                      |
| **LCD ST7789**    | DC         | GPIO 2   | Data/Command               | LCD_DC (⚠️ Shared with LED_BUILTIN) |
| **LCD ST7789**    | RST        | GPIO 4   | Reset                      | LCD_RST                     |
| **LCD ST7789**    | BLK        | GPIO 32  | Backlight                  | LCD_BLK (MUST be HIGH)      |
| **TB6612_PWMA**   | PWMA       | GPIO 12  | PWM Direction A            | Light intensity control      |
| **TB6612_AIN1**   | AIN1       | GPIO 25  | Direction bit 1            | Current direction control    |
| **TB6612_AIN2**   | AIN2       | GPIO 33  | Direction bit 2            | Current direction control    |
| **TB6612_STBY**   | STBY       | GPIO 14  | Standby                    | Module activation (HIGH)    |
| **MATRIX8X8**     | DIN        | GPIO 27  | WS2812B Data               | Dedicated pin for matrix    |
| **MOTION_SENSOR_PIN** | OUT        | GPIO 35  | Motion sensor (PIR or RCWL-0516, auto-detected) | See docs for details |

---

## ESP32-C3 HW-675 Board (NEW in v5.2.0)

### 📋 Complete Pin Mapping Table

| Pin    | GPIO   | Analog Functions          | Digital Functions        | Usage (HW-675)               |
|--------|--------|---------------------------|--------------------------|------------------------------|
| GND    | --     | Ground                    | --                       | Common Ground                |
| 3V3    | --     | 3.3V Output (Regulator)   | --                       | Sensor Power Supply          |
| 5V     | --     | Input/Output (VBUS)       | --                       | USB Power Supply             |
| G9     | GPIO 9 | Boot Strapping Pin        | Digital Input            | **BOOT BUTTON** (Pull-up)    |
| G10    | GPIO 10| --                        | FSPICS0 (SPI)            | **MOTION_SENSOR** (Optional) |
| G4     | GPIO 4 | ADC1_CH4 / JTAG           | PWM / USB_JTAG           | FREE                         |
| G3     | GPIO 3 | ADC1_CH3                  | PWM                      | **TB6612_STBY**              |
| G2     | GPIO 2 | ADC1_CH2                  | PWM / FSPIQ (SPI)        | **TB6612_AIN2**              |
| G1     | GPIO 1 | ADC1_CH1                  | PWM / FSPID (SPI)        | **TB6612_AIN1**              |
| G0     | GPIO 0 | ADC1_CH0                  | PWM / FSPI_CLK           | **TB6612_PWMA**              |
| G5     | GPIO 5 | ADC2_CH0                  | **I2C SDA**              | **OLED DISPLAY (SDA)**       |
| G6     | GPIO 6 | --                        | **I2C SCL**              | **OLED DISPLAY (SCL)**       |
| G7     | GPIO 7 | --                        | FSPID (SPI)              | FREE                         |
| G8     | GPIO 8 | Strapping Pin (High)      | PWM                      | **WS2812B MATRIX (DATA)**    |
| G21    | GPIO 21| --                        | UART TX                  | FREE (Debug Serial)          |
| G20    | GPIO 20| --                        | UART RX                  | FREE (Debug Serial)          |

### 🔌 ESP32-C3 HW-675 Component Assignment

| Component              | GPIO Pin | Description                          | Notes                    |
|------------------------|----------|--------------------------------------|--------------------------|
| **BUTTON_BOOT**        | GPIO 9   | Integrated button on board           | Mode cycle (click), Reboot (long-press) |
| **OLED SSD1306 (SDA)** | GPIO 5   | I2C Data                             | 72×40 px display         |
| **OLED SSD1306 (SCL)** | GPIO 6   | I2C Clock                            | Address: 0x3C            |
| **TB6612_PWMA**        | GPIO 0   | PWM Direction A                      | Light intensity control  |
| **TB6612_AIN1**        | GPIO 1   | Direction bit 1                      | Current direction        |
| **TB6612_AIN2**        | GPIO 2   | Direction bit 2                      | Current direction        |
| **TB6612_STBY**        | GPIO 3   | Standby                              | Module activation (HIGH) |
| **MATRIX8X8**          | GPIO 8   | WS2812B Data                         | NeoPixel matrix          |
| **MOTION_SENSOR_PIN**  | GPIO 10  | Motion sensor (optional)             | PIR or RCWL-0516         |

### 🎨 LCD ST7789 Connection Schematic

```
ESP32 IdeaSpark      LCD ST7789
┌─────────┐        ┌──────────┐
│ GPIO 23 ├───────►│ MOSI     │
│ GPIO 18 ├───────►│ SCLK     │
│ GPIO 15 ├───────►│ CS       │
│ GPIO 2  ├───────►│ DC       │ ⚠️ Shared with LED_BUILTIN
│ GPIO 4  ├───────►│ RST      │
│ GPIO 32 ├───────►│ BLK      │ ⚠️ MUST be HIGH to see display
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

### 🌈 NeoPixel 8x8 Matrix Connection Schematic

```
ESP32 IdeaSpark      WS2812B 8x8 Matrix
┌─────────┐        ┌──────────┐
│ GPIO 27 ├───────►│ DIN      │
│   5V    ├───────►│ VCC      │ (External power supply recommended)
│   GND   ├───────►│ GND      │
└─────────┘        └──────────┘
```

## ⚠️ Compatible ESP32 + ST7789

You may use any ESP32 board with a compatible ST7789 display, but you must respect the default pin mapping above for full compatibility.

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

**Document version: v1.13.0 (2026-01-06)**
