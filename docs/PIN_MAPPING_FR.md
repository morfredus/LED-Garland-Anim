# Guide de Connexion des Pins - LED-Garland-Anim v1.0.0

> 📌 **Guide Débutant** : Ce document explique comment connecter physiquement les composants à votre carte **ESP32 IdeaSpark LCD 1.14"** pour le projet LED-Garland-Anim.

## 🎯 Informations de Version

- **Version** : 1.0.0
- **Plateforme** : ESP32 IdeaSpark avec écran LCD ST7789 1.14" intégré
- **Nom de Carte** : ESP32 IdeaSpark 1.14 LCD
- **Affichage** : LCD TFT ST7789 câblé sur PCB (135×240 pixels)

---

## 📋 ESP32 IdeaSpark LCD 1.14" - Mapping Complet des Pins

### Tableau de Référence Rapide

| Composant | Signal | Pin GPIO | Description | Notes |
|-----------|--------|----------|-------------|-------|
| **LCD ST7789** | MOSI | GPIO 23 | Données SPI | Câblé sur PCB |
| **LCD ST7789** | SCLK | GPIO 18 | Horloge SPI | Câblé sur PCB |
| **LCD ST7789** | CS | GPIO 15 | Chip Select | Câblé sur PCB |
| **LCD ST7789** | DC | GPIO 2 | Data/Command | Câblé sur PCB |
| **LCD ST7789** | RST | GPIO 4 | Reset | Câblé sur PCB |
| **LCD ST7789** | BLK | GPIO 32 | Rétroéclairage | **DOIT être HIGH pour voir l'image** |
| **TB6612_PWMA** | PWMA | GPIO 12 | Contrôle PWM | Intensité lumineuse (0-255) |
| **TB6612_AIN1** | AIN1 | GPIO 25 | Contrôle direction 1 | Contrôle sens courant |
| **TB6612_AIN2** | AIN2 | GPIO 33 | Contrôle direction 2 | Contrôle sens courant |
| **TB6612_STBY** | STBY | GPIO 14 | Standby | Activation module (HIGH=actif) |
| **PIR_SENSOR** | OUT | GPIO 35 | Signal détection | HIGH = mouvement détecté |
| **BUTTON_1** | Bouton | GPIO 16 | Bouton externe | Changement animation |
| **BUTTON_2** | Bouton | GPIO 17 | Bouton externe | Changement mode |
| **BUTTON_BOOT** | Bouton | GPIO 0 | Bouton BOOT intégré | Appui long = redémarrage |
| **I2C_SDA** | SDA | GPIO 21 | Données I2C | Disponible pour extension |
| **I2C_SCL** | SCL | GPIO 22 | Horloge I2C | Disponible pour extension |

---

## 🖥️ Écran LCD ST7789 (Intégré)

### Spécifications Affichage
- **Résolution** : 135×240 pixels
- **Profondeur Couleur** : RGB565 (16-bit, 65K couleurs)
- **Interface** : SPI (pins matérielles)
- **Orientation** : Paysage (rotation = 1)
- **Fréquence Rafraîchissement** : 10 FPS pour animations

### Connexions Câblées

```
Carte ESP32 IdeaSpark
┌─────────────────────────────────┐
│                                 │
│  ┌───────────────────────────┐  │
│  │   LCD ST7789 1.14"        │  │
│  │   (135×240 pixels)        │  │
│  │   Câblé sur PCB           │  │
│  └───────────────────────────┘  │
│                                 │
│  GPIO 23 ──► MOSI (Données SPI) │
│  GPIO 18 ──► SCLK (Horloge SPI) │
│  GPIO 15 ──► CS (Chip Select)   │
│  GPIO  2 ──► DC (Data/Command)  │
│  GPIO  4 ──► RST (Reset)        │
│  GPIO 32 ──► BLK (Rétroéclairage) │ ⚠️ DOIT ÊTRE HIGH
│                                 │
└─────────────────────────────────┘
```

**⚠️ CRITIQUE - Contrôle Rétroéclairage** :
- **GPIO 32 (BLK)** contrôle le rétroéclairage de l'écran
- **Doit être mis à HIGH** pour voir une image à l'écran
- Configuré automatiquement dans la fonction `setupDisplay()`

---

## 🎄 Pilote Moteur TB6612FNG + Guirlande LED

### Configuration des Pins

