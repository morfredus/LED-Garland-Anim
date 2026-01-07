# Release v5.1.5 – 2026-01-07

**Version**: 5.1.5 (PATCH)  
**Release Type**: Minor Update  
**Date**: 2026-01-07  
**Platform**: ESP32 Classic (IdeaSpark/DevKitC)  
**Build Status**: ✅ SUCCESS  

---

## 📋 Summary

Release v5.1.5 adds the missing **`secrets_example.h`** template file for easy WiFi configuration setup, alongside all improvements from v5.1.4 (Telegram removal + complete documentation overhaul).

This is the **complete, recommended version** that combines:
- **v5.1.2 firmware**: Telegram module removal (cleaner codebase)
- **v5.1.3 documentation**: Complete audit and version synchronization
- **v5.1.5 config**: Added `secrets_example.h` template for user convenience

---

## 🆕 What's New in v5.1.5

### ✅ Added
- **`include/secrets_example.h`**: Template file for WiFi network configuration
  - Provides example structure for users setting up their WiFi credentials
  - Clearly shows how to add multiple networks
  - Prevents users from accidentally modifying `secrets.h` (which is git-ignored)
  - **Usage**: Copy to `include/secrets.h`, edit with your WiFi details

### ✨ From v5.1.4 (Included in v5.1.5)

#### Added
- **New beginner-friendly guides** (bilingual EN/FR):
  - `docs/QUICKSTART.md` / `QUICKSTART_FR.md`: 5-minute quick start guide
  - `docs/HARDWARE_GUIDE.md` / `HARDWARE_GUIDE_FR.md`: Complete component shopping list with suppliers
- **Release notes for v5.1.4**:
  - `docs/RELEASE_v5.1.4.md` (English)
  - `docs/RELEASE_v5.1.4_FR.md` (French)

#### Removed (v5.1.2)
- Deleted unused Telegram module files: `src/telegram_control.cpp`, `include/telegram_control.h`
- Deleted 7 obsolete release note files (v1.x, v3.x series)
- Removed all Telegram references from documentation

#### Changed (v5.1.4)
- **Version synchronization** across all documentation to v5.1.4 (now v5.1.5)
- **README.md restructured**: "Choosing USB or OTA Upload" section repositioned
- **Firmware version**: 5.1.2 → 5.1.5 in platformio.ini, config.h, main.cpp

---

## 📦 Package Contents

### Firmware Files
- ✅ `platformio.ini` (PROJECT_VERSION="5.1.5")
- ✅ `include/config.h` (@version 5.1.5)
- ✅ `src/main.cpp` (@version 5.1.5)
- ✅ **`include/secrets_example.h`** (NEW - Template for WiFi setup)
- ✅ All source files (no Telegram references)

### Documentation
- ✅ **README.md / README_FR.md** (v5.1.5)
- ✅ **USER_GUIDE.md / USER_GUIDE_FR.md** (v5.1.5)
- ✅ **QUICKSTART.md / QUICKSTART_FR.md** (v5.1.5)
- ✅ **HARDWARE_GUIDE.md / HARDWARE_GUIDE_FR.md** (v5.1.5)
- ✅ **ARCHITECTURE.md / ARCHITECTURE_FR.md** (v5.1.5)
- ✅ **PIN_MAPPING.md / PIN_MAPPING_FR.md** (v5.1.5)
- ✅ **TROUBLESHOOTING.md / TROUBLESHOOTING_FR.md** (v5.1.5)
- ✅ **OTA_UPDATE.md / OTA_UPDATE_FR.md** (v5.1.5)
- ✅ **PIR_SENSOR_SETUP.md / PIR_SENSOR_SETUP_FR.md** (v5.1.5)
- ✅ **RADAR_SENSOR_SETUP.md / RADAR_SENSOR_SETUP_FR.md** (v5.1.5)
- ✅ **RELEASE_v5.1.5.md / RELEASE_v5.1.5_FR.md** (This file)
- ✅ Complete **CHANGELOG.md / CHANGELOG_FR.md** with v5.1.5 entry

---

## 🚀 Getting Started

### First-Time Setup

1. **Clone or download** the v5.1.5 release
2. **Configure WiFi**:
   - Copy `include/secrets_example.h` → `include/secrets.h`
   - Edit `include/secrets.h` with your WiFi credentials:
     ```cpp
     inline const char* WIFI_NETWORKS[][2] = {
         {"YourSSID_1", "YourPassword_1"},
         {"YourSSID_2", "YourPassword_2"}
     };
     ```
   - Save and proceed to build

