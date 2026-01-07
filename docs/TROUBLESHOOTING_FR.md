## Problème de sauvegarde/restauration de configuration

**Symptômes :**
- Les réglages (mode, animation, intervalles) sont perdus après redémarrage ou coupure d’alimentation.

**Causes possibles :**
- Partition NVS corrompue ou pleine
- Mémoire flash ESP32 défectueuse
- Bug firmware (voir logs pour erreurs NVS)

**Solutions :**
- Effacer la flash et reprogrammer le firmware
- Vérifier les messages d’erreur sur la console série
- Si le problème persiste, ouvrir un ticket avec les logs
# Dépannage - LED-Garland-Anim v5.1.4

Guide rapide pour diagnostiquer les problèmes sur ESP32 IdeaSpark.

## Check-list Express
- Flasher le bon environnement (`esp32devkitc`).
- Vérifier les identifiants WiFi dans `include/secrets.h`.
- Respecter les pins de `include/board_config.h` (voir PIN_MAPPING_FR.md).
- Masse commune entre ESP32, TB6612FNG et alimentation externe.
- Ouvrir le moniteur série en 115200 pour lire les logs.

## WiFi / Réseau
- Bloqué sur "Connecting" : réseau 2.4 GHz obligatoire, vérifier SSID/mot de passe et filtrage MAC.
- Pas d'IP affichée : vérifier la liste DHCP du routeur, redémarrer carte + box si besoin.
- Coupures fréquentes : rapprocher du point d'accès, éviter les hubs USB peu puissants, limiter les obstacles métalliques.

## Interface Web Injoignable
- Pinger l'IP affichée sur le LCD ; si échec, revoir WiFi/DHCP.
- Vider le cache ou utiliser un onglet privé ; utiliser `http://<ip>` (pas HTTPS).
- Si certaines pages répondent mal, redémarrer la carte pour relancer le serveur web interne.

## Boutons (Animation/Mode)
- BUTTON_1 GPIO16, BUTTON_2 GPIO17, BUTTON_BOOT sur GPIO0.
- Boutons actifs bas avec pull-up interne ; le câblage doit aller à GND à l'appui.
- Si rebonds, vérifier la longueur des fils et l'état des interrupteurs ; les logs série doivent afficher les pressions.

## Capteurs
- MOTION_SENSOR_PIN : GPIO35. Le système auto-détecte PIR (HC-SR501) ou RCWL-0516. Vérifiez l'alim 5V/GND. Pour PIR : ajustez sensibilité/temporisation. Pour RCWL : vérifiez les interférences ou faux positifs.
Si détection permanente, éloigner le capteur des sources de chaleur/soleil (PIR) ou d'interférences (RCWL) ; si jamais, augmenter la sensibilité (PIR) ou vérifier le câblage (RCWL).

## Affichage
- LCD ST7789 : contrôler toutes les lignes SPI et l'alim BLK (backlight).
- Couleurs erratiques : raccourcir les câbles, vérifier la masse commune.

## Sortie Guirlande / TB6612FNG
- TB6612_STBY doit être HIGH (GPIO14).
- Direction : TB6612_AIN1/TB6612_AIN2 (GPIO25/33). Intensité : TB6612_PWMA (GPIO12).
- VM doit être alimenté en 5–15V par une source externe ; ne pas alimenter la guirlande via l'USB seul.

---

**Version du document : v5.1.4 (2026-01-07)**
