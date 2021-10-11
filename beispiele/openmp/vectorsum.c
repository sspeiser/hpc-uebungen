#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8192 * 8192

int main()
{
    float *a = malloc(N * sizeof(float));
    int i;
    for(i=0;i<N;i++) {
        a[i] = 1.0;
    }
    

    // Sequenziell
    double wtime = omp_get_wtime();
    double sum = 0.0;
    for(i=0;i<N;i++) { sum += a[i]; }
    wtime = omp_get_wtime() - wtime;
    printf("Sequenziell: %.3f Sekunden\n", wtime);
    printf("Ergebnis: %f ... sollte %f sein\n", sum, N * 1.0);

    // Parallel ohne Synch -> falsches Ergebnis
    wtime = omp_get_wtime();
    sum = 0.0;
    #pragma omp parallel for
    for(i=0;i<N;i++) {
        sum += a[i];
    }
    wtime = omp_get_wtime() - wtime;
    printf("Parallel ohne Synchronisation: %.3f Sekunden\n", wtime);
    printf("Ergebnis: %f ... sollte %f sein\n", sum, N * 1.0);

    // Parallel mit Synch -> langsam
    wtime = omp_get_wtime();
    sum = 0.0;
    #pragma omp parallel for
    for(i=0;i<N;i++) {
        #pragma omp critical
        sum += a[i];
    }
    wtime = omp_get_wtime() - wtime;
    printf("Parallel mit Synchronisation: %.3f Sekunden\n", wtime);
    printf("Ergebnis: %f ... sollte %f sein\n", sum, N * 1.0);


    // Parallel mit reduction
    wtime = omp_get_wtime();
    sum = 0.0;
    #pragma omp parallel for reduction (+:sum)
    for(i=0;i<N;i++) {
        sum += a[i];
    }
    wtime = omp_get_wtime() - wtime;
    printf("Parallel mit Reduction: %.3f Sekunden\n", wtime);
    printf("Ergebnis: %f ... sollte %f sein\n", sum, N * 1.0);
}