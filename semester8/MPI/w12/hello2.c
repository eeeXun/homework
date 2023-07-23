/* hello2.c */
#include <mpe.h>
#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int event1a, event1b;
    MPE_Log_get_state_eventIDs(&event1a, &event1b);
    if (rank == 0) {
        MPE_Describe_state(event1a, event1b, "Sleep", "red");
    }

    MPE_Log_event(event1a, 0, NULL);
    sleep(1 + rank);
    MPE_Log_event(event1b, 0, NULL);
    printf("I am %d of %d\n", rank + 1, size);

    MPI_Finalize();
    return 0;
}
