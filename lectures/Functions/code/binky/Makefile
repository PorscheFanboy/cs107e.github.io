CFLAGS  = -Wall -nostdlib -nostartfiles -ffreestanding 
CFLAGS += -O0 -fomit-frame-pointer
CFLAGS += -g

all: binky.list

binky.list: binky.exe
	arm-none-eabi-objdump binky.exe -d > binky.list

binky.exe: binky.c start.s Makefile
	arm-none-eabi-gcc $(CFLAGS) start.s binky.c -o binky.exe

clean :
	rm -f *.exe
	rm -f *.list