| Signal | ESP32 GPIO | Pin TB6612FNG | Fonction |
|--------|------------|---------------|----------|
| PWMA | GPIO 12 | PWMA | Contrôle intensité PWM (0-255) |
| AIN1 | GPIO 25 | AIN1 | Bit contrôle direction 1 |
| AIN2 | GPIO 33 | AIN2 | Bit contrôle direction 2 |
| STBY | GPIO 14 | STBY | Standby (HIGH = actif) |
| VCC | 3.3V | VCC | Alimentation logique |
| VM | 5-15V | VM | Alimentation moteur/guirlande |
| GND | GND | GND | Masse commune |

### Schéma de Connexion

```
ESP32 IdeaSpark         TB6612FNG              Guirlande LED
┌─────────────┐         ┌──────────┐           ┌──────────┐
│             │         │          │           │          │
│  GPIO 12    ├────────►│ PWMA     │           │          │
│  GPIO 25    ├────────►│ AIN1     │           │          │
│  GPIO 33    ├────────►│ AIN2     │           │          │
│  GPIO 14    ├────────►│ STBY     │           │          │
│             │         │          │           │          │
│    3.3V     ├────────►│ VCC      │           │          │
│    GND      ├────────►│ GND      ├──────────►│ GND (-)  │
│             │         │          │           │          │
│             │   ┌────►│ VM       │           │          │
│             │   │     │          │           │          │
│             │   │     │ AO1      ├──────────►│ Fil 1    │
│             │   │     │ AO2      ├──────────►│ Fil 2    │
│             │   │     │          │           │          │
└─────────────┘   │     └──────────┘           └──────────┘
                  │
        Alimentation Externe
           (5V-15V DC)
           ┌───────┐
           │   +   ├──────┘
           │   -   ├────────────────────────────►GND Commun
           └───────┘
```

### Alimentation TB6612FNG

**⚠️ IMPORTANT - Double Alimentation** :
- **VCC (3.3V)** : Logique de contrôle depuis pin 3V3 de l'ESP32
- **VM (5-15V)** : Alimentation moteur pour guirlande LED (source externe)
- **GND** : **DOIT ÊTRE COMMUN** entre ESP32, TB6612FNG et alimentation externe

### Table de Vérité TB6612FNG

| AIN1 | AIN2 | STBY | Sortie | État Guirlande |
|------|------|------|--------|----------------|
| LOW | LOW | HIGH | OFF | LEDs éteintes (frein) |
| HIGH | LOW | HIGH | Avant | LEDs Direction A allumées |
| LOW | HIGH | HIGH | Arrière | LEDs Direction B allumées |
| HIGH | HIGH | HIGH | Frein | Court-circuit frein |
| X | X | LOW | Désactivé | Module désactivé |

### Principe Fonctionnement Guirlande LED

```
Configuration LEDs Anti-Parallèle :

Fil 1 ──┬──►|──►|──►|── (Direction A : ~25 LEDs)
        │
Fil 2 ──┼──◄|──◄|──◄|── (Direction B : ~25 LEDs)
        │
       GND
```

- **Avant (AIN1=HIGH, AIN2=LOW)** : LEDs Direction A s'allument
- **Arrière (AIN1=LOW, AIN2=HIGH)** : LEDs Direction B s'allument
- **PWM (PWMA 0-255)** : Contrôle luminosité des LEDs actives
- **Fréquence** : 5000 Hz pour gradation douce

---

## 🚶 Capteur Mouvement PIR (HC-SR501)

### Configuration des Pins

| ESP32 GPIO | Pin PIR | Fonction |
|------------|---------|----------|
| GPIO 35 | OUT | Signal digital (HIGH = mouvement détecté) |
| 5V | VCC | Alimentation |
| GND | GND | Masse |

### Schéma de Connexion

```
ESP32 IdeaSpark      PIR HC-SR501
┌─────────────┐      ┌──────────┐
│             │      │          │
│  GPIO 35    ├─────►│ OUT      │ (Pin input-only)
│     5V      ├─────►│ VCC      │
│    GND      ├─────►│ GND      │
│             │      │          │
└─────────────┘      └──────────┘
```

**📌 Notes Sélection Pin** :
- **GPIO 35** est une pin input-only (parfaite pour capteurs)
- Ne peut pas être utilisée en sortie
- Pas de résistances pull-up/pull-down internes

