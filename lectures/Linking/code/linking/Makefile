NAME = main

CPPFLAGS = 
ASFLAGS =
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding $(CPPFLAGS)
LDFLAGS = -nostdlib -T memmap
LDLIBS =

OBJECTS = start.o cstart.o linking.o
 
all : $(NAME).exe

$(NAME).exe: $(OBJECTS) $(NAME).o
	arm-none-eabi-ld $(LDFLAGS)  $^ -o $@
	arm-none-eabi-objdump -d --no-show-raw-insn $@ > $@.list

%.bin: %.exe
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
	arm-none-eabi-gcc -MM $(CFLAGS) -c $< > $*.d

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d --no-show-raw-insn $< > $@

clean:
	rm -f *.bin *.exe *.o *.d *.list *~

# Targets that aren't filename of build product should be declared "phony" 
.PHONY: all clean

# include dependency info
#  "-" suppresses errors
-include $(NAME).d $(SRCS:.c=.d)
