NAME = libmypi

# Names of objects to compile into your libmypi.a
OBJECTS  = abort.o font.o gpioextra.o gpioevent.o 
OBJECTS += mailbox.o ps2.o reboot.o strtol.o uart.o 

CS107E=../..

CFLAGS  = -I$(CS107E)/libpi/include -g -Wall -Werror -Wpointer-arith 
CFLAGS += -Og -std=c99 -ffreestanding 
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name

all : $(NAME).a 

$(NAME).a: $(OBJECTS)
	arm-none-eabi-ar rD $@ $^

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

clean:
	rm -f $(NAME).a *.o *.list *~

.PHONY: all clean 

.PRECIOUS: %.o %.a
