#include "keypad.h"
#include "led.h"
#include <8051.h>
#define SPEAKER P1_7
#define TONE_SIZE 12
#define RECORD_SIZE 100
#define BEAT_CLOCK 15536 // 0.05s

char key, speaker_on = 0;
unsigned short current_tone;
__xdata struct RECORD {
    char index;
    unsigned short tone[RECORD_SIZE];
    // increment (record times)
    unsigned char times[RECORD_SIZE];
} record;
__xdata struct PLAY {
    char index;
    // decrement (play times)
    unsigned char times;
} play;

const unsigned short tone_freq[TONE_SIZE] = {
    262, // C
    277, // C#
    294, // D
    311, // D#
    330, // E
    349, // F
    370, // F#
    392, // G
    415, // G#
    440, // A
    466, // A#
    494, // B
};
unsigned short tone[TONE_SIZE];

// 0 for init state
// 1 for recording
// 2 for play recording
char mode = 0;

// 0 for normal
// 1 for high 1
// 2 for high 2
// 3 for high 3
// 4 for high 4
char tone_mode = 0;

// first digit for mode
// second digit for tone_mode (0 for init)
// third & forth digit for what key pressing
unsigned short state = 0x0000;

void reset();
void add_state(char n);
void update_state_mode();
void update_state_tone_mode();
void update_tone();

void main()
{
    /////////////////////////////////// init ///////////////////////////////////
    // M0 on
    TMOD = 0x11;
    // TR0 on
    TCON = 0x50;
    // EA, ET0, ET1 on
    EA = 1;
    ET0 = 1;
    ET1 = 1;
    reset();
    /////////////////////////////////// init ///////////////////////////////////
    while (1) {
        key = keypad();
        if (key < 16) {
            if (key == 0) {
                // reset
                reset();
            } else if (mode != 2 && key >= 1 && key <= 0xC) {
                // not accept key while playing (mode 2)
                // play sound & start recording

                // recording begin
                if (mode == 0) {
                    record.index = 0;
                    mode = 1;
                    update_state_mode();
                } else {
                    record.index++;
                }
                record.times[record.index] = 0;
                record.tone[record.index] = tone[key - 1];
                // recording end

                current_tone = tone[key - 1];
                speaker_on = 1;
                add_state(key);
            } else if (key == 0xD) {
                // lower freq
                if (tone_mode > 0) {
                    tone_mode--;
                    update_tone();
                }
            } else if (key == 0xE) {
                // higher freq
                if (tone_mode < 4) {
                    tone_mode++;
                    update_tone();
                }
            } else if (key == 0xF) {
                // play record mode
                play.index = 0;
                play.times = record.times[play.index];
                mode = 2;
                update_state_mode();
            }
            // debounce
            while (keypad() < 16)
                display(state);
            if (mode == 1 && speaker_on) {
                // when recording, you record a sound, then release
                // which means that next step is no sound
                // tone = 0 for not playing sound
                speaker_on = 0;
                record.index++;
                record.times[record.index] = 0;
                record.tone[record.index] = 0;
            }
        }
        display(state);
    }
}

void reset()
{
    mode = 0;
    tone_mode = 0;
    state = 0x0000;
    update_tone();
    record.index = 0;
    record.times[record.index] = 0;
    speaker_on = 0;
}

void add_state(char n)
{
    // add newly income key press & shift orig key left
    state = (0xFF00 & state) + (0x00FF & (state << 4)) + n;
}

void update_state_mode()
{
    state = (0x0FFF & state) + (mode << 12);
}

void update_state_tone_mode()
{
    state = (0xF0FF & state) + (tone_mode << 8);
}

void update_tone()
{
    for (char i = 0; i < TONE_SIZE; i++) {
        tone[i] = 65536 - 1000000 / (2 * (tone_freq[i]) << (tone_mode));
    }
    update_state_tone_mode();
}

void tone_isr(void) __interrupt(1) __using(1)
{
    TH0 = current_tone >> 8;
    TL0 = current_tone & 0xFF;
    if (speaker_on)
        SPEAKER = !SPEAKER;
}

void beat_isr(void) __interrupt(3) __using(3)
{
    TH1 = BEAT_CLOCK >> 8;
    TL1 = BEAT_CLOCK & 0xFF;
    if (mode == 1) {
        record.times[record.index]++;
    } else if (mode == 2) {
        if (play.times == 0 && play.index >= record.index) {
            // no times to play & no next record
            // return to init mode
            speaker_on = 0;
            mode = 0;
            update_state_mode();
            return;
        } else if (play.times == 0 && play.index < record.index) {
            // no times to play, but exist next record
            play.index++;
            play.times = record.times[play.index];
        }

        // if recording (0), turn off speaker
        if (record.tone[play.index] == 0) {
            speaker_on = 0;
        } else {
            current_tone = record.tone[play.index];
            speaker_on = 1;
        }

        play.times--;
    }
}
