#include "mysocket.h"
#include "protocols.h"
#include "myScreen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include "portaudio.h"
#define LINE "+-------------------------------------------------------------------------------------+"
#define INPUT "+                                                                                     +"
#define PKG_SIZE (20)
using namespace std;

typedef float SAMPLE;
#define NUM_CHANNELS    (2)
#define NUM_SECONDS     (5)
#define SAMPLE_RATE  (44100)
#define MAX_FRAME_INDEX (NUM_SECONDS * SAMPLE_RATE)
#define FRAMES_PER_BUFFER (512)
#define SAMPLE_SILENCE  (0.0f)
#define louder (5)
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_BYTES (NUM_CHANNELS * NUM_SECONDS * SAMPLE_RATE * sizeof(SAMPLE))

MyScreen scr;
char prompt[90];
char screen[PKG_SIZE][90];
struct paData {
	int frameIndex;
	SAMPLE* recordedSamples;
};
struct Package {
	paData data;
	char title[90];
	bool read;
};
Package package[PKG_SIZE];
int pkg_index;
string get_substr(string s);
void push_pkg(Package p, SAMPLE* s);
void delete_pkg(int num);
void set_pkg_screen(int i);
void set_prompt(string s);
void update_screen();

static int recordCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData);
static int playCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData);

DWORD WINAPI recvThread(LPVOID lpParameter)
{
	Package p;
	SAMPLE* s;
	s = (SAMPLE*)malloc(SAMPLE_BYTES);
	Endpoint& ep = (*(Endpoint*)lpParameter);
	/*for (int i = 0; i < PKG_SIZE; i++) {
		package[i].data.recordedSamples = (SAMPLE*)malloc(SAMPLE_BYTES);
	}*/
	while (ep.Recv(&p, sizeof(p), 0) > 0) {
		if (strcmp(p.title, "oo") == 0) {
			set_prompt("Over and Out");
			break;
		}
		else {
			ep.Recv(s, SAMPLE_BYTES, 0);
			push_pkg(p, s);
			//push_pkg(p);
			//ep.Recv(s, SAMPLE_BYTES, 0);
			//package[pkg_index - 1].data.recordedSamples = s;
			//ep.Recv(package[pkg_index - 1].data.recordedSamples, SAMPLE_BYTES, 0);
			update_screen();
		}
	}
	ep.Close();

	exit(0);
}

