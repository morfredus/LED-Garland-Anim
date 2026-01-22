
# 🚀 Guide Rapide - LED-Garland-Anim v5.2.1

*Ce document est valide à partir de la version 5.2.1.*

## Plateformes supportées
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32-C3 HW-675 (OLED)
- ESP32-S3 Mini (esp32s3_mini)

**Objectif** : Faire fonctionner votre guirlande LED en 5 minutes !

Ce guide s'adresse aux débutants sans expérience ESP32. Suivez ces étapes dans l'ordre.

---

## ⏱️ Prérequis (5 minutes)

### 1. Installer les logiciels

**Windows / macOS / Linux :**

1. **Installer VS Code** : https://code.visualstudio.com/
2. **Installer l'extension PlatformIO** :
   - Ouvrir VS Code
   - Cliquer sur l'icône Extensions (barre latérale gauche)
   - Rechercher "PlatformIO IDE"
   - Cliquer sur "Install"
   - Attendre la fin de l'installation (2-3 minutes)
   - Redémarrer VS Code si demandé

3. **Installer Git** (si pas déjà installé) :
   - Windows : https://git-scm.com/download/win
   - macOS : Ouvrir Terminal, taper `git --version` (installe automatiquement si besoin)
   - Linux : `sudo apt install git` (Ubuntu/Debian)

### 2. Liste du matériel requis

✅ Carte ESP32 IdeaSpark ou DevKitC  
✅ Câble USB (micro-USB ou USB-C selon la carte)  
✅ Module pilote moteur TB6612FNG  
✅ Guirlande LED 2 fils (LEDs anti-parallèles)  
✅ Matrice NeoPixel 8x8 WS2812B  
✅ Capteur PIR (HC-SR501) ou radar RCWL-0516  
✅ Alimentation externe 5V (2A minimum)  
✅ Breadboard et câbles de connexion  

**Vous n'avez pas tous les composants ?** Voir [HARDWARE_GUIDE_FR.md](HARDWARE_GUIDE_FR.md) pour la liste d'achat.

---

## 📥 Étape 1 : Télécharger le projet (2 minutes)

1. Ouvrir VS Code
2. Appuyer sur `Ctrl+Shift+P` (Windows/Linux) ou `Cmd+Shift+P` (macOS)
3. Taper "Git: Clone" et appuyer sur Entrée
4. Coller l'URL du dépôt : `https://github.com/[votre-nom]/LED-Garland-Anim`
5. Choisir un dossier (ex: `Documents/PlatformIO/`)
6. Cliquer sur "Open" quand demandé

**Alternative (ligne de commande) :**
```bash
cd ~/Documents/PlatformIO
git clone https://github.com/[votre-nom]/LED-Garland-Anim
cd LED-Garland-Anim
code .
```

---

## 🔌 Étape 2 : Câbler les composants (10 minutes)

### Schéma de connexion rapide

**TB6612FNG → ESP32 :**
```
PWMA  → GPIO 13
AIN1  → GPIO 26
AIN2  → GPIO 25
STBY  → GPIO 15
VCC   → 3.3V
GND   → GND
VM    → 5V externe (PAS l'USB !)
```

**Matrice NeoPixel → ESP32 :**
```
DIN   → GPIO 34
VCC   → 5V externe
GND   → GND (masse commune avec ESP32)
```

**Capteur PIR → ESP32 :**
```
VCC   → 5V
OUT   → GPIO 35
GND   → GND
```

**Guirlande LED → TB6612FNG :**
```
A01   → Fil guirlande 1
A02   → Fil guirlande 2
```

⚠️ **CRITIQUE** : 
- Connecter le GND de l'alimentation externe au GND de l'ESP32 (masse commune)
- NE PAS alimenter la guirlande ou la matrice par USB seul
- Le VM du TB6612FNG doit venir de l'alimentation externe, pas de l'ESP32

📖 **Besoin de détails ?** Voir [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md) avec schémas complets.

---

## ⚙️ Étape 3 : Configurer le WiFi (1 minute)

1. Dans VS Code, ouvrir `include/secrets.h`
2. Remplacer par vos identifiants WiFi :
   ```cpp
   #define WIFI_SSID "NomDeVotreReseau"
   #define WIFI_PASSWORD "VotreMotDePasse"
   ```
3. Sauvegarder le fichier (`Ctrl+S` / `Cmd+S`)

⚠️ **Important** : L'ESP32 ne supporte que les réseaux WiFi 2.4 GHz, pas 5 GHz !

---

## 📤 Étape 4 : Téléverser le firmware (3 minutes)

### Premier téléversement (USB obligatoire)

1. Connecter l'ESP32 à l'ordinateur par câble USB
2. Dans la barre inférieure de VS Code, cliquer sur **"✓ Build"** (icône coche)
   - Attendre la compilation (30-60 secondes)
   - Message "SUCCESS" doit apparaître
3. Cliquer sur **"→ Upload"** (flèche droite)
   - PlatformIO détecte automatiquement le port COM
   - Attendre le téléversement (20-30 secondes)
4. Cliquer sur **"🔌 Serial Monitor"** (icône prise)
   - Régler le débit à **115200**
   - Observer les messages de démarrage

