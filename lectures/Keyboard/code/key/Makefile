NAME = scan

LIBPI = ../../../../libpi
LIBPIMOD = $(LIBPI)/modules

CPPFLAGS = -I$(LIBPI)/include
ASFLAGS =
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding $(CPPFLAGS)
LDFLAGS = -nostdlib -T memmap -L$(LIBPI)/lib -lgcc 
 
OBJECTS = start.o cstart.o 
LIBPI_MODULES  = $(LIBPIMOD)/memory.o $(LIBPIMOD)/gpio.o $(LIBPIMOD)/gpioextra.o  
LIBPI_MODULES += $(LIBPIMOD)/timer.o $(LIBPIMOD)/led.o $(LIBPIMOD)/gpioevent.o 
LIBPI_MODULES += $(LIBPIMOD)/keyboard-sync.o $(LIBPIMOD)/uart.o $(LIBPIMOD)/printf.o 
LIBPI_MODULES += $(LIBPIMOD)/ps2.o

all : $(NAME).bin

$(NAME).elf: $(NAME).o $(OBJECTS) $(LIBPI_MODULES)
	arm-none-eabi-ld $^ -o $@ $(LDFLAGS)  
	arm-none-eabi-objdump -D $@ > $@.list

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
	arm-none-eabi-gcc -MM $(CFLAGS) -c $< > $*.d

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump -D --no-show-raw-insn $< > $@

clean:
	rm -f *.bin *.elf *.o *.d *.list *~

install: $(NAME).bin
	rpi-install.py -p $(NAME).bin

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
