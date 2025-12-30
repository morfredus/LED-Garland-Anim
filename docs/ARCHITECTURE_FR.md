# 📚 Architecture - LED-Garland-Anim v1.0.0

## 🎯 Vue d'ensemble

LED-Garland-Anim v1.0.0 est désormais unifié pour la carte ESP32 IdeaSpark avec écran LCD ST7789 intégré (1.14").
- **Interface Web** : Contrôle à distance et configuration
- **Affichage Local** : LCD ST7789 (plus d'OLED/TFT/ILI9341)
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

// Convention de nommage GPIO :
// BUTTON_BOOT, BUTTON_1, BUTTON_2, I2C_SDA, I2C_SCL, TB6612_PWMA, TB6612_AIN1, TB6612_AIN2, TB6612_STBY, PIR_SENSOR, LED_BUILTIN
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

Voir [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md) pour le détail. Seule la carte ESP32 IdeaSpark + ST7789 est supportée.

## Système d'affichage

- LCD ST7789 (135x240px)
- Écran de démarrage moderne : nom projet, version, progression WiFi
- Interface principale : en-têtes centrés, infos compactes, grande zone d'animation
- 11 visualisations animées (une par animation)
- Mises à jour temps réel à 10 FPS

## Capteurs & Boutons

- Capteur PIR (GPIO 35)
- Boutons utilisateur (GPIO 16/17)
- Driver TB6612FNG (PWM, direction, standby)

## Interface Web

- Tableau de bord : infos système, mémoire, WiFi
- Contrôle guirlande : sélection animation/mode
- Visualisation capteurs

## Versionnement

- Ce document : v1.0.0 (2025-12-30)
- Voir CHANGELOG_FR.md pour le détail
