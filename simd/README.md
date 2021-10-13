# Übung: Single Instruction Multiple Data (SIMD)

## Vektor-Addition

In der Datei `matrixadd-simd.c` finden Sie ein Programm, das zwei Matrizen addiert - ähnlich zur Cache-Übung. Dabei wird jedes Wertepaar einzeln in einer for-Schleife durchlaufen.

Optimieren Sie das Programm indem Sie mehrere Wertepaare in einem Schritt gleichzeitig addieren. C-Compiler machen das bei entsprechender Optimierungsstufe automatisch - wenn sie sich sicher sind, dass die Optimierung keine ungewünschten Seiteneffekte hat. Dafür ist es oft notwendig bestimmte Hinweise zu setzen, z.B. mit dem [`restrict`](https://en.wikipedia.org/wiki/Restrict)-Keyword in C oder (teils compilerspezifischen) [Vector-Extensions](https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html#Vector-Extensions). Der Vorteil hierbei ist, dass der Compiler je nach Zielarchitektur die passenden SIMD-Befehle auswählen kann. Wenn man nur für eine bestimmte Prozessorarchitektur optimiert, dann ist die Nutzung von (Inline-)Assembler eine Möglichkeit. Ein Zwischending ist die Nutzung der Intel Intrinsics - das sind Datentypen und Funktionen, die die Prozessorbefehle in C abbilden und sich um Dinge wie Registerzuweisung automatisch kümmern.

In dieser Übung werden wir nur 3 Befehle benötigen:
- `__m128 _mm_load_ps (float const* mem_addr)`: Lädt von der Speicheradresse `mem_addr` 4 hintereinanderliegend `float`s zu je 32-Bit/4 Byte in einen 128-bit SIMD-Wert.
- `__m128 _mm_add_ps (__m128 a, __m128 b)`: Addiert paarweise die 4 `float`s in den Werten a und b und gibt das Ergebnis zurück
- `void _mm_store_ps (float* mem_addr, __m128 a)`: speichert den Wert a an eine Speicheradresse zurück

Die Anzahl der Befehle ist wie erwähnt sehr groß - eine Referenz finden Sie im [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide/).

Optimieren Sie die Addition mit Hilfe der genannten Intrinsics und kompilieren und führen das Programm aus:
 ```
 $ gcc matrixadd-simd.c -mavx -lm
 ...
 # Windows
 $ a.exe
 ...
 # Unix
 $ ./a.out
 ```

Um wie viel konnten Sie das Programm beschleunigen?

Eine ausführlichere Einführung zu Intrinsics finden Sie [hier](https://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX).

Übersetzen Sie das ursprüngliche serielle Programm mit hoher Optimierung und lassen sich einen Report über automatisch gefundene Vektorisierung geben:
```
$ gcc-11 matrixadd-simd.c -mavx -O3 -fopt-info-vec-all
```
Welche Leistung wird erreicht? Wie könnte die Performance noch weiter gesteigert werden? Was ist der limitierende Faktor?


## Graustufen-Konvertierung

Betrachten wir die Graustufen-Konvertierung. Wir können die ersten 5 Pixel zu je 3 Byte und den Rot-Wert des 6. Pixel (insgesamt 16 Byte = 128 Bit) in ein 128-Bit SIMD-Register laden und als 16 vorzeichenlose Integer behandeln:
```
128-Bit: [R1 G1 B1 R2 G2 B2 R3 G3 B3 R4 G4 B4 R5 G5 B5 R6]
```

Welche SIMD-Befehle bräuchten Sie nun, um eine Graustufen-Konvertierung vorzunehmen?
Denken Sie hierbei nach über:
- Datentypen
- Speicheranordnung

Wie könnte man die Speicherung des Farbbilds anpassen, um eine leichtere/schnellere SIMD-Optimierung zu erreichen?