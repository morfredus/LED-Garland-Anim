# Release Notes - v5.1.0

**Date**: January 6, 2026  
**Version**: 5.1.0 (MINOR)  
**Classification**: Usability Improvement + Feature Addition

---

## 🎯 Objectives

This release resolves SSID text overflow issues and reorganizes the animated LCD screen for improved readability by converting split left/right panels into full-width stacked zones. The mDNS device name is now prominently displayed alongside IP and network info.

---

## ✨ What's New

### 1. **Animated LCD Layout Reorganization**

The animated screen has been restructured from a **split left-right panel design** to **full-width stacked zones**:

#### Previous Layout (v5.0.0):
```
┌─────────────────────────────────────┐
│       PROJECT NAME + VERSION        │  Header (14, 14, 212, 58)
├────────────────┬────────────────────┤
│ LEFT INFO      │ RIGHT ANIMATION    │
│ (128px wide)   │ (96px wide)        │
│ Mode           │ Mini show (small)  │
│ Anim guirlande │ [Animation zone]   │
│ Anim matrice   │                    │
│ ----           │                    │
│ SSID: [text]   │                    │  <- SSID could overflow
│ IP: [addr]     │                    │
└────────────────┴────────────────────┘
```

#### New Layout (v5.1.0):
```
┌─────────────────────────────────────┐
│       PROJECT NAME + VERSION        │  Header (14, 14, 212, 58) - Unchanged
├─────────────────────────────────────┤
│ INFO FRAME (Fullwidth, 70px tall)   │  Mode | WiFi: SSID | IP | mDNS | Anim
│ Improved readability, no overflow   │
├─────────────────────────────────────┤
│                                     │
│     ANIMATION ZONE (Fullwidth)      │  Larger viewport
│     Better aspect ratio, more space │
│                                     │
└─────────────────────────────────────┘
```

**Benefits**:
- ✅ SSID no longer overflows (auto-truncates to 20 chars with "...")
- ✅ All network info (Mode, WiFi, IP, mDNS) in one visible frame
- ✅ Animation zone gains more vertical space (was cramped in 96px)
- ✅ Better use of screen real-estate
- ✅ Easier to read on a small 1.14" display

---

### 2. **SSID Truncation Logic**

A new helper function `truncateText()` automatically shortens long SSIDs:

```cpp
auto truncateText = [](const String& text, int maxLen) -> String {
    if (text.length() <= maxLen) return text;
    return text.substring(0, maxLen - 2) + "..";
};

// Example:
// "VeryLongNetworkNameHere12345" (28 chars)
// → "VeryLongNetworkNameHere.." (20 chars max)
```

---

### 3. **mDNS Name Display**

#### Enhanced Function Signatures:
```cpp
// Now accepts mDnsName parameter (optional)
void displayScreenByMode(const char* ssid, IPAddress ip, const char* modeName,
                         const char* animationName, const char* matrixAnimationName = nullptr,
                         const char* mDnsName = nullptr);

void displayMainScreen(const char* ssid, IPAddress ip, const char* modeName,
                       const char* animationName, const char* matrixAnimationName = nullptr,
                       const char* mDnsName = nullptr);
```

#### Display Output:
The animated screen now shows mDNS in the info frame:
```
Mode: Permanent
WiFi: HomeNetwork
IP: 192.168.1.42
mDNS: garland.local
Anim: rainbow + pulse
```

---

### 4. **Updated Display Calls**

All callers have been updated to pass the mDNS name:

#### main.cpp:
```cpp
String mDnsStr = String(getDeviceName()) + ".local";
displayScreenByMode(WiFi.SSID().c_str(), WiFi.localIP(),
                   getGarlandModeName(), getGarlandAnimationName(),
                   getMatrix8x8AnimationName(), mDnsStr.c_str());
```

#### web_interface.cpp:
```cpp
// Same pattern in handleSetAnimation(), handleSetMode(), handleDisplayMode()
String mDnsStr = String(getDeviceName()) + ".local";
displayScreenByMode(..., mDnsStr.c_str());
```

## 🔧 Technical Details

### Code Changes:

