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

    MPI_Scan(a, b, 3, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    sleep(rank);
    printf("Rank %d: ", rank);
    for (int i = 0; i < 3; ++i)
        printf("b[%d] = %d\t", i, b[i]);
    printf("\n");

    MPI_Finalize();
    return 0;
}
