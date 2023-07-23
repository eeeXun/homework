#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int a[3], b[3];

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < 3; ++i)
        a[i] = rank * 100 + i;

    MPI_Reduce(a, b, 3, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        for (int i = 0; i < 3; ++i)
            printf("b[%d] = %d\n", i, b[i]);

    MPI_Finalize();
    return 0;
}
