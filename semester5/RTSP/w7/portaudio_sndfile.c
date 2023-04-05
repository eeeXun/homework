#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sndfile.h>
#include <string.h>
#include "portaudio.h"
#define NUM_SECONDS   (5)
#define SAMPLE_RATE   (44100)
#define NUM_CHANNELS  (2)
#define FN "recorded.wav"

typedef struct
{
    int frame_index;
    float *buffer;
}
paTestData;

static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */
    paTestData *data = (paTestData*)userData;
    float *in = &data->buffer[data->frame_index * NUM_CHANNELS];
    float *out = (float*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = *in++;  /* left */
        if( NUM_CHANNELS == 2 ) *out++ = *in++;  /* right */

    }
    data->frame_index += framesPerBuffer;
    return paContinue;
}

/*******************************************************************/
static paTestData data;
int main(int argc, char *argv[])
{
    SNDFILE *file;
    SF_INFO info;
    char filename[80];
    if (argc == 2) {
        strcpy(filename, argv[1]);
        printf("Loading %s.\n", argv[1]);
    } else {
        strcpy(filename, FN);
        printf("Default filename is %s.\n", filename);
    }
    if(!(file = sf_open(filename, SFM_READ, &info))) {
        printf("Could not open file: %s\n", filename);
        puts(sf_strerror(NULL));
        sf_close(file);
        exit(1);
    }
    float *buffer;
    buffer = (float*)malloc(info.frames * info.channels * sizeof(float));
    sf_count_t nSample;
    nSample = sf_readf_float(file, buffer, info.frames);
    sf_close(file);
    data.buffer = buffer;
///////////////////////////////////////////////////////////////////////////////
    PaStream *stream;
    PaError err;

    printf("PortAudio Test: output sawtooth wave.\n");
    /* Initialize our data for use by callback. */
    data.frame_index = 0;
    /* Initialize library before making any other calls. */
    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paFloat32,  /* 32 bit floating point output */
                                SAMPLE_RATE,
                                sizeof(buffer),        /* frames per buffer */
                                patestCallback,
                                &data );
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    /* Sleep for several seconds. */
    Pa_Sleep(NUM_SECONDS*1000);

    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;
    Pa_Terminate();
    printf("Test finished.\n");
    return err;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occurred while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return err;
}
