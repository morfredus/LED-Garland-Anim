# Release v5.1.2 – 2026-01-07

## Résumé
- Suppression complète du module bot Telegram (code + documentation).
- Nettoyage complet de la documentation et synchronisation des versions.
- Taille du firmware réduite, base de code simplifiée.

## Points clés

### 🗑️ Suppression du module Telegram (PATCH)
- **Fichiers supprimés** : 
  - `src/telegram_control.cpp` (329 lignes)
  - `include/telegram_control.h` (33 lignes)
- **Toutes les références supprimées** de :
  - README.md / README_FR.md
  - CHANGELOG.md / CHANGELOG_FR.md
  - docs/RELEASE_v5.1.0.md/FR
  - docs/RELEASE_v1.11.3.md
- **Raison** : Le module Telegram n'était pas utilisé et ajoutait une complexité inutile

### 📚 Nettoyage de la documentation (v5.1.3)
- **Notes de release obsolètes supprimées** (8 fichiers) :
  - FIXES_v1.12.0.md
  - RELEASE_v1.10.0.md à v1.12.1.md (4 fichiers)
  - RELEASE_v3.0.1.md, v3.0.2.md
- **Synchronisation des versions** dans toute la documentation (v5.1.2) :
  - README.md/FR
  - USER_GUIDE.md/FR
  - ARCHITECTURE.md/FR
  - PIN_MAPPING.md/FR
  - TROUBLESHOOTING.md/FR
  - PIR_SENSOR_SETUP.md/FR
  - RADAR_SENSOR_SETUP.md/FR
- **Restructuration README.md** : Section USB/OTA déplacée à l'emplacement approprié (après Installation)

## Fichiers modifiés

### Modifications du code (v5.1.2)
- platformio.ini (changement de version : 5.1.1 → 5.1.2)
- include/config.h (en-tête de version mis à jour)
- src/main.cpp (en-tête de version mis à jour)
- Supprimés : src/telegram_control.cpp, include/telegram_control.h

### Modifications de la documentation (v5.1.2 + v5.1.3)
- Racine : README.md/FR, CHANGELOG.md/FR
- docs/ : USER_GUIDE, ARCHITECTURE, PIN_MAPPING, TROUBLESHOOTING, PIR_SENSOR_SETUP, RADAR_SENSOR_SETUP (tous EN/FR)
- docs/ : RELEASE_v5.1.0/FR, RELEASE_v1.11.3.md
- Supprimés : 8 fichiers de notes de release obsolètes

## État de compilation

**Compilation : ✅ SUCCÈS**
- Flash : 71,3 % (935 105 octets / 1 310 720)
- RAM : 15,5 % (50 648 octets / 327 680)
- Aucune erreur ou avertissement de compilation

## Notes de mise à jour

### Depuis v5.1.1
1. Flasher le firmware v5.1.2 (USB ou OTA)
2. Aucun changement de configuration requis
3. Tous les réglages existants préservés (NVS)
4. Fonctionnalité identique (suppression Telegram uniquement)

### Améliorations de la documentation
- Mise à jour de toutes les versions de documents pour cohérence
- Suppression des notes de release obsolètes (séries v1.x, v3.x)
- Amélioration de la structure du README (section USB/OTA déplacée)
- Tous les guides référencent maintenant la version actuelle (5.1.2)

## Classification SEMVER

- **v5.1.2 (PATCH)** : Suppression du module Telegram
  - Aucun changement cassant
  - Aucune nouvelle fonctionnalité
  - Nettoyage du code et suppression du module inutilisé
  
- **v5.1.3 (PATCH)** : Nettoyage de la documentation
  - Aucune modification de code
  - Synchronisation des versions de documentation
  - Suppression de fichiers obsolètes

## Prochaines étapes

Les futures releases se concentreront sur :
- Documentation améliorée pour débutants (QUICKSTART.md)
- Guide matériel avec liste de composants (HARDWARE_GUIDE.md)
- Guide de compilation détaillé (BUILD_GUIDE.md)

---

**Date de release** : 7 janvier 2026  
**Cible** : esp32devkitc  
**Framework** : Arduino (ESP32)  
**Plateforme** : Espressif 32
