# Notes de Version v5.2.0 - Support ESP32-C3 HW-675

**Date**: 2026-01-07  
**Version**: 5.2.0  
**Type**: MINEUR (Nouvelle plateforme matérielle)

---

## 🎯 Résumé de la Version

Cette version introduit le **support complet de l'ESP32-C3 HW-675** avec écran **OLED 0.42" (72×40 px)** intégré, élargissant la compatibilité matérielle pour inclure l'architecture RISC-V aux côtés du support ESP32 Classic (Xtensa) existant. L'implémentation maintient une compatibilité ascendante à 100% et une parité fonctionnelle entre les deux plateformes.

---

## ✨ Nouvelles Fonctionnalités

### 1. Support Plateforme ESP32-C3 HW-675

**Nouvel Environnement PlatformIO**: `esp32c3_hw675`
- Carte: `esp32-c3-devkitm-1`
- Architecture: RISC-V single-core @ 160MHz
- Flash: 4MB, RAM: 320KB
- Serial USB CDC avec timing d'initialisation approprié
- Build flags: `TARGET_ESP32C3_HW675`, `HAS_OLED_U8G2`, `ARDUINO_USB_MODE=1`, `ARDUINO_USB_CDC_ON_BOOT=1`

### 2. Module d'Affichage OLED (`src/display_oled.cpp`)

