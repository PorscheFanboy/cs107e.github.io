NAME = echo

ARMGNU ?= arm-none-eabi

CC = $(ARMGNU)-gcc
LD = $(ARMGNU)-ld
AS = $(ARMGNU)-as
OBJCOPY = $(ARMGNU)-objcopy
OBJDUMP = $(ARMGNU)-objdump

LIBPI = ../../../../libpi

CPPFLAGS = -I$(LIBPI)/include
CFLAGS = -std=c99 -Wall -Og -g -ffreestanding $(CPPFLAGS)
ASFLAGS = 
LDFLAGS  = -nostdlib -T memmap -L$(LIBPI)/lib
LDLIBS = -lpi

SOURCES = $(NAME).c

all : $(NAME).bin

$(NAME).elf: start.o $(SOURCES:.c=.o)
	$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
	$(CC) -MM $(CFLAGS) -c $< > $*.d

%.s: %.c
	$(CC) $(CFLAGS) -S $< 

%.bin: %.elf
	$(OBJCOPY) $< -O binary $@

%.list: %.o
	$(OBJDUMP) -d --no-show-raw-insn $< > $@

install: $(NAME).bin
	rpi-install.py $(NAME).bin

clean :
	rm -f *.bin
	rm -f *.elf
	rm -f *.o
	rm -f *.d
	rm -f *.list

.PHONY : all install clean

.PRECIOUS: %.elf %.o

# include dependency info 
#  "-" suppresses errors
-include $(SRCS:.c=.d)
