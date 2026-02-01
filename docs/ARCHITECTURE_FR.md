### Persistance de la configuration (NVS)

La configuration (mode, animation, intervalles) est stockée dans la NVS de l’ESP32 via les fonctions `loadGarlandSettings()` et `saveGarlandSettings()` (voir `garland_control.cpp`).

- Au démarrage, `loadGarlandSettings()` est appelée après l’initialisation matérielle pour restaurer l’état précédent.
- Toute modification via l’interface ou les boutons déclenche `saveGarlandSettings()`.
- Si la NVS est vide ou corrompue, les valeurs par défaut sont utilisées puis sauvegardées.

Ceci garantit la restauration automatique des réglages utilisateur après redémarrage ou coupure d’alimentation.
# 📚 Architecture - LED-Garland-Anim v5.6.1

## 🎯 Vue d'ensemble


LED-Garland-Anim v5.6.x prend en charge plusieurs plateformes matérielles officielles :

- **ESP32 Classic (IdeaSpark/DevKitC)**
- **ESP32 Wroom (DevKit V1)**
- **ESP32-C3 HW-675 (OLED 0.42" 72×40)**
- **ESP32-S3 Mini (esp32s3_mini)**
- **ESP32-S3 Super Mini (esp32s3_supermini)**

Toutes les fonctionnalités sont disponibles sur chaque carte, avec adaptation automatique de l'affichage (OLED ou sans écran selon la plateforme).

- **Interface Web** : Contrôle à distance et configuration
- **Affichage Local** : OLED (HW-675), ou sans écran (autres plateformes)
- **Contrôle Physique** : Boutons pour changement d'animation/mode
- **Modes Intelligents** : Gestion automatique basée sur capteurs
- **Module TB6612FNG** : Contrôle bi-directionnel de la guirlande
- **Détection automatique du capteur de mouvement** : PIR (HC-SR501) ou radar Doppler (RCWL-0516) auto-détecté sur GPIO 35

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

// Convention de nommage GPIO :
// BUTTON_BOOT, BUTTON_1, BUTTON_2, I2C_SDA, I2C_SCL, TB6612_PWMA, TB6612_AIN1, TB6612_AIN2, TB6612_STBY, MOTION_SENSOR_PIN, LED_BUILTIN
```

**Animations (11 types)** :
- `ANIM_OFF` : Guirlande éteinte
- `ANIM_FADE_ALTERNATE` : Transition douce entre sens A et B
- `ANIM_BLINK_ALTERNATE` : Alternance rapide entre sens A et B
- `ANIM_PULSE` : Pulsation simultanée
- `ANIM_BREATHING` : Respiration lente
- `ANIM_STROBE` : Flash stroboscopique rapide
- `ANIM_HEARTBEAT` : Double pulsation (battement de cœur)
- `ANIM_WAVE` : Onde sinusoïdale
- `ANIM_SPARKLE` : Scintillement aléatoire
- `ANIM_METEOR` : Traînée météore
- `ANIM_AUTO` : Enchaînement des animations

## Mapping matériel

Voir [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md) pour le détail. Toutes les plateformes listées ci-dessus sont supportées officiellement.


## Système d'affichage

- OLED SSD1306 (72x40px)
- Écran de démarrage moderne : nom projet, version, progression WiFi
- Interface principale : en-têtes centrés, infos compactes, zone d'animation
- 11 visualisations animées (une par animation)
- Mises à jour temps réel à 10 FPS

## Capteurs & Boutons

- Capteur de mouvement (PIR ou RCWL-0516, GPIO 35, auto-détecté)
- Boutons utilisateur (GPIO 16/17)
- Driver TB6612FNG (PWM, direction, standby)

## Interface Web

- Tableau de bord : infos système, mémoire, WiFi
- Contrôle guirlande : sélection animation/mode
- Visualisation capteurs

## Versionnement

- Ce document : v1.13.0 (2026-01-06)
- Voir CHANGELOG_FR.md pour le détail
