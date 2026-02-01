## Choisir entre upload USB ou OTA

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

**Version : 5.6.3** (2026-02-01)


Contrôleur d'animation de guirlande LED bi-directionnelle et matrice NeoPixel 8x8 pour **ESP32 Classic** (IdeaSpark/DevKitC), **ESP32 Wroom**, **ESP32-S3 Mini**, **ESP32-S3 Super Mini** — toutes plateformes compatibles avec l'affichage **OLED SSD1306 (I2C)** si connecté (voir les broches par carte dans le guide de mapping). Auto-détection PIR/RCWL-0516, **interface web modernisée avec sauvegarde instantanée**, layout responsive, mises à jour AJAX sans flash, mises à jour OTA via web, **support mDNS pour un accès facile via nom unique**, commandes physiques : BOOT + 1 bouton utilisateur (voir ci-dessous), 11 animations de guirlande, plusieurs animations festives pour matrice, contrôle double indépendant, modes intelligents, configuration persistante, animations de démarrage automatiques.

## ✨ Nouveautés v5.2.0

1. **Support ESP32-C3 HW-675 (MINEUR)** - Nouvelle plateforme matérielle avec écran OLED 0.42" (72×40 px)
2. **Affichage OLED universel** - Affichage IP + Mode sur OLED SSD1306 (I2C), disponible sur toutes les plateformes si branché
3. **Fonctionnalité bouton BOOT** - Changement de mode (clic) et redémarrage système (appui long)
4. **Diagnostics I2C** - Détection automatique des périphériques au démarrage
5. **Compatibilité multi-cartes** - Support transparent des architectures ESP32 Classic et ESP32-C3

Voir [CHANGELOG_FR.md](./CHANGELOG_FR.md) pour les versions précédentes.

## ✨ Nouveautés v3.0.0

### 💥 Réorganisation Complète des Cartes de l'Interface Web (BREAKING CHANGE)
- **Nouveau flux de navigation** - Ordre des cartes complètement restructuré pour une meilleure UX
- **Animations prioritaires** - Animations Guirlande et Matrice maintenant en haut (plus fréquemment consultées)
- **Carte Mode 3 zones** - Mode + mode d’écran côte à côte, tous paramètres dessous en section unifiée
- **Mode écran intégré** - Mode d'affichage écran maintenant dans carte Mode (carte séparée supprimée)
- **Paramètres consolidés** - Tous paramètres temporels + luminosité matrice en un seul endroit
- **Défilement réduit** - Disposition plus compacte avec regroupement logique

### 📋 Nouvel Ordre des Cartes (v3.0.0)
1. 🎄 **Animations Guirlande** - Toutes les animations guirlande (était Carte 2)
2. 🎨 **Matrice 8x8** - Toutes les animations matrice (était Carte 3)
3. 🎯 **Mode de fonctionnement** - Disposition 3 zones :
   - Zone A (gauche) : Sélection mode (Auto/Manuel/Détection)
  - Zone B (droite) : Mode affichage écran (était Carte 4 séparée)
   - Zone C (dessous) : Tous paramètres temporels + luminosité matrice
4. ℹ️ **Système & Réseau** - Informations système et réseau
5. 🏷️ **Nom d'appareil** - Configuration nom d'appareil

### 🎨 Design Amélioré de la Carte Mode
**Disposition Côte à Côte** (CSS Grid) :
- **Moitié gauche** : Sélection mode de fonctionnement (Auto | Manuel | Détection mouvement)
- **Moitié droite** : Mode affichage écran (Animation + matrice | Animation seule | Écran éteint)
- **Pleine largeur dessous** : Tous paramètres temporels (durée mouvement, intervalle guirlande, intervalle matrice) + luminosité matrice

**Avantages** :
- Toute la configuration en un seul endroit
- Défilement vertical réduit
- Meilleure hiérarchie visuelle
- Regroupement logique des paramètres

---

## Versions Précédentes

### v2.0.0 (2026-01-06) - Refonte Complète de l'Interface
- **Sauvegarde instantanée sur tous les contrôles** - Plus de boutons "Appliquer" ! Les changements prennent effet immédiatement
- **Curseurs modernes** - Tous les intervalles temporels utilisent des sliders avec affichage en temps réel
- **Notifications centralisées** - Barre de notification fixe en haut pour toutes les confirmations
- **Regroupement logique** - Tous les paramètres temporels regroupés dans la carte "Mode de fonctionnement"
- **Corrections de Bugs Critiques** :
  1. **Mode écran éteint** - L'affichage efface maintenant les pixels avant de couper le rétro-éclairage
  2. **Démarrage auto matrice** - Le mode auto s'active correctement au démarrage avec les paramètres sauvegardés

---



## Plateformes matérielles supportées

