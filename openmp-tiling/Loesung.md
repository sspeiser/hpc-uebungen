# Arbeitsaufteilung

## Frage: 

Wie können Sie eine n x n-Matrix optimal auf p Prozessoren aufteilen unter folgenden Bedingungen:
- Stencil-Operation, die die 4 direkt benachbarten Elemente der Matrix zur Berechnung des neuen Werts verwendet (links, rechts, oben, unten - nicht diagonal)
- Kein "Wrap-Over", d.h. das erste Element ("links-oben") verwendet nur 3 Nachbarn
- Nur Read-Operationen


## Antwort:

Optimal ist eine Aufteilung, die Blocks bildet mit möglichst wenigen Randelementen. Das sind in diesem Fall Quadrate, z.B. bei n = 8 und p = 4:
![Illustration Tiling](tiling.svg)


Als Größenordnung:
- n = 1024, p = 16:
  - Quadrate: 6.144
  - Zeilen: 30.720
  - Verhältnis: 5x
