LIBPI = ../../../../../libpi
CPPFLAGS = -I$(LIBPI)/include
ASFLAGS =
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding $(CPPFLAGS)
LDFLAGS = -nostdlib -T memmap
 
NAME = blink
OBJECTS = timer.o gpio.o start.o

all : $(NAME).bin

$(NAME).exe: $(NAME).o $(OBJECTS)
	arm-none-eabi-ld $(LDFLAGS)  $^ -o $@
	arm-none-eabi-objdump -d --no-show-raw-insn $@ > $@.list

%.bin: %.exe
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	cpp -P $< | arm-none-eabi-as $(ASFLAGS) -o $@

%.list: %.o
	arm-none-eabi-objdump -d --no-show-raw-insn $< > $@

clean:
	rm -f *.bin *.exe *.o *.list *~

.PRECIOUS: %.exe %.o

# Targets that aren't filename of build product should be declared "phony" 
.PHONY: all clean

