# 🛒 Hardware Guide - LED-Garland-Anim v5.1.2

Complete shopping list and component specifications for building the LED-Garland-Anim project.

---

## 📋 Complete Component List

### Essential Components

| Component | Quantity | Estimated Cost | Notes |
|-----------|----------|----------------|-------|
| ESP32 IdeaSpark or DevKitC | 1 | $8-15 | Must be ESP32 Classic (not S2/S3/C3) |
| TB6612FNG Module | 1 | $2-5 | Dual H-bridge motor driver |
| 2-wire LED Garland | 1 | $5-10 | Anti-parallel LEDs (~50 LEDs) |
| WS2812B 8x8 Matrix | 1 | $8-12 | 64 addressable RGB LEDs |
| PIR Sensor HC-SR501 | 1 | $2-4 | Motion detection |
| 5V Power Supply | 1 | $8-15 | 2A minimum, 3-5A recommended |
| Breadboard 830 points | 1 | $3-5 | For prototyping |
| Jumper Wires (M-M, M-F) | 1 set | $3-5 | 40pcs minimum |
| USB Cable | 1 | $2-5 | Match your ESP32 port (micro/Type-C) |

**Total Estimated Cost**: $40-75 USD

### Optional Components

| Component | Quantity | Cost | Purpose |
|-----------|----------|------|---------|
| RCWL-0516 Radar | 1 | $2-3 | Alternative to PIR (faster, more sensitive) |
| ST7789 Display 1.14" | 1 | $5-8 | Built-in on IdeaSpark, optional for DevKitC |
| DC Barrel Jack Adapter | 1 | $2-3 | For cleaner power connection |
| Capacitor 1000µF 16V | 1-2 | $1-2 | Power supply smoothing |
| Resistor 470Ω | 1 | $0.10 | Data line protection for NeoPixels |

---

## 🔍 Detailed Component Specifications

### 1. ESP32 Development Board

**Recommended Models:**

#### ESP32 IdeaSpark ⭐ (Recommended)
- **Features**: Built-in ST7789 1.14" LCD, USB-C, 4MB Flash
- **Advantages**: No external display needed, modern connector
- **Where to buy**: 
  - AliExpress: Search "ESP32 IdeaSpark ST7789"
  - Price: ~$12-15

#### ESP32 DevKitC (Alternative)
- **Features**: Standard 38-pin board, 4MB Flash, micro-USB
- **Advantages**: Widely available, well-documented
- **Where to buy**:
  - Amazon: Search "ESP32 DevKitC"
  - SparkFun: DEV-15663
  - Adafruit: Product ID 3269
- **Price**: ~$8-12

**Important**: Must be ESP32 "Classic" (Xtensa dual-core), NOT:
- ❌ ESP32-S2 (single core, different pinout)
- ❌ ESP32-S3 (different architecture)
- ❌ ESP32-C3 (RISC-V, incompatible)

### 2. TB6612FNG Motor Driver Module

**Specifications:**
- Input voltage (VM): 4.5V - 15V
- Output current: 1.2A per channel (3.2A peak)
- Logic voltage (VCC): 2.7V - 5.5V
- Standby control: Built-in
- Dual H-bridge: Independent direction control

**Where to buy:**
- Adafruit: Product ID 2448 (with headers)
- Amazon: Search "TB6612FNG breakout"
- SparkFun: ROB-14451
- AliExpress: ~$2 (bulk pricing)

**Price**: $2-5

**Why TB6612FNG?**
- Bidirectional LED control (forward/reverse)
- Higher current capacity than L298N
- PWM intensity control
- Compact size

### 3. 2-Wire LED Garland

**Specifications:**
- Type: Anti-parallel LED arrangement
- Wire count: 2 wires only (not 3-wire animated garlands)
- LED count: ~50-100 LEDs
- Voltage: Compatible with 5-12V
- Color: Warm white, cool white, or multicolor

**Identification:**
- ✅ Has only 2 wires
- ✅ LEDs light in alternating pattern when polarity reversed
- ✅ Often sold as "mini LED string lights"
- ❌ NOT pre-programmed animated garlands (those have 3+ wires)

**Where to buy:**
- Local hardware stores (seasonal, Christmas/holiday section)
- Amazon: Search "2 wire LED string lights 50 count"
- IKEA: "SÄRDAL" or similar LED strings
- Dollar stores (check wire count!)

**Price**: $5-10

**Test before buying**: Connect to 9V battery; reverse polarity should change which LEDs light up.

### 4. WS2812B 8x8 NeoPixel Matrix