- **ESP32 Classic (IdeaSpark/DevKitC)**
- **ESP32 Wroom**
- **ESP32-S3 Mini** (esp32s3_mini)
- **ESP32-S3 Super Mini** (esp32s3_supermini)

> 📌 **Affichage OLED SSD1306 (I2C) disponible sur toutes les plateformes si connecté. Voir les broches par carte dans le guide de mapping.**

#### Composants requis (toutes plateformes)
- **Module TB6612FNG** (double pont H)
- **Écran OLED SSD1306 (I2C)** (optionnel mais supporté sur toutes plateformes ; voir broches par carte)
- **Guirlande LED 2 fils** (LEDs en anti-parallèle, ~50 LEDs)
- **Matrice NeoPixel 8x8 WS2812B-64** (64 LEDs RGB adressables)
- **Capteur de mouvement** : PIR HC-SR501 ou RCWL-0516 (auto-détection)
- **Écran OLED SSD1306 (I2C)** (optionnel)
- **Alimentation adaptée** pour la guirlande et la matrice (5V recommandé pour NeoPixels)

*Ce document est valide à partir de la version 5.6.3.*

## 1. Matériel requis

### ESP32 Classic (IdeaSpark/DevKitC)
- **Carte ESP32 Classic (IdeaSpark/DevKitC)**
- **Module TB6612FNG** (double pont H)
- **Guirlande LED 2 fils** (LEDs en anti-parallèle, ~50 LEDs)
- **Matrice NeoPixel 8x8 WS2812B-64** (64 LEDs RGB adressables)
- **Capteur de mouvement** : PIR HC-SR501 ou RCWL-0516 (auto-détection)
- **Écran OLED SSD1306 (I2C)** (optionnel)
- **Alimentation adaptée** pour la guirlande et la matrice (5V recommandé pour NeoPixels)

### ESP32 Wroom (NOUVEAU en v5.3.1)
- **Carte ESP32 Wroom**
- **Module TB6612FNG** (double pont H)
- **Guirlande LED 2 fils** (LEDs en anti-parallèle, ~50 LEDs)
- **Matrice NeoPixel 8x8 WS2812B-64** (64 LEDs RGB adressables)
- **Capteur de mouvement** : PIR HC-SR501 ou RCWL-0516 (auto-détection)
- **Écran OLED SSD1306 (I2C)** (optionnel)
- **Alimentation adaptée** pour la guirlande et la matrice (5V recommandé pour NeoPixels)

### ESP32-S3 Mini
- **Carte ESP32-S3 Mini**
- **Module TB6612FNG** (double pont H)
- **Guirlande LED 2 fils** (LEDs en anti-parallèle, ~50 LEDs)
- **Matrice NeoPixel 8x8 WS2812B-64** (64 LEDs RGB adressables)
- **Écran OLED SSD1306 (I2C)** (optionnel)
- **Capteur de mouvement** : PIR HC-SR501 ou RCWL-0516 (auto-détection)
- **Alimentation adaptée** pour la guirlande et la matrice (5V recommandé pour NeoPixels)

### Schéma des pins principaux (ESP32 Classic)
```
TB6612FNG (Guirlande) :

### Schéma des pins principaux

#### ESP32 Classic (IdeaSpark/DevKitC)
```
TB6612FNG (Guirlande) :
  PWMA  → GPIO 12
  AIN1  → GPIO 25
  AIN2  → GPIO 33
  STBY  → GPIO 14
Matrice NeoPixel 8x8 :
  DATA  → GPIO 27
MOTION_SENSOR_PIN (PIR/RCWL-0516) → GPIO 35
OLED I2C :
  SDA   → GPIO 21
  SCL   → GPIO 22
BTN1     → GPIO 16 (Bouton utilisateur)
BOOT     → GPIO 0  (Boot/Reset)
```

#### ESP32 Wroom
```
TB6612FNG (Guirlande) :
  PWMA  → GPIO 12
  AIN1  → GPIO 25
  AIN2  → GPIO 33
  STBY  → GPIO 14
Matrice NeoPixel 8x8 :
  DATA  → GPIO 27
MOTION_SENSOR_PIN (PIR/RCWL-0516) → GPIO 35
OLED I2C :
  SDA   → GPIO 21
  SCL   → GPIO 22
BTN1     → GPIO 16 (Bouton utilisateur)
BOOT     → GPIO 0  (Boot/Reset)
```

#### ESP32-S3 Mini / Super Mini
```
TB6612FNG (Guirlande) :
  PWMA  → GPIO 10
  AIN1  → GPIO 11
  AIN2  → GPIO 12
  STBY  → GPIO 13
Matrice NeoPixel 8x8 :
  DATA  → GPIO 7
