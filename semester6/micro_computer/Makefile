all: eOrgan-108321019.hex

keypad.rel: keypad.c keypad.h
	sdcc -c keypad.c keypad.rel
led.rel: led.c led.h
	sdcc -c led.c led.rel
myIO.lib: keypad.rel led.rel
	sdar -rs myIO.lib keypad.rel led.rel

eOrgan-108321019.hex: eOrgan-108321019.c myIO.lib
	sdcc eOrgan-108321019.c myIO.lib
	packihx eOrgan-108321019.ihx > eOrgan-108321019.hex

clean:
	del  *.rel *.asm *.lk *.lib *.map *.mem *.rst *.lst *.ihx *.rel *.sym *.hex