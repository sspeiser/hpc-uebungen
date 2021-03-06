#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N (uint64_t) 8192l * (uint64_t) 8192l * (uint64_t) 8l

float *a;
float *b;
float *c;

void measure(char* label, void (*berechnung)(void), uint64_t n, uint32_t flop_pro_berechnung, uint32_t byte_pro_berechnung) {
    double mflop = n * flop_pro_berechnung / 1000000.0;
    double gb_mem = byte_pro_berechnung * n / 1000.0 / 1000.0 / 1000.0;
    double wtime = omp_get_wtime();
    (*berechnung)();
    wtime = omp_get_wtime() - wtime;
    double mflops = mflop / wtime;
    printf("%s:\n\t %.3f Sekunden\n", label, wtime);
    printf("\t%.2f MFLOP/s\n", mflops);
    printf("\t%.2f GByte/s\n", gb_mem / wtime);
}

void addition_seq() {
    for(uint64_t i=0;i<N;i++) 
    { 
        c[i] = a[i] + b[i];
    }
}
int main()
{
    a = malloc(N * sizeof(float));
    b = malloc(N * sizeof(float));
    c = malloc(N * sizeof(float));
    uint64_t i;
    for(i=0;i<N;i++) {
        a[i] = 1.0;
        b[i] = 2.0;
    }

    printf("##############\n");
    measure("addition_seq", &addition_seq, N, 1, 3 * sizeof(float));
}