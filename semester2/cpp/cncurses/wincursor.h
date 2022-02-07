#include <Winbase.h>
#include <Windows.h>
#include <curses.h>
#include <string>
using std::string;

class Screen {
public:
    Screen();
    ~Screen();
    int key();
    int Refresh(void);
    void sleep(unsigned int seconds);
    void setTimeOut(int delay);

private:
    WINDOW* win;
};

class String {
public:
    String(string s, size_t row = 0, size_t col = 0);
    void show() const;
    void hide() const;
    unsigned short getY();
    unsigned short getX();
    void setY(unsigned short row);
    void setX(unsigned short col);
    bool outOfBoundary() const;

private:
    string text;
    short y;
    short x;
};

class Timestamp {
public:
    Timestamp();
    Timestamp(WORD tv_sec, WORD tv_usec);
    WORD getSec();
    WORD getUSec();
    double operator-(const Timestamp& t);

private:
    WORD sec;
    WORD usec;
};
