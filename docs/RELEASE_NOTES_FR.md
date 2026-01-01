# Notes de Version - LED-Garland-Anim

Historique complet des versions du projet LED-Garland-Anim.

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

**LED-Garland-Anim v1.10.0** - Contrôleur moderne de guirlande LED pour ESP32 IdeaSpark 🎄✨
