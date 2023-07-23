#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_M 6
#define MATRIX_N 8
#define SUB_SIZE 3

void print_matrix(int* matrix, int m, int n)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%s", matrix[i * n + j], j == n - 1 ? "\n" : " ");
        }
    }
}

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int* matrix;
    if (rank == 0) {
        int arr_size[2] = { MATRIX_M, MATRIX_N };
        int sub_arr_size[2] = { SUB_SIZE, SUB_SIZE };
        int arr_start[2] = { 0, 0 };
        MPI_Datatype MATRIX33;
        MPI_Type_create_subarray(2, arr_size, sub_arr_size, arr_start,
            MPI_ORDER_C, MPI_INT, &MATRIX33);
        MPI_Type_commit(&MATRIX33);
        matrix = malloc(sizeof(int) * MATRIX_M * MATRIX_N);
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                scanf("%d", &matrix[MATRIX_N * i + j]);
            }
        }
        for (int i = 0; i <= MATRIX_M - SUB_SIZE; i++) {
            for (int j = 0; j <= MATRIX_N - SUB_SIZE; j++) {
                MPI_Send(&matrix[MATRIX_N * i + j], 1, MATRIX33, 1, 0,
                    MPI_COMM_WORLD);
            }
        }
    } else {
        matrix = malloc(sizeof(int) * SUB_SIZE * SUB_SIZE);
        int count = 0;
        for (int i = 0; i <= MATRIX_M - SUB_SIZE; i++) {
            for (int j = 0; j <= MATRIX_N - SUB_SIZE; j++) {
                MPI_Recv(matrix, SUB_SIZE * SUB_SIZE, MPI_INT, 0, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                count++;
                printf("Matrix %d\n", count);
                print_matrix(matrix, SUB_SIZE, SUB_SIZE);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
