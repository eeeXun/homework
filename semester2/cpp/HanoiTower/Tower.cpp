#include "Tower.h"
#include <iostream>
using namespace std;

int Tower::max = 0;
Tower::Tower(int M)
{
    if (M > 0) {
        max += M;
        towerHeight = max;
        t = new char[max + 1];
        for (int i = 1; i <= max; ++i)
            t[i] = M + 1 - i;
    } else {
        towerHeight = 0;
        t = new char[max + 1];
        for (int i = 1; i <= max; ++i)
            t[i] = 0;
    }
}
