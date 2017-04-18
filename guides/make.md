---
layout: page
title: Guide to Make for ARM cross-development
---

*Written for CS107E by Pat Hanrahan & Anna Zeng*

Make is a tool that automates building executable programs;
a makefile is a file that tells `make` what to do in order to build
the programs you want. As you will see soon enough, they make life
as a computer science student a whole lot smoother!

This guide is about using makefiles
for cross-development for the ARM.
We will briefly review makefile syntax and usage.
For more information about makefiles,
read the 
[CS107 Guide to Makefiles](http://web.stanford.edu/class/cs107/guide_make.html).

Below is a simple makefile that can be used
to build a binary for the ARM processor.

    NAME = blink

    CFLAGS  = -std=c99 -Og -g -Wall -ffreestanding

    all: $(NAME).bin

    %.bin: %.o
        $(ARM)-objcopy $< -O binary $@

    %.o: %.c
        $(ARM)-gcc $(CFLAGS) -c $< -o $@

    %.o: %.s
        $(ARM)-as $(CFLAGS) -o $< $@

    %.list: %.o
        $(ARM)-objdump -d $< > $@

    install: $(NAME).bin
        rpi-install.py $<

    clean:
        rm -f *.o *.bin *.list

Now, this Makefile may look a bit cryptic at first! Let's try breaking it down and see if this makes sense.

### Makefile Basics: Rules

From lecture, we were introduced to Makefiles as an improvement on the `doit` script;
our first Makefile looked a little something like:
    
    all: button.bin
    
    button.bin: button.c
        arm-none-eabi-gcc -Og -g -Wall -std=c99 -ffreestanding -c button.c -o button.o
        arm-none-eabi-objcopy button.o -O binary button.bin
        arm-none-eabi-objdump button.o -d > button.list
    
    clean: 
        rm -f *.list *.bin *.o

__Rules__ are written in terms of "you require __dependencies__ on the right-hand-side
to satisfy the need for our __target__ on the left-hand-side." Here, we indicate: by default, make all;
to do that, make `button.bin`.
    
    all: button.bin

This brings us to the next rule, which tells us how to make `button.bin`. You may interpret this as
requiring certain ingredients (dependencies on the right-hand-side)
to create the thing you want (target on the left-hand-side).

    button.bin: button.c

The text which immediately follow the rule, or __recipe__ for the rule,
are commands necessary to turn the ingredients (`button.c` in this case)
into the final product (`button.bin` in this case).
We also throw in a comment to explain the additional flags included with our call to `arm-none-eabi-gcc`.

    # Here, we set compile flags for gcc:
    #  -std=c99 use the c99 standard
    #  -Og       generate optimized code designed for debugging
    #  -g        add debugging information
    #  -Wall     give warnings about *all* issues
    #  -ffreestanding generate code assuming no operating system

    button.bin: button.c
        arm-none-eabi-gcc -Og -g -Wall -std=c99 -ffreestanding -c button.c -o button.o
        arm-none-eabi-objcopy button.o -O binary button.bin
        arm-none-eabi-objdump button.o -d > button.list

The line below indicates what should happen when we `make clean`; the keyword `clean` tells Make to run the command below.

    clean: 
        rm -f *.list *.bin *.o


### Makefile Magic: Macros & More Rules

After copy-pasting and editing every Makefile each time a new program is created,
we have finally decided that it's time to channel a little Dawson Engler and become more efficient.
After all, Makefiles are written for convenience!

    NAME = blink
    ARM = arm-none-eabi

    CFLAGS  = -std=c99 -Og -g -Wall -ffreestanding

    all: $(NAME).bin

    $(NAME).bin: $(NAME).c
        $(ARM)-gcc $(CFLAGS) -c $(NAME).c -o $(NAME).o
        $(ARM)-objcopy $(NAME).o -O binary $(NAME).bin
        $(ARM)-objdump $(NAME).o -d > $(NAME).list
    
    clean: 
        rm -f *.list *.bin *.o

So we've just added three __macros__ up top. They're similar to variables
in that they put text in where you expect them to go.
Be sure to use the `$(<macro_name>)`
syntax to access the value of the macro and allow string concatenation.
(Did you see what we did there with the `ARM` macro?)
Phew, this saves us a lot of visual space!

Now, let's introduce a few special rules here to replace our one rule for `blink.bin`.

    # This is the rule for compiling a C program to make an object file.
    %.o: %.c
        $(ARM)-gcc $(CFLAGS) -c $< -o $@

    # This is the rule for converting an assembly language program
    # to machine code in an object file.
    %.o: %.s
        $(ARM)-as $(CFLAGS) -o $< $@

    # This is predefined rule to creating a *.bin file from a *.o file,
    # in this case, blink.bin from blink.o
    %.bin: %.o
        $(ARM)-objcopy $< -O binary $@

    # This is the rule for disassembling the object file
    # to make a listing
    %.list: %.o
        $(ARM)-objdump -d $< > $@

The key to figuring out what they do is to know:

* `%` is a wildcard symbol when used in a rule; `%.o` for example matches any file that ends with `.o`
* `$@` refers to the left part of the rule, before the `:`
* `$<` refers to the first element in the right part of the rule, after the `:`

So, really, you can think of the makefile as a big cookbook that culminates in the program you ultimately wish to create.

For convenience, we can also throw in another rule so we don't have to type in `rpi-install.py blink.bin`
every time we want to run our program on the Pi.

    # The install target uploads freshly made binary image to rpi bootloader
    install: $(NAME).bin
        rpi-install.py $<

Congratulations! You are now a makefile wizard!✨
