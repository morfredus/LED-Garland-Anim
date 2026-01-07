# Release Notes v5.2.0 - ESP32-C3 HW-675 Support

**Date**: 2026-01-07  
**Version**: 5.2.0  
**Type**: MINOR (New hardware platform)

---

## 🎯 Release Summary

This release introduces **full support for ESP32-C3 HW-675** with integrated **OLED 0.42" (72×40 px)** display, expanding hardware compatibility to include RISC-V architecture alongside existing ESP32 Classic (Xtensa) support. The implementation maintains 100% backward compatibility and feature parity across both platforms.

---

## ✨ New Features

### 1. ESP32-C3 HW-675 Platform Support

**New PlatformIO Environment**: `esp32c3_hw675`
- Board: `esp32-c3-devkitm-1`
- Architecture: RISC-V single-core @ 160MHz
- Flash: 4MB, RAM: 320KB
- USB CDC Serial with proper initialization timing
- Build flags: `TARGET_ESP32C3_HW675`, `HAS_OLED_U8G2`, `ARDUINO_USB_MODE=1`, `ARDUINO_USB_CDC_ON_BOOT=1`

### 2. OLED Display Module (`src/display_oled.cpp`)

**Display Specifications**:
- Controller: SSD1306
- Resolution: 72×40 pixels (0.42" diagonal)
- Interface: I2C Hardware (SDA=GPIO5, SCL=GPIO6)
- I2C Address: 0x3C
- Library: U8g2 @ ^2.35.19

**Features**:
- Simplified display layout optimized for small resolution
- Shows: IP address + Current mode only
- I2C bus scanner for hardware diagnostics
- Boot screen with project name
- Auto-update on mode changes

**U8g2 Constructor** (validated):
```cpp
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
```

### 3. Board Configuration Dispatcher

**File**: `include/board_config.h`

Automatic pin mapping selection based on build target:
- `#ifdef TARGET_ESP32C3_HW675` → ESP32-C3 HW-675 pins
- `#else` → ESP32 Classic IdeaSpark pins

**ESP32-C3 HW-675 Pin Map**:
| Function | GPIO | Notes |
|----------|------|-------|
| OLED SDA | 5 | I2C Data |
| OLED SCL | 6 | I2C Clock |
| TB6612 PWMA | 0 | Garland intensity |
| TB6612 AIN1 | 1 | Direction control |
| TB6612 AIN2 | 2 | Direction control |
| TB6612 STBY | 3 | Module enable |
| Matrix WS2812B | 8 | NeoPixel data |
| BOOT Button | 9 | Mode cycle + reboot |
| Motion Sensor | 10 | PIR/RCWL (optional) |

### 4. BOOT Button Functionality (ESP32-C3)

**Button**: GPIO 9 (integrated on board)

**Actions**:
- **Single click**: Cycle through operating modes
  1. MODE_MOTION_TRIGGER (Détection)
  2. MODE_MOTION_MATRIX_INDEPENDENT (Détection+Tout)
  3. MODE_PERMANENT (Permanent)
- **Long press (1 second)**: System reboot

### 5. USB CDC Serial Initialization (ESP32-C3)

**Issue**: ESP32-C3 USB CDC requires explicit initialization timing  
**Solution**: Added ESP32-C3 specific code in `main.cpp`:

```cpp
#ifdef TARGET_ESP32C3_HW675
    delay(2000);  // Wait for USB CDC enumeration
    while (!Serial && millis() < 3000) {
        delay(10);  // Wait for serial connection
    }
    Serial.println("==========================================");
    Serial.println("ESP32-C3 HW-675 - LED Garland Controller");
    Serial.println("==========================================");
#endif
```

---

## 🔧 Technical Changes

### Modified Files

1. **`platformio.ini`**: Added `[env:esp32c3_hw675]` with U8g2 dependency
2. **`include/config.h`**: Conditional `HAS_ST7789` exclusion for ESP32-C3
3. **`include/board_config.h`**: Pin mapping dispatcher
4. **`src/display.cpp`**: Fixed stub conditions (`#elif !defined(HAS_OLED_U8G2)`)
5. **`src/main.cpp`**: ESP32-C3 USB CDC init + BOOT button handler

### New Files

- **`src/display_oled.cpp`**: OLED display implementation (136 lines)

### Build Statistics

**ESP32-C3 HW-675** (`esp32c3_hw675`):
- Flash: 70.7% (926KB / 1310KB)
- RAM: 13.7% (45KB / 327KB)
- Build time: ~18s

**ESP32 Classic** (`esp32devkitc`):
- Flash: 71.3% (unchanged)
- RAM: 15.5% (unchanged)
- Build time: ~20s (unchanged)

---

## 🎓 Validated Hardware

### Test Configuration

**Board**: ESP32-C3-DevKitM-1 with HW-675 OLED module  
**OLED**: SSD1306 72×40 via I2C (address 0x3C)  
**Power**: USB-C 5V  
**Firmware**: v5.2.0 built with `pio run -e esp32c3_hw675`

### Working Test Code

Validated OLED functionality with minimal test:

```cpp
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define SDA_PIN 5
#define SCL_PIN 6

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 72, 40);
  u8g2.setFont(u8g2_font_04b_03_tr);
  u8g2.drawStr(2, 12, "OLED OK");
  u8g2.drawStr(2, 24, "Init...");
  u8g2.sendBuffer();
  delay(2000);
}
```

**PlatformIO environment** (validated):
```ini
[env:esp32c3_hw675]
platform = espressif32
board = esp32-c3-devkitm-1
framework = arduino
monitor_speed = 115200
lib_deps = 
    olikraus/U8g2 @ ^2.35.19
    adafruit/Adafruit NeoPixel @ ^1.12.0
build_flags = 
    -D ARDUINO_USB_MODE=1
    -D ARDUINO_USB_CDC_ON_BOOT=1
```

---

## 📚 Documentation Updates

### Updated Files (EN/FR)
- ✅ CHANGELOG.md / CHANGELOG_FR.md → v5.2.0 entry
- ✅ README.md / README_FR.md → ESP32-C3 hardware requirements
- ✅ PIN_MAPPING.md / PIN_MAPPING_FR.md → Complete ESP32-C3 table
- ✅ HARDWARE_GUIDE.md / HARDWARE_GUIDE_FR.md → ESP32-C3 specs
- ✅ QUICKSTART.md / QUICKSTART_FR.md → `esp32c3_hw675` build instructions
- ✅ ARCHITECTURE.md / ARCHITECTURE_FR.md → `display_oled.cpp` module

### Removed Files
- ❌ RELEASE_v4.0.0.md/FR → v5.0.0.md/FR → v5.1.x.md/FR (14 files deleted)

### New Files
- ✅ RELEASE_v5.2.0.md / RELEASE_v5.2.0_FR.md

---

## 🔄 Compatibility

### Backward Compatibility
- ✅ **ESP32 Classic builds unchanged**: No modifications to existing `esp32devkitc` environment
- ✅ **Web UI identical**: 100% feature parity across platforms
- ✅ **Configuration format**: Same `secrets.h` and NVS structure
- ✅ **OTA updates**: Compatible with both platforms

### Platform Comparison

| Feature | ESP32 Classic | ESP32-C3 HW-675 |
|---------|--------------|-----------------|
| Architecture | Xtensa dual-core | RISC-V single-core |
| Display | ST7789 135×240 TFT | SSD1306 72×40 OLED |
| Display Interface | SPI | I2C |
| Buttons | 3 (BOOT + BTN1 + BTN2) | 1 (BOOT multifunc) |
| Motion Sensor | GPIO35 (standard) | GPIO10 (optional) |
| Garland Control | TB6612FNG standard | TB6612FNG standard |
| Matrix LEDs | GPIO27 (GPIO34 alternative) | GPIO8 |
| Web UI | Full | Full |
| OTA | ✅ | ✅ |

---

## 🚀 Installation

### For ESP32 Classic (Existing)
```bash
pio run -e esp32devkitc
pio run -e esp32devkitc -t upload
```

### For ESP32-C3 HW-675 (New)
```bash
pio run -e esp32c3_hw675
pio run -e esp32c3_hw675 -t upload
pio device monitor
```

### First Boot
1. Device connects to WiFi (configured in `secrets.h`)
2. Serial output shows:
   - Banner: "ESP32-C3 HW-675 - LED Garland Controller"
   - I2C scan: "Device at 0x3C"
   - OLED test screen: "OLED OK / Init..."
3. OLED displays: IP address + current mode
4. Web UI accessible at IP or mDNS name

---

## 🐛 Known Issues

### None Critical
All features validated and working as expected.

### Optional Enhancements (Future)
- Matrix animations could be optimized for smaller OLED display
- Additional display modes for OLED (animation preview, network stats)
- Software I2C fallback for alternative pin configurations

---

## 🎯 Migration Guide

### From v5.1.5 to v5.2.0

**No action required** for existing ESP32 Classic users. This is a pure **MINOR** release adding new hardware support without breaking changes.

**For new ESP32-C3 HW-675 users**:
1. Use environment `esp32c3_hw675` in platformio.ini
2. Follow pin mapping in docs/PIN_MAPPING.md (ESP32-C3 section)
3. Connect OLED via I2C (SDA=5, SCL=6, no external resistors needed)
4. BOOT button (GPIO9) handles all mode changes

---

## 👥 Contributors

- **morfredus** - ESP32-C3 integration, OLED driver, documentation

---

## 📝 Version Classification

**SEMVER**: **5.2.0 (MINOR)**
- Major: 5 (Festive UI redesign)
- Minor: 2 (New hardware platform support)
- Patch: 0 (Initial release)

**Rationale**: Adding ESP32-C3 support is a **MINOR** change because:
- ✅ New functionality (OLED display, new board)
- ✅ Backward compatible (ESP32 Classic unchanged)
- ✅ No breaking changes to existing code or configuration
- ✅ Additive only (new environment, new files)

---

## 🔗 Resources

- **GitHub Repository**: https://github.com/morfredus/LED-Garland-Anim
- **Documentation**: See `docs/` folder (EN + FR)
- **Hardware Guide**: docs/HARDWARE_GUIDE.md
- **Pin Mapping**: docs/PIN_MAPPING.md
- **Quickstart**: docs/QUICKSTART.md

---

**Happy coding! 🎄✨**
