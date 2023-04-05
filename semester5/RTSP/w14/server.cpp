#define _CRT_SECURE_NO_WARNINGS
#include "mysocket.h"
#include "protocols.h"
#include <sndfile.h>
#include <stdio.h>
#include <windows.h>
#define BUFCOUNT 12
#define BUFFSIZE (1 << 10)
#define HOST "127.0.0.1"
#define PORT "5000"

struct Circular{
	float buffer[BUFCOUNT][BUFFSIZE];
	float buffer_tmp;
	int read_index;
	int write_index;
	int read_remain;
	int write_remain;
	int r_preceed;
	int r_w_equal;
} circular;

DWORD WINAPI sendThread(LPVOID lpParameter)
{
	Endpoint& ep = *((Endpoint*)lpParameter);
	int tmp_size;
	while (circular.write_remain > 0) {
		if (circular.r_preceed) {
			if (circular.write_remain >= BUFFSIZE)
				tmp_size = BUFFSIZE;
			else
				tmp_size = circular.write_remain;
			ep.Send(circular.buffer[circular.write_index], sizeof(float) * tmp_size, 0);
			circular.write_remain -= tmp_size;
			circular.write_index = (circular.write_index + 1) % BUFCOUNT;
			if (circular.write_index == circular.read_index) {
				circular.r_preceed = 0;
				circular.r_w_equal = 1;
			}
		}
		else {
			continue;
		}
	}

	return 0;
}

int main()
{
	char filename[80];
	char dst[80];
	printf("Which audio file to send?\n");
	scanf("%s", filename);
	sprintf(dst, "%s:%s", HOST, PORT);
	SNDFILE* file;
	SF_INFO info;
	if (!(file = sf_open(filename, SFM_READ, &info))) {
		printf("Could not open file: %s\n", filename);
		puts(sf_strerror(NULL));
		sf_close(file);
		exit(1);
	}

	printf("Listen on %s\n", dst);
	Endpoint ep(TCP | SERVER, dst);
	// read & send
	int tmp_size;
	circular.read_index = 0;
	circular.write_index = 0;
	circular.read_remain = info.frames * info.channels;
	circular.write_remain = info.frames * info.channels;
	circular.r_preceed = 0;
	circular.r_w_equal = 1;
	// send frames
	ep.Send(&info.frames, sizeof(int), 0);
	// send sample rate
	ep.Send(&info.samplerate, sizeof(int), 0);
	// send channels
	ep.Send(&info.channels, sizeof(int), 0);

	// send 
	HANDLE sendHandle = CreateThread(0, 0, sendThread, &ep, 0, 0);
	// read
	while (circular.read_remain > 0) {
		if ((!circular.r_preceed)
			|| (circular.r_preceed && !circular.r_w_equal)) {
			if (circular.read_index >= BUFFSIZE)
				tmp_size = BUFFSIZE;
			else
				tmp_size = circular.read_remain;
			sf_read_float(file, circular.buffer[circular.read_index], tmp_size);
			circular.read_remain -= tmp_size;
			circular.read_index = (circular.read_index + 1) % BUFCOUNT;
			circular.r_preceed = 1;
			if (circular.read_index == circular.write_index)
				circular.r_w_equal = 1;
		}
	}
	sf_close(file);
	CloseHandle(sendHandle);

	return 0;
}