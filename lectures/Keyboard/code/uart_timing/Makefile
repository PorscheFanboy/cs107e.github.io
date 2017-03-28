NAME = hello

LIBPI = ../../../../../libpi

CPPFLAGS = -I$(LIBPI)/include
CFLAGS = -std=c99 -Wall -Og -g -ffreestanding $(CPPFLAGS)
LDFLAGS  = -nostdlib -T memmap -L$(LIBPI)/lib

SOURCES = $(NAME).c uart.c cstart.c

all : $(NAME).bin

LIBPI_MODULES = $(LIBPI)/modules/memory.o $(LIBPI)/modules/gpio.o $(LIBPI)/modules/timer.o

$(NAME).exe: start.o $(LIBPI_MODULES) $(SOURCES:.c=.o) 
	arm-none-eabi-ld $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@ 

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< 
	arm-none-eabi-gcc -MM $(CFLAGS) -c $< > $*.d

%.s: %.c
	arm-none-eabi-gcc $(CFLAGS) -S $< 

%.bin: %.exe
	arm-none-eabi-objcopy $< -O binary $@

install: $(NAME).bin
	rpi-install.py -p $(NAME).bin

clean :
	rm -f *.bin
	rm -f *.exe
	rm -f *.o
	rm -f *.d
	rm -f *.list

.PHONY : all install clean

.PRECIOUS: %.exe %.o

# include dependency info 
#  "-" suppresses errors
-include $(SRCS:.c=.d)
