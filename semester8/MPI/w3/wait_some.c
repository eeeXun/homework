// mpirun -n 100 ./a.out
//
// outcount in MPI_Waitsome return how many request done
// If the #processor is too small, outcount is normally 1
// Need to specify with larger number to see the effect
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_arr(int* arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], i == size - 1 ? "\n" : " ");
    }
}

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int data[size - 1];
        int indices[size - 1];
        int outcount;
        int want_n = size - 1;
        MPI_Request requests[size - 1];
        MPI_Status statuses[size - 1];

        for (int i = 0; i < size - 1; i++)
            MPI_Irecv(
                &data[i], 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD, &requests[i]);
        while (want_n > 0) {
            MPI_Waitsome(size - 1, requests, &outcount, indices, statuses);
            printf("Outcount: %d\n", outcount);
            printf("Data: ");
            print_arr(data, size - 1);
            printf("Indices: ");
            print_arr(indices, size - 1);
            want_n -= outcount;
        }
        printf("Rank 0 done\n");
    } else {
        int data;
        MPI_Request request;
        data = rank * 10;
        if (rank > 50) {
            sleep(3);
        }
        printf("Rank sleep end: %d\n", rank);
        MPI_Isend(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    }

    MPI_Finalize();
    return 0;
}
