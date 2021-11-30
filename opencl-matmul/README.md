# Übungen zu Matrizen-Multiplikation mit OpenCL

- Starten Sie mit der Variante "unoptimized" im entsprechenden Unterordner.
- Gehen Sie "blocked" Matrix Multiplikation im Ordner blocked-cpu durch (wird in Vorlesung erklärt)
- Übertragen Sie "blocked" von CPU auf die OpenCL - eine Vorlage und Lösung ist im Ordner "blocked". Wichtig zu beachten:
  - da keine Synchronisation auf dem Global Memory stattfindet, sollte ein Work Item die komplette Berechnung für ein Element im Outputarray übernehmen
   
