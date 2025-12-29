# Pin Connection Guide - LED-Garland-Anim

> 📌 **Beginner's Guide**: This document explains how to physically connect components to your ESP32-S3 or ESP32 Classic board for the LED-Garland-Anim project.

## 🎯 Table of Contents
- [ESP32-S3 DevKitC-1](#esp32-s3-devkitc-1)
- [ESP32 Classic DevKitC](#esp32-classic-devkitc)
- [Detailed Connection Schematics](#detailed-connection-schematics)
- [TB6612FNG Module](#tb6612fng-module---garland-controller)
- [Beginner Tips](#beginner-tips)

---

## ESP32-S3 DevKitC-1

### 📋 Pin Summary Table

| Component | Signal | GPIO Pin | Description | Notes |
|-----------|--------|----------|-------------|-------|
| **BUTTON_BOOT** | Button | GPIO 0 | Integrated button on board | Already present, long press restart |
| **BUTTON_1** | Button | GPIO 16 | External button | Animation change |
| **BUTTON_2** | Button | GPIO 17 | External button | Mode change |
| **NEOPIXEL** | Data | GPIO 48 | Integrated addressable RGB LED | Visual status feedback |
| **I2C_SDA (OLED SSD1306)** | SDA | GPIO 21 | I2C Data | Connection to OLED SDA pin |
| **I2C_SCL (OLED SSD1306)** | SCL | GPIO 20 | I2C Clock | Connection to OLED SCL pin |
| **OLED SSD1306** | VCC | 3.3V | Power | ESP32 3V3 pin |
| **OLED SSD1306** | GND | GND | Ground | ESP32 GND pin |
| **TFT ST7789** | MOSI (SDA) | GPIO 11 | SPI Data | ST7789 SDA pin |
| **TFT ST7789** | SCLK (SCL) | GPIO 12 | SPI Clock | ST7789 SCL pin |
| **TFT ST7789** | CS | GPIO 10 | Chip Select | Device selection |
| **TFT ST7789** | DC | GPIO 9 | Data/Command | Data/command indicator |
| **TFT ST7789** | RST | GPIO 13 | Reset | Screen reset |
| **TFT ST7789** | BL | GPIO 7 | Backlight | LED backlight |
| **TFT ST7789** | VCC | 3.3V | Power | ESP32 3V3 pin |
| **TFT ST7789** | GND | GND | Ground | ESP32 GND pin |
| **TB6612_PWMA** | PWMA | GPIO 5 | PWM Direction A | Light intensity control |
| **TB6612_AIN1** | AIN1 | GPIO 6 | Direction bit 1 | Current direction control |
| **TB6612_AIN2** | AIN2 | GPIO 4 | Direction bit 2 | Current direction control |
| **TB6612_STBY** | STBY | GPIO 8 | Standby | Module activation (HIGH=active) |
| **TB6612FNG** | VCC | 3.3V | Logic power | ESP32 3V3 pin |
| **TB6612FNG** | VM | 5-15V | Motor power | External power for garland |
| **TB6612FNG** | GND | GND | Ground | Common with ESP32 GND |
| **PIR_SENSOR** | OUT | GPIO 14 | Detection signal | HIGH = motion detected |
| **PIR Sensor** | VCC | 5V | Power | ESP32 5V pin (via USB) |
| **PIR Sensor** | GND | GND | Ground | ESP32 GND pin |
| **LDR_SENSOR** | Signal | GPIO 15 | ADC Read | Voltage divider with R=10kΩ |
| **LDR** | VCC | 3.3V | Power | Via 10kΩ resistor |
| **LDR** | GND | GND | Ground | Via LDR to GND |

### 🎄 TB6612FNG + Garland Connection Schematic

```
ESP32-S3                TB6612FNG              LED Garland
┌─────────┐            ┌──────────┐           ┌──────────┐
│         │            │          │           │          │
│ GPIO 5  ├───────────►│ PWMA     │           │          │
│ GPIO 6  ├───────────►│ AIN1     │           │          │
│ GPIO 4  ├───────────►│ AIN2     │           │          │
│ GPIO 8  ├───────────►│ STBY     │           │          │
│         │            │          │           │          │
│   3V3   ├───────────►│ VCC      │           │          │
│   GND   ├───────────►│ GND      ├──────────►│ GND (-)  │
│         │            │          │           │          │
│         │    ┌──────►│ VM       │           │          │
│         │    │       │          │           │          │
│         │    │       │ AO1      ├──────────►│ Wire 1   │
│         │    │       │ AO2      ├──────────►│ Wire 2   │
│         │    │       │          │           │          │
└─────────┘    │       └──────────┘           └──────────┘
               │
        External Power
        (5V-15V)
        ┌──────┐
        │  +   ├──────┘
        │  -   ├────────────────────────────►Common GND
        └──────┘
```

**⚠️ IMPORTANT - TB6612FNG Power Supply**:
- **VCC** (3.3V): Control logic from ESP32
- **VM** (5-15V): Power supply for garland (from external source)
- **GND**: Common ground between ESP32, TB6612FNG and external power

**💡 Operating Principle**:
- LEDs are mounted in anti-parallel (2 groups back-to-back)
- Current direction change = change of lit LED group
- PWM controls light intensity (0-255)

### 🚶 PIR Sensor Connection Schematic

```
ESP32-S3           PIR HC-SR501
┌─────────┐        ┌──────────┐
│         │        │          │
│ GPIO 14 ├───────►│ OUT      │
│    5V   ├───────►│ VCC      │
│   GND   ├───────►│ GND      │
│         │        │          │
└─────────┘        └──────────┘
```

**PIR Configuration**:
- Adjust sensitivity via module potentiometer
- Adjust timeout delay (typically 3s-5min)
- HIGH signal when motion detected

### 💡 LDR Photoresistor Connection Schematic

```
ESP32-S3           LDR + Resistor
┌─────────┐        
│         │        3.3V
│         │          │
│         │         ┌┴┐
│         │         │ │ R = 10kΩ
│         │         └┬┘
│         │          │
│ GPIO 15 ├──────────┼───┐
│         │          │   │
│         │         ┌┴┐  │
│         │         │ │ LDR (Photoresistor)
│         │         └┬┘  │
│         │          │   │
│   GND   ├──────────┴───┘
│         │
└─────────┘
```

**Principle**:
- Voltage divider: 10kΩ resistor in series with LDR
- More light → low LDR resistance → high voltage
- Less light → high LDR resistance → low voltage
- 12-bit ADC reading: 0-4095

### 🔘 Button Connection Schematic

```
ESP32-S3           Button 1              Button 2
┌─────────┐        ┌──────┐              ┌──────┐
│         │        │      │              │      │
│ GPIO 16 ├────┬───┤  ○   ├───┐      ┌───┤  ○   ├───┐
│         │    │   │      │   │      │   │      │   │
│ GPIO 17 ├────┼───┘──────┘   │      │   └──────┴───┘
│         │    │              │      │              │
│   GND   ├────┴──────────────┴──────┴──────────────┘
│         │
└─────────┘
```

**Configuration**:
- Active-low buttons (press = GND)
- Internal pull-up enabled in code
- Debounce handled by OneButton library

### 🔌 OLED SSD1306 Connection Schematic (I2C)

```
ESP32-S3           OLED SSD1306
┌─────────┐        ┌──────────┐
│         │        │          │
│ GPIO 21 ├───────►│ SDA      │
│ GPIO 20 ├───────►│ SCL      │
│    3V3  ├───────►│ VCC      │
│    GND  ├───────►│ GND      │
│         │        │          │
└─────────┘        └──────────┘
```

**Default I2C Address**: `0x3C` (sometimes `0x3D`)

### 🖥️ TFT ST7789 Connection Schematic (SPI)

```
ESP32-S3           TFT ST7789
┌─────────┐        ┌──────────┐
│         │        │          │
│ GPIO 11 ├───────►│ MOSI/SDA │
│ GPIO 12 ├───────►│ SCLK/SCL │
│ GPIO 10 ├───────►│ CS       │
│ GPIO  9 ├───────►│ DC       │
│ GPIO 13 ├───────►│ RST      │
│ GPIO  7 ├───────►│ BL       │
│    3V3  ├───────►│ VCC      │
│    GND  ├───────►│ GND      │
│         │        │          │
└─────────┘        └──────────┘
```

---

## ESP32 Classic DevKitC

### 📋 Pin Summary Table

| Component | Signal | GPIO Pin | Description | Notes |
|-----------|--------|----------|-------------|-------|
| **BUTTON_BOOT** | Button | GPIO 0 | Integrated button on board | Already present, long press restart |
| **BUTTON_1** | Button | GPIO 4 | External button | Animation change |
| **BUTTON_2** | Button | GPIO 16 | External button | Mode change |
| **LED_BUILTIN** | LED | GPIO 2 | Integrated blue LED | Visual heartbeat |
| **OLED SSD1306** | SDA | GPIO 21 | I2C Data | Connection to OLED SDA pin |
| **OLED SSD1306** | SCL | GPIO 22 | I2C Clock | Connection to OLED SCL pin |
| **OLED SSD1306** | VCC | 3.3V | Power | ESP32 3V3 pin |
| **OLED SSD1306** | GND | GND | Ground | ESP32 GND pin |
| **TFT ILI9341** | MOSI | GPIO 23 | SPI Data | TFT SDA pin |
| **TFT ILI9341** | SCLK | GPIO 18 | SPI Clock | TFT SCL pin |
| **TFT ILI9341** | CS | GPIO 19 | Chip Select | Device selection |
| **TFT ILI9341** | DC | GPIO 27 | Data/Command | Data/command indicator |
| **TFT ILI9341** | RST | GPIO 26 | Reset | Screen reset |
| **TFT ILI9341** | BL | GPIO 13 | Backlight | LED backlight |
| **TFT ILI9341** | VCC | 3.3V | Power | ESP32 3V3 pin |
| **TFT ILI9341** | GND | GND | Ground | ESP32 GND pin |
| **TB6612_PWMA** | PWMA | GPIO 12 | PWM Direction A | Light intensity control |
| **TB6612_AIN1** | AIN1 | GPIO 32 | Direction bit 1 | Current direction control |
| **TB6612_AIN2** | AIN2 | GPIO 33 | Direction bit 2 | Current direction control |
| **TB6612_STBY** | STBY | GPIO 14 | Standby | Module activation (HIGH=active) |
| **TB6612FNG** | VCC | 3.3V | Logic power | ESP32 3V3 pin |
| **TB6612FNG** | VM | 5-15V | Motor power | External power for garland |
| **TB6612FNG** | GND | GND | Ground | Common with ESP32 GND |
| **PIR_SENSOR** | OUT | GPIO 35 | Detection signal | HIGH = motion detected |
| **PIR Sensor** | VCC | 5V | Power | ESP32 5V pin (via USB) |
| **PIR Sensor** | GND | GND | Ground | ESP32 GND pin |
| **LDR_SENSOR** | Signal | GPIO 34 | ADC Read | Voltage divider with R=10kΩ |
| **LDR** | VCC | 3.3V | Power | Via 10kΩ resistor |
| **LDR** | GND | GND | Ground | Via LDR to GND |

### 🎄 TB6612FNG + Garland Connection Schematic (ESP32 Classic)

```
ESP32 Classic          TB6612FNG              LED Garland
┌─────────┐            ┌──────────┐           ┌──────────┐
│         │            │          │           │          │
│ GPIO 12 ├───────────►│ PWMA     │           │          │
│ GPIO 32 ├───────────►│ AIN1     │           │          │
│ GPIO 33 ├───────────►│ AIN2     │           │          │
│ GPIO 14 ├───────────►│ STBY     │           │          │
│         │            │          │           │          │
│   3V3   ├───────────►│ VCC      │           │          │
│   GND   ├───────────►│ GND      ├──────────►│ GND (-)  │
│         │            │          │           │          │
│         │    ┌──────►│ VM       │           │          │
│         │    │       │          │           │          │
│         │    │       │ AO1      ├──────────►│ Wire 1   │
│         │    │       │ AO2      ├──────────►│ Wire 2   │
│         │    │       │          │           │          │
└─────────┘    │       └──────────┘           └──────────┘
               │
        External Power
        (5V-15V)
        ┌──────┐
        │  +   ├──────┘
        │  -   ├────────────────────────────►Common GND
        └──────┘
```

---

## TB6612FNG Module - Garland Controller

### 📚 Module Description

The **TB6612FNG** is a dual H-bridge that allows control of direction and intensity of current in two DC motors or, in our case, a bi-directional LED garland.

**Specifications**:
- Logic voltage: 2.7V - 5.5V (3.3V ESP32 compatible)
- Motor voltage (VM): 4.5V - 13.5V (15V max)
- Continuous current per channel: 1.2A
- Peak current: 3.2A (10ms)
- Supported PWM frequency: up to 100 kHz

### 🔌 TB6612FNG Pinout

```
        TB6612FNG
    ┌──────────────┐
VM ─┤1          24├─ VCC (3.3V)
GND─┤2          23├─ AO1 (Motor output A1)
AO2─┤3          22├─ AO2 (Motor output A2)
BO1─┤4          21├─ BO1 (Motor output B1)
BO2─┤5          20├─ BO2 (Motor output B2)
    │              │
PWMA─┤6         19├─ PWMB
AIN1─┤7         18├─ BIN1
AIN2─┤8         17├─ BIN2
STBY─┤9         16├─ GND
    │              │
    └──────────────┘
```

**For our project**, we use only **Channel A**:
- **PWMA**: PWM signal for intensity control
- **AIN1, AIN2**: Current direction control
- **STBY**: Module enable/disable
- **AO1, AO2**: Outputs to garland's 2 wires

### ⚡ Truth Table

| AIN1 | AIN2 | PWMA | Channel A State |
|------|------|------|-----------------|
| LOW  | LOW  | X    | Off (short to GND) |
| HIGH | LOW  | PWM  | Direction A (Forward) - LED group A |
| LOW  | HIGH | PWM  | Direction B (Backward) - LED group B |
| HIGH | HIGH | X    | Brake (internal short) |

**STBY** must be **HIGH** to activate the module.

### 🎨 Control Examples

#### Light LEDs Direction A (50% intensity)
```cpp
digitalWrite(TB6612_AIN1, HIGH);
digitalWrite(TB6612_AIN2, LOW);
analogWrite(TB6612_PWMA, 128);  // 50% of 255
```

#### Light LEDs Direction B (100% intensity)
```cpp
digitalWrite(TB6612_AIN1, LOW);
digitalWrite(TB6612_AIN2, HIGH);
analogWrite(TB6612_PWMA, 255);  // 100%
```

#### Turn off all LEDs
```cpp
digitalWrite(AIN1, LOW);
digitalWrite(AIN2, LOW);
// or
digitalWrite(STBY, LOW);  // Put entire module to sleep
```

---

## Beginner Tips

### ⚠️ Electrical Safety

1. **Always disconnect** power before modifying wiring
2. **Check polarity**: VCC = positive, GND = negative
3. **Don't reverse** power supply (risk of component destruction)
4. **Correct voltage**: ESP32 = 3.3V logic (not 5V on GPIO!)
5. **Garland current**: Ensure TB6612FNG can supply required current
6. **External power**: Use suitable power supply for VM (not ESP32 USB)

### 🔧 Wiring Verification

**Checklist before powering on**:
- [ ] All grounds (GND) connected together
- [ ] No short circuit between VCC and GND
- [ ] GPIO pins match code (`board_config.h`)
- [ ] External power has correct voltage (5-15V for VM)
- [ ] Cables properly inserted (no loose connections)
- [ ] Buttons correctly oriented

### 🧪 Progressive Testing

1. **Test ESP32 alone**: Upload code, check serial logs
2. **Test WiFi**: Check connection and IP acquisition
3. **Test displays**: Check OLED/TFT display
4. **Test buttons**: Press Btn1/Btn2, observe logs
5. **Test sensors**: Check PIR and LDR readings in serial monitor
6. **Test TB6612FNG**: Connect module (without garland), test directions
7. **Test garland**: Connect garland and test animations

### 🔍 Common Troubleshooting

#### ESP32 Won't Start
- Check USB power supply (defective cable?)
- Try another USB port
- Hold BOOT while uploading

#### OLED Won't Turn On
- Check I2C address (0x3C or 0x3D)
- Test with I2C scanner
- Check SDA/SCL connections (don't reverse)

#### TFT Shows Wrong Colors
- Check all SPI connections
- Ensure BL (backlight) is powered
- Test with library example sketch

#### Garland Won't Light
- Check that STBY is HIGH
- Check VM power supply (5-15V)
- Test AO1/AO2 outputs with multimeter
- Ensure code sends proper signals

#### PIR Continuously Detects
- Adjust sensitivity potentiometer
- Move away from heat sources (radiator, direct sun)
- Increase timeout delay on module

#### LDR Doesn't Vary
- Check voltage divider (10kΩ resistor)
- Test LDR resistance with multimeter
- Ensure GPIO 15/34 is in ADC mode

### 📐 Useful Calculations

**Garland current calculation**:
- Number of LEDs: ~50 (25 per direction)
- Current per LED: ~20mA (typical)
- Max total current: 25 × 20mA = 500mA = 0.5A
- ✅ TB6612FNG supports 1.2A continuous → OK

**LDR voltage divider**:
```
Vadc = 3.3V × (R / (R + Rldr))
```
- R = 10kΩ (fixed resistor)
- Rldr = variable (100Ω in full light, 10MΩ in dark)
- More light → low Rldr → high Vadc

---

## 📚 Additional Resources

### Datasheets
- **TB6612FNG**: [Toshiba TB6612FNG Datasheet](https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf)
- **HC-SR501**: [PIR Motion Sensor Datasheet](https://www.epitran.it/ebayDrive/datasheet/44.pdf)
- **ESP32-S3**: [Espressif ESP32-S3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)

### Tutorials
- [TB6612FNG Guide on SparkFun](https://learn.sparkfun.com/tutorials/tb6612fng-hookup-guide)
- [Using PIR Sensor](https://randomnerdtutorials.com/esp32-pir-motion-sensor/)
- [Reading LDR Photoresistor](https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/)

### Testing Tools
- **I2C Scanner**: To find OLED address
- **Multimeter**: To check voltages and continuity
- **Oscilloscope**: To observe PWM signals (optional)

---

**Note**: This guide accompanies the LED-Garland-Anim v0.2.0 project. For questions or issues, consult README.md and the commented source code.

**Document Version**: v0.2.0 - 2025-12-09
