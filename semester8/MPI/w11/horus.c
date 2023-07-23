#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 100000
#endif

int main(int argc, char* argv[])
{
    int size, rank;
    double startwtime, endwtime;
    double mypi, pi;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
        startwtime = MPI_Wtime();

    srand(rank);
    double x, y;
    int count = 0;
    for (int i = 0; i < N; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if ((x * x + y * y) < 1 && ((1 - x) * (1 - x) + (1 - y) * (1 - y)) < 1)
            count++;
    }
    mypi = (double)count / N;
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi /= size;
        endwtime = MPI_Wtime();
        printf("Resule: %lf\n", pi);
        printf("wall clock time = %f\n", endwtime - startwtime);
    }

    MPI_Finalize();
    return 0;
}
