# Depannage - LED-Garland-Anim v5.6.5

*Ce document est valide a partir de la version 5.6.5.*

## Cartes Supportees

Ce projet supporte **deux cartes** :

| Carte | Environnement | Description |
|-------|---------------|-------------|
| **ESP32-S3 Super Mini** | `esp32s3_supermini` | Carte compacte, **choix par defaut** |
| **ESP32 Wroom DevKit V1** | `esp32wroom` | Carte de developpement classique |

---

## Check-list Rapide

Avant de depanner, verifiez :

1. **Bon environnement** : Flasher le bon environnement PlatformIO
   - ESP32-S3 Super Mini : `esp32s3_supermini`
   - ESP32 Wroom : `esp32wroom`
2. **Identifiants WiFi** : Verifier `include/secrets.h` (reseau 2.4 GHz uniquement)
3. **Cablage des pins** : Respecter les pins de votre carte (voir tableaux ci-dessous)
4. **Masse commune** : ESP32, TB6612FNG et alimentation externe doivent partager GND
5. **Moniteur serie** : Regler le debit a **115200** pour lire les logs

---

## Reference des Pins par Carte

### ESP32-S3 Super Mini

| Fonction | GPIO |
|----------|------|
| I2C SDA | GPIO 4 |
| I2C SCL | GPIO 5 |
| TB6612 PWMA | GPIO 10 |
| TB6612 AIN1 | GPIO 11 |
| TB6612 AIN2 | GPIO 12 |
| TB6612 STBY | GPIO 13 |
| DATA Matrice | GPIO 7 |
| Capteur Mouvement | GPIO 2 |
| Bouton Utilisateur | GPIO 8 |
| Bouton BOOT | GPIO 0 |

### ESP32 Wroom

| Fonction | GPIO |
|----------|------|
| I2C SDA | GPIO 21 |
| I2C SCL | GPIO 22 |
| TB6612 PWMA | GPIO 12 |
| TB6612 AIN1 | GPIO 25 |
| TB6612 AIN2 | GPIO 33 |
| TB6612 STBY | GPIO 14 |
| DATA Matrice | GPIO 27 |
| Capteur Mouvement | GPIO 35 |
| Bouton Utilisateur | GPIO 16 |
| Bouton BOOT | GPIO 0 |

---

## Problemes WiFi / Reseau

### Le WiFi ne se Connecte Pas

**Symptomes :**
- Bloque sur "Connecting..."
- La LED reste allumee sans clignoter

**Solutions :**
1. **Verifier reseau 2.4 GHz** - L'ESP32 ne supporte PAS le 5 GHz
2. **Verifier identifiants** dans `include/secrets.h` (SSID et mot de passe exacts)
3. **Verifier routeur** - Certains routeurs bloquent les nouveaux appareils ou filtrent les MAC
4. **Rapprocher du routeur** - Signal faible = echec de connexion
5. **Redemarrer** l'ESP32 et le routeur

### Pas d'Adresse IP Affichee

**Solutions :**
1. Verifier la liste des clients DHCP du routeur
2. Redemarrer l'ESP32 et le routeur
3. Verifier l'orthographe des identifiants WiFi

### Deconnexions Frequentes

**Solutions :**
1. Rapprocher l'ESP32 du point d'acces
2. Eviter les hubs USB a faible puissance
3. Reduire le blindage metallique autour de la carte
4. Verifier les interferences d'autres appareils 2.4 GHz

---

## Problemes Interface Web

### L'Interface Web ne Charge Pas

**Solutions :**
1. **Pinguer l'IP** affichee sur l'OLED ou le moniteur serie
   ```
   ping 192.168.x.x
   ```
2. **Vider le cache** du navigateur ou essayer en navigation privee
3. **Utiliser HTTP** pas HTTPS : `http://192.168.x.x`
4. **Verifier meme reseau** - Votre appareil doit etre sur le meme WiFi
5. **Essayer mDNS** : `http://garland.local`

### Certaines Pages ne Fonctionnent Pas

**Solution :** Redemarrer l'ESP32 pour reinitialiser le serveur web interne

---

## Problemes de Boutons

### Les Boutons ne Repondent Pas

**GPIO des boutons par carte :**
- ESP32-S3 Super Mini : Bouton Utilisateur = **GPIO 8**
- ESP32 Wroom : Bouton Utilisateur = **GPIO 16**
- Les deux cartes : Bouton BOOT = **GPIO 0**

**Fonctions des boutons :**
- Bouton Utilisateur : 1 clic = animation guirlande suivante, 2 clics = animation matrice suivante, appui long = changer de mode
- Bouton BOOT : Appui long = redemarrage

**Solutions :**
1. Verifier que le cablage va vers GND a l'appui (boutons actifs bas)
2. Verifier que les pull-ups internes sont actives (par defaut dans le firmware)
3. Tester avec un multimetre la continuite
4. Verifier la mise a la terre correcte

---

## Problemes de Capteur de Mouvement

### Capteur Toujours Declenche (Faux Positifs)

**GPIO du capteur de mouvement par carte :**
- ESP32-S3 Super Mini : **GPIO 2**
- ESP32 Wroom : **GPIO 35**

**Pour PIR (HC-SR501) :**
1. Eloigner des sources de chaleur (radiateurs, soleil)
2. Reduire la sensibilite (tourner potentiometre sens antihoraire)
3. Verifier que le cavalier est sur "H" (mode repetition)

**Pour Radar RCWL-0516 :**
1. Eloigner des objets metalliques
2. Eloigner des alimentations et appareils a decoupage
3. Ajouter un blindage si les interferences persistent

