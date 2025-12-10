# 📚 Architecture - LED-Garland-Anim v0.2.0

## 🎯 Overview

The LED-Garland-Anim project uses a modular architecture for controlling a bi-directional LED garland with:
- **Web Interface**: Remote control and configuration
- **Local Display**: OLED/TFT with real-time information
- **Physical Control**: Buttons for animation/mode changes
- **Smart Modes**: Automatic management based on sensors/schedules
- **TB6612FNG Module**: Bi-directional garland control

## Modular Structure

### 1. Garland Control Module (`garland_control.h/cpp`)

**Responsibility**: Animation and operating mode management

```cpp
#include "garland_control.h"

// Main functions:
void setupGarland();                           // Initialization
void updateGarland();                          // Update (called in loop)
void setGarlandAnimation(GarlandAnimation);    // Change animation
void setGarlandMode(GarlandMode);              // Change mode
const char* getGarlandAnimationName();         // Current animation name
const char* getGarlandModeName();              // Current mode name
```

**Animations (14 types)**:
- `ANIM_FADE`, `ANIM_BLINK`, `ANIM_WAVE`, `ANIM_STROBE`, `ANIM_PULSE`
- `ANIM_CHASE`, `ANIM_HEARTBEAT`, `ANIM_SPARKLE`, `ANIM_RAINBOW`
- `ANIM_BREATHING`, `ANIM_FIRE`, `ANIM_TWINKLE`, `ANIM_METEOR`, `ANIM_AUTO`

**Modes (4 types)**:
- `MODE_PERMANENT`: Always on
- `MODE_SCHEDULED`: Based on configured schedules
- `MODE_MOTION_TRIGGER`: Activation by PIR sensor
- `MODE_NIGHT_OFF`: Shutdown based on LDR brightness

**Schedule Configuration (v0.2.0)**:
```cpp
void setSchedule(uint8_t startHour, uint8_t startMinute, 
                 uint8_t endHour, uint8_t endMinute);
void getSchedule(uint8_t* startHour, uint8_t* startMinute,
                 uint8_t* endHour, uint8_t* endMinute);
```

---

### 2. Display Module (`display.h/cpp`)

**Responsibility**: OLED and TFT screen management

```cpp
#include "display.h"

// Main functions:
void setupDisplays();                          // OLED/TFT initialization
void displayWifiProgress(const char* ssid);    // WiFi connection display
void displayIP(IPAddress ip);                  // IP address display
void updateOledAnimationStatus(                // OLED update (v0.2.0)
    const char* animationName,
    const char* modeName,
    IPAddress ip
);
```

**v0.2.0 Features**:
- Display animation and mode name
- Animated visualization bar (14 patterns)
- Automatic adaptation 128x32 / 128x64
- 10 FPS refresh rate (100ms)

---

### 3. Web Interface Module (`web_interface.h`, `web_pages.h`, `web_styles.h`)

**Responsibility**: Web control and configuration interface

#### `web_styles.h` - CSS Styles
```cpp
// Centralized CSS for web interface
const char* WEB_STYLES = "...";
```

#### `web_pages.h` - HTML Generation
```cpp
String generateDashboardPage(
    uint32_t chipId, uint32_t flashSize, uint32_t flashSpeed,
    uint32_t heapSize, uint32_t freeHeap,
    uint32_t psramSize, uint32_t freePsram,
    uint32_t cpuFreq
);
```

**Dashboard Cards**:
1. LED Garland (animation, mode, schedule config)
2. Hardware (board, chip ID, CPU)
3. Flash Memory
4. RAM (Heap)
5. PSRAM
6. WiFi Network
7. System (uptime, temperature)
8. Network Details

#### `web_interface.h` - HTTP Handlers
```cpp
void handleRoot();              // GET /
void handleReboot();            // GET /reboot
void handleSetAnimation();      // GET /animation?id=X
void handleSetMode();           // GET /mode?id=X
void handleStatus();            // GET /status (JSON)
void handleSetSchedule();       // GET /schedule?start_hour=...
void setupWebServer();          // Route initialization
```

