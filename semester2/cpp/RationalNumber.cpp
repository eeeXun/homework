#include <cmath>
#include <iostream>
using namespace std;

int GCD(int, int);

class Rational {
    friend ostream& operator<<(ostream&, Rational&);

public:
    Rational(int = 0, int = 1);
    Rational add(Rational);
    Rational substract(Rational);
    Rational multiple(Rational);
    Rational divide(Rational);
    void print();
    Rational operator+(Rational&);
    Rational operator-(Rational&);
    Rational operator*(Rational&);
    Rational operator/(Rational&);

private:
    int numerator, denominator;
};

int main()
{
    Rational a(1, 3);
    Rational b(1, 2);
    Rational c = a + b;
    Rational d = a - b;
    Rational e = c * a;
    Rational f = c / b;
    cout << c << ' ' << d << ' ' << e << ' ' << f << endl;

    return 0;
}

int GCD(int n, int d)
{
    if (n % d == 0)
        return d;
    if (d % n == 0)
        return n;
    if (n > d) {
        GCD(n % d, d);
    } else {
        GCD(n, d % n);
    }
}

Rational::Rational(int a, int b)
{
    numerator = a;
    denominator = b;
}
Rational Rational::add(Rational b)
{
    Rational temp;
    temp.numerator = numerator * b.denominator + b.numerator * denominator;
    temp.denominator = denominator * b.denominator;
    return temp;
}
Rational Rational::substract(Rational b)
{
    Rational temp;
    temp.numerator = numerator * b.denominator - b.numerator * denominator;
    temp.denominator = denominator * b.denominator;
    return temp;
}
Rational Rational::multiple(Rational b)
{
    Rational temp;
    temp.numerator = numerator * b.numerator;
    temp.denominator = denominator * b.denominator;
    return temp;
}
Rational Rational::divide(Rational b)
{
    Rational temp;
    temp.numerator = numerator * b.denominator;
    temp.denominator = denominator * b.numerator;
    return temp;
}
void Rational::print() { cout << numerator << '/' << denominator << endl; }
Rational Rational::operator+(Rational& b) { return this->add(b); }
Rational Rational::operator-(Rational& b) { return this->substract(b); }
Rational Rational::operator*(Rational& b) { return this->multiple(b); }
Rational Rational::operator/(Rational& b) { return this->divide(b); }
ostream& operator<<(ostream& output, Rational& a)
{
    int gcd = GCD(abs(a.numerator), abs(a.denominator));
    a.numerator /= gcd;
    a.denominator /= gcd;
    output << a.numerator << '/' << a.denominator;
    // return output;
}
