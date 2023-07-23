#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

void print_arr(int* arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], i < size - 1 ? " " : "\n");
    }
}

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int* send_arr;
    int* recv_arr;
    int* counts;
    int* displs;
    // init counts & displs
    int cnt, n = N;
    counts = malloc(sizeof(int) * size);
    displs = calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        cnt = n / (size - i);
        counts[i] = cnt;
        n -= cnt;
        if (i < size - 1) {
            displs[i + 1] = displs[i] + cnt;
        }
    }
    recv_arr = malloc(sizeof(int) * counts[rank]);
    // init data
    if (rank == 0) {
        send_arr = malloc(sizeof(int) * N);
        for (int i = 0; i < N; i++) {
            send_arr[i] = i;
        }
    }
    // scatter
    MPI_Scatterv(send_arr, counts, displs, MPI_INT, recv_arr, counts[rank],
        MPI_INT, 0, MPI_COMM_WORLD);
    // modify arr
    for (int i = 0; i < counts[rank]; i++) {
        recv_arr[i] += 100 * rank;
    }
    // gather
    MPI_Gatherv(recv_arr, counts[rank], MPI_INT, send_arr, counts, displs,
        MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        print_arr(send_arr, N);
    }

    MPI_Finalize();
    return 0;
}
