# Réglage recommandé pour ce projet

Pour la guirlande LED animée (LED-Garland-Anim), le réglage optimal du capteur PIR est :

- **Sensibilité** : moyenne à élevée (potentiomètre « Sx » tourné aux 2/3 de la course, dans le sens horaire). Permet de détecter efficacement une présence humaine à 2–4 mètres.
- **Temporisation** : courte à moyenne (potentiomètre « Tx » réglé entre 2 et 5 secondes). La guirlande s’éteint rapidement après le départ, tout en restant réactive.
- **Cavalier (mode de déclenchement)** : position « H » (répétition activée, parfois notée « Repeat/Trigger »). L’animation reste active tant qu’un mouvement est détecté.

**Résumé** :
- Sensibilité : 2/3 (moyenne/haute)
- Temporisation : 2 à 5 s
- Cavalier : mode « H » (répétition)

Ces réglages assurent une détection fiable et une expérience utilisateur optimale pour l’animation de la guirlande LED.

# Réglage et branchement du capteur PIR (HC-SR501)

## Vue d'ensemble
Le capteur PIR (HC-SR501) permet de détecter les mouvements pour déclencher la guirlande LED. Une installation et un réglage précis sont essentiels pour un fonctionnement fiable.

## Branchement
- **VCC** : À connecter au 5V (broche 5V de l’ESP32)
- **GND** : À connecter à la masse
- **OUT** : À connecter au GPIO 35 (entrée uniquement sur ESP32 IdeaSpark)

## Réglages physiques
### 1. Sensibilité
- **Potentiomètre marqué "Sx" ou "Sens"**
- Tourner dans le sens horaire pour augmenter la portée (jusqu’à ~6m)
- Tourner dans le sens antihoraire pour réduire
- Adapter selon la taille de la pièce et la distance souhaitée

### 2. Temporisation (Hold Time)
- **Potentiomètre marqué "Tx" ou "Time"**
- Définit la durée pendant laquelle la sortie reste à HIGH après détection (de quelques secondes à plusieurs minutes)
- Pour ce projet, la durée logicielle est gérée par le firmware, mais le réglage physique peut influencer la réactivité

### 3. Cavalier (Mode de déclenchement)
- **H (répétitif)** : La sortie reste à HIGH tant qu’un mouvement est détecté
- **L (non-répétitif)** : La sortie passe à HIGH une fois, puis attend la fin de la temporisation avant de se réarmer
- Pour une détection continue, placer le cavalier sur "H"

## Conseils d’installation
- Éviter la lumière directe, les radiateurs ou les bouches d’aération
- Placer à hauteur d’homme pour une détection optimale
- Tester la sensibilité et la temporisation selon l’environnement pour éviter les déclenchements intempestifs

## Dépannage
- Déclenchement permanent : réduire la sensibilité, éloigner des sources de chaleur
- Jamais déclenché : augmenter la sensibilité, vérifier le câblage
- Sortie instable : vérifier l’alimentation et la masse commune

---
**Version du document : v1.11.1 (2025-12-31)**