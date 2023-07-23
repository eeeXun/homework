#include <mpi.h>
#include <stdio.h>

int a[3], b[3];

void f(void* inputBuffer, void* outputBuffer, int* len, MPI_Datatype* datatype)
{
    int* input = (int*)inputBuffer;
    int* output = (int*)outputBuffer;
    for (int i = 0; i < *len; ++i)
        output[i] += input[i];
}

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < 3; ++i)
        a[i] = rank * 100 + i;

    MPI_Op my_op;
    MPI_Op_create(f, 1, &my_op);
    MPI_Reduce(a, b, 3, MPI_INT, my_op, 0, MPI_COMM_WORLD);

    if (rank == 0)
        for (int i = 0; i < 3; i++)
            printf("b[%d] = %d\n", i, b[i]);

    MPI_Finalize();
    return 0;
}
