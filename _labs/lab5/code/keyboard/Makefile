NAME = main

LIBPI = ../../../../libpi
MODULES = $(LIBPI)/modules
CPPFLAGS = -I$(LIBPI)/include
ASFLAGS =
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding $(CPPFLAGS)
LDFLAGS = -nostdlib -T memmap -L$(LIBPI)/lib -lgcc
 
OBJECTS = start.o cstart.o keyboard.o
LIBPI_MODULES  = $(MODULES)/memory.o $(MODULES)/gpio.o 
LIBPI_MODULES += $(MODULES)/gpioextra.o  $(MODULES)/timer.o 
LIBPI_MODULES += $(MODULES)/led.o $(MODULES)/gpioevent.o 
LIBPI_MODULES += $(MODULES)/uart.o $(MODULES)/printf.o

all : $(NAME).bin

$(NAME).elf: $(NAME).o $(OBJECTS) $(LIBPI_MODULES)
	arm-none-eabi-gcc $^ -o $@ $(LDFLAGS)  
	arm-none-eabi-objdump -D $@ > $@.list

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
	arm-none-eabi-gcc -MM $(CFLAGS) -c $< > $*.d

%.o: %.s
	cpp -P $< | arm-none-eabi-as $(ASFLAGS) -o $@

%.list: %.o
	arm-none-eabi-objdump -D --no-show-raw-insn $< > $@

clean:
	rm -f *.bin *.elf *.o *.d *.list *~

install: $(NAME).bin
	rpi-install.py -s $(NAME).bin

headers: $(NAME).elf
	arm-none-eabi-readelf --h $(NAME).elf

symbols:
	arm-none-eabi-readelf --symbols $(NAME).elf

sections:
	arm-none-eabi-readelf ---sections $(NAME).elf

segments:
	arm-none-eabi-readelf --segments $(NAME).elf

# Targets that aren't filename of build product should be declared "phony" 
.PHONY: all clean

# include dependency info
#  "-" suppresses errors
-include $(NAME).d $(OBJECTS:.o=.d)
