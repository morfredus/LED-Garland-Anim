## Sauvegarde et restauration de la configuration (NVS)

Le système utilise la NVS (mémoire non-volatile) de l’ESP32 pour sauvegarder et restaurer automatiquement les paramètres utilisateur :

- **Mode** (permanent ou détection de mouvement)
- **Animation en cours** (guirlande et matrice)
- **Intervalle du mode auto** (guirlande)
- **Intervalle du mode auto** (matrice, indépendant depuis v5.1.1)
- **Durée d'animation sur détection**
- **Luminosité matrice**

**Fonctionnement :**
- Au démarrage, la dernière configuration sauvegardée est chargée si elle existe, sinon les valeurs par défaut sont utilisées.
- Toute modification via l'interface web ou les boutons est sauvegardée immédiatement.
- Les réglages sont conservés même après redémarrage ou coupure d'alimentation.

**Aucune action requise de l'utilisateur** : la gestion est entièrement automatique.


# Guide Utilisateur - LED-Garland-Anim v5.2.1

*Ce document est valide à partir de la version 5.2.1.*

## Plateformes supportées
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32-C3 HW-675 (OLED)
- ESP32-S3 Mini (esp32s3_mini)

Guide utilisateur complet pour le contrôleur d'animation de guirlande LED (ESP32 IdeaSpark + ST7789).

**Version du document : v5.1.1 (2026-01-07)**

- [Guide Utilisateur - LED-Garland-Anim v5.0.0](#guide-utilisateur---led-garland-anim-v500)
  - [🚦 Détection automatique du capteur de mouvement](#-détection-automatique-du-capteur-de-mouvement)
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
- **Sélection du mode d’affichage écran** (Animé, Statique, Éteint)
- Visualisation capteurs
- Actions Sauvegarder/Restaurer/Effacer la configuration

---


## Affichage LCD ST7789

- **Écran couleur 1.14" 135x240px**
- **3 modes d'affichage sélectionnables** :
  - **Animé (v5.1.0)** – **Disposition empilée pleine largeur** :
    - **En-tête** : Bannière festive avec nom du projet et version (inchangé du statique)
    - **Cartouche d'infos** (pleine largeur, 82px) : 5 lignes de données affichées dans un cadre décoré :
      1. **Mode** : Mode de fonctionnement actuel (Permanent, Détection, etc.)
      2. **WiFi** : SSID tronqué à 20 caractères avec « ... » si nécessaire
      3. **IP** : Adresse IP de l'appareil
      4. **mDNS** : Nom d'appareil avec suffix `.local` (ex. `garland.local`)
      5. **Animations** : Noms animation guirlande et matrice actuelles
    - **Zone d'animation** (pleine largeur, sous cartouche) : Grand viewport avec rafraîchissement temps réel (~10 FPS)
    - **Lisibilité améliorée** : Disposition empilée évite l'étriquement horizontal; fenêtre animation plus grande pour un meilleur retour visuel
  - **Statique** : Tableau de bord festif affichant nom du projet, version, SSID, IP et mDNS (`*.local`)
  - **Éteint** : Écran et rétroéclairage coupés
- Sélection à la volée depuis l’interface web (radio)
- Valeur par défaut configurable dans `config.h`
- Persistance automatique (NVS, restauré au boot)
- Effet immédiat, sans reboot
- 11 visualisations animées (une par animation, mode animé)
- Mises à jour temps réel à 10 FPS (mode animé)

---

## Modes de Fonctionnement
- **Permanent** : Toujours allumé (par défaut)
- **Détection Mouvement** : Activation par capteur PIR (30s après mouvement)

---

## Animations
- Éteint, Fade Alterné, Clignotement Alterné, Pulsation, Respiration, Strobe, Battement Cœur, Vague, Scintillement, Météore, Auto (enchaînement)

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
- Suivre l'état sur le LCD et le tableau de bord web

---

## Dépannage
Voir [TROUBLESHOOTING_FR.md](TROUBLESHOOTING_FR.md) pour l'aide.

---

**Version du document : v5.1.1 (2026-01-07)**