MOTION_SENSOR_PIN (PIR/RCWL-0516) → GPIO 7
OLED I2C :
  SDA   → GPIO 4
  SCL   → GPIO 5
BTN1     → GPIO 8 (Bouton utilisateur)
BOOT     → GPIO 0  (Boot/Reset)
```

---

## 2. Fonctionnalités principales
- **Animations** : 11 pour la guirlande + plusieurs animations festives pour la matrice 8x8
- **3 modes d’affichage OLED** :
  - **Animé** : Écran d'informations OLED (nom, version, IP, mode, animations)
  - **Statique** : Même informations sans animation
  - **Éteint** : Écran éteint
- **Sélection du mode d’affichage** :
  - Sélection à la volée depuis l’UI web (boutons radio)
  - Valeur par défaut configurable dans `config.h`
  - Persistance automatique (NVS, restauré au boot)
  - Effet immédiat, sans reboot
- **37 animations pour matrice** organisées par thème :
  - **Originales (10)** : Étoile, Météore, Étoile filante, Père Noël, Sapin, Cloche, Neige, Cadeau, Bougie, Flocon
  - **Noël (10)** : Canne à sucre, Couronne, Chaussette, Renne, Pain d'épices, Chocolat chaud, Cheminée, Glaçons, Aurore boréale, Cadeaux
  - **Nouvel An (7)** : Feux d'artifice, Champagne, Compte à rebours, Confettis, Horloge, Cotillon, Boule disco
  - **Pâques (4)** : Œuf de Pâques, Lapin, Poussin, Fleurs
  - **Moderne/Abstrait (6)** : Vague arc-en-ciel, Pluie scintillante, Plasma, Pluie matricielle, Spirale, Cœur, Champ d'étoiles
- **Contrôle de luminosité de la matrice** : Ajustement indépendant (0-255) pour la matrice
- **Animation de démarrage** : Animation d'étoile scintillante sur la matrice au démarrage
- **3 Modes de Fonctionnement Intelligents** : Permanent (tout allumé), Détection (tout suit mouvement), Détection Indépendante (guirlande suit mouvement, matrice toujours allumée)
- Auto-détection PIR HC-SR501 ou RCWL-0516
- Affichage OLED SSD1306 (128x64 ou 128x32 via config)
- Interface web complète avec contrôles pour la matrice
- **Mise à jour OTA via interface Web** (nouveau v1.4.0)
- Contrôles physiques par boutons
- Configuration persistante (NVS) pour guirlande et matrice
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
3. Dans `platformio.ini`, choisir votre environnement :
  - `esp32devkitc`: ESP32 Classic (4MB Flash)
  - `esp32wroom`: ESP32 Wroom (DevKit V1)
  - `esp32s3_mini`: ESP32-S3 Mini
  - `esp32s3_supermini`: ESP32-S3 Super Mini
4. Câbler les composants selon le schéma ci-dessus
5. Compiler et téléverser
  ```bash
  # Pour ESP32 Classic :
  pio run -e esp32devkitc
  pio run -e esp32devkitc -t upload
  
  # Pour ESP32-S3 Mini :
  pio run -e esp32s3_mini
  pio run -e esp32s3_mini -t upload

  # Pour ESP32-S3 Super Mini :
  pio run -e esp32s3_supermini
  pio run -e esp32s3_supermini -t upload
  
  # Moniteur série :
  pio device monitor
  ```

---

## 5. Interface Web et Accès Réseau

### 5.1. Accès à l'Interface Web

L'appareil est accessible de **deux manières** :

1. **Via l'adresse IP** (méthode traditionnelle) :
   ```
   http://192.168.x.x
   ```
   Trouvez l'adresse IP de votre ESP32 dans :
   - La sortie du moniteur série
  - L'écran OLED (si connecté)
   - La liste des appareils connectés de votre routeur

2. **Via le nom mDNS** (recommandé) 🆕 :
   ```
   http://garland.local
   ```
   - Plus besoin de mémoriser les adresses IP !
   - Fonctionne sur la plupart des appareils (Windows 10+, macOS, Linux, iOS, Android)
   - **Nom par défaut** : `garland` (personnalisable)

### 5.2. Personnalisation du Nom d'Appareil

Vous pouvez changer le nom mDNS directement depuis l'interface web :

1. Accédez à l'interface web (`http://garland.local` ou `http://[IP]`)
2. Faites défiler jusqu'à la section **"🏷️ Nom d'appareil (mDNS)"**
3. Entrez le nom souhaité (alphanumérique, tiret, underscore, max 32 caractères)
4. Cliquez sur **"Appliquer"**
5. Votre appareil est maintenant accessible via `http://[votre-nom].local`

**Exemples :**
- `lumieres-noel.local`
- `led-salon.local`
- `sapin-noel.local`

