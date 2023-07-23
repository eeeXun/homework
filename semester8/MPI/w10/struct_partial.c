#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    short id;
    char name[10];
    int height;
    int weight;
} Data;

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int blocklen[4] = { 0, 10, 1, 1 };
    MPI_Aint disp[4] = { offsetof(Data, id), offsetof(Data, name),
        offsetof(Data, height), offsetof(Data, weight) };
    MPI_Datatype old_type[4] = { MPI_SHORT, MPI_CHAR, MPI_INT, MPI_INT };
    MPI_Datatype data_type;
    MPI_Type_create_struct(4, blocklen, disp, old_type, &data_type);
    MPI_Type_commit(&data_type);

    Data* my_data;
    Data recv_data;
    if (rank == 0) {
        my_data = malloc(sizeof(Data) * 4);
        Data tmp[] = { { 1, "Alice", 161, 61 }, { 2, "Bob", 162, 62 },
            { 3, "Carol", 163, 63 }, { 4, "Daniel", 164, 64 } };
        for (int i = 0; i < 4; i++) {
            my_data[i].id = tmp[i].id;
            strcpy(my_data[i].name, tmp[i].name);
            my_data[i].height = tmp[i].height;
            my_data[i].weight = tmp[i].weight;
        }
    }
    MPI_Scatter(
        my_data, 1, data_type, &recv_data, 1, data_type, 0, MPI_COMM_WORLD);
    sleep(rank);
    printf("Rand %d: id: %d, name: %s, height: %d, weight: %d, BMI: %.1f\n",
        rank, recv_data.id, recv_data.name, recv_data.height, recv_data.weight,
        recv_data.weight * 10000
            / (double)(recv_data.height * recv_data.height));

    MPI_Finalize();
    return 0;
}
