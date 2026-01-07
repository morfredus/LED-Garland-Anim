# Détection de mouvement par radar Doppler (RCWL-0516) - LED-Garland-Anim v5.1.4

## Présentation
Le module RCWL-0516 est un capteur radar Doppler micro-ondes permettant de détecter rapidement et précisément les mouvements, même à travers certains matériaux non métalliques. Il constitue une alternative plus réactive et moins sensible à la température que le capteur PIR.

## Branchement
- **VCC** : 3,3 V ou 5 V (compatible ESP32)
- **GND** : Masse
- **OUT** : GPIO 35 (ou autre entrée numérique de l’ESP32)
- **CDS** (optionnel) : Laisser flottant ou relier à GND pour activer la détection en continu

## Exemple de code (remplacement du PIR)
```cpp
#define RADAR_PIN 35  // GPIO utilisé pour la sortie OUT du RCWL-0516

void setup() {
  pinMode(RADAR_PIN, INPUT);
  // ...autres initialisations...
}

void loop() {
  bool mouvement = digitalRead(RADAR_PIN) == HIGH;
  if (mouvement) {
    // Déclencher l’animation ou l’action souhaitée
  }
  // ...autres traitements...
}
```

## Conseils d’intégration
- Détecte à travers le plastique fin, mais pas le métal.
- Éviter la proximité immédiate d’alimentations ou d’objets métalliques.
- Sensible aux mouvements derrière des cloisons fines : ajuster le positionnement si besoin.
- Portée ajustable en ajoutant une résistance sur la broche « R-GN ».

## Avantages
- Détection très rapide et précise
- Insensible à la température ambiante
- Large angle de détection (~120°)

## Limites
- Pas de réglage de sensibilité physique intégré (mais modifiable par résistance)
- Peut détecter à travers des parois fines non métalliques (attention aux faux positifs)

## À intégrer dans le firmware et la documentation utilisateur si ce capteur est retenu comme option officielle.
