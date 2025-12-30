# LED-Garland-Anim

**Version 1.0.0** - Contrôleur d'Animation de Guirlande LED Bi-directionnelle pour ESP32 IdeaSpark

Contrôlez une guirlande à 2 fils avec LEDs en anti-parallèle via un module pilote moteur TB6612FNG. Dispose de 11 animations spectaculaires avec visualisations LCD vibrantes, mode Auto avec démarrage instantané, 2 modes de fonctionnement intelligents, écran couleur ST7789 1.14" intégré, interface web, et contrôles physiques par boutons.

[🇬🇧 English version](README.md) | [📝 Changelog](CHANGELOG_FR.md) | [📚 Documentation](docs/) | [📋 Notes de Version](docs/RELEASE_NOTES_FR.md)

---

## 🎯 Version 1.0.0 - Plateforme ESP32 IdeaSpark

Cette version majeure se concentre exclusivement sur la carte **ESP32 IdeaSpark** avec écran **LCD ST7789 1.14"** intégré (135×240 pixels). Tout support ESP32-S3 et affichages obsolètes (OLED/TFT) a été supprimé pour une plateforme moderne et simplifiée.

### 🆕 Nouveau dans v1.0.0
- ✨ **Interface LCD ST7789 Moderne** - Affichage couleur vibrant avec animations fluides
- 🎨 **11 Visualisations Animées** - Chaque animation a sa représentation visuelle unique
- 📱 **Affichage Réseau WiFi** - SSID et IP toujours visibles à l'écran principal
- 🐛 **Correction Détection Mouvement** - Timer à déclenchement front montant fonctionnel
- 🔧 **Plateforme Simplifiée** - ESP32 IdeaSpark uniquement, réduction code 15%

---

## ✨ Fonctionnalités Principales

### 🎄 11 Animations Spectaculaires
- **Éteint** : Guirlande désactivée (texte rouge "OFF")
- **Fade Alterné** : Transition douce avec barres dégradé jaune/bleu
- **Clignotement Alterné** : Alternance rapide entre Direction A et B
- **Pulsation** : Battement simultané avec cercle violet qui grandit
- **Respiration** : Montée/descente lente avec fade cyan
- **Strobe** : Flashs stroboscopiques blancs rapides
- **Battement Cœur** : Double pulsation rouge (♥️ BOM-bom...)
- **Vague** : Onde sinusoïdale cyan fluide
- **Scintillement** : 15 points jaunes clignotant aléatoirement
- **Météore** : Effet traînée lumineuse orange/jaune
- **Mode Auto** : Cycle à travers toutes les animations (30s chacune) avec doubles cercles en orbite

### 🎮 2 Modes de Fonctionnement Intelligents
- **Permanent** : Toujours allumé (par défaut au démarrage)
- **Déclenchement Mouvement** : Activation capteur PIR (30s après détection avec détection front)

### 🖥️ Écran LCD ST7789 1.14" (135×240 pixels)
- **Écran Démarrage** : Nom projet, version, barre progression connexion WiFi
- **Écran Principal** :
  - Nom application et version (centrés)
  - Infos réseau WiFi (SSID + adresse IP)
  - Noms mode et animation actuels
  - Grande zone visualisation animée (234×57 pixels)
- **11 Animations Visuelles Distinctes** : Effets fluides, colorés et modernes à 10 FPS
- **Interface Professionnelle** : Séparateurs cyan, labels colorés, layout optimisé

### 🌐 Interface Web
- **Tableau de Bord Complet** : Infos système, mémoire, statistiques WiFi
- **Contrôle Guirlande** : Sélection animation et mode (2 modes, 11 animations incl. Auto)
- **Visualisation Capteurs** : État capteur mouvement PIR
- **Actions Distantes** : Rafraîchir et redémarrer
- **Mises à Jour Temps Réel** : Affichage mis à jour via interface web

### 🔘 Contrôles Physiques
- **Bouton BOOT (GPIO 0)** : Redémarrage sur appui long (1s)
- **Bouton 1 (GPIO 16)** : Changement animation + accès mode auto
- **Bouton 2 (GPIO 17)** : Changement mode fonctionnement

### 🔧 Caractéristiques Techniques
- **Plateforme Unique** : ESP32 IdeaSpark LCD 1.14" uniquement
- **WiFiMulti** : Connexion automatique à plusieurs réseaux
- **Module TB6612FNG** : Contrôle guirlande bi-directionnelle (PWM 0-255, 5000 Hz)
- **Capteur PIR** : Détection mouvement HC-SR501 avec déclenchement front
- **Paramètres Persistants** : Stockage NVS pour mode, animation et durées
- **Code Optimisé** : Réduction 15% depuis v0.x.x multi-plateforme

---

## 📋 Prérequis

