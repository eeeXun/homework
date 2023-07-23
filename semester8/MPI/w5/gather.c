#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#define ARRSIZE 100
int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[ARRSIZE];
    int b[ARRSIZE / 4];
    for (int i = 0; i < ARRSIZE; i++) {
        b[i] = i + rank * (ARRSIZE / 4);
    }

    MPI_Gather(
        b, ARRSIZE / 4, MPI_INT, arr, ARRSIZE / 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < 100; ++i)
            printf("%d ", arr[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
