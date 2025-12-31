# [1.5.3] – 2025-12-31

### Modifié
- **Positionnement du message de reboot** : Le message utilise maintenant un positionnement absolu en haut à droite, les boutons ne se rétrécissent plus
- **Confirmation de mise à jour OTA** : Remplacement du popup bloquant `confirm()` par une double confirmation (timeout 5 secondes)
- Le texte du bouton OTA change en "⚠️ Cliquer à nouveau pour confirmer la mise à jour" au premier clic
- Un message d'avertissement apparaît sous le bouton OTA après le premier clic

### Corrigé
- Disposition UI : Le message de confirmation reboot ne déplace plus les boutons
- UX : Les boutons conservent une largeur fixe quel que soit l'état d'affichage du message
- OTA : Suppression des popups bloquants `alert()` pour les erreurs de validation de fichier
- OTA : Les erreurs de validation de fichier s'affichent maintenant comme messages de statut inline

### Technique
- Message reboot : Changement de flexbox vers `position:absolute` avec `top:0;right:0`
- Message reboot : Ajout d'ombre et max-width pour meilleure visibilité
- OTA : Conversion du submit de formulaire en gestionnaire de clic bouton `handleUpload()`
- OTA : Ajout de la variable d'état `uploadConfirmed` pour la logique de double-clic
- OTA : Remplacement de alert() par affichage statusMessage inline

---
# [1.5.2] – 2025-12-31

### Ajouté
- **Confirmation inline pour changements d'animation** : Affiche "✓ Animation changée : [Nom]" lors de la sélection d'une nouvelle animation
- **Confirmation inline pour changements de mode** : Affiche "✓ Mode changé : [Nom]" lors du changement de mode
- Retour visuel amélioré pour toutes les actions utilisateur dans l'interface web

### Modifié
- **Positionnement du message de confirmation reboot** : Le message apparaît maintenant à droite des boutons au lieu d'en dessous
- Le message de reboot utilise une disposition flexbox pour éviter le déplacement des boutons
- Toutes les confirmations utilisent maintenant un délai cohérent de 3 secondes avant disparition automatique
- Rechargement de la page retardé d'1 seconde après changement d'animation/mode pour afficher la confirmation

### Technique
- Ajout de la fonction `showParamMessage()` pour les confirmations animation/mode
- Modification de `changeAnimation()` pour extraire et afficher le nom de l'animation
- Modification de `changeMode()` pour extraire et afficher le nom du mode
- Le conteneur du message de reboot utilise `display:flex` pour un alignement correct
- Améliorations CSS pour le positionnement des messages inline

---
# [1.5.1] – 2025-12-31

### Corrigé
- **Bug critique** : L'animation de démarrage fonctionne maintenant correctement même quand l'animation sauvegardée est OFF
- La logique d'animation utilise maintenant correctement `activeAnimation` au lieu de `currentAnimation` pour les tests d'exécution
- L'animation d'intro n'est plus bloquée par l'animation OFF dans les paramètres sauvegardés

### Technique
- Modification de `updateGarland()` : Changement du test de `currentAnimation == ANIM_OFF` à `activeAnimation == ANIM_OFF`
- Cela garantit que l'animation d'intro joue indépendamment de l'état de l'animation sauvegardée

---
# [1.5.0] – 2025-12-31

### Ajouté
- **Animation de démarrage automatique** : Animation d'intro de 10 secondes (Fade Alterné) démarre immédiatement au boot
- **Transition automatique** : Après l'intro, bascule automatiquement vers l'animation et le mode sauvegardés
- **Messages de confirmation inline** : Toutes les opérations save/restore/erase affichent des confirmations inline (pas de popups bloquants)
- **Double-clic pour confirmer le redémarrage** : Le bouton redémarrer nécessite deux clics pour la sécurité (timeout de 5 secondes)

### Modifié
- Comportement au démarrage : L'animation démarre immédiatement, même en mode détection de mouvement
- Interface web : Suppression de tous les popups bloquants alert() et confirm()
- Bouton redémarrer : Ajout d'un retour visuel (changement de couleur) au premier clic
- Expérience utilisateur : Les confirmations non-bloquantes améliorent le workflow
- Numéro de version incrémenté à 1.5.0 (SEMVER - MINOR)

