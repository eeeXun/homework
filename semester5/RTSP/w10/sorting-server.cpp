#include "mysocket.h"
#include "protocols.h"
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_PORT "5000"
using std::swap;

void quick_sort(int* arr, int left, int right);

int main(int argc, char *argv[]) {
    int N;
    char dst[50];
    if (argc == 3)
        sprintf(dst, "%s:%s", argv[1], argv[2]);
    else
        sprintf(dst, "%s:%s", argv[1], DEFAULT_PORT);
    Endpoint ep(TCP | SERVER, dst);

    ep.Recv(&N, sizeof(N), 0);
    int* a = (int *)malloc(sizeof(int) * N);
    ep.Recv(a, sizeof(int) * N, 0);
    quick_sort(a, 0, N - 1);
    for (int i = 0; i < N; ++i) {
        printf("%d: %d\n", i, a[i]);
    }

    return 0;
}

void quick_sort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int l = left - 1, r = right;
        while (l < r) {
            while (l < right && arr[++l] < pivot);
            while (r > left && arr[--r] > pivot);
            if (l >= r)
                break;
            swap(arr[l], arr[r]);
        }
        swap(arr[l], arr[right]);
        quick_sort(arr, left, l - 1);
        quick_sort(arr, l + 1, right);
    }
}
