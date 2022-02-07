#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void judge(int* my_card)
{
    for (int i = 0; i < 5; i++) {
        cout << "card(" << my_card[i] << "): ";

        //
        if (my_card[i] / 13 == 0)
            cout << "C";
        else if (my_card[i] / 13 == 1)
            cout << "D";
        else if (my_card[i] / 13 == 2)
            cout << "H";
        else
            cout << "S";
        //

        if (my_card[i] % 13 >= 0 && my_card[i] % 13 <= 7)
            cout << my_card[i] % 13 + 2;
        else if (my_card[i] % 13 == 8)
            cout << "T";
        else if (my_card[i] % 13 == 9)
            cout << "J";
        else if (my_card[i] % 13 == 10)
            cout << "Q";
        else if (my_card[i] % 13 == 11)
            cout << "K";
        else
            cout << "A";

        cout << endl;
    }
}

int main()
{
    srand(time(NULL));
    int my_card[5];
    for (int i = 0; i < 5; i++) {
        my_card[i] = rand() % 52;
    }
    judge(my_card);

    return 0;
}
