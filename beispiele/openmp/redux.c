#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1024 * 1024 * 1024

int main()
{
    float *a = malloc(N * sizeof(float));
    int i;
    for(i=0;i<N;i++) {
        a[i] = 1/1024.0/1024.0;
    }
    

    // Parallel
    double wtime = omp_get_wtime();
    double sum = 0.0;
    // #pragma omp parallel for reduction (+:sum)
    // for(i=0;i<N;i++) {
    //     sum += a[i];
    // }
    int nthreads = omp_get_max_threads();
    printf("nthreads %d\n", nthreads);
    double *sums = malloc(nthreads * sizeof(double));
    if(sums == NULL) {
        printf("Error allocating sums\n");
    }
    #pragma omp parallel for
    for(i=0;i<N;i++) { 
        printf("Thread id: %d\n", omp_get_thread_num());
        sums[omp_get_thread_num()] += a[i];
    }
    for(i=0; i < nthreads;i++) {
        sum += sums[i];
    }
    wtime = omp_get_wtime() - wtime;
    printf("Parallel: %8.2f\t%.3f Sekunden\n", sum, wtime);
}