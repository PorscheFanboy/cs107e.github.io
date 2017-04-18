# This simple Makefile defines recipe for 
# button.bin 	(built from button.c C source file)

# take note of the -O<level> optimization setting
CFLAGS = -O2 -g -Wall -std=c99 -ffreestanding

all: button.bin

button.bin: button.c Makefile
	arm-none-eabi-gcc $(CFLAGS) button.c -c -o button.o
	arm-none-eabi-objcopy button.o -O binary button.bin
	arm-none-eabi-objdump button.o -d > button.list

install: button.bin
	rpi-install.py button.bin

clean: 
	rm -f *.list *.bin *.o