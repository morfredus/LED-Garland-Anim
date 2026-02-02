# Guide de Connexion des Pins - LED-Garland-Anim v5.6.5

*Ce document est valide a partir de la version 5.6.5.*

## Cartes Supportees

Ce projet supporte **deux cartes** :

| Carte | Environnement | Description |
|-------|---------------|-------------|
| **ESP32-S3 Super Mini** | `esp32s3_supermini` | Carte compacte, **choix par defaut** |
| **ESP32 Wroom DevKit V1** | `esp32wroom` | Carte de developpement classique |

---

## Mapping Complet des Pins

### ESP32-S3 Super Mini

| Fonction | GPIO | Description |
|----------|------|-------------|
| **I2C SDA** | GPIO 4 | Donnees ecran OLED |
| **I2C SCL** | GPIO 5 | Horloge ecran OLED |
| **TB6612 PWMA** | GPIO 10 | Luminosite guirlande (PWM) |
| **TB6612 AIN1** | GPIO 11 | Direction A guirlande |
| **TB6612 AIN2** | GPIO 12 | Direction B guirlande |
| **TB6612 STBY** | GPIO 13 | Activation guirlande (HIGH = ON) |
| **DATA Matrice** | GPIO 7 | Donnees matrice NeoPixel 8x8 |
| **Capteur Mouvement** | GPIO 2 | Entree PIR ou RCWL-0516 |
| **Bouton Utilisateur** | GPIO 8 | Controle animation/mode |
| **Bouton BOOT** | GPIO 0 | Integre (appui long = redemarrage) |
| **LED** | GPIO 8 | LED integree |

### ESP32 Wroom DevKit V1

| Fonction | GPIO | Description |
|----------|------|-------------|
| **I2C SDA** | GPIO 21 | Donnees ecran OLED |
| **I2C SCL** | GPIO 22 | Horloge ecran OLED |
| **TB6612 PWMA** | GPIO 12 | Luminosite guirlande (PWM) |
| **TB6612 AIN1** | GPIO 25 | Direction A guirlande |
| **TB6612 AIN2** | GPIO 33 | Direction B guirlande |
| **TB6612 STBY** | GPIO 14 | Activation guirlande (HIGH = ON) |
| **DATA Matrice** | GPIO 27 | Donnees matrice NeoPixel 8x8 |
| **Capteur Mouvement** | GPIO 35 | Entree PIR ou RCWL-0516 |
| **Bouton Utilisateur** | GPIO 16 | Controle animation/mode |
| **Bouton BOOT** | GPIO 0 | Integre (appui long = redemarrage) |
| **LED** | GPIO 2 | LED integree |

---

## Tableau de Reference Rapide

| Fonction | ESP32-S3 Super Mini | ESP32 Wroom |
|----------|---------------------|-------------|
| I2C SDA | GPIO 4 | GPIO 21 |
| I2C SCL | GPIO 5 | GPIO 22 |
| TB6612 PWMA | GPIO 10 | GPIO 12 |
| TB6612 AIN1 | GPIO 11 | GPIO 25 |
| TB6612 AIN2 | GPIO 12 | GPIO 33 |
| TB6612 STBY | GPIO 13 | GPIO 14 |
| DATA Matrice | GPIO 7 | GPIO 27 |
| Capteur Mouvement | GPIO 2 | GPIO 35 |
| Bouton Utilisateur | GPIO 8 | GPIO 16 |
| Bouton BOOT | GPIO 0 | GPIO 0 |

---

## Controles par Boutons Physiques

Le firmware utilise **un bouton utilisateur** plus le bouton BOOT integre :

| Bouton | Action | Fonction |
|--------|--------|----------|
| **Bouton Utilisateur** | 1 clic | Animation suivante guirlande |
| **Bouton Utilisateur** | 2 clics | Animation suivante matrice |
| **Bouton Utilisateur** | Appui long | Changement de mode |
| **Bouton BOOT** | Appui long | Redemarrage systeme |

**GPIO du Bouton Utilisateur :**
- ESP32-S3 Super Mini : **GPIO 8**
- ESP32 Wroom : **GPIO 16**

---

## Conseils de Cablage pour Debutants

### Ecran OLED (SSD1306)
Connectez votre ecran OLED en I2C :
- **VCC** vers 3.3V
- **GND** vers GND
- **SDA** vers le pin SDA (GPIO 4 sur S3 Super Mini, GPIO 21 sur Wroom)
- **SCL** vers le pin SCL (GPIO 5 sur S3 Super Mini, GPIO 22 sur Wroom)

### Driver Moteur TB6612FNG (Controle Guirlande)
- **PWMA** controle la luminosite (0-255)
- **AIN1/AIN2** controlent le sens du courant
- **STBY** doit etre HIGH pour que le moteur fonctionne
- **VM** vers l'alimentation de votre guirlande (generalement 12V ou 24V)
- **VCC** vers 3.3V
- **GND** vers GND (partage avec l'ESP32)

### Matrice NeoPixel 8x8
- **DIN** (Data In) vers le pin DATA Matrice
- **VCC** vers 5V (utilisez une alimentation externe pour beaucoup de LEDs)
- **GND** vers GND (partage avec l'ESP32)

### Capteur de Mouvement (PIR ou RCWL-0516)
- **OUT** vers le pin Capteur de Mouvement
- **VCC** vers 3.3V ou 5V (verifiez votre capteur)
- **GND** vers GND

---

## Notes

- Le mapping de reference est defini dans `include/board_config.h`
- L'ecran OLED est optionnel mais recommande pour afficher le statut
- Le capteur de mouvement est optionnel (uniquement necessaire pour les modes declenchement par mouvement)
