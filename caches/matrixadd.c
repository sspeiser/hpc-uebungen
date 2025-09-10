#include <stdio.h>
#include <stdlib.h>

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
    float **a = (float **)malloc2d(X, Y, sizeof(float));
    float **b = (float **)malloc2d(X, Y, sizeof(float));
    
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

    // TODO: Optimize this loop
    for (j = 0; j < Y; j++)
    {
        for (i = 0; i < X; i++)
        {
            a[i][j] += b[i][j];
        }
    }

    uint64_t end = system_current_time_millis();
    double secs = (end - start) / 1.0e3;

    double flop = X * Y;

    printf("%.2f MFLOP\n%.2f sec\n", flop / 1000000.0, secs);
    printf("%.2f MFLOPs\n", flop / secs / 1000000.0);

    return 0;
}