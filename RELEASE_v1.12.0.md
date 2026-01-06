# Release Notes v1.12.0

**Date:** 2026-01-06

---

## 🎯 Major Feature: mDNS Support for Easy Network Access

Version 1.12.0 introduces **mDNS (Multicast DNS)** support, allowing users to access the web interface using a **unique, memorable device name** instead of searching for IP addresses.

---

## ✨ What's New

### 🏷️ Unique Device Name (mDNS)

**No more IP hunting!** Access your LED controller via a friendly name:

```
http://garland.local
```

**Key Features:**
- **Default name**: `garland.local` (customizable)
- **Configurable via web UI**: Change the name anytime from the interface
- **Persistent storage**: Name saved in NVS (non-volatile storage)
- **Instant updates**: mDNS restarts automatically when name changes
- **Cross-platform compatible**: Works on Windows 10+, macOS, Linux, iOS, Android

**Configuration:**
1. Access the web interface
2. Find the **"🏷️ Device Name (mDNS)"** section
3. Enter your desired name (alphanumeric, dash, underscore, max 32 chars)
4. Click **"Apply"**
5. Device immediately accessible at `http://[your-name].local`

**Validation:**
- Alphanumeric characters (a-z, A-Z, 0-9)
- Hyphens (-) and underscores (_) allowed
- Cannot start or end with a hyphen
- Maximum 32 characters
- Real-time validation in the web UI

---

## 🔧 Technical Implementation

### New Components

#### Configuration (`config.h`)
```cpp
#define DEFAULT_DEVICE_NAME "garland"  // Default mDNS name
#define MAX_DEVICE_NAME_LEN 32         // Maximum length
```

#### Functions Added
- `getDeviceName()` - Get current device name
- `setDeviceName(name)` - Set and validate new name
- `loadDeviceNameFromNVS()` - Load from persistent storage
- `saveDeviceNameToNVS()` - Save to persistent storage
- `isValidDeviceName(name)` - Validate name format

#### Web API Endpoints
- `GET /device_name` - Retrieve current device name
- `POST /device_name?name=X` - Set new device name

#### mDNS Integration
- Automatic service publication on startup
- HTTP service advertised on port 80
- Dynamic restart when name changes
- OTA hostname synchronized with mDNS name

---

## 📊 Updated Status API

The `/status` endpoint now includes the device name:

```json
{
  "animation": "Fade Alterne",
  "animation_id": 1,
  "mode": "Permanent",
  "mode_id": 0,
  "motion_detected": false,
  "auto_interval_ms": 30000,
  "motion_duration_ms": 30000,
  "matrix_animation": "Snowflakes",
  "matrix_animation_id": 0,
  "matrix_brightness": 15,
  "display_mode": "Animé",
  "display_mode_id": 0,
  "device_name": "garland",
  "ip": "192.168.1.100"
}
```

---

## 📝 Documentation Updates

### Updated Files
- ✅ `README.md` - Added mDNS section and updated access instructions
- ✅ `README_FR.md` - French version updated
- ✅ All source files - Version bumped to 1.12.0

### New Sections
- **"Web Interface and Network Access"** - Comprehensive guide
- **"Customizing the Device Name"** - Step-by-step instructions
- **"Accessing the Web Interface"** - Two methods documented

---

## 🔄 Breaking Changes

**None.** This release is fully backward compatible.

Existing devices will:
- Continue to work with IP addresses
- Use default name "garland" until customized
- Preserve all previous settings

---

## 🐛 Bug Fixes

- None in this release (focused on new feature)

---

## 📦 Full Changelog

### Added
- mDNS support with `ESPmDNS.h`
- Device name configuration in `config.h`
- Device name persistence in NVS
- Device name validation function
- Web UI section for device name configuration
- JavaScript validation and preview
- New API endpoints for device name management
- mDNS name displayed in WiFi info section
- Comprehensive documentation updates

### Changed
- Version bumped to 1.12.0 across all files
- `main.cpp`: Added mDNS initialization
- `garland_control.cpp`: Added device name functions
- `web_interface.cpp`: Added handlers for device name
- `web_pages.cpp`: Added UI section for device name
- README sections restructured for better organization
- Startup logs now show mDNS name

### Improved
- Network accessibility (no more IP searching)
- User experience (memorable names)
- Documentation clarity

---

## 🚀 Upgrade Instructions

### From v1.11.x

1. **Upload new firmware** via USB or OTA
2. Device will use default name "garland" initially
3. **Optional**: Customize the name via web UI
4. All previous settings preserved

**No configuration changes required.**

---

## 🎓 Usage Examples

### Example 1: Home Decoration
```
Device Name: christmas-tree
Access URL: http://christmas-tree.local
```

### Example 2: Multiple Devices
```
Living Room: http://living-room-led.local
Bedroom:     http://bedroom-led.local
Kitchen:     http://kitchen-led.local
```

### Example 3: Event Setup
```
Main Stage:  http://stage-lights.local
Side Decor:  http://side-decor.local
```

---

## 🔮 Future Enhancements

Potential improvements for future releases:
- Multiple network interface support
- Custom DNS records
- Network discovery protocol
- Mobile app integration

---

## 📞 Support

For issues or questions:
- Open an issue on GitHub
- Check documentation in `docs/`
- Review troubleshooting guide

---

## 🙏 Acknowledgments

Thanks to the ESP32 community for mDNS libraries and documentation.

---

**Version History:**
- v1.12.0 (2026-01-06) - mDNS support
- v1.11.3 (2026-01-01) - Previous stable release

**Full release history available in** `CHANGELOG.md`
