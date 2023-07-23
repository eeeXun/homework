#include <mpi.h>
#include <stdio.h>

int data[] = { 24, 48, 192, 96 };
int a, b;

void my_max(
    void* inputBuffer, void* outputBuffer, int* len, MPI_Datatype* datatype)
{
    int* input = (int*)inputBuffer;
    int* output = (int*)outputBuffer;
    if (*input > *output)
        *output = *input;
}

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Op my_op;
    MPI_Op_create(my_max, 1, &my_op);

    a = data[rank];
    MPI_Reduce(&a, &b, 1, MPI_INT, my_op, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("Max = %d\n", b);

    MPI_Finalize();
    return 0;
}
