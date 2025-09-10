# Amdahl's Law

In der Datei `amdahl-soln.ipynb` befindet sich ein Jupyter Notebook, das die folgenden Übungen löst. Bitte versuchen die Berechnung zuerst selbst - neben Python gibt es weitere Möglichkeiten das zu tun:
- Von Hand: auf Papier und ggfs. mit einem Taschenrechner
- Tabellenkalkulation (LibreOffice / Excel)
- In einer beliebigen Programmiersprache

<div class="alert alert-warning">
<b>ÜBUNG: </b> Amdahl's Gesetz<br />
<p>Erstellen Sie eine Tabelle/ein Chart, das den maximalen Speedup für folgende Kombinationen zeigt:
<ul>
<li>Prozessoren: 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096</li>
<li>Paralleler Anteil: 50%, 75%, 90%, 95%</li>
</ul>

Wie viel Zeit wird eingespart bei einem Programm mit parallelem Anteil 80%, das auf 1 Prozessor 24 Stunden läuft beim Umstieg von 1 auf 16 Prozessoren? Wie viel beim Umstieg von 16 auf 64 Prozessoren?
</div>

<div class="alert alert-warning">
<b>ÜBUNG: </b> Amdahl's Gesetz mit heterogenen Prozessoren<br />
<p>Betrachten wir einen Prozessor mit einem Kern für sequenzielle Aufgaben und 4 Kernen für parallele Aufgaben. Aufgrund von technologischen Entwicklungen können Sie bei der nächsten Prozessorgeneration entweder den Kern für sequenzielle Aufgaben doppelt so schnell machen (A) oder die Anzahl der Kerne für parallele Aufgaben verdopplen (B). Wofür entscheiden Sie sich (d.h. wie hoch ist der jeweilige Speedup), wenn der typische Workload einen parallelen Anteil von 25%, 50%, 75%, 90% oder 95% hat?
</div>