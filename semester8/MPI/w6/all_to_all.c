#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#define N 16
int array[N], b[N];

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize array on each process
    for (int i = 0; i < N; i++) {
        b[i] = i + rank * 100;
    }
    // Gathers data from all tasks and distribute the combined data to all tasks
    MPI_Alltoall(
        b, N / size, MPI_INT, array, N / size, MPI_INT, MPI_COMM_WORLD);

    // Print array element on each process
    sleep(rank);
    printf("Rank %d: ", rank);
    for (int i = 0; i < N; ++i)
        printf("%3d ", array[i]);
    printf("\n");

    MPI_Finalize();
    return 0;
}