### Capteur ne Declenche Jamais

**Pour PIR :**
1. Augmenter la sensibilite (tourner potentiometre sens horaire)
2. Verifier alimentation 5V et connexions GND
3. Attendre 30-60 secondes de chauffe

**Pour RCWL-0516 :**
1. Verifier le cablage (VCC, GND, OUT)
2. Verifier que le pin OUT est connecte au bon GPIO
3. Tester avec un multimetre le changement de tension au mouvement

---

## Problemes d'Affichage (OLED)

### L'Ecran OLED Reste Noir

**Pins I2C par carte :**
- ESP32-S3 Super Mini : SDA = **GPIO 4**, SCL = **GPIO 5**
- ESP32 Wroom : SDA = **GPIO 21**, SCL = **GPIO 22**

**Solutions :**
1. Verifier le cablage SDA/SCL correspond a votre carte
2. Verifier l'adresse I2C : generalement **0x3C** ou **0x3D**
3. Verifier l'alimentation 3.3V
4. Verifier la connexion GND commune
5. Lancer le scan I2C dans les logs serie au demarrage pour detecter les peripheriques

### L'Affichage Montre des Caracteres Aleatoires

1. Verifier le cablage I2C (inverser SDA/SCL si inverses)
2. Verifier que l'ecran est compatible SSD1306
3. Verifier la connexion de masse

---

## Problemes de Guirlande (TB6612FNG)

### La Guirlande ne S'Allume Pas

**Pins TB6612 par carte :**

| Pin | ESP32-S3 Super Mini | ESP32 Wroom |
|-----|---------------------|-------------|
| PWMA | GPIO 10 | GPIO 12 |
| AIN1 | GPIO 11 | GPIO 25 |
| AIN2 | GPIO 12 | GPIO 33 |
| STBY | GPIO 13 | GPIO 14 |

**Solutions :**
1. **Verifier pin STBY** - Doit etre HIGH pour que le driver fonctionne
2. **Verifier alimentation VM** - 5-15V externe requis (PAS par USB !)
3. **Verifier VCC** - 3.3V depuis l'ESP32
4. **Verifier GND** - Masse commune avec ESP32 et alimentation
5. **Tester la guirlande separement** - Connecter a une pile 9V pour verifier
6. **Inverser A01/A02** - Essayer d'inverser la polarite

### La Guirlande ne S'Allume que dans Une Direction

1. Verifier le cablage AIN1 et AIN2
2. Verifier que les deux GPIO sont correctement connectes
3. Essayer une autre animation (ex : "Blink Alternate")

---

## Problemes de Matrice (NeoPixel 8x8)

### La Matrice ne S'Allume Pas

**Pin DATA de la matrice par carte :**
- ESP32-S3 Super Mini : **GPIO 7**
- ESP32 Wroom : **GPIO 27**

**Solutions :**
1. Verifier le cablage du pin DATA
2. Verifier l'alimentation 5V (externe, pas USB)
3. Verifier la connexion GND (commune avec ESP32)
4. Essayer de baisser la luminosite d'abord (forte luminosite = plus de courant)
5. Ajouter une resistance 470 ohm sur la ligne DATA (recommande)
6. Ajouter un condensateur 1000uF pres de l'entree d'alimentation de la matrice

### La Matrice Affiche de Mauvaises Couleurs

1. Verifier le type de puce WS2812B (pas WS2811)
2. Verifier la connexion du pin DATA
3. Verifier la mise a la terre correcte

---

## Problemes de Configuration

### Les Reglages ne Sont Pas Sauvegardes Apres Redemarrage

**Symptomes :**
- Mode, animation, intervalles reviennent aux valeurs par defaut apres coupure de courant

**Causes :**
- Partition NVS corrompue ou pleine
- Flash ESP32 defectueuse
- Bug firmware

**Solutions :**
1. Effacer la flash completement et re-telecharger le firmware :
   ```bash
   pio run -e esp32s3_supermini -t erase
   pio run -e esp32s3_supermini -t upload
   ```
2. Verifier les messages d'erreur NVS dans la console serie
3. Si le probleme persiste, ouvrir un ticket avec les logs

---

## Problemes de Televersement

### Echec de Televersement - Port Non Trouve

**Solutions :**
1. Installer le pilote USB pour votre carte :
   - ESP32-S3 Super Mini : Generalement pas de pilote necessaire (USB CDC)
   - ESP32 Wroom : Installer pilote CP210x ou CH340
2. Essayer un autre cable USB (certains sont charge seulement)
3. Essayer un autre port USB

### Echec de Televersement - Erreur de Connexion

**Solutions :**
1. Maintenir le bouton BOOT en cliquant sur Upload
2. Relacher BOOT quand le televersement commence
3. Essayer une vitesse de televersement plus basse dans platformio.ini

### Erreur de Permission (Linux)

```bash
sudo usermod -a -G dialout $USER
```
Puis deconnexion et reconnexion.

---

## Toujours des Problemes ?

1. **Verifier la sortie serie** - La plupart des erreurs y sont enregistrees
2. **Verifier le cablage** - Utiliser les tableaux de pins ci-dessus pour votre carte specifique
3. **Commencer simple** - Tester un composant a la fois
4. **Verifier l'alimentation** - Une alimentation inadequate cause beaucoup de problemes
5. **Ouvrir un ticket** - Inclure les logs et details materiels

---

**Version du document : v5.6.5 (2026-02-02)**
