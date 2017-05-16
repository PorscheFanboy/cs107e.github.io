NAME = fb-main

CS107E=../../../..
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -O3 -std=c99 -ffreestanding 
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/libpi/lib
LDLIBS = -lpi
 
OBJECTS = fb.o mailbox.o
# The `(OBJECTS:.o=-not-volatile.o)` is notation for: wherever you see something
# in OBJECTS that matches the pattern *.o, replace that with *-not-volatile.o.
# Feel free to use OBJ_NVOL if you'd like to try running the program without the
# `volatile` modifier on the framebuffer or mailbox.
OBJ_NVOL = (OBJECTS:.o=-not-volatile.o)

all : $(NAME).bin listings

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

# Added `-DNVOLATILE` to define NVOLATILE, found in #ifdefs in fb.c and mailbox.c.
# This tells the preprocessor to include content wrapped between #ifdef and #else,
# as opposed to #else and #endif when NVOLATILE is not defined.
%-not-volatile.o: %.c
	arm-none-eabi-gcc -DNVOLATILE $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

install: $(NAME).bin
	rpi-install.py -s $<

listings: mailbox.list mailbox-not-volatile.list 

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install

.PRECIOUS: %.o %.elf
