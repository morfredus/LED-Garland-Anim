# Release Notes - v5.1.1

**Date**: January 7, 2026  
**Version**: 5.1.1 (PATCH)  
**Classification**: Critical Bug Fix

---

## 🎯 Summary

This patch release fixes a critical bug where the 8x8 matrix animation in AUTO mode was incorrectly using the garland's animation interval instead of its own. As of v5.1.1, the matrix and garland AUTO modes now operate independently with separate, configurable intervals.

---

## 🐛 Critical Bug Fixed

### Matrix AUTO Mode Using Wrong Interval (FIXED)

**Problem:**
- The 8x8 matrix animation in AUTO mode was using `getAutoAnimationIntervalMs()` (garland interval)
- This meant the matrix could not have its own independent animation cycle duration
- Users could not set different animation speeds for garland and matrix

**Root Cause:**
- Line 2019 in `src/matrix8x8_control.cpp` in the `updateMatrix8x8()` function was calling the wrong getter function
- Misleading code comment indicated the intervals were intentionally shared

**Solution:**
- Changed line 2019 to use `getMatrix8x8AnimationIntervalMs()` instead of `getAutoAnimationIntervalMs()`
- Updated documentation to clarify that intervals are now independent
- Removed misleading comment about shared intervals

**Impact:**
- ✅ Matrix AUTO mode now respects the "Matrix Animation Interval" setting
- ✅ Garland AUTO mode continues to use "Auto Mode Interval" setting
- ✅ Both can run simultaneously at different speeds
- ✅ Each interval is independently saved and restored on restart
- ✅ **Fully backward-compatible**: Web API unchanged, existing settings preserved

---

## 🔧 Technical Details

### Code Changes

**File**: `src/matrix8x8_control.cpp`

**Before:**
```cpp
// Line 21 (removed)
// NOTE: Auto mode interval is shared with garland - uses getAutoAnimationIntervalMs()

// Line 2019
unsigned long interval = getAutoAnimationIntervalMs();  // Shared with garland
```

**After:**
```cpp
// Line 23 (updated)
// Matrix animation interval (independent from garland)

// Line 2019
unsigned long interval = getMatrix8x8AnimationIntervalMs();  // Matrix-specific interval
```

### Persistence Verification

- **Load**: `loadMatrix8x8Settings()` correctly restores saved interval from NVS
- **Save**: `setMatrix8x8AnimationIntervalMs()` correctly saves interval to NVS
- **Restore**: Matrix interval survives device reboots independently

### Version Updates

All file headers updated to v5.1.1 (2026-01-07):
- `include/config.h`
- `include/matrix8x8_control.h`
- `src/matrix8x8_control.cpp`
- `src/main.cpp`
- `include/garland_control.h`

---

## 📚 Documentation Updates

### User Guides
- **docs/USER_GUIDE.md**: Updated to v5.1.1, added section "⚠️ Important: Garland & Matrix Auto Modes Are Independent"
- **docs/USER_GUIDE_FR.md**: Updated to v5.1.1, added French translation of independence notice

### Changelogs
- **CHANGELOG.md**: Added v5.1.1 entry with detailed fix description
- **CHANGELOG_FR.md**: Added v5.1.1 entry with French description

### NVS Persistence Documentation
Updated to clearly indicate that both garland and matrix intervals are saved independently:
- Garland: "Auto Mode Interval"
- Matrix: "Matrix Animation Interval"

---

## ✅ Validation Checklist

- ✅ Matrix AUTO mode now uses independent interval from web UI setting
- ✅ Garland AUTO mode continues to use its own interval (unchanged)
- ✅ Matrix interval is correctly saved to NVS when changed
- ✅ Matrix interval is correctly restored on device startup
- ✅ Both intervals can have different values simultaneously
- ✅ No API breaking changes
- ✅ All file versions updated to 5.1.1
- ✅ Both changelogs updated (EN + FR)
- ✅ Both user guides updated with independence notice (EN + FR)

---

## 📋 Commits and Changes Summary

### Files Modified:
1. `src/matrix8x8_control.cpp` - Core fix (line 2019 and comment cleanup)
2. `include/config.h` - Version bump to 5.1.1
3. `include/matrix8x8_control.h` - Version bump to 5.1.1
4. `src/main.cpp` - Version bump to 5.1.1
5. `include/garland_control.h` - Version bump to 5.1.1
6. `CHANGELOG.md` - Added v5.1.1 entry
7. `CHANGELOG_FR.md` - Added v5.1.1 entry
8. `docs/USER_GUIDE.md` - Updated version and added independence notice
9. `docs/USER_GUIDE_FR.md` - Updated version and added independence notice (French)

### Files Created:
- `docs/RELEASE_v5.1.1.md` (this file)
- `docs/RELEASE_v5.1.1_FR.md` (French version)

---

## 🎉 For Users

If you're using v5.1.0 or earlier:

1. **Update to v5.1.1** using OTA or serial upload
2. **Check the Web Interface**: You'll now see two separate interval settings:
   - "Auto Mode Interval" (Garland in AUTO mode)
   - "Matrix Animation Interval" (Matrix in AUTO mode)
3. **Customize independently**: Set different speeds for each device as desired
4. **Settings persist**: Your new intervals will survive reboots

---

## 📊 SEMVER Classification

**Type**: PATCH (5.1.0 → 5.1.1)

**Rationale**:
- Fixes critical bug (matrix interval independence)
- No new features added
- No breaking API changes
- Fully backward-compatible
- Existing configuration preserved

---

## 🔗 Related Resources

- [CHANGELOG.md](CHANGELOG.md) - Full changelog
- [USER_GUIDE.md](USER_GUIDE.md) - Updated user guide
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) - Troubleshooting help
- [GitHub Repository](https://github.com/morfredus/LED-Garland-Anim.git)
