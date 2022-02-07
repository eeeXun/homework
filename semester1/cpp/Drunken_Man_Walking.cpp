#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int a()
{
    int x = rand();
    if (x % 2 == 1) {
        return 1;
    } else {
        return -1;
    }
}

int main()
{
    srand(time(NULL));
    cout << "Please input the initial position (p) -- ";
    int i;
    cin >> i;
    while (i > 0 && i < 10) {
        cout << "|";
        for (int j = 1; j < i; j++) {
            cout << " ";
        }
        cout << "*";
        for (int j = i + 1; j <= 9; j++) {
            cout << " ";
        }
        cout << "|" << endl;
        i = i + a();
    }
    if (i == 0) {
        cout << "He arrives home safely.";
    } else {
        cout << "He falls into a river in a cold winter!";
    }

    return 0;
}
