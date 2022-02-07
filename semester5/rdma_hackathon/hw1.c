#include <arpa/inet.h> // inet_pton
#include <netinet/in.h> // sockaddr_in
#include <stdio.h>
#include <stdlib.h> // atoi
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h> // close
#define PORT 8000
#define KB 1 << 10

void usage(char*);
int server(int);
int client(char*, int);

int main(int argc, char* argv[])
{
    int ch, port = PORT;
    char* IP;
    int serverMode = 0, clientMode = 0, portFlag = 0;
    while ((ch = getopt(argc, argv, "hsc:p:")) != -1) {
        switch (ch) {
        case 'h':
            usage(argv[0]);
            return 0;
        case 's':
            serverMode = 1;
            break;
        case 'c':
            IP = optarg;
            clientMode = 1;
            break;
        case 'p':
            port = atoi(optarg);
            portFlag = 1;
            break;
        }
    }

    if (serverMode) {
        server(port);
    } else if (clientMode) {
        client(IP, port);
    } else {
        usage(argv[0]);
        return -1;
    }

    return 0;
}

void usage(char* file)
{
    printf("Synopsis: %s { -s | -c server } [-p port]\n", file);
    printf("Default port: %d\n", PORT);
}

int server(int port)
{
    int serverSock, newsockfd;
    struct sockaddr_in addrport;
    int addrlen = sizeof(addrport);

    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    addrport.sin_family = AF_INET;
    // automatically be filled with current host's IP address
    addrport.sin_addr.s_addr = INADDR_ANY;
    // set port number
    addrport.sin_port = htons(port);

    // bind
    if (bind(serverSock, (struct sockaddr*)&addrport, addrlen) < 0) {
        printf("%s\n", "bind failed");
        return -1;
    }
    // listen
    if (listen(serverSock, 3) < 0) {
        printf("%s\n", "listen failed");
        return -1;
    }
    // accept
    if ((newsockfd = accept(
             serverSock, (struct sockaddr*)&addrport, (socklen_t*)&addrlen))
        < 0) {
        printf("%s\n", "accept failed");
        return -1;
    }
    int MB = 1 << 20;
    char buffer[MB];
    for (int i = 0; i < 11; i++)
        recv(newsockfd, buffer, MB, 0);

    close(serverSock);
    return 0;
}

int client(char* serverIP, int port)
{
    int clientSock;
    struct sockaddr_in server_addrport;
    int addrlen = sizeof(server_addrport);
    struct timeval t1, t2;
    struct timezone tz;
    int delta, udelta;

    clientSock = socket(AF_INET, SOCK_STREAM, 0);
    server_addrport.sin_family = AF_INET;
    server_addrport.sin_port = htons(PORT);
    if (inet_pton(AF_INET, serverIP, &server_addrport.sin_addr) <= 0) {
        printf("%s\n", "Invalid address");
        return -1;
    }
    /* connect */
    if ((connect(clientSock, (struct sockaddr*)&server_addrport, addrlen))
        < 0) {
        printf("%s\n", "Connect error");
        return -1;
    }

    /* send */
    int pkg_size = KB;
    int MB = 1 << 20;
    double throughput, timepass;
    for (int i = 0; i < 11; i++) {
        char buffer[pkg_size];
        gettimeofday(&t1, &tz);
        send(clientSock, buffer, pkg_size, 0);
        gettimeofday(&t2, &tz);

        delta = t2.tv_sec - t1.tv_sec;
        udelta = t2.tv_usec - t1.tv_usec;
        if (udelta < 0) {
            delta--;
            udelta += 1000000;
        }

        timepass = delta + (double)udelta / 1000000;
        throughput = (double)pkg_size / timepass;
        printf("%d\t%lf\tMB/Sec\t\n", pkg_size, throughput / (double)MB);
        pkg_size *= 2;
    }
    close(clientSock);
    return 0;
}
