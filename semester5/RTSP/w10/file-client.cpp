#include "mysocket.h"
#include "protocols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

void usage();

int main(int argc, char *argv[]) {
    FILE *fp;
    char dst[50];
    int name_len;
    char *file_name;
    int file_size;
    char data[SIZE];
    int block_size;

    // check argument & terminate
    if(argc != 4)
        usage();
    // Setup
    sprintf(dst, "%s:%s", argv[1], argv[2]);
    Endpoint ep(TCP | CLIENT, dst);
    name_len = strlen(argv[3]);
    file_name = (char *)malloc(name_len);
    strcpy(file_name, argv[3]);
    // file size
    fp = fopen(file_name, "rb");
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // send length of file name
    ep.Send(&name_len, sizeof(int), 0);
    // send file name
    ep.Send(file_name, name_len, 0);
    // send file size
    ep.Send(&file_size, sizeof(int), 0);
    // send data
    while((block_size = fread(data, sizeof(char), SIZE, fp)) > 0) {
        ep.Send(data, block_size, 0);
        printf("%s", data);
    }
    fclose(fp);

    return 0;
}

void usage() {
    printf("./client [host] [port] [file name]\n");
    exit(1);
}
