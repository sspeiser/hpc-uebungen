# Warmup: Parallele Programmierung mit OpenMP


## Passwort-Crack

Passwörter werden häufig nicht als Klartext, sondern [gehashten](https://en.wikipedia.org/wiki/Cryptographic_hash_function) Version gespeichert. Die Hashfunktion kann einfach berechnet werden aber nicht praktisch invertiert werden. Das heißt:
- Aus dem Passwort kann sehr einfach der Hashwert berechnet werden
- Aus dem Hashwert kann das Passwort nicht direkt bestimmt werden.
Der Vorteil ist:
- es kann einfach geprüft werden, ob jemand im Besitz des Passworts ist: indem man den Hashwert des Passworts mit dem abgespeicherten Hashwert vergleicht
- wenn ein Angreifer den abgespeicherten Hashwert in die Hände bekommt, kann daraus nicht das Passwort erraten werden

Hashfunktionen spielen auch bei der digitalen Signatur oder Proof-of-Work (Cryptocoins) eine große Rolle.

Die einzige Möglichkeit das Passwort zu einem Hashwert zu bestimmen ist per Brute Force alle möglichen Passwörter zu generieren und deren Hashwert zu berechnen bis man den gewünschten Wert gefunden hat. Dies ist sehr aufwändig, da aktuelle Hashfunktionen einen extrem großen Wertebereich von mehr als 256 Bit abdecken.

Das Durchprobieren der Möglichkeiten ist trivial parallelisierbar - alle Passwörter können unabhängig berechnet werden. Großartige Synergieeffekte wären nicht zu erwarten, da die Hashfunktion explizit unterschiedliche Werte auch für ähnliche Inputs liefern soll.

Im Programm `password-crack.c` ist ein Grundgerüst für ein C-Programm mit 2 Parametern:
- hash "password": Gibt den Hashwert von password auf der Konsole in Hex-Schreibweise aus
- crack "hash": Berechnet ein Passwort zum gegebenen Hashwert (Platzhalter)
In beiden Fällen ist das Passwort auf ein fixes Format von 8 Ziffern begrenzt. 
Wir benutzen die Self-Contained SHA Hashlibrary von  https://github.com/amosnier/sha-2.

Ihre Aufgabe ist es die "crack" Funktion zu implementieren. Erst seriell und dann mit OpenMP optimiert.

Generieren Sie einen Hash von einem Passwort und lassen Sie eine andere Gruppe das Passwort berechnen.

Messen Sie dabei die erzielte Leistung in Hashes pro Sekunde. 

Das Programm kompilieren können Sie mit:
```
# Unix/GNU
$ make password-crack
# MinGW unter Windows
$ mingw32-make password-crack
# Microsoft Tools
$ nmake password-crack
```
