#include "turtle.h"
#include <iomanip>
#include <iostream>
using namespace std;

turtle::turtle()
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            graph[i][j] = '.';
        }
    }
    direction = 0;
    position[0] = 0;
    position[1] = 0;
}
void turtle::checkcommand(char command, bool& pen, turtle& T)
{
    if (command == '1') {
        pen = false;
        cout << "pen up" << endl;
    } else if (command == '2') {
        pen = true;
        cout << "pen down" << endl;
    } else if (command == '3') {
        T.turnRight();
        T.nowdirection();
    } else if (command == '4') {
        T.turnLeft();
        T.nowdirection();
    } else if (command == '5') {
        char com;
        int step;
        cin >> com >> step;
        if (com != ',' || step <= 0 || step > 20) {
            cout << "please input '5' , ',' and length of step,which must >0 "
                    "and <20"
                 << endl;
        } else {
            if (T.moveable(step)) {
                T.ahead(step, pen);
                T.printPosition();
            } else {
                cout << "you are going out of graph" << endl;
            }
        }
    } else if (command == '6') {
        T.printgraph();
    } else {
        cout << "wrong command!" << endl;
    }
}
void turtle::turnRight()
{
    direction++;
    if (direction > 3) {
        direction = 0;
    }
}
void turtle::turnLeft()
{
    direction--;
    if (direction < 0) {
        direction = 3;
    }
}
void turtle::nowdirection()
{
    if (direction == 0)
        cout << "direction:right" << endl;
    else if (direction == 1)
        cout << "direction:down" << endl;
    else if (direction == 2)
        cout << "direction:left" << endl;
    else
        cout << "direction:up" << endl;
}
bool turtle::moveable(int step)
{
    int x = position[0];
    int y = position[1];
    if (direction == 0) {
        x += step;
    } else if (direction == 1) {
        y += step;
    } else if (direction == 2) {
        x -= step;
    } else {
        y -= step;
    }
    if (x >= 0 && x < 20 && y >= 0 && y < 20)
        return true;
    else
        return false;
}
void turtle::ahead(int step, bool pen)
{
    int x = position[0];
    int y = position[1];
    if (direction == 0) {
        x += step;
        if (pen) {
            for (position[0]; position[0] <= x; position[0]++) {
                graph[position[0]][y] = '*';
            }
        }
        position[0] = x;
    } else if (direction == 1) {
        y += step;
        if (pen) {
            for (position[1]; position[1] <= y; position[1]++) {
                graph[x][position[1]] = '*';
            }
        }
        position[1] = y;
    } else if (direction == 2) {
        x -= step;
        if (pen) {
            for (position[0]; position[0] >= x; position[0]--) {
                graph[position[0]][y] = '*';
            }
        }
        position[0] = x;
    } else {
        y -= step;
        if (pen) {
            for (position[1]; position[1] >= y; position[1]--) {
                graph[x][position[1]] = '*';
            }
        }
        position[1] = y;
    }
}
void turtle::printPosition()
{
    cout << "position:(" << position[0] << "," << position[1] << ")" << endl;
}
void turtle::printgraph()
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout << setw(2) << graph[j][i];
        }
        cout << endl;
    }
    cout << endl;
}
