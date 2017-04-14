# This simple Makefile defines recipes for these two executables:
# on_asm.bin 	(built from the on.s assembly file) 
# on_c.bin 		(built from on.c C source file)

ARM = arm-none-eabi
CFLAGS = -Og -g -Wall -std=c99 -ffreestanding

all: on_asm.bin on_c.bin

on_asm.bin: on.s
	cpp -P on.s | $(ARM)-as -o on_asm.o
	$(ARM)-objcopy on_asm.o -O binary on_asm.bin
	$(ARM)-objdump -d on_asm.o > on_asm.list 

on_c.bin: on.c
	$(ARM)-gcc $(CFLAGS) -c on.c -o on_c.o
	$(ARM)-objcopy on_c.o -O binary on_c.bin
	$(ARM)-objdump on_c.o -d > on_c.list

clean: 
	rm -f *.list *.bin *.o