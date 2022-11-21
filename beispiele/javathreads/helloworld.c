// Include-Datei für OpenMP:
#include <omp.h>
#include <stdio.h>

int main()
{
    // Ganz normal sequenzieller Code:
    printf("Hello\n");
    // Nun kommt ein paralleler Abschnitt:
    int i = 0;
    #pragma omp parallel
    {
        // int j = i;
        // printf("World from %i\n", omp_get_thread_num());
        // i = j + 1;
        i += 1;
    }
    // Paralleler Abschnitt zu Ende, nun wieder sequenziell:
    printf("Done\n");
    printf("Total: %i\n", i);
}