---

## Dependency Diagram

```
main.cpp
├── #include "config.h"
├── #include "board_config.h"
├── #include "secrets.h"
├── #include "display.h"              → display.cpp
├── #include "garland_control.h"      → garland_control.cpp
└── #include "web_interface.h"
    ├── #include "web_pages.h"
    │   └── #include "web_styles.h"
    └── #include "garland_control.h"
```

## Main Data Flow

### Startup (setup)
```
main.cpp::setup()
    ↓
setupDisplays() → OLED/TFT initialized
    ↓
setupWifi() → WiFi connection (progress displayed on OLED)
    ↓
setupGarland() → TB6612FNG initialized, Fade animation, Permanent mode
    ↓
setupWebServer() → HTTP routes configured
    ↓
displayIP() → IP displayed for 3 seconds on OLED
```

### Main Loop (loop)
```
main.cpp::loop()
    ↓
updateGarland() → Animation according to current mode
    ↓
button1.tick() → Button 1 press detection (animation)
    ↓
button2.tick() → Button 2 press detection (mode)
    ↓
buttonBoot.tick() → Long press BOOT detection (restart)
    ↓
server.handleClient() → HTTP request processing
    ↓
if (millis() - lastOledAnimUpdate > 100)
    updateOledAnimationStatus() → OLED refresh (10 FPS)
```

### HTTP Request Workflow
```
Client → GET /animation?id=3
    ↓
server.handleClient() (main.cpp)
    ↓
handleSetAnimation() (web_interface.h)
    ↓
setGarlandAnimation(ANIM_STROBE) (garland_control.cpp)
    ↓
updateOledAnimationStatus() (display.cpp)
    ↓
server.send(200, "text/plain", "Animation changed")
    ↓
Client ← OK Response
```

### Schedule Configuration Workflow (v0.2.0)
```
Client → GET /schedule?start_hour=18&start_minute=0&end_hour=23&end_minute=0
    ↓
handleSetSchedule() (web_interface.h)
    ↓
setSchedule(18, 0, 23, 0) (garland_control.cpp)
    ↓
Static variables updated
    ↓
Client ← "Schedule saved"
```

---

## TB6612FNG Control

### Direction Logic
```cpp
// Direction 0: Off
digitalWrite(AIN1, LOW);
digitalWrite(AIN2, LOW);

// Direction 1: Direction A Forward
digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, LOW);

// Direction 2: Direction B Backward
digitalWrite(AIN1, LOW);
digitalWrite(AIN2, HIGH);

// Direction 3: Brake
digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, HIGH);

// PWM intensity control
analogWrite(PWMA, brightness); // 0-255
```

### Bi-directional Animation Principle
```
Garland (50 anti-parallel LEDs)
┌─────────────────────────────┐
│ 25 LEDs Direction A (→)     │ Lit if AIN1=HIGH, AIN2=LOW
│ 25 LEDs Direction B (←)     │ Lit if AIN1=LOW, AIN2=HIGH
└─────────────────────────────┘

Alternating Fade Animation:
  Phase 0-127: Direction A brightness=0→255
  Phase 128-255: Direction B brightness=255→0
```

---

## File Structure

