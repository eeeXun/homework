#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2 && argc != 3) {
        printf("Usage: show.exe [infile]\n");
        printf("Usage: show.exe [infile] [key]\n");
        return 1;
    }
    FILE *ifp;
    char c;
    int shift = atoi(argv[2]);
    char *inf = argv[1];
    ifp = fopen(inf, "r");
    while((c = fgetc(ifp)) != EOF) {
        if(argc == 3) {
            if(c >= 65 && c <= 90) {
                c -= shift;
                if(c < 65)
                    c = 90 - (65 - c);
            }
        }
        printf("%c", c);
    }
    fclose(ifp);

    return 0;
}