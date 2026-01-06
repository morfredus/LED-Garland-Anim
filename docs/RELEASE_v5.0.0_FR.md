# Release v5.0.0 - Refonte festive de l’écran animé

## Faits marquants
- L’écran LCD animé reprend le style festif du statique (fond texturé, cadres ruban, scintillements, double guirlande).
- La zone d’animation devient une fenêtre compacte « Mini show » pour privilégier le texte et les décors tout en gardant l’animation fluide.
- Cartouche d’infos enrichie : Mode, animation guirlande, animation matrice, SSID et IP regroupés avec des accents colorés pour une lecture immédiate.

## Changements
1. Refonte de `displayMainScreen` avec le langage visuel festif déjà utilisé sur l’écran statique.
2. Réduction et cadrage de la zone d’animation en mini scène ; conservation de toutes les informations affichées.
3. Documentation synchronisée (README, USER_GUIDE) et ajout de cette note de version.

## Fichiers impactés
- src/display.cpp
- include/display.h
- platformio.ini
- CHANGELOG.md / CHANGELOG_FR.md
- README.md / README_FR.md
- docs/USER_GUIDE.md / docs/USER_GUIDE_FR.md

## Notes de mise à niveau
- Recompiler et téléverser normalement ; aucune configuration supplémentaire requise.
- Le mode animé présente désormais une fenêtre d’animation réduite et un panneau d’informations plus riche.
