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

void addition_par() {
    #pragma omp parallel for
    for(uint64_t i=0;i<N;i++) 
    { 
        c[i] = a[i] + b[i];
    }
}

void veclength_seq() {
    for(uint64_t i=0;i<N;i++) 
    { 
        c[i] = sqrt(a[i] * a[i] + b[i] * b[i]);
    }
}

void veclength_par() {
    #pragma omp parallel for
    for(uint64_t i=0;i<N;i++) 
    { 
        c[i] = sqrt(a[i] * a[i] + b[i] * b[i]);
    }
}

void stencil_seq() {
    for(uint64_t i=0;i<N-8;i++) 
    {   
        c[i] = 0.9 * a[i] + 0.8 * a[i+1] + 0.7 * a[i+2] + 0.6 * a[i+3] + 0.5 * a[i+4] + 0.4 * a[i+5] + 0.3 * a[i+6] + 0.2 * a[i+7];
    }
}

void stencil_par() {
    #pragma omp parallel for
    for(uint64_t i=0;i<N-8;i++) 
    {   
        c[i] = 0.9 * a[i] + 0.8 * a[i+1] + 0.7 * a[i+2] + 0.6 * a[i+3] + 0.5 * a[i+4] + 0.4 * a[i+5] + 0.3 * a[i+6] + 0.2 * a[i+7];
    }
}

void mixed_calc_seq() {
    for(uint64_t i=0;i<N;i++) 
    {   
        c[i] = 0.75 * a[i] + 0.25 * b[i];
        a[i] = 0.4 * a[i] + 0.2 * b[i];
        b[i] = 1.2 * b[i];
    }
}

void mixed_calc_par() {
    #pragma omp parallel for
    for(uint64_t i=0;i<N;i++) 
    {   
        c[i] = 0.75 * a[i] + 0.25 * b[i];
        a[i] = 0.4 * a[i] + 0.2 * b[i];
        b[i] = 1.2 * b[i];
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
    measure("veclength_seq", &veclength_seq, N, 4, 3 * sizeof(float));
    measure("veclength_par", &veclength_par, N, 4, 3 * sizeof(float));

    printf("##############\n");
    measure("addition_seq", &addition_seq, N, 1, 3 * sizeof(float));
    measure("addition_par", &addition_par, N, 1, 3 * sizeof(float));

    printf("###############\n");
    measure("stencil_seq", &stencil_seq, N - 8, 8+7, 9 * sizeof(float));
    measure("stencil_par", &stencil_par, N - 8, 8+7, 9 * sizeof(float));

    printf("###############\n");
    measure("mixed_calc_seq", &mixed_calc_seq, N, 7, 3 * sizeof(float)); 
    measure("mixed_calc_par", &mixed_calc_par, N, 7, 3 * sizeof(float)); 
}