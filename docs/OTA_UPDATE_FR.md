# Procédure de mise à jour OTA

Ce guide explique comment mettre à jour le firmware LED-Garland-Anim via WiFi en utilisant deux méthodes différentes.

---

## Prérequis
- L'ESP32 doit avoir été flashé au moins une fois par USB avec un firmware >= 1.3.0 (OTA activé)
- L'appareil doit être connecté au WiFi
- Pour la méthode 1 (Web) : N'importe quel navigateur web
- Pour la méthode 2 (ArduinoOTA) : PlatformIO (VS Code) ou Arduino IDE

---

## Méthode 1 : Mise à jour OTA via interface web (v1.11.1+) ⭐

**La méthode la plus simple et recommandée !**

### Étapes

1. **Compilez votre firmware** avec PlatformIO :
   ```bash
   pio run -e esp32devkitc
   ```

2. **Accédez à l'interface web** :
   - Ouvrez `http://[IP_ESP32]` dans votre navigateur
   - L'adresse IP s'affiche sur l'écran LCD ST7789

3. **Naviguez vers la page de mise à jour OTA** :
   - Cliquez sur le bouton **"⬆️ Mise à jour OTA"** du tableau de bord
   - Ou accédez directement à `http://[IP_ESP32]/update`

4. **Téléversez le firmware** :
   - Cliquez sur **"📁 Sélectionner fichier .bin"**
   - Naviguez vers `.pio/build/esp32devkitc/firmware.bin`
   - Cliquez sur **"🚀 Lancer la mise à jour"** (nécessite une double confirmation pour la sécurité)

5. **Suivez la progression** :
   - Barre de progression dans le navigateur
   - Affichage du pourcentage sur l'écran ST7789
   - Messages de statut (succès/échec)

6. **Redémarrage automatique** :
   - L'ESP32 redémarre automatiquement après une mise à jour réussie
   - Attendez la reconnexion WiFi (~10 secondes)

### Avantages
- ✅ Interface graphique intuitive
- ✅ Aucune commande PlatformIO nécessaire
- ✅ Fonctionne depuis n'importe quel appareil (PC, smartphone, tablette)
- ✅ Affichage de progression en temps réel
- ✅ Validation automatique du fichier (extension .bin requise)
- ✅ Confirmation par double-clic pour éviter les mises à jour accidentelles

### Notes importantes
- ⚠️ **Ne débranchez pas et ne réinitialisez pas** l'appareil pendant la mise à jour !
- ⚠️ Assurez une connexion WiFi stable
- ⚠️ Le fichier firmware doit avoir l'extension `.bin`
- ⚠️ La mise à jour prend 10-30 secondes selon la taille du fichier

---

## Méthode 2 : Mise à jour OTA via ArduinoOTA (PlatformIO)

**Méthode traditionnelle pour les développeurs qui préfèrent la ligne de commande :**

### Étapes

1. **Allumez l'ESP32 et connectez-le au WiFi**
   - L'adresse IP s'affiche sur l'écran LCD (ou vérifiez sur votre box)

2. **Ouvrez PlatformIO ou l'Arduino IDE**
   - Dans PlatformIO, sélectionnez l'environnement (ex : `esp32devkitc`)

3. **Sélectionnez le port OTA**
   - Dans PlatformIO : l'appareil apparaît comme `LED-Garland-Anim@<ip>` ou `LED-Garland-Anim.local` dans la liste des ports
   - Dans Arduino IDE : sélectionnez le port réseau correspondant

4. **Téléversez le firmware**
   - Cliquez sur le bouton d'upload comme d'habitude, ou utilisez :
     ```bash
     pio run -e esp32devkitc -t upload --upload-port [IP_ESP32]
     ```
   - Le téléversement se fait via WiFi
   - L'appareil redémarre automatiquement après la mise à jour

### Dépannage
- Si l'appareil n'apparaît pas dans la liste des ports :
  - Vérifiez la connexion WiFi
  - Assurez-vous que l'ordinateur est sur le même réseau
  - Essayez d'utiliser l'adresse IP au lieu de `.local`
- OTA n'est disponible que si le WiFi est connecté
- Le premier flash doit toujours se faire par USB

---

## Comparaison

| Fonctionnalité | OTA Web | ArduinoOTA |
|----------------|---------|------------|
| **Facilité d'utilisation** | ⭐⭐⭐⭐⭐ Très facile | ⭐⭐⭐ Modérée |
| **Outils requis** | Navigateur web seulement | PlatformIO/Arduino IDE |
| **Progression visuelle** | ✅ Oui (navigateur + LCD) | ❌ Non |
| **Depuis n'importe quel appareil** | ✅ Oui | ❌ Non (machine de dev uniquement) |
| **Confirmation de sécurité** | ✅ Double-clic | ❌ Non |
| **Idéal pour** | Utilisateurs finaux, mises à jour rapides | Développeurs, builds automatisés |

---

## Note de sécurité

OTA est activé par défaut et ne nécessite pas de mot de passe. Pour les environnements de production, considérez :
- Définir un mot de passe avec `ArduinoOTA.setPassword()` dans le code
- Restreindre l'accès à l'interface web
- Utiliser un réseau WiFi séparé pour les appareils IoT

---

## Historique des versions

- **v1.11.1** : Ajout de la confirmation par double-clic pour les mises à jour OTA
- **v1.11.1** : Ajout de l'interface de mise à jour OTA via web
- **v1.11.1** : Ajout du support ArduinoOTA

---

Pour plus de détails sur ArduinoOTA, voir la [documentation officielle ArduinoOTA](https://github.com/esp8266/Arduino/blob/master/doc/ota_updates/ota_updates.md).

**Version du document : v1.11.1 (2025-12-31)**
