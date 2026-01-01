# Notes de Version - LED-Garland-Anim

Historique complet des versions du projet LED-Garland-Anim.

---

# [1.11.3] – 2026-01-01

### Corrections (PATCH - Améliorations Qualité des Animations)

**Animation Matrix Rain (Pluie Matrix)**
- Correction de l'animation n'utilisant que les 2 premières lignes au lieu de l'affichage 8x8 complet
- Refonte complète avec flux de chute indépendants par colonne
- Chaque colonne a une vitesse différente et des positions de départ échelonnées
- Dégradé de luminosité approprié créant un effet Matrix réaliste

**Animation Horloge**
- Redessinée pour remplacer le design brouillon et encombré par un design propre et élégant
- Cadran circulaire en teinte bleue avec marqueurs d'heures dorés à 12, 3, 6, 9
- Aiguille des secondes rouge fluide avec rotation de 60 secondes
- Beaucoup plus lisible et visuellement attrayante

---

# [1.11.2] – 2026-01-01

### Corrections (PATCH - Correction Système de Coordonnées)

**Système de Mapping des Coordonnées de la Matrice**
- Correction du schéma d'indexation en zigzag incorrect dans la matrice NeoPixel 8x8
- Implémentation d'une indexation linéaire uniforme (toutes les lignes 0-7 vont de gauche→droite)
- Corrige le positionnement des pixels et les distorsions visuelles dans les 38 animations de la matrice
- Modification de la fonction `xy()` pour utiliser un mapping linéaire simple : `return y * 8 + x;`

### Technique
- Toutes les lignes suivent maintenant le même schéma gauche-à-droite
- Spécification des coordonnées : Ligne N = pixels (N×8) à (N×8+7)
- Garantit l'alignement correct des animations avec la disposition physique des LEDs

---

# [1.11.1] – 2026-01-01

### Corrections (PATCH - Synchronisation)