### Corrigé
- Problème de démarrage : La guirlande s'anime maintenant immédiatement au lieu d'attendre une interaction utilisateur
- Fiabilité du redémarrage : La double confirmation évite les redémarrages accidentels
- Mode détection de mouvement : L'animation d'intro joue avant l'activation de la détection de mouvement

### Technique
- Ajout de la constante `INTRO_ANIMATION_DURATION` (10 secondes)
- Ajout des variables d'état `introAnimationActive`, `savedAnimation`, `savedMode`
- Modification de `setupGarland()` pour démarrer l'animation d'intro immédiatement
- Modification de `updateGarland()` pour gérer la transition intro-vers-sauvegarde
- Fonctions JavaScript pour messages inline : `showMessage()`, `saveSettings()`, `loadSettings()`, `eraseSettings()`
- Confirmation de redémarrage JavaScript avec timeout : `rebootDevice()`

---
# [1.4.0] – 2025-12-31

### Ajouté
- **Système de mise à jour OTA via interface Web** : Upload de firmware (.bin) directement depuis le navigateur
- Page web dédiée `/update` avec interface intuitive pour téléverser le firmware
- Affichage de la progression en temps réel (barre de progression, pourcentage)
- Validation du fichier uploadé (vérification extension .bin)
- Affichage de l'état de la mise à jour sur l'écran ST7789 (progression, succès, échec)
- Gestion complète des erreurs avec messages clairs
- Redémarrage automatique après mise à jour réussie
- Bouton d'accès rapide à la mise à jour OTA depuis le tableau de bord

### Modifié
- Numéro de version incrémenté à 1.4.0 (SEMVER)
- Documentation utilisateur complétée avec instructions OTA Web (FR/EN)
- ArduinoOTA conservé comme méthode alternative (PlatformIO OTA)

### Technique
- Utilisation de `Update.h` natif ESP32 pour le flash du firmware
- Handler d'upload avec gestion mémoire optimisée (upload par chunks)
- Interface JavaScript pour l'upload asynchrone avec XMLHttpRequest
- Validation côté client et serveur

---
# [1.3.0] – 2025-12-31

### Ajouté
- Prise en charge des mises à jour OTA (Over-the-Air) du firmware via ArduinoOTA
- Documentation et guides utilisateur mis à jour (FR/EN)

### Modifié
- Numéro de version incrémenté à 1.3.0 (SEMVER)

---
# [1.2.2] – 2025-12-31

### Modifié
- Harmonisation complète et réorganisation logique des README.md et README_FR.md (structure, clarté, suppression des doublons)
- Suppression définitive des références à ESP32-S3 et anciens environnements
- Relecture et ordonnancement de toute la documentation et des guides pour une clarté utilisateur
- Version, changelog et notes de version mis à jour

---
# [1.2.1] – 2025-12-31

### Ajouté
- Prise en charge de l'auto-détection du capteur de mouvement (PIR HC-SR501 ou RCWL-0516) sur GPIO 35
- Documentation technique et utilisateur mise à jour (FR/EN)

### Modifié
- Mapping des pins : PIR_SENSOR remplacé par MOTION_SENSOR_PIN (GPIO 35)
- Suppression de toutes les références à la LDR/photoresistor (fonctionnalité supprimée)
- Tableaux de mapping et guides adaptés au matériel réellement supporté
- Dépannage et guides mis à jour pour la nouvelle logique capteur

### Corrigé
- Cohérence de la documentation (FR/EN)
- Numéros de version et dates dans tous les documents

### Supprimé
- Tout le code et la documentation liés à la LDR/photoresistor
- Support des écrans et cartes obsolètes (seul ESP32 Classic + ST7789 est supporté)

---
# Notes de version – LED-Garland-Anim v1.2.0

## [1.2.0] – 2025-12-31

### Ajouté
- Détection automatique du type de capteur de mouvement (PIR HC-SR501 ou radar Doppler RCWL-0516) sur GPIO 35
- Nouvelle documentation technique pour le RCWL-0516 (FR/EN)
- Toute la documentation utilisateur et technique mise à jour pour v1.2.0 (FR/EN)

