# Release v5.1.5 – 2026-01-07

**Version**: 5.1.5 (PATCH)  
**Type de release**: Mise à jour mineure  
**Date**: 2026-01-07  
**Plateforme**: ESP32 Classic (IdeaSpark/DevKitC)  
**État de compilation**: ✅ SUCCÈS  

---

## 📋 Résumé

La version 5.1.5 ajoute le fichier template manquant **`secrets_example.h`** pour faciliter la configuration WiFi, en plus de toutes les améliorations de la v5.1.4 (suppression Telegram + révision complète de la documentation).

C'est la **version complète et recommandée** qui combine:
- **v5.1.2 firmware**: Suppression du module Telegram (code plus propre)
- **v5.1.3 documentation**: Audit complet et synchronisation des versions
- **v5.1.5 config**: Ajout du template `secrets_example.h` pour la commodité des utilisateurs

---

## 🆕 Nouveautés de v5.1.5

### ✅ Ajouté
- **`include/secrets_example.h`**: Fichier template pour la configuration du réseau WiFi
  - Fournit une structure d'exemple pour les utilisateurs configurant leurs identifiants WiFi
  - Montre clairement comment ajouter plusieurs réseaux
  - Empêche les utilisateurs de modifier accidentellement `secrets.h` (qui est git-ignoré)
  - **Utilisation**: Copier vers `include/secrets.h`, éditer avec vos identifiants WiFi

### ✨ Depuis v5.1.4 (Inclus dans v5.1.5)

#### Ajouté
- **Nouveaux guides pour débutants** (bilingues FR/EN):
  - `docs/QUICKSTART.md` / `QUICKSTART_FR.md`: Guide de démarrage rapide (5 minutes)
  - `docs/HARDWARE_GUIDE.md` / `HARDWARE_GUIDE_FR.md`: Liste complète de composants avec fournisseurs
- **Notes de release pour v5.1.4**:
  - `docs/RELEASE_v5.1.4.md` (Anglais)
  - `docs/RELEASE_v5.1.4_FR.md` (Français)

#### Supprimé (v5.1.2)
- Suppression des fichiers du module Telegram inutilisé: `src/telegram_control.cpp`, `include/telegram_control.h`
- Suppression de 7 fichiers de notes de release obsolètes (séries v1.x, v3.x)
- Suppression de toutes les références Telegram de la documentation

#### Modifié (v5.1.4)
- **Synchronisation des versions** dans toute la documentation à v5.1.4 (maintenant v5.1.5)
- **README.md restructuré**: Section "Choisir l'upload USB ou OTA" repositionnée
- **Version firmware**: 5.1.2 → 5.1.5 dans platformio.ini, config.h, main.cpp

---

## 📦 Contenu du package

### Fichiers firmware
- ✅ `platformio.ini` (PROJECT_VERSION="5.1.5")
- ✅ `include/config.h` (@version 5.1.5)
- ✅ `src/main.cpp` (@version 5.1.5)
- ✅ **`include/secrets_example.h`** (NOUVEAU - Template pour WiFi)
- ✅ Tous les fichiers source (aucune référence Telegram)

### Documentation
- ✅ **README.md / README_FR.md** (v5.1.5)
- ✅ **USER_GUIDE.md / USER_GUIDE_FR.md** (v5.1.5)
- ✅ **QUICKSTART.md / QUICKSTART_FR.md** (v5.1.5)
- ✅ **HARDWARE_GUIDE.md / HARDWARE_GUIDE_FR.md** (v5.1.5)
- ✅ **ARCHITECTURE.md / ARCHITECTURE_FR.md** (v5.1.5)
- ✅ **PIN_MAPPING.md / PIN_MAPPING_FR.md** (v5.1.5)
- ✅ **TROUBLESHOOTING.md / TROUBLESHOOTING_FR.md** (v5.1.5)
- ✅ **OTA_UPDATE.md / OTA_UPDATE_FR.md** (v5.1.5)
- ✅ **PIR_SENSOR_SETUP.md / PIR_SENSOR_SETUP_FR.md** (v5.1.5)
- ✅ **RADAR_SENSOR_SETUP.md / RADAR_SENSOR_SETUP_FR.md** (v5.1.5)
- ✅ **RELEASE_v5.1.5.md / RELEASE_v5.1.5_FR.md** (Ce fichier)
- ✅ **CHANGELOG.md / CHANGELOG_FR.md** complet avec entrée v5.1.5

---

## 🚀 Démarrage rapide

### Configuration initiale

1. **Cloner ou télécharger** la version v5.1.5
2. **Configurer WiFi**:
   - Copier `include/secrets_example.h` → `include/secrets.h`
   - Éditer `include/secrets.h` avec vos identifiants WiFi:
     ```cpp
     inline const char* WIFI_NETWORKS[][2] = {
         {"VotreSSID_1", "VotreMotDePasse_1"},
         {"VotreSSID_2", "VotreMotDePasse_2"}
     };
     ```
   - Sauvegarder et passer à la compilation

3. **Compiler le firmware** (PlatformIO):
   ```bash
   pio run -e esp32devkitc
   ```

