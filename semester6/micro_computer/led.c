#include "led.h"

const unsigned char led[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x83, // 6
    0xF8, // 7
    0x80, // 8
    0x98, // 9
    0x08, // A (A.)
    0x00, // B (8.)
    0x46, // C (C.)
    0x40, // D (0.)
    0x06, // E (E.)
    0x0E, // F (F.)
};

void delay(unsigned short n)
{
    unsigned d1, d2;
    for (d1 = 0; d1 < 50; d1++) {
        for (d2 = 0; d2 < n; d2++)
            ;
    }
}

void display(unsigned short n)
{
    for (char c = 0; c < 4; c++) {
        if (c == 0) {
            D1 = 1;
            D2 = 1;
            D3 = 1;
            D4 = 0;
        } else if (c == 1) {
            D1 = 1;
            D2 = 1;
            D3 = 0;
            D4 = 1;
        } else if (c == 2) {
            D1 = 1;
            D2 = 0;
            D3 = 1;
            D4 = 1;
        } else {
            D1 = 0;
            D2 = 1;
            D3 = 1;
            D4 = 1;
        }
        LED = led[n % (1 << 4)];
        n = (n >> 4);
        delay(20);
    }
}