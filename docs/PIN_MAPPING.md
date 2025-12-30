# Pin Connection Guide - LED-Garland-Anim v1.0.0

> 📌 **Beginner's Guide**: This document explains how to physically connect components to your **ESP32 IdeaSpark 1.14" LCD** board for the LED-Garland-Anim project.

## 🎯 Version Information

- **Version**: 1.0.0
- **Platform**: ESP32 IdeaSpark with integrated ST7789 1.14" LCD
- **Board Name**: ESP32 IdeaSpark 1.14 LCD
- **Display**: Hardwired ST7789 TFT LCD (135×240 pixels)

---

## 📋 ESP32 IdeaSpark 1.14" LCD - Complete Pin Mapping

### Quick Reference Table

| Component | Signal | GPIO Pin | Description | Notes |
|-----------|--------|----------|-------------|-------|
| **LCD ST7789** | MOSI | GPIO 23 | SPI Data | Hardwired on PCB |
| **LCD ST7789** | SCLK | GPIO 18 | SPI Clock | Hardwired on PCB |
| **LCD ST7789** | CS | GPIO 15 | Chip Select | Hardwired on PCB |
| **LCD ST7789** | DC | GPIO 2 | Data/Command | Hardwired on PCB |
| **LCD ST7789** | RST | GPIO 4 | Reset | Hardwired on PCB |
| **LCD ST7789** | BLK | GPIO 32 | Backlight | **MUST be HIGH to see image** |
| **TB6612_PWMA** | PWMA | GPIO 12 | PWM Control | Light intensity (0-255) |
| **TB6612_AIN1** | AIN1 | GPIO 25 | Direction bit 1 | Current direction control |
| **TB6612_AIN2** | AIN2 | GPIO 33 | Direction bit 2 | Current direction control |
| **TB6612_STBY** | STBY | GPIO 14 | Standby | Module enable (HIGH=active) |
| **PIR_SENSOR** | OUT | GPIO 35 | Detection signal | HIGH = motion detected |
| **BUTTON_1** | Button | GPIO 16 | External button | Animation change |
| **BUTTON_2** | Button | GPIO 17 | External button | Mode change |
| **BUTTON_BOOT** | Button | GPIO 0 | Integrated BOOT button | Long press = restart |
| **I2C_SDA** | SDA | GPIO 21 | I2C Data | Available for expansion |
| **I2C_SCL** | SCL | GPIO 22 | I2C Clock | Available for expansion |

---

## 🖥️ LCD ST7789 Display (Integrated)

### Display Specifications
- **Resolution**: 135×240 pixels
- **Color Depth**: RGB565 (16-bit, 65K colors)
- **Interface**: SPI (hardware pins)
- **Orientation**: Landscape (rotation = 1)
- **Refresh Rate**: 10 FPS for animations

### Hardwired Connections

```
ESP32 IdeaSpark Board
┌─────────────────────────────────┐
│                                 │
│  ┌───────────────────────────┐  │
│  │   ST7789 1.14" LCD        │  │
│  │   (135×240 pixels)        │  │
│  │   Hardwired on PCB        │  │
│  └───────────────────────────┘  │
│                                 │
│  GPIO 23 ──► MOSI (SPI Data)    │
│  GPIO 18 ──► SCLK (SPI Clock)   │
│  GPIO 15 ──► CS (Chip Select)   │
│  GPIO  2 ──► DC (Data/Command)  │
│  GPIO  4 ──► RST (Reset)        │
│  GPIO 32 ──► BLK (Backlight)    │ ⚠️ MUST BE HIGH
│                                 │
└─────────────────────────────────┘
```

**⚠️ CRITICAL - Backlight Control**:
- **GPIO 32 (BLK)** controls display backlight
- **Must be set HIGH** to see any image on screen
- Configured automatically in `setupDisplay()` function

---

## 🎄 TB6612FNG Motor Driver + LED Garland

### Pin Configuration

