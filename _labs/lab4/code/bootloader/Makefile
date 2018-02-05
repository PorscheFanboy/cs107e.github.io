CS107E = ../../../../cs107e
CFLAGS = -I$(CS107E)/include -Wall -O2 -std=c99 -ffreestanding
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpi

all : bootloader.bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o start.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c Makefile
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d --no-show-raw-insn $< > $@

installsd : bootloader.bin
	cp bootloader.bin /Volumes/PIBOOT/kernel.img

clean :
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean

.PRECIOUS: %.elf %.o