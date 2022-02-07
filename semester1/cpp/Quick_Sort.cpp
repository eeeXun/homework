#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

int cmpFunc(const void* a, const void* b)
{
    return strcmp(*(char**)a, *(char**)b);
}
void show_array(char* a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << a[i] << '\n';
}

int main()
{
    const int N = 10;
    char word[N][20];
    char* a[N];

    for (int i = 0; i < N; i++) {
        cin >> word[i];
        a[i] = word[i];
    }
    cout << "=====\n";
    qsort(a, N, sizeof(a[0]), cmpFunc);
    show_array(a, N);
    return 0;
}
