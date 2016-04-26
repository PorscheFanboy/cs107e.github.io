blink

This directory contains all the files. The gpio_ and timer_ functions
come from libpi.a.

The Makefile shows all the steps we need to do to build blink properly

o Note the order of the files in memmap
  - make sure _start goes first and ends up with the address 0x8000.

o Note how start.s sets the stack pointer

o Note how cstart.c initializes bss to 0

o Then main runs

