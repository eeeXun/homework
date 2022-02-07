#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    srand(time(NULL));
    int matrix_m = atoi(argv[1]); // row of matrix_1
    int matrix_n = matrix_m, matrix_p = matrix_m;
    // int matrix_n = atoi(argv[2]); // column of matrix_1 & row of matrix_2
    // int matrix_p = atoi(argv[3]); // column of matrix_2
    int avg, sum = 0;
    int matrix_1[matrix_m][matrix_n];

    // Init matrix
    for (int i = 0; i < matrix_m; i++) {
        for (int j = 0; j < matrix_n; j++) {
            matrix_1[i][j] = rand() % 1000;
        }
    }

    MPI_Init(&argc, &argv);
    // Get the number of process
    int SIZE;
    MPI_Comm_size(MPI_COMM_WORLD, &SIZE);
    // Get the rank of process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* buf;
    int gap = matrix_m / SIZE;
    if (rank != SIZE - 1) {
        for (int i = rank * gap; i < (rank + 1) * gap; i++) {
            avg = 0;
            for (int j = 0; j < matrix_n; j++) {
                avg += matrix_1[i][j];
            }
            // broadcast
            avg /= matrix_p;
            sum += avg;
            for (int root = 0; root < SIZE; root++) {
                if (rank == root) {
                    for (int dest = 0; dest < SIZE; dest++) {
                        if (dest != root)
                            MPI_Send(
                                &avg, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
                    }
                } else {
                    MPI_Recv(&avg, 1, MPI_DOUBLE, root, 0, MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE);
                    sum += avg;
                }
            }
        }
    } else {
        for (int i = rank * gap; i < matrix_m; i++) {
            avg = 0;
            for (int j = 0; j < matrix_n; j++) {
                avg += matrix_1[i][j];
            }
            // broadcast
            avg /= (double)matrix_p;
            for (int root = 0; root < SIZE; root++) {
                if (rank == root) {
                    for (int dest = 0; dest < SIZE; dest++) {
                        if (dest != root)
                            MPI_Send(
                                &avg, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
                    }
                } else {
                    MPI_Recv(&avg, 1, MPI_DOUBLE, root, 0, MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE);
                    sum += avg;
                }
            }
        }
    }
    // printf("[%d]: %d\n", rank, sum/matrix_m);

    MPI_Finalize();
    return 0;
}
