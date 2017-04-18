# This simple Makefile defines pattern rule to build 
# name.bin from name.c C source file

CFLAGS = -Og -g -Wall -std=c99 -ffreestanding
LDFLAGS = -nostdlib -T memmap
LDLIBS = -lgcc

all: dice

%.bin: %.o start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $*.elf
	arm-none-eabi-objcopy $*.elf -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump $< -d > $@

# This recipe is for a native executable on hosted environment
# (not cross-compiled, not freestanding)
%: %.c
	gcc -g -Wall -std=c99 -c $< -o $*_native.o
	gcc $*_native.o -o $@

clean: 
	rm -f *.list *.bin *.elf *.o dice wipe