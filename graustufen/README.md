# Konvertierung eines Bilds in Graustufen

In dieser Übung wollen wir ein Farbbild in Graustufen umwandeln. Die Ziele der Übung sind:
- "Warm werden" mit C und Python
- Erste Performance-Messungen durchführen
- Unterschiedliche Muster für Lösung einer Aufgabe ausprobieren

Wenn ein Farbbild in Graustufen konvertiert wird, wird für jeden Pixel der Graufstufenwert als gewichtete Summe der Farbkomponenten berechnet (siehe [Wikipedia](https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale)):
```
GRAU = 0.2126 * ROT + 0.7152 * GRUEN + 0.0722 * BLAU
```

## Nicht-optimierter serieller Ansatz in C

In der Datei `graustufen-loop.c` finden Sie ein Grundgerüst für ein C-Programm, das
1. ein farbiges JPG einliest in ein Byte-Array
2. einen Speicherbereich für das Byte-Array eines Graustufen-Bilds gleicher Größe allokiert
3. das Byte-Array in ein JPG schreibt

Was fehlt ist Ihr Code zwischen Schritt 2 und 3, der die Konvertierung vornimmt.

Beachten Sie:
- im eingelesenen Byte-Array belegt jeder Pixel 3 Byte: Rot, Grün, Blau; die Pixel sind wie in C üblich im [Row-Major-Format](https://en.wikipedia.org/wiki/Row-_and_column-major_order) angeordnet
- das zu schreibende Byte-Array ist im Prinzip gleich hat jedoch nur 1 Byte für die Graustufe pro Pixel
- Die einzelnen Rot-/Grün-/Blau-/Graustufenwerte werden im Bereich 0 - 255 als Ganzzahlen abgelegt

Gehen Sie wie folgt vor:
1. Nutzen Sie einfache Schleifen, um durch alle Pixel zu gehen und jeweils aus den Farbwerten den Graustufenwert zu berechnen: Im Code an Stelle `// TODO Konvertierung`
2. Berechnen Sie die Anzahl der benötigten Fließkommaoperationen (FLOP) für die Konvertierung - also die Anzahl der Multiplikationen und Additionen und geben diese aus: Im Code an Stelle `// TODO FLOP Berechnung`
3. Messen Sie die Zeit für Ihre Konvertierung - ohne das Laden und Schreiber der Dateien. Nutzen Sie hierfür die Funktion `gettimeofday`: Im Code an Stelle `// TODO Zeitmessen Start` und `// TODO Zeitmessen Ende`
4. Berechnen Sie die FLOP/s, die Ihr Algorithmus erreicht hat und geben Sie das Ergebnis aus an Stelle `//TODO Ausgabe FLOP/s`
5. Vergleichen Sie die erreichte Zahl mit der theoretischen Single-Core Leistung Ihrer CPU. Warum liegt der Wert darunter?

Kompilieren Sie das Programm mit gcc:
```
$ gcc -o graustufen-loop.out graustufen-loop.c -lm
...
$ ./graustufen-loop.out
```

## NumPy

Siehe [Jupyter-Notebook](graustufen-numpy.ipynb).

