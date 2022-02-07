#include "cursor.h"
#include <string>
using std::string;

enum Directions { LEFT, RIGHT, UP, DOWN };

class MyString : public String {
public:
    MyString(string s, size_t row = 0, size_t col = 0)
        : String(s, row, col)
    {
    }
    void Move(Directions d)
    {
        hide();
        switch (d) {
        case Directions::LEFT:
            setX(this->getX() - 1);
            this->show();
            break;
        case Directions::RIGHT:
            setX(this->getX() + 1);
            this->show();
            break;
        case Directions::UP:
            setY(this->getY() + 1);
            this->show();
            break;
        case Directions::DOWN:
            setY(this->getY() - 1);
            this->show();
            break;
        }
        show();
    }
};

int main()
{
    Screen myScreen;
    MyString a("Q", 10, 10);
    a.show();
    int c = myScreen.key();
    while (c != 'q') {
        switch (c) {
        case 'h':
            a.Move(LEFT);
            myScreen.Refresh();
            myScreen.sleep(1);
            break;
        case 'l':
            a.Move(RIGHT);
            myScreen.Refresh();
            myScreen.sleep(1);
            break;
        case 'j':
            a.Move(DOWN);
            myScreen.Refresh();
            myScreen.sleep(1);
            break;
        case 'k':
            a.Move(UP);
            myScreen.Refresh();
            myScreen.sleep(1);
            break;
        }
        c = myScreen.key();
    }

    return 0;
}
