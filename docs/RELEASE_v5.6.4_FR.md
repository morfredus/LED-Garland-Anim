# Notes de version v5.6.4 (2026-02-02)

**Valide à partir de la version 5.6.4**

## 🐛 Corrections de bugs critiques

### 1. Restauration de la persistance du mode de fonctionnement
**Problème** : Le mode de fonctionnement (Permanent/Détection mouvement) n'était pas correctement restauré au démarrage, revenant toujours en mode permanent indépendamment des paramètres sauvegardés.

**Cause racine** : Incompatibilité de type NVS (stockage non volatil) — le mode était sauvegardé en tant que `u8` (non signé 8 bits) mais relu en tant que `i32` (entier signé 32 bits), causant une corruption de données.

**Solution** : Unification du stockage et de la récupération pour utiliser le type `i32` de manière cohérente, garantissant la persistance du mode entre les redémarrages.

**Impact** : Les utilisateurs peuvent maintenant compter sur la préservation du mode de fonctionnement choisi après un cycle d'alimentation ou un redémarrage.

---

### 2. Correction du mapping des pins pour ESP32-S3 Mini
**Problème** : Le pin du capteur de mouvement était incorrectement documenté comme GPIO7 dans tous les fichiers de documentation, mais le matériel utilise en réalité GPIO2.

**Solution** : Correction de `MOTION_SENSOR_PIN` de GPIO7 vers GPIO2 dans :
- [README.md](../README.md)
- [README_FR.md](../README_FR.md)
- [PIN_MAPPING.md](PIN_MAPPING.md)
- [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md)

**Impact** : La configuration matérielle correspond maintenant à la documentation, évitant les erreurs de connexion pour les utilisateurs d'ESP32-S3 Mini.

---

## 📚 Mises à jour de la documentation

### Tableau des commandes par boutons physiques
Mise à jour de toute la documentation utilisateur avec un tableau complet détaillant les fonctionnalités des boutons BOOT et USER :

| Bouton | Action | Fonction |
|--------|--------|----------|
| **BOOT** | Appui court | Changement de mode de fonctionnement |
| **BOOT** | Appui long (2s) | Redémarrage système |
| **USER** | Appui court | Changement d'animation guirlande (mode Manuel) |
| **USER** | Appui long (2s) | Activer/désactiver la matrice |

Ce tableau est maintenant inclus dans :
- Les fichiers README principaux ([README.md](../README.md) / [README_FR.md](../README_FR.md))
- La documentation de mapping des pins ([PIN_MAPPING.md](PIN_MAPPING.md) / [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md))

---

## 🔧 Détails techniques

### Correction du type NVS
```cpp
// Avant (incorrect)
nvs_set_u8(nvs_handle, "operating_mode", mode);  // Sauvegarde en u8
nvs_get_i32(nvs_handle, "operating_mode", &mode); // Lecture en i32 ❌

// Après (correct)
nvs_set_i32(nvs_handle, "operating_mode", mode);  // Sauvegarde en i32 ✅
nvs_get_i32(nvs_handle, "operating_mode", &mode); // Lecture en i32 ✅
```

### Mapping GPIO (ESP32-S3 Mini)
```cpp
// board_config.h
#ifdef TARGET_ESP32S3_MINI
    #define MOTION_SENSOR_PIN 2  // Précédemment documenté incorrectement comme GPIO7
#endif
```

---

## 📦 Matériel supporté

Cette version prend en charge toutes les plateformes existantes :
- **ESP32 Classic** (IdeaSpark/DevKitC)
- **ESP32 Wroom** (DevKit V1)
- **ESP32-S3 Mini** (esp32s3_mini)
- **ESP32-S3 Super Mini** (esp32s3_supermini)

Toutes les plateformes supportent l'affichage **OLED SSD1306 (I2C)** si connecté.

---

## 🚀 Installation

### PlatformIO
```bash
# Mise à jour vers v5.6.4
git pull origin main
git checkout v5.6.4
pio run -e <votre_carte> -t upload
```

Remplacez `<votre_carte>` par :
- `esp32devkitc` (ESP32 Classic)
- `esp32_wroom` (ESP32 Wroom)
- `esp32s3_mini` (ESP32-S3 Mini)
- `esp32s3_supermini` (ESP32-S3 Super Mini)

### Mise à jour OTA
Si OTA est déjà configuré sur votre appareil :
```bash
pio run -e <votre_carte> -t upload --upload-port <ip_appareil>
```

---

## 📖 Documentation

- [README principal](../README.md) / [README français](../README_FR.md)
- [Changelog complet](../CHANGELOG.md) / [Changelog français](../CHANGELOG_FR.md)
- [Guide de mapping des pins](PIN_MAPPING.md) / [Guide français](PIN_MAPPING_FR.md)
- [Guide matériel](HARDWARE_GUIDE.md) / [Guide français](HARDWARE_GUIDE_FR.md)
- [Dépannage](TROUBLESHOOTING.md) / [Dépannage français](TROUBLESHOOTING_FR.md)

---

## 🙏 Retours

Si vous rencontrez des problèmes avec cette version, veuillez ouvrir une issue sur le dépôt du projet avec :
- La plateforme matérielle utilisée
- Les étapes pour reproduire
- La sortie du moniteur série (si applicable)

---

**Version précédente** : [v5.6.3](RELEASE_v5.6.3_FR.md)  
**Changelog complet** : [CHANGELOG_FR.md](../CHANGELOG_FR.md)
