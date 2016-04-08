blink.bin: blink.s
	cpp -P blink.s | arm-none-eabi-as -o blink.o
	arm-none-eabi-objcopy blink.o -O binary blink.bin

install: blink.bin
	rpi-install.py blink.bin

clean :
	rm -f *.o *.bin


