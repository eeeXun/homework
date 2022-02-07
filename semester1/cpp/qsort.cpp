#include <cstdlib>
#include <iostream>
int f1(const void* a, const void* b) { return *(int*)b - *(int*)a; }
int f2(const void* a, const void* b)
{
    return (*(int*)a % 10) + (*(int*)a / 10) - *(int*)b % 10 - *(int*)b / 10;
}
int f3(const void* a, const void* b) { return *(int*)a - *(int*)b; }

void print_array(int a[], int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << a[i] << (i == n - 1 ? '\n' : ' ');
}

int main()
{
    int (*pfun[3])(const void* a, const void* b) = { f1, f2, f3 };
    int a[10] = { 57, 33, 18, 21, 70, 67, 44, 41, 82, 92 };
    for (int i = 0; i < 3; ++i) {
        qsort(a, 10, sizeof(a[0]), pfun[i]);
        print_array(a, 10);
    }
    return 0;
}
