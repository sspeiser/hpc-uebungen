#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <math.h>

#define N 16
#define P 16
// Von Hand als Wurzel(P) berechnet
#define BLOCKS_Y 4
#define BLOCKS_X 4
//
#define BLOCKSIZEY (N / BLOCKS_Y)
#define BLOCKSIZEX (N / BLOCKS_X)

void mem_to_thread(int thread[N][N])
{
    int block;
#pragma omp parallel for
    for (block = 0; block < P; block++)
    {
        int blocky = block / BLOCKS_X;
        int blockx = block % BLOCKS_X;
        int ystart = blocky * BLOCKSIZEY;
        int yend = ystart + BLOCKSIZEY;
        if (yend > N)
        {
            yend = N;
        }
        int xstart = blockx * BLOCKSIZEX;
        int xend = xstart + BLOCKSIZEX;
        if (xend > N)
        {
            xend = N;
        }
        for (int y = ystart; y < yend; y++)
        {
            for (int x = xstart; x < xend; x++)
            {
                thread[y][x] = omp_get_thread_num();
            }
        }
    }
}

void mem_to_thread_alt(int thread[N][N])
{
    int blocky;
    int blockx;

#pragma omp parallel for private(blockx) collapse(2)
    for (blocky = 0; blocky < BLOCKS_Y; blocky++)
    {
        for (blockx = 0; blockx < BLOCKS_X; blockx++)
        {
            int ystart = blocky * BLOCKSIZEY;
            int yend = ystart + BLOCKSIZEY;
            int xstart = blockx * BLOCKSIZEX;
            int xend = xstart + BLOCKSIZEX;
            for (int y = ystart; y < yend; y++)
            {
                for (int x = xstart; x < xend; x++)
                {
                    thread[y][x] = omp_get_thread_num();
                }
            }
        }
    }
}

void print_thread_nums(int thread[N][N])
{
    int x, y;
    printf("    |");
    for (x = 0; x < N; x++)
        printf("| %2i ", x);
    printf("|\n");
    printf("------");
    for (x = 0; x < N; x++)
        printf("-----");
    printf("-\n");
    for (y = 0; y < N; y++)
    {
        printf(" %2i |", y);
        for (x = 0; x < N; x++)
            printf("| %2i ", thread[y][x]);
        printf("|\n");
    }
}

int main()
{
    int thread[N][N];

    omp_set_num_threads(N);

    mem_to_thread_alt(thread);

    print_thread_nums(thread);
}
