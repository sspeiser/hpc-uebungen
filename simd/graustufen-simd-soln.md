Hier ist keine ausführliche Lösung, sondern ein paar Hinweise. Eine Implementierung könnte ein Abschlussprojekt darstellen.

- Ablage des Bilds in 3 getrennten Arrays für R, G und B statt in einem Pixel-Array
- Verwenden von Shuffle-Methoden, Shifts und AND-Masken um getrennte R-G-B-Vektoren zu erstellen
- Verwenden von horizontalen Adds um "nebeneinanderliegende" Werte in einem SIMD-Register zu addieren
- Beschleunigungsmöglichkeit: Verwenden von FMA-Instruktionen, die in einem Schritt multiplizieren und addieren