# A simple makefile for building program composed of C/asm source files
# and linked against the reference version of libpi.a
# Builds for ARM target using cross-development toolchain.
# Refer to CS107E guide to Make for more information on makefiles

NAME = main
OBJECTS =

# Your libpi modules: edit to list libpi modules for which to use your own code.
# These .o files will be built from the .c source file in the local directory.
# For any module not listed, the version from the reference libpi will be used.
LIBPI_STUDENT_MODULES =

CS107E=/Users/will/Code/git/cs107e.github.io
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -Og -std=c99 -ffreestanding
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/libpi/lib
LDLIBS = -lpi -lgcc


all : $(NAME).bin $(LIBPI_STUDENT_MODULES)

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o $(LIBPI_STUDENT_MODULES)
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

install: $(NAME).bin
	rpi-install.py $<

test: test.bin
	rpi-install.py $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install test

.PRECIOUS: %.o %.elf
