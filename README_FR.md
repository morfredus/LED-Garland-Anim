# LED-Garland-Anim

**Version 0.6.0** - Contrôleur d'animation de guirlande LED bi-directionnelle pour ESP32/ESP32-S3

Contrôlez une guirlande à 2 fils avec LEDs en anti-parallèle via un module TB6612FNG. Dispose de 14 animations, 2 modes de fonctionnement intelligents, affichage OLED avec visualisation animée, interface web, et contrôles physiques par boutons.

[🇬🇧 English version](README.md) | [📝 Journal des modifications](CHANGELOG_FR.md) | [📚 Documentation](docs/)

---

## ✨ Fonctionnalités Principales

### 🎄 14 Animations de Guirlande
- **Fade Alterné**: Transition douce entre les deux sens de LEDs
- **Clignotement**: Alternance rapide entre Sens A et B
- **Onde Douce**: Effet de vague fluide
- **Stroboscope**: Flash rapide alterné
- **Pulsation**: Battement simultané des deux sens
- **Poursuite**: Effet de course entre les LEDs
- **Battement de Cœur**: Double pulsation caractéristique
- **Scintillement**: Clignotement aléatoire
- **Arc-en-ciel**: Vague multicolore simulée
- **Respiration**: Montée/descente lente de l'intensité
- **Feu**: Simulation d'effet flamme
- **Clignotement Doux**: Transition sinusoïdale
- **Météore**: Traînée lumineuse qui s'estompe
- **Mode Automatique**: Enchaînement de toutes les animations (30s chacune)

### 🎮 2 Modes de Fonctionnement Intelligents
- **Permanent**: Toujours allumé (par défaut au démarrage)
- **Détection Mouvement**: Déclenchement par capteur PIR (30s après détection mouvement)

### 🖥️ Affichage OLED en Temps Réel
- Affichage en direct des noms d'animation et de mode
- Adresse IP locale pour accès web
- Barre de visualisation animée (14 motifs distincts)
- Mise en page adaptative pour écrans 128x32 et 128x64
- Taux de rafraîchissement 10 FPS pour animations fluides

### 📡 Contrôle Telegram
- Commandes bot : `/anim <id|nom>`, `/mode <id|nom>`, `/nextanim`, `/nextmode`, `/status`, `/liste`
- `/liste` renvoie toutes les animations et modes avec leurs IDs
- Notification Telegram automatique à la connexion WiFi (SSID, IP, animation/mode courants)

### 🌐 Interface Web
- **Tableau de Bord Complet**: Info système, mémoire, statistiques WiFi
- **Contrôle Guirlande**: Sélection animation et mode (2 modes, 15 animations dont Auto)
- **Visualisation Capteurs**: État PIR, niveau luminosité
- **Actions à Distance**: Actualisation et redémarrage

### 🔘 Contrôles Physiques
- **Bouton 0 (BOOT)**: Redémarrage en appui long (1s)
- **Bouton 1**: Changement d'animation + accès mode auto
- **Bouton 2**: Changement de mode de fonctionnement

### 📱 Affichage & Feedback
- **Support OLED SSD1306**: Progression WiFi, IP, infos temps réel
- **Support TFT ST7789**: Écran couleur haute résolution
- **LED RGB NeoPixel**: Feedback visuel d'état
- **Multi-affichage**: OLED et TFT simultanément

### 🔌 Matériel Supporté
- **Multi-Cartes**: ESP32-S3 (N16R8, N8R8) et ESP32 Classic (DevKitC)
- **WiFiMulti**: Connexion automatique à plusieurs réseaux
- **Module TB6612FNG**: Contrôle bi-directionnel de la guirlande
- **Capteur PIR**: Détection de mouvement HC-SR501 (optionnel)
- **Photorésistance LDR**: Détection jour/nuit (optionnel)

---

## 📋 Prérequis

### Logiciels
- **PlatformIO** (extension VS Code ou CLI)
- **Python 3.x** (pour PlatformIO)
- **Git** (pour contrôle de version)

### Matériel
- Carte **ESP32-S3 DevKitC-1** ou **ESP32 DevKitC**
- Module **TB6612FNG** (contrôleur moteur double pont H)
- Guirlande LED à 2 fils (LEDs en anti-parallèle, ~50 LEDs total)
- Capteur **PIR HC-SR501** (optionnel, pour mode détection mouvement)
- Écran **OLED SSD1306** 128x32 ou 128x64 (optionnel)
- Écran **TFT ST7789** 240x240 (optionnel)
- **LED RGB NeoPixel** WS2812B (optionnel)
- Alimentation adaptée pour la guirlande (vérifier tension/courant)

---

## 🛠️ Installation

### 1. Cloner le Projet
```bash
git clone <votre-repo>
cd Anim-Guirlande
```

### 2. Configurer `include/secrets.h`
Éditez `include/secrets.h` pour définir vos réseaux WiFi et les identifiants du bot Telegram (`TELEGRAM_BOT_TOKEN`, `TELEGRAM_CHAT_ID`).

