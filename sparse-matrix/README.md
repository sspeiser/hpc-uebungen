# Sparse Matrix: Repräsentation und Berechnung

Wir verwenden das Format [Compressed Sparse Row (CSR)](https://de.wikipedia.org/wiki/Compressed_Row_Storage).

Gegen sei die Matrix `matrix`:
```
[[1, 4, 0, 0, 1],
 [0, 0, 0, 0, 0],
 [0, 5, 6, 0, 0],
 [0, 0, 3, 0, 0]]
```

Stellen Sie die Matrix im CSR-Format dar.

Implementieren Sie die [Matrix-Vector-Multiplikation](https://de.wikipedia.org/wiki/Matrix-Vektor-Produkt) für eine Matrix im CSR-Format und einen "normalen" Vektor.

Um Ihren Code zu testen nutzen Sie den Vector `vector`:
```
[3, 4, 5, 6, 7]
```

In welchen Fällen lohnt sich CSR - wann ist eine vollständige Repräsentation der Matrix speichereffizienter?