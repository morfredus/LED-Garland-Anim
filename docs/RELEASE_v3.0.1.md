# Release v3.0.1 – 2026-01-06

## Summary
- Fixed TFT animation box: border and cyan separation line now stay visible while animations run.
- Root cause: `updateAnimationVisual()` erased too close to borders when clearing the area.
- Fix: increased clear margins from 1px to 2px to avoid overwriting the rectangle and separation line.

## Impact
- Visual bug fix only; no feature changes.
- UI rendering is now stable for all animations.

## Files Touched
- src/display.cpp (fillRect margins in `updateAnimationVisual()`)
- platformio.ini, include/config.h, include/display.h
- src/main.cpp, src/garland_control.cpp, src/matrix8x8_control.cpp
- include/web_styles.h, src/web_pages.cpp
- CHANGELOG.md / CHANGELOG_FR.md, README.md / README_FR.md, docs/RELEASE_v3.0.1.md

## Build
- Target: esp32devkitc
- Status: ✅ SUCCESS
- RAM: 15.8% (51,700 bytes of 327,680)
- Flash: 81.3% (1,065,837 bytes of 1,310,720)

## SEMVER
- Classification: PATCH (bug fix only)
- Breaking changes: None
