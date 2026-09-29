default:
	avr-gcc -Os -mmcu=atmega328p -c waveform.c
	avr-gcc -mmcu=atmega328p -mrelax -o waveform.elf waveform.o
	sudo avrdude -c arduino -p m328p -P /dev/ttyACM0 -U flash:w:waveform.elf:e