**Spécifications de l'Écran**:
- Contrôleur: SSD1306
- Résolution: 72×40 pixels (0.42" diagonale)
- Interface: I2C Matériel (SDA=GPIO5, SCL=GPIO6)
- Adresse I2C: 0x3C
- Bibliothèque: U8g2 @ ^2.35.19

**Fonctionnalités**:
- Disposition simplifiée optimisée pour petite résolution
- Affiche: Adresse IP + Mode actuel uniquement
- Scanner bus I2C pour diagnostic matériel
- Écran de démarrage avec nom du projet
- Mise à jour automatique lors des changements de mode

**Constructeur U8g2** (validé):
```cpp
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
```

### 3. Dispatcher de Configuration Carte

**Fichier**: `include/board_config.h`

Sélection automatique du mapping de pins selon la cible de build:
- `#ifdef TARGET_ESP32C3_HW675` → Pins ESP32-C3 HW-675
- `#else` → Pins ESP32 Classic IdeaSpark

**Mapping Pins ESP32-C3 HW-675**:
| Fonction | GPIO | Notes |
|----------|------|-------|
| OLED SDA | 5 | Données I2C |
| OLED SCL | 6 | Horloge I2C |
| TB6612 PWMA | 0 | Intensité guirlande |
| TB6612 AIN1 | 1 | Contrôle direction |
| TB6612 AIN2 | 2 | Contrôle direction |
| TB6612 STBY | 3 | Activation module |
| Matrice WS2812B | 8 | Données NeoPixel |
| Bouton BOOT | 9 | Cycle mode + reboot |
| Capteur Mouvement | 10 | PIR/RCWL (optionnel) |

### 4. Fonctionnalité Bouton BOOT (ESP32-C3)

**Bouton**: GPIO 9 (intégré sur carte)

**Actions**:
- **Clic simple**: Cycle entre les modes de fonctionnement
  1. MODE_MOTION_TRIGGER (Détection)
  2. MODE_MOTION_MATRIX_INDEPENDENT (Détection+Tout)
  3. MODE_PERMANENT (Permanent)
- **Appui long (1 seconde)**: Redémarrage système

### 5. Initialisation Serial USB CDC (ESP32-C3)

**Problème**: ESP32-C3 USB CDC nécessite un timing d'initialisation explicite  
**Solution**: Ajout de code spécifique ESP32-C3 dans `main.cpp`:

```cpp
#ifdef TARGET_ESP32C3_HW675
    delay(2000);  // Attente énumération USB CDC
    while (!Serial && millis() < 3000) {
        delay(10);  // Attente connexion série
    }
    Serial.println("==========================================");
    Serial.println("ESP32-C3 HW-675 - LED Garland Controller");
    Serial.println("==========================================");
#endif
```

---

## 🔧 Modifications Techniques

### Fichiers Modifiés

1. **`platformio.ini`**: Ajout `[env:esp32c3_hw675]` avec dépendance U8g2
2. **`include/config.h`**: Exclusion conditionnelle `HAS_ST7789` pour ESP32-C3
3. **`include/board_config.h`**: Dispatcher mapping pins
4. **`src/display.cpp`**: Correction conditions stub (`#elif !defined(HAS_OLED_U8G2)`)
5. **`src/main.cpp`**: Init USB CDC ESP32-C3 + handler bouton BOOT

### Nouveaux Fichiers

- **`src/display_oled.cpp`**: Implémentation affichage OLED (136 lignes)

### Statistiques de Build

**ESP32-C3 HW-675** (`esp32c3_hw675`):
- Flash: 70.7% (926KB / 1310KB)
- RAM: 13.7% (45KB / 327KB)
- Temps build: ~18s

**ESP32 Classic** (`esp32devkitc`):
- Flash: 71.3% (inchangé)
- RAM: 15.5% (inchangé)
- Temps build: ~20s (inchangé)

---

## 🎓 Matériel Validé

### Configuration de Test

**Carte**: ESP32-C3-DevKitM-1 avec module OLED HW-675  
**OLED**: SSD1306 72×40 via I2C (adresse 0x3C)  
**Alimentation**: USB-C 5V  
**Firmware**: v5.2.0 compilé avec `pio run -e esp32c3_hw675`

### Code de Test Validé

Fonctionnalité OLED validée avec test minimal:

```cpp
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define SDA_PIN 5
#define SCL_PIN 6

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 72, 40);
  u8g2.setFont(u8g2_font_04b_03_tr);
  u8g2.drawStr(2, 12, "OLED OK");
  u8g2.drawStr(2, 24, "Init...");
  u8g2.sendBuffer();
  delay(2000);
}
```

**Environnement PlatformIO** (validé):
```ini
[env:esp32c3_hw675]
platform = espressif32
board = esp32-c3-devkitm-1
framework = arduino
monitor_speed = 115200
lib_deps = 
    olikraus/U8g2 @ ^2.35.19
    adafruit/Adafruit NeoPixel @ ^1.12.0
build_flags = 
    -D ARDUINO_USB_MODE=1
    -D ARDUINO_USB_CDC_ON_BOOT=1
```

---

## 📚 Mises à Jour Documentation

### Fichiers Mis à Jour (EN/FR)
- ✅ CHANGELOG.md / CHANGELOG_FR.md → Entrée v5.2.0
- ✅ README.md / README_FR.md → Matériel ESP32-C3 requis
- ✅ PIN_MAPPING.md / PIN_MAPPING_FR.md → Tableau complet ESP32-C3
- ✅ HARDWARE_GUIDE.md / HARDWARE_GUIDE_FR.md → Spécifications ESP32-C3
- ✅ QUICKSTART.md / QUICKSTART_FR.md → Instructions build `esp32c3_hw675`
- ✅ ARCHITECTURE.md / ARCHITECTURE_FR.md → Module `display_oled.cpp`

### Fichiers Supprimés
- ❌ RELEASE_v4.0.0.md/FR → v5.0.0.md/FR → v5.1.x.md/FR (14 fichiers supprimés)

### Nouveaux Fichiers
- ✅ RELEASE_v5.2.0.md / RELEASE_v5.2.0_FR.md

---

## 🔄 Compatibilité

### Compatibilité Ascendante
- ✅ **Builds ESP32 Classic inchangés**: Aucune modification de l'environnement `esp32devkitc` existant
- ✅ **Interface Web identique**: Parité fonctionnelle à 100% entre plateformes
- ✅ **Format configuration**: Même structure `secrets.h` et NVS
- ✅ **Mises à jour OTA**: Compatible avec les deux plateformes

### Comparaison Plateformes

| Fonctionnalité | ESP32 Classic | ESP32-C3 HW-675 |
|----------------|--------------|-----------------|
| Architecture | Xtensa dual-core | RISC-V single-core |
| Écran | ST7789 135×240 TFT | SSD1306 72×40 OLED |
| Interface Écran | SPI | I2C |
| Boutons | 3 (BOOT + BTN1 + BTN2) | 1 (BOOT multifonc) |
| Capteur Mouvement | GPIO35 (standard) | GPIO10 (optionnel) |
| Contrôle Guirlande | TB6612FNG standard | TB6612FNG standard |
| LEDs Matrice | GPIO27 (GPIO34 alternatif) | GPIO8 |
| Interface Web | Complète | Complète |
| OTA | ✅ | ✅ |

---

## 🚀 Installation

### Pour ESP32 Classic (Existant)
```bash
pio run -e esp32devkitc
pio run -e esp32devkitc -t upload
```

### Pour ESP32-C3 HW-675 (Nouveau)
```bash
pio run -e esp32c3_hw675
pio run -e esp32c3_hw675 -t upload
pio device monitor
```

### Premier Démarrage
1. L'appareil se connecte au WiFi (configuré dans `secrets.h`)
2. Sortie série affiche:
   - Bannière: "ESP32-C3 HW-675 - LED Garland Controller"
   - Scan I2C: "Device at 0x3C"
   - Écran test OLED: "OLED OK / Init..."
3. OLED affiche: Adresse IP + mode actuel
4. Interface Web accessible via IP ou nom mDNS

---

## 🐛 Problèmes Connus

### Aucun Critique
Toutes les fonctionnalités validées et fonctionnelles comme attendu.

### Améliorations Optionnelles (Futur)
- Animations matrice pourraient être optimisées pour petit écran OLED
- Modes d'affichage additionnels pour OLED (preview animation, stats réseau)
- Fallback I2C software pour configurations pins alternatives

---

## 🎯 Guide de Migration

### De v5.1.5 vers v5.2.0

**Aucune action requise** pour utilisateurs ESP32 Classic existants. Ceci est une version **MINEURE** pure ajoutant du support matériel sans changements cassants.

**Pour nouveaux utilisateurs ESP32-C3 HW-675**:
1. Utiliser environnement `esp32c3_hw675` dans platformio.ini
2. Suivre mapping pins dans docs/PIN_MAPPING_FR.md (section ESP32-C3)
3. Connecter OLED via I2C (SDA=5, SCL=6, pas de résistances externes nécessaires)
4. Bouton BOOT (GPIO9) gère tous les changements de mode

---

## 👥 Contributeurs

- **morfredus** - Intégration ESP32-C3, driver OLED, documentation

---

## 📝 Classification Version

**SEMVER**: **5.2.0 (MINEUR)**
- Majeur: 5 (Refonte UI festive)
- Mineur: 2 (Support nouvelle plateforme matérielle)
- Patch: 0 (Version initiale)

**Justification**: Ajout support ESP32-C3 est un changement **MINEUR** car:
- ✅ Nouvelle fonctionnalité (écran OLED, nouvelle carte)
- ✅ Compatible ascendant (ESP32 Classic inchangé)
- ✅ Pas de changements cassants au code ou configuration existants
- ✅ Additif uniquement (nouvel environnement, nouveaux fichiers)

---

## 🔗 Ressources

- **Dépôt GitHub**: https://github.com/morfredus/LED-Garland-Anim
- **Documentation**: Voir dossier `docs/` (EN + FR)
- **Guide Matériel**: docs/HARDWARE_GUIDE_FR.md
- **Mapping Pins**: docs/PIN_MAPPING_FR.md
- **Quickstart**: docs/QUICKSTART_FR.md

---

**Bon codage ! 🎄✨**
