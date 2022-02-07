#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
    int a[3][3], b[3][3], c[3][3] = { 0 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> b[i][j];
        }
    }
    //
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            c[0][i] += a[0][j] * b[j][i];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            c[1][i] += a[1][j] * b[j][i];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            c[2][i] += a[2][j] * b[j][i];
        }
    }
    //
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(3) << c[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
