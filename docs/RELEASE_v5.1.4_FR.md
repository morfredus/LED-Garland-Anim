# Release v5.1.4 – 2026-01-07

## Résumé
Release complète et consolidée combinant le nettoyage du firmware (suppression Telegram) et les améliorations documentaires complètes dans un seul package unifié.

## Points clés

### 🔧 Modifications du Firmware

#### Suppression du module Telegram
- **Fichiers supprimés** : 
  - `src/telegram_control.cpp` (329 lignes)
  - `include/telegram_control.h` (33 lignes)
- **Toutes les références Telegram supprimées** du code et documentation
- **Impact** : Codebase plus propre, moins de bloat, maintenance simplifiée
- **Compatibilité rétro** : ✅ Entièrement compatible avec les configurations existantes

### 📚 Améliorations de la Documentation

#### Synchronisation des versions
Toute la documentation synchronisée à v5.1.4 pour la cohérence :
- ✅ README.md / README_FR.md
- ✅ USER_GUIDE.md / USER_GUIDE_FR.md
- ✅ ARCHITECTURE.md / ARCHITECTURE_FR.md
- ✅ PIN_MAPPING.md / PIN_MAPPING_FR.md
- ✅ TROUBLESHOOTING.md / TROUBLESHOOTING_FR.md
- ✅ OTA_UPDATE.md / OTA_UPDATE_FR.md
- ✅ PIR_SENSOR_SETUP.md / PIR_SENSOR_SETUP_FR.md
- ✅ RADAR_SENSOR_SETUP.md / RADAR_SENSOR_SETUP_FR.md

#### Fichiers obsolètes supprimés
- `docs/FIXES_v1.12.0.md`
- `docs/RELEASE_v1.10.0.md` à `v1.12.1.md` (4 fichiers)
- `docs/RELEASE_v3.0.1.md` et `v3.0.2.md` (2 fichiers)

#### Nouveaux guides pour débutants (Bilingue EN/FR)
- **QUICKSTART.md/FR** : Guide de démarrage rapide 5 minutes
  - Instructions étape par étape
  - Conseils de dépannage
  - Tous les composants expliqués
  
- **HARDWARE_GUIDE.md/FR** : Liste d'achat complète des composants
  - Où acheter chaque composant
  - Spécifications et info de compatibilité
  - Coûts estimés actuels par région
  - Fournisseurs recommandés mondialement

#### Améliorations de la structure documentation
- README.md restructuré : section USB/OTA déplacée au bon endroit
- Tous les guides réorganisés pour meilleur flux logique
- En-têtes de versions cohérents dans tous les documents
- Références croisées améliorées

### 🏗️ Détails Techniques

#### Spécifications de compilation
- **Cible** : esp32devkitc (ESP32 Classic)
- **Flash** : 71,3 % (935 105 octets / 1 310 720 octets)
- **RAM** : 15,5 % (50 648 octets / 327 680 octets)
- **État compilation** : ✅ SUCCÈS (aucune erreur/avertissement)

#### Fichiers modifiés
- **Code** : 3 fichiers (platformio.ini, include/config.h, src/main.cpp)
- **Documentation** : 28+ fichiers mis à jour à v5.1.4
- **Nouveaux fichiers** : 2 (guides QUICKSTART, HARDWARE_GUIDE EN/FR)
- **Fichiers supprimés** : 7 notes de release obsolètes

### 🎯 Ce qui est corrigé/changé

**Performance** :
- Aucun changement de performance (amélioration qualité code uniquement)

**Fonctionnalités** :
- Aucune nouvelle fonctionnalité (release nettoyage)

**Compatibilité** :
- ✅ Entièrement compatible rétro
- ✅ Toute fonctionnalité existante préservée
- ✅ Tous réglages existants compatibles

### 📦 Package Unifié Unique

