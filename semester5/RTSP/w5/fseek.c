#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char name[10];
    unsigned char height;
    unsigned char weight;
} Student;

int main(int argc, char* argv[])
{
    Student s;
    Student ninja = {"Ninja", 160, 50};

    char fn[20];
    if (argc == 2)
        strcpy(fn, argv[1]);
    FILE *fp = fopen(fn, "r+b");
    if (!fp) {
        printf("Error: %d\n", errno);
        if (errno == 2)
            printf("Can't find the file: %s\n", fn);
        return errno;
    }
    while(fread(&s, sizeof(s), 1, fp)) {
        if(strcmp(s.name, "November") == 0) {
            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&ninja, sizeof(ninja), 1, fp);
        }
    };

    return 0;
}
