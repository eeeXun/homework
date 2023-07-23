#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int world_rank, world_size;
    MPI_Group world_group;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    const int ranks[8] = { 2, 3, 5, 7, 11, 13, 17, 19 };

    MPI_Group new_group;
    MPI_Comm new_comm;
    int new_rank = -1, new_size = -1;
    MPI_Group_incl(world_group, sizeof(ranks) / sizeof(int), ranks, &new_group);
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);
    if (MPI_COMM_NULL != new_comm) {
        MPI_Comm_rank(new_comm, &new_rank);
        MPI_Comm_size(new_comm, &new_size);
    }
    printf("WORLD RANK/SIZE: %d/%d \t PRIME RANK/SIZE: %d/%d\n", world_rank,
        world_size, new_rank, new_size);

    MPI_Group_free(&world_group);
    MPI_Group_free(&new_group);
    if (MPI_COMM_NULL != new_comm) {
        MPI_Comm_free(&new_comm);
    }

    MPI_Finalize();
    return 0;
}
