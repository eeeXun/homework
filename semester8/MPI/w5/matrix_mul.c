#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void print_matrix(int* matrix, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%s", matrix[i * n + j], j == n - 1 ? "\n" : " ");
        }
    }
}

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n, divided;
    int* matrix;
    int* arr_recv;
    int* result;
    if (rank == 0) {
        scanf("%d", &n);
        matrix = malloc(sizeof(int) * n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i * n + j]);
            }
        }
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank != 0)
        matrix = malloc(sizeof(int) * n * n);
    MPI_Bcast(matrix, n * n, MPI_INT, 0, MPI_COMM_WORLD);

    divided = n / size;
    arr_recv = malloc(sizeof(int) * n * divided);
    MPI_Scatter(matrix, n * divided, MPI_INT, arr_recv, n * divided, MPI_INT, 0,
        MPI_COMM_WORLD);

    result = calloc(sizeof(int), n * divided);
    for (int i = 0; i < divided; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i * n + j] += arr_recv[i * n + k] * matrix[k * n + j];
            }
        }
    }

    MPI_Gather(result, n * divided, MPI_INT, matrix, n * divided, MPI_INT, 0,
        MPI_COMM_WORLD);

    if (rank == 0)
        print_matrix(matrix, n);

    MPI_Finalize();
    return 0;
}
