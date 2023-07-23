#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void merge(int *arr, int start, int mid, int end) {
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[start + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergesort(int *arr, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergesort(arr, start, mid);
        mergesort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

int main(int argc, char** argv) {
    int rank, size, n, i;
    int *arr, *subarr;
    double starttime, endtime;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the number of elements: ");
        scanf("%d", &n);

        arr = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            arr[i] = rand() % n;

        starttime = MPI_Wtime();
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int subsize = n / size;
    subarr = (int*)malloc(subsize * sizeof(int));

    MPI_Scatter(arr, subsize, MPI_INT, subarr, subsize, MPI_INT, 0, MPI_COMM_WORLD);

    mergesort(subarr, 0, subsize - 1);

    MPI_Gather(subarr, subsize, MPI_INT, arr, subsize, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        mergesort(arr, 0, n - 1);

        endtime = MPI_Wtime();
        printf("Time taken: %f\n", endtime - starttime);

        free(arr);
    }

    free(subarr);

    MPI_Finalize();

    return 0;
}
