# 🚀 Release v1.2.1 – LED-Garland-Anim

## 🇫🇷 Notes de version (FR)

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

## 🇬🇧 Release Notes (EN)

### Added
- Support for auto-detection of motion sensor (PIR HC-SR501 or RCWL-0516) on GPIO 35
- Updated technical and user documentation (EN/FR)

### Changed
- Pin mapping: PIR_SENSOR replaced by MOTION_SENSOR_PIN (GPIO 35)
- All references to LDR/photoresistor removed (feature dropped)
- Mapping tables and guides adapted to actual supported hardware
- Troubleshooting and guides updated for new sensor logic

### Fixed
- Documentation consistency (EN/FR)
- Version numbers and dates in all documents

### Removed
- All code and documentation related to LDR/photoresistor
- Support for obsolete screens and boards (only ESP32 Classic + ST7789 supported)

---

## 📦 Assets
- Firmware binaire (PlatformIO build)
- Documentation complète (FR/EN)
- [CHANGELOG.md](CHANGELOG.md) | [CHANGELOG_FR.md](CHANGELOG_FR.md)
- [RELEASE_NOTES.md](docs/RELEASE_NOTES.md) | [RELEASE_NOTES_FR.md](docs/RELEASE_NOTES_FR.md)

---

Pour toute question ou retour, ouvrez une issue sur GitHub ou consultez la documentation !
