#include "turtle.h"
#include <iostream>
using namespace std;

void checkcommand(char command, bool& pen, turtle& T);

int main()
{
    turtle T;
    char command;
    bool pen = false;
    while (cin >> command && command != '9') {
        T.checkcommand(command, pen, T);
    }
    return 0;
}
