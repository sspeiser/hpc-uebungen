# Übung: Nutzung Caches

Im Programm `matrixadd.c` wird eine Matriz `B` zu einer anderen Matriz `A` addiert. Die Matrizen sind bewusst so groß gehalten, dass sie nicht vollständig in den Cache passen.

Kompilieren Sie das Programm und führen es aus:
```
$ gcc matrixadd.c
...
$ ./a.out
# oder unter Windows ggfs.:
$ ./a.exe
...
```
Das Programm gibt die erreichten MFLOP/s aus - nur bezogen auf die Additionen.
Entspricht das Ergebnis Ihrer Erwartung, wenn Sie an Taktfrequenz und FLOP/Cycle der genutzten CPU denken?

Wie können Sie die markierte Schleife einfach optimieren? Überlegen Sie wie/in welcher Reihenfolge die Matrizen im Speicher abgelegt werden. Wie ist das Zugriffsmuster und wie kann der Cache unterstützen.

Welche Performance-Steigerung ist mit der einfachen Optimierung möglich? Passen nun die FLOP/s zur Erwartung? Wenn nicht, warum nicht?

Gibt es neben den FLOP für die Addition noch weitere Operationen, die Sie optimieren können?

Übersetzen Sie dann noch Ihr Programm mit starker Optimierung und prüfen wie viele MFLOP/s erreicht werden:
```
$ gcc -O3 matrixadd.c
```
