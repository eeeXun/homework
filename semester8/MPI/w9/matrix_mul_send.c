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
    MPI_Datatype COLUMN;
    MPI_Type_vector(N, 1, N, MPI_INT, &COLUMN);
    MPI_Type_commit(&COLUMN);

    int *a, *b, *b_col, *c, *c_col;
    a = malloc(sizeof(int) * N * N);
    b_col = malloc(sizeof(int) * N);
    c_col = calloc(N, sizeof(int));
    if (rank == 0) {
        b = malloc(sizeof(int) * N * N);
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
        // rank 0
        for (int i = 0; i < N; i++) {
            b_col[i] = b[N * i];
        }
        // rank others
        for (int i = 1; i < N; i++) {
            MPI_Send(&b[i], 1, COLUMN, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(b_col, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Bcast(a, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    // calculate
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c_col[i] += a[N * i + j] * b_col[j];
        }
    }

    if (rank == 0) {
        c = malloc(sizeof(int) * N * N);
        // rank 0
        for (int i = 0; i < N; i++) {
            c[N * i] = c_col[i];
        }
        // rank others
        for (int i = 1; i < N; i++) {
            MPI_Recv(&c[i], 1, COLUMN, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        print_matrix(c, N);
    } else {
        MPI_Send(c_col, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
