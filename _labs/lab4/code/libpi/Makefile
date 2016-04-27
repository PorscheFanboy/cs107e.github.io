NAME = blink

LIBPI = ../../../../libpi
CPPFLAGS = -I$(LIBPI)/include
ASFLAGS =
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding $(CPPFLAGS)
LDFLAGS = -nostdlib -T memmap
 
OBJECTS = timer.o gpio.o

all : $(NAME).bin

$(NAME).elf: $(NAME).o start.o libpi.a
	arm-none-eabi-ld $(LDFLAGS)  $^ -o $@
	arm-none-eabi-objdump -d --no-show-raw-insn $@ > $@.list

libpi.a: $(OBJECTS)
	arm-none-eabi-ar crf libpi.a $^

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
	arm-none-eabi-gcc -MM $(CFLAGS) -c $< > $*.d

%.o: %.s
	cpp -P $< | arm-none-eabi-as $(ASFLAGS) -o $@

%.list: %.o
	arm-none-eabi-objdump -d --no-show-raw-insn $< > $@


clean:
	rm -f *.bin *.elf *.o *.d *.list *~

# Targets that aren't filename of build product should be declared "phony" 
.PHONY: all clean

# include dependency info
#  "-" suppresses errors
-include $(NAME).d $(OBJECTS:.o=.d)