| Signal | ESP32 GPIO | TB6612FNG Pin | Function |
|--------|------------|---------------|----------|
| PWMA | GPIO 12 | PWMA | PWM intensity control (0-255) |
| AIN1 | GPIO 25 | AIN1 | Direction control bit 1 |
| AIN2 | GPIO 33 | AIN2 | Direction control bit 2 |
| STBY | GPIO 14 | STBY | Standby (HIGH = active) |
| VCC | 3.3V | VCC | Logic power |
| VM | 5-15V | VM | Motor/garland power |
| GND | GND | GND | Common ground |

### Connection Schematic

```
ESP32 IdeaSpark         TB6612FNG              LED Garland
┌─────────────┐         ┌──────────┐           ┌──────────┐
│             │         │          │           │          │
│  GPIO 12    ├────────►│ PWMA     │           │          │
│  GPIO 25    ├────────►│ AIN1     │           │          │
│  GPIO 33    ├────────►│ AIN2     │           │          │
│  GPIO 14    ├────────►│ STBY     │           │          │
│             │         │          │           │          │
│    3.3V     ├────────►│ VCC      │           │          │
│    GND      ├────────►│ GND      ├──────────►│ GND (-)  │
│             │         │          │           │          │
│             │   ┌────►│ VM       │           │          │
│             │   │     │          │           │          │
│             │   │     │ AO1      ├──────────►│ Wire 1   │
│             │   │     │ AO2      ├──────────►│ Wire 2   │
│             │   │     │          │           │          │
└─────────────┘   │     └──────────┘           └──────────┘
                  │
           External Power
           (5V-15V DC)
           ┌───────┐
           │   +   ├──────┘
           │   -   ├────────────────────────────►Common GND
           └───────┘
```

### TB6612FNG Power Requirements

**⚠️ IMPORTANT - Dual Power Supply**:
- **VCC (3.3V)**: Control logic from ESP32 3V3 pin
- **VM (5-15V)**: Motor power for LED garland (external source)
- **GND**: **MUST BE COMMON** between ESP32, TB6612FNG, and external power supply

### TB6612FNG Truth Table

| AIN1 | AIN2 | STBY | Output | Garland State |
|------|------|------|--------|---------------|
| LOW | LOW | HIGH | OFF | LEDs off (brake) |
| HIGH | LOW | HIGH | Forward | Direction A LEDs on |
| LOW | HIGH | HIGH | Reverse | Direction B LEDs on |
| HIGH | HIGH | HIGH | Brake | Short brake |
| X | X | LOW | Disabled | Module disabled |

### LED Garland Operating Principle

```
Anti-Parallel LED Configuration:

Wire 1 ──┬──►|──►|──►|── (Direction A: ~25 LEDs)
         │
Wire 2 ──┼──◄|──◄|──◄|── (Direction B: ~25 LEDs)
         │
        GND
```

- **Forward (AIN1=HIGH, AIN2=LOW)**: Direction A LEDs light up
- **Reverse (AIN1=LOW, AIN2=HIGH)**: Direction B LEDs light up
- **PWM (PWMA 0-255)**: Controls brightness of active LEDs
- **Frequency**: 5000 Hz for smooth dimming

---

## 🚶 PIR Motion Sensor (HC-SR501)

### Pin Configuration

| ESP32 GPIO | PIR Pin | Function |
|------------|---------|----------|
| GPIO 35 | OUT | Digital signal (HIGH = motion detected) |
| 5V | VCC | Power supply |
| GND | GND | Ground |

### Connection Schematic

```
ESP32 IdeaSpark      PIR HC-SR501
┌─────────────┐      ┌──────────┐
│             │      │          │
│  GPIO 35    ├─────►│ OUT      │ (Input-only pin)
│     5V      ├─────►│ VCC      │
│    GND      ├─────►│ GND      │
│             │      │          │
└─────────────┘      └──────────┘
```