**Synchronisation Intervalle Mode Auto Matrice**
- Le mode auto matrice partage maintenant le même intervalle que le mode auto guirlande
- Un seul contrôle UI ajuste la durée d'animation pour les deux simultanément
- Les deux modules appellent `getAutoAnimationIntervalMs()` pour une synchronisation temporelle
- Par défaut : 30 secondes (configurable de 5s à 5 minutes via l'interface web)

---

# [1.11.0] – 2026-01-01

### Ajouts (MINOR - Nouvelles Fonctionnalités + Améliorations Majeures)

**NOUVELLE FONCTIONNALITÉ : Mode Auto pour la Matrice**
- Cycle automatique à travers toutes les animations de la matrice
- Intervalle synchronisé avec le mode auto guirlande
- N'utilise jamais l'état OFF - affichage d'animation continu

**Corrections Logique Modes de Détection**
- MODE_MOTION_TRIGGER : La matrice se rallume correctement lors de la détection de mouvement
- Correction d'un bug critique où la matrice restait éteinte après le timeout
- Préserve les paramètres d'animation et de luminosité pendant les cycles de détection de mouvement

**Améliorations Qualité des Animations** (14 animations corrigées)
- Canne en Sucre : Crochet diagonal réaliste avec rayures rouges/blanches rotatives
- Horloge : Aiguille des secondes en temps réel, rotation horaire, marqueurs d'heures appropriés
- Lapin : Yeux clignotants ajoutés
- Fleur : Fleur reconnaissable à 8 pétales qui s'épanouit
- Météore : Couverture diagonale complète de la matrice
- Père Noël : Traits faciaux améliorés (chapeau, yeux, nez, barbe)
- Cadeau : Boîte claire avec ruban et nœud
- Flocon de Neige : Effet de pulsation battement de cœur
- Vague Arc-en-Ciel : Mouvement d'onde sinusoïdale véritable
- Plasma : Clarté visuelle améliorée
- Radar : Persistance des cibles améliorée

### Supprimé
- Animation Glaçons complètement supprimée

---

# [1.10.0] – 2026-01-01

### Ajouts (MINOR - Nouvelles Animations + Améliorations UX)

**Nouvelles Animations Matrice :**
- **Feu de Camp** : Simulation réaliste de feu avec algorithme de propagation de chaleur (carte thermique 64 cellules, diffusion vers le haut/latérale, dégradé rouge→orange→jaune→blanc)
- **Radar** : Balayage radar militaire vert avec cibles (ligne de balayage rotative, traînée estompée, grille concentrique, cibles aléatoires)

**Refonte d'Animation :**
- **Chaussette (Noël)** : Complètement redessinée pour meilleure reconnaissance
  - Forme claire de chaussette avec bord blanc, corps rouge, bande verte, étoile dorée
  - Animation de balancement pendulaire réaliste
  - Désormais facilement identifiable comme chaussette de Noël

### Modifications

- **Interface Web : Plus de Rechargement de Page (CORRECTION UX CRITIQUE)**
  - Suppression de tous les appels `location.reload()` - plus de flash blanc
  - Implémentation de mises à jour AJAX uniquement pour transitions fluides
  - Nouvelles fonctions : `updateCurrentAnimation()`, `updateCurrentMode()`, `updateCurrentMatrix()`
  - Retour visuel instantané sans rafraîchissement de page

### Technique
- Total Animations : 37 → 39 (Feu de Camp + Radar)
- Enum mis à jour, tableau de noms d'animations, switch cases
- Mises à jour DOM JavaScript sans rechargement de page
- Classes CSS des boutons radio mises à jour instantanément

---

# [1.9.0] – 2026-01-01

### Modifications (MINOR - Améliorations Interface)

**Modernisation Interface Web :**
- **Boutons Radio Remplacent Listes Déroulantes** : Toutes les sélections utilisent maintenant des grilles de boutons radio (Matrice : 37, Modes : 3, Guirlande : 11)
- **Layout Responsive 2 Colonnes** : 2 colonnes sur écrans larges, 1 colonne sur étroits (<600px)
- **Sélection Instantanée** : Suppression de tous les boutons "Appliquer" - changements appliqués immédiatement via événements `onchange`
- **Retour Visuel Amélioré** : Éléments sélectionnés surlignés avec fond/bordure verts, effets de survol
- **Messages Plus Rapides** : Réduction du temps d'affichage de 3s à 2,5s

### Corrections
- **BUGFIX #8** : 3ème mode manquant (MODE_MOTION_MATRIX_INDEPENDENT) s'affiche maintenant correctement dans l'interface web

### Technique
- 8 nouvelles classes CSS pour boutons radio et grille responsive
- Remplacement `<select>` par `<div class='radio-grid'>` + inputs radio
- Fonctions JavaScript acceptent paramètre ID directement
- Interface compacte malgré 51 boutons radio au total
- Layout une colonne optimisé pour mobile

---

# [1.8.1] – 2026-01-01

### Corrections (PATCH - Corrections de Bugs Uniquement)

**7 Corrections de Bugs Numérotées :**
- **BUGFIX #1** : Matrix Rain - Réduction du fade (220→245) pour garder les rangées inférieures visibles
- **BUGFIX #2** : Horloge - Inversion de la direction de rotation (sens horaire maintenant)
- **BUGFIX #3** : Compte à rebours - Chiffres 3, 2, 1 redessinés pour meilleure clarté
- **BUGFIX #4** : Glaçons - Ajout des 8 glaçons avec gouttes d'eau animées
- **BUGFIX #5** : Bougie - Base élargie à 4px, flamme rétrécie à 2px avec scintillement
- **BUGFIX #6** : Cloche - La cloche reste fixe, seul le battant bouge
- **BUGFIX #7** : Layout Interface Web - Espace réservé avec `visibility:hidden` empêche déplacement des boutons

---

# [1.8.0] – 2026-01-01

### Ajouts
- **Nouveau Mode** : MODE_MOTION_MATRIX_INDEPENDENT (guirlande déclenchée par mouvement, matrice toujours allumée)
- **Synchronisation Matrice** : La matrice suit l'état de la guirlande en mode MODE_MOTION_TRIGGER
- **Libellés de Mode Améliorés** : "Permanent", "Détection (tout)", "Détection (guirlande)"

### Corrections (CRITIQUES)
- **Mapping GPIO** : Restauration du GPIO matrice de 13 vers 32 (pin correcte)
- **Bugs de Timing d'Animations** : Correction de 8 animations utilisant le timing défectueux \`elapsed % N == 0\`
  - Affectées : Meteor, Shooting Star, Snow, Champagne, Confetti, Sparkle Rain, Matrix Rain, Stars Field
  - Solution : Timing basé sur seuil avec variables statiques \`lastUpdate\`

---

# [1.7.0] – 2026-01-01

### Ajouts

**27 Nouvelles Animations Matrice** (total : 37)

**Noël (10) :**
- Canne à sucre, Couronne, Chaussette, Renne, Bonhomme en pain d'épices
- Chocolat chaud, Cheminée, Glaçons, Aurore boréale, Pile de cadeaux

**Nouvel An (7) :**
- Feux d'artifice, Bulles de champagne, Compte à rebours 3-2-1, Confettis
- Horloge, Cotillon, Boule disco

**Pâques (4) :**
- Œuf de Pâques, Lapin sauteur, Poussin éclos, Fleurs printanières

**Moderne/Abstrait (6) :**
- Vague arc-en-ciel, Pluie scintillante, Effet plasma, Pluie matricielle digitale
- Spirale rotative, Cœur pulsant, Champ d'étoiles scintillantes

---

# [1.6.0] – 2026-01-01

### Ajouts
- **Support Matrice NeoPixel 8x8** : Matrice WS2812B-64 sur GPIO 32
- **10 Animations Matrice** : Étoile, Météore, Étoile filante, Père Noël, Sapin, Cloche, Neige, Cadeau, Bougie, Flocon
- **Contrôle Double Indépendant** : Guirlande et matrice fonctionnent indépendamment
- **Paramètres Matrice** : Sélection d'animation, contrôle de luminosité (0-255)
- **Persistance NVS** : Paramètres matrice sauvegardés/restaurés automatiquement
- **Intégration Interface Web** : Contrôles matrice ajoutés au tableau de bord

---

**Voir CHANGELOG_FR.md pour l'historique détaillé des commits.**

**LED-Garland-Anim v1.11.3** - Contrôleur moderne de guirlande LED pour ESP32 IdeaSpark 🎄✨
