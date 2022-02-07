#include <iostream>
#include <map>
#include <string>
using namespace std;

int GCD(int, int);

int main()
{
    typedef map<string, int> countrycount;
    countrycount pairs;
    string key;
    countrycount::iterator i;
    int numerator, denominator, gcd;
    int position_backlash;
    while (cin >> key) {
        position_backlash = key.find("/");
        numerator = stoi(key.substr(0, position_backlash));
        denominator = stoi(key.substr(position_backlash + 1, key.length()));
        gcd = GCD(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        key = to_string(numerator) + "/" + to_string(denominator);
        i = pairs.find(key);
        if (i == pairs.end())
            pairs[key] = 1;
        else
            pairs[key] += 1;
    }
    for (i = pairs.begin(); i != pairs.end(); i++)
        cout << i->first << " * " << i->second << endl;
}

int GCD(int a, int b)
{
    if (a % b != 0)
        return GCD(b, a % b);
    else
        return b;
}