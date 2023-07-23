#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 100
#endif

void init(int a[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        a[i] = rand() % N;
}

/* Exchange Sort */
void sort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; ++i)
        for (j = i + 1; j < n; ++j)
            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
}

int main(int argc, char** argv)
{
    int rank, a[N], b[N / 2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        init(a, N);
        MPI_Send(&a[N / 2], N / 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
        sort(a, N / 2);
        MPI_Recv(b, N / 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        /* Serial: Merge array b and sorted part of array a */
        int i = 0, j = 0;
        while (i < N / 2 && j < N / 2) {
            if (a[i] < b[j])
                printf("%d ", a[i++]);
            else
                printf("%d ", b[j++]);
        }
        if (i == N / 2) {
            for (; j < N / 2; ++j)
                printf("%d ", b[j]);
            printf("\n");
        } else {
            for (; i < N / 2; ++i)
                printf("%d ", a[i]);
            printf("\n");
        }
    } else if (rank == 1) {
        MPI_Recv(b, N / 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sort(b, N / 2);
        MPI_Send(b, N / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
