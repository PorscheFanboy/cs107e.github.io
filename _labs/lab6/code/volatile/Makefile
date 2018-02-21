NAME = fb-main
MODULES = fb.o mailbox.o

CS107E=../../../../cs107e
CFLAGS = -I$(CS107E)/include -g -Wall -O2 -std=c99 -ffreestanding
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lc_pi -lpi


# The `(OBJECTS:.o=-not-volatile.o)` is notation for: wherever you see something
# in OBJECTS that matches the pattern *.o, replace that with *-not-volatile.o.
# Feel free to use OBJ_NVOL if you'd like to try running the program without the
# `volatile` modifier on the framebuffer or mailbox.
OBJ_NVOL = (MODULES:.o=-not-volatile.o)

all : $(NAME).bin listings

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o start.o cstart.o $(MODULES)
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

# Added `-DNVOLATILE` to define NVOLATILE, found in #ifdefs in fb.c and mailbox.c.
# This tells the preprocessor to include content wrapped between #ifdef and #else,
# as opposed to #else and #endif when NVOLATILE is not defined.
%-not-volatile.o: %.c
	arm-none-eabi-gcc -DNVOLATILE $(CFLAGS) -c $< -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

listings: mailbox.list mailbox-not-volatile.list 

install: $(NAME).bin
	rpi-install.py -p $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install

.PRECIOUS: %.elf %.o

%:%.c
%:%.o
