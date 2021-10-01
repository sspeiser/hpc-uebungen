#include <omp.h>
#include <stdio.h>

int main()
{
    #pragma omp parallel
    {
        printf("Hello World. Thread = %d\n", omp_get_thread_num());
    }
}