### Modifié
- Mapping des pins : PIR_SENSOR remplacé par MOTION_SENSOR_PIN (GPIO 35)
- Suppression de toutes les références à la LDR/photoresistor (fonctionnalité supprimée)
- Tableaux de mapping et guides adaptés au matériel réellement supporté
- Dépannage et guides mis à jour pour la nouvelle logique capteur

### Corrigé
- Cohérence de la documentation (FR/EN)
- Numéros de version et dates dans tous les documents

### Supprimé
- Tout le code et la documentation liés à la LDR/photoresistor
- Support des écrans et cartes obsolètes (seul ESP32 Classic + ST7789 est supporté)

---

Voir CHANGELOG_FR.md pour l’historique détaillé des commits.
## [1.1.0] - 2024-06-XX

### Ajouté
- Sauvegarde et restauration automatique de la configuration utilisateur (mode, animation, intervalles) via NVS. Les réglages sont conservés après redémarrage ou coupure d’alimentation.
# Notes de Version - Version 1.1.0

**Date de Sortie :** 30 Décembre 2025

## 🎉 Version Majeure : Unification Plateforme ESP32 IdeaSpark

La version 1.0.0 représente une modernisation complète de la plateforme, se concentrant exclusivement sur la carte ESP32 IdeaSpark avec écran LCD ST7789 1.14" intégré.

---

## ♻️ Nouveautés 1.1.0

- Suppression de toutes les références à la LDR/photorésistance (projet désormais PIR uniquement)
- Documentation (FR + EN) entièrement réécrite et mise à jour : matériel, câblage, configuration, utilisation
- Numéros de version mis à jour partout (SEMVER)
- Cohérence totale entre code, documentation et mapping matériel

---

## 🌟 Points Forts

### Système d'Affichage ST7789 Moderne
- **Écran de Démarrage Élégant** : Nom du projet, version et progression connexion WiFi
- **Interface Principale Optimisée** : En-têtes centrés, infos compactes, zone animation 20% plus grande
- **11 Visualisations Animées** : Animations fluides et colorées pour chaque mode guirlande
- **Design Professionnel** : Rectangles arrondis, dégradés vibrants, esthétique moderne

### Simplification Plateforme
- **Cible Unique** : ESP32 IdeaSpark LCD 1.14" uniquement
- **Supprimé** : Tous environnements ESP32-S3 et code affichage legacy (OLED/TFT/ILI9341)
- **Codebase Plus Propre** : Réduction code 15%, architecture simplifiée

### Corrections Critiques
- **Timer Détection Mouvement** : Arrête maintenant correctement les animations après durée configurée
- **Détection de Front** : Déclenchement front montant évite réinitialisations continues
- **Layout Affichage** : Optimisé pour s'adapter parfaitement à l'écran 135×240

---

## 🔑 Changements Principaux

### Ajouté
- Module affichage ST7789 complet avec écrans démarrage et principal
- Configuration carte ESP32 IdeaSpark avec mapping pins optimisé
- 11 visualisations animées distinctes avec couleurs vibrantes
- Mises à jour animation temps réel à 10 FPS

### Modifié
- Unification vers plateforme ESP32 unique (support ESP32-S3 supprimé)
- Architecture affichage modernisée avec API simplifiée
- Layout interface optimisé pour zone animation maximale
- Mise à jour tous appels affichage dans codebase

### Corrigé
- Timer détection mouvement avec logique détection de front
- Erreurs compilation (capteur LDR, includes affichage, signatures fonctions)
- Problèmes coupure layout affichage

### Supprimé
- Tout code affichage OLED (SSD1306) et configuration
- Tout code affichage TFT et ILI9341
- Environnements ESP32-S3 et complexité multi-cartes
- Support capteur LDR

---

## 📦 Matériel Requis

**Carte Supportée :**
- **ESP32 IdeaSpark LCD 1.14"** (ESP32 Classic avec écran ST7789 intégré)

**Composants :**
- Module pilote moteur TB6612FNG
- Capteur mouvement PIR (HC-SR501)
- Deux boutons utilisateur (GPIO 16, 17)
- Guirlande LED 2 fils avec LEDs en anti-parallèle

---