### 3. Configurer PlatformIO
Modifiez les chemins de build dans `platformio.ini` (optionnel) :

```ini
build_dir       = C:/pio_builds/LED-Garland-Anim/build
build_cache_dir = C:/pio_builds/LED-Garland-Anim/cache
```

### 4. Sélectionner l'Environnement
Choisissez votre carte dans `platformio.ini` :
- `esp32s3_n16r8`: ESP32-S3 avec 16MB Flash / 8MB PSRAM (par défaut)
- `esp32s3_n8r8`: ESP32-S3 avec 8MB Flash / 8MB PSRAM
- `esp32devkitc`: ESP32 Classic (4MB Flash)

### 5. Câbler les Composants
Consultez **[docs/PIN_MAPPING.md](./docs/PIN_MAPPING.md)** pour les schémas de connexion détaillés.

#### Résumé Pins ESP32-S3 :
```
TB6612FNG:
  PWMA  → GPIO 5
  AIN1  → GPIO 6
  AIN2  → GPIO 4
  STBY  → GPIO 8

Capteurs:
  PIR   → GPIO 14

Boutons:
  BTN1  → GPIO 16
  BTN2  → GPIO 17

Affichages:
  OLED SDA → GPIO 21
  OLED SCL → GPIO 22
```

#### Résumé Pins ESP32 Classic :
```
TB6612FNG:
  PWMA  → GPIO 25
  AIN1  → GPIO 32
  AIN2  → GPIO 33
  STBY  → GPIO 14

Capteurs:
  PIR   → GPIO 35

Boutons:
  BTN1  → GPIO 4
  BTN2  → GPIO 16

Affichages:
  OLED SDA → GPIO 21
  OLED SCL → GPIO 22
```

### 6. Compiler et Téléverser
```bash
# Compilation
pio run -e esp32s3_n16r8

# Upload
pio run -e esp32s3_n16r8 -t upload

# Moniteur série
pio device monitor
```

---

## 📡 Utilisation

### Démarrage
1. La guirlande démarre en animation **Auto** et mode **Permanent**
2. L'écran OLED/TFT affiche la progression de connexion WiFi
3. Une fois connecté, l'adresse IP s'affiche et une notification Telegram est envoyée (SSID/IP/animation/mode)
4. Accédez à l'interface web : `http://[IP_ESP32]`

### Contrôles Physiques
- **Bouton 1**: Passer à l'animation suivante (ou entrer en mode auto)
- **Bouton 2**: Changer de mode de fonctionnement
- **Bouton BOOT (appui long)**: Redémarrer l'ESP32

### Interface Web
- **Sélecteur Animation**: Choisir parmi 15 animations (dont Auto)
- **Sélecteur Mode**: Basculer entre 2 modes de fonctionnement
- **Bouton Actualiser**: Mettre à jour les informations système
- **Bouton Redémarrer**: Redémarrage à distance

### Bot Telegram
- Commandes (depuis le chat autorisé) :
  - `/anim <id|nom>` (ex : `/anim 3`, `/anim auto`)
  - `/mode <id|nom>` (ex : `/mode 1`, `/mode detect`)
  - `/nextanim`, `/nextmode`
  - `/status` (animation, mode, IP courants)
  - `/liste` (toutes les animations et modes avec IDs)

### Affichage OLED
- Affiche le nom de l'animation courante
- Affiche le nom du mode de fonctionnement courant
- Affiche l'adresse IP
- Barre de visualisation animée en bas (14 motifs distincts)

---

## 📁 Structure du Projet

```
Anim-Guirlande/
├── include/
│   ├── board_config.h        # Pin mapping ESP32/S3
│   ├── config.h              # Configuration générale
│   ├── secrets.h             # Réseaux WiFi + identifiants Telegram
│   ├── display.h             # Gestion écrans OLED/TFT
│   ├── garland_control.h     # Contrôle guirlande et animations
│   ├── web_interface.h       # Handlers HTTP
│   ├── web_pages.h           # Générateur HTML
│   └── web_styles.h          # Styles CSS
├── src/
│   ├── main.cpp              # Point d'entrée
│   ├── display.cpp           # Implémentation affichage
│   └── garland_control.cpp   # Implémentation animations
├── docs/
│   ├── PIN_MAPPING.md        # Schémas de connexion
│   ├── ARCHITECTURE.md       # Documentation technique
│   ├── USER_GUIDE_FR.md      # Guide utilisateur
│   └── TROUBLESHOOTING_FR.md # Guide de dépannage
├── platformio.ini            # Configuration PlatformIO
├── README.md                 # Version anglaise
├── README_FR.md              # Ce fichier
├── CHANGELOG.md              # Historique versions (anglais)
└── CHANGELOG_FR.md           # Historique versions (français)
```

---

## 🔧 Configuration Avancée

### Désactiver les Écrans
Dans `include/config.h` :
```cpp
// #define HAS_OLED        // Commenter pour désactiver
// #define HAS_ST7789      // Commenter pour désactiver
```

### Ajuster la Durée de Détection Mouvement
Dans `include/garland_control.h` :
```cpp
#define MOTION_TRIGGER_DURATION 30000  // Durée en ms après détection
```

