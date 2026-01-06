# Version v4.0.0 – 2026-01-06

## Résumé
- Refonte majeure de l'écran statique ST7789 en tableau de bord festif.
- Le mode statique affiche désormais en continu le nom du programme, la version, le SSID, l'IP et le mDNS dans un cadre décoré.
- Documentation mise à jour (EN/FR) pour refléter la nouvelle expérience LCD.

## Points clés
### LCD / ST7789
- Dashboard statique festif avec cadre ruban, coins scintillants et double guirlande décorative.
- Carte de connectivité : SSID, adresse IP et mDNS (`*.local`) toujours visibles.
- Texte non replié pour garder les SSID longs lisibles sans masquer les décorations.

### Documentation
- README.md / README_FR.md : passage en 4.0.0 et description du nouvel écran statique.
- docs/USER_GUIDE.md / docs/USER_GUIDE_FR.md : section LCD mise à jour avec le tableau de bord festif.
- Ajout des notes de version bilingues : docs/RELEASE_v4.0.0.md et docs/RELEASE_v4.0.0_FR.md.

## Notes de mise à jour
1. Flasher le firmware v4.0.0 (USB ou OTA).
2. Placer l'écran en mode **Statique** pour afficher le nouveau tableau de bord festif.
3. Vérifier que SSID, IP et `http://<nom-appareil>.local` sont visibles sur le LCD.

## Build
- Cible : esp32devkitc
- Statut : non compilé dans cette modification (aucune génération automatique requise).

## SEMVER
- Dernière version : 4.0.0 (MAJEUR)
- Raison : Refonte complète de l'écran statique LCD avec nouvelles données (mDNS) et nouveau visuel.
