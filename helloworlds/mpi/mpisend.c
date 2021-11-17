#include <mpi.h>
#include <stdio.h>

int main() {
    MPI_Init(NULL, NULL);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        for(int i=1;i<size;i++) {
            MPI_Send(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Status status;
        int received_rank;
        MPI_Recv(&received_rank, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("Received %d\n", received_rank);
    }
    MPI_Finalize();
}