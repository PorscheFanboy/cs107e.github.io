NAME = winky
OBJECTS =

CS107E=../../../..
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -Og -std=c99 -ffreestanding -mapcs-frame -fno-omit-frame-pointer
LDFLAGS = -nostdlib -T memmap
# Here, we use the `-L` flag to tell the linker where to find the libpi library.
# The `lpi` flag tells the linker to link your program with libpi.
LDLIBS = -L$(CS107E)/libpi/lib -lpi

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: start.o cstart.o %.o $(OBJECTS) 
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
	
%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

%.elf.list: %.elf
	arm-none-eabi-objdump -d $< > $@

install: $(NAME).bin
	rpi-install.py $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean

.PRECIOUS: %.o %.elf