**Specifications:**
- Type: WS2812B (integrated control chip)
- Configuration: 8x8 grid (64 LEDs)
- Voltage: 5V
- Current: ~60mA per LED at full white (3.84A max for full matrix)
- Data protocol: Single-wire serial
- Refresh rate: 400Hz - 800Hz

**Where to buy:**
- Adafruit: Product ID 1487 (NeoPixel NeoMatrix 8x8)
- Amazon: Search "WS2812B 8x8 matrix"
- BTF-LIGHTING (reliable brand on Amazon)
- AliExpress: Search "WS2812 8x8 flexible panel"

**Price**: $8-12

**Important notes:**
- Verify 8x8 configuration (some matrices are 16x16 or different sizes)
- Check if panel is flexible or rigid PCB (both work)
- Ensure WS2812B chips (some panels use WS2811 which requires different library)

### 5. Motion Sensors

#### PIR Sensor HC-SR501 (Standard option)

**Specifications:**
- Detection range: 3-7 meters
- Detection angle: ~120°
- Operating voltage: 5V
- Output: 3.3V HIGH when motion detected
- Adjustable sensitivity (potentiometer Sx)
- Adjustable time delay (potentiometer Tx)
- Trigger modes: Single / Repeat (jumper)

**Where to buy:**
- Adafruit: Product ID 189
- Amazon: Search "HC-SR501 PIR sensor"
- SparkFun: SEN-13285

**Price**: $2-4

**Advantages**: 
- Low cost
- Easy to adjust
- Low false positive rate

**Disadvantages**:
- Slower response (~2 seconds)
- Affected by temperature changes

#### RCWL-0516 Doppler Radar (Advanced option)

**Specifications:**
- Detection range: 5-9 meters
- Detection angle: ~120°
- Operating voltage: 4-28V (3.3V/5V compatible)
- Output: 3.3V HIGH when motion detected
- Microwave frequency: 3.18 GHz
- No moving parts

**Where to buy:**
- Amazon: Search "RCWL-0516 radar sensor"
- AliExpress: Search "RCWL-0516"

**Price**: $2-3

**Advantages**:
- Very fast response (<100ms)
- Detects through thin walls/materials
- Not affected by temperature

**Disadvantages**:
- Higher false positive rate
- More sensitive to interference
- No built-in sensitivity adjustment

### 6. Power Supply

**Specifications:**
- Voltage: 5V DC (regulated)
- Current: 
  - Minimum: 2A (basic operation)
  - Recommended: 3A (safe margin)
  - Ideal: 5A (full brightness capability)
- Connector: Barrel jack (5.5mm x 2.1mm) or USB-C
- Certification: UL/CE certified recommended

**Current breakdown:**
- ESP32: ~0.5A peak (WiFi active)
- TB6612FNG: ~1A (garland at full brightness)
- WS2812B Matrix: ~3.8A (all 64 LEDs full white)
- PIR Sensor: ~50mA
- Total maximum: ~5.35A

**Where to buy:**
- Amazon: Search "5V 5A power supply DC"
- Adafruit: Product ID 1995 (5V 4A)
- Mean Well brand (industrial quality)

**Price**: $8-15

**Important safety notes:**
- ⚠️ Do NOT use cheap/uncertified power supplies
- ⚠️ Ensure proper polarity (center-positive for barrel jacks)
- ⚠️ Never exceed rated current
- ✅ Add 1000µF capacitor near matrix for stability

### 7. Breadboard and Wiring

**Breadboard:**
- Size: 830 tie-points (standard size)
- Features: Power rails on both sides
- Optional: Breadboard power supply module (MB102)

**Jumper Wires:**
- Male-to-Male: 20pcs minimum
- Male-to-Female: 20pcs minimum
- Length: 10cm-20cm variety pack
- Quality: Dupont connectors, 22AWG wire

**Where to buy:**
- Amazon: "Electronics component kit" (usually includes both)
- Adafruit: Breadboard ID 239, Wires ID 758/826
- SparkFun: Breadboard PRT-12002

**Price**: $5-10 for both

### 8. USB Cable

**Specifications:**
- Type: Match your ESP32 board
  - Micro-USB (most DevKitC boards)
  - USB-C (IdeaSpark, newer boards)
- Features: Data transfer capable (not charge-only!)
- Length: 1-2 meters recommended

**Where to buy:**
- Amazon: Search "[micro-USB|USB-C] data cable"
- Included with many ESP32 boards

**Price**: $2-5

**Test**: Cable must support data transfer, not just charging. Verify by connecting any USB device that requires data sync.

