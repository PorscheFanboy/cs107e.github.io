CFLAGS = -std=c99 -O2 -nostdlib -nostartfiles -ffreestanding 

all:
	arm-none-eabi-gcc $(CFLAGS) string.c -o string.exe
	arm-none-eabi-objcopy string.exe -O binary string.bin
	arm-none-eabi-objdump -D --section=.data string.exe 
	hexdump -e '"%04_ax: " 1/4 "%08x\n"' string.bin

clean :
	rm -f *.o *.bin *.exe *.list


