# Troubleshooting - LED-Garland-Anim v0.6.3

Use this guide to debug the ESP32-S3 and ESP32 Classic builds when something does not work as expected.

## Quick Checklist
- Confirm you flashed the correct environment (`esp32s3_n16r8`, `esp32s3_n8r8`, or `esp32devkitc`).
- Double-check WiFi credentials and Telegram token/chat in `include/secrets.h`.
- Pins must match `include/board_config.h` (S3: PIR 14, LDR 15, buttons 16/17; Classic: PIR 35, LDR 34, buttons 4/16).
- Common ground between ESP32, TB6612FNG, and external power.
- Serial monitor at 115200 baud to read logs.

## WiFi / Network
- Stuck on "Connecting" or WiFi LED stays purple: verify 2.4 GHz network, SSID/password, and that the router is not blocking new MACs.
- IP not shown: check router DHCP list; if none, reboot the board and router.
- Frequent drops: move closer to AP, avoid USB hubs with low power, and reduce metal shielding around the board.

## Telegram Bot
- No replies: ensure `TELEGRAM_BOT_TOKEN` and `TELEGRAM_CHAT_ID` are set and match the authorized chat.
- TLS errors: keep `client.setInsecure()` in place; verify system time (set by WiFi) is obtained before polling.
- Bot silent after reboot: confirm the device is on WiFi (check OLED/TFT IP); send `/status` to verify reachability.

## Web Interface Unreachable
- Ping the IP shown on OLED/TFT; if ping fails, recheck WiFi or DHCP.
- Clear browser cache or try incognito; ensure you use `http://<ip>` (not HTTPS).
- If only some endpoints fail, reboot to reset the internal web server.

## Buttons (Animation/Mode)
- S3: BTN1 GPIO16, BTN2 GPIO17. Classic: BTN1 GPIO4, BTN2 GPIO16. BOOT on GPIO0.
- Buttons are active-low with internal pull-ups; ensure wiring goes to GND on press.
- If bouncy, inspect cabling length and switch quality; logs should show presses.

## Sensors
- PIR: S3 GPIO14; Classic GPIO35. Verify module has 5V and GND, adjust sensitivity and delay pots.
- LDR: S3 GPIO15; Classic GPIO34. Check the 10kΩ voltage divider wiring and that ADC pin reads 0–4095.
- If motion always true, move the PIR away from heaters/sunlight; if never true, increase sensitivity.

## Displays
- OLED (I2C 0x3C/0x3D): SDA/SCL per board_config, pull-ups usually on the module. Swap SDA/SCL if screen is blank.
- TFT (ST7789 on S3 / ILI9341 on Classic): verify all SPI lines plus BL (backlight) are powered; reseat jumpers.
- For ghosting or random colors, lower cable length and check that GND is common.

## Garland Output / TB6612FNG
- STBY must be HIGH (GPIO8 on S3, GPIO14 on Classic).
- Direction: AIN1/AIN2 (GPIO6/4 on S3, GPIO32/33 on Classic). Intensity: PWMA (GPIO5 on S3, GPIO12 on Classic).
- VM must be powered by an external 5–15V source; never power the garland from USB 5V alone.
- If one direction fails, swap AO1/AO2 to confirm wiring; check for cold solder joints.

## Telegram and WiFi Status Messages Missing
- Ensure WiFi connected before Telegram init (see serial logs for "Connected to").
- Chat must match `TELEGRAM_CHAT_ID`; other chats are ignored silently.

## Build / Upload Problems
- Use `pio run -e <env>` for build; if upload fails, hold BOOT (GPIO0) on Classic during first flash.
- Delete `.pio` build cache if you changed frameworks drastically.

If issues persist, capture serial logs from boot to the failure point and compare against the pin tables in `docs/PIN_MAPPING*.md`.
