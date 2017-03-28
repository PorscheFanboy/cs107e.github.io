ARMGNU = arm-none-eabi

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

NAME = blink
SOURCES = $(NAME).c 

all : $(NAME).bin

install: $(NAME).bin
	rpi-install.py $(NAME).bin


%.bin: %.exe
	$(OBJCOPY) $< -O binary $@

%.exe: start.o cstart.o $(SOURCES:.c=.o)
	$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@ 

%.list: %.o
	$(OBJDUMP) -d --no-show-raw-insn $< > $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
	$(CC) -MM $(CFLAGS) -c $< > $*.d

clean :
	rm -f *.bin
	rm -f *.exe
	rm -f *.o
	rm -f *.d
	rm -f *.list

.PHONY : all clean

.PRECIOUS: %.exe %.o

# include dependency info 
#  "-" suppresses errors
-include $(SRCS:.c=.d)

