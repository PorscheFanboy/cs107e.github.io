NAME = blink

LIBPI = ../../../../../libpi
CPPFLAGS = -I$(LIBPI)/include
ASFLAGS =
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding $(CPPFLAGS)
LDFLAGS = -nostdlib -T memmap -L$(LIBPI)/lib
 
OBJECTS = start.o cstart.o

all : $(NAME).bin

$(NAME).exe: $(NAME).o $(OBJECTS)
	arm-none-eabi-ld $(LDFLAGS)  $^ -o $@ -lpi
	arm-none-eabi-objdump -d --no-show-raw-insn $@ > $@.list

%.bin: %.exe
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
	arm-none-eabi-gcc -MM $(CFLAGS) -c $< > $*.d

%.o: %.s
	cpp -P $< | arm-none-eabi-as $(ASFLAGS) -o $@

%.list: %.o
	arm-none-eabi-objdump -d --no-show-raw-insn $< > $@

clean:
	rm -f *.bin *.exe *.o *.d *.list *~

# Targets that aren't filename of build product should be declared "phony" 
.PHONY: all clean

# include dependency info
#  "-" suppresses errors
-include $(NAME).d $(OBJECTS:.o=.d)
