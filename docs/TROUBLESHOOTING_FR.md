
## 🖥️ Schéma de connexion LCD ST7789 (ESP32 Classic)

```
ESP32 Classic         LCD ST7789
┌─────────┐        ┌──────────┐
│         │        │          │
│ GPIO 23 ├───────►│ MOSI/SDA │
│ GPIO 18 ├───────►│ SCLK/SCL │
│ GPIO 15 ├───────►│ CS       │
│ GPIO  2 ├───────►│ DC       │
│ GPIO  4 ├───────►│ RST      │
│ GPIO 32 ├───────►│ BL       │
│   3V3   ├───────►│ VCC      │
│   GND   ├───────►│ GND      │
│         │        │          │
└─────────┘        └──────────┘
```

| Signal | Pin GPIO | Description | Macro C | Changement |
|--------|----------|-------------|---------|------------|
| MOSI   | GPIO 23  | Données SPI | LCD_MOSI| 🔄 #2 (2025-12-30) |
| SCLK   | GPIO 18  | Horloge SPI | LCD_SCLK| 🔄 #2 (2025-12-30) |
| CS     | GPIO 15  | Chip Select | LCD_CS  | 🔄 #2 (2025-12-30) |
| DC     | GPIO 2   | Data/Command| LCD_DC  | 🔄 #2 (2025-12-30) |
| RST    | GPIO 4   | Reset       | LCD_RST | 🔄 #2 (2025-12-30) |
| BLK    | GPIO 32  | Backlight   | LCD_BLK | 🔄 #2 (2025-12-30) |

> **Historique des changements LCD ST7789 :**
> - #2 (2025-12-30) : Nouveau mapping (MOSI=23, SCLK=18, CS=15, DC=2, RST=4, BLK=32)
> - #1 (2025-12-29) : Mapping initial
# Dépannage - LED-Garland-Anim v0.8.0

Guide rapide pour diagnostiquer les problèmes sur ESP32-S3 et ESP32 Classic.

## Check-list Express
- Flasher le bon environnement (`esp32s3_n16r8`, `esp32s3_n8r8` ou `esp32devkitc`).
- Vérifier les identifiants WiFi dans `include/secrets.h`.
- Respecter les pins de `include/board_config.h` (S3 : PIR_SENSOR 14, LDR_SENSOR 15, BUTTON_1 16, BUTTON_2 17 ; Classic : PIR_SENSOR 35, LDR_SENSOR 34, BUTTON_1 4, BUTTON_2 16).
- Masse commune entre ESP32, TB6612FNG et alimentation externe.
- Ouvrir le moniteur série en 115200 pour lire les logs.

## WiFi / Réseau
- Bloqué sur "Connecting" : réseau 2.4 GHz obligatoire, vérifier SSID/mot de passe et filtrage MAC.
- Pas d'IP affichée : vérifier la liste DHCP du routeur, redémarrer carte + box si besoin.
- Coupures fréquentes : rapprocher du point d'accès, éviter les hubs USB peu puissants, limiter les obstacles métalliques.

## Interface Web Injoignable
- Pinger l'IP affichée ; si échec, revoir WiFi/DHCP.
- Vider le cache ou utiliser un onglet privé ; utiliser `http://<ip>` (pas HTTPS).
- Si certaines pages répondent mal, redémarrer la carte pour relancer le serveur web interne.

## Boutons (Animation/Mode)
- S3 : BUTTON_1 GPIO16, BUTTON_2 GPIO17. Classic : BUTTON_1 GPIO4, BUTTON_2 GPIO16. BUTTON_BOOT sur GPIO0.
- Boutons actifs bas avec pull-up interne ; le câblage doit aller à GND à l'appui.
- Si rebonds, vérifier la longueur des fils et l'état des interrupteurs ; les logs série doivent afficher les pressions.

## Capteurs
- PIR_SENSOR : S3 GPIO14 ; Classic GPIO35. Alimentez en 5V + GND, ajustez sensibilité et temporisation.
- LDR_SENSOR : S3 GPIO15 ; Classic GPIO34. Vérifier le diviseur 10kΩ + LDR et les lectures ADC (0–4095).
- Si détection permanente, éloigner des sources de chaleur/soleil ; si jamais, augmenter la sensibilité.

## Affichages
- OLED (I2C 0x3C/0x3D) : SDA/SCL selon board_config, pull-ups généralement sur le module. Inverser SDA/SCL si écran noir.
// LCD ST7789 : contrôler toutes les lignes SPI et l'alim BL (backlight).
- Couleurs erratiques : raccourcir les câbles, vérifier la masse commune.

## Sortie Guirlande / TB6612FNG
- TB6612_STBY doit être HIGH (GPIO8 sur S3, GPIO14 sur Classic).
- Direction : TB6612_AIN1/TB6612_AIN2 (GPIO6/4 sur S3, GPIO32/33 sur Classic). Intensité : TB6612_PWMA (GPIO5 sur S3, GPIO12 sur Classic).
- VM doit être alimenté en 5–15V par une source externe ; ne pas alimenter la guirlande via l'USB seul.
- Si un sens ne fonctionne pas, inverser AO1/AO2 pour tester et inspecter les soudures.

## Problèmes de Build / Upload
- Compiler avec `pio run -e <env>` ; si upload difficile, maintenir BOOT (GPIO0) sur Classic au premier flash.
- Purger le cache `.pio` si changement majeur de framework.

Si le problème persiste, capturez les logs série depuis le boot et comparez le câblage aux tableaux de correspondance GPIO dans la documentation.
