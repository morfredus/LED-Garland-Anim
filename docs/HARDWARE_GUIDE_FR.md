
# 🛒 Guide Matériel - LED-Garland-Anim v5.6.3

*Ce document est valide à partir de la version 5.6.3.*

## Plateformes supportées
- ESP32 Classic (IdeaSpark/DevKitC)
- ESP32 Wroom (DevKit V1)
- ESP32-S3 Mini (esp32s3_mini)
- ESP32-S3 Super Mini (esp32s3_supermini)

Liste d'achat complète et spécifications des composants pour construire le projet LED-Garland-Anim.

---

## 📋 Liste Complète des Composants

### Composants Essentiels

| Composant | Quantité | Coût Estimé | Notes |
|-----------|----------|-------------|-------|
| ESP32 IdeaSpark ou DevKitC | 1 | 8-15€ | Doit être ESP32 Classic (pas S2/S3) |
| Module TB6612FNG | 1 | 2-5€ | Pilote moteur double pont en H |
| Guirlande LED 2 fils | 1 | 5-10€ | LEDs anti-parallèles (~50 LEDs) |
| Matrice WS2812B 8x8 | 1 | 8-12€ | 64 LEDs RGB addressables |
| Capteur PIR HC-SR501 | 1 | 2-4€ | Détection de mouvement |
| Alimentation 5V | 1 | 8-15€ | 2A minimum, 3-5A recommandé |
| Breadboard 830 points | 1 | 3-5€ | Pour le prototypage |
| Câbles de connexion (M-M, M-F) | 1 set | 3-5€ | 40pcs minimum |
| Câble USB | 1 | 2-5€ | Selon le port ESP32 (micro/Type-C) |

**Coût Total Estimé** : 40-75€

### Composants Optionnels

| Composant | Quantité | Coût | Utilité |
|-----------|----------|------|---------|
| Radar RCWL-0516 | 1 | 2-3€ | Alternative au PIR (plus rapide, plus sensible) |
| Adaptateur jack DC | 1 | 2-3€ | Pour connexion alimentation plus propre |
| Condensateur 1000µF 16V | 1-2 | 1-2€ | Lissage de l'alimentation |
| Résistance 470Ω | 1 | 0.10€ | Protection ligne de données NeoPixels |

---

## 🔍 Spécifications Détaillées

### 1. Carte de Développement ESP32

**Modèles Recommandés :**

#### ESP32 IdeaSpark ⭐ (Recommandé)
- **Caractéristiques** : USB-C, 4MB Flash
- **Avantages** : Connecteur moderne
- **Où acheter** :
  - AliExpress : Rechercher "ESP32 IdeaSpark"
  - Prix : ~12-15€

#### ESP32 DevKitC (Alternative)
- **Caractéristiques** : Carte standard 38 broches, 4MB Flash, micro-USB
- **Avantages** : Largement disponible, bien documenté
- **Où acheter** :
  - Amazon : Rechercher "ESP32 DevKitC"
  - Mouser / Digi-Key
- **Prix** : ~8-12€

**Important** :
- Pour l'environnement **ESP32 Classic**, choisissez bien une carte ESP32 "Classic" (Xtensa dual-core).
- Les cartes **ESP32-S3 Mini/Super Mini** sont supportées via leurs environnements dédiés.
- Évitez les ESP32-S2 si vous ciblez l'environnement Classic.

### 2. Module Pilote Moteur TB6612FNG

**Spécifications :**
- Tension d'entrée (VM) : 4.5V - 15V
- Courant de sortie : 1.2A par canal (3.2A crête)
- Tension logique (VCC) : 2.7V - 5.5V
- Contrôle veille : Intégré
- Double pont en H : Contrôle de direction indépendant

**Où acheter :**
- Amazon FR : Rechercher "TB6612FNG breakout"
- AliExpress : ~2€ (tarif groupé)
- Gotronic (FR) : Module TB6612FNG

**Prix** : 2-5€

### 3. Guirlande LED 2 Fils

**Spécifications :**
- Type : Arrangement LED anti-parallèle
- Nombre de fils : 2 fils uniquement (pas les guirlandes animées 3 fils)
- Nombre de LEDs : ~50-100 LEDs
- Tension : Compatible 5-12V
- Couleur : Blanc chaud, blanc froid, ou multicolore

**Identification :**
- ✅ A seulement 2 fils
- ✅ Les LEDs s'allument en motif alterné quand la polarité est inversée
- ✅ Souvent vendues comme "mini guirlandes lumineuses LED"
- ❌ PAS les guirlandes animées pré-programmées (3+ fils)

**Où acheter :**
- Magasins de bricolage (section Noël/fêtes)
- Amazon : Rechercher "guirlande LED 2 fils 50 LEDs"
- IKEA : "SÄRDAL" ou guirlandes LED similaires
- Magasins discount (vérifier le nombre de fils !)

**Prix** : 5-10€


### 4bis. Affichage supporté : OLED SSD1306 128x64 (I2C)

- Universel, supporté sur toutes les plateformes (SDA=GPIO4, SCL=GPIO5 par défaut)
- Affichage monochrome, 128x64px
- Démarrage : nom du projet, version, progression WiFi
- Principal : nom du projet, version, SSID, IP, mDNS, mode, animations
- Zone d'animation : visualisation temps réel, messages système
- Sélection du mode d'affichage (Animé, Statique, Éteint) depuis l'interface web
- Persistance automatique (NVS, restauré au boot)
- Effet immédiat, sans reboot
- 11 visualisations animées (une par animation, mode animé)
- Mises à jour temps réel à 10 FPS (mode animé)

