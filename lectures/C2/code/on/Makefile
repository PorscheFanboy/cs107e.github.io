CFLAGS = -O2 -nostdlib -nostartfiles -ffreestanding

all: on1.bin 

cmp: on1.bin on2.bin
	cmp on1.bin on2.bin

%.o: %.s 
	arm-none-eabi-as $< -o $*.o

%.o: %.c 
	arm-none-eabi-gcc $(CFLAGS) -c $<

%.bin: %.o
	arm-none-eabi-objcopy $*.o -O binary $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

clean:
	rm -f *.bin *.list *.o

.PRECIOUS: %.o %.bin %.list
