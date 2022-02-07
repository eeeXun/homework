#include <iostream>

class turtle {
public:
    turtle();
    void checkcommand(char command, bool& pen, turtle& T);
    void turnRight();
    void turnLeft();
    void nowdirection();
    bool moveable(int step);
    void ahead(int step, bool pen);
    void printPosition();
    void printgraph();

private:
    char graph[20][20];
    int direction;
    int position[2];
};
