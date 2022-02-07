#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string filename;
    cout << "Filename?";
    cin >> filename;

    ifstream infile(filename.c_str());
    string name;
    float height, weight, bmi;
    float maxw = 0, minw = 200, maxh = 0, minh = 200, maxb = 0, minb = 200;
    while (infile >> name >> height >> weight) {
        bmi = weight / ((height / 100) * (height / 100));
        if (height > maxh)
            maxh = height;
        if (height < minh)
            minh = height;
        if (weight > maxw)
            maxw = weight;
        if (weight < minw)
            minw = weight;
        if (bmi > maxb)
            maxb = bmi;
        if (bmi < minb)
            minb = bmi;
    }
    cout << "MAX"
         << "    " << maxh << "    " << maxw << "    " << maxb << endl;
    cout << "Min"
         << "    " << minh << "    " << minw << "    " << minb << endl;
    infile.close();

    return 0;
}