**Configuration sauvegardée automatiquement** en mémoire non-volatile (NVS).

### 5.3. Fonctionnalités de l'Interface Web

- **Interface Web**
  - UI moderne avec boutons radio pour toutes les sélections
  - Layout responsive (2 colonnes desktop, 1 colonne mobile)
  - Mises à jour instantanées, sans rechargement de page
  - **Mode d'affichage** : Sélection Animé, Statique, Éteint (effet immédiat)
  - **Configuration du Nom** : Changement du nom mDNS à la volée
  - Tous les réglages (animation, mode, affichage, durées, nom) sont persistants et restaurés au boot
  - Informations réseau visibles dans le tableau de bord (SSID, IP, mDNS)
  - Actions Sauvegarder/Restaurer/Effacer la configuration
  - **Affichage OLED** : nom, version, IP, mode et animations

---

## 6. Utilisation

### Démarrage
1. La guirlande démarre avec une **animation d'intro de 10 secondes** (Fade Alterné)
2. Après l'intro, elle bascule automatiquement vers l'animation et le mode sauvegardés
3. L'écran affiche la progression WiFi puis l'adresse IP
4. Accès web : `http://garland.local` (ou `http://[IP_ESP32]`)
5. **Note:** L'animation d'intro démarre immédiatement, même en mode détection

### Contrôles physiques
- **Bouton utilisateur** :
  - 1 clic : animation suivante guirlande
  - 2 clics : animation suivante matrice
  - appui long : changement de mode global
- **Bouton BOOT** : Redémarrage (appui long)

**Note OLED** : Nom du projet, version, IP, mode et animations sont affichés à l’écran.


## 7. Mises à jour OTA (Over-the-Air)

Voir le guide détaillé : [docs/OTA_UPDATE_FR.md](docs/OTA_UPDATE_FR.md)

Le firmware prend en charge **deux méthodes de mise à jour OTA** :

### 7.1. Mise à jour OTA via Interface Web (Nouveau v1.4.0) ⭐

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
  - Messages de statut (succès/échec)

6. L'ESP32 redémarre automatiquement après une mise à jour réussie

**Avantages :**
- ✅ Interface graphique intuitive
- ✅ Pas besoin de commandes PlatformIO
- ✅ Fonctionne depuis n'importe quel navigateur (PC, smartphone, tablette)
- ✅ Affichage de la progression en temps réel
- ✅ Validation automatique du fichier

**⚠️ Important :** Ne débranchez pas l'appareil pendant la mise à jour !

### 7.2. Mise à jour OTA via ArduinoOTA (PlatformIO)

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
## 8. Configuration avancée

Dans `include/config.h` :
```cpp
// #define HAS_OLED_U8G2   // Commenter pour désactiver l'OLED
```
Dans `include/garland_control.h` :
```cpp
#define MOTION_TRIGGER_DURATION 30000  // Durée en ms après détection
```

---

## 9. Spécifications techniques

- Guirlande LED : 2 fils, LEDs anti-parallèle, PWM 8 bits 5kHz
- TB6612FNG : double pont H, contrôle sens/intensité
- Capteurs : PIR (LOW repos, HIGH détection), RCWL-0516 (HIGH repos, LOW détection)
- Affichage : OLED SSD1306 (I2C), 128x64 ou 128x32 (configurable)
- Mémoire : Flash 4MB, RAM ~500KB
- WiFi : 2.4GHz, auto-reconnexion, serveur web intégré

---

## 10. Dépannage

- Vérifier câblage, alimentation, configuration WiFi
- Voir [docs/TROUBLESHOOTING_FR.md](docs/TROUBLESHOOTING_FR.md)

---

## 11. Versions

**Version Actuelle : v5.6.3** (2026-02-01)
Voir [CHANGELOG_FR.md](./CHANGELOG_FR.md)

---

## 12. Documentation

- [Guide utilisateur](docs/USER_GUIDE_FR.md)
- [Architecture technique](docs/ARCHITECTURE_FR.md)
- [Mapping des pins](docs/PIN_MAPPING_FR.md)
- [Dépannage](docs/TROUBLESHOOTING_FR.md)
- [Notes de version](docs/RELEASE_NOTES_FR.md)

---

## 13. Contribution

1. Fork le projet
2. Créer une branche (`git checkout -b feature/amelioration`)
3. Commit les changements (`git commit -m 'Ajout fonctionnalité'`)
4. Push sur la branche (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request

---

## 14. Licence

Ce projet est fourni tel quel à des fins éducatives et personnelles.

---

## 15. Auteur

Projet ESP32 pour guirlandes LED bi-directionnelles avec animations avancées et modes intelligents.

---

## 16. Remerciements

- Équipe PlatformIO
- Adafruit (librairies NeoPixel et U8g2)
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
