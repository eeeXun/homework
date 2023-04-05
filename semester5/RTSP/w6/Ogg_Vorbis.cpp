/* If this program fails to run successfully,    try to compile it with "Release" mode. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sndfile.h>
#define FN              "../wave_homework/recorded.wav"
#define OFN				"out.ogg"

int main() {
	SNDFILE *infile;
	SNDFILE *outfile;
	SF_INFO sfinfo;
	memset(&sfinfo, 0, sizeof(sfinfo));

	if (!(infile = sf_open(FN, SFM_READ, &sfinfo))) {
		printf("Error : could not open file : %s\n", FN);
		puts(sf_strerror(NULL));
		exit(1);
	}
	printf("%lld %d %d 0x%x\n",
		sfinfo.frames, sfinfo.samplerate, sfinfo.channels, sfinfo.format);
	float* buffer;
	buffer = (float*)malloc(sfinfo.frames*sfinfo.channels * sizeof(float));
	sf_count_t nSample;
	nSample = sf_readf_float(infile, buffer, sfinfo.frames);

	sfinfo.format = SF_FORMAT_OGG | SF_FORMAT_VORBIS;
	if (!sf_format_check(&sfinfo))
	{
		sf_close(infile);
		printf("Invalid encoding\n");
		return -1;
	};
	if (!(outfile = sf_open(OFN, SFM_WRITE, &sfinfo)))
	{
		printf("Error : could not open file : %s\n", OFN);
		puts(sf_strerror(NULL));
		exit(1);
	};
	nSample = sf_writef_float(outfile, buffer, nSample);
	printf("%lld samples written.\n", nSample);
	free(buffer);
	sf_close(outfile);
	sf_close(infile);
	printf("ok\n");
	return 0;
}