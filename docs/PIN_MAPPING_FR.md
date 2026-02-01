

# Guide de Connexion des Pins - LED-Garland-Anim v5.6.1

*Ce document est valide à partir de la version 5.6.1.*


## Plateformes supportées
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32 Wroom
- ESP32-C3 HW-675
- ESP32-S3 Mini (esp32s3_mini)
- ESP32-S3 Super Mini (esp32s3_supermini)

> 📌 **Affichage OLED SSD1306 (I2C) disponible sur toutes les plateformes si connecté sur SDA/SCL**
> 📌 **Rotation OLED** : Configurable via `OLED_ROTATION` dans config.h (U8G2_R0, U8G2_R1, U8G2_R2, U8G2_R3)

> 📌 **Guide débutant** : Ce document explique comment connecter physiquement les composants à votre carte ESP32 pour le projet LED-Garland-Anim.

## 🎯 Table des matières



# Mapping des broches (v5.3.1)



## Affichage OLED SSD1306 (I2C)

L'écran OLED SSD1306 (I2C) est supporté sur toutes les plateformes. Branchement recommandé :
- **SDA** : GPIO 4 (par défaut)
- **SCL** : GPIO 5 (par défaut)
Alimentez l'écran en 3.3V ou 5V selon le module. Adresse I2C par défaut : `0x3C`.

## Autres périphériques

### Tableau de mapping complet (toutes plateformes)

| Fonction                | ESP32 Classic/Wroom/S3 Mini | ESP32-C3 HW-675      |
|-------------------------|-----------------------------|----------------------|
| **BTN1**                | GPIO 16                     | -                    |
| **BTN2**                | GPIO 17                     | -                    |
| **BTN3**                | GPIO 4                      | -                    |
| **BOOT (Mode/Reset)**   | -                           | GPIO 9               |
| **TB6612_PWMA**         | GPIO 13                     | GPIO 0               |
| **TB6612_AIN1**         | GPIO 26                     | GPIO 1               |
| **TB6612_AIN2**         | GPIO 25                     | GPIO 2               |
| **TB6612_STBY**         | GPIO 15                     | GPIO 3               |
| **MATRIX8X8 (DATA)**    | GPIO 34                     | GPIO 8               |
| **MOTION_SENSOR_PIN**   | GPIO 35                     | GPIO 10 (optionnel)  |
| **OLED SDA**            | GPIO 4                      | SDA                  |
| **OLED SCL**            | GPIO 5                      | SCL                  |
| **TB6612_PWMA**   | PWMA       | GPIO 12  | PWM Sens A                 | Contrôle intensité lumineuse|
| **TB6612_AIN1**   | AIN1       | GPIO 25  | Direction bit 1            | Contrôle direction courant  |
| **TB6612_AIN2**   | AIN2       | GPIO 33  | Direction bit 2            | Contrôle direction courant  |
| **TB6612_STBY**   | STBY       | GPIO 14  | Standby                    | Activation module (HIGH)    |
| **MATRIX8X8**     | DIN        | GPIO 27  | WS2812B Data               | Pin dédié pour la matrice  |
| **MOTION_SENSOR_PIN** | OUT        | GPIO 35  | Capteur de mouvement (PIR ou RCWL-0516, auto-détecté) | Voir docs pour détails |

---

## Carte ESP32-C3 HW-675 (NOUVEAU en v5.2.0)


---

## Schémas de connexion détaillés

### Boutons physiques (Classic/Wroom/S3 Mini)
| Bouton   | GPIO  | Fonction                       |
|----------|-------|-------------------------------|
| BTN1     | 16    | Animation suivante / auto      |
| BTN2     | 17    | Animation matrice suivante     |
| BTN3     | 4     | Changement de mode             |

### Bouton BOOT (C3 HW-675)
| Bouton   | GPIO  | Fonction                       |
|----------|-------|-------------------------------|
| BOOT     | 9     | Changement mode (clic), reboot (long) |


### Note OLED
Sur OLED, l’IP est affichée en petit, la ligne du bas indique le mode actif.

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

### 🌈 Schéma de connexion Matrice NeoPixel 8x8

```
ESP32 IdeaSpark      Matrice WS2812B 8x8
┌─────────┐        ┌──────────┐
│ GPIO 27 ├───────►│ DIN      │
│   5V    ├───────►│ VCC      │ (Alimentation externe recommandée)
│   GND   ├───────►│ GND      │
└─────────┘        └──────────┘
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

**Note** : Ce guide accompagne le projet LED-Garland-Anim v1.11.3. Pour toute question ou problème, consultez le README.md et le code source commenté.

**Version du document : v1.13.0 (2026-01-06)**
