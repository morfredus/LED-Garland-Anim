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
