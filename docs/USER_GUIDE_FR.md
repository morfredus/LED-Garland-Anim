
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
# Guide Utilisateur - LED-Garland-Anim v0.8.0

Guide utilisateur complet pour le contrôleur d'animation de guirlande LED LED-Garland-Anim.

---

## Table des Matières

1. [Premier démarrage](#premier-démarrage)
2. [Contrôles physiques](#contrôles-physiques)
3. [Interface web](#interface-web)
4. [Affichage OLED](#affichage-oled)
5. [Modes de fonctionnement](#modes-de-fonctionnement)
6. [Animations](#animations)
7. [Configuration horaire](#configuration-horaire)
8. [Utilisation quotidienne](#utilisation-quotidienne)
9. [Dépannage](#dépannage)

---

## Premier Démarrage

### À Quoi S'attendre
1. **Écran OLED** affiche "Connexion WiFi..."
2. **LED NeoPixel** clignote en bleu pendant la connexion WiFi
3. Après connexion, **adresse IP** affichée pendant 3 secondes
4. **Guirlande** démarre avec animation Fade Alterné en mode Permanent
5. **LED NeoPixel** devient verte quand prête

### Notez Votre Adresse IP
Notez l'adresse IP affichée sur l'écran OLED ou consultez la liste DHCP de votre routeur. Vous en aurez besoin pour accéder à l'interface web.

Exemple : `192.168.1.100`

---

## Contrôles Physiques

### Emplacements des Boutons

#### ESP32-S3
- **BUTTON_BOOT** : Intégré sur la carte (GPIO 0)
- **BUTTON_1** : GPIO 16 (bouton externe)
- **BUTTON_2** : GPIO 17 (bouton externe)

#### ESP32 Classic
- **BUTTON_BOOT** : Intégré sur la carte (GPIO 0)
- **BUTTON_1** : GPIO 4 (bouton externe)
- **BUTTON_2** : GPIO 16 (bouton externe)

### Fonctions des Boutons

#### Bouton 1 - Contrôle Animation
- **Appui court** : Passer à l'animation suivante
- **Séquence** : Fade → Blink → Wave → ... → Mode Auto → (recommencer)
- **Feedback visuel** : NeoPixel clignote en violet

#### Bouton 2 - Contrôle Mode
- **Appui court** : Passer au mode de fonctionnement suivant
- **Séquence** : Permanent → Détection Mouvement → (recommencer)
- **Feedback visuel** : NeoPixel clignote en cyan

#### Bouton 0 (BOOT) - Redémarrage
- **Appui long (1 seconde)** : Redémarrer l'ESP32
- **Feedback visuel** : NeoPixel devient rouge
- **Cas d'usage** : Récupération d'erreurs ou application de changements de configuration

---

## Interface Web

### Durées configurables et persistance
- Intervalle du mode AUTO (ms): ajustable depuis la carte principale, enregistré en NVS et restauré automatiquement après redémarrage.
- Durée d’extinction après mouvement (ms): ajustable, enregistrée en NVS et restaurée au démarrage.
- Endpoints API: `GET /auto_interval?ms=<millis>` et `GET /motion_duration?ms=<millis>`.
- Statut (`GET /status`): expose `auto_interval_ms` et `motion_duration_ms`.

### Accès à l'Interface
1. Ouvrir un navigateur web sur téléphone/ordinateur
2. Entrer l'adresse IP de l'ESP32 : `http://[VOTRE_IP]`
3. Le tableau de bord se charge automatiquement

### Cartes du Tableau de Bord

#### 1. Carte LED Guirlande (Première Position)
**Sélecteur Animation**
- Menu déroulant avec 15 options
- Animation actuelle en surbrillance
- Cliquer "Appliquer" pour changer

**Sélecteur Mode**
- 2 modes de fonctionnement (Permanent, Détection Mouvement)
- Mode actuel en surbrillance
- Cliquer "Appliquer" pour changer

**Configuration Horaire**
- Supprimée depuis v0.5.1 (modes simplifiés à 2). Pas d'UI horaire dans la version actuelle.

**État Capteurs**
- Mouvement détecté : Oui/Non
- Niveau luminosité : 0-4095
- Nuit détectée : Oui/Non

#### 2. Carte Matériel
- Nom de la carte (ESP32-S3 / ESP32 Classic)
- ID Chip (identifiant unique)
- Version SDK
- Fréquence CPU (MHz)

#### 3. Carte Mémoire Flash
- Taille totale (MB)
- Vitesse (MHz)
- Mode (QIO/DIO)

#### 4. Carte RAM (Heap)
- Taille totale (KB)
- Mémoire libre (KB)
- Pourcentage d'utilisation avec barre de progression

#### 5. Carte PSRAM (si disponible)
- Taille totale (MB)
- Mémoire libre (KB)
- Pourcentage d'utilisation avec barre de progression

#### 6. Carte Réseau WiFi
- SSID connecté
- Adresse IP
- Adresse MAC
- Force du signal (dBm et %)

#### 7. Carte Système
- Uptime (heures, minutes, secondes)
- Température CPU (°C)

#### 8. Carte Détails Réseau
- Masque sous-réseau
- IP passerelle
- IP serveur DNS

### Boutons d'Action
- **🔄 Actualiser** : Recharger la page avec données mises à jour
- **🔴 Redémarrer** : Redémarrer l'ESP32 (demande confirmation)

---

## Affichage OLED

### Disposition Écran

#### Écran 128x64 (Grand)
```
┌────────────────────────────┐
│ Animation: Fade            │  Ligne 1: Animation actuelle
│ Mode: Permanent            │  Ligne 2: Mode actuel
│ IP: 192.168.1.100          │  Ligne 3: Adresse IP
│ [████▒▒▒▒░░░░░░░░░]       │  Ligne 4: Barre animée
└────────────────────────────┘
```

#### Écran 128x32 (Petit)
```
┌────────────────────────────┐
│ Fade / Permanent           │  Ligne 1: Animation + Mode
│ 192.168.1.100              │  Ligne 2: Adresse IP
│ [████▒▒▒▒░░░░░░░░░]       │  Ligne 3: Barre animée
└────────────────────────────┘
```

### Motifs Barre d'Animation

Chaque animation a une visualisation unique :

- **Éteint (Off)** : Barre vide
- **Fade Alterné** : Barre glissante avec dégradé
- **Clignotement Alterné** : Blocs alternés gauche/droite
- **Pulse** : Barre centrale qui grandit/rétrécit
- **Breathing** : Expansion/contraction
- **Strobe** : Flashs rapides alternés
- **Battement Cœur** : Double pulsation caractéristique
- **Vague** : Onde sinusoïdale fluide
- **Scintillement** : Pixels aléatoires clignotants
- **Météore** : Traînée mobile avec estompage
- **Auto** : Tiret rotatif (indique mode cyclique avec démarrage instantané)

**Quand Aucune Animation n'est Active** (v0.4.0+) :
- L'écran affiche 3 points fixes en bas de l'écran
- Indique que le système fonctionne mais animation est arrêtée
- Se met à jour quand l'animation redémarre
- Réduit le scintillement inutile de l'écran

**Note** : Pendant le mode nuit, l'OLED affiche points minimalistes au centre et le rétroéclairage est éteint.

---

## Modes de Fonctionnement

### 1. Mode Permanent
**Comportement** : Guirlande toujours allumée avec l'animation sélectionnée

**Cas d'usage** :
- Décoration continue
- Test des animations
- Événements et fêtes

**Activation** :
- Bouton 2 jusqu'à affichage "Permanent"
- Interface web : Sélectionner mode "Permanent"

### 2. Mode Détection Mouvement
**Comportement** : S'active pendant 30 secondes après détection de mouvement (PIR)

**Prérequis** : Capteur PIR connecté

**Cas d'usage** :
- Décoration d'entrée
- Éclairage de couloir
- Affichages interactifs

**Durée déclenchement** : 30 secondes (configurable dans le code via `MOTION_TRIGGER_DURATION`)

**Notes** :
- Uniquement 2 modes dans la v0.8.0 (Permanent, Détection Mouvement). Les modes Horaires et Coupure Nuit ont été retirés.
- Ajouter du debounce si nécessaire avec des modules PIR bruyants.

**Quand le Mode Nuit s'Active** :
1. Rétroéclairage OLED s'éteint
2. Animation s'arrête (LEDs guirlande répondent encore au mouvement si configuré)
3. Clignotement LED bleue/NeoPixel s'arrête
4. L'écran affiche points minimalistes pour indiquer que le système fonctionne

**Quand la Lumière Revient** :
1. Rétroéclairage OLED s'allume automatiquement
2. Affichage normal reprend
3. Clignotement LED bleue/NeoPixel reprend
4. Animation continue (si mode actif)

---

## Animations

### Description des Animations

#### 1. Fade Alterné
Fondu enchaîné fluide entre LEDs Sens A et B. Crée un effet de pulsation douce.

**Durée** : ~3 secondes par cycle  
**Effet** : Apaisant, subtil

#### 2. Clignotement
Alternance rapide entre les deux sens de LEDs.

**Durée** : 500ms par sens  
**Effet** : Énergique, accrocheur

#### 3. Onde Douce
Simule une vague traversant la guirlande avec intensité sinusoïdale.

**Durée** : ~2 secondes par vague  
**Effet** : Fluide, dynamique

#### 4. Stroboscope
Flashs alternés rapides entre les sens.

**Durée** : 100ms par flash  
**Effet** : Intense, ambiance fête

#### 5. Pulsation
Les deux sens pulsent ensemble avec intensité synchronisée.

**Durée** : ~2 secondes par pulsation  
**Effet** : Comme un battement de cœur, rythmique

#### 6. Poursuite
Crée une illusion de LEDs qui se poursuivent.

**Durée** : Pas de 50ms  
**Effet** : Course, ludique

#### 7. Battement de Cœur
Motif double pulsation mimant un battement de cœur.

**Durée** : Motif boum-BOUM avec pause  
**Effet** : Organique, vivant

#### 8. Scintillement
Changements d'intensité aléatoires créent un effet de clignotement.

**Durée** : Aléatoire continu  
**Effet** : Étoilé, magique

#### 9. Arc-en-ciel
Simule des couleurs arc-en-ciel via alternance et modulation rapides.

**Durée** : ~4 secondes par cycle  
**Effet** : Coloré, festif

#### 10. Respiration
Montée et descente lentes et fluides de l'intensité.

**Durée** : ~4 secondes par respiration  
**Effet** : Méditatif, relaxant

#### 11. Feu
Vacillement aléatoire imitant une bougie ou des flammes.

**Durée** : Aléatoire continu  
**Effet** : Chaleureux, cosy

#### 12. Clignotement Doux
Fondu entrant et sortant sinusoïdal doux.

**Durée** : ~1.5 secondes par clignotement  
**Effet** : Doux, romantique

#### 13. Météore
Crée un effet de traînée lumineuse comme une pluie de météores.

**Durée** : Pas de 50ms avec estompage  
**Effet** : Dynamique, céleste

#### 14. Mode Auto
Parcourt automatiquement les 13 animations.

**Durée** : 30 secondes par animation  
**Effet** : Variété, mode vitrine

---

## Configuration Horaire

### Configuration Interface Web (v0.2.0+)

1. **Accéder à l'Interface Web**
   - Naviguer vers `http://[IP_ESP32]`
   - Défiler jusqu'à la carte "LED Guirlande"

2. **Mode Horaire**
   - Supprimé depuis v0.5.1 (modes simplifiés à 2). Aucun réglage horaire disponible.

---

## Utilisation Quotidienne

### Routine Matinale
1. Vérifier état actuel sur OLED
2. Utiliser Bouton 1 pour changer animation si désiré
3. Laisser en mode Permanent ou Détection Mouvement selon besoin

### Routine Soirée
1. Choisir mode Permanent (allumé en continu) ou Détection Mouvement
2. Interface web pour vérifier fonctionnement
3. Ajuster animation via boutons, web ou Telegram

### En Quittant la Maison
1. Régler en mode Détection Mouvement pour réduire l'usage (pas de mouvement = éteint)
2. Ou laisser en mode Permanent si souhaité
3. Vérifier interface web ou Telegram si nécessaire

### Actions Rapides Dépannage
- **Guirlande ne fonctionne pas** : Appuyer Bouton 1 pour cycler animations
- **Mauvais mode** : Appuyer Bouton 2 pour changer mode
- **Système bloqué** : Appui long bouton BOOT pour redémarrer
- **IP perdue** : Vérifier écran OLED ou liste DHCP routeur

---

## Dépannage

Pour un guide de dépannage détaillé, consultez [TROUBLESHOOTING_FR.md](./TROUBLESHOOTING_FR.md).

### Problèmes Courants

#### La Guirlande Ne S'Allume Pas
**Solutions** :
1. Vérifier câblage TB6612FNG
2. S'assurer pin STBY à HIGH
3. Tester avec animation Clignotement
4. Vérifier alimentation

#### Écran OLED Vide
**Solutions** :
1. Vérifier adresse I2C (0x3C ou 0x3D)
2. Contrôler connexions SDA/SCL
3. Tester avec scanner I2C
4. Vérifier alimentation 3.3V

#### WiFi Ne Se Connecte Pas
**Solutions** :
1. Vérifier identifiants `secrets.h`
2. S'assurer WiFi 2.4 GHz (pas 5 GHz)
3. Se rapprocher du routeur
4. Consulter moniteur série

---

**Version** : 0.6.0  
**Dernière mise à jour** : 2025-12-10  
**Suivant** : [Guide de Dépannage](./TROUBLESHOOTING_FR.md)
