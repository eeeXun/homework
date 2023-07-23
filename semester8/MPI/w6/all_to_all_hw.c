// Run with: mpirun -n 4 ./a.out
// Suppose there are 4 student, each of them have 4 exams. Mandarin, English, Math, Science
// Every processor would get a student's scores in these four subject
// Now, we want the get average of each subject
// So we utilize MPI_Alltoall function to calculate average
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 4
int score[N], subject[N];

int get_rand_score(int rank, int index)
{
    srand(time(NULL) + rank + index);
    return rand() % 100;
}

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize score for student
    for (int i = 0; i < N; i++) {
        score[i] = get_rand_score(rank, i);
    }
    // Gathers data from all tasks and distribute the combined data to all tasks
    MPI_Alltoall(
        score, N / size, MPI_INT, subject, N / size, MPI_INT, MPI_COMM_WORLD);
    // Calculate average
    float average = 0;
    for (int i = 0; i < N; i++) {
        average += subject[i];
    }
    average /= N;

    // Print scores of a student
    sleep(rank);
    printf("Rank %d score:", rank);
    for (int i = 0; i < N; i++)
        printf(" %d", score[i]);
    printf("\n");
    // Print subject average
    printf("Subject %d average: %.2f\n", rank, average);

    MPI_Finalize();
    return 0;
}
