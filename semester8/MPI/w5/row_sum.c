#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n, divided;
    int* arr_send;
    int* arr_recv;
    int* sum;
    if (rank == 0) {
        scanf("%d", &n);
        arr_send = malloc(sizeof(int) * n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &arr_send[i * n + j]);
            }
        }
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    divided = n / size;
    arr_recv = malloc(sizeof(int) * n * divided);
    MPI_Scatter(arr_send, n * divided, MPI_INT, arr_recv, n * divided, MPI_INT,
        0, MPI_COMM_WORLD);

    sum = calloc(divided, sizeof(int));
    for (int i = 0; i < divided; i++) {
        for (int j = 0; j < n; j++) {
            sum[i] += arr_recv[i * n + j];
        }
        printf("Rank %d, sum=%d\n", rank, sum[i]);
    }

    MPI_Gather(
        sum, divided, MPI_INT, arr_recv, divided, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            printf("sum[%d] = %d\n", i, arr_recv[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
