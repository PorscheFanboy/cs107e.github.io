CFLAGS  = --std=c99 -Wall -nostdlib -nostartfiles -ffreestanding 
CFLAGS += -O0 -fomit-frame-pointer
CFLAGS += -g

all: winky.list

winky.list: winky.elf
	arm-none-eabi-objdump winky.elf -d > winky.list

winky.elf: winky.c start.s Makefile
	arm-none-eabi-gcc $(CFLAGS) start.s winky.c -o winky.elf

clean :
	rm -f *.exe
	rm -f *.list





