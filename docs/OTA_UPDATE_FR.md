# Procédure de mise à jour OTA (ArduinoOTA)

Ce guide explique comment mettre à jour le firmware LED-Garland-Anim via le WiFi grâce à ArduinoOTA.

---

## Prérequis
- L’ESP32 doit avoir été flashé au moins une fois par USB avec un firmware >= 1.3.0 (OTA activé)
- L’appareil doit être connecté au même réseau WiFi que votre ordinateur
- PlatformIO (VS Code) ou Arduino IDE installé

---

## Étapes de la mise à jour OTA

1. **Allumez l’ESP32 et connectez-le au WiFi**
   - L’adresse IP s’affiche sur l’écran LCD (ou vérifiez sur votre box)

2. **Ouvrez PlatformIO ou l’Arduino IDE**
   - Dans PlatformIO, sélectionnez l’environnement (ex : `esp32devkitc`)

3. **Sélectionnez le port OTA**
   - Dans PlatformIO : l’appareil apparaît comme `LED-Garland-Anim@<ip>` ou `LED-Garland-Anim.local` dans la liste des ports
   - Dans Arduino IDE : sélectionnez le port réseau correspondant

4. **Téléversez le firmware**
   - Cliquez sur le bouton d’upload comme d’habitude
   - Le téléversement se fait via WiFi
   - L’appareil redémarre automatiquement après la mise à jour

---

## Dépannage
- Si l’appareil n’apparaît pas dans la liste des ports :
  - Vérifiez la connexion WiFi
  - Assurez-vous que l’ordinateur est sur le même réseau
  - Essayez d’utiliser l’adresse IP au lieu de `.local`
- OTA n’est disponible que si le WiFi est connecté
- Le premier flash doit toujours se faire par USB

---

## Sécurité
OTA est activé par défaut et ne nécessite pas de mot de passe. Pour la production, ajoutez un mot de passe avec `ArduinoOTA.setPassword()` dans le code.

---

Pour plus de détails, voir la [documentation officielle ArduinoOTA](https://github.com/esp8266/Arduino/blob/master/doc/ota_updates/ota_updates.md).