**Spécifications :**
- Type : WS2812B (puce de contrôle intégrée)
- Configuration : Grille 8x8 (64 LEDs)
- Tension : 5V
- Courant : ~60mA par LED en blanc complet (3.84A max pour matrice complète)
- Protocole de données : Série fil unique
- Taux de rafraîchissement : 400Hz - 800Hz

**Où acheter :**
- Amazon : Rechercher "WS2812B 8x8 matrice"
- BTF-LIGHTING (marque fiable sur Amazon)
- AliExpress : Rechercher "WS2812 8x8 panneau flexible"

**Prix** : 8-12€

### 5. Capteurs de Mouvement

#### Capteur PIR HC-SR501 (Option standard)

**Spécifications :**
- Portée de détection : 3-7 mètres
- Angle de détection : ~120°
- Tension de fonctionnement : 5V
- Sortie : 3.3V HIGH quand mouvement détecté
- Sensibilité ajustable (potentiomètre Sx)
- Temporisation ajustable (potentiomètre Tx)

**Où acheter :**
- Amazon : Rechercher "HC-SR501 PIR capteur"
- AliExpress

**Prix** : 2-4€

#### Radar Doppler RCWL-0516 (Option avancée)

**Spécifications :**
- Portée de détection : 5-9 mètres
- Angle de détection : ~120°
- Tension de fonctionnement : 4-28V (compatible 3.3V/5V)
- Sortie : 3.3V HIGH quand mouvement détecté
- Fréquence micro-ondes : 3.18 GHz

**Où acheter :**
- Amazon : Rechercher "RCWL-0516 radar capteur"
- AliExpress

**Prix** : 2-3€

### 6. Alimentation Électrique

**Spécifications :**
- Tension : 5V DC (régulée)
- Courant :
  - Minimum : 2A (fonctionnement de base)
  - Recommandé : 3A (marge de sécurité)
  - Idéal : 5A (capacité luminosité maximale)
- Connecteur : Jack barrel (5.5mm x 2.1mm) ou USB-C
- Certification : UL/CE recommandée

**Répartition du courant :**
- ESP32 : ~0.5A crête (WiFi actif)
- TB6612FNG : ~1A (guirlande luminosité max)
- Matrice WS2812B : ~3.8A (64 LEDs blanc complet)
- Capteur PIR : ~50mA
- Total maximum : ~5.35A

**Où acheter :**
- Amazon FR : Rechercher "alimentation 5V 5A DC"
- Mean Well (qualité industrielle)

**Prix** : 8-15€

**Notes de sécurité importantes :**
- ⚠️ NE PAS utiliser d'alimentations bon marché/non certifiées
- ⚠️ Assurer la polarité correcte (centre positif pour jacks barrel)
- ✅ Ajouter condensateur 1000µF près de la matrice pour stabilité

---

## 🌍 Fournisseurs Recommandés par Région

### France
- **Amazon.fr** : Expédition rapide Prime
- **Gotronic** : Composants électroniques, support FR
- **Kubii** : Distributeur Adafruit/SparkFun
- **AliExpress** : Prix bas, expédition 2-4 semaines

### Europe
- **Pimoroni** (UK) : Distributeur Adafruit
- **Berrybase** (Allemagne) : ESP32 et capteurs
- **Amazon** : Spécifique au pays (.de, .fr, .co.uk)

### Options Budget
- **AliExpress** : Prix les plus bas, expédition longue
- **Banggood** : Prix compétitifs
- **eBay** : Mix vendeurs locaux/internationaux

---

## 🛠️ Outils Requis

### Outils Essentiels
- Pince à dénuder (22-24 AWG)
- Pince coupante
- Ordinateur avec port USB (Windows/Mac/Linux)

### Outils Utiles
- Multimètre (test tension/continuité)
- Fer à souder (optionnel, connexions permanentes)
- Pistolet à colle chaude (soulagement contrainte câbles)

---

## ✅ Liste de Vérification

Avant de commencer, vérifier que vous avez :

### Obligatoire
- [ ] Carte ESP32 (IdeaSpark ou DevKitC)
- [ ] Module pilote TB6612FNG
- [ ] Guirlande LED 2 fils
- [ ] Matrice WS2812B 8x8
- [ ] Capteur PIR HC-SR501 ou RCWL-0516
- [ ] Alimentation 5V (2A minimum)
- [ ] Breadboard
- [ ] Câbles de connexion (M-M et M-F)
- [ ] Câble USB (compatible avec votre ESP32)

### Recommandé
- [ ] Condensateur 1000µF 16V
- [ ] Résistance 470Ω
- [ ] Adaptateur jack barrel
- [ ] Multimètre

---

## 🆘 Aide à l'Achat

### Questions Fréquentes

**Q : Puis-je utiliser une alimentation 3A au lieu de 5A ?**  
R : Oui, mais limitez la luminosité de la matrice à ~60% pour éviter la surcharge.

**Q : ESP32-S2/S3 fonctionnera-t-il ?**  
R : Non, ce firmware est spécifique à l'ESP32 "Classic" (dual-core original).

**Q : Ma guirlande a 3 fils, fonctionnera-t-elle ?**  
R : Non, les guirlandes 3 fils sont pré-programmées. Vous avez besoin de guirlandes 2 fils anti-parallèles simples.

---

## 📚 Guides Associés

- **Démarrage Rapide** : Configuration initiale → [QUICKSTART_FR.md](QUICKSTART_FR.md)
- **Guide de Câblage** : Schémas de connexion → [PIN_MAPPING_FR.md](PIN_MAPPING_FR.md)
- **Guide de Compilation** : Instructions → [BUILD_GUIDE_FR.md](BUILD_GUIDE_FR.md)
- **Guide Utilisateur** : Documentation complète → [USER_GUIDE_FR.md](USER_GUIDE_FR.md)

---

**Version du document : v5.1.5 (2026-01-07)**