### Réglages Capteur PIR
- **Sensibilité** : Ajustable via potentiomètre (portée 3-7 mètres)
- **Temps Délai** : Ajustable via potentiomètre (5s - 300s)
- **Mode Déclenchement** : Répétable (H) ou Non-répétable (L) - réglage jumper

---

## 🔘 Boutons Utilisateur

### Configuration des Pins

| Bouton | ESP32 GPIO | Fonction | Déclenchement |
|--------|------------|----------|---------------|
| BUTTON_BOOT | GPIO 0 | Redémarrage système | Appui long (1s) |
| BUTTON_1 | GPIO 16 | Changement animation | Appui court |
| BUTTON_2 | GPIO 17 | Changement mode | Appui court |

### Schéma de Connexion

```
       ESP32 IdeaSpark
       ┌─────────────┐
       │             │
       │  GPIO 0     ├────┐  BUTTON_BOOT
       │  (BOOT)     │    │  (intégré)
       │             │    │
       │  GPIO 16    ├────┤  BUTTON_1
       │             │    │  (externe)
       │             │    │
       │  GPIO 17    ├────┤  BUTTON_2
       │             │    │  (externe)
       │             │    │
       │    GND      ├────┴─── GND Commun
       │             │
       └─────────────┘

Câblage Boutons Externes (BUTTON_1 et BUTTON_2) :

    GPIO 16/17 ──────┤   ├───── GND
                     │   │
                   Bouton

Note : Résistances pull-up internes activées dans le logiciel
```

### Configuration Boutons
- **Mode Pull-up** : Résistances pull-up internes activées
- **État Actif** : LOW (pressé = connexion GND)
- **Anti-rebond** : Géré par bibliothèque OneButton

---

## 🔌 Bus I2C (Disponible pour Extension)

### Configuration des Pins

| ESP32 GPIO | Signal I2C | Fonction |
|------------|------------|----------|
| GPIO 21 | SDA | Données I2C |
| GPIO 22 | SCL | Horloge I2C |

**Disponible pour** :
- Capteurs externes (BME280, BMP180, etc.)
- Modules RTC (DS3231, DS1307)
- Écrans OLED I2C (si nécessaire)
- Autres périphériques I2C

---

## ⚡ Guide Alimentation

### Options Alimentation ESP32 IdeaSpark

1. **USB-C (Recommandé pour développement)**
   - Tension : 5V
   - Courant : 500mA typique
   - Fournit : Rails 5V et 3.3V

2. **Pin VIN**
   - Tension : 5V-12V DC
   - Courant : Jusqu'à 1A
   - Régulé à 3.3V sur carte

### Besoins Alimentation TB6612FNG

- **VCC** : 2.7V - 5.5V (connecter au 3.3V ESP32)
- **VM** : 4.5V - 13.5V (connecter à alimentation externe)
- **Courant Sortie** : Jusqu'à 1.2A par canal (pic 3.2A)

### Configuration Alimentation Recommandée

```
┌─────────────────────┐
│  Batterie USB       │ 5V, 2A
│  ou Adaptateur Mural│
└──────┬──────────────┘
       │
       ├──────────► ESP32 IdeaSpark (USB-C)
       │                 │
       │                 ├──► Logique 3.3V
       │                 └──► Écran LCD
       │
       └──────────► TB6612FNG (pin VM)
                        │
                        └──► Guirlande LED
```

**⚠️ Avertissements Alimentation** :
- **Toujours** connecter GND entre ESP32 et TB6612FNG
- **Jamais** dépasser 13.5V sur pin VM du TB6612FNG
- **Assurer** que l'alimentation peut fournir assez de courant pour la guirlande

---

## 🛠️ Résolution Conflits de Pins

### Changements Pins v1.0.0

| Signal | Ancien GPIO (v0.x) | Nouveau GPIO (v1.0.0) | Raison |
|--------|-------------------|----------------------|---------|
| TB6612_AIN1 | GPIO 32 | **GPIO 25** | GPIO 32 nécessaire pour rétroéclairage LCD |
| PIR_SENSOR | GPIO 14 | **GPIO 35** | GPIO 35 est input-only (idéale pour capteurs) |

### Pins Partagées (Acceptable)

- **GPIO 2 (LED_BUILTIN + LCD_DC)** : Usage partagé acceptable
  - LED_BUILTIN clignote au démarrage
  - LCD_DC utilisée pour signalisation données/commande écran
  - Pas de conflit car LCD_DC est output uniquement

