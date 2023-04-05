#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    char fn[20];
    if (argc == 2)
        strcpy(fn, argv[1]);
    FILE *fp = fopen(fn, "rb");
    if (!fp) {
        printf("Error: %d\n", errno);
        if (errno == 2)
            printf("Can't find the file: %s\n", fn);
        return errno;
    }
    fseek(fp, 0L, SEEK_END);
    int length = ftell(fp);
    rewind(fp);
    char tmp;
    char dot = '.';
    char out[20];
    for(int i = 0; i < length; i++) {
        fread(&tmp, sizeof(tmp), 1, fp);
        if(i % 16 == 0)
            printf("\n%.6x\t%.2x ", i, tmp);
        else if((i + 1) % 8 == 0)
            printf("%.2x   ", tmp);
        else
            printf("%.2x ", tmp);
        // store content
        if(tmp >= 32 && tmp <= 127)
            strncat(out, &tmp, 1);
        else
            strncat(out, &dot, 1);
        // show content
        if((i + 1) % 16 == 0) {
            printf("\t%s", out);
            memset(out, 0, sizeof(out));
        } else if(i == (length -1)) {
            for(int j = 0; j < 16 - ((i+1) % 16); j++) {
                printf("   ");
            }
            if ((i+1) % 16 < 9)
                printf("   ");
            printf("\t%s", out);
        }
    }
    fclose(fp);
    return 0;
}