---

## 📊 Spécifications Techniques

### Guirlande LED
- Type : 2 fils avec LEDs en anti-parallèle
- Configuration : ~25 LEDs Sens A + ~25 LEDs Sens B
- Contrôle : PWM 8 bits (0-255) à 5000 Hz
- Module : TB6612FNG (double pont H)

### Logique de Contrôle TB6612FNG
- Direction 0 (Off) : AIN1=LOW, AIN2=LOW
- Direction 1 (Forward A) : AIN1=HIGH, AIN2=LOW
- Direction 2 (Backward B) : AIN1=LOW, AIN2=HIGH
- Direction 3 (Brake) : AIN1=HIGH, AIN2=HIGH
- STBY doit être à HIGH pour activer

### Capteurs
- **PIR** : Signal digital (HIGH = mouvement détecté)
- **LDR** : Analogique 12 bits (0-4095)

### Mémoire (ESP32-S3 N16R8)
- Flash : 16 MB (partition huge_app)
- PSRAM : 8 MB (80 MHz Octal)
- RAM : ~500 KB (heap + PSRAM)

### WiFi
- Multi-réseau automatique (WiFiMulti)
- Auto-reconnexion en cas de perte
- Serveur Web sur port 80

---

## 🚀 Comportement au Démarrage

Au démarrage, le système s'initialise avec :
- **Mode Animation** : `AUTO` - Enchaîne les 14 animations (30 sec chacune)
- **Mode Fonctionnement** : `PERMANENT` - Guirlande toujours allumée
- **Affichage** : Affiche le nom de l'animation et l'adresse IP sur l'OLED

Modifiez ces valeurs par défaut dans `src/garland_control.cpp` :
```cpp
static GarlandAnimation currentAnimation = ANIM_AUTO;    // Changer vers une animation
static GarlandMode currentMode = MODE_PERMANENT;         // Ou MODE_MOTION_TRIGGER
```

---

## 🐛 Dépannage

### La Guirlande Ne S'Allume Pas
- Vérifier le câblage du TB6612FNG (VCC, GND, VM)
- S'assurer que STBY est à HIGH
- Tester avec animation simple (ex: Clignotement)
- Vérifier tension/courant de l'alimentation

### Le Capteur PIR Détecte en Continu
- Ajuster la sensibilité (potentiomètre sur module)
- Vérifier le délai de temporisation du PIR
- Éloigner des sources de chaleur

### L'ESP32 Ne Se Connecte Pas au WiFi
- Vérifier `secrets.h` (SSID et mot de passe corrects)
- S'assurer d'être en WiFi 2.4 GHz (pas 5 GHz)
- Consulter le moniteur série pour erreurs
- Essayer de se rapprocher du routeur

### Écran OLED Noir
- Vérifier l'adresse I2C (0x3C ou 0x3D)
- Tester avec scanner I2C
- Contrôler les connexions SDA/SCL
- Vérifier alimentation 3.3V

### Les Boutons Ne Répondent Pas
- Vérifier que les pins GPIO ne sont pas INPUT_ONLY
- Contrôler la configuration pull-up
- Tester avec multimètre
- S'assurer de la mise à la masse

---

## 📝 Versions

**Version Actuelle : v0.2.0** (2025-12-09)

Voir [CHANGELOG_FR.md](./CHANGELOG_FR.md) pour l'historique complet.

---

## 📚 Documentation

- **[README.md](./README.md)** - Version anglaise
- **[CHANGELOG.md](./CHANGELOG.md)** - Historique versions (anglais)
- **[CHANGELOG_FR.md](./CHANGELOG_FR.md)** - Historique versions (français)
- **[docs/PIN_MAPPING.md](./docs/PIN_MAPPING.md)** - Schémas de connexion détaillés
- **[docs/ARCHITECTURE.md](./docs/ARCHITECTURE.md)** - Architecture du code
- **[docs/USER_GUIDE_FR.md](./docs/USER_GUIDE_FR.md)** - Guide utilisateur complet
- **[docs/TROUBLESHOOTING_FR.md](./docs/TROUBLESHOOTING_FR.md)** - Dépannage détaillé

---

## 🤝 Contribution

Les contributions sont les bienvenues ! Merci de :
1. Fork le projet
2. Créer une branche (`git checkout -b feature/amelioration`)
3. Commit les changements (`git commit -m 'Ajout fonctionnalité'`)
4. Push sur la branche (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request

---

## 📄 Licence

Ce projet est fourni tel quel à des fins éducatives et personnelles.

---

## 👤 Auteur

Créé en tant que projet ESP32 spécialisé pour contrôler des guirlandes LED bi-directionnelles avec animations avancées et modes de fonctionnement intelligents.

---

## 🙏 Remerciements

- Équipe PlatformIO pour l'excellente plateforme de développement
- Adafruit pour les bibliothèques d'affichage et capteurs
- Communauté ESP32 pour le support du framework Arduino
- Module TB6612FNG pour le contrôle fiable moteur/LED
