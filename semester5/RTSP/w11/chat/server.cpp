#include "mysocket.h"
#include "protocols.h"
#include "myScreen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
using namespace std;

#define LINE "+--------------------------------------------------------------------------------+"
#define INPUT "+                                                                                +"
MyScreen scr;
char screen[20][83];
void push_screen(string s, int from_loc);
void update_screen();

DWORD WINAPI recvThread(LPVOID lpParameter)
{
	string input;
	Endpoint& ep = (*(Endpoint*)lpParameter);
	while (true) {
		getline(cin, input);
		ep.Write(input);
		push_screen(input, 1);
		update_screen();
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
	for (int i = 0; i < 20; i++) {
		sprintf(screen[i], "|%80s|", " ");
	}
	update_screen();
	Endpoint ep(TCP | SERVER, dst);
	HANDLE myhandle = CreateThread(0, 0, recvThread, &ep, 0, 0);

	while (ep.Read(-20, buf) > 0) {
		if (buf == "oo") {
			push_screen("Over and Out", 0);
			update_screen();
			break;
		}
		else {
			push_screen(buf, 0);
			update_screen();
		}
		buf.clear();
	}
	CloseHandle(myhandle);

	return 0;
}

// send -> from_loc = 1
// recv -> from_loc = 0
void push_screen(string s, int from_loc)
{
	for (int i = 0; i < 19; i++) {
		strcpy(screen[i], screen[i + 1]);
	}
	if (from_loc)
		sprintf(screen[19], "|%80s|", s.c_str());
	else
		sprintf(screen[19], "|%-80s|", s.c_str());
}

void update_screen()
{
	scr.addstr(0, 0, LINE);
	for (int i = 0; i < 20; i++) {
		scr.addstr(i + 1, 0, screen[i]);
	}
	scr.addstr(21, 0, LINE);
	scr.addstr(22, 0, INPUT);
	scr.addstr(23, 0, LINE);
	scr.move(22, 1);
}