# OTA Update Process - LED-Garland-Anim v5.6.3

This guide explains how to update the LED-Garland-Anim firmware over WiFi using two different methods.

---

## Prerequisites
- The ESP32 must be flashed at least once via USB with a firmware version 1.11.0 (OTA enabled)
- The device must be connected to WiFi
- For method 1 (Web-based): Any web browser
- For method 2 (ArduinoOTA): PlatformIO (VS Code) or Arduino IDE

---

## Method 1: Web-Based OTA Update (v1.11.3+) ⭐

**The simplest and recommended method!**

### Step-by-Step

1. **Compile your firmware** with PlatformIO:
   ```bash
   pio run -e esp32devkitc
   ```

2. **Access the web interface**:
   - Go to `http://[ESP32_IP]` in your browser
   - The IP address is displayed on the OLED screen (if connected)

3. **Navigate to OTA update page**:
   - Click the **"⬆️ OTA Update"** button on the dashboard
   - Or directly access `http://[ESP32_IP]/update`

4. **Upload firmware**:
   - Click **"📁 Select .bin file"**
   - Navigate to `.pio/build/esp32devkitc/firmware.bin`
   - Click **"🚀 Start Update"** (requires double-click confirmation for safety)

5. **Monitor progress**:
   - Progress bar in the browser
   - Status messages (success/failure)
   - Status messages (success/failure)

6. **Automatic reboot**:
   - The ESP32 reboots automatically after a successful update
   - Wait for WiFi reconnection (~10 seconds)

### Advantages
- ✅ Intuitive graphical interface
- ✅ No PlatformIO commands needed
- ✅ Works from any device (PC, smartphone, tablet)
- ✅ Real-time progress display
- ✅ Automatic file validation (.bin extension required)
- ✅ Double-click confirmation prevents accidental updates

### Important Notes
- ⚠️ **Do not unplug or reset** the device during the update!
- ⚠️ Ensure stable WiFi connection
- ⚠️ Firmware file must have `.bin` extension
- ⚠️ Update takes 10-30 seconds depending on file size

---

## Method 2: OTA Update via ArduinoOTA (PlatformIO)

**Traditional method for developers who prefer command-line:**

### Step-by-Step

1. **Power on the ESP32 and connect it to WiFi**
   - The device will display its IP address on the OLED screen (or check your router)

2. **Open PlatformIO or Arduino IDE**
   - In PlatformIO, select the environment (e.g. `esp32devkitc`)

3. **Select the OTA port**
   - In PlatformIO: The device should appear as `LED-Garland-Anim@<ip>` or `LED-Garland-Anim.local` in the upload ports list
   - In Arduino IDE: Select the network port corresponding to your device

4. **Upload the firmware**
   - Click the upload button as usual, or use:
     ```bash
     pio run -e esp32devkitc -t upload --upload-port [ESP32_IP]
     ```
   - The upload will proceed over WiFi
   - The device will reboot automatically after a successful update

### Troubleshooting
- If the device does not appear in the port list:
  - Ensure it is connected to WiFi
  - Check that your computer is on the same network
  - Try using the device's IP address instead of `.local`
- OTA is only available when WiFi is connected
- The first upload must always be done via USB

---

## Comparison

| Feature | Web-based OTA | ArduinoOTA |
|---------|---------------|------------|
| **Ease of use** | ⭐⭐⭐⭐⭐ Very easy | ⭐⭐⭐ Moderate |
| **Required tools** | Web browser only | PlatformIO/Arduino IDE |
| **Visual progress** | ✅ Yes (browser + OLED) | ❌ No |
| **From any device** | ✅ Yes | ❌ No (only dev machine) |
| **Safety confirmation** | ✅ Double-click | ❌ No |
| **Best for** | End users, quick updates | Developers, automated builds |

---

## Security Note

OTA is enabled by default and does not require a password. For production environments, consider:
- Setting a password with `ArduinoOTA.setPassword()` in the code
- Restricting access to the web interface
- Using a separate WiFi network for IoT devices

---

## Version History

- **v1.11.3**: Added double-click confirmation for OTA updates
- **v1.11.3**: Added web-based OTA update interface
- **v1.11.3**: Added ArduinoOTA support

---

For more details on ArduinoOTA, see the official [ArduinoOTA documentation](https://github.com/esp8266/Arduino/blob/master/doc/ota_updates/ota_updates.md).

**Document version: v1.11.3 (2025-12-31)**
