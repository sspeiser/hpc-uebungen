# Collective Communication mit MPI

## Vorbereitung im PC-Raum
1. Download des MSMPI-SDK (die 2. Datei `msmpisdk.msi`) und Installation
2. Erst dann Visual Studio öffnen/Konsole in der CMake ausgeführt wird
3. Starten eines Command Prompts als Admin und Eingabe: `net start msmpilaunchsvc`

Ausführen des Programms über Visual Studio funktioniert im Normalfall nicht. Starten Sie stattdessen einen Developer Command Prompt aus dem Startmenü Visual Studio. Wechseln Sie dort in das Verzeichnis Ihres Programms - im Normalfall etwas wie:
```
p:
cd  hpc-uebungen\mpi-collective-comm\out\build\x64-Debug
mpiexec mpi-collective-comm.exe
```

Im PC-Raum können wir probieren mit `mpiexec -hosts 8 hostA 8 hostB` das Programm verteilt laufen zu lassen. Ggfs müssen auf den einzelnen PCs `smpd –d` gestartet werden und die Firewall konfiguriert.

## Aufgabe


In der Datei `mpi-coll-comm.c` ist ein Grundgerüst mit einem MPI-Programm wo jeder Prozess ein zufälliges `n` bestimmt mit den Elementen, die der Prozess verarbeiten kann. In einem Praxis-Szenario könnte das eher eine vorbestimmte Größe sein, die die Leistungsfähigkeit des Rechenknotens abbildet. Nehmen wir als Beispiel 4 Ranks mit den Größen `[2, 1, 4, 2]`. Gehen Sie durch die folgenden Schritte:
1. Auf Rank 0 wird ein Array `global_numbers` erzeugt mit der Größe `total_n`. Diese Variable ist bisher nicht gesetzt - bestimmten Sie die Gesamtzahl mit der `MPI_Reduce` Funktion. Im Beispiel ist `total_n = 9`
2. Bestimmen Sie auf jedem Rank, an welcher Stelle in `global_numbers` die Daten für diesen Rank beginnen und speichern Sie das Ergebnis in `offset`. Sie können hierfür die `MPI_Exscan`-Funktion verwenden. Im Beispiel für Rank 0, offset = 0; für Rank 1, offset = 2; für Rank 2, offset = 3; für Rank 3, offset = 7
3. Wir wollen das Array `global_numbers` an die verschiedenen Ranks verteilen, dazu gibt es die Funktion `MPI_Scatterv`, da die einzelnen Abschnitte aber unterschiedliche groß sind brauchen wir Arrays von offsets und sizes, die uns sagen welcher Teilabschnitt an welchen Rank geht. Sammeln Sie diese Arrays per `MPI_Gather` von allen Ranks ein
4. Nun senden Sie die Teilabschnitte mit `MPI_Scatterv` an die Ranks. Die Ranks addieren dann ihre Rank-Nummer auf jede Zahl in ihrem Teilarray (`local_numbers`).
5. Sammeln Sie nun die ganzen Teilarrays mit `MPI_Gatherv` wieder ein und speichern die aktualisierten Werte in `global_numbers`

Anschliessend wird `global_numbers` auf dem Bildschirm ausgegeben.

