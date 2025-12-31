## 8. Choisir entre upload USB ou OTA

Vous pouvez choisir la méthode de téléversement (USB ou OTA) à chaque upload sans modifier platformio.ini :

- **Téléversement USB (série) :**
  - Vérifiez que `upload_protocol` n’est pas défini dans platformio.ini (ou est commenté)
  - Utilisez :
    ```bash
    pio run -e esp32devkitc -t upload
    ```
  - PlatformIO détectera automatiquement le port série (ex : COM8)

- **Téléversement OTA (WiFi) :**

  - Utilisez :
    ```bash
    pio run -e esp32devkitc -t upload --upload-port 192.168.x.x
    ```
  - Remplacez `192.168.x.x` par l’adresse IP de votre ESP32
  - PlatformIO utilisera automatiquement OTA pour cet upload
  - ⚠️ **Note :** PlatformIO affichera un avertissement :
    > We have just detected `upload_port` as IP address or host name of ESP device. `upload_protocol` is switched to `espota`.
    Ceci est normal et ne nécessite aucune modification de votre configuration.

**Astuce :** Ne mettez pas `upload_protocol = espota` en global. Utilisez l’option `--upload-port` pour l’OTA uniquement quand nécessaire.

---
# LED-Garland-Anim

**Version : 1.5.0** (2025-12-31)

Contrôleur d'animation de guirlande LED bi-directionnelle pour ESP32 Classic (IdeaSpark/DevKitC) avec écran ST7789, auto-détection PIR/RCWL-0516, web interface, boutons physiques, 11 animations, modes intelligents, configuration persistante.

---

## 1. Matériel requis

- **Carte ESP32 Classic (IdeaSpark/DevKitC)**
- **Module TB6612FNG** (double pont H)
- **Guirlande LED 2 fils** (LEDs en anti-parallèle, ~50 LEDs)
- **Capteur de mouvement** : PIR HC-SR501 ou RCWL-0516 (auto-détection)
- **Écran TFT ST7789** (optionnel)
- **LED RGB NeoPixel** WS2812B (optionnel)
- **Alimentation adaptée** pour la guirlande

### Schéma des pins principaux (ESP32 Classic)
TB6612FNG :
  PWMA  → GPIO 12
  AIN1  → GPIO 25
  AIN2  → GPIO 33
  STBY  → GPIO 14
MOTION_SENSOR_PIN (PIR/RCWL-0516) → GPIO 35
LCD_MOSI → GPIO 23
LCD_SCLK → GPIO 18
LCD_CS   → GPIO 15
LCD_DC   → GPIO 2
LCD_RST  → GPIO 4
LCD_BLK  → GPIO 32
BTN1     → GPIO 16
BTN2     → GPIO 17

---

## 2. Fonctionnalités principales

- Contrôle d'une guirlande LED avec ESP32 Classic
- 11 animations spectaculaires
- 2 modes de fonctionnement intelligents (Permanent, Détection Mouvement)
- Auto-détection PIR HC-SR501 ou RCWL-0516
- Affichage couleur ST7789 (optionnel)
- Interface web complète
- **Mise à jour OTA via interface Web** (nouveau v1.4.0)
- Contrôles physiques par boutons
- Configuration persistante (NVS)
- Mises à jour OTA (ArduinoOTA + Web)

---

## 3. Prérequis logiciels

- **PlatformIO** (extension VS Code ou CLI)
- **Python 3.x**
- **Git**

---

## 4. Installation

1. Cloner le projet
  ```bash
  git clone <votre-repo>
  cd LED-Garland-Anim
  ```
2. Configurer `include/secrets.h` (WiFi)
3. Dans `platformio.ini`, utiliser uniquement :
  - `esp32devkitc`: ESP32 Classic (4MB Flash)
4. Câbler les composants selon le schéma ci-dessus
5. Compiler et téléverser
  ```bash
  pio run -e esp32devkitc
  pio run -e esp32devkitc -t upload
  pio device monitor
  ```

---

## 5. Utilisation

### Démarrage
1. La guirlande démarre avec une **animation d'intro de 10 secondes** (Fade Alterné)
2. Après l'intro, elle bascule automatiquement vers l'animation et le mode sauvegardés
3. L'écran affiche la progression WiFi puis l'adresse IP
4. Accès web : `http://[IP_ESP32]`
5. **Note:** L'animation d'intro démarre immédiatement, même en mode détection

