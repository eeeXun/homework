#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
    cout << "Please input an integer as the random seed -- ";
    int randseed;
    cin >> randseed;
    srand(randseed);
    int times[6] = { 0 };
    for (int i = 1; i <= 20; i++) {
        int point = rand() % 6;
        times[point]++;
    }
    for (int j = 1; j <= 6; j++) {
        cout << j << ": " << times[j - 1] << " ";
        for (int k = 1; k <= times[j - 1]; k++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}
