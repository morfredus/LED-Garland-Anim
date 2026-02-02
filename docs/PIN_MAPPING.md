# Pin Connection Guide - LED-Garland-Anim v5.6.5

*This document is valid from version 5.6.5.*

## Supported Boards

This project supports **two boards**:

| Board | Environment | Description |
|-------|-------------|-------------|
| **ESP32-S3 Super Mini** | `esp32s3_supermini` | Compact board, **default choice** |
| **ESP32 Wroom DevKit V1** | `esp32wroom` | Classic development board |

---

## Complete Pin Mapping

### ESP32-S3 Super Mini

| Function | GPIO | Description |
|----------|------|-------------|
| **I2C SDA** | GPIO 4 | OLED display data |
| **I2C SCL** | GPIO 5 | OLED display clock |
| **TB6612 PWMA** | GPIO 10 | Garland brightness (PWM) |
| **TB6612 AIN1** | GPIO 11 | Garland direction A |
| **TB6612 AIN2** | GPIO 12 | Garland direction B |
| **TB6612 STBY** | GPIO 13 | Garland enable (HIGH = ON) |
| **Matrix DATA** | GPIO 7 | NeoPixel 8x8 matrix data |
| **Motion Sensor** | GPIO 2 | PIR or RCWL-0516 input |
| **User Button** | GPIO 8 | Animation/mode control |
| **BOOT Button** | GPIO 0 | Built-in (long press = reboot) |
| **LED** | GPIO 8 | Built-in LED |

### ESP32 Wroom DevKit V1

| Function | GPIO | Description |
|----------|------|-------------|
| **I2C SDA** | GPIO 21 | OLED display data |
| **I2C SCL** | GPIO 22 | OLED display clock |
| **TB6612 PWMA** | GPIO 12 | Garland brightness (PWM) |
| **TB6612 AIN1** | GPIO 25 | Garland direction A |
| **TB6612 AIN2** | GPIO 33 | Garland direction B |
| **TB6612 STBY** | GPIO 14 | Garland enable (HIGH = ON) |
| **Matrix DATA** | GPIO 27 | NeoPixel 8x8 matrix data |
| **Motion Sensor** | GPIO 35 | PIR or RCWL-0516 input |
| **User Button** | GPIO 16 | Animation/mode control |
| **BOOT Button** | GPIO 0 | Built-in (long press = reboot) |
| **LED** | GPIO 2 | Built-in LED |

---

## Quick Reference Table

| Function | ESP32-S3 Super Mini | ESP32 Wroom |
|----------|---------------------|-------------|
| I2C SDA | GPIO 4 | GPIO 21 |
| I2C SCL | GPIO 5 | GPIO 22 |
| TB6612 PWMA | GPIO 10 | GPIO 12 |
| TB6612 AIN1 | GPIO 11 | GPIO 25 |
| TB6612 AIN2 | GPIO 12 | GPIO 33 |
| TB6612 STBY | GPIO 13 | GPIO 14 |
| Matrix DATA | GPIO 7 | GPIO 27 |
| Motion Sensor | GPIO 2 | GPIO 35 |
| User Button | GPIO 8 | GPIO 16 |
| BOOT Button | GPIO 0 | GPIO 0 |

---

## Physical Button Controls

The firmware uses **one user button** plus the built-in BOOT button:

| Button | Action | Function |
|--------|--------|----------|
| **User Button** | 1 click | Next garland animation |
| **User Button** | 2 clicks | Next matrix animation |
| **User Button** | Long press | Change operating mode |
| **BOOT Button** | Long press | System reboot |

**User Button GPIO:**
- ESP32-S3 Super Mini: **GPIO 8**
- ESP32 Wroom: **GPIO 16**

---

## Wiring Tips for Beginners

### OLED Display (SSD1306)
Connect your OLED display using I2C:
- **VCC** to 3.3V
- **GND** to GND
- **SDA** to the SDA pin (GPIO 4 on S3 Super Mini, GPIO 21 on Wroom)
- **SCL** to the SCL pin (GPIO 5 on S3 Super Mini, GPIO 22 on Wroom)

### TB6612FNG Motor Driver (Garland Control)
- **PWMA** controls brightness (0-255)
- **AIN1/AIN2** control the direction of the current
- **STBY** must be HIGH for the motor to work
- **VM** to your garland power supply (usually 12V or 24V)
- **VCC** to 3.3V
- **GND** to GND (share with ESP32)

### NeoPixel Matrix 8x8
- **DIN** (Data In) to the Matrix DATA pin
- **VCC** to 5V (use external power for many LEDs)
- **GND** to GND (share with ESP32)

### Motion Sensor (PIR or RCWL-0516)
- **OUT** to the Motion Sensor pin
- **VCC** to 3.3V or 5V (check your sensor)
- **GND** to GND

---

## Notes

- The authoritative pin mapping is defined in `include/board_config.h`
- OLED display is optional but recommended for status display
- Motion sensor is optional (only needed for motion-triggered modes)