**Dépannage téléversement :**
- "Port introuvable" : Installer le pilote USB CP210x ou CH340 pour votre carte
- "Échec connexion" : Maintenir le bouton BOOT pendant le téléversement
- Erreur permission (Linux) : `sudo usermod -a -G dialout $USER` puis déconnexion/reconnexion

### Vérifier le succès

Le moniteur série doit afficher :
```
[WiFi] Connected to NomDeVotreReseau
[WiFi] IP address: 192.168.x.x
[mDNS] Started as: garland.local
[Setup] Complete! Ready.
```

---

## 🌐 Étape 5 : Accéder à l'interface web (1 minute)

### Méthode 1 : Utiliser mDNS (le plus simple)

Ouvrir un navigateur et aller à :
```
http://garland.local
```

### Méthode 2 : Utiliser l'adresse IP

Utiliser l'adresse IP affichée sur le LCD ou dans le moniteur série :
```
http://192.168.x.x
```

**L'interface web ne charge pas ?**
- Vérifier que l'ESP32 est allumé et connecté au WiFi
- Vérifier l'adresse IP dans le moniteur série
- Essayer de pinguer : `ping garland.local` ou `ping 192.168.x.x`
- Vider le cache du navigateur ou essayer en navigation privée
- S'assurer d'être sur le même réseau WiFi

---

## 🎉 Étape 6 : Tester les animations (1 minute)

### Sur l'interface web

1. **Tester la guirlande** :
   - Aller à la section "🎄 Animations Guirlande"
   - Cliquer sur "Fade Alternate"
   - La guirlande doit s'animer !

2. **Tester la matrice** :
   - Aller à la section "🎨 Matrice 8x8"
   - Cliquer sur "Star"
   - La matrice doit afficher une étoile animée !

3. **Tester la détection de mouvement** :
   - Aller à la section "🎯 Mode de fonctionnement"
   - Sélectionner "Détection mouvement"
   - Passer la main devant le capteur PIR
   - La guirlande et la matrice doivent s'activer !

### Test des boutons physiques

- **BUTTON_1 (GPIO 16)** : Changer l'animation de la guirlande
- **BUTTON_2 (GPIO 17)** : Changer le mode de fonctionnement
- **Bouton BOOT** : Basculer l'animation de la matrice (bouton intégré)

---

## ✅ Liste de vérification du succès

Vous devriez maintenant avoir :
- ✅ Guirlande animée avec transitions fluides
- ✅ Matrice affichant des animations colorées
- ✅ Interface web accessible à `http://garland.local`
- ✅ Détection de mouvement déclenchant les animations
- ✅ Boutons physiques fonctionnels
- ✅ LCD affichant l'IP et le statut (si équipé)

---

## 🆘 Quelque chose ne fonctionne pas ?

### Problèmes courants

**WiFi ne se connecte pas :**
- Vérifier SSID/mot de passe dans `secrets.h`
- Vérifier réseau 2.4 GHz (pas 5 GHz)
- Vérifier que le routeur autorise les nouveaux appareils

**Guirlande ne s'allume pas :**
- Vérifier que la broche STBY du TB6612FNG est HIGH (GPIO 15)
- Vérifier alimentation externe connectée à VM
- Tester la polarité de la guirlande (inverser A01/A02)

**Matrice ne s'allume pas :**
- Vérifier connexion GPIO 34 (broche DATA)
- Vérifier alimentation 5V suffisante (2A minimum)
- Tester avec luminosité réduite d'abord

**Capteur ne détecte pas :**
- PIR : Ajuster le potentiomètre de sensibilité (sens horaire = plus sensible)
- RCWL : Éloigner des objets métalliques et alimentations
- Vérifier connexion GPIO 35

📖 **Dépannage détaillé** : Voir [TROUBLESHOOTING_FR.md](TROUBLESHOOTING_FR.md)

---

## 🎯 Prochaines étapes

Maintenant que tout fonctionne :

1. **Explorer toutes les animations** : 11 animations guirlande + 37 animations matrice disponibles !
2. **Personnaliser les réglages** : Ajuster intervalles, luminosité et modes dans l'interface web
3. **Apprendre les mises à jour OTA** : Mettre à jour le firmware sans fil (voir [OTA_UPDATE_FR.md](OTA_UPDATE_FR.md))
4. **Lire le guide utilisateur** : Documentation complète dans [USER_GUIDE_FR.md](USER_GUIDE_FR.md)
5. **Ajuster les capteurs** : Affiner les réglages PIR/RCWL (voir [PIR_SENSOR_SETUP_FR.md](PIR_SENSOR_SETUP_FR.md))

---

## 📚 Ressources supplémentaires

- **Guide matériel** : Liste de composants avec fournisseurs → [HARDWARE_GUIDE_FR.md](HARDWARE_GUIDE_FR.md)
- **Guide de compilation** : Instructions détaillées → [BUILD_GUIDE_FR.md](BUILD_GUIDE_FR.md)
- **Plan de câblage** : Schémas complets → [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md)
- **Architecture** : Structure du code et modules → [ARCHITECTURE_FR.md](ARCHITECTURE_FR.md)
- **Changelog** : Historique des versions → [CHANGELOG_FR.md](../CHANGELOG_FR.md)

---

**🎊 Félicitations !** Vous avez configuré LED-Garland-Anim avec succès !

**Version du document : v5.1.5 (2026-01-07)**
