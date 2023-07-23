#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int getRandom(bool* arr, int rank, int n)
{
    srand(rank);
    int ans = rand() % n;
    while (arr[ans] == 1) {
        ans = rand() % n;
    }
    printf("%d send to %d\n\n", rank, ans);
    return ans;
}

int main(int argc, char** argv)
{
    int size, rank;
    int next, length;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    bool* bitmap = calloc(size, sizeof(bool));

    // if(rank==0){
    switch (rank) {
    case 0:
        bitmap[0] = 1;
        length = 1;

        int* data = calloc(length, sizeof(int));
        data[length - 1] = rank;

        // get next node
        next = getRandom(bitmap, rank, size);

        // send data's length
        MPI_Send(&length, 1, MPI_INT, next, 0, MPI_COMM_WORLD);

        // send data
        MPI_Send(data, length, MPI_INT, next, 0, MPI_COMM_WORLD);
        break;
        // }else{
    default: {
        // receive data's length
        MPI_Recv(&length, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);
        length = length + 1;

        // receive data
        int* data = calloc(length, sizeof(int));
        MPI_Recv(data, length - 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);

        // add rank into data & transform to bitmap
        data[length - 1] = rank;
        printf("%d get: ", rank);
        for (int i = 0; i < length; i++) {
            printf("%d%s", data[i], i == length - 1 ? "\n" : " ");
            bitmap[data[i]] = 1;
        }

        if (length != size) {
            // get next node
            next = getRandom(bitmap, rank, size);

            // send data's length
            MPI_Send(&length, 1, MPI_INT, next, 0, MPI_COMM_WORLD);

            // send data
            MPI_Send(data, length, MPI_INT, next, 0, MPI_COMM_WORLD);
        }
        break;
    }
    }

    MPI_Finalize();
    return 0;
}
