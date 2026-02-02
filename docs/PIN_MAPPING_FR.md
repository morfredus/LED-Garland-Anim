# Guide de Connexion des Pins - LED-Garland-Anim v5.6.4

*Ce document est valide à partir de la version 5.6.4.*

## Plateformes supportées
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32 Wroom (DevKit V1)
- ESP32-S3 Mini (esp32s3_mini)
- ESP32-S3 Super Mini (esp32s3_supermini)

> 📌 **Affichage OLED SSD1306 (I2C)** disponible sur toutes les plateformes si connecté.
> 📌 **Rotation OLED** : Configurable via `OLED_ROTATION` dans config.h (U8G2_R0, U8G2_R1, U8G2_R2, U8G2_R3)

---

## Mapping principal (par carte)

| Carte | I2C SDA / SCL | TB6612 PWMA / AIN1 / AIN2 / STBY | DATA Matrice | Capteur de mouvement | Bouton utilisateur (BUTTON_1) | BOOT |
|---|---|---|---|---|---|---|
| ESP32 Classic | GPIO21 / GPIO22 | GPIO12 / GPIO25 / GPIO33 / GPIO14 | GPIO27 | GPIO35 | GPIO16 | GPIO0 |
| ESP32 Wroom | GPIO21 / GPIO22 | GPIO12 / GPIO25 / GPIO33 / GPIO14 | GPIO27 | GPIO35 | GPIO16 | GPIO0 |
| ESP32-S3 Mini / Super Mini | GPIO4 / GPIO5 | GPIO10 / GPIO11 / GPIO12 / GPIO13 | GPIO7 | GPIO2 | GPIO8 | GPIO0 |

---

## Contrôles par boutons physiques

Le firmware utilise **un seul bouton utilisateur** (BUTTON_1) plus le bouton BOOT intégré :

| Bouton | Action | Fonction |
|--------|--------|----------|
| **BUTTON_1** | 1 clic | Animation suivante guirlande |
| **BUTTON_1** | 2 clics | Animation suivante matrice |
| **BUTTON_1** | Appui long | Changement de mode |
| **BOOT** | Appui long | Redémarrage système |

---

## Notes
- Sur ESP32-S3 Mini / Super Mini, le capteur de mouvement utilise GPIO2 et la matrice utilise GPIO7.
- Voir board_config.h pour le mapping de référence.
