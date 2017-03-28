ARMGNU ?= arm-none-eabi

CC = $(ARMGNU)-gcc
LD = $(ARMGNU)-ld
AS = $(ARMGNU)-as
OBJCOPY = $(ARMGNU)-objcopy
OBJDUMP = $(ARMGNU)-objdump

LIBGCC ?= $(shell $(CC) -print-libgcc-file-name)
LIBPI ?= ../../../../libpi

CPPFLAGS = -I$(LIBPI)/include
CFLAGS = -std=c99 -Wall -Og -g -ffreestanding $(CPPFLAGS)
CFLAGS += -mapcs-frame -fno-omit-frame-pointer
ASFLAGS = 
LDFLAGS  = -nostdlib -T memmap -L$(LIBPI)/lib
LDLIBS = -lpi $(LIBGCC)

NAME = key
SRCS = $(NAME).c 

all : $(NAME).bin

%.bin: %.elf
	$(OBJCOPY) $< -O binary $@

%.elf: start.o cstart.o interrupt_handlers.o $(SRCS:.c=.o)
	$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@ 

%.list: %.o
	$(OBJDUMP) -d --no-show-raw-insn $< > $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
	$(CC) -MM $(CFLAGS) -c $< > $*.d

%.s: %.c
	$(CC) $(CFLAGS) -S $< 

install: $(NAME).bin
	rpi-install.py $(NAME).bin

clean :
	rm -f *.bin
	rm -f *.elf
	rm -f *.o
	rm -f *.d
	rm -f *.list

# Targets that aren't filename of build product should be declared "phony"
.PHONY : all clean

.PRECIOUS: %.elf %.o

# include dependency info 
#  "-" suppresses errors
-include $(SRCS:.c=.d)

