#include "mysocket.h"
#include "protocols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
using namespace std;

DWORD WINAPI recvThread(LPVOID lpParameter)
{
	string input;
	Endpoint& ep = (*(Endpoint*)lpParameter);
	while (true) {
		getline(cin, input);
		ep.Write(input);
		if (input == "oo")
			break;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	char dst[50];
	sprintf(dst, "%s:%s", argv[1], argv[2]);
	string buf;
	Endpoint ep(TCP | SERVER, dst);
	HANDLE myhandle = CreateThread(0, 0, recvThread, &ep, 0, 0);

	while (ep.Read(-20, buf) > 0) {
		if (buf == "oo") {
			printf("Over and Out\n");
			break;
		}
		else {
			printf("%s\n", buf.c_str());
		}
		buf.clear();
	}
	CloseHandle(myhandle);

	return 0;
}