# CPU vs. Memory

Im Programm `cpu-vs-mem.c` finden Sie ein Methode `measure`, die eine Funktion ausführt und über die gegebenen Parameter berechnet wie viele MFLOP/s pro Sekunde erreicht wurden und wie viele Gigabyte an Daten pro Sekunde verarbeitet wurden.

Im Moment ist nur eine Funktion definiert, die 2 große Float-Arrays paarweise addiert und in einem dritten Array speichert. 

Gehen Sie wie folgt vor:
- Implementieren Sie eine weitere Funktion, die das gleiche tut aber parallelisiert über OpenMP
- Übersetzen Sie den Code auf mindestens 2 Arten und vergleichen die Ergebnisse:
  - `gcc -fopenmp cpu-vs-mem.c -mavx -lm`
  - `gcc -O3 -fopenmp cpu-vs-mem.c -mavx -lm`

Was sind die Unterschiede bei den 4 verschiedenen Ausführungen, wo liegt der begrenzende Faktor.

Implementieren Sie für die folgenden Funktionen jeweils eine sequenzielle und eine OpenMP-parallelisierte Version und testen sowohl mit als auch ohne `-O3`:
- Länge von Vektoren, wenn a die x und b die y Koordinate enthält: c[i] = sqrt(a[i] * a[i] + b[i] * b[i]);
- Einen Stencil, der c[i] aus einer gewichteten Summe der Elemente a[i] bis a[i] + 7 berechnet (alle Elemente mit 1/8 gewichtet, d.h. der Durchschnitt wird gebildet)
- Einer gemischten Berechnung, wo c[i] eine gewichtete Summe von a[i] und b[i] ist, a[i] eine gewichtete Summe von a[i] und b[i] und b[i] eine Skalierung (Multiplikation) von b[i]

Achten Sie auf die passenden Parameter `flop_pro_berechnung, byte_pro_berechnung` beim Aufruf von `measure`.

Was sind Ihre Beobachtungen bzgl. MFLOP/s und GByte/s? Woran kann es liegen?