# Notes de version - v5.1.0

**Date**: 6 janvier 2026  
**Version**: 5.1.0 (MINEUR)  
**Classification**: Amélioration de l'utilisabilité + Ajout de fonctionnalité

---

## 🎯 Objectifs

Cette version corrige le débordement du texte SSID et réorganise l'écran LCD animé pour une meilleure lisibilité en convertissant les panneaux côte-à-côte en zones empilées fullwidth. Le nom d'appareil mDNS s'affiche désormais en évidence aux côtés de l'IP et des infos réseau.

---

## ✨ Quoi de neuf

### 1. **Réorganisation du layout de l'écran animé**

L'écran animé a été restructuré d'un **design avec panneaux côte-à-côte** vers des **zones empilées fullwidth** :

#### Layout antérieur (v5.0.0):
```
┌─────────────────────────────────────┐
│       NOM DU PROJET + VERSION       │  En-tête (14, 14, 212, 58)
├────────────────┬────────────────────┤
│ INFOS GAUCHE   │ ANIMATION DROITE   │
│ (128px large)  │ (96px large)       │
│ Mode           │ Mini show (petit)  │
│ Anim guirlande │ [Zone animation]   │
│ Anim matrice   │                    │
│ ----           │                    │
│ SSID: [texte]  │                    │  ← SSID risque de déborder
│ IP: [adresse]  │                    │
└────────────────┴────────────────────┘
```

#### Nouveau layout (v5.1.0):
```
┌─────────────────────────────────────┐
│       NOM DU PROJET + VERSION       │  En-tête (14, 14, 212, 58) - Inchangé
├─────────────────────────────────────┤
│ CADRE INFOS (Fullwidth, 70px)       │  Mode | WiFi: SSID | IP | mDNS | Anim
│ Lisibilité améliorée, sans dépassem │
├─────────────────────────────────────┤
│                                     │
│  ZONE ANIMATION (Fullwidth)         │  Viewport plus grand
│  Meilleur ratio d'aspect            │
│                                     │
└─────────────────────────────────────┘
```

**Avantages**:
- ✅ SSID ne déborde plus (troncature automatique à 20 chars avec "...")
- ✅ Toutes les infos réseau (Mode, WiFi, IP, mDNS) dans un cadre visible
- ✅ Zone animation gagne plus d'espace vertical (était à l'étroit en 96px)
- ✅ Meilleure utilisation de l'écran (petit affichage 1.14")
- ✅ Plus facile à lire

---

### 2. **Logique de troncature du SSID**

Une nouvelle fonction helper `truncateText()` raccourcit automatiquement les longs SSID :

```cpp
auto truncateText = [](const String& text, int maxLen) -> String {
    if (text.length() <= maxLen) return text;
    return text.substring(0, maxLen - 2) + "..";
};

// Exemple:
// "NomDuResauTresLongId12345" (28 chars)
// → "NomDuResauTresLongId.." (20 chars max)
```

---

### 3. **Affichage du nom mDNS**

#### Signatures de fonction améliorées:
```cpp
// Accepte désormais le paramètre mDnsName (optionnel)
void displayScreenByMode(const char* ssid, IPAddress ip, const char* modeName,
                         const char* animationName, const char* matrixAnimationName = nullptr,
                         const char* mDnsName = nullptr);

void displayMainScreen(const char* ssid, IPAddress ip, const char* modeName,
                       const char* animationName, const char* matrixAnimationName = nullptr,
                       const char* mDnsName = nullptr);
```

#### Résultat affiché:
L'écran animé affiche maintenant mDNS dans le cadre d'infos :
```
Mode: Permanent
WiFi: MonReseau
IP: 192.168.1.42
mDNS: guirlande.local
Anim: arc-en-ciel + pulse
```

---

### 4. **Appels display mis à jour**

Tous les appelants ont été mis à jour pour passer le nom mDNS :

#### main.cpp:
```cpp
String mDnsStr = String(getDeviceName()) + ".local";
displayScreenByMode(WiFi.SSID().c_str(), WiFi.localIP(),
                   getGarlandModeName(), getGarlandAnimationName(),
                   getMatrix8x8AnimationName(), mDnsStr.c_str());
```

#### web_interface.cpp:
```cpp
// Même pattern dans handleSetAnimation(), handleSetMode(), handleDisplayMode()
String mDnsStr = String(getDeviceName()) + ".local";
displayScreenByMode(..., mDnsStr.c_str());
```

#### telegram_control.cpp:
```cpp
// Mis à jour dans applyAnimationCommand(), applyModeCommand(), etc.
String mDnsStr = String(getDeviceName()) + ".local";
displayMainScreen(..., mDnsStr.c_str());
```

---

## 🔧 Détails techniques

### Modifications du code:

