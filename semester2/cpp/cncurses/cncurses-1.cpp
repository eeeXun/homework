#include "wincursor.h"
#include <vector>
using std::vector;

int main()
{
    Screen myScreen;
    String q("Q", 10, 10);
    for (int row = 10; row >= 0; --row) {
        q.hide();
        q.setY(row);
        q.show();
        myScreen.Refresh();
        myScreen.sleep(1);
    }
    for (int row = 10; row <= 20; ++row) {
        q.hide();
        q.setX(row);
        q.show();
        myScreen.Refresh();
        myScreen.sleep(1);
    }
    for (int row = 0; row <= 10; ++row) {
        q.hide();
        q.setY(row);
        q.show();
        myScreen.Refresh();
        myScreen.sleep(1);
    }
    for (int row = 20; row >= 10; --row) {
        q.hide();
        q.setX(row);
        q.show();
        myScreen.Refresh();
        myScreen.sleep(1);
    }

    int c = myScreen.key();

    return 0;
}
