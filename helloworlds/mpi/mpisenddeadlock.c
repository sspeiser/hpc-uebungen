#include <mpi.h>
#include <stdio.h>

int main() {
    MPI_Init(NULL, NULL);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(size != 2) {
        printf("Example only for two processes\n");
    }
    int partner_rank = 1- rank;

    int message_received;
    MPI_Recv(&message_received, 1, MPI_INT, partner_rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Received %d\n", message_received);
    MPI_Send(&rank, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

    MPI_Finalize();
}