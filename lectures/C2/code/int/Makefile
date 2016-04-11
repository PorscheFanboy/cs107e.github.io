CFLAGS = -std=c99 -O2 -nostdlib -nostartfiles -ffreestanding 

int.bin: int.c Makefile
	arm-none-eabi-gcc $(CFLAGS) int.c -o int.exe
	arm-none-eabi-objcopy int.exe -O binary int.bin
	arm-none-eabi-objdump -D --section=.data int.exe 
	hexdump -e '"%04_ax: " 1/4 "%08x\n"' int.bin

clean :
	rm -f *.o *.bin *.exe *.list


