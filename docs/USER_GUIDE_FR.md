# Guide Utilisateur - LED-Garland-Anim v1.0.0

Guide utilisateur complet pour le contrôleur d'animation de guirlande LED (ESP32 IdeaSpark + ST7789).

---

## Table des Matières

1. [Premier démarrage](#premier-démarrage)
2. [Contrôles physiques](#contrôles-physiques)
3. [Interface web](#interface-web)
4. [Affichage LCD ST7789](#affichage-lcd-st7789)
5. [Modes de fonctionnement](#modes-de-fonctionnement)
6. [Animations](#animations)
7. [Utilisation quotidienne](#utilisation-quotidienne)
8. [Dépannage](#dépannage)

---

## Premier Démarrage

### À Quoi S'attendre
1. **LCD ST7789** affiche "Connexion WiFi..."
2. **LED_BUILTIN** clignote en bleu pendant la connexion WiFi
3. Après connexion, **adresse IP** affichée pendant 3 secondes
4. **Guirlande** démarre avec animation Fade Alterné en mode Permanent
5. **LED_BUILTIN** devient verte quand prête

### Notez Votre Adresse IP
Notez l'adresse IP affichée sur l'écran LCD ou consultez la liste DHCP de votre routeur. Vous en aurez besoin pour accéder à l'interface web.

Exemple : `192.168.1.100`

---

## Contrôles Physiques

### Emplacements des Boutons
- **BUTTON_BOOT** : GPIO 0 (sur la carte)
- **BUTTON_1** : GPIO 16 (changement animation)
- **BUTTON_2** : GPIO 17 (changement mode)

---

## Interface Web
- Accès via l'adresse IP affichée sur le LCD
- Tableau de bord : infos système, mémoire, WiFi
- Contrôle guirlande : sélection animation/mode
- Visualisation capteurs

---

## Affichage LCD ST7789
- Écran couleur 1.14" 135x240px
- Écran de démarrage moderne : nom projet, version, progression WiFi
- Interface principale : en-têtes centrés, infos compactes, grande zone d'animation
- 11 visualisations animées (une par animation)
- Mises à jour temps réel à 10 FPS

---

## Modes de Fonctionnement
- **Permanent** : Toujours allumé (par défaut)
- **Détection Mouvement** : Activation par capteur PIR (30s après mouvement)

---

## Animations
- Éteint, Fade Alterné, Clignotement Alterné, Pulsation, Respiration, Strobe, Battement Cœur, Vague, Scintillement, Météore, Auto (enchaînement)

---

## Utilisation Quotidienne
- Changer animation/mode avec les boutons ou l'interface web
- Suivre l'état sur le LCD et le tableau de bord web

---

## Dépannage
Voir [TROUBLESHOOTING_FR.md](TROUBLESHOOTING_FR.md) pour l'aide.

---

**Version du document : v1.0.0 (2025-12-30)**
