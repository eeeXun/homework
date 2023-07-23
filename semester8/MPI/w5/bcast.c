#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[size];
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            arr[i] = i;
        }
    }

    MPI_Bcast(arr, size, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Rank %d:arr[%d]=%d\n", rank, rank, arr[rank]);

    MPI_Finalize();
    return 0;
}
