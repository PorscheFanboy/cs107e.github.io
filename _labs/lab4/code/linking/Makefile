NAME = linking

OBJECTS = 

CS107E = ../../../..
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -Og -std=c99 -ffreestanding 
LDFLAGS = -nostdlib -T memmap 
LDLIBS = 

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: start.o cstart.o %.o $(OBJECTS)
	arm-none-eabi-ld $(LDFLAGS) $^ $(LDLIBS) -o $@
	arm-none-eabi-objdump -D $@ > $@.list

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

install: $(NAME).bin
	rpi-install.py $<

clean:
	rm -f *.i *.o *.bin *.elf *.list *~

.PHONY: all clean install

.PRECIOUS: %.o %.elf
