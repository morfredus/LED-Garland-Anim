# [1.2.1] - 2025-12-31

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
### [1.1.0] - 2024-06-XX
#### Ajouté
- Sauvegarde et restauration automatique de la configuration utilisateur (mode, animation, intervalles) via NVS. Les réglages sont conservés après redémarrage ou coupure d’alimentation.
# Journal des modifications

Toutes les modifications notables de ce projet seront documentées dans ce fichier.

Le format est basé sur [Keep a Changelog](https://keepachangelog.com/fr/1.0.0/),
et ce projet adhère au [Semantic Versioning](https://semver.org/lang/fr/).


## [1.1.0] - 2025-12-30

### ♻️ Nettoyage & Documentation
- Suppression de toutes les références à la LDR/photorésistance dans le code et la documentation (projet désormais PIR uniquement)
- Mise à jour complète de toute la documentation utilisateur et technique (FR + EN) : matériel, câblage, utilisation, cohérence
- Numéros de version mis à jour partout (SEMVER)
- Cohérence totale entre code, docs et mapping matériel

---

## [1.0.0] - 2025-12-30

### 🎯 Refonte Majeure : Plateforme ESP32 IdeaSpark avec LCD 1.14"

Cette version représente une unification complète de la plateforme, se concentrant exclusivement sur la carte ESP32 IdeaSpark avec écran LCD ST7789 intégré.

### ✨ Ajouté
- **Module d'Affichage ST7789** - Réécriture complète du système d'affichage pour LCD TFT 1.14" (135x240px)
  - Écran de démarrage moderne avec nom du projet, version et barre de progression WiFi
  - Interface principale optimisée avec en-têtes centrés, infos mode/animation compactes et grande zone d'animation
  - 11 visualisations animées distinctes (une par animation) avec rendu fluide basé sur des frames
  - Rectangles arrondis, couleurs vibrantes (dégradés jaune/bleu) et effets visuels modernes
  - Mises à jour d'animation en temps réel à 10 FPS pour affichage fluide
  - Mode "AUTO" visuel avec cercles en orbite, "Battement Cœur" avec effet de double pulsation
  - "Fade Alterné" amélioré avec barres jaune/bleu, "Vague" avec amplitude plus grande
  - État "ÉTEINT" dédié avec texte rouge centré

- **Configuration Carte ESP32 IdeaSpark** - Nouveau mapping matériel unifié
  - Définitions complètes des pins pour LCD ST7789 1.14" intégré (MOSI, SCLK, CS, DC, RST, BLK)
  - Pins pilote moteur TB6612FNG optimisées pour IdeaSpark (AIN1 déplacé sur GPIO 25 pour éviter conflit LCD_BLK)
  - Capteur PIR de mouvement sur GPIO 35 (pin input-only, parfait pour capteur)
  - Boutons utilisateur sur GPIO 16 et 17
  - Bus I2C disponible sur GPIO 21/22 pour extension future

### 🔄 Modifié
- **Unification Plateforme** - Simplification vers plateforme ESP32 unique
  - Suppression des environnements ESP32-S3 (esp32s3_n16r8, esp32s3_n8r8)
  - Conservation uniquement de l'environnement `esp32devkitc` avec configuration ESP32 IdeaSpark
  - Mise à jour configuration PlatformIO pour focus mono-carte
  - Nom de carte : "ESP32 IdeaSpark 1.14 LCD"

- **Architecture Affichage** - Modernisation complète
  - Remplacement de tous les appels `updateOledAnimationStatus()` par `displayMainScreen()`
  - Suppression des déclarations forward display.h en faveur d'includes propres
  - Ajout include `display.h` dans web_interface.h pour visibilité des fonctions
  - API d'affichage simplifiée à 4 fonctions principales : `setupDisplay()`, `displayBootScreen()`, `displayMainScreen()`, `updateAnimationVisual()`

- **Optimisation Layout Interface** - Maximisation espace écran
  - Suppression SSID WiFi/IP de l'écran principal (affichés uniquement au démarrage)
  - Réduction hauteur en-tête de 14 pixels (texte compact, espacement optimisé)
  - Infos mode/animation déplacées plus haut et plus compactes (10 pixels économisés)
  - Zone d'animation agrandie de 67px à 81px de hauteur (+20% surface visuelle)
  - Nom application et version centrés en haut pour apparence professionnelle
  - Lignes de séparation nettes pour hiérarchie visuelle

### 🐛 Corrigé
- **Timer Détection Mouvement** - Correction critique pour mode détection
  - Implémentation détection de front montant avec variable `lastMotionState`
  - Timer déclenché uniquement sur transition montante (LOW→HIGH)
  - Évite réinitialisation continue du timer quand capteur PIR reste HIGH
  - Animations s'arrêtent maintenant correctement après durée configurée (30 secondes par défaut)
  - Ajout logs de débogage toutes les 5 secondes montrant statut timer et temps écoulé
  - Correction problème où mode "détection" n'éteignait jamais les animations

- **Erreurs de Compilation** - Multiples corrections de build
  - Suppression support capteur LDR (erreurs `LDR_SENSOR` undefined corrigées)
  - Mise à jour tous les appels d'affichage Telegram vers nouvelle API
  - Correction include manquant `display.h` dans web_interface.h
  - Correction incompatibilités de signatures de fonctions entre modules

### ❌ Supprimé
- **Support Affichages Obsolètes** - Suppression complète code d'affichage legacy
  - Suppression tout code affichage OLED (SSD1306) et configuration
  - Suppression tout code affichage TFT et ILI9341
  - Suppression dépendance bibliothèque Adafruit SSD1306 de platformio.ini
  - Suppression flag de configuration `HAS_OLED` de config.h
  - Conservation uniquement du flag `HAS_ST7789`

- **Code Multi-Plateforme** - Simplification support carte
  - Suppression configurations et mappings pins spécifiques ESP32-S3
  - Suppression complexité compilation conditionnelle multi-cartes
  - Suppression fonctions stub d'affichage inutilisées

- **Capteur LDR** - Détection lumineuse matérielle supprimée
  - Suppression définitions pin `LDR_SENSOR` de board_config.h
  - Suppression `pinMode(LDR_SENSOR, INPUT)` de `setupGarland()`
  - Modification `getLightLevel()` pour retourner 0 (capteur supprimé)
  - Array capteurs simplifié à détection mouvement PIR uniquement

### 📦 Dépendances
- **Bibliothèques Requises Mises à Jour**:
  - Adafruit NeoPixel @ ^1.12.0
  - ArduinoJson @ ^7.0.3
  - OneButton @ ^2.5.0
  - Adafruit GFX Library @ ^1.11.9
  - Adafruit ST7735 and ST7789 Library @ ^1.11.0
  - ❌ Supprimée : Adafruit SSD1306

### 🔧 Détails Techniques
- **Spécifications Affichage**:
  - Résolution : 135×240 pixels (orientation paysage avec rotation=1)
  - Profondeur couleur : RGB565 (couleur 16-bit)
  - Communication SPI sur pins SPI matérielles
  - Contrôle rétroéclairage via GPIO 32 (doit être HIGH pour visibilité)
  - Fréquence rafraîchissement animation : 10 FPS (intervalle 100ms)

- **Conflits Pins Résolus**:
  - Déplacement TB6612_AIN1 de GPIO 32 vers GPIO 25 (GPIO 32 nécessaire pour rétroéclairage LCD)
  - LED_BUILTIN (GPIO 2) partagée avec LCD_DC (acceptable comme pin data/command)
  - Aucun conflit entre affichage, pilote moteur, capteurs et boutons

- **Architecture Code**:
  - Système affichage modulaire avec séparation claire des responsabilités
  - Module affichage fonctionne indépendamment avec ou sans flag `HAS_ST7789`
  - Fonctions stub vides fournies quand ST7789 désactivé pour sécurité compilation
  - Tous appels affichage non-bloquants et optimisés pour exécution loop()

### 📊 Métriques Version
- **Utilisation Flash** : Optimisé pour ESP32 Classic (flash 4MB)
- **Réduction Code** : ~15% réduction depuis codebase multi-plateforme
- **Fichiers Modifiés** : 12 fichiers principaux mis à jour
- **Commits** : 7 commits consolidés en release v1.0.0
- **Lignes Modifiées** : +850 ajouts, -1200 suppressions

### 🎨 Améliorations Visuelles
- **Écran Démarrage**:
  - Nom projet centré en cyan (taille 2)
  - Numéro version centré dessous en blanc
  - Barre progression WiFi avec remplissage vert et pourcentage
  - Lignes séparation nettes pour structure visuelle

- **Écran Principal**:
  - Nom application centré en haut (cyan, taille 1)
  - Version centrée dessous (blanc, taille 1)
  - Labels mode/animation compacts à gauche (magenta/orange)
  - Grande zone visualisation animation (234×81 pixels)
  - Animations fluides avec palettes couleurs vibrantes

- **Visuels Animations**:
  - "Fade Alterné" : Barres arrondies jaune/bleu avec modulation luminosité
  - "Pulsation" : Cercle violet qui grandit/rétrécit
  - "Respiration" : Rectangle arrondi cyan avec fade in/out doux
  - "Strobe" : Flashs rectangulaires blancs rapides
  - "Battement Cœur" : Effet cercle rouge double pulsation
  - "Vague" : Onde sinusoïdale cyan avec amplitude plus grande
  - "Scintillement" : 15 points jaunes clignotant aléatoirement
  - "Météore" : Effet traînée dégradé orange/jaune
  - "Auto" : Texte vert "AUTO" avec doubles cercles en orbite (jaune/cyan)
  - "ÉTEINT" : Texte rouge "OFF" centré sur fond noir

### 🚀 Notes Migration
**Changements Cassants**:
- Cartes ESP32-S3 non supportées - ESP32 IdeaSpark uniquement
- Affichages OLED non supportés - LCD ST7789 uniquement
- Capteur LDR supprimé - détection mouvement (PIR) uniquement

**Chemin Mise à Niveau**:
1. Matériel : Remplacer ESP32-S3 par carte ESP32 IdeaSpark LCD 1.14"
2. Configuration : Supprimer toute configuration OLED/TFT de secrets.h
3. Câblage : Suivre nouveau mapping pins dans board_config.h
4. Compilation : Utiliser environnement `esp32devkitc` exclusivement
5. Affichage : Profiter de la nouvelle interface LCD moderne avec animations !

### ✅ Tests Complétés
- [x] Compilation réussie sur environnement esp32devkitc
- [x] Initialisation et rendu affichage ST7789
- [x] Écran démarrage avec barre progression WiFi
- [x] Optimisation layout écran principal (pas de coupure)
- [x] Tous les 11 visuels d'animation rendus correctement
- [x] Détection front timer mouvement fonctionnelle
- [x] Mises à jour affichage interface web fonctionnelles
- [x] Contrôles boutons mettant à jour affichage correctement
- [x] Contrôles Telegram mettant à jour affichage correctement
- [x] Aucune fuite mémoire ni problème watchdog timer

---

## [0.7.0-rc1] - 2025-12-13

### 🎨 Interface Web Simplifiée et Festive
- UI épurée avec seulement les paramètres essentiels de la guirlande
- Thème visuel Noël/Nouvel An : palette rouge-or-vert, bordures dorées
- Saisie des durées en **secondes** (conversion automatique en millisecondes)
- Boutons "Valider" pour appliquer les changements de durée
- Note explicative dynamique pour le calcul du nombre d'animations en mode Détection+Auto

### 💾 Gestion de la Sauvegarde NVS
- Bouton **Sauvegarder** : enregistrement manuel des paramètres en NVS
- Bouton **Restaurer** : rechargement depuis la sauvegarde NVS
- Bouton **Effacer** : suppression de la sauvegarde (confirmation requise)
- Endpoints API : `/save`, `/load`, `/erase`

### ⚙️ Paramètres Clairs
- **Durée d'une animation (mode Auto)** : temps d'affichage de chaque animation en mode Auto
- **Durée d'allumage après détection** : temps total avant extinction après mouvement
- Affichage du SSID WiFi et de l'IP dans une carte réseau minimaliste

### 🔧 Améliorations Techniques
- Persistance automatique lors du changement d'animation, mode ou durées
- Statut API enrichi avec l'adresse IP (`/status` inclut `"ip"`)
- Labels UI explicites pour différencier les deux types de durée

## [0.6.4] - 2025-12-13

### 🔒 Persistance des paramètres (NVS)
- Sauvegarde automatique du `mode`, de l'`animation`, de `auto_interval_ms` et de `motion_duration_ms` dans la mémoire NVS de l'ESP32.
- Chargement des paramètres au démarrage via `loadGarlandSettings()` appelé dans `setupGarland()`.
- Initialisation NVS en début de `setup()` avec gestion d’effacement si nécessaire.

### 🌐 UI et API Web
- UI Web: ajout de champs numériques pour modifier l’intervalle AUTO et la durée de détection mouvement, pré-remplis avec les valeurs courantes.
- API Web: nouveaux endpoints `GET /auto_interval?ms=...` et `GET /motion_duration?ms=...` et statut enrichi (`/status`) exposant `auto_interval_ms` et `motion_duration_ms`.

### 🧩 Divers
- Mise à jour des en-têtes et affichage de version à 0.6.4.

## [0.6.3] - 2025-12-13

### ✨ Ajout : 5 Nouvelles Animations Spectaculaires
- ⚡ **Strobe**: Effet de flash stroboscopique rapide - flashs intenses alternant entre les directions
- ♥️ **Battement Cœur**: Effet de double pulsation (BOM-bom... BOM-bom...) imitant un battement de cœur
- 🌊 **Vague**: Onde sinusoïdale fluide circulant entre les directions de LEDs
- ✨ **Scintillement**: Effet de scintillement aléatoire avec intensité variable
- ☄️ **Météore**: Effet de traînée lumineuse avec estompage progressif simulant un météore

### 🎭 Vitrine d'Animations
**Total animations : 11** (6 originales + 5 nouvelles)
- Originales : Éteint, Fade Alterné, Clignotement Alterné, Pulsation, Respiration, Auto
- **Nouvelles** : Strobe, Battement Cœur, Vague, Scintillement, Météore

### Détails Techniques
- Toutes les animations optimisées pour guirlande monochrome 2 fils avec LEDs en anti-parallèle
- Le mode Auto cycle maintenant à travers les 10 animations actives (30s chacune)
- Transitions fluides et effets utilisant le contrôle du pont en H TB6612FNG
- Ajout d'appels yield() pour éviter les problèmes de watchdog timer

### Expérience Utilisateur
- 🎵 Plus de variété visuelle pour l'éclairage décoratif
- 🔄 Mode Auto enrichi avec 5 effets supplémentaires
- 🕹️ Le Bouton 1 cycle à travers les 11 animations + Auto
- 💻 Interface web mise à jour avec les nouvelles options d'animation

## [0.6.2] - 2025-12-12

### 🐞 Corrigé : Démarrage Mode Auto
- ✅ **Le Mode Auto Démarre Maintenant Instantanément**
  - Corrigé : Le mode AUTO démarre immédiatement avec la première animation (Fade Alterné)
  - Éliminé la période vide de 30 secondes lors de la sélection du mode AUTO
  - Le mode Auto apparaît maintenant correctement dans le cycle du Bouton 1
  
### 🛠️ Changements Techniques
- 💾 **Architecture Interne** : Séparation de `currentAnimation` (affichage/UI) et `activeAnimation` (exécution)
  - `currentAnimation` : Stocke l'animation sélectionnée incluant ANIM_AUTO (affichée sur OLED/web)
  - `activeAnimation` : Animation réellement exécutée (toujours concrète comme FADE, PULSE, etc.)
  - Ajout du flag `autoModeActive` pour suivre l'état du mode AUTO
- 🔄 **Logique Mode Auto** : Gestion du cycle améliorée
  - La première animation démarre immédiatement quand AUTO est sélectionné
  - Cycle entre les animations 1-4 toutes les 30 secondes
  - Réinitialisation correcte lors de la sortie/rentrée en mode AUTO

### Expérience Utilisateur
- ✨ Le Bouton 1 affiche maintenant correctement "Auto" dans le cycle
- ✨ La guirlande s'allume instantanément quand le mode AUTO est sélectionné
- ✨ L'OLED affiche "Auto" pendant que les animations défilent automatiquement

## [0.6.1] - 2025-12-12

### 🔧 Correction Critique : Module Telegram Désactivé
- ❌ **Telegram Bot Retiré** - Cause du gel système identifiée
  - Le polling Telegram bloquait la boucle principale et causait les resets watchdog
  - Toutes les fonctionnalités Telegram désactivées (setupTelegramBot, handleTelegramBot, sendTelegramStatus)
  - `#include "telegram_control.h"` retiré
  - Système maintenant stable avec animations continues sans gel

### Modifié
- ⚡ **Boucle principale simplifiée** : Code de throttling Telegram retiré
- 📉 **Mémoire réduite** : Utilisation flash réduite de 79.3% à 75.9% (~45 KB économisés)
- 🎯 **Démarrage animation** : Animation par défaut changée de `ANIM_AUTO` à `ANIM_FADE_ALTERNATE`
  - La guirlande s'allume **immédiatement** au démarrage au lieu d'attendre 30 secondes

### Performance
- ✅ Système stable - aucun gel observé après suppression Telegram
- ✅ Les 6 animations fonctionnent en douceur
- ✅ Interface web réactive
- ✅ Contrôles bouton réactifs

### ⚠️ Limitation Connue
- Commande Telegram à distance temporairement indisponible
- Pour réactiver : décommenter includes et appels fonctions dans main.cpp (nécessite refactorisation)

## [0.6.0] - 2025-12-12

### Ajouté
- 🤖 **Commande Telegram** :
  - Bot en polling avec `/anim <id|nom>`, `/mode <id|nom>`, `/nextanim`, `/nextmode`, `/status`, `/liste`
  - `/liste` renvoie tous les modes et animations avec leurs IDs
  - Notification Telegram automatique à la connexion WiFi (SSID, IP, anim/mode courants)

### Modifié
- 🔐 **Secrets** : `WIFI_NETWORKS` désormais défini inline dans `secrets.h` (plus de `secrets.cpp`).
- 📄 **Documentation** : README/README_FR et USER_GUIDE/USER_GUIDE_FR mis à jour pour Telegram et version 0.6.0.

### Corrigé
- 🐛 **Gel ESP32 Classic** : `PIN_TB6612_PWMA` changé de GPIO 25 à GPIO 12
  - GPIO 25/26 sont des pins DAC causant des interférences WiFi et resets watchdog
  - Les animations ne figent plus pendant l'exécution sur ESP32 Classic
  - Section LED_RGB inutilisée supprimée (conflit GPIO 16 avec BUTTON_2)

## [0.5.1] - 2025-12-10 (Patch - Documentation)

### Mis à jour
- 📄 **Fichiers de Documentation** :
  - Mise à jour README.md et README_FR.md pour v0.5.1
  - Mise à jour tous commentaires d'en-tête dans fichiers source pour v0.5.1
  - Clarification : démarrage utilise mode Auto et mode Permanent par défaut
  - Suppression références MODE_SCHEDULED et MODE_NIGHT_OFF de la documentation utilisateur

## [0.5.1] - 2025-12-10

### Mise à Jour
- 📋 **Documentation**: Mise à jour README.md et README_FR.md avec description des 2 modes simplifiés
- 📋 **Guides Utilisateur**: Suppression des références à MODE_SCHEDULED et MODE_NIGHT_OFF
- 📋 **Info Démarrage**: Clarification du démarrage en mode Automatique et mode Permanent
- 📋 **Interface Web**: Suppression des infos sur configuration horaire et détection nuit de la doc utilisateur

## [0.5.1] - 2025-12-10

### Supprimé
- ❌ **Suppression du mode MODE_SCHEDULED** :
  - Suppression de la configuration des horaires (setSchedule, getSchedule)
  - Suppression de la planification horaire (configuration heure début/fin)
  - Simplification de l'enum mode de 4 à 2 modes
  
- ❌ **Suppression du mode MODE_NIGHT_OFF** :
  - Suppression de la détection automatique de nuit via seuil LDR
  - Suppression de la constante LDR_NIGHT_THRESHOLD
  - Suppression de la fonction isNightTime()
  - Maintien de getLightLevel() pour accès aux données brutes du capteur

### Simplifié
- 🎯 **Simplification à 2 modes essentiels**:
  - `MODE_PERMANENT` : Guirlande toujours allumée
  - `MODE_MOTION_TRIGGER` : Activation par détection de mouvement (durée 30 secondes)
- 📄 Mise à jour de toute la documentation (ARCHITECTURE.md, ARCHITECTURE_FR.md)
- 🌐 Mise à jour interface web pour afficher seulement 2 modes
- Suppression de l'interface de configuration horaire du tableau de bord

## [0.4.1] - 2025-12-10 (Patch)

### Corrigé
- 🔧 **Problème OLED Toujours Éteint** :
  - Correction de la double déclaration de variable `isNight` dans la boucle principale
  - Suppression de la fonction problématique `setOledBacklight()` qui éteignait complètement l'écran
  - OLED affiche maintenant correctement le mode veille avec indicateur (SLEEP/ZZZ)
  - Mode nuit affiche seulement l'indicateur veille, pas un écran noir
  - Correction du problème de portée des variables empêchant les transitions jour/nuit

- 🌙 **Logique Mode Nuit** :
  - Correction de la logique de détection du mode nuit dans la boucle
  - Rétroéclairage OLED n'est plus désactivé (reste allumé mais affiche contenu minimal)
  - Barre d'animation se met à jour correctement en mode jour uniquement
  - Mode veille activé correctement en mode nuit avec indicateur visuel

- 📱 **Comportement Affichage** :
  - Amélioration de l'affichage mode veille avec texte "SLEEP" (128x64) ou "ZZZ" (128x32)
  - Points toujours visibles en veille, pas d'extinction
  - Meilleur retour visuel entre mode nuit et animation arrêtée

## [0.4.0] - 2025-12-10

### Ajouté
- 🌙 **Mode Nuit (Détection Automatique de Luminosité)** :
  - Nouveau mode MODE_NIGHT_OFF utilisant le capteur LDR (photorésistance)
  - Détection automatique de la nuit via seuil de luminosité (LDR_NIGHT_THRESHOLD = 500)
  - En mode nuit : rétroéclairage OLED s'éteint, affichage montre points fixes minimalistes
  - Les indicateurs LED bleue/NeoPixel s'arrêtent de clignoter en mode nuit
  - La détection de mouvement et animations continuent à respecter le mode nuit
  - Entièrement automatique - aucune configuration manuelle requise

- 🔳 **Points Fixes sur OLED Sans Animation** :
  - Quand aucune animation n'est active (ANIM_OFF ou hors horaires), l'OLED affiche 3 points fixes
  - Retour visuel que le système fonctionne mais est inactif
  - En mode nuit : affichage très minimaliste avec points au centre
  - Réduit le scintillement inutile de l'écran

- ⚡ **Efficacité Énergétique Améliorée** :
  - LED/NeoPixel heartbeat désactivé en mode nuit pour économiser l'énergie
  - Rétroéclairage OLED désactivé en mode nuit (configurable on/off)
  - Vérification GPIO : tous les pins confirmés sûrs pour communication USB et boot/reset
  - Configurations ESP32-S3 et ESP32 Classic vérifiées

### Modifié
- 📊 **Amélioration de la Barre d'Animation OLED** :
  - Barre d'animation affiche maintenant 3 points fixes au lieu de rien quand animation est OFF
  - Meilleur retour visuel pendant les périodes inactives

- 🏷️ **Mise à jour de Version** :
  - Mise à jour vers version 0.4.0 avec mode nuit et efficacité énergétique
  - Toutes les chaînes de version mises à jour dans la base de code

## [0.3.0] - 2025-12-09

### Modifié
- 🔄 **Ordre des lignes sur affichage OLED** :
  - Inversion de l'ordre des lignes Animation et Mode sur écran OLED 32px
  - La première ligne "M:" affiche maintenant le Mode (était Animation)
  - La deuxième ligne "A:" affiche maintenant l'Animation (était Mode)
  - Amélioration de la lisibilité en priorisant l'information de mode

- 🎯 **Mode d'animation par défaut** :
  - Changement de l'animation au démarrage de `ANIM_FADE_ALTERNATE` vers `ANIM_AUTO`
  - Le système démarre maintenant en mode cyclage automatique par défaut
  - Le mode auto fait défiler les 14 animations toutes les 30 secondes
  - Offre une meilleure expérience utilisateur initiale avec de la variété

- 🏷️ **Mise à jour de la version** :
  - Mise à jour vers le versioning sémantique 0.3.0
  - Version mise à jour dans tous les fichiers sources et en-têtes

## [0.2.0] - 2025-12-09

### Ajouté
- 🖥️ **Affichage OLED en temps réel** :
  - Affichage en direct du nom de l'animation courante sur écran OLED
  - Affichage en direct du nom du mode courant sur écran OLED
  - Affichage de l'adresse IP locale pour accès à l'interface web
  - Mise en page adaptative pour écrans OLED 128x32 et 128x64
  - Mise à jour automatique sur appui bouton ou changement web
  - Taux de rafraîchissement 10 FPS (intervalle 100ms) pour animations fluides

- 🎨 **Barre de visualisation animée** :
  - Barre d'animation visuelle sur dernière ligne de l'écran OLED
  - 14 motifs d'animation distincts correspondant aux animations de guirlande :
    - Fade : Barre glissante avec effet de dégradé
    - Blink : Blocs alternés gauche/droite
    - Wave : Progression d'onde fluide
    - Strobe : Blocs clignotants rapides
    - Pulse : Barre centrale qui grandit/rétrécit
    - Chase : Motif de point qui court
    - Heartbeat : Effet de pulsation double
    - Sparkle : Illumination de pixels aléatoires
    - Rainbow : Motif d'onde mobile
    - Breathing : Barre qui s'étend/se contracte
    - Fire : Barres de hauteur aléatoire qui vacillent
    - Twinkle : Pixels aléatoires épars
    - Meteor : Traînée mobile avec estompage
    - Mode auto : Animation de tirets rotatifs
  - Aucune barre d'animation affichée quand la guirlande est éteinte

- ⏰ **Interface de configuration horaire** :
  - Champs de saisie d'heure dans l'interface web pour mode programmé
  - 4 entrées numériques : heure/minute début, heure/minute fin
  - Valeurs actuelles de l'horaire pré-remplies dans les entrées
  - Bouton d'enregistrement avec popup de confirmation
  - Point d'accès API `/schedule` pour configuration
  - Fonctions backend `getSchedule()` et `setSchedule()`
  - Informations d'horaire incluses dans la réponse JSON `/status`
  - Horaire par défaut : 18:00 - 23:00
  - Validation des entrées (0-23 heures, 0-59 minutes)

- 🎛️ **Réorganisation de l'interface web** :
  - Carte de contrôle LED Guirlande déplacée en première position
  - Configuration horaire intégrée dans la carte Guirlande
  - Hiérarchie visuelle améliorée dans le tableau de bord

### Corrigé
- 🔧 **Corrections GPIO des boutons** :
  - Changement Bouton 1 de GPIO 34 vers GPIO 4 (ESP32 Classic)
  - Changement Bouton 2 de GPIO 35 vers GPIO 15 (ESP32 Classic)
  - Correction problème pins INPUT_ONLY (GPIO 34/35 sans pull-ups internes)
  - Boutons maintenant détectés correctement avec résistances pull-up internes

- 🖥️ **Initialisation affichage OLED** :
  - Déplacement de `setupDisplays()` avant `setupWifi()` dans setup()
  - Correction problème OLED vierge causé par initialisation tardive
  - L'écran affiche maintenant correctement la progression de connexion WiFi

- 🔄 **Rafraîchissement barre d'animation** :
  - Ajout d'un timer de rafraîchissement périodique 100ms dans la boucle principale
  - La barre d'animation s'anime maintenant en continu (était statique)
  - Incrémentation appropriée du compteur de frames à chaque dessin

### Modifié
- 📍 **Allocation des pins GPIO** (ESP32 Classic):
  - Bouton 1 : GPIO 34 → GPIO 4
  - Bouton 2 : GPIO 35 → GPIO 15
  - Pins LED RGB réservées : R=GPIO16, G=GPIO17, B=GPIO5
  - GPIO 25/26 disponibles pour configuration alternative des boutons

- 🏷️ **Gestion des versions** :
  - Mise à jour vers versioning sémantique 0.2.0
  - Ajout des drapeaux de compilation `PROJECT_VERSION` et `PROJECT_NAME`
  - Informations de version accessibles dans tout le code

## [0.1.0] - 2025-12-09

### Ajouté
- 🎄 **Système d'animations pour guirlande LED bi-directionnelle** :
  - 14 animations différentes (Fade Alterné, Clignotement, Onde Douce, Stroboscope, Pulsation, Poursuite, Battement de Cœur, Scintillement, Arc-en-ciel, Respiration, Feu, Clignotement Doux, Météore)
  - Mode automatique enchaînant toutes les animations (30s chacune)
  - Support du module TB6612FNG pour contrôle bi-directionnel
  - LEDs en anti-parallèle (~25 LEDs Sens A + ~25 LEDs Sens B)
  - Contrôle PWM 8 bits à 5000 Hz

- 🎮 **Modes de fonctionnement intelligents** :
  - Mode Permanent : Toujours allumé
  - Mode Horaires : Allumage selon plages horaires (préparé pour RTC)
  - Mode Détection Mouvement : Déclenchement par capteur PIR (30s après détection)
  - Mode Coupure Nuit : Extinction automatique selon luminosité (LDR)

- 🔘 **Gestion des boutons physiques** :
  - Bouton 0 (BOOT) : Redémarrage en appui long (1s) - conservé
  - Bouton 1 : Changement d'animation + accès mode automatique
  - Bouton 2 : Changement de mode de fonctionnement
  - Feedback visuel NeoPixel sur chaque action

- 🌐 **Interface Web complète** :
  - Carte dédiée au contrôle de la guirlande
  - Sélecteur d'animation avec liste déroulante (15 options)
  - Sélecteur de mode (4 options)
  - Affichage état capteurs (PIR, LDR, nuit)
  - Changement d'animation/mode en temps réel depuis l'interface
  - Routes API : `/animation?id=X`, `/mode?id=X`, `/status` (JSON)

- 📡 **Capteurs et détection** :
  - Support capteur PIR (HC-SR501) pour détection de mouvement
  - Support photorésistance LDR pour détection jour/nuit
  - Seuil de nuit configurable (défaut : 500/4095)
  - Durée de déclenchement configurable (défaut : 30s)

- 📍 **Pin mapping ESP32-S3** :
  - TB6612FNG : PWMA(GPIO5), AIN1(GPIO6), AIN2(GPIO4), STBY(GPIO8)
  - Capteurs : PIR(GPIO14), LDR(GPIO15)
  - Boutons : BTN1(GPIO16), BTN2(GPIO17)

- 📍 **Pin mapping ESP32 Classic** :
  - TB6612FNG : PWMA(GPIO25), AIN1(GPIO32), AIN2(GPIO33), STBY(GPIO14)
  - Capteurs : PIR(GPIO36), LDR(GPIO39)
  - Boutons : BTN1(GPIO34), BTN2(GPIO35)

- 🗂️ **Architecture modulaire** :
  - Nouveau module `garland_control.h/cpp` pour gestion animations
  - Séparation claire des responsabilités
  - Documentation Doxygen complète

### Modifié
- 🔧 **main.cpp refactorisé** :
  - Intégration du module `garland_control`
  - Gestion de 3 boutons (Boot, Btn1, Btn2)
  - Ajout de `updateGarland()` dans la boucle principale
  - Callbacks boutons adaptés aux nouvelles fonctionnalités

- 🎨 **Interface web enrichie** :
  - Ajout de la carte "Guirlande LED" au tableau de bord
  - Scripts JavaScript pour changements en temps réel
  - Intégration des handlers `/animation`, `/mode`, `/status`

- 📦 **Configuration projet** :
  - Version mise à jour : v0.1.0
  - Nom du projet : "Anim-Guirlande"
  - Tous les fichiers header versionés v0.1.0

- 📚 **Documentation complète** :
  - README.md entièrement réécrit pour le projet guirlande
  - Description détaillée des 14 animations
  - Guide d'installation et câblage
  - Spécifications techniques TB6612FNG
  - Guide de dépannage
  - CHANGELOG.md restructuré pour Semantic Versioning

### Conservé
- ✅ **Multi-environnement PlatformIO** :
  - ESP32-S3 N16R8 (16MB/8MB) - environnement par défaut
  - ESP32-S3 N8R8 (8MB/8MB)
  - ESP32 Classic DevKitC (4MB)

- ✅ **Affichage OLED et ST7789** :
  - Support simultané OLED SSD1306 et TFT ST7789
  - Affichage progression WiFi
  - Affichage adresse IP après connexion
  - Module `display.h/cpp` conservé

- ✅ **NeoPixel LED RGB** :
  - Feedback visuel d'état WiFi
  - Confirmation actions boutons
  - Heartbeat dans la boucle principale

- ✅ **Connectivité WiFi** :
  - WiFiMulti pour connexion multi-réseaux
  - Auto-reconnexion en cas de perte
  - Fichier `secrets.h` pour identifiants

- ✅ **Interface Web modulaire** :
  - Architecture v0.6.0 conservée
  - `web_styles.h`, `web_pages.h`, `web_interface.h`
  - Tableau de bord avec cartes (Matériel, Flash, RAM, PSRAM, WiFi, Système)

### Supprimé
- 🗑️ **Code inutilisé nettoyé** :
  - Fonctions et variables non nécessaires supprimées
  - Commentaires obsolètes retirés
  - Code mort éliminé

### Notes Techniques
- **Contrôle TB6612FNG** :
  - Direction 0 : Off (AIN1=LOW, AIN2=LOW)
  - Direction 1 : Sens A Forward (AIN1=HIGH, AIN2=LOW)
  - Direction 2 : Sens B Backward (AIN1=LOW, AIN2=HIGH)
  - Direction 3 : Brake/Court-circuit (AIN1=HIGH, AIN2=HIGH)
  - STBY doit être à HIGH pour activer le module

- **Animations** :
  - Utilisation alternance rapide entre Sens A/B pour simuler effets simultanés
  - Phases calculées avec `millis()` pour animations fluides
  - Pas de `delay()` pour ne pas bloquer la boucle principale

- **Capteurs** :
  - PIR : Lecture digitale (HIGH = mouvement détecté)
  - LDR : Lecture analogique ADC 12 bits (0-4095)
  - Temporisation 30s après détection PIR

### Migration depuis version précédente
Si vous migrez depuis Base_ESP32_S3 (v0.7.0) :

1. **Ajouter le matériel** :
   - Module TB6612FNG
   - Guirlande LED bi-directionnelle
   - Capteur PIR (optionnel)
   - Photorésistance LDR (optionnel)
   - 2 boutons poussoirs supplémentaires

2. **Câbler selon PIN_MAPPING.md** :
   - Voir schémas détaillés dans `docs/PIN_MAPPING.md`
   - Respecter les tensions d'alimentation (TB6612FNG : VM pour guirlande, VCC pour logique)

3. **Compiler et téléverser** :
   - Le code est rétrocompatible
  - Les anciens composants (OLED, TFT, NeoPixel) fonctionnent toujours
   - Les nouvelles fonctionnalités s'ajoutent sans casser l'existant

### Compatibilité
- ✅ ESP32-S3 DevKitC-1 (N16R8, N8R8)
- ✅ ESP32 DevKitC Classic
- ✅ Arduino-ESP32 Core v6.x
- ✅ PlatformIO 6.x
- ✅ Windows (testé), Linux et macOS (devraient fonctionner)

### Tests Réalisés
- [x] Compilation sans erreur
- [x] Upload firmware ESP32-S3
- [x] Connexion WiFi multi-réseaux
- [x] Serveur Web fonctionnel
- [x] Affichage OLED/TFT
- [x] Boutons physiques réactifs
- [x] Module guirlande (à tester avec matériel réel)
- [x] Capteurs PIR/LDR (à tester avec matériel réel)

### Prochaines Évolutions Possibles (Roadmap)
- 🔮 Intégration module RTC pour mode horaires réel
- 🔮 Configuration horaires via interface web (✅ Ajouté en v0.2.0)
- 🔮 Sauvegarde préférences en EEPROM/LittleFS
- 🔮 Création d'animations personnalisées via web
- 🔮 Support MQTT pour domotique
- 🔮 Synchronisation multi-guirlandes
- 🔮 Capteur de température/humidité pour effets réactifs

---

**Note** : Ce projet LED-Garland-Anim est une refonte complète du template Base_ESP32_S3, spécialisé pour le contrôle d'animations de guirlande LED bi-directionnelle avec module TB6612FNG.

[0.2.0]: https://github.com/votre-repo/LED-Garland-Anim/releases/tag/v0.2.0
[0.1.0]: https://github.com/votre-repo/LED-Garland-Anim/releases/tag/v0.1.0
