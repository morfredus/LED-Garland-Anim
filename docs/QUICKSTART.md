
# 🚀 Quick Start Guide - LED-Garland-Anim v5.6.0

*This document is valid from version 5.6.0.*


## Supported Platforms
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32 Wroom
- ESP32-C3 HW-675
- ESP32-S3 Mini (esp32s3_mini)

> 📌 **OLED SSD1306 (I2C) display is supported on all platforms if connected to SDA/SCL**


**Goal**: Get your LED garland animating in 5 minutes!
**OLED SSD1306 (I2C) display is supported on all platforms if connected (SDA=GPIO4, SCL=GPIO5 by default).**

This guide assumes you have zero ESP32 experience. Follow these steps in order.

---

## ⏱️ Prerequisites (5 minutes)

### 1. Install Software

**Windows / macOS / Linux:**

1. **Install VS Code**: https://code.visualstudio.com/
2. **Install PlatformIO extension**:
   - Open VS Code
   - Click Extensions icon (left sidebar)
   - Search "PlatformIO IDE"
   - Click "Install"
   - Wait for installation to complete (may take 2-3 minutes)
   - Restart VS Code when prompted

3. **Install Git** (if not already installed):
   - Windows: https://git-scm.com/download/win
   - macOS: Open Terminal, type `git --version` (will prompt to install if needed)
   - Linux: `sudo apt install git` (Ubuntu/Debian)


### 2. Required Hardware Checklist

✅ ESP32 board (IdeaSpark, DevKitC, Wroom, HW-675, S3 Mini)  
✅ USB cable (micro-USB or USB-C, depending on board)  
✅ TB6612FNG motor driver module  
✅ 2-wire LED garland (anti-parallel LEDs)  
✅ 8x8 WS2812B NeoPixel matrix  
✅ PIR sensor (HC-SR501) or RCWL-0516 radar  
✅ OLED SSD1306 (I2C) display (optional but supported on all platforms, SDA=GPIO4, SCL=GPIO5 by default)  
✅ External 5V power supply (2A minimum)  
✅ Breadboard and jumper wires  

**Don't have all components yet?** See [HARDWARE_GUIDE.md](HARDWARE_GUIDE.md) for shopping list with links.

---

## 📥 Step 1: Download Project (2 minutes)

1. Open VS Code
2. Press `Ctrl+Shift+P` (Windows/Linux) or `Cmd+Shift+P` (macOS)
3. Type "Git: Clone" and press Enter
4. Paste repository URL: `https://github.com/[your-username]/LED-Garland-Anim`
5. Choose a folder location (e.g., `Documents/PlatformIO/`)
6. Click "Open" when prompted

**Alternative (command line):**
```bash
cd ~/Documents/PlatformIO
git clone https://github.com/[your-username]/LED-Garland-Anim
cd LED-Garland-Anim
code .
```

---

## 🔌 Step 2: Wire Components (10 minutes)

### Quick Connection Diagram

**TB6612FNG → ESP32:**
```
PWMA  → GPIO 13
AIN1  → GPIO 26
AIN2  → GPIO 25
STBY  → GPIO 15
VCC   → 3.3V
GND   → GND
VM    → External 5V+ (NOT USB!)
```

**NeoPixel Matrix → ESP32:**
```
DIN   → GPIO 34
VCC   → External 5V+
GND   → GND (common ground with ESP32)
```

**PIR Sensor → ESP32:**
```
VCC   → 5V
OUT   → GPIO 35
GND   → GND
```

**LED Garland → TB6612FNG:**
```
A01   → Garland wire 1
A02   → Garland wire 2
```

⚠️ **CRITICAL**: 
- Connect external 5V power supply GND to ESP32 GND (common ground)
- Do NOT power garland or matrix from USB alone
- TB6612FNG VM must come from external power, not ESP32

📖 **Need detailed wiring?** See [PIN_MAPPING.md](PIN_MAPPING.md) with full schematics.

---

## ⚙️ Step 3: Configure WiFi (1 minute)

1. In VS Code, open `include/secrets.h`
2. Replace with your WiFi credentials:
   ```cpp
   #define WIFI_SSID "YourNetworkName"
   #define WIFI_PASSWORD "YourPassword"
   ```
3. Save file (`Ctrl+S` / `Cmd+S`)

⚠️ **Important**: ESP32 only supports 2.4 GHz WiFi networks, not 5 GHz!

---

## 📤 Step 4: Upload Firmware (3 minutes)

### First Upload (USB required)

1. Connect ESP32 to computer via USB cable
2. In VS Code bottom bar, click **"✓ Build"** (checkmark icon)
   - Wait for compilation (30-60 seconds)
   - Should see "SUCCESS" message
