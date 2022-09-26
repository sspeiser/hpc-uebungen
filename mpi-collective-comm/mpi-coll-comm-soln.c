#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MIN 1
#define N_MAX 5

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Jeder Knoten bestimmt die Anzahl der zu verarbeitenden Elemente
    // Zwischen N_MIN und N_MAX
    srand(time(0) + rank);
    int n = N_MIN + rand() % (N_MAX - N_MIN + 1);

    printf("[%02d] n = %d\n", rank, n);

    // Die Gesamtzahl wird bestimmt und auf rank 0 ein entsprechend
    // grosses Array erzeugt
    int total_n;
    MPI_Reduce(&n, &total_n, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double *global_numbers;
    if (rank == 0)
    {
        global_numbers = malloc(total_n * sizeof(double));
        for (int i = 0; i < total_n; i++)
        {
            global_numbers[i] = (double)i;
        }
        printf("[00]: Gesamtzahl der Elemente = %d\n", total_n);
    }

    // Nun bestimmen wir die Offsets im Gesamtarray, wo für jeden Rank
    // die relevanten Daten beginnen
    int offset;
    MPI_Exscan(&n, &offset, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("[%02d] offset = %d\n", rank, offset);

    // Um MPI_Scatterv zu nutzen müssen wir die offsets und die startpunkte
    // Diese sammeln wir per allgather ein
    // Wir könnten auch das eine aus dem anderen berechnen
    int *offsets;
    int *sizes;
    if (rank == 0)
    {
        offsets = malloc(size * sizeof(int));
        sizes = malloc(size * sizeof(int));
    }
    MPI_Gather(&offset, 1, MPI_INT, offsets, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(&n, 1, MPI_INT, sizes, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Nun können wir das globale Array an die einzelnen Prozesse verteilen
    double *local_numbers = malloc(n * sizeof(double));
    MPI_Scatterv(global_numbers, sizes, offsets, MPI_DOUBLE, 
                 local_numbers, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Jeder Prozess addiert seine Ranknummer auf das lokale Array
    for (int i = 0; i < n; i++)
    {
        local_numbers[i] += (double)rank;
    }

    // Nun werden wieder alle Arrays eingesammelt
    MPI_Gatherv(local_numbers, n, MPI_DOUBLE, global_numbers, sizes, offsets, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Auf Rank 0 können wir jetzt das Array ausgeben:
    if (rank == 0)
    {
        for (int i = 0; i < total_n; i++)
        {
            printf("numbers[%d] = %.1f\n", i, global_numbers[i]);
        }
    }

    free(local_numbers);
    if(rank == 0) {
        free(global_numbers);
        free(offsets);
        free(sizes);
    }

    MPI_Finalize();
}