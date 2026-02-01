

# Guide de Connexion des Pins - LED-Garland-Anim v5.6.3

*Ce document est valide à partir de la version 5.6.3.*


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
| ESP32-S3 Mini / Super Mini | GPIO4 / GPIO5 | GPIO10 / GPIO11 / GPIO12 / GPIO13 | GPIO7 | GPIO7 | GPIO8 | GPIO0 |

---

## Notes
- Le firmware utilise **un seul bouton utilisateur** (BUTTON_1). Les autres entrées bouton ne sont pas utilisées.
- Sur ESP32-S3 Mini / Super Mini, le capteur de mouvement et la matrice partagent GPIO7, conformément à board_config.h.
- Voir board_config.h pour le mapping de référence.

**Note** : Ce guide accompagne le projet LED-Garland-Anim v1.11.3. Pour toute question ou problème, consultez le README.md et le code source commenté.

**Version du document : v1.13.0 (2026-01-06)**
