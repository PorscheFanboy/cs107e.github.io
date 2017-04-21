
CFLAGS = -Og -Wall -g -std=c99 -ffreestanding 
LDFLAGS = -nostdlib
LDLIBS = 

all : example.bin framed.bin example.list framed.list

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o cstart.o start.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

framed.o: CFLAGS += -fno-omit-frame-pointer

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

# The clean target removes previous build products, will force build a-new on next make
clean:
	rm -f *.o *.bin *.elf *.list

# Targets that aren't filename of build product should be declared "phony" 
.PHONY: all clean

# Mark these intermediate files to be saved, rather than discarded after final build
.PRECIOUS: %.o %.elf
