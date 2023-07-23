#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#ifndef N
#define N 4
#endif

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int n = N;
        int cnt, disp[size];
        disp[0] = 0;
        for (int i = 0; i < size; i++) {
            cnt = n / (size - i);
            n -= cnt;
            if (i == size - 1) {
                printf("%d\n", cnt);
            } else {
                disp[i + 1] = disp[i] + cnt;
                printf("%d, ", cnt);
            }
        }
        for (int i = 0; i < size; i++) {
            printf("%d%s", disp[i], i == size - 1 ? "\n" : ", ");
        }
    }

    MPI_Finalize();
    return 0;
}
