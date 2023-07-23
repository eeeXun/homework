#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char name[8];
    int height;
    int weight;
} Data;

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int blocklen[3] = { 8, 1, 1 };
    MPI_Aint disp[3] = { offsetof(Data, name), offsetof(Data, height),
        offsetof(Data, weight) };
    MPI_Datatype old_type[3] = { MPI_CHAR, MPI_INT, MPI_INT };
    MPI_Datatype data_type;
    MPI_Type_create_struct(3, blocklen, disp, old_type, &data_type);
    MPI_Type_commit(&data_type);

    Data* my_data;
    Data recv_data;
    if (rank == 0) {
        my_data = malloc(sizeof(Data) * 4);
        Data tmp[] = { { "Alice", 161, 61 }, { "Bob", 162, 62 },
            { "Carol", 163, 63 }, { "Daniel", 164, 64 } };
        for (int i = 0; i < 4; i++) {
            strcpy(my_data[i].name, tmp[i].name);
            my_data[i].height = tmp[i].height;
            my_data[i].weight = tmp[i].weight;
        }
    }
    MPI_Scatter(
        my_data, 1, data_type, &recv_data, 1, data_type, 0, MPI_COMM_WORLD);
    sleep(rank);
    printf("Rand %d: name: %s, height: %d, weight: %d, BMI: %.1f\n", rank,
        recv_data.name, recv_data.height, recv_data.weight,
        recv_data.weight * 10000
            / (double)(recv_data.height * recv_data.height));

    MPI_Finalize();
    return 0;
}
