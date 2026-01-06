# Release v3.0.2 – 2026-01-06

## Summary
- Cumulative notes covering changes from v1.11.3 through v3.0.2.
- Latest fix: ST7789 animation area now preserves the white border and cyan separator even when matrix info is displayed.

## Scope (delta vs v1.11.3)
- Versions included: 1.11.3, 1.11.4, 1.12.0, 1.12.1, 2.0.0, 3.0.0, 3.0.1, 3.0.2.
- Themes: TFT rendering fixes, web UI rebuild and reordering, mDNS support, matrix animation updates, performance tuning, and one hardware pin change.

## Highlights
### Display / TFT
- 3.0.2: `updateAnimationVisual` now receives the matrix flag from the main loop; the clear area matches the correct rectangle and no longer erases the border or cyan line.
- 3.0.1: Increased clear-rectangle margins so animation rendering cannot overwrite the 1-pixel border.
- 2.0.0: Screen-off handling clears pixels before backlight off; display mode selector moved into the Mode card.

### Web Interface
- 3.0.0: Card order changed and Mode card rebuilt into a three-zone layout; matrix brightness control moved into the Mode card.
- 2.0.0: Full UI modernization with instant apply (no page reload), sliders for all intervals/brightness, consolidated system and network info.
- 1.11.4: Dashboard page rebuilt to restore missing controls; header cleanup and include ordering fixes.

### Network / Access
- 1.12.0: Added mDNS with configurable device name stored in NVS; status and UI now expose http://[name].local access.

### Matrix and Animations
- 1.11.3: Matrix Rain redesigned to use the full 8x8 area; Clock redrawn for clarity and readability.
- 1.11.4: Added display mode name helper and corrected display-mode handler parameter naming.

### Performance / Responsiveness
- 1.12.1: Throttled matrix refresh (>=15 ms), garland engine (>=10 ms), and ST7789 refresh (200 ms) to reduce loop load without altering visuals.

### Hardware
- 1.11.4: NeoPixel 8x8 data pin moved from GPIO 13 to GPIO 34. Rewire before flashing any firmware newer than 1.11.3.

## Upgrade Notes from v1.11.3
1. Move the matrix data wire to GPIO 34 (mandatory hardware change).
2. Flash v3.0.2 firmware (USB or OTA).
3. Optionally configure a device name in the web UI to use mDNS access.
4. Re-familiarize yourself with the new web UI card order and Mode card layout introduced in 2.0.0/3.0.0.
5. Verify on TFT that the animation border and cyan separator remain visible during animations with and without matrix info.

## Build
- Target: esp32devkitc
- Status: success
- RAM: ~15.8% (about 51,700 bytes of 327,680)
- Flash: ~81.3% (about 1,065,800 bytes of 1,310,720)

## SEMVER
- Latest release: 3.0.2 (PATCH)
- Breaking changes since 1.11.3: hardware pin remap (1.11.4), major web UI reorganizations (2.0.0 and 3.0.0).