3. **Build the firmware** (PlatformIO):
   ```bash
   pio run -e esp32devkitc
   ```

4. **Flash the firmware** (USB or OTA):
   - USB: `pio run --target upload -e esp32devkitc`
   - OTA: [See OTA_UPDATE.md for details](./OTA_UPDATE.md)

5. **Access the web interface**:
   - Open browser: `http://garland.local` (or IP address)
   - Configure animations, colors, and sensors as desired

---

## 🔧 Technical Specifications

### Hardware Support
- **Microcontroller**: ESP32 Classic (IdeaSpark or DevKitC)
- **Flash Memory**: 4MB
- **RAM**: 320KB
- **GPIO Pins**: 28 (23 digital, 15 analog)
- **WiFi**: 802.11 b/g/n (2.4 GHz)
- **OTA Support**: ✅ ArduinoOTA + Web OTA

### Build Information
- **Framework**: Arduino (espressif32@^6)
- **Language**: C++ (C++17)
- **Build Size**:
  - **Flash**: ~72% (935,105 / 1,310,720 bytes)
  - **RAM**: ~16% (50,648 / 327,680 bytes)
- **Compilation**: ✅ SUCCESS (no errors/warnings)

### Supported Features
- 🎄 LED Garland animation with 5 animation modes
- 📺 8x8 LED Matrix display with effects
- 💡 ST7789 LCD display (320×240)
- 🌐 Web-based control interface (responsive)
- 📱 Real-time WiFi configuration (SSID/password change)
- 🔌 GPIO button control (mode + animation switching)
- 🚨 PIR motion sensor integration (optional)
- 🎯 RCWL-0516 radar sensor integration (optional)
- 🔄 Firmware updates (OTA + USB)
- 💾 NVS persistence (settings survive reboot)
- 🌙 Device name customization (mDNS: `device-name.local`)

---

## 📝 Version History

| Version | Date | Type | Notes |
|---------|------|------|-------|
| 5.1.5 | 2026-01-07 | PATCH | Added `secrets_example.h` template + v5.1.2+v5.1.3+v5.1.4 consolidation |
| 5.1.4 | 2026-01-07 | PATCH | Consolidated v5.1.2 (Telegram removal) + v5.1.3 (doc sync) |
| 5.1.3 | 2026-01-07 | PATCH | Complete documentation overhaul (28+ files updated to v5.1.2) |
| 5.1.2 | 2026-01-07 | PATCH | Removed unused Telegram module (src/telegram_control.*) |
| 5.1.1 | 2026-01-07 | PATCH | Fixed matrix animation interval independence |
| 5.1.0 | 2026-01-06 | MINOR | Reorganized animated LCD layout to full-width stacked zones |
| 5.0.0 | 2025-12-25 | MAJOR | Major refactoring: modular architecture, web UI, multiple sensor support |

---

## 🎯 Recommendation

✅ **v5.1.5 is the recommended version** for all users:
- Includes all features from v5.0.0 through v5.1.4
- Clean, Telegram-free codebase
- Complete documentation (EN/FR)
- Easy WiFi setup with `secrets_example.h` template
- Fully tested and stable

---

## 📖 Documentation Links

- **[README](../README.md)** – Project overview and installation
- **[Quick Start](./QUICKSTART.md)** – 5-minute setup guide
- **[User Guide](./USER_GUIDE.md)** – Complete feature documentation
- **[Hardware Setup](./HARDWARE_GUIDE.md)** – Component sourcing and connections
- **[Architecture](./ARCHITECTURE.md)** – Code structure and design
- **[Pin Mapping](./PIN_MAPPING.md)** – Wiring diagrams and GPIO assignments
- **[OTA Updates](./OTA_UPDATE.md)** – Firmware update procedures
- **[Troubleshooting](./TROUBLESHOOTING.md)** – Problem-solving guide
- **[PIR Sensor](./PIR_SENSOR_SETUP.md)** – Motion detection setup
- **[Radar Sensor](./RADAR_SENSOR_SETUP.md)** – Doppler radar integration

---

## 🆘 Support

For issues or questions:
1. **Check [TROUBLESHOOTING.md](./TROUBLESHOOTING.md)** for common problems
2. **Review [QUICKSTART.md](./QUICKSTART.md)** for setup guidance
3. **Read [USER_GUIDE.md](./USER_GUIDE.md)** for feature documentation
4. **Open an issue** on [GitHub](https://github.com/morfredus/LED-Garland-Anim/issues)

---

**Happy decorating! 🎄✨**

**Available at**: https://github.com/morfredus/LED-Garland-Anim/releases/tag/v5.1.5