### Logiciels
- **PlatformIO** (extension VS Code ou CLI recommandé)
- **Python 3.x** (pour PlatformIO)
- **Git** (pour contrôle version)

### Matériel
- Carte **ESP32 IdeaSpark LCD 1.14"** (avec écran ST7789 intégré)
- Module **TB6612FNG** (contrôleur dual pont-H)
- Guirlande LED 2 fils (LEDs anti-parallèle, ~50 LEDs total)
- Capteur **PIR HC-SR501** (pour mode déclenchement mouvement)
- 2x **Boutons poussoirs** (pour contrôles utilisateur)
- Alimentation appropriée :
  - ESP32 : 5V via USB-C (500mA+)
  - TB6612FNG : 5-15V externe (1-2A selon guirlande)

### Non Supporté en v1.0.0
- ❌ Cartes ESP32-S3 (supprimées)
- ❌ Affichages OLED (SSD1306)
- ❌ Autres affichages TFT (ILI9341, etc.)
- ❌ Capteur lumière LDR

---

## 🛠️ Installation

### 1. Cloner le Projet
```bash
git clone https://github.com/votre-utilisateur/LED-Garland-Anim.git
cd LED-Garland-Anim
```

### 2. Configurer `include/secrets.h`
Créer ou éditer `include/secrets.h` pour configurer vos réseaux WiFi :

```cpp
#ifndef SECRETS_H
#define SECRETS_H

// Réseaux WiFi (connexion au premier disponible)
const char* WIFI_NETWORKS[][2] = {
    {"VotreSSID1", "VotreMotDePasse1"},
    {"VotreSSID2", "VotreMotDePasse2"},
    {nullptr, nullptr}  // Terminateur
};

// Optionnel : Bot Telegram (si utilisation telegram_control.cpp)
#define TELEGRAM_BOT_TOKEN "votre_token_bot"
#define TELEGRAM_CHAT_ID "votre_chat_id"

#endif
```

### 3. Câblage Matériel

Consultez **[docs/PIN_MAPPING_FR.md](./docs/PIN_MAPPING_FR.md)** pour schémas détaillés.

#### Résumé Pins ESP32 IdeaSpark :
```
LCD ST7789 (Intégré sur PCB) :
  MOSI  → GPIO 23
  SCLK  → GPIO 18
  CS    → GPIO 15
  DC    → GPIO 2
  RST   → GPIO 4
  BLK   → GPIO 32  ⚠️ DOIT ÊTRE HIGH

Pilote Moteur TB6612FNG :
  PWMA  → GPIO 12
  AIN1  → GPIO 25
  AIN2  → GPIO 33
  STBY  → GPIO 14

Capteurs :
  PIR   → GPIO 35 (pin input-only)

Boutons :
  BTN1  → GPIO 16
  BTN2  → GPIO 17
  BOOT  → GPIO 0 (intégré)

I2C (disponible pour extension) :
  SDA   → GPIO 21
  SCL   → GPIO 22
```

**⚠️ Critique** : GPIO 32 (LCD_BLK) doit être mis à HIGH pour voir l'affichage !

### 4. Compiler et Téléverser

```bash
# Compiler pour ESP32 IdeaSpark (seule plateforme supportée)
pio run -e esp32devkitc

# Téléverser sur la carte
pio run -e esp32devkitc -t upload

# Moniteur série
pio device monitor
```

**Note** : L'environnement par défaut est `esp32devkitc` configuré pour ESP32 IdeaSpark.

---

## 📡 Utilisation

### Séquence Démarrage
1. **Écran Démarrage** : Affiche nom projet, version et progression connexion WiFi
2. **Connexion WiFi** : Se connecte au premier réseau disponible de secrets.h
3. **Écran Principal** : Affiche infos WiFi (SSID + IP), mode, animation et visuel
4. **Notification Telegram** : Envoie message démarrage avec détails réseau (si configuré)
5. **Interface Web** : Disponible à `http://[IP_ESP32]`

### Contrôles Physiques
- **Bouton 1 (GPIO 16)** :
  - Appui court : Animation suivante
  - Cycle : Éteint → Fade → Clignotement → Pulsation → Respiration → Strobe → Battement → Vague → Scintillement → Météore → Auto → Éteint...
- **Bouton 2 (GPIO 17)** :
  - Appui court : Mode suivant
  - Cycle : Permanent → Déclenchement Mouvement → Permanent...
- **Bouton BOOT (GPIO 0)** :
  - Appui long (1s) : Redémarrage ESP32

### Interface Web
Naviguez vers `http://[IP_ESP32]` pour :
- **Tableau de Bord** : Informations système (mémoire libre, uptime, signal WiFi)
- **Contrôle Guirlande** : Sélection animation (11 options) et mode (2 options)
- **État Capteurs** : État capteur mouvement PIR
- **Actions** : Rafraîchir données ou redémarrer appareil

