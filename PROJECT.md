## Projektarbeit

### Ziel

Zeigen, dass Sie ...
- ... die Konzepte aus der Vorlesung High Performance Computing auf praktische Fragestellungen anwenden können
- ... die Beispiele aus den Übungen für weitergehende Problemstellungen anpassen, kombinieren und/oder erweitern können

Dazu sollen Sie ein Programm erstellen. Der erwartete Arbeitsumfang beträgt mindestens 25 Stunden pro Person.

### Umfang

Ihr Programm soll mehreren Technologien (z.B. OpenMP, MPI und GPU) umgesetzt werden. Dazu ein Vergleich der Performance und Herausforderungen beim Programmieren. Wie viele Technologien sinnvoll sind, hängt von der Schwierigkeit ab, z.B.
- Wie unterschiedlich sind die Technologien - eine konzeptuelle Leistung soll ersichtsichlich sein. Gegenbeispiel: Syntax-Konvertierung von OpenMP in Java-Fork-Join-Framework

Es kann auch ausreichend sein eine einzelne Anwendung in einer einzelnen Technologie umzusetzen, wenn hier eine entsprechende Leistung nachgewiesen werden kann, z.B. durch:
- Schwierige Übersetzung des Anwendungsproblems in entsprechendes paralleles Programmiermodell. Eine *optimale* Umsetztung der Graustufenkonvertierung mit SIMD-Intrinsics ist ggfs. schon ausreichend
- Darstellung und Bewertung sinnvoller Zwischenschritte, z.B. Baseline zu Cache Optimierung zu SIMD zu Multithreaded, ...
- Feintuning für eine Plattform, um tatsächliche hohe Performance zu erreichen statt nur ein Konzept umzusetzen. Z.B. dokumentierte Experimente, um die optimalen Blockgrößen bei Matrix-Multiplikation festzulegen, um die Cache-Level eines Prozessors auszunutzen
- Nutzung von und Vergleich mit nicht in der Vorlesung behandelten Technologie/Konzept.
- Sehr hohe Skalierung der Anwendung, die zusätzliche Herausforderungen mit sich bringt. Z.B. Verteilung auf mehrere Rechner notwendig


### Beispielanwendungen

- Game of Life
- Sharks and Fish (WATOR)
- Bildverarbeitung
- Matrix-Multiplikation
- Neuronale Netze
- Heat Equation oder Fire Simulation
- N-Body Simulation
- Billiardbälle mit Kollisionen
- Traffic Simulation
- Circuit Simulation
- Fraktale/Mandelbrot
- (Radix-)Sort verteilt


## Abgabe bis TBD EOD (23:59 Uhr)

- Projektbericht (Seitenangaben als Richtwerte): 
    - Motivation (0,5 Seiten)
    - Definition Problemstellung (0,5 - 1 Seite)
    - Lösungsansatz (1 Seite)
    - Implementierung inklusive Schwierigkeiten (1-2 Seiten)
    - Bewertung des Ansatzes und der performance-limitierenden Faktoren (1-2 Seiten) 
    - Erkentnisse, Fazit, nächste Schritte (0,5 - 1 Seite)
- Source Code (Link zu Repository)
- Optional: Tätigkeitsnachweis (Datum, Uhrzeit, Dauer, Tätigkeit) - hilft bei der Bewertung des Aufwands für die Problemstellung

### Demonstration (30 Minuten) 

- Vorstellung (20 Minuten)
- Fragen zu Vortrag und Verständnisfragen zu anderen Inhalten der Vorlesung (10 Minuten)