---

## 📊 Carte Complète Allocation GPIO

| GPIO | Fonction | Direction | Notes |
|------|----------|-----------|-------|
| 0 | BUTTON_BOOT | Entrée | Bouton boot (intégré) |
| 2 | LCD_DC | Sortie | Data/command écran + LED_BUILTIN |
| 4 | LCD_RST | Sortie | Reset écran |
| 12 | TB6612_PWMA | Sortie | Contrôle PWM guirlande |
| 14 | TB6612_STBY | Sortie | Standby TB6612 |
| 15 | LCD_CS | Sortie | Chip select écran |
| 16 | BUTTON_1 | Entrée | Bouton utilisateur 1 |
| 17 | BUTTON_2 | Entrée | Bouton utilisateur 2 |
| 18 | LCD_SCLK | Sortie | Horloge SPI écran |
| 21 | I2C_SDA | E/S | Données I2C (extension) |
| 22 | I2C_SCL | Sortie | Horloge I2C (extension) |
| 23 | LCD_MOSI | Sortie | Données SPI écran |
| 25 | TB6612_AIN1 | Sortie | Contrôle direction 1 |
| 32 | LCD_BLK | Sortie | Rétroéclairage écran (DOIT être HIGH) |
| 33 | TB6612_AIN2 | Sortie | Contrôle direction 2 |
| 35 | PIR_SENSOR | Entrée | Détection mouvement (input-only) |

**Total GPIOs Utilisées** : 16 / 34 disponibles

---

## 🧰 Conseils Débutants

### 1. Commencer par Test Écran
```cpp
void setup() {
    pinMode(LCD_BLK, OUTPUT);
    digitalWrite(LCD_BLK, HIGH);  // Allumer le rétroéclairage !

    display.init(135, 240);
    display.setRotation(1);
    display.fillScreen(ST77XX_WHITE);
}
```

### 2. Tester TB6612FNG Séparément
- Connecter les LEDs d'abord
- Tester directions avant/arrière
- Vérifier contrôle luminosité PWM
- Vérifier alimentation externe

### 3. Vérifier Capteur PIR
- Ajuster potentiomètres sensibilité et délai
- Tester dans Moniteur Série
- Assurer alimentation 5V

### 4. Test Boutons
```cpp
void loop() {
    if (digitalRead(BUTTON_1) == LOW) {
        Serial.println("Bouton 1 pressé !");
    }
}
```

### 5. Erreurs Courantes à Éviter
- ❌ Oublier de mettre LCD_BLK à HIGH (écran reste noir)
- ❌ GND manquant entre ESP32 et TB6612FNG
- ❌ Utiliser GPIO 35 en sortie (c'est input-only !)
- ❌ Dépasser 13.5V sur pin VM du TB6612FNG

---

## 📚 Ressources Additionnelles

- **Pinout ESP32** : [Documentation Officielle Espressif](https://docs.espressif.com/)
- **Datasheet ST7789** : Documentation bibliothèque Adafruit ST7789
- **Datasheet TB6612FNG** : [Toshiba Officiel](https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf)
- **PIR HC-SR501** : Module capteur mouvement standard

---

## 🔍 Dépannage

### Écran LCD Ne Fonctionne Pas
1. Vérifier que LCD_BLK est mis à HIGH
2. Vérifier connexions SPI (MOSI, SCLK, CS)
3. Tester avec commande simple fill screen
4. Vérifier alimentation 3.3V

### Guirlande Ne S'Allume Pas
1. Vérifier que TB6612FNG STBY est à HIGH
2. Vérifier alimentation externe VM (5-15V)
3. Vérifier connexion GND commune
4. Tester niveaux logiques AIN1/AIN2
5. Mesurer signal PWM PWMA

### Capteur PIR Toujours Déclenché
1. Ajuster potentiomètre sensibilité
2. Éloigner capteur des sources de chaleur
3. Vérifier courants d'air/vibrations
4. Vérifier tension alimentation 5V

### Boutons Ne Répondent Pas
1. Vérifier câblage vers GND
2. Vérifier pull-up interne activée dans code
3. Tester avec multimètre (devrait lire 3.3V quand non pressé)

---

**LED-Garland-Anim v1.0.0** - Plateforme ESP32 IdeaSpark LCD 1.14" 🎄✨