Cette release consolide deux mises à jour séparées (v5.1.2 firmware + v5.1.3 documentation) en un seul package v5.1.4 cohésif pour :
- Téléchargement plus simple (une release au lieu de deux)
- Historique des versions plus clair
- Point de référence unique pour utilisateurs
- Gestion du changelog facilitée

### 🎁 Inclus dans Cette Release

✅ Firmware complet nettoyé (pas de module Telegram)  
✅ Toute la documentation mise à jour (v5.1.4)  
✅ 4 nouveaux guides débutants (QUICKSTART + HARDWARE_GUIDE EN/FR)  
✅ Support bilingue (Anglais + Français)  
✅ Notes de release complètes  
✅ CHANGELOG complet avec entrée v5.1.4  

## Notes de mise à jour

### Depuis v5.1.1
1. Flasher le firmware v5.1.4 (USB ou OTA)
2. Aucun changement de configuration requis
3. Tous réglages existants préservés
4. Aucun changement cassant

### Depuis v5.1.2 ou v5.1.3
- Si vous avez déjà mis à jour vers v5.1.2 ou v5.1.3, aucune action requise
- v5.1.4 est la version consolidée, recommandée

### Utilisateurs pour la première fois
Commencer ici :
1. **Lire** : [docs/QUICKSTART_FR.md](docs/QUICKSTART_FR.md)
2. **Acheter** : Vérifier [docs/HARDWARE_GUIDE_FR.md](docs/HARDWARE_GUIDE_FR.md)
3. **Câbler** : Suivre [docs/PIN_MAPPING_FR.md](docs/PIN_MAPPING_FR.md)
4. **Construire** : Utiliser [BUILD_GUIDE_FR.md](docs/BUILD_GUIDE_FR.md) (si disponible)
5. **Explorer** : Fonctionnalités complètes dans [docs/USER_GUIDE_FR.md](docs/USER_GUIDE_FR.md)

## Historique des versions

| Version | Date | Type | Changements notables |
|---------|------|------|----------------------|
| 5.1.4 | 2026-01-07 | Release | Consolidé v5.1.2 + v5.1.3 |
| 5.1.3 | 2026-01-07 | PATCH | Nettoyage doc (non release standalone) |
| 5.1.2 | 2026-01-07 | PATCH | Suppression Telegram (non release standalone) |
| 5.1.1 | 2026-01-07 | PATCH | Correction indépendance intervalle matrice |
| 5.1.0 | 2026-01-06 | MINOR | Réorganisation layout LCD |
| 5.0.0 | 2026-01-06 | MAJOR | Design LCD animé festif |

## Installation & Téléchargements

**Disponible à** : https://github.com/morfredus/LED-Garland-Anim/releases/tag/v5.1.4

**Inclut** :
- Code source
- Firmware compilé (si disponible)
- Documentation complète
- Tous guides débutants

## Support & Dépannage

- **Aide rapide** : Voir [docs/QUICKSTART_FR.md](docs/QUICKSTART_FR.md)
- **Problèmes ?** : Vérifier [docs/TROUBLESHOOTING_FR.md](docs/TROUBLESHOOTING_FR.md)
- **Questions matériel** : Lire [docs/HARDWARE_GUIDE_FR.md](docs/HARDWARE_GUIDE_FR.md)
- **Problèmes câblage** : Consulter [docs/PIN_MAPPING_FR.md](docs/PIN_MAPPING_FR.md)
- **Bugs/Problèmes** : Signaler sur GitHub Issues

## Classification SEMVER

**v5.1.4 (PATCH)**
- Justification : Nettoyage code (suppression Telegram) + améliorations documentation ; aucun changement fonctionnel des fonctionnalités expédiées ; entièrement compatible rétro

---

**Date de release** : 7 janvier 2026  
**Plateforme cible** : ESP32 Classic (IdeaSpark / DevKitC)  
**Framework** : Arduino ESP32 (espressif32@^6)  
**Langues documentation** : Bilingue (Anglais + Français)  

🎉 **Merci d'utiliser LED-Garland-Anim !**
