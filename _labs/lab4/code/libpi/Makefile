NAME = blink

OBJECTS = timer.o gpio.o

CS107E = ../../../..
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -Og -std=c99 -ffreestanding
LDFLAGS = -nostdlib -T memmap
 
all : $(NAME).bin

%.elf: %.o start.o cstart.o libpi.a
	arm-none-eabi-ld $(LDFLAGS) $^ -o $@
	arm-none-eabi-objdump -d $@ > $@.list

libpi.a: $(OBJECTS)
	arm-none-eabi-ar crf libpi.a $^

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

clean:
	rm -f *.o *.bin *.elf *.list *.a *~

.PHONY: all clean

.PRECIOUS: %.o %.elf