# Dépannage - LED-Garland-Anim v0.6.2

Guide rapide pour diagnostiquer les problèmes sur ESP32-S3 et ESP32 Classic.

## Check-list Express
- Flasher le bon environnement (`esp32s3_n16r8`, `esp32s3_n8r8` ou `esp32devkitc`).
- Vérifier les identifiants WiFi et le token/chat Telegram dans `include/secrets.h`.
- Respecter les pins de `include/board_config.h` (S3 : PIR 14, LDR 15, boutons 16/17 ; Classic : PIR 35, LDR 34, boutons 4/16).
- Masse commune entre ESP32, TB6612FNG et alimentation externe.
- Ouvrir le moniteur série en 115200 pour lire les logs.

## WiFi / Réseau
- Bloqué sur "Connecting" : réseau 2.4 GHz obligatoire, vérifier SSID/mot de passe et filtrage MAC.
- Pas d'IP affichée : vérifier la liste DHCP du routeur, redémarrer carte + box si besoin.
- Coupures fréquentes : rapprocher du point d'accès, éviter les hubs USB peu puissants, limiter les obstacles métalliques.

## Bot Telegram
- Pas de réponse : confirmer `TELEGRAM_BOT_TOKEN` et `TELEGRAM_CHAT_ID` (chat autorisé uniquement).
- Erreurs TLS : laisser `client.setInsecure()` et attendre que le WiFi ait synchronisé l'heure.
- Bot muet après reboot : contrôler l'IP sur OLED/TFT, envoyer `/status` pour vérifier la liaison.

## Interface Web Injoignable
- Pinger l'IP affichée ; si échec, revoir WiFi/DHCP.
- Vider le cache ou utiliser un onglet privé ; utiliser `http://<ip>` (pas HTTPS).
- Si certaines pages répondent mal, redémarrer la carte pour relancer le serveur web interne.

## Boutons (Animation/Mode)
- S3 : BTN1 GPIO16, BTN2 GPIO17. Classic : BTN1 GPIO4, BTN2 GPIO16. BOOT sur GPIO0.
- Boutons actifs bas avec pull-up interne ; le câblage doit aller à GND à l'appui.
- Si rebonds, vérifier la longueur des fils et l'état des interrupteurs ; les logs série doivent afficher les pressions.

## Capteurs
- PIR : S3 GPIO14 ; Classic GPIO35. Alimentez en 5V + GND, ajustez sensibilité et temporisation.
- LDR : S3 GPIO15 ; Classic GPIO34. Vérifier le diviseur 10kΩ + LDR et les lectures ADC (0–4095).
- Si détection permanente, éloigner des sources de chaleur/soleil ; si jamais, augmenter la sensibilité.

## Affichages
- OLED (I2C 0x3C/0x3D) : SDA/SCL selon board_config, pull-ups généralement sur le module. Inverser SDA/SCL si écran noir.
- TFT (ST7789 sur S3 / ILI9341 sur Classic) : contrôler toutes les lignes SPI et l'alim BL (backlight).
- Couleurs erratiques : raccourcir les câbles, vérifier la masse commune.

## Sortie Guirlande / TB6612FNG
- STBY doit être HIGH (GPIO8 sur S3, GPIO14 sur Classic).
- Direction : AIN1/AIN2 (GPIO6/4 sur S3, GPIO32/33 sur Classic). Intensité : PWMA (GPIO5 sur S3, GPIO12 sur Classic).
- VM doit être alimenté en 5–15V par une source externe ; ne pas alimenter la guirlande via l'USB seul.
- Si un sens ne fonctionne pas, inverser AO1/AO2 pour tester et inspecter les soudures.

## Statuts WiFi / Telegram absents
- Vérifier la connexion WiFi avant l'init Telegram (log "Connected to").
- Le chat doit correspondre à `TELEGRAM_CHAT_ID` ; les autres sont ignorés silencieusement.

## Problèmes de Build / Upload
- Compiler avec `pio run -e <env>` ; si upload difficile, maintenir BOOT (GPIO0) sur Classic au premier flash.
- Purger le cache `.pio` si changement majeur de framework.

Si le problème persiste, capturez les logs série depuis le boot et comparez le câblage aux tableaux `docs/PIN_MAPPING*.md`.
