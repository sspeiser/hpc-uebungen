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


#define Y 8192
#define X 8192

void **malloc2d(int rows, int cols, size_t size)
{
    size_t row_size = cols * size;
    void **array = malloc(rows * sizeof(void *) + rows * row_size);
    for (int i = 0; i < rows; i++)
    {
        size_t offset = rows * sizeof(void *) + i * row_size;
        array[i] = (void *)((unsigned char *)array + offset);
    }
    return array;
}

int main()
{
    float **a = (float **)malloc2d(Y, X, sizeof(float));
    float **b = (float **)malloc2d(Y, X, sizeof(float));
    
    int x, y;

    printf("sizeof(float) = %lu\n", sizeof(float));
    printf("Größe der Matrix: %i x %i = %i Elemente\n", X, Y, X * Y);
    printf("Größe einer Matrix: %lu kBytes\n", sizeof(float) * X * Y / 1024);
    printf("Größe einer Reihe: %lu kBytes\n", sizeof(float) * X / 1024);
    printf("Größe einer Spalte: %lu kBytes\n", sizeof(float) * Y / 1024);

    for (x = 0; x < X; x++)
    {
        for (y = 0; y < Y; y++)
        {
            a[y][x] = 1.0;
            b[y][x] = 2.0;
        }
    }

     // Zeitmessen Start
    uint64_t start = system_current_time_millis();

    // TODO: Optimize this loop
    for (y = 0; y < Y; y++)
    {
        for (x = 0; x < X; x++)
        {
            // a[y][x] += b[y][x];
            a[y][x] = a[y][x] + b[y][x];
        }
    }

    /****
     * 
     * I = Flops / Byte
     * I = 1 FLOP / 8 Byte
     * 
     * P = 2.6 GFLOP/s
     * b = 20 GB/s
     * 
     * Wie oft Schleife pro Sekunde:
     * Rechenleistung: 2.6 Milliarden mal pro Sekunde
     * Bandbreite: 2.5 Milliarden mal pro Sekunde
     * 
     * 
     */

    // a + b
    //


    uint64_t end = system_current_time_millis();
    double secs = (end - start) / 1.0e3;

    double flop = X * Y;
    // Eingelese Bytes: Beide Arrays (X*Y) * 2
    double byte = X * Y * 2 * sizeof(float);

    printf("%.2f MFLOP\n%.2f sec\n", flop / 1000000.0, secs);
    printf("%.2f MFLOPs\n", flop / secs / 1000000.0);
    printf("%.2f MByte\n %.2f MByte/s\n", byte / 1000000.0, byte / 1000000.0 / secs);

    return 0;
}
