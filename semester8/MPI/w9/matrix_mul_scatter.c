#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 3
#endif

void print_matrix(int* matrix, int n)
{
    for (int i = 0; i < n; i++) {
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

    // type
    MPI_Datatype COLUMN, COLTYPE;
    MPI_Type_vector(N, 1, N, MPI_INT, &COLUMN);
    MPI_Type_create_resized(COLUMN, 0, sizeof(int), &COLTYPE);
    MPI_Type_commit(&COLTYPE);

    int *a, *b, *b_col, *c, *c_col;
    a = malloc(sizeof(int) * N * N);
    b_col = malloc(sizeof(int) * N);
    c_col = calloc(N, sizeof(int));
    if (rank == 0) {
        b = malloc(sizeof(int) * N * N);
        c = malloc(sizeof(int) * N * N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &a[N * i + j]);
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &b[N * i + j]);
            }
        }
    }
    MPI_Bcast(a, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, 1, COLTYPE, b_col, 3, MPI_INT, 0, MPI_COMM_WORLD);
    // calculate
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c_col[i] += a[N * i + j] * b_col[j];
        }
    }

    MPI_Gather(c_col, 3, MPI_INT, c, 1, COLTYPE, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        print_matrix(c, N);
    }

    MPI_Finalize();
    return 0;
}
