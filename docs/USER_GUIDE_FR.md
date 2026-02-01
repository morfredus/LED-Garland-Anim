## Sauvegarde et restauration de la configuration (NVS)
# Guide Utilisateur - LED-Garland-Anim v5.6.3

Ce guide explique comment utiliser et configurer le projet LED-Garland-Anim. Il est valable à partir de la version 5.6.3.


**Fonctionnement :**
- Au démarrage, la dernière configuration sauvegardée est chargée si elle existe, sinon les valeurs par défaut sont utilisées.
- Toute modification via l'interface web ou les boutons est sauvegardée immédiatement.
- Les réglages sont conservés même après redémarrage ou coupure d'alimentation.

**Aucune action requise de l'utilisateur** : la gestion est entièrement automatique.


# Guide Utilisateur - LED-Garland-Anim v5.6.3
**Version du document : v5.6.3 (2026-02-01)**
- ESP32 Wroom
- ESP32-S3 Mini (esp32s3_mini)
- ESP32-S3 Super Mini (esp32s3_supermini)

> 📌 **Affichage OLED SSD1306 (I2C) supporté sur toutes les plateformes si connecté (voir broches par carte dans PIN_MAPPING)**

Guide utilisateur complet pour le contrôleur d'animation de guirlande LED (ESP32 Classic IdeaSpark/DevKitC, ESP32 Wroom, ESP32-S3 Mini, ESP32-S3 Super Mini) — toutes plateformes compatibles OLED SSD1306 (I2C).

**Version du document : v5.6.3 (2026-02-01)**

- [Guide Utilisateur - LED-Garland-Anim v5.3.0](#guide-utilisateur---led-garland-anim-v530)
- [Guide Utilisateur - LED-Garland-Anim v5.3.2](#guide-utilisateur---led-garland-anim-v532)
  - [Mises à jour OTA](#mises-à-jour-ota)
  - [Premier Démarrage](#premier-démarrage)
    - [À Quoi S'attendre](#à-quoi-sattendre)
    - [Notez Votre Adresse IP](#notez-votre-adresse-ip)
  - [Contrôles Physiques](#contrôles-physiques)
    - [Emplacements des Boutons](#emplacements-des-boutons)
  - [Interface Web](#interface-web)
  - [Affichage OLED SSD1306 (I2C)](#affichage-oled-ssd1306-i2c)
  - [Modes de Fonctionnement](#modes-de-fonctionnement)
  - [Animations](#animations)
  - [Animation Horloge (à partir de v5.3.2)](#animation-horloge-à-partir-de-v532)
    - [⚠️ Important : Les modes AUTO guirlande et matrice sont indépendants (v5.1.1)](#️-important--les-modes-auto-guirlande-et-matrice-sont-indépendants-v511)
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
1. **OLED SSD1306 (I2C)** affiche "Connexion WiFi..."
2. **LED_BUILTIN** clignote en bleu pendant la connexion WiFi
3. Après connexion, **adresse IP** affichée pendant 3 secondes
4. **Guirlande** joue une animation d'intro de 10 secondes (Fade Alterné), puis bascule vers l'animation/mode sauvegardé
5. **LED_BUILTIN** devient verte quand prête

### Notez Votre Adresse IP
Notez l'adresse IP affichée sur l'écran OLED ou consultez la liste DHCP de votre routeur. Vous en aurez besoin pour accéder à l'interface web.

Exemple : `192.168.1.100`

---

## Contrôles Physiques


### Emplacements des Boutons (depuis v5.3.4)
- **BOUTON BOOT** : GPIO 0 (sur la carte)
- **BOUTON UTILISATEUR** : GPIO 16 (panneau avant ou externe)

### Fonctions des Boutons (depuis v5.3.4)
- **BOUTON UTILISATEUR (GPIO 16) :**
  - 1 clic : animation suivante guirlande
  - 2 clics : animation suivante matrice
  - appui long : changement de mode global
- **BOUTON BOOT (GPIO 0) :** Appui long = redémarrage (inchangé)

---


## Interface Web
- Accès via l'adresse IP affichée sur l'OLED
- Tableau de bord : infos système, mémoire, WiFi
- Contrôle guirlande : sélection animation/mode
- **Sélection du mode d’affichage écran** (Animé, Statique, Éteint)
- Visualisation capteurs
- Actions Sauvegarder/Restaurer/Effacer la configuration

---



## Affichage OLED SSD1306 (I2C)

- **Écran monochrome 128x64 ou 128x32** (SSD1306, I2C)
- **Affichage universel** : supporté sur toutes les plateformes si connecté (voir broches par carte dans PIN_MAPPING)
- **Écran de démarrage** : nom du projet, version, progression WiFi
- **Écran principal** : nom du projet, version, adresse IP, mode, animations guirlande + matrice
- **Sélection du mode d'affichage** (Animé, Statique, Éteint) depuis l'interface web
- **Persistance automatique** (NVS, restauré au boot)
- **Effet immédiat, sans reboot**

---

## Modes de Fonctionnement
- **Permanent** : Toujours allumé (par défaut)
- **Détection Mouvement** : Activation par capteur PIR (30s après mouvement)

---

## Animations
- Éteint, Fade Alterné, Clignotement Alterné, Pulsation, Respiration, Strobe, Battement Cœur, Vague, Scintillement, Météore, Auto (enchaînement)

## Animation Horloge (à partir de v5.3.2)

Une animation horloge analogique est disponible sur la matrice 8x8. Elle affiche une trotteuse rouge réaliste :
- **Mouvement fluide** : la trotteuse avance de façon continue, sans à-coups, pour un rendu naturel.
- **Effet d’inertie** : la trotteuse présente un léger rebond à chaque seconde, imitant le comportement d’une horloge mécanique haut de gamme.
- **Longueur ajustée** : l’aiguille atteint le bord du cadran pour une meilleure lisibilité.
- **Synchronisation** : la trotteuse effectue un tour complet en 60 secondes, calée sur le temps système.

Cette animation est accessible dans la liste des animations matrice via l’interface web ou les boutons physiques.

---

### ⚠️ Important : Les modes AUTO guirlande et matrice sont indépendants (v5.1.1)
Depuis la version 5.1.1, la **guirlande** et la **matrice** possèdent des **intervalles de mode AUTO séparés** :

- **Mode AUTO guirlande** : Utilise le paramètre « Intervalle du mode auto » de l'interface web
- **Mode AUTO matrice** : Utilise le paramètre « Intervalle d'animation matrice » de l'interface web
- Les deux peuvent fonctionner simultanément avec des durées de cycle d'animation différentes
- Chaque intervalle est sauvegardé indépendamment et restauré au redémarrage

**Exemple :** La guirlande change d'animation toutes les 20 secondes tandis que la matrice change toutes les 45 secondes.

---

## Utilisation Quotidienne
- Changer animation/mode avec les boutons ou l'interface web
- Suivre l'état sur l'OLED et le tableau de bord web

---

## Dépannage
Voir [TROUBLESHOOTING_FR.md](TROUBLESHOOTING_FR.md) pour l'aide.

---

**Version du document : v5.3.2 (2026-01-22)**