```
Anim-Guirlande/
├── include/
│   ├── config.h              General configuration (HAS_OLED, HAS_ST7789, etc.)
│   ├── board_config.h        ESP32-S3 / ESP32 Classic pin mapping
│   ├── secrets.h             WiFi credentials (not versioned)
│   ├── display.h             OLED/TFT management + animation bar
│   ├── garland_control.h     Animations + modes + sensors
│   ├── web_styles.h          Web interface CSS
│   ├── web_pages.h           Dashboard HTML generator
│   └── web_interface.h       HTTP handlers + routes
├── src/
│   ├── main.cpp              Entry point, setup, loop
│   ├── display.cpp           Display implementation
│   └── garland_control.cpp   Animation/mode implementation
├── docs/
│   ├── ARCHITECTURE.md       This file
│   ├── ARCHITECTURE_FR.md    French version
│   ├── PIN_MAPPING.md        Connection schematics
│   ├── PIN_MAPPING_FR.md     French version
│   ├── USER_GUIDE.md         User guide (English)
│   └── USER_GUIDE_FR.md      User guide (French)
├── platformio.ini            PlatformIO configuration
├── README.md                 Main documentation (English)
├── README_FR.md              Main documentation (French)
├── CHANGELOG.md              Version history (English)
└── CHANGELOG_FR.md           Version history (French)
```

---

## Best Practices

### 📏 Memory Management
- Use `F()` macro for constant strings in PROGMEM
- Avoid `String` for large data (use `char*` or buffers)
- Monitor heap with `ESP.getFreeHeap()`
- ESP32-S3: Take advantage of PSRAM (8 MB)

### 🔒 Security
- WiFi credentials in `secrets.h` (ignored by Git)
- Basic validation of schedule parameters (0-23h, 0-59min)
- JavaScript confirmation for restart
- No web authentication (add if public exposure)

### 📱 Web Interface
- Responsive design (CSS Grid auto-fit)
- Mobile-first (tested on smartphones)
- Immediate visual feedback (popups, reloads)
- Simple REST API (GET with query params)

### ⚡ Performance
- Non-blocking animations (`millis()` instead of `delay()`)
- OLED refreshed at 10 FPS (CPU economy)
- 8-bit PWM at 5000 Hz (TB6612FNG)
- Avoid complex calculations in `loop()`

### 🐛 Debugging
- Use `LOG_PRINT()` / `LOG_PRINTLN()` (defined in config.h)
- Serial monitor at 115200 baud
- ESP32 Exception Decoder (PlatformIO)
- Check WiFi before web access

---

## Future Developments

### 🔮 Future Features
- **RTC Module**: Real-time clock for accurate schedules
- **EEPROM Save**: Persist animation/mode on reboot
- **MQTT**: Home automation integration (Home Assistant, etc.)
- **OTA Updates**: Firmware updates without cable
- **Custom Animations**: Web animation editor
- **Multi-garland**: WiFi synchronization

### 🛠️ Technical Improvements
- Web authentication (login/password)
- HTTPS (SSL certificates)
- WebSocket for real-time updates
- Complete REST API (POST/PUT/DELETE)
- Web interface in React/Vue
- LittleFS storage for config

---

## Version & History

**Current version**: v0.2.0 (2025-12-09)

**Major evolutions**:
- **v0.1.0**: Animation system + modes + basic web interface
- **v0.2.0**: Real-time OLED + animation bar + web schedule config

**Key files**:
- ✅ `garland_control.h/cpp` - Created in v0.1.0
- ✅ `display.h/cpp` - Enhanced in v0.2.0
- ✅ `web_interface.h` - Extended in v0.2.0 (`/schedule`)
- ✅ `web_pages.h` - Extended in v0.2.0 (schedule config UI)

---

## References

- **[README.md](../README.md)** - Complete project documentation
- **[README_FR.md](../README_FR.md)** - French version
- **[PIN_MAPPING.md](./PIN_MAPPING.md)** - Hardware connection schematics
- **[PIN_MAPPING_FR.md](./PIN_MAPPING_FR.md)** - French version
- **[USER_GUIDE.md](./USER_GUIDE.md)** - Detailed user guide
- **[USER_GUIDE_FR.md](./USER_GUIDE_FR.md)** - French version
- **[CHANGELOG.md](../CHANGELOG.md)** - Complete version history

---

**Last updated**: 2025-12-09  
**Document version**: 0.2.0
