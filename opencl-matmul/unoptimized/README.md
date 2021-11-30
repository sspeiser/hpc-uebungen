# Matrix Multiplication mit OpenCL - Ohne jegliche Optimierung

Es ist ein Gerüst gegeben in `matmul-unoptimized.c`:
  - Initialisiert zwei Matrixen der Größe N x N (für N = 1024) mit konstanten Werten
  - Kopieren der Matrixen zum Compute Device
  - Kernel aufrufen mit richtigen Dimensionen
  - Kopieren des Ergebnisses zurück zum Host
  - Überprüfen des Ergebnisses
  - Ausgabe der GFLOP/s und Fehler

In der Datei `matmul-unoptimized.cl` finden Sie eine passende Kernel-Deklaration mit Parametern.

Schreiben Sie den Code für den Kernel und messen die Ergebnisse.
Für die Matrizen-Multiplikation können Sie folgenden Sequenziellen Code als Vorlage nehmen:
```
for(int y=0; y<N; y++)
{
    for(int x=0; x<N; x++)
    {
        c[y * N + x] = 0.0;
        for(int k=0; k<N; k++)
        {
            c[y * N + x] += a[y * N + k] * b[k * N + x];
        }
    }
}
```

Können Sie die Anzahl der Zugriffe auf den global Speicher der Graphikkarte reduzieren? Welche Performance erreichen Sie?