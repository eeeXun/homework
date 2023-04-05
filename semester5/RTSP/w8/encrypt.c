#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Usage: encrypt.exe [infile] [key] [outfile]\n");
        return 1;
    }
    FILE *ifp, *ofp;
    char c;
    int shift = atoi(argv[2]);
    char *inf = argv[1];
    char *ouf = argv[3];
    ifp = fopen(inf, "r");
    ofp = fopen(ouf, "w");
    while((c = fgetc(ifp)) != EOF) {
        if(c >= 97 && c <= 122)
            c -= 32;
        if(c >= 65 && c <= 90) {
            c += shift;
            if(c > 90)
                c = (c - 90) + 65;
        }
        fprintf(ofp, "%c", c);
    }
    fclose(ifp);
    fclose(ofp);

    return 0;
}