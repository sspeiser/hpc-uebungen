# Arbeitsaufteilung

Wie können Sie eine n x n-Matrix optimal auf p Prozessoren aufteilen unter folgenden Bedingungen:
- Stencil-Operation, die die 4 direkt benachbarten Elemente der Matrix zur Berechnung des neuen Werts verwendet (links, rechts, oben, unten - nicht diagonal)
- Kein "Wrap-Over", d.h. das erste Element ("links-oben") verwendet nur 2 Nachbarn
- Nur Read-Operationen von Elementen, die zu einem anderen Prozessor gehören

Berechnen Sie die Anzahl der benötigten Operationen
- als absolute Zahl für n = 8 und p = 4 und 
- als allgemeine Formel von n und p

für

- Ihre optimale Aufteilung
- die Aufteilung in p Zeilen


In der Datei `openmp-tiling.c` ist ein OpenMP-Programm, das eine 16x16-Matrix auf 16 Threads aufteilt und dann die Aufteilung ausgibt. Wie können Sie die Funktion `mem_to_thread` so umändern, dass die optimale Aufteilung entsteht? Um den Code einfach zu halten, können Sie davon ausgehen, dass die Matrix quadratisch und jede Seitenlänge durch die Anzahl der Threads teilbar ist.
