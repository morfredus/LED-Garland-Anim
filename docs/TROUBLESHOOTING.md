# Troubleshooting - LED-Garland-Anim v5.6.5

*This document is valid from version 5.6.5.*

## Supported Boards

This project supports **two boards**:

| Board | Environment | Description |
|-------|-------------|-------------|
| **ESP32-S3 Super Mini** | `esp32s3_supermini` | Compact board, **default choice** |
| **ESP32 Wroom DevKit V1** | `esp32wroom` | Classic development board |

---

## Quick Checklist

Before troubleshooting, verify:

1. **Correct environment**: Flash the right PlatformIO environment for your board
   - ESP32-S3 Super Mini: `esp32s3_supermini`
   - ESP32 Wroom: `esp32wroom`
2. **WiFi credentials**: Check `include/secrets.h` (2.4 GHz network only)
3. **Pin wiring**: Match pins to your board (see tables below)
4. **Common ground**: ESP32, TB6612FNG, and external power must share GND
5. **Serial monitor**: Set baud rate to **115200** to read logs

---

## Pin Reference by Board

### ESP32-S3 Super Mini

| Function | GPIO |
|----------|------|
| I2C SDA | GPIO 4 |
| I2C SCL | GPIO 5 |
| TB6612 PWMA | GPIO 10 |
| TB6612 AIN1 | GPIO 11 |
| TB6612 AIN2 | GPIO 12 |
| TB6612 STBY | GPIO 13 |
| Matrix DATA | GPIO 7 |
| Motion Sensor | GPIO 2 |
| User Button | GPIO 8 |
| BOOT Button | GPIO 0 |

### ESP32 Wroom

| Function | GPIO |
|----------|------|
| I2C SDA | GPIO 21 |
| I2C SCL | GPIO 22 |
| TB6612 PWMA | GPIO 12 |
| TB6612 AIN1 | GPIO 25 |
| TB6612 AIN2 | GPIO 33 |
| TB6612 STBY | GPIO 14 |
| Matrix DATA | GPIO 27 |
| Motion Sensor | GPIO 35 |
| User Button | GPIO 16 |
| BOOT Button | GPIO 0 |

---

## WiFi / Network Issues

### WiFi Won't Connect

**Symptoms:**
- Stuck on "Connecting..." message
- LED stays on without blinking

**Solutions:**
1. **Verify 2.4 GHz network** - ESP32 does NOT support 5 GHz
2. **Check credentials** in `include/secrets.h` (SSID and password exactly as configured on router)
3. **Check router settings** - Some routers block new devices or have MAC filtering
4. **Move closer to router** - Weak signal causes connection failures
5. **Reboot both** ESP32 and router

### No IP Address Shown

**Solutions:**
1. Check router's DHCP client list
2. Reboot ESP32 and router
3. Verify WiFi credentials spelling

### Frequent Disconnections

**Solutions:**
1. Move ESP32 closer to access point
2. Avoid USB hubs with low power output
3. Reduce metal shielding around the board
4. Check for interference from other 2.4 GHz devices

---

## Web Interface Issues

### Web Interface Not Loading

**Solutions:**
1. **Ping the IP** shown on OLED or serial monitor
   ```
   ping 192.168.x.x
   ```
2. **Clear browser cache** or try incognito/private mode
3. **Use HTTP** not HTTPS: `http://192.168.x.x`
4. **Verify same network** - Your device must be on the same WiFi
5. **Try mDNS**: `http://garland.local`

### Some Pages Don't Work

**Solution:** Reboot ESP32 to reset internal web server

---

## Button Issues

### Buttons Don't Respond

**Button GPIO by board:**
- ESP32-S3 Super Mini: User Button = **GPIO 8**
- ESP32 Wroom: User Button = **GPIO 16**
- Both boards: BOOT Button = **GPIO 0**

**Button functions:**
- User Button: 1 click = next garland animation, 2 clicks = next matrix animation, long press = change mode
- BOOT Button: Long press = reboot

**Solutions:**
1. Check wiring goes to GND when pressed (buttons are active-low)
2. Verify internal pull-ups are enabled (default in firmware)
3. Test with multimeter for continuity
4. Check for proper grounding

---

## Motion Sensor Issues

### Sensor Always Triggered (False Positives)

**Motion Sensor GPIO by board:**
- ESP32-S3 Super Mini: **GPIO 2**
- ESP32 Wroom: **GPIO 35**

**For PIR (HC-SR501):**
1. Move away from heat sources (heaters, sunlight)
2. Reduce sensitivity (turn potentiometer counter-clockwise)
3. Check jumper is on "H" (repeating mode)

