---
layout: page
title: 'Lab 4: Linking and Loading'
permalink: /labs/lab4/
---

## Goals

During this lab you will:

1. Experiment with the linker `ld`, with the goal of understanding what is in
   an object (ELF) file, and how object files are combined to produce an
   executable.

2. Understand how executing programs are laid out in memory.

3. Read and understand the source to the bootloader. It is important to be able
   to read code produced in the wild.

To complete the lab, you must answer the questions in the [check
list](checklist). The last question involves writing a description of how
the bootloader works. See the detailed instructions in the third section of the
lab.

## Lab exercises

#### Exercise 1: Linking (45 min)

In the first part of this lab, you
will be repeating
some of live coding
demonstrations showed during lecture on linking and loading.

To start, check out the
[code](https://github.com/cs107e/cs107e.github.io/tree/master/_labs/lab4/code)
for this lab by changing to the `cs107e.github.io/_labs/lab4/code`
directory.

**Symbols in Object Files**

`cd` into the `linking` folder.

We will begin to examine the symbols 
(i.e.  function names, variables, constants, etc)
in this program by typing:

    % make clean
    % make start.o
    % arm-none-eabi-nm start.o

What is the purpose of `arm-none-eabi-nm`?
Here's [helpful documentation](https://manned.org/arm-none-eabi-nm)
to get a better understanding.
What does it print out?
What do the single
letter symbols 'T', 'U', and 't' mean?
In another window, you may want
to open `start.s` in a text editor for comparison.

Don't move forward until you and your partners understand `nm`'s
output.

Let's now try examining the symbols for this program.

    % make linking.o
    % arm-none-eabi-nm linking.o

What does this command print out?
What does the printout tell you
about the variables and the functions in `linking.c`? 
(You may want to open `linking.c` in a text editor 
to see the source material for `linking.o`.)
What do the single letter symbols 'D', 'R', 'C', and 'b' mean?
What do the numbers of the left mean?

Finally, let's see what `arm-none-eabi-nm` tell us about the symbols in
`cstart.o`.

    % make cstart.o
    % arm-none-eabi-nm cstart.o

**Linking Object Files into Executables**

During lecture, we went over how object files need to be linked together to form
one executable. `arm-none-eabi-ld` is the command that *links* the three files
together to form a single executable. Let's do this now.

    % make linking.elf
    arm-none-eabi-ld -nostdlib -T memmap linking.o start.o cstart.o -o linking.elf
    ...

Next, look at the symbols for the executable as you did before with `nm`.

    % arm-none-eabi-nm linking.elf

What has happened during the link process?
Are there any undefined symbols?
What happened to the symbols marked 'C'?

**Disassembling**

Let's disassemble `start.o` to get a better idea of what happens during linking.

    % arm-none-eabi-objdump -d start.o
    ...
    00000000 <_start>:
       0:   e3a0d302    mov sp, #134217728  ; 0x8000000
       4:   e3a0b000    mov fp, #0
       8:   ebfffffe    bl  0 <_cstart>

Note the branch at location 8.

The *branch and link* instruction `bl` branches to location 0.
 Is 0 the address of `cstart`?

Now let's disassemble `linking.elf`, 
and let's look at the same code after linking.

    % arm-none-eabi-objdump -d linking.elf
    ...
    00008000 <_start>:
        8000:   e3a0d302    mov sp, #134217728  ; 0x8000000
        8004:   e3a0b000    mov fp, #0
        8008:   eb000017    bl  806c <_cstart>
    ...
    0000806c <_cstart>:
        806c:   e92d4008    push    {r3, lr}
        8070:   e59f3024    ldr r3, [pc, #36]   ; 809c <_cstart+0x30>
        8074:   e59f2024    ldr r2, [pc, #36]   ; 80a0 <_cstart+0x34>
        8078:   e3a01000    mov r1, #0
    ...

What is the difference between the branch address before and after linking?
 What did the linker do to change the address?
 Again, don't move forward until you and
your partners understand the answers to these questions. 
(Note: This is checklist question 2.)

**Combining Object Files into Libraries**

Next, `cd` into `../libpi`.
This directory contains an example of building a library
`libpi.a` containing the files `gpio.o` and `timer.o`.

Read the `Makefile`.
Notice the lines

    libpi.a: $(OBJECTS)
    	arm-none-eabi-ar crf libpi.a $^

The `arm-none-eabi-ar` program forms an *archive* from a list of files.
The flags `crf` mean to create (c) the archive, 
replace/insert (r) the files,
and use the filename (f) for the name of the archive.

Libraries can then be passed to the linker.

    $ make
    ...
    arm-none-eabi-ld -nostdlib -T memmap  blink.o start.o libpi.a -o blink.elf
    ...

The linker `ld` treats objects files (`.o`) and libraries (`.a`).
When linking object files, all the files are combined.
When linking libraries, only files containing definitions of
undefined symbols are added to the executable.
This makes it possible to make libraries with lots of useful modules,
 and only include the ones that you actually use in the final executable.

#### Exercise 2: The Memory Map (30 min)

A crucial part of executing any program is memory management. In order to get a
sense of how memory gets organized through linking, go back to the
`code/linking` folder and run the following lines:

    $ make clean
    $ make linking.elf
    arm-none-eabi-ld  -T memmap linking.o cstart.o start.o -o linking.elf
    arm-none-eabi-objdump -D linking.elf > linking.elf.list

Notice that this generates the file `linking.elf.list`, 
which shows the mapping of symbols to their addresses.

Look at the listing. How do the `.text`, `.data`, `.rodata`, and `.bss` sections
from the different files get combined during linking?

Now look at `memmap`.

- Do you see how the `memmap` linker script specifies how sections from
  individual files are to be combined?

- One of the purposes of `memmap` is to ensure that the global label `start`
  appears first in the executable file. How does `memmap` specify that `start.o`
  should be first?

- Another purpose of `memmap` is to setup block storage of uninitialized
  variables. It does this by defining the addresses `__bss_start__` and
  `__bss_end__`. How are those addresses determined? In C, uninitialized
  variables should be set to 0. How does `cstart` use those addresses to
  initialize the variables to 0?

`memmap` is actually a linker script! To learn more about twiddling with them,
here's some [helpful documentation](https://sourceware.org/binutils/docs-2.21/ld/Scripts.html).

#### Exercise 3: The Bootloader (45 min)

The third part of the lab involves reading and understanding how programs get
sent from your laptop to your Pi.

The code for this portion is in the folder
`bootloader`. Specifically, we will be reading the code for
the program that runs on the Pi, receives your program binary from your
computer, then starts it.

The bootloader we are using is a modified version of one written by 
David Welch, the person most
responsible for figuring out how to write bare metal programs on the Raspberry
Pi. If it wasn't for his work, we would not be offering this course.

In order for your laptop to transmit the program binary to the Pi, we have been
using the program `rpi-install.py`. The laptop and the Pi communicate using a
simple file transfer protocol called XMODEM. In the jargon of XMODEM, the host
laptop is called the tranmitter.

The `bootloader.c` program is normally installed on your SD card as
`kernel.img`. When the Pi boots, it loads the bootloader code, and starts
running it. The bootloader program uses the Pi's UART to communicate with the
host (i.e. your laptop). What happens is the Pi receives the binary, loads it
into memory, and then branches to the code to begin execution.

**Sending Programs**

The transmitter first reads in the binary file it wants to send, and then sends 
the bytes to the Raspberry Pi as a series of packets. This is the algorithm
used in the transmitter.

![xmodem image](images/xmodem.jpg)

1. Start the transmission by sending the SOH character, which has the value 
   0x01. SOH is a *control character* which stands for *start of transmission*.

2. Next send the packet number as a byte. The first packet is numbered 1, and 
   the packet number is incremented after each packet is sent.

3. Next send a byte whose value is the complement of the packet number, or 
   `~packet_number`.

4. Send a 128 byte chunk of the binary file.

5. Finally, send a checksum byte.

6. Repeat the above for all the packets being transmitted. When there are no 
   more packets to be sent, send the EOT character; EOT stands for *end of 
   transmission*.

**Receving Programs on the Pi**

You should be in the `cs107e.github.io/_labs/lab4/code/bootloader`
directory.

First, read the assembly language file `start.s`.
Note the `.space` directive between `_start` and the label `skip`.
This has the effect of placing the bootloader code
at location `0x200000`.
This creates a hole in memory
(between 0x8000 and 0x200000).
The bootloader loads your program into that hole.
Why can't the bootloader code also be placed at 0x8000?

Now let's look at the algorithm used to receive the XMODEM
protocol, as implemented in the file `bootloader.c`.
This program, which runs on the Raspberry Pi, is the receiver.

It reads bytes by doing the following:

1. Wait for a SOH.

2. Read the packet number.
The first block must be packet number 1.
The packet number of each packet should be incremented
after each packet is successfully received.
If the receiver sees a packet with the wrong packet number,
the receiver should send the control character `NAK`, for
negative acknowledge, to the transmitter.

3. Check that the complement of the packet number is correct.
How does the C code in bootloader check that the complement is correct?
If the packet number and
the complement of the packet number are not consistent,
send a `NAK` to the transmitter.

4. Read the 128 bytes comprising the payload of the packet.
Incrementally update the checksum when a byte arrives.
The checksum is formed by adding together mod 256 all the bytes in the packet.

	How is this done in the bootloader?
	Suppose we send 128 bytes,
	where the 1st byte is 1, the 2nd byte is 2, and so on, until
	we get to 128th byte which has the value 128.
	What is the value of the checksum in this case?

4. After all 128 bytes have been sent,
read the checksum byte sent by the transmitter.
Compare the checksum sent by the transmitter
with the calculated checksum.
If they agree, send an `ACK` (acknowledge) to the transmitter;
if they do not agree, send a `NAK` (not acknowledge) to the transmitter.

5. If the packet has been successfully received,
copy it to memory,
and prepare to receive the next packet.

6. If the receiver receives the EOT byte,
then the tranmission has ended.
EOT stands for *end of transmission*.
Send an `ACK`,
and then jump to the program memory location.

Where does the bootloader copy the program?
What happens when the bootloader detects an error
which requires it to send a `NAK`?
How does it recover from errors?
Why does it use the timer?

Discuss the bootloader code in detail with your lab mates.
Make sure you understand all of it.

Each group is responsible for
writing a description of the C implementation of the bootloader.
Break the description up into parts,
one for each person in your group.
Assign part of the description to each person.
Each person should write one paragraph
describing the part of the implementation assigned to them.
**Collate your descriptions, and hand in the completed writeup to the CA.**

Here is a helpful diagram as you look through the code.

![bootloader diagram](images/bootloader.jpg)

### Don't forget!

Remember to take a look at the
[Lab 3 extension](https://cs107e.github.io/labs/lab3/#extension-the-stack-and-the-frame).
We have a checklist question for you!
