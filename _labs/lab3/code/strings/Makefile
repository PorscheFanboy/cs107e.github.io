
NAME = strings

CS107E=../../../..
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -Og -std=c99 -ffreestanding 
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/libpi/lib
LDLIBS = -lpi

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d --no-show-raw-insn $< > $@

install: $(NAME).bin
	rpi-install.py -s $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean

.PRECIOUS: %.o %.elf
