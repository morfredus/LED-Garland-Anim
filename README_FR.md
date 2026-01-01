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

**Version : 1.10.0** (2026-01-01)

Contrôleur d'animation de guirlande LED bi-directionnelle et matrice NeoPixel 8x8 pour ESP32 Classic (IdeaSpark/DevKitC) avec écran ST7789, auto-détection PIR/RCWL-0516, interface web modernisée avec boutons radio, layout responsive et mises à jour AJAX sans flash, boutons physiques, 11 animations de guirlande, 39 animations festives pour matrice (Noël, Nouvel An, Pâques, Feu de Camp, Radar), contrôle double indépendant, modes intelligents, configuration persistante, animations de démarrage automatiques.

---

## 1. Matériel requis

- **Carte ESP32 Classic (IdeaSpark/DevKitC)**
- **Module TB6612FNG** (double pont H)
- **Guirlande LED 2 fils** (LEDs en anti-parallèle, ~50 LEDs)
- **Matrice NeoPixel 8x8 WS2812B-64** (64 LEDs RGB adressables)
- **Capteur de mouvement** : PIR HC-SR501 ou RCWL-0516 (auto-détection)
- **Écran TFT ST7789** (optionnel, intégré sur IdeaSpark)
- **Alimentation adaptée** pour la guirlande et la matrice (5V recommandé pour NeoPixels)

### Schéma des pins principaux (ESP32 Classic)
TB6612FNG (Guirlande) :
  PWMA  → GPIO 12
  AIN1  → GPIO 25
  AIN2  → GPIO 33
  STBY  → GPIO 14
Matrice NeoPixel 8x8 :
  DATA  → GPIO 13
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

- **Double contrôle LED** : Guirlande LED 2 fils + matrice NeoPixel 8x8 avec contrôle indépendant
- **48 animations au total** : 11 pour la guirlande + 37 animations festives pour la matrice 8x8
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
- Affichage couleur ST7789 (optionnel, intégré sur IdeaSpark)
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

## 8. Spécifications techniques

- Guirlande LED : 2 fils, LEDs anti-parallèle, PWM 8 bits 5kHz
- TB6612FNG : double pont H, contrôle sens/intensité
- Capteurs : PIR (LOW repos, HIGH détection), RCWL-0516 (HIGH repos, LOW détection)
- Affichage : ST7789 1.14" 135x240px (optionnel)
- Mémoire : Flash 4MB, RAM ~500KB
- WiFi : 2.4GHz, auto-reconnexion, serveur web intégré

---

## 9. Dépannage

- Vérifier câblage, alimentation, configuration WiFi
- Voir [docs/TROUBLESHOOTING_FR.md](docs/TROUBLESHOOTING_FR.md)

---

## 10. Versions

**Version Actuelle : v1.11.2** (2026-01-01)
Voir [CHANGELOG_FR.md](./CHANGELOG_FR.md)

---

## 11. Documentation

- [Guide utilisateur](docs/USER_GUIDE_FR.md)
- [Architecture technique](docs/ARCHITECTURE_FR.md)
- [Mapping des pins](docs/PIN_MAPPING_FR.md)
- [Dépannage](docs/TROUBLESHOOTING_FR.md)
- [Notes de version](docs/RELEASE_NOTES_FR.md)

---

## 12. Contribution

1. Fork le projet
2. Créer une branche (`git checkout -b feature/amelioration`)
3. Commit les changements (`git commit -m 'Ajout fonctionnalité'`)
4. Push sur la branche (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request

---

## 13. Licence

Ce projet est fourni tel quel à des fins éducatives et personnelles.

---

## 14. Auteur

Projet ESP32 pour guirlandes LED bi-directionnelles avec animations avancées et modes intelligents.

---

## 15. Remerciements

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
