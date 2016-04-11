CFLAGS = -std=c99 -O2 -nostdlib -nostartfiles -ffreestanding 

array.bin: array.c Makefile
	arm-none-eabi-gcc $(CFLAGS) array.c -o array.exe
	arm-none-eabi-objcopy array.exe -O binary array.bin
	arm-none-eabi-objdump -D --section=.data array.exe 
	#arm-none-eabi-nm -g array.exe 
	hexdump -e '"%04_ax: " 1/4 "%08x\n"' array.bin

clean :
	rm -f *.o *.bin *.exe *.list


