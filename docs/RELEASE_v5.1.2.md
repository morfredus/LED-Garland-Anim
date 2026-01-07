# Release v5.1.2 – 2026-01-07

## Summary
- Complete removal of Telegram bot module (code + documentation).
- Comprehensive documentation cleanup and version synchronization.
- Firmware size reduced, codebase simplified.

## Highlights

### 🗑️ Telegram Module Removal (PATCH)
- **Deleted files**: 
  - `src/telegram_control.cpp` (329 lines)
  - `include/telegram_control.h` (33 lines)
- **Removed all references** from:
  - README.md / README_FR.md
  - CHANGELOG.md / CHANGELOG_FR.md
  - docs/RELEASE_v5.1.0.md/FR
  - docs/RELEASE_v1.11.3.md
- **Reason**: Telegram module was unused and added unnecessary complexity

### 📚 Documentation Cleanup (v5.1.3)
- **Deleted obsolete release notes** (8 files):
  - FIXES_v1.12.0.md
  - RELEASE_v1.10.0.md through v1.12.1.md (4 files)
  - RELEASE_v3.0.1.md, v3.0.2.md
- **Version synchronization** across all documentation (v5.1.2):
  - README.md/FR
  - USER_GUIDE.md/FR
  - ARCHITECTURE.md/FR
  - PIN_MAPPING.md/FR
  - TROUBLESHOOTING.md/FR
  - PIR_SENSOR_SETUP.md/FR
  - RADAR_SENSOR_SETUP.md/FR
- **Restructured README.md**: Moved USB/OTA upload section to appropriate location (after Installation)

## Files Touched

### Code Changes (v5.1.2)
- platformio.ini (version bump: 5.1.1 → 5.1.2)
- include/config.h (version header updated)
- src/main.cpp (version header updated)
- Deleted: src/telegram_control.cpp, include/telegram_control.h

### Documentation Changes (v5.1.2 + v5.1.3)
- Root: README.md/FR, CHANGELOG.md/FR
- docs/: USER_GUIDE, ARCHITECTURE, PIN_MAPPING, TROUBLESHOOTING, PIR_SENSOR_SETUP, RADAR_SENSOR_SETUP (all EN/FR)
- docs/: RELEASE_v5.1.0/FR, RELEASE_v1.11.3.md
- Deleted: 8 obsolete release note files

## Build Status

**Build: ✅ SUCCESS**
- Flash: 71.3% (935,105 bytes / 1,310,720)
- RAM: 15.5% (50,648 bytes / 327,680)
- No compile errors or warnings

## Upgrade Notes

### From v5.1.1
1. Flash firmware v5.1.2 (USB or OTA)
2. No configuration changes required
3. All existing settings preserved (NVS)
4. Functionality identical (Telegram removal only)

### Documentation Improvements
- Updated all document versions for consistency
- Removed obsolete release notes (v1.x, v3.x series)
- Improved README structure (USB/OTA section moved)
- All guides now reference current version (5.1.2)

## SEMVER Classification

- **v5.1.2 (PATCH)**: Telegram module removal
  - No breaking changes
  - No new features
  - Code cleanup and removal of unused module
  
- **v5.1.3 (PATCH)**: Documentation cleanup
  - No code changes
  - Documentation version synchronization
  - Obsolete file removal

## Next Steps

Future releases will focus on:
- Enhanced beginner documentation (QUICKSTART.md)
- Hardware guide with component list (HARDWARE_GUIDE.md)
- Detailed build guide (BUILD_GUIDE.md)

---

**Release Date**: January 7, 2026  
**Target**: esp32devkitc  
**Framework**: Arduino (ESP32)  
**Platform**: Espressif 32
