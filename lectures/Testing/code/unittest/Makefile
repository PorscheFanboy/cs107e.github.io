NAME = main

OBJECTS = clock.o 

CS107E=../../../..
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -Og -std=c99 -ffreestanding 
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/libpi/lib
LDLIBS = -lpi -lgcc

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@
	arm-none-eabi-objdump -d $@ > $@.list

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
	
%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

install: $(NAME).bin
	rpi-install.py $<

# Can use 'make test' to build the test program and upload it to Pi
test: test.bin
	rpi-install.py $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install test

.PRECIOUS: %.o %.elf
