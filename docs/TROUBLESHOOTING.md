## Configuration Not Saved or Restored

**Symptoms:**
- Settings (mode, animation, intervals) are lost after reboot or power cycle.

**Possible Causes:**
- NVS partition is corrupted or full
- ESP32 flash is defective
- Firmware bug (see logs for NVS errors)

**Solutions:**
- Erase flash and re-upload firmware
- Check for error messages on serial console
- If problem persists, file an issue with logs
# Troubleshooting - LED-Garland-Anim v1.2.1

Use this guide to debug the ESP32 IdeaSpark build when something does not work as expected.

## Quick Checklist
- Confirm you flashed the correct environment (`esp32devkitc`).
- Double-check WiFi credentials in `include/secrets.h`.
- Pins must match `include/board_config.h` (see PIN_MAPPING.md).
- Common ground between ESP32, TB6612FNG, and external power.
- Serial monitor at 115200 baud to read logs.

## WiFi / Network
- Stuck on "Connecting" or LED_BUILTIN stays blue: verify 2.4 GHz network, SSID/password, and that the router is not blocking new MACs.
- IP not shown: check router DHCP list; if none, reboot the board and router.
- Frequent drops: move closer to AP, avoid USB hubs with low power, and reduce metal shielding around the board.

## Web Interface Unreachable
- Ping the IP shown on LCD; if ping fails, recheck WiFi or DHCP.
- Clear browser cache or try incognito; ensure you use `http://<ip>` (not HTTPS).
- If only some endpoints fail, reboot to reset the internal web server.

## Buttons (Animation/Mode)
- BUTTON_1 GPIO16, BUTTON_2 GPIO17, BUTTON_BOOT on GPIO0.
- Buttons are active-low with internal pull-ups; ensure wiring goes to GND on press.
- If bouncy, inspect cabling length and switch quality; logs should show presses.

## Sensors
- MOTION_SENSOR_PIN: GPIO35. System auto-detects PIR (HC-SR501) or RCWL-0516. Verify module has 5V and GND. For PIR: adjust sensitivity and delay pots. For RCWL: check for interference or false triggers.
If motion always true, move the sensor away from heaters/sunlight (PIR) or sources of interference (RCWL); if never true, increase sensitivity (PIR) or check wiring (RCWL).

## Display
- LCD ST7789: verify all SPI lines plus BLK (backlight) are powered; reseat jumpers.
- For ghosting or random colors, lower cable length and check that GND is common.

## Garland Output / TB6612FNG
- TB6612_STBY must be HIGH (GPIO14).
- Direction: TB6612_AIN1/TB6612_AIN2 (GPIO25/33). Intensity: TB6612_PWMA (GPIO12).
- VM must be powered by an external 5–15V source; never power the garland from USB 5V alone.

---

**Document version: v1.2.1 (2025-12-31)**
