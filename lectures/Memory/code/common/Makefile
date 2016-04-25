NAME = main

CPPFLAGS = 
ASFLAGS =
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding $(CPPFLAGS)
LDFLAGS = -nostdlib -T memmap
LDLIBS =

OBJECTS = start.o cstart.o tricky.o
 
all : $(NAME).exe

$(NAME).exe: $(NAME).o $(OBJECTS)
	arm-none-eabi-ld $(LDFLAGS)  $^ -o $@

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

sections:
	#arm-none-eabi-readelf --sections $(NAME).exe
	arm-none-eabi-readelf --sections $(NAME).o

segments:
	arm-none-eabi-readelf --segments $(NAME).exe

headers: $(NAME).exe
	arm-none-eabi-readelf -h $(NAME).exe

symbols:
	arm-none-eabi-readelf --symbols $(NAME).exe

# Targets that aren't filename of build product should be declared "phony" 
.PHONY: all clean

# include dependency info
#  "-" suppresses errors
-include $(NAME).d $(SRCS:.c=.d)
