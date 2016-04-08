ARM = arm-none-eabi

CFLAGS = -Og -nostdlib -nostartfiles -ffreestanding

on.bin: on.c Makefile
	$(ARM)-gcc $(CFLAGS) on.c -o on.o
	$(ARM)-objcopy on.o -O binary on.bin
	$(ARM)-objdump on.o -d > on.list

install:
	rpi-install.py on.bin

clean: 
	rm -f *.bin *.list *.o

