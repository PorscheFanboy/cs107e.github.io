NAME = main
OBJECTS = interrupt_handlers.o /Users/osnr/dev/cs107e/staff/private/lecture/Performance/code/stackprof/stackprof.o vectors.o

# Edit to point to CS107E folder (needed for .h files)
CS107E=../../../..
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -Werror -Og -std=c99 -ffreestanding -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name
LDFLAGS = -nostdlib -T memmap -L.
LDLIBS = -lmypi -lgcc

all : $(NAME).bin

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
	rpi-install.py -r -p $<

%.stackprof: %.bin
	rpi-install.py -r -q -p $< | tr -d "\r" > $@

%.cpuprofile: %.stackprof
	cat $< | cpuprofilify --type perf > $@

%.svg: %.stackprof
	~/dev/FlameGraph/stackcollapse-perf.pl $< | ~/dev/FlameGraph/flamegraph.pl > $@

clean:
	rm -f *.o *.bin *.elf *.list *.stackprof *.cpuprofile *.svg *~

.PHONY: all clean install

.PRECIOUS: %.o %.elf %.stackprof
