#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

#define N 16
#define BLOCKS 16

void mem_to_thread(int thread[N][N])
{
    int b;
#pragma omp parallel for
    for (b = 0; b < BLOCKS; b++) {
        int blockx = b % 4;
        int blocky = b / 4;
        int startx = blockx * 4;
        int starty = blocky * 4;

        for (int y = starty; y < starty + 4; y++)
        {
            for (int x = startx; x < startx + 4; x++)
            {
                thread[y][x] = omp_get_thread_num();
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
    int x, y;
    int thread[N][N];

    omp_set_num_threads(N);

    mem_to_thread(thread);

    print_thread_nums(thread);
}
