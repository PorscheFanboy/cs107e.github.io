# This simple Makefile defines recipe for 
# button.bin 	(built from button.c C source file)

ARM = arm-none-eabi
# take note of the -O<level> optimization setting
CFLAGS = -O0 -g -Wall -std=c99 -ffreestanding

all: button.bin

button.bin: button.c Makefile
	$(ARM)-gcc $(CFLAGS) button.c -c -o button.o
	$(ARM)-objcopy button.o -O binary button.bin
	$(ARM)-objdump button.o -d > button.list

clean: 
	rm -f *.list *.bin *.o