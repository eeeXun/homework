#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include "mysocket.h"
#include "portaudio.h"
#include "protocols.h"
#include <windows.h>
#define BUFCOUNT 12
#define BUFFRAME 256
#define BUFFSIZE (1 << 10)
#define HOST "127.0.0.1"
#define NUM_SECONDS 5
#define PORT "5000"

struct Circular {
	float buffer[BUFCOUNT][BUFFSIZE];
	float buffer_tmp;
	int read_index;
	int write_index;
	int read_remain;
	int write_remain;
	int r_preceed;
	int r_w_equal;
} circular;

static int paCallback(const void* inputBuffer, void* outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void* userData)
{
	int* tmp_size = (int*)userData;
	float* out = (float*)outputBuffer;

	if (*tmp_size == BUFSIZ)
		out = circular.buffer[circular.write_index];
	else
		for (int i = 0; i < *tmp_size; i++)
			*out++ = circular.buffer[circular.write_index][i];

	return 0;
}

DWORD WINAPI recvThread(LPVOID lpParameter)
{
	Endpoint& ep = *((Endpoint*)lpParameter);
	int tmp_size;
	while (circular.read_remain > 0) {
		if ((!circular.r_preceed)
			|| (circular.r_preceed && !circular.r_w_equal)) {
			if (circular.read_index >= BUFFSIZE)
				tmp_size = BUFFSIZE;
			else
				tmp_size = circular.read_remain;
			ep.Recv(circular.buffer[circular.read_index], sizeof(float) * tmp_size, 0);
			circular.read_remain -= tmp_size;
			circular.read_index = (circular.read_index + 1) % BUFCOUNT;
			circular.r_preceed = 1;
			if (circular.read_index == circular.write_index)
				circular.r_w_equal = 1;
		}
	}

	return 0;
}

int main()
{
	char dst[80];
	sprintf(dst, "%s:%s", HOST, PORT);
	printf("Press any key to connect to %s\n", dst);
	_getch();

	int frames, samplerate, channels;
	Endpoint ep(TCP | CLIENT, dst);
	printf("Connect to %s\n", dst);
	ep.Recv(&frames, sizeof(int), 0);
	ep.Recv(&samplerate, sizeof(int), 0);
	ep.Recv(&channels, sizeof(int), 0);

	// init
	circular.read_index = 0;
	circular.write_index = 0;
	circular.read_remain = frames * channels;
	circular.write_remain = frames * channels;
	circular.r_preceed = 0;
	circular.r_w_equal = 1;
	// recv
	HANDLE recvHandle = CreateThread(0, 0, recvThread, &ep, 0, 0);
	// play
	PaStream* stream;
	PaError err;
	int tmp_size;
	while (circular.write_remain > 0) {
		if (circular.r_preceed) {
			if (circular.write_remain >= BUFFSIZE)
				tmp_size = BUFFSIZE;
			else
				tmp_size = circular.write_remain;

			err = Pa_Initialize();
			if (err != paNoError) goto error;

			err = Pa_OpenDefaultStream(&stream,
				0,				/* no input channels */
				channels,		/* stereo output */
				paFloat32,		/* 32 bit floating point output */
				samplerate,
				BUFFRAME,       /* frames per buffer */
				paCallback,
				&tmp_size);
			if (err != paNoError) goto error;

			err = Pa_StartStream(stream);
			if (err != paNoError) goto error;

			Pa_Sleep(NUM_SECONDS * 1000);

			err = Pa_StopStream(stream);
			if (err != paNoError) goto error;
			err = Pa_CloseStream(stream);
			if (err != paNoError) goto error;

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
	CloseHandle(recvHandle);

	return err;
error:
	Pa_Terminate();
	fprintf(stderr, "An error occurred while using the portaudio stream\n");
	fprintf(stderr, "Error number: %d\n", err);
	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
	return err;
	CloseHandle(recvHandle);

	return 0;
}