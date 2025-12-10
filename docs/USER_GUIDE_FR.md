# Guide Utilisateur - LED-Garland-Anim v0.4.0

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
- **Bouton 0 (BOOT)** : Intégré sur la carte
- **Bouton 1** : GPIO 16 (bouton externe)
- **Bouton 2** : GPIO 17 (bouton externe)

#### ESP32 Classic
- **Bouton 0 (BOOT)** : Intégré sur la carte
- **Bouton 1** : GPIO 4 (bouton externe)
- **Bouton 2** : GPIO 15 (bouton externe)

### Fonctions des Boutons

#### Bouton 1 - Contrôle Animation
- **Appui court** : Passer à l'animation suivante
- **Séquence** : Fade → Blink → Wave → ... → Mode Auto → (recommencer)
- **Feedback visuel** : NeoPixel clignote en violet

#### Bouton 2 - Contrôle Mode
- **Appui court** : Passer au mode de fonctionnement suivant
- **Séquence** : Permanent → Horaires → Détection Mouvement → Coupure Nuit → (recommencer)
- **Feedback visuel** : NeoPixel clignote en cyan

#### Bouton 0 (BOOT) - Redémarrage
- **Appui long (1 seconde)** : Redémarrer l'ESP32
- **Feedback visuel** : NeoPixel devient rouge
- **Cas d'usage** : Récupération d'erreurs ou application de changements de configuration

---

## Interface Web

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
- 4 modes de fonctionnement
- Mode actuel en surbrillance
- Cliquer "Appliquer" pour changer

**Configuration Horaire** (v0.2.0+)
- Heure début : Entrées Heure et Minute
- Heure fin : Entrées Heure et Minute
- Cliquer "Enregistrer Horaire" pour appliquer
- Popup de confirmation apparaît

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

- **Fade** : Barre glissante avec dégradé
- **Blink** : Blocs alternés gauche/droite
- **Wave** : Progression d'onde fluide
- **Strobe** : Blocs clignotants rapides
- **Pulse** : Barre centrale qui grandit/rétrécit
- **Chase** : Point qui court
- **Heartbeat** : Pulsation double
- **Sparkle** : Pixels aléatoires
- **Rainbow** : Vague mobile
- **Breathing** : Expansion/contraction
- **Fire** : Barres de hauteur aléatoire vacillantes
- **Twinkle** : Pixels épars aléatoires
- **Meteor** : Traînée mobile avec estompage
- **Auto** : Tiret rotatif (indique mode cyclique)

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

### 2. Mode Horaires (v0.2.0+)
**Comportement** : Guirlande s'active uniquement pendant la fenêtre horaire configurée

**Configuration** :
1. Accéder à l'interface web
2. Défiler jusqu'à la section "Configuration Horaire"
3. Définir heure de début (heure et minute)
4. Définir heure de fin (heure et minute)
5. Cliquer "Enregistrer Horaire"

**Horaire par défaut** : 18:00 - 23:00

**Cas d'usage** :
- Décoration automatique en soirée (18h - 23h)
- Économie d'énergie
- Fonctionnement sans surveillance

**Important** : Nécessite une heure système précise. Envisager d'ajouter un module RTC pour résistance aux coupures de courant.

### 3. Mode Détection Mouvement
**Comportement** : S'active pendant 30 secondes après détection de mouvement

**Prérequis** : Capteur PIR connecté

**Cas d'usage** :
- Décoration d'entrée
- Éclairage de couloir
- Affichages interactifs

**Durée déclenchement** : 30 secondes (configurable dans le code)

**Capteur** : Module PIR HC-SR501
- Portée détection : ~7 mètres
- Angle détection : ~120°
- Sensibilité et délai ajustables

### 4. Mode Coupure Nuit
**Comportement** : S'éteint automatiquement quand la luminosité ambiante est faible (nuit)

**Prérequis** : Photorésistance LDR connectée

**Fonctionnalités** (v0.4.0+) :
- **Détection automatique** : Utilise le capteur de lumière pour détecter la nuit
- **Rétroéclairage OLED off** : L'écran économise de l'énergie en mode nuit
- **Indicateurs LED silencieux** : LED bleue et NeoPixel arrêtent de clignoter
- **Affichage minimaliste** : OLED affiche 3 points fixes au lieu de l'animation
- **Sans configuration manuelle** : Entièrement automatique selon le niveau de lumière
- **Seuil de nuit** : 500/4095 ADC (configurable)
  - Valeur plus basse = environnement plus sombre nécessaire
  - Typique : 300-600 selon éclairage ambiant

**Cas d'usage** :
- Décoration de jour uniquement
- Arrêt automatique la nuit
- Affichages réactifs à la lumière
- Mode économie d'énergie pendant les heures de sommeil

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

2. **Localiser Section Horaire**
   - Sous le sélecteur de mode
   - Titre "⏰ Configuration Horaire"

3. **Définir Heure Début**
   - Entrer heure début (0-23)
   - Entrer minute début (0-59)
   - Exemple : 18:00 pour 18h

4. **Définir Heure Fin**
   - Entrer heure fin (0-23)
   - Entrer minute fin (0-59)
   - Exemple : 23:00 pour 23h

5. **Enregistrer Configuration**
   - Cliquer bouton "💾 Enregistrer Horaire"
   - Popup de confirmation apparaît
   - Page se recharge avec nouvelles valeurs

### Horaires Courants

**Décoration Soirée** (Par défaut)
- Début : 18:00 (18h)
- Fin : 23:00 (23h)
- Usage : Ambiance soirée automatique

**Toute la Nuit**
- Début : 18:00 (18h)
- Fin : 06:00 (6h)
- Usage : Décoration nocturne prolongée

**Jour Uniquement**
- Début : 08:00 (8h)
- Fin : 18:00 (18h)
- Usage : Heures ouvrables, vitrines magasins

**Événement Court**
- Début : 19:00 (19h)
- Fin : 21:00 (21h)
- Usage : Dîners, événements spécifiques

### Vérification
Après enregistrement, vérifier :
- Valeurs horaire mises à jour dans champs
- Guirlande se comporte selon horaire
- Vérifier heure système si problèmes

---

## Utilisation Quotidienne

### Routine Matinale
1. Vérifier état actuel sur OLED
2. Aucune action nécessaire en modes Horaires/Mouvement
3. Utiliser Bouton 1 pour changer animation si désiré

### Routine Soirée
1. Mode Horaires s'active automatiquement
2. Interface web pour vérifier fonctionnement
3. Ajuster horaire si nécessaire

### En Quittant la Maison
1. Régler en mode Horaires pour contrôle automatique
2. Ou éteindre en mettant en Détection Mouvement (pas de mouvement = éteint)
3. Vérifier interface web à distance si même réseau

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

**Version** : 0.2.0  
**Dernière mise à jour** : 2025-12-09  
**Suivant** : [Guide de Dépannage](./TROUBLESHOOTING_FR.md)
