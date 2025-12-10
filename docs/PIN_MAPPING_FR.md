# Guide de Connexion des Pins - Anim-Guirlande

> 📌 **Guide débutant** : Ce document explique comment connecter physiquement les composants à votre carte ESP32-S3 ou ESP32 Classic pour le projet Anim-Guirlande.

## 🎯 Table des matières
- [ESP32-S3 DevKitC-1](#esp32-s3-devkitc-1)
- [ESP32 Classic DevKitC](#esp32-classic-devkitc)
- [Schémas de connexion détaillés](#schémas-de-connexion-détaillés)
- [Module TB6612FNG](#module-tb6612fng-contrôleur-de-guirlande)
- [Conseils pour débutants](#conseils-pour-débutants)

---

## ESP32-S3 DevKitC-1

### 📋 Tableau récapitulatif des pins

| Composant | Signal | Pin GPIO | Description | Notes |
|-----------|--------|----------|-------------|-------|
| **Bouton BOOT** | Button | GPIO 0 | Bouton intégré sur la carte | Déjà présent, redémarrage appui long |
| **Bouton 1** | Button | GPIO 16 | Bouton externe | Changement animation |
| **Bouton 2** | Button | GPIO 17 | Bouton externe | Changement mode |
| **LED RGB (NeoPixel)** | Data | GPIO 48 | LED RGB adressable intégrée | Feedback visuel d'état |
| **OLED SSD1306** | SDA | GPIO 21 | Données I2C | Connexion vers la broche SDA de l'OLED |
| **OLED SSD1306** | SCL | GPIO 20 | Horloge I2C | Connexion vers la broche SCL de l'OLED |
| **OLED SSD1306** | VCC | 3.3V | Alimentation | Broche 3V3 de l'ESP32 |
| **OLED SSD1306** | GND | GND | Masse | Broche GND de l'ESP32 |
| **TFT ST7789** | MOSI (SDA) | GPIO 11 | Données SPI | Broche SDA du ST7789 |
| **TFT ST7789** | SCLK (SCL) | GPIO 12 | Horloge SPI | Broche SCL du ST7789 |
| **TFT ST7789** | CS | GPIO 10 | Chip Select | Sélection du périphérique |
| **TFT ST7789** | DC | GPIO 9 | Data/Command | Indicateur données/commande |
| **TFT ST7789** | RST | GPIO 13 | Reset | Réinitialisation de l'écran |
| **TFT ST7789** | BL | GPIO 7 | Backlight | Rétroéclairage (LED) |
| **TFT ST7789** | VCC | 3.3V | Alimentation | Broche 3V3 de l'ESP32 |
| **TFT ST7789** | GND | GND | Masse | Broche GND de l'ESP32 |
| **TB6612FNG** | PWMA | GPIO 5 | PWM Sens A | Contrôle intensité lumineuse |
| **TB6612FNG** | AIN1 | GPIO 6 | Direction bit 1 | Contrôle direction courant |
| **TB6612FNG** | AIN2 | GPIO 4 | Direction bit 2 | Contrôle direction courant |
| **TB6612FNG** | STBY | GPIO 8 | Standby | Activation module (HIGH=actif) |
| **TB6612FNG** | VCC | 3.3V | Alimentation logique | Broche 3V3 de l'ESP32 |
| **TB6612FNG** | VM | 5-15V | Alimentation moteur | Alimentation externe pour guirlande |
| **TB6612FNG** | GND | GND | Masse | Commun avec GND ESP32 |
| **Capteur PIR** | OUT | GPIO 14 | Signal détection | HIGH = mouvement détecté |
| **Capteur PIR** | VCC | 5V | Alimentation | Broche 5V de l'ESP32 (via USB) |
| **Capteur PIR** | GND | GND | Masse | Broche GND de l'ESP32 |
| **Photorésistance LDR** | Signal | GPIO 15 | Lecture ADC | Diviseur de tension avec R=10kΩ |
| **LDR** | VCC | 3.3V | Alimentation | Via résistance 10kΩ |
| **LDR** | GND | GND | Masse | Via LDR vers GND |

### 🎄 Schéma de connexion TB6612FNG + Guirlande

```
ESP32-S3                TB6612FNG              Guirlande LED
┌─────────┐            ┌──────────┐           ┌──────────┐
│         │            │          │           │          │
│ GPIO 5  ├───────────►│ PWMA     │           │          │
│ GPIO 6  ├───────────►│ AIN1     │           │          │
│ GPIO 4  ├───────────►│ AIN2     │           │          │
│ GPIO 8  ├───────────►│ STBY     │           │          │
│         │            │          │           │          │
│   3V3   ├───────────►│ VCC      │           │          │
│   GND   ├───────────►│ GND      ├──────────►│ GND (-)  │
│         │            │          │           │          │
│         │    ┌──────►│ VM       │           │          │
│         │    │       │          │           │          │
│         │    │       │ AO1      ├──────────►│ Fil 1    │
│         │    │       │ AO2      ├──────────►│ Fil 2    │
│         │    │       │          │           │          │
└─────────┘    │       └──────────┘           └──────────┘
               │
        Alim Externe
        (5V-15V)
        ┌──────┐
        │  +   ├──────┘
        │  -   ├────────────────────────────►GND commun
        └──────┘
```

**⚠️ IMPORTANT - Alimentation TB6612FNG** :
- **VCC** (3.3V) : Logique de contrôle depuis ESP32
- **VM** (5-15V) : Alimentation puissance pour la guirlande (depuis source externe)
- **GND** : Masse commune entre ESP32, TB6612FNG et alimentation externe

**💡 Principe de fonctionnement** :
- Les LEDs sont montées en anti-parallèle (2 groupes dos-à-dos)
- Changement de direction du courant = changement de groupe de LEDs allumées
- PWM contrôle l'intensité lumineuse (0-255)

### 🚶 Schéma de connexion Capteur PIR

```
ESP32-S3           PIR HC-SR501
┌─────────┐        ┌──────────┐
│         │        │          │
│ GPIO 14 ├───────►│ OUT      │
│    5V   ├───────►│ VCC      │
│   GND   ├───────►│ GND      │
│         │        │          │
└─────────┘        └──────────┘
```

**Configuration PIR** :
- Ajuster la sensibilité via potentiomètre du module
- Ajuster le délai de temporisation (généralement 3s-5min)
- Signal HIGH quand mouvement détecté

### 💡 Schéma de connexion Photorésistance LDR

```
ESP32-S3           LDR + Résistance
┌─────────┐        
│         │        3.3V
│         │          │
│         │         ┌┴┐
│         │         │ │ R = 10kΩ
│         │         └┬┘
│         │          │
│ GPIO 15 ├──────────┼───┐
│         │          │   │
│         │         ┌┴┐  │
│         │         │ │ LDR (Photorésistance)
│         │         └┬┘  │
│         │          │   │
│   GND   ├──────────┴───┘
│         │
└─────────┘
```

**Principe** :
- Diviseur de tension : résistance 10kΩ en série avec LDR
- Plus de lumière → résistance LDR faible → tension élevée
- Moins de lumière → résistance LDR élevée → tension faible
- Lecture ADC 12 bits : 0-4095

### 🔘 Schéma de connexion Boutons

```
ESP32-S3           Bouton 1              Bouton 2
┌─────────┐        ┌──────┐              ┌──────┐
│         │        │      │              │      │
│ GPIO 16 ├────┬───┤  ○   ├───┐      ┌───┤  ○   ├───┐
│         │    │   │      │   │      │   │      │   │
│ GPIO 17 ├────┼───┘──────┘   │      │   └──────┴───┘
│         │    │              │      │              │
│   GND   ├────┴──────────────┴──────┴──────────────┘
│         │
└─────────┘
```

**Configuration** :
- Boutons actifs bas (appui = GND)
- Pull-up interne activé dans le code
- Antibounce géré par bibliothèque OneButton

### 🔌 Schéma de connexion OLED SSD1306 (I2C)

```
ESP32-S3           OLED SSD1306
┌─────────┐        ┌──────────┐
│         │        │          │
│ GPIO 21 ├───────►│ SDA      │
│ GPIO 20 ├───────►│ SCL      │
│    3V3  ├───────►│ VCC      │
│    GND  ├───────►│ GND      │
│         │        │          │
└─────────┘        └──────────┘
```

**Adresse I2C par défaut** : `0x3C` (parfois `0x3D`)

### 🖥️ Schéma de connexion TFT ST7789 (SPI)

```
ESP32-S3           TFT ST7789
┌─────────┐        ┌──────────┐
│         │        │          │
│ GPIO 11 ├───────►│ MOSI/SDA │
│ GPIO 12 ├───────►│ SCLK/SCL │
│ GPIO 10 ├───────►│ CS       │
│ GPIO  9 ├───────►│ DC       │
│ GPIO 13 ├───────►│ RST      │
│ GPIO  7 ├───────►│ BL       │
│    3V3  ├───────►│ VCC      │
│    GND  ├───────►│ GND      │
│         │        │          │
└─────────┘        └──────────┘
```

---

## ESP32 Classic DevKitC

### 📋 Tableau récapitulatif des pins

| Composant | Signal | Pin GPIO | Description | Notes |
|-----------|--------|----------|-------------|-------|
| **Bouton BOOT** | Button | GPIO 0 | Bouton intégré sur la carte | Déjà présent, redémarrage appui long |
| **Bouton 1** | Button | GPIO 4 | Bouton externe | Changement animation |
| **Bouton 2** | Button | GPIO 16 | Bouton externe | Changement mode |
| **LED Builtin** | LED | GPIO 2 | LED bleue intégrée | Heartbeat visuel |
| **OLED SSD1306** | SDA | GPIO 21 | Données I2C | Connexion vers la broche SDA de l'OLED |
| **OLED SSD1306** | SCL | GPIO 22 | Horloge I2C | Connexion vers la broche SCL de l'OLED |
| **OLED SSD1306** | VCC | 3.3V | Alimentation | Broche 3V3 de l'ESP32 |
| **OLED SSD1306** | GND | GND | Masse | Broche GND de l'ESP32 |
| **TFT ILI9341** | MOSI | GPIO 23 | Données SPI | Broche SDA du TFT |
| **TFT ILI9341** | SCLK | GPIO 18 | Horloge SPI | Broche SCL du TFT |
| **TFT ILI9341** | CS | GPIO 19 | Chip Select | Sélection du périphérique |
| **TFT ILI9341** | DC | GPIO 27 | Data/Command | Indicateur données/commande |
| **TFT ILI9341** | RST | GPIO 26 | Reset | Réinitialisation de l'écran |
| **TFT ILI9341** | BL | GPIO 13 | Backlight | Rétroéclairage (LED) |
| **TFT ILI9341** | VCC | 3.3V | Alimentation | Broche 3V3 de l'ESP32 |
| **TFT ILI9341** | GND | GND | Masse | Broche GND de l'ESP32 |
| **TB6612FNG** | PWMA | GPIO 25 | PWM Sens A | Contrôle intensité lumineuse |
| **TB6612FNG** | AIN1 | GPIO 32 | Direction bit 1 | Contrôle direction courant |
| **TB6612FNG** | AIN2 | GPIO 33 | Direction bit 2 | Contrôle direction courant |
| **TB6612FNG** | STBY | GPIO 14 | Standby | Activation module (HIGH=actif) |
| **TB6612FNG** | VCC | 3.3V | Alimentation logique | Broche 3V3 de l'ESP32 |
| **TB6612FNG** | VM | 5-15V | Alimentation moteur | Alimentation externe pour guirlande |
| **TB6612FNG** | GND | GND | Masse | Commun avec GND ESP32 |
| **Capteur PIR** | OUT | GPIO 35 | Signal détection | HIGH = mouvement détecté |
| **Capteur PIR** | VCC | 5V | Alimentation | Broche 5V de l'ESP32 (via USB) |
| **Capteur PIR** | GND | GND | Masse | Broche GND de l'ESP32 |
| **Photorésistance LDR** | Signal | GPIO 34 | Lecture ADC | Diviseur de tension avec R=10kΩ |
| **LDR** | VCC | 3.3V | Alimentation | Via résistance 10kΩ |
| **LDR** | GND | GND | Masse | Via LDR vers GND |

### 🎄 Schéma de connexion TB6612FNG + Guirlande (ESP32 Classic)

```
ESP32 Classic           TB6612FNG              Guirlande LED
┌─────────┐            ┌──────────┐           ┌──────────┐
│         │            │          │           │          │
│ GPIO 25 ├───────────►│ PWMA     │           │          │
│ GPIO 32 ├───────────►│ AIN1     │           │          │
│ GPIO 33 ├───────────►│ AIN2     │           │          │
│ GPIO 14 ├───────────►│ STBY     │           │          │
│         │            │          │           │          │
│   3V3   ├───────────►│ VCC      │           │          │
│   GND   ├───────────►│ GND      ├──────────►│ GND (-)  │
│         │            │          │           │          │
│         │    ┌──────►│ VM       │           │          │
│         │    │       │          │           │          │
│         │    │       │ AO1      ├──────────►│ Fil 1    │
│         │    │       │ AO2      ├──────────►│ Fil 2    │
│         │    │       │          │           │          │
└─────────┘    │       └──────────┘           └──────────┘
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
digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, LOW);
analogWrite(PWMA, 128);  // 50% de 255
```

#### Allumer LEDs Sens B (intensité 100%)
```cpp
digitalWrite(AIN1, LOW);
digitalWrite(AIN2, HIGH);
analogWrite(PWMA, 255);  // 100%
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
5. **Test capteurs** : Vérifier lectures PIR et LDR dans le moniteur série
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

#### LDR ne varie pas
- Vérifier le diviseur de tension (résistance 10kΩ)
- Tester la résistance de la LDR avec multimètre
- S'assurer que GPIO 15/34 est bien en mode ADC

### 📐 Calculs Utiles

**Calcul du courant de la guirlande** :
- Nombre de LEDs : ~50 (25 par sens)
- Courant par LED : ~20mA (typique)
- Courant total max : 25 × 20mA = 500mA = 0.5A
- ✅ TB6612FNG supporte 1.2A continu → OK

**Diviseur de tension LDR** :
```
Vadc = 3.3V × (R / (R + Rldr))
```
- R = 10kΩ (résistance fixe)
- Rldr = variable (100Ω en pleine lumière, 10MΩ dans le noir)
- Plus de lumière → Rldr faible → Vadc élevé

---

## 📚 Ressources Complémentaires

### Datasheets
- **TB6612FNG** : [Toshiba TB6612FNG Datasheet](https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf)
- **HC-SR501** : [PIR Motion Sensor Datasheet](https://www.epitran.it/ebayDrive/datasheet/44.pdf)
- **ESP32-S3** : [Espressif ESP32-S3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)

### Tutoriels
- [Guide TB6612FNG sur SparkFun](https://learn.sparkfun.com/tutorials/tb6612fng-hookup-guide)
- [Utilisation capteur PIR](https://randomnerdtutorials.com/esp32-pir-motion-sensor/)
- [Lecture photorésistance LDR](https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/)

### Outils de Test
- **Scanner I2C** : Pour trouver l'adresse de l'OLED
- **Multimètre** : Pour vérifier tensions et continuité
- **Oscilloscope** : Pour observer les signaux PWM (optionnel)

---

**Note** : Ce guide accompagne le projet LED-Garland-Anim v0.2.0. Pour toute question ou problème, consultez le README.md et le code source commenté.

**Version du document** : v0.2.0 - 2025-12-09
