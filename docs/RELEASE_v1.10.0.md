# LED-Garland-Anim v1.10.0

**Release Date:** January 1, 2026

## 🎉 Major Release: Enhanced Animations + Flash-Free UI

Version 1.10.0 brings exciting new animations, a completely redesigned Stocking animation, and a critical UX improvement that eliminates all page reloads for a smooth, professional web experience.

---

## 🔥 What's New

### New Matrix Animations (2 Added)

#### 1. Campfire 🔥
Realistic fire simulation using heat propagation algorithm.
- **Features**: 64-cell heat map, upward/lateral heat diffusion
- **Visual**: Organic flames with red→orange→yellow→white gradient
- **Effect**: Natural flickering movement from bottom rows

#### 2. Radar 📡
Military-style green radar sweep with target blips.
- **Features**: 360° rotating sweep, fading trail, concentric grid
- **Visual**: Classic radar screen with smooth sweep animation
- **Effect**: Random appearing/fading target detection

### Animation Redesign

#### Stocking (Christmas) 🎄
Completely redrawn for better recognition and visual appeal.
- **Problem Solved**: Previous design was unrecognizable and unclear
- **New Design**: Clear stocking shape with:
  - White cuff at top
  - Red body with distinct leg and foot
  - Green decorative stripe
  - Gold twinkling sparkle
  - Gray hanging hook
  - Realistic pendulum swing animation
- **Result**: Now easily identifiable as festive Christmas stocking

---

## ✨ Critical UX Improvements

### Flash-Free Web Interface
**Problem:** Page reloads caused disruptive white flash when changing animations/modes.

**Solution:** Complete elimination of page reloads.
- Removed all `location.reload()` calls
- Implemented AJAX-only updates
- New JavaScript functions for dynamic DOM updates
- Instant visual feedback without page refresh

**Benefits:**
- ✅ No more white flash
- ✅ Smooth, professional transitions
- ✅ Instant confirmation messages
- ✅ Modern web app experience

---

## 📊 Complete Feature Set

### Total Animations
- **Garland**: 11 animations
- **Matrix**: 39 festive animations
  - Original: 11
  - Christmas: 10
  - New Year: 7
  - Easter: 4
  - Modern/Abstract: 7 (including new Campfire and Radar)

### Operating Modes
1. **Permanent**: Both always on
2. **Motion Detection - All**: Both triggered by motion
3. **Motion Detection - Garland Only**: Matrix always on, garland motion-triggered

### Web Interface Features
- Radio button grids (no dropdowns)
- Responsive 2-column layout (1 column on mobile)
- Instant selection (no "Apply" buttons)
- Flash-free updates (NEW in v1.10.0)
- Visual feedback with green highlights

---

## 🛠️ Technical Improvements

### Code Quality
- Clean animation implementations
- Efficient heat propagation algorithm (Campfire)
- Smooth rotation math (Radar)
- Redesigned pattern data (Stocking)

### UI/UX
- AJAX-based updates
- Dynamic DOM manipulation
- CSS class toggling for visual feedback
- No blocking page operations

### Documentation
- Complete EN/FR synchronization
- Comprehensive user guide
- Full version history
- Detailed animation descriptions

---

## 📦 Installation & Updates

### Web-Based OTA (Recommended)
1. Access device web interface
2. Click "OTA Update" button
3. Select firmware file: `.pio/build/esp32devkitc/firmware.bin`
4. Upload and wait for automatic reboot

### PlatformIO OTA
```bash
pio run -e esp32devkitc -t upload --upload-port <DEVICE_IP>
```

---

## 🔧 Compatibility

**Hardware:**
- ESP32 Classic (IdeaSpark/DevKitC)
- ST7789 1.14" LCD (135×240)
- TB6612FNG H-Bridge
- 8x8 NeoPixel WS2812B-64 Matrix (GPIO 32)
- Motion Sensor (PIR HC-SR501 or RCWL-0516 on GPIO 35)

**Software:**
- PlatformIO
- Arduino Framework for ESP32
- Adafruit NeoPixel Library

---

## 📚 Documentation

### Updated Guides
- **USER_GUIDE.md**: Complete usage guide with all 39 animations
- **RELEASE_NOTES.md**: Full version history
- **TROUBLESHOOTING.md**: Common issues and solutions
- **French Versions**: All docs synchronized (FR/EN)

### Quick Links
- [User Guide](docs/USER_GUIDE.md)
- [Release Notes](docs/RELEASE_NOTES.md)
- [OTA Update Guide](docs/OTA_UPDATE.md)
- [Troubleshooting](docs/TROUBLESHOOTING.md)

---

## 🎯 Upgrade Highlights

### From v1.9.0
- ✅ 2 new animations (Campfire, Radar)
- ✅ Redesigned Stocking animation
- ✅ No more page reloads (flash-free UI)
- ✅ Updated documentation

### From v1.8.x
- ✅ Radio button interface (v1.9.0)
- ✅ 2-column responsive layout (v1.9.0)
- ✅ 2 new animations + redesigned Stocking
- ✅ Flash-free experience

### From v1.7.x or earlier
- ✅ Modern web UI with radio buttons
- ✅ 39 matrix animations (vs 37 or fewer)
- ✅ 3 operating modes
- ✅ Flash-free updates
- ✅ Complete documentation

---

## 🐛 Known Issues

None at this time. Please report any issues on the project repository.

---

## 🙏 Thank You

Thank you for using LED-Garland-Anim! This v1.10.0 release brings:
- Beautiful new animations
- Smooth, professional UI
- Complete documentation
- Ready for production use

For questions, issues, or contributions, please visit the project repository.

---

**LED-Garland-Anim v1.10.0** - Modern LED Controller for ESP32 🎄✨

**Commits in this release:**
- feat: add Campfire/Radar animations, redesign Stocking, remove page reloads
- docs: update all documentation to v1.10.0 (EN/FR synchronization)

**Full Changelog**: See [CHANGELOG.md](CHANGELOG.md) and [CHANGELOG_FR.md](CHANGELOG_FR.md)
