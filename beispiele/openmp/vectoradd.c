#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8192 * 8192 * 8

int main()
{
    float *a = malloc(N * sizeof(float));
    float *b = malloc(N * sizeof(float));
    int i;
    for(i=0;i<N;i++) {
        a[i] = 1.0;
        b[i] = 2.0;
    }
    

    // Sequenziell
    double wtime = omp_get_wtime();
    for(i=0;i<N;i++) { a[i] += b[i]; }
    wtime = omp_get_wtime() - wtime;
    printf("Sequenziell: %.3f Sekunden\n", wtime);

    // Manuell Parallel
    wtime = omp_get_wtime();
    #pragma omp parallel
    {
        int id, i, nthreads;
        id = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        for(i=id; i<N; i += nthreads) {
            a[i] += b[i];
        }
    }
    wtime = omp_get_wtime() - wtime;
    printf("Manuell Parallel: %.3f Sekunden\n", wtime);

    // Parallel For-Loop
    wtime = omp_get_wtime();
    #pragma omp parallel
    #pragma omp for
    for(i=0;i<N;i++) { a[i] += b[i]; }
    wtime = omp_get_wtime() - wtime;
    printf("Parallel for: %.3f Sekunden\n", wtime);

 // Parallel For-Loop
    wtime = omp_get_wtime();
    #pragma omp parallel
    #pragma omp for simd 
    for(i=0;i<N;i++) { a[i] += 4.0 * 
    b[i]; }
    wtime = omp_get_wtime() - wtime;
    printf("Parallel for: %.3f Sekunden\n", wtime);   
}