NAME = clear
OBJECTS = helpers.o

CS107E = ../../../../cs107e
OPTIMIZATION = -O0
CFLAGS = -I$(CS107E)/include -Wall -ffreestanding
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lc_pi -lpi -lgcc -lpiextra

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(OPTIMIZATION) $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

install: $(NAME).bin
	../../../../guides/mac_toolchain/rpi-install.py -p /dev/ttyS4 $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install

.PRECIOUS: %.o %.elf

# empty recipe used to disable built-in rules for native build
%:%.c
%:%.o
%:%.s
