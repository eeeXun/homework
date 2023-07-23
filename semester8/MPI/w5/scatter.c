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
    if (rank == 0) {
        for (int i = 0; i < ARRSIZE; i++) {
            arr[i] = i;
        }
    }

    MPI_Scatter(
        arr, ARRSIZE / 4, MPI_INT, b, ARRSIZE / 4, MPI_INT, 0, MPI_COMM_WORLD);

    sleep(rank);
    printf("Rank %d:\n", rank);
    for (int i = 0; i < 25; ++i) {
        printf("b[%d] = %d ", i, b[i]);
        if (i % 5 == 4)
            printf("\n");
    }

    MPI_Finalize();
    return 0;
}
