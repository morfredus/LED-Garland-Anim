# Release v5.0.0 - Animated LCD Festive Redesign

## Highlights
- Animated LCD screen now mirrors the festive static look (textured background, ribbon frames, sparkles, twin garlands).
- Animation area is now a compact "Mini show" window to prioritize text and decorations while keeping smooth visuals.
- Info card enhanced: Mode, Garland animation, Matrix animation, SSID, and IP are grouped with colorful accents for instant readability.

## Changes
1. Rebuilt `displayMainScreen` with the festive visual language used by the static screen.
2. Shrunk the animation viewport and framed it as a mini stage; preserved all displayed data.
3. Synced documentation (README, USER_GUIDE) and added this release note.

## Files Touched
- src/display.cpp
- include/display.h
- platformio.ini
- CHANGELOG.md / CHANGELOG_FR.md
- README.md / README_FR.md
- docs/USER_GUIDE.md / docs/USER_GUIDE_FR.md

## Upgrade Notes
- Rebuild and upload as usual; no configuration changes required.
- Animated mode now presents a reduced animation window with richer surrounding information.