**For RCWL-0516 Radar:**
1. Move away from metal objects
2. Move away from power supplies and switching devices
3. Add shielding if interference persists

### Sensor Never Triggers

**For PIR:**
1. Increase sensitivity (turn potentiometer clockwise)
2. Check 5V power and GND connections
3. Wait 30-60 seconds for warm-up period

**For RCWL-0516:**
1. Check wiring (VCC, GND, OUT)
2. Verify OUT pin connects to correct GPIO
3. Test with multimeter for voltage change on movement

---

## Display Issues (OLED)

### OLED Screen Stays Black

**I2C pins by board:**
- ESP32-S3 Super Mini: SDA = **GPIO 4**, SCL = **GPIO 5**
- ESP32 Wroom: SDA = **GPIO 21**, SCL = **GPIO 22**

**Solutions:**
1. Check SDA/SCL wiring matches your board
2. Verify I2C address: usually **0x3C** or **0x3D**
3. Check 3.3V power supply
4. Verify common GND connection
5. Run I2C scan in serial logs at boot to detect devices

### Display Shows Garbage

1. Check I2C wiring (swap SDA/SCL if reversed)
2. Verify display is SSD1306 compatible
3. Check for proper ground connection

---

## Garland Issues (TB6612FNG)

### Garland Doesn't Light Up

**TB6612 pins by board:**

| Pin | ESP32-S3 Super Mini | ESP32 Wroom |
|-----|---------------------|-------------|
| PWMA | GPIO 10 | GPIO 12 |
| AIN1 | GPIO 11 | GPIO 25 |
| AIN2 | GPIO 12 | GPIO 33 |
| STBY | GPIO 13 | GPIO 14 |

**Solutions:**
1. **Check STBY pin** - Must be HIGH for motor driver to work
2. **Check VM power** - External 5-15V required (NOT from USB!)
3. **Check VCC** - 3.3V from ESP32
4. **Check GND** - Common ground with ESP32 and power supply
5. **Test garland separately** - Connect to 9V battery to verify it works
6. **Swap A01/A02** - Try reversing polarity

### Garland Only Lights in One Direction

1. Check AIN1 and AIN2 wiring
2. Verify both GPIO pins are correctly connected
3. Try different animation (e.g., "Blink Alternate")

---

## Matrix Issues (NeoPixel 8x8)

### Matrix Doesn't Light Up

**Matrix DATA pin by board:**
- ESP32-S3 Super Mini: **GPIO 7**
- ESP32 Wroom: **GPIO 27**

**Solutions:**
1. Check DATA pin wiring
2. Verify 5V power supply (external, not USB)
3. Check GND connection (common with ESP32)
4. Try lowering brightness first (high brightness needs more current)
5. Add 470 ohm resistor on DATA line (recommended)
6. Add 1000uF capacitor near matrix power input

### Matrix Shows Wrong Colors

1. Verify WS2812B chip type (not WS2811)
2. Check DATA pin connection
3. Verify proper grounding

---

## Configuration Issues

### Settings Not Saved After Reboot

**Symptoms:**
- Mode, animation, intervals reset to defaults after power cycle

**Causes:**
- NVS partition corrupted or full
- ESP32 flash defective
- Firmware bug

**Solutions:**
1. Erase flash completely and re-upload firmware:
   ```bash
   pio run -e esp32s3_supermini -t erase
   pio run -e esp32s3_supermini -t upload
   ```
2. Check serial console for NVS error messages
3. If problem persists, file an issue with logs

---

## Upload Issues

### Upload Fails - Port Not Found

**Solutions:**
1. Install USB driver for your board:
   - ESP32-S3 Super Mini: Usually no driver needed (USB CDC)
   - ESP32 Wroom: Install CP210x or CH340 driver
2. Try different USB cable (some are charge-only)
3. Try different USB port

### Upload Fails - Connection Error

**Solutions:**
1. Hold BOOT button while clicking Upload
2. Release BOOT when upload starts
3. Try lower upload speed in platformio.ini

### Permission Error (Linux)

```bash
sudo usermod -a -G dialout $USER
```
Then logout and login again.

---

## Still Having Issues?

1. **Check serial output** - Most errors are logged there
2. **Verify wiring** - Use the pin tables above for your specific board
3. **Start simple** - Test one component at a time
4. **Check power supply** - Inadequate power causes many issues
5. **File an issue** - Include logs and hardware details

---

**Document version: v5.6.5 (2026-02-02)**