1. **src/display.cpp**:
   - Fonction `displayMainScreen()` refactorisée (~130 lignes)
   - Lambda helper `truncateText()` ajoutée
   - Nouveaux calculs de layout pour zones fullwidth
   - `displayScreenByMode()` mise à jour pour gérer le paramètre mDnsName

2. **include/display.h**:
   - Signatures de fonction mises à jour avec le paramètre `mDnsName`
   - Docstrings mises à jour pour refléter le nouveau layout

3. **src/main.cpp, src/web_interface.cpp, src/telegram_control.cpp**:
   - Tous les appels display construisent et passent la chaîne mDNS
   - Pattern cohérent : `String(getDeviceName()) + ".local"`

4. **platformio.ini**:
   - Version relevée : `PROJECT_VERSION="5.0.0"` → `PROJECT_VERSION="5.1.0"`

### Rétrocompatibilité:
✅ **Entièrement compatible** - Le paramètre mDnsName est optionnel (par défaut nullptr)

---

## 📊 Dimensions du layout

### En-tête (Inchangé):
- Position: (14, 14)
- Taille: 212×58 px
- Contenu: NOM_PROJET + "v" + VERSION_PROJET

### Cadre Infos (Nouveau):
- Position: (8, 88)
- Taille: 224×70 px  ← **Fullwidth**
- Contenu:
  - Ligne 1: Mode: [modeName]
  - Ligne 2: WiFi: [ssid troncé à 20 chars]
  - Ligne 3: IP: [ip.toString()]
  - Ligne 4: mDNS: [deviceName.local] (si fourni)
  - Ligne 5: Anim: [animationName] [+ matrixAnimationName]

### Zone Animation (Nouvelle):
- Position: (8, 162)
- Taille: 224×[hauteur restante] px  ← **Fullwidth, plus grande**
- Contenu: Rendu animation réelle

---

## 🐛 Problèmes corrigés

1. **Débordement SSID** → Troncature automatique à 20 chars avec "..."
2. **Affichage mDNS manquant** → Affiché désormais dans le cadre infos
3. **Zone animation à l'étroit** → Plus d'espace vertical avec layout fullwidth
4. **Lisibilité faible** → Meilleur espacement, contraste couleurs, séparation lignes

---

## 📚 Mises à jour documentation

- ✅ [README.md](../README.md) – Mis à jour en v5.1.0, description layout
- ✅ [README_FR.md](../README_FR.md) – Mis à jour en v5.1.0, description en français
- ✅ [docs/USER_GUIDE.md](USER_GUIDE.md) – Section écran animé mise à jour
- ✅ [docs/USER_GUIDE_FR.md](USER_GUIDE_FR.md) – Version française mise à jour
- ✅ [CHANGELOG.md](../CHANGELOG.md) – Entrée v5.1.0 ajoutée
- ✅ [CHANGELOG_FR.md](../CHANGELOG_FR.md) – Entrée v5.1.0 en français

---

## 🚀 Build & Test

### Résultat du build:
```
Successfully created esp32 image.
Flash:   81.7%
RAM:     15.8%
Took 466.84 seconds
```

### Checklist de test:
- ✅ Modes d'affichage (Animé, Statique, Éteint) s'affichent correctement
- ✅ Troncature SSID fonctionne (noms longs testés)
- ✅ Nom mDNS s'affiche correctement
- ✅ Zone animation s'affiche sans superposition
- ✅ Clics bouton déclenchent mises à jour display
- ✅ Changements interface web appliquent à l'LCD
- ✅ Animation boot s'affiche correctement
- ✅ Mises à jour OTA préservent paramètres

---

## 📝 Résumé commit

```
feat(display): reorganize animated LCD to fullwidth stacked zones (v5.1.0)

- Convertir panneaux côte-à-côte vers cadre infos fullwidth + zone animation
- Ajouter troncature SSID (max 20 chars) pour prévenir débordement
- Ajouter paramètre mDnsName à displayScreenByMode() et displayMainScreen()
- Mettre à jour tous les appels display pour passer mDNS (main.cpp, web_interface.cpp, telegram_control.cpp)
- Améliorer lisibilité avec meilleur espacement et contraste couleurs
- Relevar version 5.0.0 → 5.1.0 dans platformio.ini, display.h, display.cpp
- Mettre à jour changelog et notes de version EN/FR
```

---

## 🎓 Classification de version

**SEMVER**: 5.1.0 (MINEUR)

**Justification**: 
- Réorganisation du layout améliore l'utilisabilité sans casser l'API
- Ajout du paramètre mDNS est optionnel (rétrocompatible)
- Corrections préviennent la confusion utilisateur (débordement SSID, infos réseau manquantes)
- Pas de changements cassants aux interfaces publiques

---

## 📌 Étapes suivantes

- Suivi retour utilisateurs sur le nouveau layout
- Considérer option configuration pour commuter les modes d'affichage par préférence utilisateur
- Futur: Support UI multi-langue sur LCD

---

**Profitez de l'affichage LCD animé amélioré ! 🎄✨**
