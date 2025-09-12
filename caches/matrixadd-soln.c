#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <sys/timeb.h>
#include <stdint.h>

uint64_t system_current_time_millis()
{
#if defined(_WIN32) || defined(_WIN64)
    struct _timeb timebuffer;
    _ftime(&timebuffer);
    return (uint64_t)(((timebuffer.time * 1000) + timebuffer.millitm));
#else
    struct timeb timebuffer;
    ftime(&timebuffer);
    return (uint64_t)(((timebuffer.time * 1000) + timebuffer.millitm));
#endif
}

#define X 8192
#define Y 8192

void **malloc2d(int x, int y, size_t size)
{
    void **array = malloc(x * sizeof(void *) + x * y * size);
    for (int i = 0; i < x; i++)
    {
        size_t offset = x * sizeof(void *) + i * y * size;
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

    // Zeitmessen Start
    uint64_t start = system_current_time_millis();

    // TODO: Optimize this loop -> DONE: Schleifenreihenfolge geändert
    
    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            a[i][j] += b[i][j];
        }
    }

    // Alternative: Unrolling ... Mit und ohne -O3
    // for (i = 0; i < X / 8; i+=8)
    // {
    //     for (j = 0; j < Y; j++)
    //     {
    //         a[i][j] += b[i][j];
    //         a[i + 1][j] += b[i + 1][j];
    //         a[i + 2][j] += b[i + 2][j];
    //         a[i + 3][j] += b[i + 3][j];
    //         a[i + 4][j] += b[i + 4][j];
    //         a[i + 5][j] += b[i + 5][j];
    //         a[i + 6][j] += b[i + 6][j];
    //         a[i + 7][j] += b[i + 7][j];

    //     }
    // }

    // Unrolling 2D ... Mit und ohne -O3:
    // for (i = 0; i < X / 4; i+=8)
    // {
    //     for (j = 0; j < Y / 4; j += 4)
    //     {
    //         a[i + 0][j + 0] += b[i + 0][j + 0];
    //         a[i + 1][j + 0] += b[i + 1][j + 0];
    //         a[i + 2][j + 0] += b[i + 2][j + 0];
    //         a[i + 3][j + 0] += b[i + 3][j + 0];
    //         a[i + 0][j + 1] += b[i + 0][j + 1];
    //         a[i + 1][j + 1] += b[i + 1][j + 1];
    //         a[i + 2][j + 1] += b[i + 2][j + 1];
    //         a[i + 3][j + 1] += b[i + 3][j + 1];
    //         a[i + 0][j + 2] += b[i + 0][j + 2];
    //         a[i + 1][j + 2] += b[i + 1][j + 2];
    //         a[i + 2][j + 2] += b[i + 2][j + 2];
    //         a[i + 3][j + 2] += b[i + 3][j + 2];
    //         a[i + 0][j + 3] += b[i + 0][j + 3];
    //         a[i + 1][j + 3] += b[i + 1][j + 3];
    //         a[i + 2][j + 3] += b[i + 2][j + 3];
    //         a[i + 3][j + 3] += b[i + 3][j + 3];
    //     }
    // }

    uint64_t end = system_current_time_millis();
    double secs = (end - start) / 1.0e3;
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