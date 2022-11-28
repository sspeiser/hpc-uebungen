#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

#define N 16

void mem_to_thread(int thread[N][N])
{
    int y;
#pragma omp parallel for
    for (y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            thread[y][x] = omp_get_thread_num();
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
