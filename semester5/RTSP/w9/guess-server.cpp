#include <iostream>
#include <random>
#include <cstring>
#include <ctime>
#include "protocols.h"
#include "mysocket.h"
using namespace std;

int main() {
    srand(time(NULL));
    string buf;
    int n = rand() % 100 + 1;
    cout << n << endl;
    char guess_str[3];
    int guess_n;
    Endpoint ep(TCP | SERVER, "127.0.0.1", "5000");
    ep.Write("Guess an integer between 1 and 100");
    while(true) {
        buf.clear();
        ep.Read(-20, buf);
        strcpy(guess_str, buf.c_str());
        guess_n = atoi(guess_str);
        if(guess_n != n) {
            if(guess_n > n)
                ep.Write("Too large");
            else
                ep.Write("Too small");
        } else {
            ep.Write("Correct");
            break;
        }
    }
    return 0;
}