4. **Flasher le firmware** (USB ou OTA):
   - USB: `pio run --target upload -e esp32devkitc`
   - OTA: [Voir OTA_UPDATE_FR.md pour les détails](./OTA_UPDATE_FR.md)

5. **Accéder à l'interface web**:
   - Ouvrir le navigateur: `http://garland.local` (ou adresse IP)
   - Configurer les animations, couleurs et capteurs selon vos préférences

---

## 🔧 Spécifications techniques

### Support matériel
- **Microcontrôleur**: ESP32 Classic (IdeaSpark ou DevKitC)
- **Mémoire Flash**: 4MB
- **RAM**: 320KB
- **Broches GPIO**: 28 (23 numériques, 15 analogiques)
- **WiFi**: 802.11 b/g/n (2,4 GHz)
- **Support OTA**: ✅ ArduinoOTA + Web OTA

### Informations de compilation
- **Framework**: Arduino (espressif32@^6)
- **Langage**: C++ (C++17)
- **Taille de compilation**:
  - **Flash**: ~72% (935 105 / 1 310 720 octets)
  - **RAM**: ~16% (50 648 / 327 680 octets)
- **Compilation**: ✅ SUCCÈS (aucune erreur/avertissement)

### Fonctionnalités supportées
- 🎄 Animation guirlande LED avec 5 modes
- 📺 Matrice LED 8x8 avec effets
- 💡 Affichage LCD ST7789 (320×240)
- 🌐 Interface de contrôle basée sur le web (responsive)
- 📱 Configuration WiFi en temps réel (changement SSID/mot de passe)
- 🔌 Contrôle par bouton GPIO (changement mode + animation)
- 🚨 Intégration capteur PIR (optionnel)
- 🎯 Intégration capteur radar RCWL-0516 (optionnel)
- 🔄 Mises à jour firmware (OTA + USB)
- 💾 Persistance NVS (paramètres survivent au redémarrage)
- 🌙 Personnalisation du nom d'appareil (mDNS: `nom-appareil.local`)

---

## 📝 Historique des versions

| Version | Date | Type | Notes |
|---------|------|------|-------|
| 5.1.5 | 2026-01-07 | PATCH | Ajout template `secrets_example.h` + consolidation v5.1.2+v5.1.3+v5.1.4 |
| 5.1.4 | 2026-01-07 | PATCH | Consolidé v5.1.2 (suppression Telegram) + v5.1.3 (sync doc) |
| 5.1.3 | 2026-01-07 | PATCH | Révision complète documentation (28+ fichiers mis à jour à v5.1.2) |
| 5.1.2 | 2026-01-07 | PATCH | Suppression module Telegram inutilisé (src/telegram_control.*) |
| 5.1.1 | 2026-01-07 | PATCH | Correction indépendance intervalle animation matrice |
| 5.1.0 | 2026-01-06 | MINOR | Réorganisation affichage LCD animé zones empilées pleine largeur |
| 5.0.0 | 2025-12-25 | MAJOR | Refactorisation majeure: architecture modulaire, interface web, multi-capteurs |

---

## 🎯 Recommandation

✅ **v5.1.5 est la version recommandée** pour tous les utilisateurs:
- Inclut toutes les fonctionnalités de v5.0.0 à v5.1.4
- Code propre, sans Telegram
- Documentation complète (FR/EN)
- Configuration WiFi facile avec le template `secrets_example.h`
- Complètement testée et stable

---

## 📖 Liens documentation

- **[README](../README_FR.md)** – Vue d'ensemble du projet et installation
- **[Démarrage rapide](./QUICKSTART_FR.md)** – Guide de configuration 5 minutes
- **[Guide utilisateur](./USER_GUIDE_FR.md)** – Documentation complète des fonctionnalités
- **[Configuration matérielle](./HARDWARE_GUIDE_FR.md)** – Approvisionnement composants et connexions
- **[Architecture](./ARCHITECTURE_FR.md)** – Structure du code et conception
- **[Cartographie des broches](./PIN_MAPPING_FR.md)** – Schémas de câblage et assignation GPIO
- **[Mises à jour OTA](./OTA_UPDATE_FR.md)** – Procédures de mise à jour firmware
- **[Dépannage](./TROUBLESHOOTING_FR.md)** – Guide de résolution de problèmes
- **[Capteur PIR](./PIR_SENSOR_SETUP_FR.md)** – Configuration détection de mouvement
- **[Capteur Radar](./RADAR_SENSOR_SETUP_FR.md)** – Intégration radar Doppler

---

## 🆘 Support

Pour les problèmes ou questions:
1. **Vérifier [TROUBLESHOOTING_FR.md](./TROUBLESHOOTING_FR.md)** pour les problèmes courants
2. **Examiner [QUICKSTART_FR.md](./QUICKSTART_FR.md)** pour les conseils de configuration
3. **Lire [USER_GUIDE_FR.md](./USER_GUIDE_FR.md)** pour la documentation des fonctionnalités
4. **Ouvrir un ticket** sur [GitHub](https://github.com/morfredus/LED-Garland-Anim/issues)

---

**Bon décor! 🎄✨**

**Disponible à**: https://github.com/morfredus/LED-Garland-Anim/releases/tag/v5.1.5