### Contrôles physiques
- **Bouton 1** : Animation suivante / mode auto
- **Bouton 2** : Changement de mode
- **Bouton BOOT** : Redémarrage (appui long)

### Interface web
- Tableau de bord, sélection animation/mode, visualisation capteurs, actions à distance
- **Confirmations inline** pour les opérations save/restore/erase (pas de popups bloquants)
- **Double-clic pour confirmer** le redémarrage (sécurité)

### Bot Telegram (optionnel)
- Commandes `/anim`, `/mode`, `/nextanim`, `/nextmode`, `/status`, `/liste`

---



## 6. Mises à jour OTA (Over-the-Air)

Voir le guide détaillé : [docs/OTA_UPDATE_FR.md](docs/OTA_UPDATE_FR.md)

Le firmware prend en charge **deux méthodes de mise à jour OTA** :

## 6. Mises à jour OTA (Over-the-Air)

Voir le guide détaillé : [docs/OTA_UPDATE_FR.md](docs/OTA_UPDATE_FR.md)

Le firmware prend en charge **deux méthodes de mise à jour OTA** :

### 6.1. Mise à jour OTA via Interface Web (Nouveau v1.4.0) ⭐

**La méthode la plus simple et recommandée !**

1. Compilez votre firmware avec PlatformIO :
   ```bash
   pio run -e esp32devkitc
   ```

2. Accédez à l'interface web de l'ESP32 : `http://[IP_ESP32]`

3. Cliquez sur le bouton **"⬆️ Mise à jour OTA"** dans le tableau de bord

4. Sur la page de mise à jour :
   - Cliquez sur **"📁 Sélectionner un fichier .bin"**
   - Naviguez vers `.pio/build/esp32devkitc/firmware.bin`
   - Cliquez sur **"🚀 Lancer la mise à jour"**

5. La progression s'affiche en temps réel :
   - Barre de progression dans le navigateur
   - Affichage du pourcentage sur l'écran ST7789
   - Messages de statut (succès/échec)

6. L'ESP32 redémarre automatiquement après une mise à jour réussie

**Avantages :**
- ✅ Interface graphique intuitive
- ✅ Pas besoin de commandes PlatformIO
- ✅ Fonctionne depuis n'importe quel navigateur (PC, smartphone, tablette)
- ✅ Affichage de la progression en temps réel
- ✅ Validation automatique du fichier

**⚠️ Important :** Ne débranchez pas l'appareil pendant la mise à jour !

### 6.2. Mise à jour OTA via ArduinoOTA (PlatformIO)

**Méthode traditionnelle pour les développeurs :**

1. Connectez l'ESP32 au WiFi
2. Dans PlatformIO, utilisez :
   ```bash
   pio run -e esp32devkitc -t upload --upload-port [IP_ESP32]
   ```
3. L'appareil apparaît comme `LED-Garland-Anim.local`
4. L'appareil redémarre automatiquement après la mise à jour

**Sécurité :** OTA n'est activé que lorsque l'ESP32 est connecté au WiFi.

---
## 7. Configuration avancée

Dans `include/config.h` :
```cpp
// #define HAS_OLED        // Commenter pour désactiver
// #define HAS_ST7789      // Commenter pour désactiver
```
Dans `include/garland_control.h` :
```cpp
#define MOTION_TRIGGER_DURATION 30000  // Durée en ms après détection
```

---

## 7. Spécifications techniques

- Guirlande LED : 2 fils, LEDs anti-parallèle, PWM 8 bits 5kHz
- TB6612FNG : double pont H, contrôle sens/intensité
- Capteurs : PIR (LOW repos, HIGH détection), RCWL-0516 (HIGH repos, LOW détection)
- Affichage : ST7789 1.14" 135x240px (optionnel)
- Mémoire : Flash 4MB, RAM ~500KB
- WiFi : 2.4GHz, auto-reconnexion, serveur web intégré

---

## 8. Dépannage

- Vérifier câblage, alimentation, configuration WiFi
- Voir [docs/TROUBLESHOOTING_FR.md](docs/TROUBLESHOOTING_FR.md)

---

## 9. Versions

**Version Actuelle : v1.5.0** (2025-12-31)
Voir [CHANGELOG_FR.md](./CHANGELOG_FR.md)