---

## 🌍 Recommended Suppliers by Region

### United States
- **Adafruit**: Premium quality, excellent documentation, US shipping
- **SparkFun**: High-quality components, good tutorials
- **Amazon**: Fast Prime shipping, wide selection
- **Digi-Key / Mouser**: Electronic components, wholesale pricing

### Europe
- **Pimoroni** (UK): Adafruit distributor, EU shipping
- **Berrybase** (Germany): ESP32 and sensors
- **Amazon**: Country-specific (Amazon.de, .fr, .co.uk)
- **AliExpress**: Longer shipping, lower prices

### Asia
- **Taobao** (China): Domestic component sourcing
- **AliExpress** (International): Global shipping from China
- **Shopee** (Southeast Asia): Regional marketplace

### Budget-Friendly Options
- **AliExpress**: Lowest prices, 2-4 week shipping
- **Banggood**: Competitive pricing, electronics focus
- **eBay**: Mix of local and international sellers

---

## 🛠️ Tools Required

### Essential Tools
- Wire strippers (22-24 AWG)
- Diagonal cutters
- Computer with USB port (Windows/Mac/Linux)

### Helpful Tools
- Multimeter (voltage/continuity testing)
- Soldering iron (optional, for permanent connections)
- Hot glue gun (cable strain relief)
- Label maker (wire identification)

---

## 📦 Pre-Made Kits

Some suppliers offer LED-Garland-Anim compatible kits:

### DIY Kit (if available)
- ESP32 board
- TB6612FNG module
- WS2812B matrix
- PIR sensor
- Breadboard & wires
- Power supply

**Advantages**: 
- All components guaranteed compatible
- Usually includes documentation
- Single-source purchasing

**Disadvantages**:
- Higher total cost
- Less flexibility in component choice

**Search terms**: 
- "ESP32 LED matrix animation kit"
- "ESP32 WS2812B starter kit"

---

## ✅ Component Checklist

Before starting your build, verify you have:

### Must-Have (Required for basic operation)
- [ ] ESP32 board (IdeaSpark or DevKitC)
- [ ] TB6612FNG motor driver module
- [ ] 2-wire LED garland
- [ ] WS2812B 8x8 matrix
- [ ] PIR sensor HC-SR501 or RCWL-0516
- [ ] 5V power supply (2A minimum)
- [ ] Breadboard
- [ ] Jumper wires (M-M and M-F)
- [ ] USB cable (matching your ESP32)

### Nice-to-Have (Improves stability/usability)
- [ ] Capacitor 1000µF 16V (power smoothing)
- [ ] Resistor 470Ω (NeoPixel data line)
- [ ] Barrel jack adapter
- [ ] Multimeter
- [ ] Wire strippers

### Optional (Enhances project)
- [ ] ST7789 display (if using DevKitC)
- [ ] RCWL-0516 radar sensor (alternative to PIR)
- [ ] Enclosure/project box
- [ ] Heatsinks for TB6612FNG
- [ ] LED diffusers for matrix

---

## 🆘 Purchasing Help

### Common Questions

**Q: Can I use a 3A power supply instead of 5A?**  
A: Yes, but you'll need to limit matrix brightness to ~60% to avoid overload.

**Q: Will ESP32-S2/S3 work with this project?**  
A: No, this firmware is specifically for ESP32 "Classic" (original dual-core model).

**Q: Can I use a different motor driver instead of TB6612FNG?**  
A: L298N works but is less efficient and larger. L9110S works for low-power garlands. TB6612FNG is optimal.

**Q: My LED garland has 3 wires, will it work?**  
A: No, 3-wire garlands are pre-programmed animated lights with built-in controllers. You need simple 2-wire anti-parallel garlands.

**Q: Can I power everything from USB?**  
A: No, USB provides only 500mA-2A. The matrix alone can draw 3.8A at full brightness. Always use external 5V supply.

---

## 📞 Support

- **Component compatibility questions**: Open an issue on GitHub
- **Purchasing help**: See [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- **Alternative suppliers**: Check project discussions

---

## 📚 Related Guides

- **Quick Start**: First-time setup → [QUICKSTART.md](QUICKSTART.md)
- **Wiring Guide**: Connection diagrams → [PIN_MAPPING.md](PIN_MAPPING.md)
- **Build Guide**: Compilation instructions → [BUILD_GUIDE.md](BUILD_GUIDE.md)
- **User Guide**: Full feature documentation → [USER_GUIDE.md](USER_GUIDE.md)

---

**Document version: v5.1.2 (2026-01-07)**
