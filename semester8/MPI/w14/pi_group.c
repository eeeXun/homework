/* compute pi using Monte Carlo method */
#include <limits.h> // INT_MAX
#include <math.h>
#include <mpe.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> // random()
#define CHUNKSIZE 1000
/* message tags */
#define REQUEST 1
#define REPLY 2

int main(int argc, char* argv[])
{
    int iter;
    int in, out, i, iters, max, ix, iy, ranks[1], done, temp;
    double x, y, Pi, error, epsilon;
    int size, rank, server, totalin, totalout, workerid;
    int rands[CHUNKSIZE], request;
    MPI_Comm world, workers;
    MPI_Group world_group, worker_group;
    MPI_Status status;
    int event1a, event1b, event2a, event2b;

    MPI_Init(&argc, &argv);
    world = MPI_COMM_WORLD;
    MPI_Comm_size(world, &size);
    MPI_Comm_rank(world, &rank);
    server = size - 1; /* last proc is server */
    MPE_Log_get_state_eventIDs(&event1a, &event1b);
    MPE_Log_get_state_eventIDs(&event2a, &event2b);
    if (rank == 0) {
        MPE_Describe_state(event1a, event1b, "Comm", "red");
        MPE_Describe_state(event2a, event2b, "Comp", "green");
        if (argc == 1)
            printf("Usage: %s <epsilon>\n", argv[0]);
        else
            sscanf(argv[1], "%lf", &epsilon);
    }
    MPI_Bcast(&epsilon, 1, MPI_DOUBLE, 0, world);

    MPI_Comm_group(world, &world_group);
    ranks[0] = server;
    MPI_Group_excl(world_group, 1, ranks, &worker_group);
    MPI_Comm_create(world, worker_group, &workers);
    MPI_Group_free(&worker_group);

    if (rank == server) { /* I am the rand server */
        do {
            MPI_Recv(
                &request, 1, MPI_INT, MPI_ANY_SOURCE, REQUEST, world, &status);
            if (request) {
                for (i = 0; i < CHUNKSIZE;) {
                    rands[i] = random();
                    if (rands[i] <= INT_MAX)
                        ++i;
                }
                MPI_Send(
                    rands, CHUNKSIZE, MPI_INT, status.MPI_SOURCE, REPLY, world);
            }
        } while (request > 0);
    } else { /* I am a worker process */
        request = 1;
        done = in = out = 0;
        max = INT_MAX; /* max int, for normalization */
        MPE_Log_event(event1a, 0, NULL);
        MPI_Send(&request, 1, MPI_INT, server, REQUEST, world);
        MPE_Log_event(event1b, 0, NULL);
        MPI_Comm_rank(workers, &workerid);
        iter = 0;
        while (!done) {
            ++iter;
            request = 1;
            MPE_Log_event(event1a, 0, NULL);
            MPI_Recv(rands, CHUNKSIZE, MPI_INT, server, REPLY, world,
                MPI_STATUS_IGNORE);
            MPE_Log_event(event1b, 0, NULL);
            MPE_Log_event(event2a, 0, NULL);
            for (i = 0; i < CHUNKSIZE;) {
                x = (((double)rands[i++]) / max) * 2 - 1;
                y = (((double)rands[i++]) / max) * 2 - 1;
                if (x * x + y * y < 1.0)
                    ++in;
                else
                    ++out;
            }
            MPI_Allreduce(&in, &totalin, 1, MPI_INT, MPI_SUM, workers);
            MPI_Allreduce(&out, &totalout, 1, MPI_INT, MPI_SUM, workers);
            Pi = (4.0 * totalin) / (totalin + totalout);
            error = fabs(Pi - 3.141592653589793238462643);
            done = (error < epsilon || (totalin + totalout) > 1000000);
            request = (done) ? 0 : 1;
            MPE_Log_event(event2b, 0, NULL);
            MPE_Log_event(event1a, 0, NULL);
            if (rank == 0) {
                printf("\rpi = %23.20f", Pi);
                MPI_Send(&request, 1, MPI_INT, server, REQUEST, world);
            } else {
                if (request)
                    MPI_Send(&request, 1, MPI_INT, server, REQUEST, world);
            }
            MPE_Log_event(event1b, 0, NULL);
        }
        MPI_Comm_free(&workers);
    }

    if (rank == 0) {
        printf("\npoints: %d\nin: %d, out: %d, <ret> to exit\n",
            totalin + totalout, totalin, totalout);
        getchar();
    }
    MPI_Finalize();

    return 0;
}