---

## 10. Documentation

- [Guide utilisateur](docs/USER_GUIDE_FR.md)
- [Architecture technique](docs/ARCHITECTURE_FR.md)
- [Mapping des pins](docs/PIN_MAPPING_FR.md)
- [Dépannage](docs/TROUBLESHOOTING_FR.md)
- [Notes de version](docs/RELEASE_NOTES_FR.md)

---

## 11. Contribution

1. Fork le projet
2. Créer une branche (`git checkout -b feature/amelioration`)
3. Commit les changements (`git commit -m 'Ajout fonctionnalité'`)
4. Push sur la branche (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request

---

## 12. Licence

Ce projet est fourni tel quel à des fins éducatives et personnelles.

---

## 13. Auteur

Projet ESP32 pour guirlandes LED bi-directionnelles avec animations avancées et modes intelligents.

---

## 14. Remerciements

- Équipe PlatformIO
- Adafruit (librairies GFX, NeoPixel, ST7789)
- Communauté ESP32
- Module TB6612FNG
## 🔧 Réglage du capteur PIR

Le capteur PIR (HC-SR501) permet de détecter les mouvements pour déclencher la guirlande.

### Réglages physiques sur le module PIR :
- **Sensibilité** :
  - Potentiomètre marqué "Sx" ou "Sens" sur le module.
  - Tourner dans le sens horaire pour augmenter la portée (jusqu’à ~6m), antihoraire pour réduire.
  - Adapter selon la taille de la pièce ou la distance souhaitée.
- **Temporisation** :
  - Potentiomètre marqué "Tx" ou "Time".
  - Permet de régler la durée pendant laquelle le signal reste actif après détection (de quelques secondes à plusieurs minutes).
  - Pour ce projet, la durée logicielle est gérée par le firmware, mais le réglage physique peut influencer le comportement.
- **Cavalier (Jumper)** :
  - Permet de choisir le mode de déclenchement :
    - **H** (répétition) : le signal reste actif tant qu’un mouvement est détecté.
    - **L** (non-répétitif) : le signal s’active une seule fois puis attend la fin de la temporisation avant de se réarmer.
  - Pour une détection continue, placer le cavalier sur "H".

### Conseils d’installation :
- Éviter les sources de chaleur ou de lumière directe (soleil, radiateur).
- Placer le capteur à hauteur d’homme pour une détection optimale.
- Tester la sensibilité et la temporisation selon l’environnement pour éviter les déclenchements intempestifs.
## 💾 Sauvegarde & Restauration Automatique (NVS)

Le projet sauvegarde et restaure automatiquement les paramètres suivants dans la mémoire non-volatile (NVS) :
- Mode actuel (permanent / détection mouvement)
- Animation en cours
- Intervalle du mode auto
- Durée d’animation sur détection

Au démarrage, si une configuration existe, elle est chargée automatiquement. Sinon, les valeurs par défaut sont utilisées. Tout changement via l’interface web ou les boutons est sauvegardé pour le prochain redémarrage.


# LED-Garland-Anim

**Version : 1.5.0**

Contrôleur d'animation de guirlande LED bi-directionnelle pour ESP32 IdeaSpark (ST7789)

Contrôlez une guirlande à 2 fils avec LEDs en anti-parallèle via un module TB6612FNG. 11 animations spectaculaires, mode Auto, 2 modes intelligents, affichage LCD ST7789, interface web, et contrôles physiques par boutons.

[🇬🇧 English version](README.md) | [📝 Journal des modifications](CHANGELOG_FR.md) | [📚 Documentation](docs/)

---


## Fonctionnalités

- Contrôle d'une guirlande LED avec une carte ESP32 (IdeaSpark)
- Écran LCD couleur (ST7789)
- Capteur de mouvement (PIR HC-SR501 ou RCWL-0516, détection automatique)
- Interface web de configuration
- Configuration persistante (NVS)
- Plusieurs modes d'animation
- Mises à jour OTA

### 🎄 11 Animations Spectaculaires de Guirlande
- **Éteint**: Guirlande désactivée
- **Fade Alterné**: Transition douce entre les deux sens de LEDs
- **Clignotement Alterné**: Alternance rapide entre Sens A et B
- **Pulsation**: Battement simultané des deux sens
- **Respiration**: Montée/descente lente de l'intensité
- **✨ Strobe**: Flash stroboscopique rapide
- **✨ Battement Cœur**: Double pulsation caractéristique (♥️ BOM-bom...)
- **✨ Vague**: Onde sinusoïdale fluide entre les directions
- **✨ Scintillement**: Effet de scintillement aléatoire
- **✨ Météore**: Traînée lumineuse avec estompage progressif
- **Mode Automatique**: Enchaînement de toutes les animations (30s chacune) avec **démarrage instantané** - aucune période vide

### 🎮 2 Modes de Fonctionnement Intelligents
- **Permanent**: Toujours allumé (par défaut au démarrage)
- **Détection Mouvement**: Déclenchement par capteur PIR (30s après détection mouvement)

### 🖥️ Affichage OLED en Temps Réel
- Affichage en direct des noms d'animation et de mode
- Adresse IP locale pour accès web
- Barre de visualisation animée (11 motifs distincts)
- Mise en page adaptative pour écrans 128x32 et 128x64
- Taux de rafraîchissement 10 FPS pour animations fluides

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

- **Multi-Cartes**: ESP32-S3 (N16R8, N8R8) et ESP32 Classic (DevKitC)
- **WiFiMulti**: Connexion automatique à plusieurs réseaux
- **Module TB6612FNG**: Contrôle bi-directionnel de la guirlande (GPIO : TB6612_PWMA, TB6612_AIN1, TB6612_AIN2, TB6612_STBY)
- **Capteur PIR**: Détection de mouvement HC-SR501 (GPIO : PIR_SENSOR)


---

## 📋 Prérequis

### Logiciels
- **PlatformIO** (extension VS Code ou CLI)
- **Python 3.x** (pour PlatformIO)
- **Git** (pour contrôle de version)



---

## 🛠️ Installation

### 1. Cloner le Projet
```bash
git clone <votre-repo>
cd LED-Garland-Anim
```
**Version 1.5.0** - Contrôleur d'animation de guirlande LED bi-directionnelle pour ESP32 IdeaSpark (ST7789)
### 2. Configurer `include/secrets.h`
Éditez `include/secrets.h` pour définir vos réseaux WiFi.

Exemple :
 **Détection Mouvement**: Déclenchement par capteur de mouvement (PIR ou RCWL-0516, 30s après détection)
#define WIFI_SSID_1 "YourNetwork"
# 🚦 Détection automatique du capteur de mouvement (v1.2.1)

À partir de la version 1.2.1, le système détecte automatiquement si un capteur PIR (HC-SR501) ou un capteur radar Doppler (RCWL-0516) est connecté sur le GPIO 35 :
- **PIR** : LOW au repos, HIGH sur détection
- **RCWL-0516** : HIGH au repos, LOW sur détection

Le firmware adapte la logique de détection en conséquence. Aucune configuration n’est requise : il suffit de connecter le capteur souhaité sur le GPIO 35.

Voir docs/PIR_SENSOR_SETUP_FR.md et docs/RADAR_SENSOR_SETUP_FR.md pour le câblage et les réglages.
#define WIFI_PASS_1 "YourPassword"
```
**Capteur de mouvement**: Détection automatique PIR (HC-SR501) ou RCWL-0516 (GPIO : MOTION_SENSOR_PIN)
### 3. Configurer PlatformIO
  MOTION_SENSOR_PIN   → GPIO 35
  MOTION_SENSOR_PIN   → GPIO 14
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
  PWMA  → GPIO 12
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
3. Une fois connecté, l'adresse IP s'affiche sur l'OLED et l'interface web
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
│   ├── secrets.h             # Réseaux WiFi
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
- **RCWL-0516** : Signal digital (LOW = mouvement détecté)

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

**Version Actuelle : v1.5.0** (2025-12-31)

Voir [CHANGELOG_FR.md](./CHANGELOG_FR.md) pour l'historique complet.

---


## Documentation

- [Guide utilisateur](docs/USER_GUIDE_FR.md)
- [Architecture technique](docs/ARCHITECTURE_FR.md)
- [Mapping des pins](docs/PIN_MAPPING_FR.md)
- [Dépannage](docs/TROUBLESHOOTING_FR.md)
- [Notes de version](docs/RELEASE_NOTES_FR.md)

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
