#include <iostream>
#include <string>
using namespace std;

class HugeInteger {
public:
    void input();
    void output();
    bool isEqualTo(HugeInteger);
    bool isGreaterThan(HugeInteger);
    HugeInteger add(HugeInteger);
    HugeInteger substract(HugeInteger);

private:
    string number, reverse;
    int len;
    bool ispositive;
};

int main()
{
    HugeInteger a, b, c, d;
    a.input();
    b.input();
    a.output();
    b.output();

    c = a.add(b);
    d = a.substract(b);
    c.output();
    d.output();

    return 0;
}

void HugeInteger::input()
{
    cin >> number;
    len = number.length();
    for (int i = 0; i < len; i++) {
        reverse += number[len - 1 - i];
    }
    ispositive = 1;
}
void HugeInteger::output()
{
    if (!ispositive)
        cout << "-";
    for (int i = reverse.length() - 1; i >= 0; i--) {
        cout << reverse[i];
    }
    cout << endl;
}
bool HugeInteger::isEqualTo(HugeInteger b)
{
    if (len == b.len) {
        for (int i = 0; i < len; i++) {
            if (number[i] != b.number[i])
                return 0;
        }
        return 1;
    } else
        return 0;
}
bool HugeInteger::isGreaterThan(HugeInteger b)
{
    if (len > b.len)
        return 1;
    else if (len < b.len)
        return 0;
    else {
        for (int i = 0; i < len; i++) {
            if (number[i] > b.number[i])
                return 1;
            else if (number[i] < b.number[i])
                return 0;
        }
        return 0;
    }
}
HugeInteger HugeInteger::add(HugeInteger b)
{
    bool carry = 0;
    char temp;
    int plen1, plen2;
    string n1, n2;
    HugeInteger plusnumber;
    plusnumber.ispositive = 1;
    if (len >= b.len) {
        plen1 = len;
        plen2 = b.len;
        n1 = reverse;
        n2 = b.reverse;
    } else {
        plen1 = b.len;
        plen2 = len;
        n1 = b.reverse;
        n2 = reverse;
    }
    for (int i = 0; i < plen2; i++) {
        plusnumber.reverse += n1[i] + n2[i] - 48;
        if (carry)
            plusnumber.reverse[i] += 1;
        if (plusnumber.reverse[i] > '9') {
            carry = 1;
            plusnumber.reverse[i] -= 10;
        } else
            carry = 0;
    }
    for (int i = plen2; i < plen1; i++) {
        plusnumber.reverse += n1[i];
        if (carry)
            plusnumber.reverse[i] += 1;
        if (plusnumber.reverse[i] > '9') {
            carry = 1;
            plusnumber.reverse[i] -= 10;
        } else
            carry = 0;
    }
    if (carry)
        plusnumber.reverse += '1';

    return plusnumber;
}
HugeInteger HugeInteger::substract(HugeInteger b)
{
    string n1, n2;
    bool borrow = 0;
    int mlen1, mlen2;
    HugeInteger minusnumber;
    if (this->isEqualTo(b)) {
        minusnumber.reverse = "0";
        minusnumber.ispositive = 1;
    } else {
        if (this->isGreaterThan(b)) {
            n1 = reverse;
            n2 = b.reverse;
            mlen1 = len;
            mlen2 = b.len;
            minusnumber.ispositive = 1;
        } else {
            n1 = b.reverse;
            n2 = reverse;
            mlen1 = b.len;
            mlen2 = len;
            minusnumber.ispositive = 0;
        }
        for (int i = 0; i < mlen2; i++) {
            minusnumber.reverse += n1[i] - n2[i] + 48;
            if (borrow)
                minusnumber.reverse[i] -= 1;
            if (minusnumber.reverse[i] < '0') {
                borrow = 1;
                minusnumber.reverse[i] += 10;
            } else
                borrow = 0;
        }
        for (int i = mlen2; i < mlen1; i++) {
            minusnumber.reverse += n1[i];
            if (borrow)
                minusnumber.reverse[i] -= 1;
            if (minusnumber.reverse[i] < '0') {
                borrow = 1;
                minusnumber.reverse[i] += 10;
            } else
                borrow = 0;
        }
    }

    return minusnumber;
}
