#include <mpi.h>
#include <stdio.h>

int main() {
    MPI_Init(NULL, NULL);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int zahl = 0;

    if(rank == 0) {
        zahl = 5;
    }

    MPI_Bcast (&zahl, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rank %d hat Zahl %d\n", rank, zahl);

    MPI_Finalize();
}
