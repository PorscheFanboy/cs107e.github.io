
all : blink.bin 

%.bin: %.o
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

install: blink.bin
	rpi-install.py $<

clean:
	rm -f *.o *.bin *.elf *.list

.PHONY: all clean
.PRECIOUS: %.o %.elf