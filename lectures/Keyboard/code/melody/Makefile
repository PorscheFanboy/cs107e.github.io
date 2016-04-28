ARMGNU ?= arm-none-eabi

CC = $(ARMGNU)-gcc
LD = $(ARMGNU)-ld
AS = $(ARMGNU)-as
OBJCOPY = $(ARMGNU)-objcopy
OBJDUMP = $(ARMGNU)-objdump

LIBGCC ?= $(shell $(CC) -print-libgcc-file-name)
LIBPI ?= ../../../../../libpi

CPPFLAGS = -I$(LIBPI)/include
CFLAGS = -std=c99 -Wall -Og -g -ffreestanding $(CPPFLAGS)
CFLAGS += -mapcs-frame -fno-omit-frame-pointer
ASFLAGS = 
LDFLAGS  = -nostdlib -T memmap -L$(LIBPI)/lib
LDLIBS = -lpi $(LIBGCC)

NAME = melody
SRCS = $(NAME).c tone.c pwm.c

all : $(NAME).bin

%.bin: %.exe
	$(OBJCOPY) $< -O binary $@

%.exe: start.o cstart.o $(SRCS:.c=.o)
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
	rm -f *.exe
	rm -f *.o
	rm -f *.d
	rm -f *.list

.PHONY : all clean

.PRECIOUS: %.exe %.o

