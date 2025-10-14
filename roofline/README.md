# Übung: Roofline-Profil

<div class="alert alert-info"><b>INFO</b><br />
Roofline Modell:<br />
<ul>
        <li>a href="https://blogs.fau.de/hager/files/2020/10/05_roofline.pdf">Kurzübersicht auf Folien FAU Erlangen-Nürnberg</a></li>
<li>Erhöhen der Compute-Intensitiviy von Matrix-Multiplikation: Lecture 3, Folien 3 - 14, <a href="https://sites.google.com/lbl.gov/cs267-spr2021/home">CS 267 der UC Berkeley</a></li>
<li>Detailliert zu Roofline Modell: Lecture 3, Folien 54 - 99, <a href="https://sites.google.com/lbl.gov/cs267-spr2021/home">CS 267 der UC Berkeley</a></li></ul>
</div>

## Roofline im PC-Raum mit Windows

Im PC-Raum mit Windows: Intel Advisor:
- https://software.intel.com/content/www/us/en/develop/documentation/advisor-tutorial-roofline/top.html
- https://software.intel.com/content/www/us/en/develop/articles/oneapi-standalone-components.html#advisor
- https://software.intel.com/content/www/us/en/develop/documentation/advisor-user-guide/top.html

## Roofline unter Unix

Erstellen Sie ein Roofline-Profil für Ihre Maschine:
```
$ git clone https://bitbucket.org/berkeleylab/cs-roofline-toolkit.git
$ cd cd cs-roofline-toolkit/Empirical_Roofline_Tool-1.1.0
$ # Edit Config/local based e.g. on Config/config.maeve...
$ ./ert Config/local
```
Das Ergebnis ist in der Datei `Results.local/Run.001/roofline.ps`.


## Alternative Übung
Laden des STREAM Benchmark um die Speicherleistung zu messen:
https://www.cs.virginia.edu/stream/

Die theoretischen GFLOPS/s können aus der Prozessorspezifikation grob ausgelesen werden.
