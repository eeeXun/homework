#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

void help();
void file_err(char *);
void snd_open(SNDFILE **, char *, SF_INFO *);

int main(int argc, char *argv[]) {
    SNDFILE *file;
    SF_INFO info;
    if(argc == 2) {
        snd_open(&file, argv[1], &info);
        printf("Artist: %s\n", sf_get_string(file, SF_STR_ARTIST));
        sf_close(file);
    } else if(argc == 3) {
        snd_open(&file, argv[1], &info);
        // read to buffer begin
        float *buffer;
        buffer = (float*)malloc(info.frames * info.channels * sizeof(float));
        sf_count_t nSample;
        nSample = sf_readf_float(file, buffer, info.frames);
        // read to buffer end
        sf_close(file);
        if(!(file = sf_open(argv[1], SFM_WRITE, &info))) {
            file_err(argv[1]);
            sf_close(file);
            exit(1);
        }
        sf_writef_float(file, buffer, nSample);
        sf_set_string(file, SF_STR_ARTIST, argv[2]);
        printf("Artist set to %s\n", argv[2]);
        sf_close(file);
    } else {
        help();
        exit(1);
    }

    return 0;
}

void help() {
    printf("Usage:\n");
    printf("`artist \"file\"`\t\t-> Show artist name\n");
    printf("`artist \"file\" \"name\"`\t-> Set artist name\n");
}

void file_err(char *file) {
    printf("Could not open file: %s\n", file);
    puts(sf_strerror(NULL));
}

void snd_open(SNDFILE **sndfile, char *file, SF_INFO *info) {
    if(!(*sndfile = sf_open(file, SFM_READ, info))) {
        file_err(file);
        sf_close(*sndfile);
        exit(1);
    }
}