**📌 Pin Selection Notes**:
- **GPIO 35** is an input-only pin (perfect for sensors)
- Cannot be used for outputs
- No internal pull-up/pull-down resistors

### PIR Sensor Settings
- **Sensitivity**: Adjustable via potentiometer (3-7 meters range)
- **Delay Time**: Adjustable via potentiometer (5s - 300s)
- **Trigger Mode**: Repeatable (H) or Non-repeatable (L) - jumper setting

---

## 🔘 User Buttons

### Pin Configuration

| Button | ESP32 GPIO | Function | Trigger |
|--------|------------|----------|---------|
| BUTTON_BOOT | GPIO 0 | System restart | Long press (1s) |
| BUTTON_1 | GPIO 16 | Change animation | Short press |
| BUTTON_2 | GPIO 17 | Change mode | Short press |

### Connection Schematic

```
       ESP32 IdeaSpark
       ┌─────────────┐
       │             │
       │  GPIO 0     ├────┐  BUTTON_BOOT
       │  (BOOT)     │    │  (integrated)
       │             │    │
       │  GPIO 16    ├────┤  BUTTON_1
       │             │    │  (external)
       │             │    │
       │  GPIO 17    ├────┤  BUTTON_2
       │             │    │  (external)
       │             │    │
       │    GND      ├────┴─── Common GND
       │             │
       └─────────────┘

External Button Wiring (BUTTON_1 and BUTTON_2):

    GPIO 16/17 ──────┤   ├───── GND
                     │   │
                   Button

Note: Internal pull-up resistors enabled in software
```

### Button Configuration
- **Pull-up Mode**: Internal pull-up resistors enabled
- **Active State**: LOW (pressed = GND connection)
- **Debounce**: Handled by OneButton library

---

## 🔌 I2C Bus (Available for Expansion)

### Pin Configuration

| ESP32 GPIO | I2C Signal | Function |
|------------|------------|----------|
| GPIO 21 | SDA | I2C Data |
| GPIO 22 | SCL | I2C Clock |

**Available for**:
- External sensors (BME280, BMP180, etc.)
- RTC modules (DS3231, DS1307)
- I2C OLED displays (if needed)
- Other I2C peripherals

---

## ⚡ Power Supply Guide

### ESP32 IdeaSpark Power Options

1. **USB-C (Recommended for development)**
   - Voltage: 5V
   - Current: 500mA typical
   - Provides: 5V and 3.3V rails

2. **VIN Pin**
   - Voltage: 5V-12V DC
   - Current: Up to 1A
   - Regulated to 3.3V on-board

### TB6612FNG Power Requirements

- **VCC**: 2.7V - 5.5V (connect to ESP32 3.3V)
- **VM**: 4.5V - 13.5V (connect to external power supply)
- **Output Current**: Up to 1.2A per channel (peak 3.2A)

### Recommended Power Setup

```
┌─────────────────────┐
│  USB Power Bank     │ 5V, 2A
│  or Wall Adapter    │
└──────┬──────────────┘
       │
       ├──────────► ESP32 IdeaSpark (USB-C)
       │                 │
       │                 ├──► 3.3V logic
       │                 └──► LCD display
       │
       └──────────► TB6612FNG (VM pin)
                        │
                        └──► LED Garland
```

**⚠️ Power Warnings**:
- **Always** connect GND between ESP32 and TB6612FNG
- **Never** exceed 13.5V on TB6612FNG VM pin
- **Ensure** power supply can provide enough current for garland

---

## 🛠️ Pin Conflicts Resolution

### v1.0.0 Pin Changes

| Signal | Old GPIO (v0.x) | New GPIO (v1.0.0) | Reason |
|--------|----------------|-------------------|---------|
| TB6612_AIN1 | GPIO 32 | **GPIO 25** | GPIO 32 needed for LCD backlight |
| PIR_SENSOR | GPIO 14 | **GPIO 35** | GPIO 35 is input-only (ideal for sensors) |

### Shared Pins (Acceptable)

