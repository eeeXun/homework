#include "mysocket.h"
#include "protocols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

void usage();
void check_file_name(char **name);

int main(int argc, char *argv[]) {
    FILE *fp;
    char dst[50];
    int name_len;
    char *file_name;
    int file_size;
    char data[SIZE];
    int block_size;

    // check argument & terminate
    if(argc != 3)
        usage();
    // Setup
    sprintf(dst, "%s:%s", argv[1], argv[2]);
    Endpoint ep(TCP | SERVER, dst);

    // recv length of file name
    ep.Recv(&name_len, sizeof(int), 0);
    // recv file name
    file_name = (char *)malloc(name_len + 1);
    memset(file_name, 0, name_len + 1);
    ep.Recv(file_name, name_len, 0);
    check_file_name(&file_name);

    // open write file
    fp = fopen(file_name, "wb");
    // recv file size
    ep.Recv(&file_size, sizeof(int), 0);
    // recv & write data
    while((block_size = ep.Recv(data, SIZE, 0)))
        fwrite(data, sizeof(char), block_size, fp);
    // close
    fclose(fp);
    printf("Receive file: %s\n", file_name);
    printf("Size: %d\n", file_size);

    return 0;
}

void usage() {
    printf("./server [host] [port]\n");
    exit(1);
}

void check_file_name(char **name) {
    char illegal_parent[3] = "..";
    char illegal_win[3] = "\\";
    char illegal_unix[3] = "/";
    if((strstr(*name, illegal_parent) != NULL)
            || (strstr(*name, illegal_win) != NULL)
            || (strstr(*name, illegal_unix) != NULL)) {
        printf("Illegal file name: %s\n", *name);
        exit(1);
    }
}