3. Click **"→ Upload"** (right arrow icon)
   - PlatformIO auto-detects COM port
   - Wait for upload (20-30 seconds)
4. Click **"🔌 Serial Monitor"** (plug icon)
   - Set baud rate to **115200**
   - Watch boot messages

**Troubleshooting upload:**
- "Port not found": Install CP210x or CH340 USB driver for your board
- "Failed to connect": Hold BOOT button while clicking Upload
- Permission error (Linux): `sudo usermod -a -G dialout $USER` then logout/login

### Verify Success

Serial monitor should show:
```
[WiFi] Connected to YourNetworkName
[WiFi] IP address: 192.168.x.x
[mDNS] Started as: garland.local
[Setup] Complete! Ready.
```

---

## 🌐 Step 5: Access Web Interface (1 minute)

### Method 1: Using mDNS (easiest)

Open browser and go to:
```
http://garland.local
```

### Method 2: Using IP Address

Use the IP address shown on the LCD or in serial monitor:
```
http://192.168.x.x
```

**Web interface not loading?**
- Verify ESP32 is powered on and connected to WiFi
- Check serial monitor for IP address
- Try pinging the device: `ping garland.local` or `ping 192.168.x.x`
- Clear browser cache or try incognito mode
- Make sure you're on the same WiFi network

---

## 🎉 Step 6: Test Animations (1 minute)

### On the Web Interface

1. **Test Garland**:
   - Go to "🎄 Animations Guirlande" section
   - Click "Fade Alternate" button
   - Garland should start animating!

2. **Test Matrix**:
   - Go to "🎨 Matrice 8x8" section
   - Click "Star" animation
   - Matrix should display animated star!

3. **Test Motion Detection**:
   - Go to "🎯 Mode de fonctionnement" section
   - Select "Détection mouvement"
   - Wave hand in front of PIR sensor
   - Both garland and matrix should activate!

### Physical Button Test

- **BUTTON_1 (GPIO 16)**: Change garland animation
- **BUTTON_2 (GPIO 17)**: Change operating mode
- **BOOT button**: Toggle matrix animation (built-in button)

---

## ✅ Success Checklist

You should now have:
- ✅ Garland animating with smooth transitions
- ✅ Matrix displaying colorful animations
- ✅ Web interface accessible at `http://garland.local`
- ✅ Motion detection triggering animations
- ✅ Physical buttons working
- ✅ LCD showing IP and status (if equipped)

---

## 🆘 Something Not Working?

### Common Issues

**WiFi won't connect:**
- Check SSID/password in `secrets.h`
- Verify 2.4 GHz network (not 5 GHz)
- Check router allows new devices

**Garland not lighting:**
- Check TB6612FNG STBY pin is HIGH (GPIO 15)
- Verify external power supply connected to VM
- Test garland polarity (try swapping A01/A02)

**Matrix not lighting:**
- Check GPIO 34 connection (DATA pin)
- Verify 5V power supply adequate (2A minimum)
- Test with lower brightness first

**Sensor not detecting:**
- PIR: Adjust sensitivity potentiometer (clockwise = more sensitive)
- RCWL: Move away from metal objects and power supplies
- Check GPIO 35 connection

📖 **Detailed troubleshooting**: See [TROUBLESHOOTING.md](TROUBLESHOOTING.md)

---

## 🎯 Next Steps

Now that everything works:

1. **Explore all animations**: 11 garland + 37 matrix animations available!
2. **Customize settings**: Adjust intervals, brightness, and modes in web interface
3. **Learn OTA updates**: Update firmware wirelessly (see [OTA_UPDATE.md](OTA_UPDATE.md))
4. **Read user guide**: Full feature documentation in [USER_GUIDE.md](USER_GUIDE.md)
5. **Adjust sensors**: Fine-tune PIR/RCWL settings (see [PIR_SENSOR_SETUP.md](PIR_SENSOR_SETUP.md))

---

## 📚 Additional Resources

- **Hardware Guide**: Component list with suppliers → [HARDWARE_GUIDE.md](HARDWARE_GUIDE.md)
- **Build Guide**: Detailed compilation instructions → [BUILD_GUIDE.md](BUILD_GUIDE.md)
- **Pin Mapping**: Complete wiring schematics → [PIN_MAPPING.md](PIN_MAPPING.md)
- **Architecture**: Code structure and modules → [ARCHITECTURE.md](ARCHITECTURE.md)
- **Changelog**: Version history → [CHANGELOG.md](../CHANGELOG.md)

---

**🎊 Congratulations!** You've successfully set up LED-Garland-Anim!

**Document version: v5.1.5 (2026-01-07)**
