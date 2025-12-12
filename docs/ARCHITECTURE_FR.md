# 📚 Architecture - LED-Garland-Anim v0.6.3

## 🎯 Vue d'ensemble

Le projet LED-Garland-Anim utilise une architecture modulaire pour contrôler une guirlande LED bi-directionnelle avec :
- **Interface Web** : Contrôle à distance et configuration
- **Affichage Local** : OLED/TFT avec informations temps réel
- **Contrôle Physique** : Boutons pour changement d'animation/mode
- **Modes Intelligents** : Gestion automatique basée sur capteurs
- **Module TB6612FNG** : Contrôle bi-directionnel de la guirlande

## Structure Modulaire

### 1. Module Contrôle Guirlande (`garland_control.h/cpp`)

**Responsabilité** : Gestion animations et modes de fonctionnement

```cpp
#include "garland_control.h"

// Fonctions principales :
void setupGarland();                           // Initialisation
void updateGarland();                          // Mise à jour (appelée dans loop)
void setGarlandAnimation(GarlandAnimation);    // Changer animation
void setGarlandMode(GarlandMode);              // Changer mode
const char* getGarlandAnimationName();         // Nom animation actuelle
const char* getGarlandModeName();              // Nom mode actuel
```

**Animations (11 types)** :
- `ANIM_OFF` : Guirlande éteinte
- `ANIM_FADE_ALTERNATE` : Transition douce entre sens A et B
- `ANIM_BLINK_ALTERNATE` : Alternance rapide entre sens A et B
- `ANIM_PULSE` : Pulsation simultanée
- `ANIM_BREATHING` : Respiration lente
- `ANIM_STROBE` : Flash stroboscopique rapide
- `ANIM_HEARTBEAT` : Double pulsation (battement de cœur)
- `ANIM_WAVE` : Vague sinusoïdale fluide
- `ANIM_SPARKLE` : Scintillement aléatoire
- `ANIM_METEOR` : Traînée lumineuse avec estompage
- `ANIM_AUTO` : Cycle automatique entre toutes les animations (30s chacune) avec démarrage instantané

**Modes (2 types)** :
- `MODE_PERMANENT` : Toujours allumé
- `MODE_MOTION_TRIGGER` : Activation par capteur PIR (détection de mouvement)

---

### 2. Module Affichage (`display.h/cpp`)

**Responsabilité** : Gestion écrans OLED et TFT

```cpp
#include "display.h"

// Fonctions principales :
void setupDisplays();                          // Initialisation OLED/TFT
void displayWifiProgress(const char* ssid);    // Affichage connexion WiFi
void displayIP(IPAddress ip);                  // Affichage adresse IP
void updateOledAnimationStatus(                // Mise à jour OLED (v0.2.0)
    const char* animationName,
    const char* modeName,
    IPAddress ip
);
```

**Fonctionnalités v0.2.0** :
- Affichage nom animation et mode
- Barre de visualisation animée (14 patterns)
- Adaptation automatique 128x32 / 128x64
- Rafraîchissement 10 FPS (100ms)

---

### 3. Module Interface Web (`web_interface.h`, `web_pages.h`, `web_styles.h`)

**Responsabilité** : Interface web de contrôle et configuration

#### `web_styles.h` - Styles CSS
```cpp
// CSS centralisé pour l'interface web
const char* WEB_STYLES = "...";
```

#### `web_pages.h` - Génération HTML
```cpp
String generateDashboardPage(
    uint32_t chipId, uint32_t flashSize, uint32_t flashSpeed,
    uint32_t heapSize, uint32_t freeHeap,
    uint32_t psramSize, uint32_t freePsram,
    uint32_t cpuFreq
);
```

**Cartes du tableau de bord** :
1. LED Guirlande (animation, mode, config horaire)
2. Matériel (board, chip ID, CPU)
3. Mémoire Flash
4. RAM (Heap)
5. PSRAM
6. Réseau WiFi
7. Système (uptime, température)
8. Détails Réseau

#### `web_interface.h` - Handlers HTTP
```cpp
void handleRoot();              // GET /
void handleReboot();            // GET /reboot
void handleSetAnimation();      // GET /animation?id=X
void handleSetMode();           // GET /mode?id=X
void handleStatus();            // GET /status (JSON)
void handleSetSchedule();       // GET /schedule?start_hour=...
void setupWebServer();          // Initialisation routes
```

---

## Diagramme de Dépendances

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

## Flux de Données Principal

### Démarrage (setup)
```
main.cpp::setup()
    ↓
setupDisplays() → OLED/TFT initialisés
    ↓
setupWifi() → Connexion WiFi (affichage progression sur OLED)
    ↓
setupGarland() → TB6612FNG initialisé, animation Fade, mode Permanent
    ↓
setupWebServer() → Routes HTTP configurées
    ↓
displayIP() → IP affichée 3 secondes sur OLED
```

### Boucle Principale (loop)
```
main.cpp::loop()
    ↓
updateGarland() → Animation selon mode actuel
    ↓
button1.tick() → Détection appui Bouton 1 (animation)
    ↓
button2.tick() → Détection appui Bouton 2 (mode)
    ↓
buttonBoot.tick() → Détection appui long BOOT (restart)
    ↓
server.handleClient() → Traitement requêtes HTTP
    ↓
if (millis() - lastOledAnimUpdate > 100)
    updateOledAnimationStatus() → Rafraîchissement OLED (10 FPS)
```

### Workflow Requête HTTP
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
server.send(200, "text/plain", "Animation changée")
    ↓
Client ← Réponse OK
```

### Workflow Configuration Horaire (v0.2.0)
```
Client → GET /schedule?start_hour=18&start_minute=0&end_hour=23&end_minute=0
    ↓
handleSetSchedule() (web_interface.h)
    ↓
