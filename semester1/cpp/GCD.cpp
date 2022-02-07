#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main()
{
    cout << "Please input two positive numbers -- ";
    int a, b, ans;
    cin >> a >> b;
    ans = gcd(a, b);
    cout << "GCD(" << a << "," << b << ") = " << ans;
}
