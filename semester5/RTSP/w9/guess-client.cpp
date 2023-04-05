#include <iostream>
#include "protocols.h"
#include "mysocket.h"
using namespace std;

int main() {
    string buf;
    Endpoint ep(TCP | CLIENT, "127.0.0.1", "5000");
    ep.Read(-40, buf);
    cout << buf << endl;
    buf.clear();
    while(true) {
        cin >> buf;
        ep.Write(buf);
        buf.clear();
        ep.Read(-40, buf);
        cout << buf << endl;
        if(buf == "Correct")
            break;
    }
    return 0;
}
