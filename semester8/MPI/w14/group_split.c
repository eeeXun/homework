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

    int color = world_rank / 4;

    MPI_Comm row_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &row_comm);

    int row_rank, row_size;
    MPI_Comm_rank(row_comm, &row_rank);
    MPI_Comm_size(row_comm, &row_size);
    printf("WORLD RANK/SIZE: %d/%d \t ROW RANK/SIZE: %d/%d\n", world_rank,
        world_size, row_rank, row_size);

    MPI_Comm_free(&row_comm);

    MPI_Finalize();
    return 0;
}
