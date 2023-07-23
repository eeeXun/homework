#include <mpi.h>
#include <stdio.h>

int data[] = { 24, 48, 192, 96 };
int a, b;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

void my_gcd(
    void* inputBuffer, void* outputBuffer, int* len, MPI_Datatype* datatype)
{
    int* input = (int*)inputBuffer;
    int* output = (int*)outputBuffer;
    *output = gcd(*input, *output);
}

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Op my_op;
    MPI_Op_create(my_gcd, 1, &my_op);

    a = data[rank];
    MPI_Reduce(&a, &b, 1, MPI_INT, my_op, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("GCD = %d\n", b);

    MPI_Finalize();
    return 0;
}
