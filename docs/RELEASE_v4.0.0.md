# Release v4.0.0 – 2026-01-06

## Summary
- Major refresh of the ST7789 static screen into a festive, always-on dashboard.
- Static mode now shows Program name, Version, SSID, IP, and mDNS in a decorated frame.
- Documentation updated (EN/FR) to reflect the new LCD experience.

## Highlights
### LCD / ST7789
- Festive static dashboard with ribbon frame, sparkle corners, and dual garland separators.
- Connectivity card now keeps SSID, IP address, and mDNS (`*.local`) visible at all times.
- Non-wrapping labels to keep long SSIDs readable without clipping the decorations.

### Documentation
- README.md / README_FR.md: version bump to 4.0.0 and description of the new static screen.
- docs/USER_GUIDE.md / docs/USER_GUIDE_FR.md: LCD section updated with the festive dashboard details.
- Added bilingual release note: docs/RELEASE_v4.0.0.md and docs/RELEASE_v4.0.0_FR.md.

## Upgrade Notes
1. Flash firmware v4.0.0 (USB or OTA).
2. Set the LCD to **Static** mode to display the new festive dashboard.
3. Verify SSID, IP, and `http://<device-name>.local` are visible on the LCD.

## Build
- Target: esp32devkitc
- Status: not built in this change set (no code-generation steps required).

## SEMVER
- Latest release: 4.0.0 (MAJOR)
- Reason: Complete redesign of the LCD static screen with new displayed data (mDNS) and layout.
