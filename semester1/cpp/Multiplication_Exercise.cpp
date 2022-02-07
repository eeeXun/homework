#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int a, b, mistake = 0;
    for (int i = 1; i <= 10; i++) {
        int c;
        a = rand() % 99;
        b = rand() % 99;
        cout << a << " * " << b << " = ";
        cin >> c;
        if (c != (a * b)) {
            cout << "Wrong! " << a << "*" << b << "=" << a * b << endl;
            mistake++;
        }
    }
    cout << "You made " << mistake << " mistake" << (mistake > 1 ? "s" : "")
         << " today.";

    return 0;
}
