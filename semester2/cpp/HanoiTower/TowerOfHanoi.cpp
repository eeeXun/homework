#include "Tower.h"
#include <iostream>
#define MAX_HEIGHT 2
using namespace std;

void show(Tower[], unsigned int);
void move(Tower[], int, int, int, unsigned int&);

int main()
{
    // At the beginning, all disks are on the first tower
    Tower tower[3] = { MAX_HEIGHT, 0, 0 };

    unsigned int nStep = 0;
    // Show Step 0
    show(tower, nStep);

    // Each step will be shown within move()
    move(tower, 0, 1, MAX_HEIGHT, nStep);
    return 0;
}

void show(Tower tower[], unsigned int nStep)
{
    cout << "Step " << nStep << endl;
    int i, j;
    for (i = 0; i < 3; i++) {
        cout << '|';
        for (j = 1; j <= MAX_HEIGHT; ++j)
            if (tower[i].t[j] > 0)
                cout << static_cast<int>(tower[i].t[j]);
        cout << endl;
    }
}

void move(Tower tower[], int src, int dst, int height, unsigned int& nStep)
{
    if (height == 1) {
        tower[dst].t[++tower[dst].towerHeight]
            = tower[src].t[tower[src].towerHeight];
        tower[src].t[tower[src].towerHeight--] = 0;
        ++nStep;
        show(tower, nStep);
    } else {
        size_t tmp = 3 - src - dst; // If you want to move from Tower 0 to To
                                    // Tower 1, tmp will be Tower 2.
        move(tower, src, tmp, height - 1, nStep);
        move(tower, src, dst, 1, nStep);
        move(tower, tmp, dst, height - 1, nStep);
    }
}