int main(int argc, char* argv[])
{
	pkg_index = 0;
	char dst[50];
	sprintf(dst, "%s:%s", argv[1], argv[2]);
	string buf;
	// portaudio init
	PaStream*           stream;
	PaError             err = paNoError;
	PaStreamParameters  inputParameters, outputParameters;

	for (int i = 0; i < PKG_SIZE; i++) {
		sprintf(screen[i], "| %2d: %-80s|", i, " ");
	}

	set_prompt("Run any command");

	Endpoint ep(TCP | SERVER, dst);
	HANDLE myhandle = CreateThread(0, 0, recvThread, &ep, 0, 0);

	string input;
	int num;
	Package p;
	paData d;
	d.recordedSamples = (SAMPLE*)malloc(SAMPLE_BYTES);
	// pa parameter start
	err = Pa_Initialize();
	if (err != paNoError) goto done;

	inputParameters.device = Pa_GetDefaultInputDevice();
	if (inputParameters.device == paNoDevice) {
		fprintf(stderr, "Error: No default input device.\n");
		goto done;
	}
	inputParameters.channelCount = NUM_CHANNELS;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	outputParameters.device = Pa_GetDefaultOutputDevice();
	if (outputParameters.device == paNoDevice) {
		fprintf(stderr, "Error: No default output device.\n");
		goto done;
	}
	outputParameters.channelCount = NUM_CHANNELS;
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	// pa parameter end
	while (true) {
		getline(cin, input);
		if (input == "oo") {
			strcpy(p.title, "oo");
			ep.Send(&p, sizeof(Package), 0);
			set_prompt("Over and Out!");
			break;
		}
		else if (input.at(0) == 'r') {
			num = stoi(get_substr(input));
			if (num >= pkg_index) {
				set_prompt("Read out of range: " + get_substr(input));
			}
			else {
				set_prompt("Playing...");
				package[num].data.frameIndex = 0;
				err = Pa_OpenStream(
					&stream,
					NULL, // no input
					&outputParameters,
					SAMPLE_RATE,
					FRAMES_PER_BUFFER,
					paClipOff,     // we won't output out of range samples so don't bother clipping them
					playCallback,
					&package[num].data);
				if (err != paNoError) goto done;

				if (stream)
				{
					err = Pa_StartStream(stream);
					if (err != paNoError) goto done;

					while ((err = Pa_IsStreamActive(stream)) == 1) Pa_Sleep(100);
					if (err < 0) goto done;

					err = Pa_CloseStream(stream);
					if (err != paNoError) goto done;
				}
				package[num].read = TRUE;
				set_pkg_screen(num);
				set_prompt("Play over!");
			}
		}
		else if (input.at(0) == 's') {
			set_prompt("Recording...");
			strcpy(p.title, get_substr(input).c_str());
			d.frameIndex = 0;

			err = Pa_OpenStream(
				&stream,
				&inputParameters,
				NULL,                  // &outputParameters
				SAMPLE_RATE,
				FRAMES_PER_BUFFER,
				paClipOff,      // we won't output out of range samples so don't bother clipping them
				recordCallback,
				&d);
			if (err != paNoError) goto done;

			err = Pa_StartStream(stream);
			if (err != paNoError) goto done;

			while ((err = Pa_IsStreamActive(stream)) == 1)
			{
				Pa_Sleep(1000);
			}
			if (err < 0) goto done;
			ep.Send(&p, sizeof(p), 0);
			ep.Send(d.recordedSamples, SAMPLE_BYTES, 0);
			set_prompt("Message transmitted!");
		}
		else if (input.at(0) == 'd') {
			num = stoi(get_substr(input));
			if (num >= pkg_index) {
				set_prompt("Delete out of range: " + get_substr(input));
			}
			else {
				delete_pkg(num);
				set_prompt("Package deleted!");
			}
		}
		else {
			set_prompt("Unknow command: " + input);
		}
	}
	CloseHandle(myhandle);

	return 0;
done:
	Pa_Terminate();
	if (err != paNoError)
	{
		fprintf(stderr, "An error occurred while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		err = 1;          // Always return 0 or 1, but no other return codes.
	}
	return err;
}

string get_substr(string s)
{
	return s.substr(2, s.length() - 2);
}

void push_pkg(Package p, SAMPLE* s)
{
	p.read = FALSE;
	if (pkg_index == PKG_SIZE) {
		for (int i = 0; i < PKG_SIZE - 1; i++) {
			package[i] = package[i + 1];
			set_pkg_screen(i);
		}
		package[PKG_SIZE - 1] = p;
		//package[PKG_SIZE - 1].data.recordedSamples = s;
		for (int i = 0; i < NUM_CHANNELS * MAX_FRAME_INDEX; i++) {
			package[PKG_SIZE - 1].data.recordedSamples[i] = s[i];
		}
		set_pkg_screen(PKG_SIZE - 1);
	}
	else {
		package[pkg_index] = p;
		package[pkg_index].data.recordedSamples = (SAMPLE*)malloc(SAMPLE_BYTES);
		//package[pkg_index].data.recordedSamples = s;
		for (int i = 0; i < NUM_CHANNELS * MAX_FRAME_INDEX; i++) {
			package[pkg_index].data.recordedSamples[i] = s[i];
		}
		set_pkg_screen(pkg_index);
		pkg_index++;
	}
}

void delete_pkg(int num)
{
	for (int i = num; i < pkg_index; i++) {
		package[i] = package[i + 1];
		set_pkg_screen(i);
	}
	pkg_index--;
	sprintf(screen[pkg_index], "| %2d: %-80s|", pkg_index, " ");
}

void update_screen()
{
	scr.addstr(0, 0, LINE);
	scr.addstr(1, 0, prompt);
	scr.addstr(2, 0, LINE);
	for (int i = 0; i < PKG_SIZE; i++) {
		scr.addstr(i + 3, 0, screen[i]);
	}
	/*
	scr.addstr(23, 0, LINE);
	scr.addstr(24, 0, INPUT);
	scr.addstr(25, 0, LINE);
	scr.move(24, 1);
	*/
	scr.addstr(PKG_SIZE + 3, 0, LINE);
	scr.addstr(PKG_SIZE + 4, 0, INPUT);
	scr.addstr(PKG_SIZE + 5, 0, LINE);
	scr.move(PKG_SIZE + 4, 1);
}

void set_pkg_screen(int i)
{
	sprintf(screen[i], "|%s%2d: %-80s|", package[i].read ? " " : "*", i, package[i].title);
}

void set_prompt(string s)
{
	sprintf(prompt, "|prompt:   %75s|", s.c_str());
	update_screen();
}

static int recordCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData)
{
	paData *data = (paData*)userData;
	const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
	SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	long framesToCalc;
	long i;
	int finished;
	unsigned long framesLeft = MAX_FRAME_INDEX - data->frameIndex;

	(void)outputBuffer; /* Prevent unused variable warnings. */
	(void)timeInfo;
	(void)statusFlags;
	(void)userData;

	if (framesLeft < framesPerBuffer)
	{
		framesToCalc = framesLeft;
		finished = paComplete;
	}
	else
	{
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}

	if (inputBuffer == NULL)
	{
		for (i = 0; i < framesToCalc; i++)
		{
			*wptr++ = SAMPLE_SILENCE;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = SAMPLE_SILENCE;  /* right */
		}
	}
	else
	{
		for (i = 0; i < framesToCalc; i++)
		{
			*wptr++ = *rptr++;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
		}
	}
	data->frameIndex += framesToCalc;
	return finished;
}

static int playCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData)
{
	paData *data = (paData*)userData;
	SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	SAMPLE *wptr = (SAMPLE*)outputBuffer;
	unsigned int i;
	int finished;
	unsigned int framesLeft = MAX_FRAME_INDEX - data->frameIndex;

	(void)inputBuffer; /* Prevent unused variable warnings. */
	(void)timeInfo;
	(void)statusFlags;
	(void)userData;

	if (framesLeft < framesPerBuffer)
	{
		/* final buffer... */
		for (i = 0; i < framesLeft; i++)
		{
			*wptr++ = *rptr++;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
		}
		for (; i < framesPerBuffer; i++)
		{
			*wptr++ = 0;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = 0;  /* right */
		}
		data->frameIndex += framesLeft;
		finished = paComplete;
	}
	else
	{
		for (i = 0; i < framesPerBuffer; i++)
		{
			*wptr++ = (*rptr++) * louder;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = (*rptr++) * louder;  /* right */
		}
		data->frameIndex += framesPerBuffer;
		finished = paContinue;
	}
	return finished;
}