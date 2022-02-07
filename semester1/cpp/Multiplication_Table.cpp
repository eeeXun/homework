#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
    int i, j;
    for (j = 1; j <= 9; j++) {
        for (i = 1; i <= 3; i++) {
            cout << i << "*" << j << "=" << setw(2) << i * j << "   ";
        }
        cout << endl;
    }
    cout << endl;
    for (j = 1; j <= 9; j++) {
        for (i = 4; i <= 6; i++) {
            cout << i << "*" << j << "=" << setw(2) << i * j << "   ";
        }
        cout << endl;
    }
    cout << endl;
    for (j = 1; j <= 9; j++) {
        for (i = 7; i <= 9; i++) {
            cout << i << "*" << j << "=" << setw(2) << i * j << "   ";
        }
        cout << endl;
    }

    return 0;
}
