# Release Notes v5.6.4 (2026-02-02)

**Valid from version 5.6.4**

## 🐛 Critical Bug Fixes

### 1. Operating Mode Persistence Restored
**Problem**: Operating mode (Permanent/Motion Trigger) was not correctly restored at boot, always reverting to permanent mode regardless of saved settings.

**Root Cause**: NVS (Non-Volatile Storage) type mismatch — the mode was being saved as `u8` (unsigned 8-bit) but read back as `i32` (signed 32-bit integer), causing data corruption.

**Solution**: Unified storage and retrieval to use `i32` type consistently, ensuring mode persistence across reboots.

**Impact**: Users can now rely on their chosen operating mode being preserved after power cycling or reboot.

---

### 2. ESP32-S3 Mini Pin Mapping Correction
**Problem**: Motion sensor pin was incorrectly documented as GPIO7 in all documentation files, but the actual hardware uses GPIO2.

**Solution**: Corrected `MOTION_SENSOR_PIN` from GPIO7 to GPIO2 across:
- [README.md](../README.md)
- [README_FR.md](../README_FR.md)
- [PIN_MAPPING.md](PIN_MAPPING.md)
- [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md)

**Impact**: Hardware setup now matches documentation, preventing connection errors for ESP32-S3 Mini users.

---

## 📚 Documentation Updates

### Physical Button Controls Table
Updated all user documentation with a comprehensive table detailing BOOT button and USER button functionality:

| Button | Action | Function |
|--------|--------|----------|
| **BOOT** | Short press | Cycle through operating modes |
| **BOOT** | Long press (2s) | System reboot |
| **USER** | Short press | Switch garland animation (Manual mode) |
| **USER** | Long press (2s) | Toggle matrix on/off |

This table is now included in:
- Main README files ([README.md](../README.md) / [README_FR.md](../README_FR.md))
- Pin mapping documentation ([PIN_MAPPING.md](PIN_MAPPING.md) / [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md))

---

## 🔧 Technical Details

### NVS Type Correction
```cpp
// Before (incorrect)
nvs_set_u8(nvs_handle, "operating_mode", mode);  // Save as u8
nvs_get_i32(nvs_handle, "operating_mode", &mode); // Read as i32 ❌

// After (correct)
nvs_set_i32(nvs_handle, "operating_mode", mode);  // Save as i32 ✅
nvs_get_i32(nvs_handle, "operating_mode", &mode); // Read as i32 ✅
```

### GPIO Mapping (ESP32-S3 Mini)
```cpp
// board_config.h
#ifdef TARGET_ESP32S3_MINI
    #define MOTION_SENSOR_PIN 2  // Previously incorrectly documented as GPIO7
#endif
```

---

## 📦 Supported Hardware

This release supports all existing platforms:
- **ESP32 Classic** (IdeaSpark/DevKitC)
- **ESP32 Wroom** (DevKit V1)
- **ESP32-S3 Mini** (esp32s3_mini)
- **ESP32-S3 Super Mini** (esp32s3_supermini)

All platforms support **OLED SSD1306 (I2C)** display if connected.

---

## 🚀 Installation

### PlatformIO
```bash
# Update to v5.6.4
git pull origin main
git checkout v5.6.4
pio run -e <your_board> -t upload
```

Replace `<your_board>` with:
- `esp32devkitc` (ESP32 Classic)
- `esp32_wroom` (ESP32 Wroom)
- `esp32s3_mini` (ESP32-S3 Mini)
- `esp32s3_supermini` (ESP32-S3 Super Mini)

### OTA Update
If OTA is already configured on your device:
```bash
pio run -e <your_board> -t upload --upload-port <device_ip>
```

---

## 📖 Documentation

- [Main README](../README.md) / [README français](../README_FR.md)
- [Full Changelog](../CHANGELOG.md) / [Changelog français](../CHANGELOG_FR.md)
- [Pin Mapping Guide](PIN_MAPPING.md) / [Guide français](PIN_MAPPING_FR.md)
- [Hardware Guide](HARDWARE_GUIDE.md) / [Guide français](HARDWARE_GUIDE_FR.md)
- [Troubleshooting](TROUBLESHOOTING.md) / [Dépannage](TROUBLESHOOTING_FR.md)

---

## 🙏 Feedback

If you encounter any issues with this release, please open an issue on the project repository with:
- Hardware platform used
- Steps to reproduce
- Serial monitor output (if applicable)

---

**Previous Release**: [v5.6.3](RELEASE_v5.6.3.md)  
**Full Changelog**: [CHANGELOG.md](../CHANGELOG.md)
