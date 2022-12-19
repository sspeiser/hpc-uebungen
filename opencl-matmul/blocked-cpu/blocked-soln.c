#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#define N 1024*2
#define MATRIX_SIZE (N * N)
#define MATRIX_MEM (N * N * sizeof(float))
#define BLOCK_SIZE 16
#define N_BLOCKS (N / BLOCK_SIZE)

void matmul_naive(size_t n, float *a, float *b, float *c)
{
    #pragma omp parallel for
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            float tmp = 0.0;
            for (int k = 0; k < N; k++)
            {
                tmp += a[y * N + k] * b[k * N + x];
            }
            c[y * N + x] += tmp;
        }
    }
}

void matmul_blocks_naive(size_t n, float *a, float *b, float *c)
{
    #pragma omp parallel for
    for (int yblock = 0; yblock < N_BLOCKS; yblock++)
    {
        for (int ylocal = 0; ylocal < BLOCK_SIZE; ylocal++)
        {
            int y = yblock * BLOCK_SIZE + ylocal;
            for (int xblock = 0; xblock < N_BLOCKS; xblock++)
            {
                for (int xlocal = 0; xlocal < BLOCK_SIZE; xlocal++)
                {
                    int x = xblock * BLOCK_SIZE + xlocal;
                    for (int kblock = 0; kblock < N_BLOCKS; kblock++)
                    {
                        float tmp = 0.0;
                        for (int klocal = 0; klocal < BLOCK_SIZE; klocal++)
                        {
                            int k = kblock * BLOCK_SIZE + klocal;
                            tmp += a[y * N + k] * b[k * N + x];
                        }
                        c[y * N + x] += tmp;
                    }
                }
            }
        }
    }
}

void matmul_blocks(size_t n, float *a, float *b, float *c)
{
    #pragma omp parallel for
    for (int yblock = 0; yblock < N_BLOCKS; yblock++)
    {
        for (int xblock = 0; xblock < N_BLOCKS; xblock++)
        {
            for (int kblock = 0; kblock < N_BLOCKS; kblock++)
            {
                for (int ylocal = 0; ylocal < BLOCK_SIZE; ylocal++)
                {
                    int y = yblock * BLOCK_SIZE + ylocal;
                    for (int xlocal = 0; xlocal < BLOCK_SIZE; xlocal++)
                    {
                        int x = xblock * BLOCK_SIZE + xlocal;
                        float tmp = 0.0;
                        for (int klocal = 0; klocal < BLOCK_SIZE; klocal++)
                        {
                            int k = kblock * BLOCK_SIZE + klocal;
                            tmp += a[y * N + k] * b[k * N + x];
                        }
                        c[y * N + x] += tmp;
                    }
                }
            }
        }
    }
}

void measure(char *label, void (*berechnung)(size_t, float *, float *, float *))
{
    float *h_a = malloc(MATRIX_MEM);
    float *h_b = malloc(MATRIX_MEM);
    float *h_c = malloc(MATRIX_MEM);
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        h_a[i] = 2.0;
        h_b[i] = 4.0;
        h_c[i] = 0.0;
    }

    struct timeval start, end;
    double secs;
    gettimeofday(&start, 0);
    berechnung(N, h_a, h_b, h_c);
    gettimeofday(&end, 0);
    secs = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1e6;

    double gflops = (2.0 * N * N * N) / 1.0e9 / secs;

    // Check Results
    int errors = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        if (fabs(h_c[i] - N * 2.0 * 4.0) > 0.0001)
        {
            errors += 1;
        }
    }

    printf("%40s | %10.2f | %10.2f | %8d\n", label, secs, gflops, errors);
    free(h_a);
    free(h_b);
    free(h_c);
}

int main(int argc, char **argv)
{

    measure("naive", matmul_naive);
    measure("blocks_naive", matmul_blocks_naive);
    measure("blocks", matmul_blocks);

    return 0;
}
