#include <mpe.h>
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
    int event1a, event1b, event2a, event2b, event3a, event3b, event4a, event4b;
    MPE_Log_get_state_eventIDs(&event1a, &event1b);
    MPE_Log_get_state_eventIDs(&event2a, &event2b);
    MPE_Log_get_state_eventIDs(&event3a, &event3b);
    MPE_Log_get_state_eventIDs(&event4a, &event4b);

    if (rank == 0) {
        // log
        MPE_Describe_state(event1a, event1b, "Read", "red");
        MPE_Describe_state(event2a, event2b, "Send", "green");
        MPE_Describe_state(event3a, event3b, "Compute", "yellow");
        MPE_Describe_state(event4a, event4b, "Recv", "blue");

        MPE_Log_event(event1a, 0, NULL);
        scanf("%d", &n);
        matrix = malloc(sizeof(int) * n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i * n + j]);
            }
        }
        MPE_Log_event(event1b, 0, NULL);
    }
    MPE_Log_event(event2a, 0, NULL);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank != 0)
        matrix = malloc(sizeof(int) * n * n);
    MPI_Bcast(matrix, n * n, MPI_INT, 0, MPI_COMM_WORLD);
    MPE_Log_event(event2b, 0, NULL);

    MPE_Log_event(event3a, 0, NULL);
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
    MPE_Log_event(event3b, 0, NULL);

    MPE_Log_event(event4a, 0, NULL);
    MPI_Gather(result, n * divided, MPI_INT, matrix, n * divided, MPI_INT, 0,
        MPI_COMM_WORLD);
    MPE_Log_event(event4b, 0, NULL);

    if (rank == 0)
        print_matrix(matrix, n);

    MPI_Finalize();
    return 0;
}
