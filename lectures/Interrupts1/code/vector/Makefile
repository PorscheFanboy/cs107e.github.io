NAME = main

OBJECTS = interrupt_handlers.o vectors.o
BOBJECTS = interrupt_handlers.o vectors.bug.o

CS107E=../../../..

CFLAGS  = -I$(CS107E)/libpi/include -g -Wall -Werror -Wpointer-arith 
CFLAGS += -Og -std=c99 -ffreestanding 
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/libpi/lib
LDLIBS = -lgcc

all : $(NAME).bin app.list app.bug.list

app.list: $(NAME).elf
	arm-none-eabi-objdump -d $< > $@

app.bug.list: $(NAME).elfb
	arm-none-eabi-objdump -d $< > $@

%.elfb: %.o $(BOBJECTS) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

install: $(NAME).bin
	rpi-install.py -p $<

test: test.bin
	rpi-install.py -p $<

clean:
	rm -f *.o *.bin *.elf* *.list *~ *.d

.PHONY: all clean install test

.PRECIOUS: %.o %.elf
