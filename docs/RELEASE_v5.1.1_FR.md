# Notes de publication - v5.1.1

**Date** : 7 janvier 2026  
**Version** : 5.1.1 (PATCH)  
**Classification** : Correction critique de bug

---

## 🎯 Résumé

Cette version de correction répare un bug critique où l'animation 8x8 en mode AUTO utilisait incorrectement l'intervalle d'animation de la guirlande au lieu du sien. À partir de la v5.1.1, les modes AUTO de la matrice et de la guirlande fonctionnent désormais indépendamment avec des intervalles séparés et configurables.

---

## 🐛 Bug Critique Corrigé

### Mode AUTO Matrice Utilisant le Mauvais Intervalle (CORRIGÉ)

**Problème :**
- L'animation 8x8 en mode AUTO utilisait `getAutoAnimationIntervalMs()` (intervalle guirlande)
- Cela signifiait que la matrice ne pouvait pas avoir sa propre durée de cycle d'animation indépendante
- Les utilisateurs ne pouvaient pas définir des vitesses d'animation différentes pour la guirlande et la matrice

**Cause racine :**
- La ligne 2019 du fichier `src/matrix8x8_control.cpp` dans la fonction `updateMatrix8x8()` appelait la mauvaise fonction getter
- Un commentaire de code trompeur indiquait que les intervalles étaient intentionnellement partagés

**Solution :**
- Modification de la ligne 2019 pour utiliser `getMatrix8x8AnimationIntervalMs()` au lieu de `getAutoAnimationIntervalMs()`
- Mise à jour de la documentation pour clarifier que les intervalles sont maintenant indépendants
- Suppression du commentaire trompeur sur le partage des intervalles

**Impact :**
- ✅ Le mode AUTO matrice respecte désormais le paramètre « Intervalle d'animation matrice »
- ✅ Le mode AUTO guirlande continue d'utiliser le paramètre « Intervalle du mode auto »
- ✅ Les deux peuvent fonctionner simultanément à des vitesses différentes
- ✅ Chaque intervalle est indépendamment sauvegardé et restauré au redémarrage
- ✅ **Entièrement rétro-compatible** : API web inchangée, paramètres existants préservés

---

## 🔧 Détails Techniques

### Modifications de Code

**Fichier** : `src/matrix8x8_control.cpp`

**Avant :**
```cpp
// Ligne 21 (supprimée)
// NOTE: Auto mode interval is shared with garland - uses getAutoAnimationIntervalMs()

// Ligne 2019
unsigned long interval = getAutoAnimationIntervalMs();  // Shared with garland
```

**Après :**
```cpp
// Ligne 23 (mise à jour)
// Matrix animation interval (independent from garland)

// Ligne 2019
unsigned long interval = getMatrix8x8AnimationIntervalMs();  // Matrix-specific interval
```

### Vérification de la Persistance

- **Chargement** : `loadMatrix8x8Settings()` restaure correctement l'intervalle sauvegardé depuis la NVS
- **Sauvegarde** : `setMatrix8x8AnimationIntervalMs()` sauvegarde correctement l'intervalle dans la NVS
- **Restauration** : L'intervalle matrice survit aux redémarrages de l'appareil indépendamment

### Mises à Jour de Version

Tous les en-têtes de fichier mis à jour à la v5.1.1 (2026-01-07) :
- `include/config.h`
- `include/matrix8x8_control.h`
- `src/matrix8x8_control.cpp`
- `src/main.cpp`
- `include/garland_control.h`

---

## 📚 Mises à Jour de Documentation

### Guides Utilisateur
- **docs/USER_GUIDE.md** : Mise à jour à la v5.1.1, ajout de la section « ⚠️ Important: Garland & Matrix Auto Modes Are Independent »
- **docs/USER_GUIDE_FR.md** : Mise à jour à la v5.1.1, ajout de la traduction française de l'avis d'indépendance

### Journaux des Modifications
- **CHANGELOG.md** : Ajout de l'entrée v5.1.1 avec description détaillée de la correction
- **CHANGELOG_FR.md** : Ajout de l'entrée v5.1.1 avec description en français

### Documentation de Persistance NVS
Mise à jour pour indiquer clairement que les deux intervalles (guirlande et matrice) sont sauvegardés indépendamment :
- Guirlande : « Intervalle du mode auto »
- Matrice : « Intervalle d'animation matrice »

---

## ✅ Liste de Validation

- ✅ Le mode AUTO matrice utilise désormais l'intervalle indépendant du paramètre d'interface web
- ✅ Le mode AUTO guirlande continue d'utiliser son propre intervalle (inchangé)
- ✅ L'intervalle matrice est correctement sauvegardé dans la NVS lors de la modification
- ✅ L'intervalle matrice est correctement restauré au démarrage de l'appareil
- ✅ Les deux intervalles peuvent avoir des valeurs différentes simultanément
- ✅ Aucun changement cassant de l'API
- ✅ Toutes les versions de fichier mises à jour à la v5.1.1
- ✅ Les deux changelogs mis à jour (EN + FR)
- ✅ Les deux guides utilisateur mis à jour avec avis d'indépendance (EN + FR)

---

## 📋 Résumé des Commits et Modifications

### Fichiers Modifiés :
1. `src/matrix8x8_control.cpp` - Correction principale (ligne 2019 et nettoyage des commentaires)
2. `include/config.h` - Mise à jour de version à 5.1.1
3. `include/matrix8x8_control.h` - Mise à jour de version à 5.1.1
4. `src/main.cpp` - Mise à jour de version à 5.1.1
5. `include/garland_control.h` - Mise à jour de version à 5.1.1
6. `CHANGELOG.md` - Ajout entrée v5.1.1
7. `CHANGELOG_FR.md` - Ajout entrée v5.1.1
8. `docs/USER_GUIDE.md` - Mise à jour version et ajout avis d'indépendance
9. `docs/USER_GUIDE_FR.md` - Mise à jour version et ajout avis d'indépendance (Français)

### Fichiers Créés :
- `docs/RELEASE_v5.1.1.md` (ce fichier)
- `docs/RELEASE_v5.1.1_FR.md` (version française)

---

## 🎉 Pour les Utilisateurs

Si vous utilisez la v5.1.0 ou antérieure :

1. **Mettez à jour vers la v5.1.1** en utilisant OTA ou téléchargement série
2. **Consultez l'interface Web** : Vous verrez désormais deux paramètres d'intervalle séparés :
   - « Intervalle du mode auto » (Guirlande en mode AUTO)
   - « Intervalle d'animation matrice » (Matrice en mode AUTO)
3. **Personnalisez indépendamment** : Définissez des vitesses différentes pour chaque appareil selon vos préférences
4. **Paramètres persistants** : Vos nouveaux intervalles survivront aux redémarrages

---

## 📊 Classification SEMVER

**Type** : PATCH (5.1.0 → 5.1.1)

**Justification** :
- Corrige bug critique (indépendance d'intervalle matrice)
- Aucune nouvelle fonctionnalité ajoutée
- Aucun changement cassant de l'API
- Entièrement rétro-compatible
- Configuration existante préservée

---

## 🔗 Ressources Associées

- [CHANGELOG_FR.md](CHANGELOG_FR.md) - Journal des modifications complet
- [USER_GUIDE_FR.md](USER_GUIDE_FR.md) - Guide utilisateur mis à jour
- [TROUBLESHOOTING_FR.md](TROUBLESHOOTING_FR.md) - Aide au dépannage
- [Dépôt GitHub](https://github.com/morfredus/LED-Garland-Anim.git)
