# Release v5.1.4 – 2026-01-07

## Summary
Complete and consolidated release combining firmware cleanup (Telegram removal) and comprehensive documentation improvements in a single, unified package.

## Highlights

### 🔧 Firmware Changes

#### Telegram Module Removal
- **Deleted files**: 
  - `src/telegram_control.cpp` (329 lines)
  - `include/telegram_control.h` (33 lines)
- **Removed all Telegram references** from code and documentation
- **Impact**: Cleaner codebase, reduced bloat, simplified maintenance
- **Backward Compatibility**: ✅ Fully compatible with existing configurations

### 📚 Documentation Improvements

#### Version Synchronization
All documentation synchronized to v5.1.4 for consistency:
- ✅ README.md / README_FR.md
- ✅ USER_GUIDE.md / USER_GUIDE_FR.md
- ✅ ARCHITECTURE.md / ARCHITECTURE_FR.md
- ✅ PIN_MAPPING.md / PIN_MAPPING_FR.md
- ✅ TROUBLESHOOTING.md / TROUBLESHOOTING_FR.md
- ✅ OTA_UPDATE.md / OTA_UPDATE_FR.md
- ✅ PIR_SENSOR_SETUP.md / PIR_SENSOR_SETUP_FR.md
- ✅ RADAR_SENSOR_SETUP.md / RADAR_SENSOR_SETUP_FR.md

#### Obsolete Files Removed
- `docs/FIXES_v1.12.0.md`
- `docs/RELEASE_v1.10.0.md` through `v1.12.1.md` (4 files)
- `docs/RELEASE_v3.0.1.md` and `v3.0.2.md` (2 files)

#### New Beginner-Friendly Guides (Bilingual EN/FR)
- **QUICKSTART.md/FR**: 5-minute quick-start guide for complete beginners
  - Step-by-step setup instructions
  - Troubleshooting tips
  - All components explained
  
- **HARDWARE_GUIDE.md/FR**: Complete component shopping list
  - Where to buy each component
  - Specifications and compatibility info
  - Current estimated costs by region
  - Recommended suppliers worldwide

#### Documentation Structure Improvements
- README.md restructured: USB/OTA upload section moved to proper location
- All guides reorganized for better logical flow
- Consistent version headers across all documents
- Enhanced cross-references between related guides

### 🏗️ Technical Details

#### Build Specifications
- **Target**: esp32devkitc (ESP32 Classic)
- **Flash**: 71.3% (935,105 bytes / 1,310,720 bytes)
- **RAM**: 15.5% (50,648 bytes / 327,680 bytes)
- **Compilation Status**: ✅ SUCCESS (no errors/warnings)

#### Files Modified
- **Code**: 3 files (platformio.ini, include/config.h, src/main.cpp)
- **Documentation**: 28+ files updated to v5.1.4
- **New Files**: 2 (QUICKSTART, HARDWARE_GUIDE guides in EN/FR)
- **Removed Files**: 7 obsolete release notes

### 🎯 What's Fixed/Changed

**Performance**: 
- No performance changes (code quality improvement only)

**Features**:
- No feature changes (cleanup release)

**Compatibility**:
- ✅ Fully backward compatible
- ✅ All existing functionality preserved
- ✅ All existing settings compatible

### 📦 Single Unified Package

This release consolidates two separate updates (v5.1.2 firmware + v5.1.3 documentation) into one cohesive v5.1.4 package for:
- Simpler downloading (one release instead of two)
- Clearer version history
- Single point of reference for users
- Easier changelog management

### 🎁 Included in This Release

✅ Complete cleaned firmware (no Telegram module)  
✅ All updated documentation (v5.1.4)  
✅ 4 new beginner guides (QUICKSTART + HARDWARE_GUIDE in EN/FR)  
✅ Bilingual support (English + French)  
✅ Comprehensive release notes  
✅ Full CHANGELOG with v5.1.4 entry  

## Upgrade Notes

### From v5.1.1
1. Flash firmware v5.1.4 (USB or OTA)
2. No configuration changes required
3. All existing settings preserved
4. No breaking changes

### From v5.1.2 or v5.1.3
- If you've already upgraded to v5.1.2 or v5.1.3, no action needed
- v5.1.4 is the consolidated, recommended version

### First-Time Users
Start here:
1. **Read**: [docs/QUICKSTART.md](docs/QUICKSTART.md) or [docs/QUICKSTART_FR.md](docs/QUICKSTART_FR.md)
2. **Buy**: Check [docs/HARDWARE_GUIDE.md](docs/HARDWARE_GUIDE.md) or [docs/HARDWARE_GUIDE_FR.md](docs/HARDWARE_GUIDE_FR.md)
3. **Wire**: Follow [docs/PIN_MAPPING.md](docs/PIN_MAPPING.md) or [docs/PIN_MAPPING_FR.md](docs/PIN_MAPPING_FR.md)
4. **Build**: Use [BUILD_GUIDE.md](docs/BUILD_GUIDE.md) or [BUILD_GUIDE_FR.md](docs/BUILD_GUIDE_FR.md) (if available)
5. **Explore**: Full features in [docs/USER_GUIDE.md](docs/USER_GUIDE.md)

## Version History

| Version | Date | Type | Notable Changes |
|---------|------|------|-----------------|
| 5.1.4 | 2026-01-07 | Release | Consolidated v5.1.2 + v5.1.3 |
| 5.1.3 | 2026-01-07 | PATCH | Doc cleanup (not released as standalone) |
| 5.1.2 | 2026-01-07 | PATCH | Telegram removal (not released as standalone) |
| 5.1.1 | 2026-01-07 | PATCH | Matrix interval independence fix |
| 5.1.0 | 2026-01-06 | MINOR | LCD layout reorganization |
| 5.0.0 | 2026-01-06 | MAJOR | Festive animated LCD design |

## Installation & Downloads

**Available at**: https://github.com/morfredus/LED-Garland-Anim/releases/tag/v5.1.4

**Includes**:
- Source code
- Compiled firmware (if available)
- Full documentation
- All beginner guides

## Support & Troubleshooting

- **Quick Help**: See [docs/QUICKSTART.md](docs/QUICKSTART.md)
- **Problems?**: Check [docs/TROUBLESHOOTING.md](docs/TROUBLESHOOTING.md)
- **Hardware Questions**: Read [docs/HARDWARE_GUIDE.md](docs/HARDWARE_GUIDE.md)
- **Wiring Issues**: Consult [docs/PIN_MAPPING.md](docs/PIN_MAPPING.md)
- **Issues/Bugs**: Report on GitHub Issues

## SEMVER Classification

**v5.1.4 (PATCH)**
- Justification: Code cleanup (Telegram removal) + documentation improvements; no functional changes to shipped features; fully backward compatible

---

**Release Date**: January 7, 2026  
**Target Platform**: ESP32 Classic (IdeaSpark / DevKitC)  
**Framework**: Arduino ESP32 (espressif32@^6)  
**Documentation Language**: Bilingual (English + French)  

🎉 **Thank you for using LED-Garland-Anim!**
