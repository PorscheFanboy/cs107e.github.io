---
layout: page
title: Guide to Make for ARM cross-development
---

*Written for CS107E by Pat Hanrahan*

This guide is about using makefiles
for cross-development for the ARM.
We will briefly review makefile syntax and usage.
For more information about makefiles,
read the 
[CS107 Guide to Makefiles](http://web.stanford.edu/class/cs107/guide_make.html).

Below is a simple makefile that can be used
to build a binary for the ARM processor.

    # create a variable that is the name of the program
    #
    NAME = blink

    # The CFLAGS variable sets compile flags for gcc: 
    #
    #  --std=c99 use the c99 standard
    #  -Og       generate optimized code designed for debugging
    #  -g        add debugging information
    #  -Wall     give warnings about *all* issues 
    #
    # these options are required for bare metal code
    #
    #  -ffreestanding generate code assuming no operating system
    #  -nostartfiles do not call or link to startup code
    #  -nostdlib do not link against standard libraries
    #
    # note how we can append options using +=
    #
    CFLAGS  = --std=c99 -Og -g -Wall 
    CFLAGS += -ffreestanding -nostdlib -nostartfiles

    #
    # By default, make all. This will make blink.bin.
    #
    # Note that $(NAME) means the value of NAME.
    # We needto use a $ to indicate that it is a variable.
    # We also enclose NAME in parenthesis so we can concatenate strings.
    #
    all: $(NAME).bin

    # 
    # This is predefined rule to creating a *.bin file from a *.o file,
    # in this case, blink.bin from blink.o
    #
    # Note the special variables:
    #
    #  $@ is the left part of the rule, blink.bin
    #  $< is the right part of the rule, blink.o
    #
    %.bin: %.o
        arm-none-objcopy $< -O binary $@

    # 
    # This is the rule for compiling a C program to make an object file.
    #
    %.o: %.c
        arm-none-eabi-gcc $(CFLAGS) -o $< on.c

    # 
    # This is the rule for converting an assembly language program
    # to machine code in an object file.
    #
    %.o: %.s
        arm-none-eabi-as $(CFLAGS) -o $< on.c

    # 
    # This is the rule for disassembling the object file
    # to make a listing
    #
    %.list: %.o
        arm-none-objdump -d $< > $@

    # The install target uploads freshly made binary image to rpi bootloader
    install: $(NAME).bin
        rpi-install.py $<

    # The clean target removes previous build products,
    # will force build a-new on next make
    clean:
        rm -f *.o *.bin *.list

