all: fb-volatile.s fb-nvolatile.s

%.s: %.o
	arm-none-eabi-objdump -d $< > $@

fb-nvolatile.o: fb-example.c
	arm-none-eabi-gcc -I../../../../libpi/include -c -O3 -o $@ $<

fb-volatile.o: fb-example.c
	arm-none-eabi-gcc -DNVOLATILE -I../../../../libpi/include -c -O3 -o $@ $<

clean:
	rm -f *.o *.s 
