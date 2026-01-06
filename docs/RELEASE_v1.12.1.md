# Release v1.12.1 – 2026-01-06

## Summary
- Performance tuning to keep the loop responsive without changing features.
- Matrix 8x8 refresh throttled to minimum 15 ms.
- Garland animation engine throttled to minimum 10 ms.
- ST7789 animated screen refresh slowed to 200 ms (was 100 ms) to reduce SPI load.

## Impact
- No functional changes; visuals and features remain the same.
- Lower CPU usage, smoother UI and OTA responsiveness.

## Files Touched
- src/matrix8x8_control.cpp (matrix throttle)
- src/garland_control.cpp (garland throttle)
- src/main.cpp (ST7789 refresh interval)
- platformio.ini, README*, CHANGELOG*, docs/RELEASE_v1.12.1.md (version bump)

## Build
- Target: esp32devkitc
- Status: ✅ SUCCESS (same footprint ~81.4% flash, 15.8% RAM)

## SEMVER
- Classification: PATCH (performance tweaks only)