## 🚀 Démarrage Rapide

### 1. Configuration Matériel
Utilisez la carte ESP32 IdeaSpark avec écran LCD ST7789 1.14" intégré.

### 2. Environnement PlatformIO
```ini
[platformio]
default_envs = esp32devkitc
```

### 3. Compilation & Upload
```bash
pio run -e esp32devkitc -t upload
```

### 4. Profitez !
Découvrez l'interface LCD moderne avec animations fluides !

---

## ⚠️ Changements Cassants

### Non Supporté Désormais
- ❌ Cartes ESP32-S3 (esp32s3_n16r8, esp32s3_n8r8)
- ❌ Affichages OLED (SSD1306)
- ❌ Affichages TFT/ILI9341
- ❌ Capteur lumière LDR

### Migration Requise
Si mise à niveau depuis v0.x.x :
1. Remplacer matériel par carte ESP32 IdeaSpark LCD 1.14"
2. Supprimer configuration OLED/TFT de secrets.h
3. Suivre nouveau mapping pins dans `include/board_config.h`
4. Utiliser environnement `esp32devkitc` exclusivement

---

## 🎨 Fonctionnalités Affichage

### Écran Démarrage
- Nom projet et version centrés
- Barre progression connexion WiFi avec pourcentage
- Design propre et professionnel

### Écran Principal
- Nom application et version en haut (centrés)
- Infos mode et animation compactes
- Grande zone visualisation animation (234×81 pixels)
- 11 motifs animés uniques :
  - **Fade Alterné** : Barres dégradé jaune/bleu
  - **Pulsation** : Cercle violet qui grandit/rétrécit
  - **Respiration** : Fade in/out cyan doux
  - **Strobe** : Flashs blancs rapides
  - **Battement Cœur** : Effet double pulsation rouge
  - **Vague** : Onde sinusoïdale cyan
  - **Scintillement** : Points jaunes clignotants
  - **Météore** : Effet traînée orange/jaune
  - **Auto** : Texte vert avec cercles en orbite
  - **ÉTEINT** : Texte rouge "OFF" centré
  - Et plus encore !

---

## 🐛 Corrections de Bugs

### Timer Détection Mouvement
- **Problème** : Animations ne s'arrêtaient pas après durée configurée
- **Correction** : Implémentation détection front (déclenchement front montant uniquement)
- **Résultat** : Timer démarre à détection mouvement et expire correctement

### Layout Affichage
- **Problème** : Rectangle animation coupé en bas d'écran
- **Correction** : Layout optimisé, infos WiFi/IP inutiles supprimées
- **Résultat** : Zone animation 20% plus grande, adaptation écran parfaite

---

## 📊 Spécifications Techniques

- **Affichage** : 135×240 pixels, couleur RGB565, communication SPI
- **Fréquence Rafraîchissement** : 10 FPS pour animations fluides
- **Plateforme** : ESP32 Classic (Flash 4MB)
- **Réduction Code** : ~15% codebase plus petite
- **Fichiers Modifiés** : 12 fichiers principaux
- **Commits** : 7 commits consolidés

---

## 🔗 Ressources

- **Changelog** : Voir [CHANGELOG_FR.md](CHANGELOG_FR.md) pour historique complet
- **Version Anglaise** : [CHANGELOG.md](CHANGELOG.md)
- **Mapping Pins** : `include/board_config.h`
- **Configuration** : `include/config.h`

---

## ✅ Testé & Vérifié

- ✅ Compilation sur environnement esp32devkitc
- ✅ Rendu affichage ST7789
- ✅ Tous les 11 visuels animation
- ✅ Timer détection mouvement
- ✅ Intégration interface web
- ✅ Contrôles boutons
- ✅ Intégration Telegram
- ✅ Fonctionnement stable (pas problèmes watchdog)

---

## 🙏 Merci

Merci d'utiliser LED-Garland-Anim ! Cette version v1.0.0 apporte une plateforme moderne et focalisée avec de belles animations visuelles.

Pour problèmes, questions ou contributions, veuillez visiter le dépôt du projet.

---

**LED-Garland-Anim v1.0.0** - Contrôleur Moderne de Guirlande LED pour ESP32 IdeaSpark 🎄✨
