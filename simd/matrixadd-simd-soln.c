#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <immintrin.h>
#include <math.h>

#define X 8192
#define Y 8192

void **malloc2d(int x, int y, size_t size)
{
    void **array = malloc(x * sizeof(void *) + x * y * size);
    for (int i = 0; i < x; i++)
    {
        int offset = x * sizeof(void *) + i * y * size;
        array[i] = (void *)((unsigned char *)array + offset);
    }
    return array;
}

int main()
{
    float ** restrict a = (float **)malloc2d(X, Y, sizeof(float));
    float ** restrict b = (float **)malloc2d(X, Y, sizeof(float));
    
    int i, j;

    printf("sizeof(float) = %lu\n", sizeof(float));
    printf("Größe der Matrix: %i x %i = %i Elemente\n", X, Y, X * Y);
    printf("Größe einer Matrix: %lu kBytes\n", sizeof(float) * X * Y / 1024);
    printf("Größe einer Reihe: %lu kBytes\n", sizeof(float) * X / 1024);

    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            a[i][j] = 1.0;
            b[i][j] = 2.0;
        }
    }

    // Measure time
    struct timeval start, end;
    gettimeofday(&start, 0);

    // TODO: SIMD Optimize Add
    int size = X * Y;
    float *a1d = a[0];
    float *b1d = b[0];
    
    // Ohne SIMD: 1 Float Point pro Schritt
    for(int i=0;i<size;i+=1) {
        *a1d = *a1d + *b1d;
        a1d += 1;
        b1d += 1;
    }

    // SSE: 4 x 32 Bit Floating Points pro Schritt
    // for(int i=0;i<size;i+=4) {
    //     __m128 avec = _mm_load_ps(a1d);
    //     __m128 bvec = _mm_load_ps(b1d);
    //     avec = _mm_add_ps (avec, bvec);
    //     _mm_store_ps(a1d, avec);
    //     a1d += 4;
    //     b1d += 4;
    // }

    // AVX: 8 x 32 Bit Floating Points pro Schritt
    // for(int i=0;i<size;i+=8) {
    //     __m256 avec = _mm256_load_ps(a1d);
    //     __m256 bvec = _mm256_load_ps(b1d);
    //     avec = _mm256_add_ps (avec, bvec);
    //     _mm256_store_ps(a1d, avec);
    //     a1d += 8;
    //     b1d += 8;
    // }

    gettimeofday(&end, 0);

    long sec = end.tv_sec - start.tv_sec;
    long usec = end.tv_usec - start.tv_usec;
    double secs = (sec + usec / 1000000.0);
    double flop = X * Y;

    printf("%.2f MFLOP\n%.2f sec\n", flop / 1000000.0, secs);
    printf("%.2f MFLOPs\n", flop / secs / 1000000.0);

    for(i=0;i<X;i++) {
        for(j=0;j<X;j++) {
            if(fabs(a[i][j] - 3.0) * 1000.0 > 0.1) {
                printf("ERROR\n");
                exit(-1);
            }
        }
    }

    return 0;
}