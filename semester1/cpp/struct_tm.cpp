#include <ctime>
#include <iostream>
using namespace std;

void input(tm* p)
{
    cout << "Year? ";
    cin >> p->tm_year;
    p->tm_year -= 1900;
    cout << "Month? ";
    cin >> p->tm_mon;
    p->tm_mon--;
    cout << "Date? ";
    cin >> p->tm_mday;
    cout << "Hour? ";
    cin >> p->tm_hour;
    cout << "Minute? ";
    cin >> p->tm_min;
    cout << "Second? ";
    cin >> p->tm_sec;
}

int main()
{
    tm a;
    tm* p = &a;
    input(p);
    mktime(p);
    cout << "You checked out the book on " << asctime(p);
    time_t Deadline = mktime(p) + 86400 * 45;
    time_t* pp = &Deadline;
    tm* deadline = gmtime(pp);
    char k[80];
    strftime(k, 80, "%A, %B %d, %Y", deadline);
    cout << "You should return it in 45 days, so the due date is " << k;
}
