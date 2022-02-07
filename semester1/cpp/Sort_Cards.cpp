#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void judge(int* my_card)
{
    for (int i = 0; i < 13; i++) {
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

        cout << " ";
    }
    cout << endl;
}

int bridge(int a, int b)
{
    if (a > b)
        return 1;
    else
        return 0;
}

int big2(int a, int b)
{
    if (a % 13 == 0 && b % 13 != 0)
        return 1;
    else if (a % 13 == 0 && b % 13 == 0) {
        if (a / 13 > b / 13)
            return 1;
        else
            return 0;
    } else if (a % 13 > b % 13 && b % 13 != 0)
        return 1;
    else if (a % 13 == b % 13) {
        if (a / 13 > b / 13)
            return 1;
        else
            return 0;
    } else
        return 0;
}

void exchange(int* my_card, int (*pcomp)(int, int))
{
    int temp;
    for (int i = 0; i < 12; i++) {
        for (int j = i + 1; j < 13; j++) {
            if (pcomp(my_card[i], my_card[j]) == 1) {
                temp = my_card[i];
                my_card[i] = my_card[j];
                my_card[j] = temp;
            }
        }
    }
    judge(my_card);
}

int main()
{
    srand(time(NULL));
    int my_card[13];
    for (int i = 0; i < 13; i++) {
        my_card[i] = rand() % 52;
    }
    judge(my_card);
    cout << "===== Sorted by bridge order =====" << endl;
    exchange(my_card, bridge);
    cout << "===== Sorted by Big2 order =====" << endl;
    exchange(my_card, big2);

    return 0;
}