- **GPIO 2 (LED_BUILTIN + LCD_DC)**: Shared usage acceptable
  - LED_BUILTIN blinks during boot
  - LCD_DC used for display data/command signaling
  - No conflict as LCD_DC is output-only

---

## 📊 Complete GPIO Allocation Map

| GPIO | Function | Direction | Notes |
|------|----------|-----------|-------|
| 0 | BUTTON_BOOT | Input | Boot button (integrated) |
| 2 | LCD_DC | Output | Display data/command + LED_BUILTIN |
| 4 | LCD_RST | Output | Display reset |
| 12 | TB6612_PWMA | Output | PWM garland control |
| 14 | TB6612_STBY | Output | TB6612 standby |
| 15 | LCD_CS | Output | Display chip select |
| 16 | BUTTON_1 | Input | User button 1 |
| 17 | BUTTON_2 | Input | User button 2 |
| 18 | LCD_SCLK | Output | Display SPI clock |
| 21 | I2C_SDA | I/O | I2C data (expansion) |
| 22 | I2C_SCL | Output | I2C clock (expansion) |
| 23 | LCD_MOSI | Output | Display SPI data |
| 25 | TB6612_AIN1 | Output | Direction control 1 |
| 32 | LCD_BLK | Output | Display backlight (MUST be HIGH) |
| 33 | TB6612_AIN2 | Output | Direction control 2 |
| 35 | PIR_SENSOR | Input | Motion detection (input-only) |

**Total GPIOs Used**: 16 / 34 available

---

## 🧰 Beginner Tips

### 1. Start with Display Test
```cpp
void setup() {
    pinMode(LCD_BLK, OUTPUT);
    digitalWrite(LCD_BLK, HIGH);  // Turn on backlight!

    display.init(135, 240);
    display.setRotation(1);
    display.fillScreen(ST77XX_WHITE);
}
```

### 2. Test TB6612FNG Separately
- Connect LEDs first
- Test forward/reverse directions
- Verify PWM brightness control
- Check external power supply

### 3. Verify PIR Sensor
- Adjust sensitivity and delay pots
- Test in Serial Monitor
- Ensure 5V power supply

### 4. Button Testing
```cpp
void loop() {
    if (digitalRead(BUTTON_1) == LOW) {
        Serial.println("Button 1 pressed!");
    }
}
```

### 5. Common Mistakes to Avoid
- ❌ Forgetting to set LCD_BLK HIGH (screen stays black)
- ❌ Missing common GND between ESP32 and TB6612FNG
- ❌ Using GPIO 35 as output (it's input-only!)
- ❌ Exceeding 13.5V on TB6612FNG VM pin

---

## 📚 Additional Resources

- **ESP32 Pinout**: [Espressif Official Docs](https://docs.espressif.com/)
- **ST7789 Datasheet**: Adafruit ST7789 library documentation
- **TB6612FNG Datasheet**: [Toshiba Official](https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf)
- **HC-SR501 PIR**: Standard motion sensor module

---

## 🔍 Troubleshooting

### LCD Display Not Working
1. Check LCD_BLK is set to HIGH
2. Verify SPI connections (MOSI, SCLK, CS)
3. Test with simple fill screen command
4. Check 3.3V power supply

### Garland Not Lighting
1. Verify TB6612FNG STBY is HIGH
2. Check VM external power supply (5-15V)
3. Verify common GND connection
4. Test AIN1/AIN2 logic levels
5. Measure PWMA PWM signal

### PIR Sensor Always Triggering
1. Adjust sensitivity potentiometer
2. Move sensor away from heat sources
3. Check for air currents/vibrations
4. Verify 5V power supply voltage

### Buttons Not Responding
1. Check wiring to GND
2. Verify internal pull-up enabled in code
3. Test with multimeter (should read 3.3V when not pressed)

---

**LED-Garland-Anim v1.0.0** - ESP32 IdeaSpark 1.14" LCD Platform 🎄✨
