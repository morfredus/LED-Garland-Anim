# Guide de Connexion des Pins - LED-Garland-Anim v1.1.0

> 📌 **Guide débutant** : Ce document explique comment connecter physiquement les composants à votre carte ESP32 IdeaSpark pour le projet LED-Garland-Anim.

## 🎯 Table des matières
- [Carte ESP32 IdeaSpark](#carte-esp32-ideaspark)
- [Schémas de connexion détaillés](#schémas-de-connexion-détaillés)
- [Module TB6612FNG](#module-tb6612fng-contrôleur-de-guirlande)
- [Conseils pour débutants](#conseils-pour-débutants)

---

## Carte ESP32 IdeaSpark

### 📋 Tableau récapitulatif des pins

| Composant         | Signal      | Pin GPIO | Description                | Notes                       |
|-------------------|------------|----------|----------------------------|-----------------------------|
| **BUTTON_BOOT**   | Bouton     | GPIO 0   | Bouton intégré sur la carte| Déjà présent                |
| **BUTTON_1**      | Bouton     | GPIO 16  | Bouton externe             | Changement animation        |
| **BUTTON_2**      | Bouton     | GPIO 17  | Bouton externe             | Changement mode             |
| **LED_BUILTIN**   | LED        | GPIO 2   | LED bleue intégrée         | Heartbeat visuel            |
| **I2C_SDA**       | SDA        | GPIO 21  | Données I2C                | Pour extension future       |
| **I2C_SCL**       | SCL        | GPIO 22  | Horloge I2C                | Pour extension future       |
| **LCD ST7789**    | MOSI       | GPIO 23  | Données SPI                | LCD_MOSI                    |
| **LCD ST7789**    | SCLK       | GPIO 18  | Horloge SPI                | LCD_SCLK                    |
| **LCD ST7789**    | CS         | GPIO 15  | Chip Select                | LCD_CS                      |
| **LCD ST7789**    | DC         | GPIO 2   | Data/Command               | LCD_DC                      |
| **LCD ST7789**    | RST        | GPIO 4   | Reset                      | LCD_RST                     |
| **LCD ST7789**    | BLK        | GPIO 32  | Backlight                  | LCD_BLK                     |
| **TB6612_PWMA**   | PWMA       | GPIO 12  | PWM Sens A                 | Contrôle intensité lumineuse|
| **TB6612_AIN1**   | AIN1       | GPIO 25  | Direction bit 1            | Contrôle direction courant  |
| **TB6612_AIN2**   | AIN2       | GPIO 33  | Direction bit 2            | Contrôle direction courant  |
| **TB6612_STBY**   | STBY       | GPIO 14  | Standby                    | Activation module (HIGH)    |
| **MOTION_SENSOR_PIN** | OUT        | GPIO 35  | Capteur de mouvement (PIR ou RCWL-0516, auto-détecté) | Voir docs pour détails |

### 🎨 Schéma de connexion LCD ST7789

```
ESP32 IdeaSpark      LCD ST7789
┌─────────┐        ┌──────────┐
│ GPIO 23 ├───────►│ MOSI     │
│ GPIO 18 ├───────►│ SCLK     │
│ GPIO 15 ├───────►│ CS       │
│ GPIO 2  ├───────►│ DC       │
│ GPIO 4  ├───────►│ RST      │
│ GPIO 32 ├───────►│ BLK      │
│   3V3   ├───────►│ VCC      │
│   GND   ├───────►│ GND      │
└─────────┘        └──────────┘
```

### 🎄 Schéma de connexion TB6612FNG + Guirlande

```
ESP32 IdeaSpark      TB6612FNG              Guirlande LED
┌─────────┐        ┌──────────┐           ┌──────────┐
│ GPIO 12 ├───────►│ PWMA     │           │          │
│ GPIO 25 ├───────►│ AIN1     │           │          │
│ GPIO 33 ├───────►│ AIN2     │           │          │
│ GPIO 14 ├───────►│ STBY     │           │          │
│   3V3   ├───────►│ VCC      │           │          │
│   GND   ├───────►│ GND      ├──────────►│ GND (-)  │
│         │    ┌──►│ VM       │           │          │
│         │    │   │ AO1      ├──────────►│ Fil 1    │
│         │    │   │ AO2      ├──────────►│ Fil 2    │
└─────────┘    │   └──────────┘           └──────────┘
              │
       Alim Externe
       (5V-15V)
       ┌──────┐
       │  +   ├──────┘
       │  -   ├────────────────────────────►GND commun
       └──────┘
```

---

## Module TB6612FNG - Contrôleur de Guirlande

### 📚 Description du Module

Le **TB6612FNG** est un double pont H (dual H-bridge) qui permet de contrôler le sens et l'intensité du courant dans deux moteurs DC ou, dans notre cas, une guirlande LED bi-directionnelle.

**Caractéristiques** :
- Tension logique : 2.7V - 5.5V (compatible 3.3V ESP32)
- Tension moteur (VM) : 4.5V - 13.5V (jusqu'à 15V max)
- Courant continu par canal : 1.2A
- Courant crête : 3.2A (10ms)
- Fréquence PWM supportée : jusqu'à 100 kHz

### 🔌 Pinout du TB6612FNG

```
        TB6612FNG
    ┌──────────────┐
VM ─┤1          24├─ VCC (3.3V)
GND─┤2          23├─ AO1 (Sortie moteur A1)
AO2─┤3          22├─ AO2 (Sortie moteur A2)
BO1─┤4          21├─ BO1 (Sortie moteur B1)
BO2─┤5          20├─ BO2 (Sortie moteur B2)
    │              │
PWMA─┤6         19├─ PWMB
AIN1─┤7         18├─ BIN1
AIN2─┤8         17├─ BIN2
STBY─┤9         16├─ GND
    │              │
    └──────────────┘
```

**Pour notre projet**, nous utilisons uniquement le **Canal A** :
- **PWMA** : Signal PWM pour contrôler l'intensité
- **AIN1, AIN2** : Contrôle de la direction du courant
- **STBY** : Activation/désactivation du module
- **AO1, AO2** : Sorties vers les 2 fils de la guirlande

### ⚡ Table de Vérité

| AIN1 | AIN2 | PWMA | État du Canal A |
|------|------|------|-----------------|
| LOW  | LOW  | X    | Off (court-circuit à GND) |
| HIGH | LOW  | PWM  | Sens A (Forward) - LEDs groupe A |
| LOW  | HIGH | PWM  | Sens B (Backward) - LEDs groupe B |
| HIGH | HIGH | X    | Brake (court-circuit interne) |

**STBY** doit être à **HIGH** pour activer le module.

### 🎨 Exemples de Contrôle

#### Allumer LEDs Sens A (intensité 50%)
```cpp
digitalWrite(TB6612_AIN1, HIGH);
digitalWrite(TB6612_AIN2, LOW);
analogWrite(TB6612_PWMA, 128);  // 50% de 255
```

#### Allumer LEDs Sens B (intensité 100%)
```cpp
digitalWrite(TB6612_AIN1, LOW);
digitalWrite(TB6612_AIN2, HIGH);
analogWrite(TB6612_PWMA, 255);  // 100%
```

#### Éteindre toutes les LEDs
```cpp
digitalWrite(AIN1, LOW);
digitalWrite(AIN2, LOW);
// ou
digitalWrite(STBY, LOW);  // Met tout le module en veille
```

---

## Conseils pour Débutants

### ⚠️ Sécurité Électrique

1. **Toujours débrancher** l'alimentation avant de modifier le câblage
2. **Vérifier la polarité** : VCC = positif, GND = négatif
3. **Ne pas inverser** l'alimentation (risque de destruction du composant)
4. **Tension correcte** : ESP32 = 3.3V logique (pas 5V sur les GPIO!)
5. **Courant de la guirlande** : S'assurer que le TB6612FNG peut fournir le courant nécessaire
6. **Alimentation externe** : Utiliser une alimentation adaptée pour VM (pas l'USB de l'ESP32)

### 🔧 Vérification du Câblage

**Checklist avant de mettre sous tension** :
- [ ] Toutes les masses (GND) sont reliées ensemble
- [ ] Pas de court-circuit entre VCC et GND
- [ ] Les pins GPIO correspondent au code (`board_config.h`)
- [ ] L'alimentation externe est de la bonne tension (5-15V pour VM)
- [ ] Les câbles sont bien insérés (pas de faux contacts)
- [ ] Les boutons sont correctement orientés

### 🧪 Tests Progressifs

1. **Test ESP32 seul** : Téléverser le code, vérifier les logs série
2. **Test WiFi** : Vérifier la connexion et l'obtention d'une IP
3. **Test écrans** : Vérifier affichage OLED/TFT
4. **Test boutons** : Appuyer sur Btn1/Btn2, observer les logs
5. **Test capteur PIR** : Vérifier lecture PIR dans le moniteur série
6. **Test TB6612FNG** : Brancher module (sans guirlande), tester directions
7. **Test guirlande** : Connecter la guirlande et tester animations

### 🔍 Dépannage Commun

#### ESP32 ne démarre pas
- Vérifier alimentation USB (câble défectueux?)
- Essayer un autre port USB
- Maintenir BOOT enfoncé pendant upload

#### OLED ne s'allume pas
- Vérifier adresse I2C (0x3C ou 0x3D)
- Tester avec un scanner I2C
- Vérifier connexions SDA/SCL (ne pas inverser)

#### TFT affiche des couleurs bizarres
- Vérifier toutes les connexions SPI
- S'assurer que BL (backlight) est alimenté
- Tester avec un sketch exemple de la bibliothèque

#### Guirlande ne s'allume pas
- Vérifier que STBY est à HIGH
- Vérifier alimentation VM (5-15V)
- Tester avec un multimètre les sorties AO1/AO2
- S'assurer que le code envoie bien les signaux

#### PIR détecte en continu
- Ajuster le potentiomètre de sensibilité
- Éloigner des sources de chaleur (radiateur, soleil direct)
- Augmenter le délai de temporisation sur le module



### 📐 Calculs Utiles

**Calcul du courant de la guirlande** :
- Nombre de LEDs : ~50 (25 par sens)
- Courant par LED : ~20mA (typique)
- Courant total max : 25 × 20mA = 500mA = 0.5A
- ✅ TB6612FNG supporte 1.2A continu → OK



---

## ⚠️ Compatible ESP32 + ST7789

Vous pouvez utiliser n'importe quelle carte ESP32 avec un écran ST7789 compatible, mais il est impératif de respecter le brochage par défaut ci-dessus pour une compatibilité totale.

## 📚 Ressources Complémentaires

### Datasheets
- **TB6612FNG** : [Toshiba TB6612FNG Datasheet](https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf)
- **HC-SR501** : [PIR Motion Sensor Datasheet](https://www.epitran.it/ebayDrive/datasheet/44.pdf)
- **ESP32-S3** : [Espressif ESP32-S3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)

### Tutoriels
- [Guide TB6612FNG sur SparkFun](https://learn.sparkfun.com/tutorials/tb6612fng-hookup-guide)
- [Utilisation capteur PIR](https://randomnerdtutorials.com/esp32-pir-motion-sensor/)


### Outils de Test
- **Scanner I2C** : Pour trouver l'adresse de l'OLED
- **Multimètre** : Pour vérifier tensions et continuité
- **Oscilloscope** : Pour observer les signaux PWM (optionnel)

---

**Note** : Ce guide accompagne le projet LED-Garland-Anim v1.0.0. Pour toute question ou problème, consultez le README.md et le code source commenté.

**Version du document : v1.2.0 (2025-12-31)**
