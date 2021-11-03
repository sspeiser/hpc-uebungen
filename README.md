# High-Performance Computing (HPC): Skript und Übungen

In diesem Repository befinden sich die Übungen für die Vorlesung High-Performance Computing (HPC) an der [HFT Stuttgart](https://www.hft-stuttgart.de) von [Sebastian Speiser](https://www.hft-stuttgart.de/p/sebastian-speiser). Die Vorlesung wird von einem Skript begleitet, das die Übungen verlinkt: [Skript](https://sspeiser.github.io/hpc-doc/intro.html).

## Ablauf der Vorlesung (WS2021/2022) - WORK IN PROGRESS

<table>
<tr>
    <th>Woche</th><th>Einheit</th><th>Inhalt</th><th>Hausaufgabe</th>
</tr>
<tr>
    <td>1</td><td>1</td>
    <td><b>Einführung</b>
        <ul><li>Formales (Moodle, PowerPoint)</li>
            <li><a href="https://sspeiser.github.io/hpc-doc/intro.html">Motivation/Einleitung (Skript)</a></li>
            <li><a href="https://sspeiser.github.io/hpc-doc/computing.html">Wofür braucht man "Computing"? (Skript)</a></li>
            <li>Ablaufplan Semester(PowerPoint/Moodle)</li>
            <li>Einrichtung Programmierumgebung (C, Jupyter, Python, Git)</li>
            <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/graustufen">Übung/Warmup: Konvertierung eines Bilds in Graustufen</a></li>
            </ul></td>
    <td><ul><li>2er Teams bilden. Bevorzugt mit/ohne C/Python-Erfahrung</li>
            <li>C lernen/auffrischen, z.B. <a href="https://www.youtube.com/watch?v=3lQEunpmtRA">C Programming (25 Minuten)</a>, <a href="https://youtu.be/mw1qsMieK5c">C Pointer (10 Minuten)</a> und <a href="https://youtu.be/wadj1UH2gVQ">Dynamic Memory in C (10 Minuten)</a></li></ul></td>
    </tr>
    <tr>
    <td>2</td><td>2</td>
    <td><b>High-Performance: Ansätze und Grenzen - I</b><br />
        <a href="https://sspeiser.github.io/hpc-doc/high-performance.html">Skript "High-Performance: Ansatz 1: Schnellere Prozessoren"</a> mit Übungen:
        <ul><li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/caches">Caches</a></li>
            <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/simd">SIMD</a></li>
            <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/roofline">Roofline-Modell</a></li></ul></td>
            <td>Python lernen/auffrischen, z.B. Skript "Data Analytics" Kapitel <a href="https://speiser.hft-pages.io/vl-data-analytics/python-intro/python-intro-live.html">"Python Grundlagen"</a> und <a href="https://speiser.hft-pages.io/vl-data-analytics/data-understanding/10-numpy.html">"NumPy"</a>. <a href="https://www.youtube.com/watch?v=HW29067qVWk">YouTube: Jupyter Notebook</a> </td>
    </tr>
    <tr>
        <td>3</td><td>3</td>
        <td><b>High-Performance: Ansätze und Grenzen - II</b><br />
        <a href="https://sspeiser.github.io/hpc-doc/high-performance.html">Skript "High-Performance: Ansatz 2, Ansatz 3, Ganz anders"</a> mit Übungen:
        <ul><li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/amdahl">Amdahl's Law</a></li></ul></td>
        <td>
            -
        </td>
    </tr>$$
    <tr>
        <td>3/4</td><td>4</td>
        <td><b>Shared Memory mit OpenMP</b><br />
        <a href="https://sspeiser.github.io/hpc-doc/sharedmemory.html">Skript "Shared Memory mit OpenMP"</a> mit Übungen:
        <ul><li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/password-crack-openmp">Parallele Programmierung mit OpenMP: Passwort cracken</a></li>
        <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/cpu-vs-mem">Memory vs. CPU als Bottleneck mit OpenMP</a></li></ul></td>
        <td>
            -
        </td>
    </tr>
    <tr>
        <td>5</td><td>5</td>
        <td><b>Daten</b><br />
        <a href="https://sspeiser.github.io/hpc-doc/data.html">Skript "Daten"</a> mit Übungen:
        <ul>
        <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/sparse-matrix">Sparse Matrix Repräsentation und Berechnungen</a></li>
        <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/numerik-floats">Genauigkeit Floats</a></li></ul></td>
        <td>
            -
        </td>
    </tr>
    <tr>
        <td>5/6</td><td>6</td>
        <td><b>Parallele Algorithmen</b><br />
        <a href="https://sspeiser.github.io/hpc-doc/algorithmen.html">Skript "Parallele Algorithmen"</a> mit Übungen:
        <ul><li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/openmp-tiling">Arbeitsaufteilung</a></li></ul></td>
        <td>
            -
        </td>
    </tr>
    <tr>
        <td>7</td><td>7</td>
        <td><b>Distributed Memory mit MPI</b><br />
        <a href="https://sspeiser.github.io/hpc-doc/distributedmemory.html">Skript "Parallele Algorithmen"</a> mit Übungen:
        <ul>
        <!-- <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/openmp-tiling">Arbeitsaufteilung</a></li> -->
        <td>TBD</td>
        </ul></td>
        <td>
            -
        </td>
    </tr>
    <tr>
        <td>8/9</td><td>8</td>
        <td><b>GPU</b><br />
        <!-- <a href="https://sspeiser.github.io/hpc-doc/distributedmemory.html">Skript "Parallele Algorithmen"</a> mit Übungen: -->
        <ul>
        <!-- <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/openmp-tiling">Arbeitsaufteilung</a></li> -->
        <td>TBD</td>
        </ul></td>
        <td>
            -
        </td>
    </tr>
    <tr>
        <td>10</td><td>9</td>
        <td><b>Dataparallelismus mit NumPy und Tensorflow</b><br />
        <!-- <a href="https://sspeiser.github.io/hpc-doc/distributedmemory.html">Skript "Parallele Algorithmen"</a> mit Übungen: -->
        <ul>
        <!-- <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/openmp-tiling">Arbeitsaufteilung</a></li> -->
        <td>TBD</td>
        </ul></td>
        <td>
            -
        </td>
    </tr>
    <tr>
        <td>11</td><td></td>
        <td><b>Puffer / Projektwerkstatt</b><br />
        <!-- <a href="https://sspeiser.github.io/hpc-doc/distributedmemory.html">Skript "Parallele Algorithmen"</a> mit Übungen: -->
        <ul>
        <!-- <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/openmp-tiling">Arbeitsaufteilung</a></li> -->
        <td>TBD</td>
        </ul></td>
        <td>
            -
        </td>
    </tr>
    <tr>
        <td>12</td><td></td>
        <td><b>Projektpräsentationen</b><br />
        <!-- <a href="https://sspeiser.github.io/hpc-doc/distributedmemory.html">Skript "Parallele Algorithmen"</a> mit Übungen: -->
        <ul>
        <!-- <li><a href="https://github.com/sspeiser/hpc-uebungen/tree/main/openmp-tiling">Arbeitsaufteilung</a></li> -->
        <td>TBD</td>
        </ul></td>
        <td>
            -
        </td>
    </tr>
    <!--
        Vorstellung Projektideen, nicht im Skript?
    -->
    <!--
        Quantencomputing
    -->
    <tr>
        <td>13</td><td>-</td>
        <td>Projektpräsentationen</td>
        <td>-</td>
    </tr>
</table>

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


## Abgabe bis 13.01.2021

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