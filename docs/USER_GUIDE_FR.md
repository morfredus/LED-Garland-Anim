## Sauvegarde et restauration de la configuration (NVS)

Le système utilise la NVS (mémoire non-volatile) de l’ESP32 pour sauvegarder et restaurer automatiquement les paramètres utilisateur :

- **Mode** (permanent ou détection de mouvement)
- **Animation en cours**
- **Intervalle du mode auto**
- **Durée d’animation sur détection**

**Fonctionnement :**
- Au démarrage, la dernière configuration sauvegardée est chargée si elle existe, sinon les valeurs par défaut sont utilisées.
- Toute modification via l’interface web ou les boutons est sauvegardée immédiatement.
- Les réglages sont conservés même après redémarrage ou coupure d’alimentation.

**Aucune action requise de l’utilisateur** : la gestion est entièrement automatique.
# Guide Utilisateur - LED-Garland-Anim v1.11.3
## 🚦 Détection automatique du capteur de mouvement (v1.11.3)

À partir de la version 1.11.0, le système détecte automatiquement si un capteur PIR (HC-SR501) ou un capteur radar Doppler (RCWL-0516) est connecté sur le GPIO 35 :
- **PIR** : LOW au repos, HIGH sur détection
- **RCWL-0516** : HIGH au repos, LOW sur détection

Le firmware adapte la logique de détection en conséquence. Aucune configuration n’est requise : il suffit de connecter le capteur souhaité sur le GPIO 35.

Voir docs/PIR_SENSOR_SETUP_FR.md et docs/RADAR_SENSOR_SETUP_FR.md pour le câblage et les réglages.

Guide utilisateur complet pour le contrôleur d'animation de guirlande LED (ESP32 IdeaSpark + ST7789).

---

## Table des Matières

- [Guide Utilisateur - LED-Garland-Anim v1.11.3](#guide-utilisateur---led-garland-anim-v121)
  - [🚦 Détection automatique du capteur de mouvement (v1.11.3)](#-détection-automatique-du-capteur-de-mouvement-v121)
  - [Table des Matières](#table-des-matières)
  - [Mises à jour OTA](#mises-à-jour-ota)
  - [Premier Démarrage](#premier-démarrage)
    - [À Quoi S'attendre](#à-quoi-sattendre)
    - [Notez Votre Adresse IP](#notez-votre-adresse-ip)
  - [Contrôles Physiques](#contrôles-physiques)
    - [Emplacements des Boutons](#emplacements-des-boutons)
  - [Interface Web](#interface-web)
  - [Affichage LCD ST7789](#affichage-lcd-st7789)
  - [Modes de Fonctionnement](#modes-de-fonctionnement)
  - [Animations](#animations)
  - [Utilisation Quotidienne](#utilisation-quotidienne)
  - [Dépannage](#dépannage)

## Mises à jour OTA

Voir le guide détaillé OTA : [docs/OTA_UPDATE_FR.md](OTA_UPDATE_FR.md)

Depuis la version 1.11.0, le firmware prend en charge les mises à jour OTA (Over-the-Air) via ArduinoOTA.

**Utilisation :**
1. Connectez l’ESP32 au WiFi.
2. Dans PlatformIO ou Arduino IDE, sélectionnez « Upload using OTA » (l’appareil apparaît comme `LED-Garland-Anim.local`).
3. L’appareil redémarre automatiquement après une mise à jour réussie.

**Sécurité :** OTA n’est activé que lorsque l’ESP32 est connecté au WiFi.

---

## Premier Démarrage

### À Quoi S'attendre
1. **LCD ST7789** affiche "Connexion WiFi..."
2. **LED_BUILTIN** clignote en bleu pendant la connexion WiFi
3. Après connexion, **adresse IP** affichée pendant 3 secondes
4. **Guirlande** joue une animation d'intro de 10 secondes (Fade Alterné), puis bascule vers l'animation/mode sauvegardé
5. **LED_BUILTIN** devient verte quand prête

### Notez Votre Adresse IP
Notez l'adresse IP affichée sur l'écran LCD ou consultez la liste DHCP de votre routeur. Vous en aurez besoin pour accéder à l'interface web.

Exemple : `192.168.1.100`

---

## Contrôles Physiques

### Emplacements des Boutons
- **BUTTON_BOOT** : GPIO 0 (sur la carte)
- **BUTTON_1** : GPIO 16 (changement animation)
- **BUTTON_2** : GPIO 17 (changement mode)

---

## Interface Web
- Accès via l'adresse IP affichée sur le LCD
- Tableau de bord : infos système, mémoire, WiFi
- Contrôle guirlande : sélection animation/mode
- Visualisation capteurs

---

## Affichage LCD ST7789
- Écran couleur 1.14" 135x240px
- Écran de démarrage moderne : nom projet, version, progression WiFi
- Interface principale : en-têtes centrés, infos compactes, grande zone d'animation
- 11 visualisations animées (une par animation)
- Mises à jour temps réel à 10 FPS

---

## Modes de Fonctionnement
- **Permanent** : Toujours allumé (par défaut)
- **Détection Mouvement** : Activation par capteur PIR (30s après mouvement)

---

## Animations
- Éteint, Fade Alterné, Clignotement Alterné, Pulsation, Respiration, Strobe, Battement Cœur, Vague, Scintillement, Météore, Auto (enchaînement)

---

## Utilisation Quotidienne
- Changer animation/mode avec les boutons ou l'interface web
- Suivre l'état sur le LCD et le tableau de bord web

---

## Dépannage
Voir [TROUBLESHOOTING_FR.md](TROUBLESHOOTING_FR.md) pour l'aide.

---

**Version du document : v1.11.3 (2025-12-31)**
