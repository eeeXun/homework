#include "keypad.h"

char keypad()
{
    unsigned char key;
    for (char r = 0; r < 4; r++) {
        KEYPAD = ~(1 << r);
        key = KEYPAD & 0xF0;
        if (key != 0xF0) {
            for (char c = 0; c < 4; c++) {
                if (!(key & (0x10 << c))) {
                    return c * 4 + r;
                }
            }
        }
    }
    return 16;
}