### Affichage LCD Principal
```
┌──────────────────────────────┐
│ LED-Garland-Anim   (centré)  │  ← Nom appli
│ v1.0.0             (centré)  │  ← Version
├──────────────────────────────┤
│ Mode: Permanent              │  ← Mode actuel
│ Anim: Fade Alterne           │  ← Animation actuelle
├──────────────────────────────┤
│ SSID: MonWiFi                │  ← Réseau WiFi
│ IP: 192.168.1.100            │  ← Adresse IP
├──────────────────────────────┤
│ ┌──────────────────────────┐ │
│ │  [Visuel Animé]          │ │  ← Zone 234×57px
│ └──────────────────────────┘ │
└──────────────────────────────┘
```

Chaque animation a son visuel unique :
- **Fade Alterné** : Barres dégradé jaune/bleu
- **Pulsation** : Cercle violet qui grandit/rétrécit
- **Battement Cœur** : Effet double pulsation rouge
- **Auto** : Texte vert avec cercles en orbite
- Et 7 autres...

---

## 📊 Changements Mapping Pins (v1.0.0)

| Signal | Ancien (v0.x) | Nouveau (v1.0.0) | Raison |
|--------|--------------|------------------|---------|
| TB6612_AIN1 | GPIO 32 | **GPIO 25** | GPIO 32 nécessaire pour rétroéclairage LCD |
| PIR_SENSOR | GPIO 14 | **GPIO 35** | GPIO 35 est input-only (optimal capteurs) |
| LDR_SENSOR | GPIO 15 | **Supprimé** | Capteur lumière non utilisé en v1.0.0 |

**Mapping complet** : Voir [docs/PIN_MAPPING_FR.md](./docs/PIN_MAPPING_FR.md)

---

## 🔧 Configuration

### Durée Animation (Mode Auto)
Par défaut : 30 secondes par animation

Changer via interface web ou éditer dans `include/garland_control.h` :
```cpp
#define AUTO_MODE_INTERVAL 30000  // millisecondes
```

### Durée Détection Mouvement
Par défaut : 30 secondes après détection mouvement

Changer via interface web ou éditer dans `include/garland_control.h` :
```cpp
#define MOTION_TRIGGER_DURATION 30000  // millisecondes
```

### Rétroéclairage Affichage
Le rétroéclairage LCD est contrôlé par GPIO 32 et mis HIGH automatiquement dans `setupDisplay()`. Pour ajuster :

```cpp
pinMode(LCD_BLK, OUTPUT);
digitalWrite(LCD_BLK, HIGH);  // ON (requis pour voir affichage)
// digitalWrite(LCD_BLK, LOW);  // OFF (écran noir)
```

---

## 📁 Structure Projet

```
LED-Garland-Anim/
├── include/
│   ├── board_config.h        # Mapping pins ESP32 IdeaSpark
│   ├── config.h              # Configuration générale (ST7789, couleurs)
│   ├── secrets.h             # Réseaux WiFi (créé par utilisateur)
│   ├── display.h             # Gestion affichage ST7789
│   ├── garland_control.h     # Animations & modes guirlande
│   ├── web_interface.h       # Handlers HTTP
│   ├── web_pages.h           # Générateur HTML
│   └── telegram_control.h    # Bot Telegram (optionnel)
├── src/
│   ├── main.cpp              # Point d'entrée
│   ├── display.cpp           # Implémentation affichage
│   ├── garland_control.cpp   # Logique animations
│   └── telegram_control.cpp  # Implémentation bot Telegram
├── docs/
│   ├── PIN_MAPPING_FR.md     # Guide câblage complet
│   ├── ARCHITECTURE_FR.md    # Documentation technique
│   ├── USER_GUIDE_FR.md      # Manuel utilisateur
│   ├── TROUBLESHOOTING_FR.md # Problèmes & solutions
│   ├── RELEASE_NOTES_FR.md   # Points forts v1.0.0
│   └── *.md                  # Versions anglaises
├── platformio.ini            # Configuration PlatformIO
├── CHANGELOG_FR.md           # Historique versions
└── README_FR.md              # Ce fichier
```

---

## 🐛 Dépannage

### Écran LCD Noir
1. **Vérifier rétroéclairage** : GPIO 32 (LCD_BLK) doit être HIGH
2. **Vérifier câblage** : Pins SPI (MOSI, SCLK, CS, DC, RST)
3. **Alimentation** : Assurer 3.3V stable
4. **Code test** :
```cpp
pinMode(LCD_BLK, OUTPUT);
digitalWrite(LCD_BLK, HIGH);
display.fillScreen(ST77XX_WHITE);  // Devrait afficher écran blanc
```

