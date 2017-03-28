NAME = linking

LIBPI = ../../../../../libpi
CPPFLAGS = -I$(LIBPI)/include
ASFLAGS =
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding $(CPPFLAGS)
LDFLAGS = -nostdlib -T memmap 
 
OBJECTS = start.o cstart.o

all : $(NAME).bin

$(NAME).elf: $(NAME).o $(OBJECTS)
	arm-none-eabi-ld $(LDFLAGS)  $^ -o $@ 
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
