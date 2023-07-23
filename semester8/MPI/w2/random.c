#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool in_array(int* data, int size, int element)
{
    for (int i = 0; i < size; i++) {
        if (data[i] == element)
            return true;
    }
    return false;
}

int get_rand(int* data, int rank, int size)
{
    srand(time(NULL) + rank);
    return data[rand() % size];
}

void print_data(int* data, int size, int rank)
{
    printf("%d : [", rank);
    for (int i = 0; i < size; i++) {
        printf("%d%s", data[i], i == size - 1 ? "]\n" : " ");
    }
}

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int length = 1;

    switch (rank) {
    case 0: {
        int* visited = malloc(length * sizeof(int));
        int* unvisited = malloc((size - length) * sizeof(int));
        visited[0] = 0;
        print_data(visited, length, rank);
        for (int i = 1; i < size; i++) {
            unvisited[i - 1] = i;
        }
        int next = get_rand(unvisited, rank, (size - length));
        MPI_Send(&length, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Send(visited, length, MPI_INT, next, 0, MPI_COMM_WORLD);
        printf("%d -> %d\n", rank, next);
        break;
    }
    default: {
        MPI_Recv(&length, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);
        length++;
        int* visited = malloc(length * sizeof(int));
        MPI_Recv(visited, length - 1, MPI_INT, MPI_ANY_SOURCE, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        visited[length - 1] = rank;
        print_data(visited, length, rank);
        if (length < size) {
            int* unvisited = malloc((size - length) * sizeof(int));
            for (int i = 0, j = 0; i < size && j < (size - length); i++) {
                if (!in_array(visited, length, i)) {
                    unvisited[j] = i;
                    j++;
                }
            }
            int next = get_rand(unvisited, rank, (size - length));
            MPI_Send(&length, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
            MPI_Send(visited, length, MPI_INT, next, 0, MPI_COMM_WORLD);
            printf("%d -> %d\n", rank, next);
        }
        break;
    }
    }

    MPI_Finalize();
    return 0;
}