### Guirlande Ne S'Allume Pas
1. **TB6612FNG STBY** : Doit être HIGH pour activer module
2. **Alimentation externe** : Vérifier 5-15V sur pin VM
3. **GND commun** : Vérifier connexion GND entre ESP32 et TB6612FNG
4. **Animation test** : Essayer "Pulsation" (simple, facile debug)

### Détection Mouvement Ne Fonctionne Pas
1. **Sensibilité PIR** : Ajuster potentiomètre sur HC-SR501
2. **Alimentation** : Assurer PIR a 5V
3. **Problème timer** : Vérifier moniteur série pour logs debug (toutes les 5s)
4. **Pin** : Vérifier connexion GPIO 35 (pin input-only)

### WiFi Ne Se Connecte Pas
1. **secrets.h** : Vérifier SSID et mot de passe
2. **2.4GHz** : ESP32 supporte seulement 2.4GHz WiFi (pas 5GHz)
3. **Moniteur série** : Vérifier tentatives connexion et erreurs
4. **Signal** : Se rapprocher du routeur

### Boutons Ne Répondent Pas
1. **Câblage** : Vérifier connexion vers GND
2. **Pull-up** : Résistances pull-up internes activées dans logiciel
3. **Test** : Devrait lire 3.3V quand non pressé, 0V quand pressé
4. **GPIO** : Assurer pins correctes (16, 17, 0)

Pour plus de solutions, voir [docs/TROUBLESHOOTING_FR.md](./docs/TROUBLESHOOTING_FR.md)

---

## 📊 Spécifications Techniques

### Affichage
- **Modèle** : LCD TFT ST7789 1.14"
- **Résolution** : 135×240 pixels
- **Couleur** : RGB565 (16-bit, 65K couleurs)
- **Interface** : SPI matériel
- **Taux Rafraîchissement** : 10 FPS pour animations
- **Orientation** : Paysage (rotation = 1)

### Contrôle Guirlande LED
- **Type** : 2 fils avec LEDs anti-parallèle
- **Configuration** : ~25 LEDs par direction (50 total)
- **Contrôleur** : Pont-H dual TB6612FNG
- **PWM** : 8-bit (0-255) à 5000 Hz
- **Directions** : Avant (A), Arrière (B), Éteint, Frein

### Mémoire & Performance
- **Flash** : 4MB (ESP32 Classic)
- **RAM** : ~320KB
- **Heap Libre** : ~200KB typique
- **Taille Code** : ~800KB compilé
- **CPU** : 240 MHz dual-core

### Consommation Énergie
- **ESP32 + LCD** : ~150mA @ 5V (USB)
- **Guirlande LED** : Variable (dépend luminosité et alimentation)
- **Total** : Recommandé 2A @ 5V pour sécurité

---

## 🚀 Feuille de Route / Idées Futures

- 🔮 Effets animation additionnels
- 🔮 Intégration MQTT pour domotique
- 🔮 Synchronisation multi-guirlandes
- 🔮 Effets réactifs capteur température/humidité
- 🔮 Mode réactif musique (entrée microphone)
- 🔮 Éditeur animation personnalisée via interface web

---

## 📝 Historique Versions

**Actuelle** : v1.0.0 (2025-12-30)

Voir [CHANGELOG_FR.md](./CHANGELOG_FR.md) pour historique complet.

Versions majeures :
- **v1.0.0** (2025-12-30) : Plateforme ESP32 IdeaSpark, LCD ST7789, affichage WiFi
- **v0.8.0** (2025-12-29) : Mise à jour convention nommage GPIO
- **v0.7.0** (2025-12-30) : LCD ST7789 et mises à jour pins boutons
- **v0.6.3** (2025-12-13) : 5 nouvelles animations (Strobe, Battement, Vague, Scintillement, Météore)
- **v0.1.0** (2025-12-09) : Version initiale avec contrôle guirlande

---

## 🤝 Contribuer

Les contributions sont bienvenues ! Merci de :
1. Forker le projet
2. Créer une branche fonctionnalité (`git checkout -b feature/amelioration`)
3. Committer vos changements (`git commit -m 'Ajout fonctionnalité'`)
4. Pousser vers la branche (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request

---

## 📄 Licence

Ce projet est fourni tel quel pour usage éducatif et personnel.

---

## 🙏 Remerciements

- **Adafruit** - Bibliothèques GFX, NeoPixel et ST7789
- **PlatformIO** - Excellente plateforme développement
- **Communauté ESP32** - Support framework Arduino
- **Toshiba** - IC pilote moteur TB6612FNG

---

**LED-Garland-Anim v1.0.0** - Contrôleur Moderne de Guirlande LED pour ESP32 IdeaSpark 🎄✨
