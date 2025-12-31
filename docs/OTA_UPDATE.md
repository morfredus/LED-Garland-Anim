# OTA Update Process (ArduinoOTA)

This guide explains how to update the LED-Garland-Anim firmware over WiFi using ArduinoOTA.

---

## Prerequisites
- The ESP32 must be flashed at least once via USB with a firmware version >= 1.3.0 (OTA enabled)
- The device must be connected to the same WiFi network as your computer
- PlatformIO (VS Code) or Arduino IDE installed

---

## Step-by-Step OTA Update

1. **Power on the ESP32 and connect it to WiFi**
   - The device will display its IP address on the LCD (or check your router)

2. **Open PlatformIO or Arduino IDE**
   - In PlatformIO, select the environment (e.g. `esp32devkitc`)

3. **Select the OTA port**
   - In PlatformIO: The device should appear as `LED-Garland-Anim@<ip>` or `LED-Garland-Anim.local` in the upload ports list
   - In Arduino IDE: Select the network port corresponding to your device

4. **Upload the firmware**
   - Click the upload button as usual
   - The upload will proceed over WiFi
   - The device will reboot automatically after a successful update

---

## Troubleshooting
- If the device does not appear in the port list:
  - Ensure it is connected to WiFi
  - Check that your computer is on the same network
  - Try using the device's IP address instead of `.local`
- OTA is only available when WiFi is connected
- The first upload must always be done via USB

---

## Security Note
OTA is enabled by default and does not require a password. For production, consider setting a password with `ArduinoOTA.setPassword()` in the code.

---

For more details, see the official [ArduinoOTA documentation](https://github.com/esp8266/Arduino/blob/master/doc/ota_updates/ota_updates.md).