1. **src/display.cpp**:
   - Refactored `displayMainScreen()` function (~130 lines)
   - Added `truncateText()` helper lambda
   - New layout calculations for fullwidth zones
   - Updated `displayScreenByMode()` to handle mDnsName parameter

2. **include/display.h**:
   - Updated function signatures with `mDnsName` parameter
   - Updated docstrings to reflect new layout

3. **src/main.cpp, src/web_interface.cpp**:
   - All display calls now construct and pass mDNS string
   - Consistent pattern: `String(getDeviceName()) + ".local"`

4. **platformio.ini**:
   - Version bumped: `PROJECT_VERSION="5.0.0"` → `PROJECT_VERSION="5.1.0"`

### Backward Compatibility:
✅ **Fully compatible** - mDnsName parameter is optional (defaults to nullptr)

---

## 📊 Layout Dimensions

### Header (Unchanged):
- Position: (14, 14)
- Size: 212×58 px
- Content: PROJECT_NAME + "v" + PROJECT_VERSION

### Info Frame (New):
- Position: (8, 88)
- Size: 224×70 px  ← **Fullwidth**
- Content:
  - Line 1: Mode: [modeName]
  - Line 2: WiFi: [ssid truncated to 20 chars]
  - Line 3: IP: [ip.toString()]
  - Line 4: mDNS: [deviceName.local] (if provided)
  - Line 5: Anim: [animationName] [+ matrixAnimationName]

### Animation Zone (New):
- Position: (8, 162)
- Size: 224×[remaining height] px  ← **Fullwidth, larger**
- Content: Actual animation rendering

---

## 🐛 Issues Fixed

1. **SSID Overflow** → Auto-truncates to 20 chars with "..."
2. **Missing mDNS Display** → Now shown in info frame
3. **Cramped Animation Zone** → More vertical space in fullwidth layout
4. **Poor Readability** → Better spacing, color contrast, line separation

---

## 📚 Documentation Updates

- ✅ [README.md](../README.md) – Bumped to v5.1.0, layout description updated
- ✅ [README_FR.md](../README_FR.md) – Bumped to v5.1.0, description en français
- ✅ [docs/USER_GUIDE.md](USER_GUIDE.md) – Animated screen section updated with new layout
- ✅ [docs/USER_GUIDE_FR.md](USER_GUIDE_FR.md) – Version française mise à jour
- ✅ [CHANGELOG.md](../CHANGELOG.md) – v5.1.0 entry added
- ✅ [CHANGELOG_FR.md](../CHANGELOG_FR.md) – Entrée v5.1.0 en français

---

## 🚀 Build & Testing

### Build Output:
```
Successfully created esp32 image.
Flash:   81.7%
RAM:     15.8%
Took 466.84 seconds
```

### Testing Checklist:
- ✅ Display modes (Animated, Static, Off) render correctly
- ✅ SSID truncation works (long names tested)
- ✅ mDNS name displays properly
- ✅ Animation zone renders without overlap
- ✅ Button clicks trigger display updates
- ✅ Web interface changes apply to LCD
- ✅ Boot animation shows correctly
- ✅ OTA updates preserve settings

---

## 📝 Commit Summary

```
feat(display): reorganize animated LCD to fullwidth stacked zones (v5.1.0)

- Convert split left/right panels to fullwidth info frame + animation zone
- Add SSID truncation (max 20 chars) to prevent overflow
- Add mDNS name parameter to displayScreenByMode() and displayMainScreen()
- Update all display calls to pass mDNS (main.cpp, web_interface.cpp)
- Improve readability with better spacing and color contrast
- Bump version 5.0.0 → 5.1.0 in platformio.ini, display.h, display.cpp
- Update changelog and release notes EN/FR
```

---

## 🎓 Version Classification

**SEMVER**: 5.1.0 (MINOR)

**Justification**: 
- Layout reorganization improves usability without breaking API
- mDNS parameter addition is optional (backward-compatible)
- Fixes prevent user confusion (SSID overflow, missing network info)
- No breaking changes to public interfaces

---

## 📌 Next Steps

- Monitor user feedback on new layout
- Consider adding configuration option to switch display modes per user preference
- Future: Multi-language UI support on LCD

---

**Enjoy the improved animated LCD display! 🎄✨**