setSchedule(18, 0, 23, 0) (garland_control.cpp)
    ↓
Variables statiques mises à jour
    ↓
Client ← "Horaire programmé enregistré"
```

---

## Contrôle TB6612FNG

### Logique de Direction
```cpp
// Direction 0 : Off
digitalWrite(AIN1, LOW);
digitalWrite(AIN2, LOW);

// Direction 1 : Sens A Forward
digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, LOW);

// Direction 2 : Sens B Backward
digitalWrite(AIN1, LOW);
digitalWrite(AIN2, HIGH);

// Direction 3 : Brake
digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, HIGH);

// Contrôle intensité PWM
analogWrite(PWMA, brightness); // 0-255
```

### Principe Animation Bi-directionnelle
```
Guirlande (50 LEDs anti-parallèle)
┌─────────────────────────────┐
│ 25 LEDs Sens A (→)          │ Allumées si AIN1=HIGH, AIN2=LOW
│ 25 LEDs Sens B (←)          │ Allumées si AIN1=LOW, AIN2=HIGH
└─────────────────────────────┘

Animation Fade Alterné :
  Phase 0-127 : Sens A brightness=0→255
  Phase 128-255 : Sens B brightness=255→0
```

---

## Structure des Fichiers

```
Anim-Guirlande/
├── include/
│   ├── config.h              Configuration générale (HAS_OLED, HAS_ST7789, etc.)
│   ├── board_config.h        Pin mapping ESP32-S3 / ESP32 Classic
│   ├── secrets.h             Identifiants WiFi (non versionné)
│   ├── display.h             Gestion OLED/TFT + barre animation
│   ├── garland_control.h     Animations + modes + capteurs
│   ├── web_styles.h          CSS de l'interface web
│   ├── web_pages.h           Générateur HTML dashboard
│   └── web_interface.h       Handlers HTTP + routes
├── src/
│   ├── main.cpp              Point d'entrée, setup, loop
│   ├── display.cpp           Implémentation affichage
│   └── garland_control.cpp   Implémentation animations/modes
├── docs/
│   ├── ARCHITECTURE.md       Ce fichier
│   ├── PIN_MAPPING.md        Schémas de connexion
│   ├── USER_GUIDE_FR.md      Guide utilisateur (français)
│   └── (autres docs...)
├── platformio.ini            Configuration PlatformIO
├── README.md                 Documentation principale (anglais)
├── README_FR.md              Documentation principale (français)
├── CHANGELOG.md              Historique versions (anglais)
└── CHANGELOG_FR.md           Historique versions (français)
```

---

## Bonnes Pratiques

### 📏 Gestion Mémoire
- Utiliser `F()` macro pour chaînes constantes en PROGMEM
- Éviter `String` pour grandes données (utiliser `char*` ou buffers)
- Surveiller heap avec `ESP.getFreeHeap()`
- ESP32-S3 : Profiter de la PSRAM (8 MB)

### 🔒 Sécurité
- Identifiants WiFi dans `secrets.h` (ignoré par Git)
- Validation basique des paramètres horaire (0-23h, 0-59min)
- Confirmation JavaScript pour redémarrage
- Pas d'authentification web (à ajouter si exposition publique)

### 📱 Interface Web
- Design responsive (Grid CSS auto-fit)
- Mobile-first (testé sur smartphones)
- Feedback visuel immédiat (popups, reloads)
- API REST simple (GET avec query params)

### ⚡ Performances
- Animations non bloquantes (`millis()` au lieu de `delay()`)
- OLED rafraîchi à 10 FPS (économie CPU)
- PWM 8 bits à 5000 Hz (TB6612FNG)
- Éviter calculs complexes dans `loop()`

### 🐛 Débogage
- Utiliser `LOG_PRINT()` / `LOG_PRINTLN()` (définis dans config.h)
- Moniteur série à 115200 baud
- ESP32 Exception Decoder (PlatformIO)
- Vérifier WiFi avant accès web

---

## Évolutions Possibles

### 🔮 Fonctionnalités Futures
- **Module RTC** : Horloge temps réel pour horaires précis
- **Sauvegarde EEPROM** : Persistance animation/mode au redémarrage
- **MQTT** : Intégration domotique (Home Assistant, etc.)
- **OTA Updates** : Mises à jour firmware sans câble
- **Animations personnalisées** : Éditeur web d'animations
- **Multi-guirlandes** : Synchronisation WiFi

### 🛠️ Améliorations Techniques
- Authentification web (login/password)
- HTTPS (certificats SSL)
- WebSocket pour mises à jour temps réel
- API REST complète (POST/PUT/DELETE)
- Interface web en React/Vue
- Stockage LittleFS pour config

---

## Version & Historique

**Version actuelle** : v0.2.0 (2025-12-09)

**Évolutions majeures** :
- **v0.1.0** : Système animations + modes + interface web de base
- **v0.2.0** : OLED temps réel + barre animation + config horaire web

**Fichiers clés** :
- ✅ `garland_control.h/cpp` - Créés en v0.1.0
- ✅ `display.h/cpp` - Améliorés en v0.2.0
- ✅ `web_interface.h` - Étendu en v0.2.0 (`/schedule`)
- ✅ `web_pages.h` - Étendu en v0.2.0 (config horaire UI)

---

## Références

- **[README.md](../README.md)** - Documentation complète du projet
- **[PIN_MAPPING.md](./PIN_MAPPING.md)** - Schémas de connexion matériel
- **[USER_GUIDE_FR.md](./USER_GUIDE_FR.md)** - Guide d'utilisation détaillé
- **[CHANGELOG.md](../CHANGELOG.md)** - Historique complet des versions

---

**Dernière mise à jour** : 2025-12-09  
**Version document** : 0.2.0
