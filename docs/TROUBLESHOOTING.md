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

# Troubleshooting - LED-Garland-Anim v5.6.3

Use this guide to debug any supported platform:
- **ESP32 Classic (IdeaSpark/DevKitC)**
- **ESP32 Wroom (DevKit V1)**
- **ESP32-S3 Mini (esp32s3_mini)**
- **ESP32-S3 Super Mini (esp32s3_supermini)**

## Quick Checklist
- Confirm you flashed the correct PlatformIO environment for your board (`esp32devkitc`, `esp32wroom`, `esp32s3_mini`, `esp32s3_supermini`).
- Double-check WiFi credentials in `include/secrets.h`.
- Pins must match `include/board_config.h` (see PIN_MAPPING.md).
- Common ground between ESP32, TB6612FNG, and external power.
- Serial monitor at 115200 baud to read logs.

## WiFi / Network
- Stuck on "Connecting" or LED_BUILTIN stays blue: verify 2.4 GHz network, SSID/password, and that the router is not blocking new MACs.
- IP not shown: check router DHCP list; if none, reboot the board and router.
- Frequent drops: move closer to AP, avoid USB hubs with low power, and reduce metal shielding around the board.

## Web Interface Unreachable
- Ping the IP shown on the OLED display; if ping fails, recheck WiFi or DHCP.
- Clear browser cache or try incognito; ensure you use `http://<ip>` (not HTTPS).
- If only some endpoints fail, reboot to reset the internal web server.

## Buttons (Animation/Mode)
- User button (BUTTON_1) and BOOT (GPIO0).
- User button: 1 click = next garland, 2 clicks = next matrix, long press = change mode.
- Buttons are active-low with internal pull-ups; ensure wiring goes to GND on press.

## Sensors
- MOTION_SENSOR_PIN: GPIO35. System auto-detects PIR (HC-SR501) or RCWL-0516. Verify module has 5V and GND. For PIR: adjust sensitivity and delay pots. For RCWL: check for interference or false triggers.
If motion always true, move the sensor away from heaters/sunlight (PIR) or sources of interference (RCWL); if never true, increase sensitivity (PIR) or check wiring (RCWL).

## Display
- OLED SSD1306 (I2C): verify SDA/SCL wiring, I2C address (0x3C/0x3D), and power.
- If the screen stays black, run the I2C scan logs on boot and check common GND.

## Garland Output / TB6612FNG
- TB6612_STBY must be HIGH (GPIO14).
- Direction: TB6612_AIN1/TB6612_AIN2 (GPIO25/33). Intensity: TB6612_PWMA (GPIO12).
- VM must be powered by an external 5–15V source; never power the garland from USB 5V alone.

---

**Document version: v5.6.3 (2026-02-01)**
