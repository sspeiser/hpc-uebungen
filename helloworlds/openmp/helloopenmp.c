#include <omp.h>
#include <stdio.h>

int main()
{
    printf("Hello\n");
    #pragma omp parallel
    {
        printf("World. Thread = %d\n", omp_get_thread_num());
    }
    printf("DONE");
}