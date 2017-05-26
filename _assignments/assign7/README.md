---
layout: page
title: 'Assignment 7: System Monitor with Interrupts'
permalink: /assignments/assign7/
released: true
---

*Written by Philip Levis*

**Due: Wednesday, May 31, 2017 at 5:00 PM**

![Google Console](images/google.png)

In this assignment, you'll complete your console. After this assignment, you
will be able to type with a PS/2 keyboard without any worry of characters being
lost because you type too quickly.

### Learning goals

In this assignment, you will

1.  Handle interrupts from your PS/2 keyboard and use them to read scan codes
    queued into a circular buffer.

2.  Modify your keyboard implementation to read scan codes from the circular
    buffer rather than directly from GPIO.

3.  Bundle the collection of modules you've written into a complete,
    self-contained library, where you understand (or you wrote!) every
    line of code in the system.

### Final project

You may find this assignment easier than previous assignments; we want
you to also be planning your final project this week. In particular,
you will need to decide on your team members (1-3 people) and fill out
a [Google form](http://goo.gl/forms/sGdJ1dirG1dm9GRb2) by Sunday night
(May 28). We will set up a repository on GitHub for your team.

Also note that next week, you will need to submit a project proposal
by Thursday night (June 1). We'll talk more about this in class and in
lab. Details about the final project may be found
[in the project assignment writeup](/assignments/project).

### Project build

This final assignment has a somewhat fancier build setup that previous
assignments.  The libpi modules you have created (gpio.c, printf.c,
shell.c, and so on) will be compiled into a complete `libmypi.a`
library, which replaces the reference libpi.

The main program will use your `libmypi.a`, not our reference
`libpi.a`: notice that you now link with `-lmypi` instead of `-lpi` in
the Makefile. This represents a pretty awesome milestone in your
growing mastery of all things system! That `libmypi.a` is a complete,
standalone library, which you can use on its own in any project from
now on.

As before, you can elide a module of yours that isn't trustworthy and
instead substitute our reference module, but the mechanism is slightly
different this time. Open the Makefile and read the comments at the
top to learn how you select modules. The basic gist is the starter
Makefile lists all modules under `LIBPI_STUDENT_MODULES`. If
necessary, you can move a named module to `LIBPI_REFERENCE_MODULES` to
replace yours with ours.

### Fully operational battle station

1.  **Clone the assignment 7 project and copy in files.**

    As always, clone your assignment branch to get the
    starter code. This project is a merge of the assignment 6 and lab 7 code
    along with a somewhat fancier Makefile.

    You should also pull in your `cs107e.github.io` folder to get the
    latest versions of libpi modules and header files.

    You should first copy into your `assign7` all of the .c files for
    the libpi modules you have previously written: `timer.c`,
    `gpio.c`, `printf.c`, `malloc.c`, `backtrace.c`, `keyboard.c`,
    `shell.c`, `fb.c`, `gl.c`, and `console.c`.

    For *this* assignment, since we want you to build a self-contained
    library, you will **also** need to copy the libpi support files
    given to you as source in `cs107e.github.io/libpi/src`, which you
    may have relied on in past assignments even if otherwise using
    your own code. These files are

    ```
    abort.c armtimer.c font.c gpioevent.c gpioextra.c interrupts.c 
    mailbox.c ps2.c reboot.c uart.c register.s vectors.s
    ```

    We've provided a `strtol.c` in the starter code already (taken
    straight from the macOS source code), in case you didn't implement
    the `strtol` extension.

    With your libpi modules and our provided source files, you now
    have all the files you need to build a complete `libmypi.a` from
    source. Use `make` to ensure that your library builds properly and
    can be successfully linked into the main program.

2.  **Set up PS/2 clock interrupts.** Modify `keyboard.c` so that
    `keyboard_init` sets up your system to trigger interrupts when there is a
    falling edge on GPIO pin 23. This is essentially the code you wrote for
    lab 7.

3.  **Handle PS/2 clock interrupts.** Add a new `keyboard_vector` function
    in your keyboard driver, `keyboard.c`. This will be the keyboard's
    interrupt handler.

    In `interrupt_handlers.c`, fill in the `interrupt_vector` function so that it calls the
    `keyboard_vector` function. You'll need to declare a prototype for
    `keyboard_vector` at the top of `interrupt_handlers.c` as well.

    Back in the handler, ensure that you clear events after you
    receive them or the event will keep on triggering forever.  Make
    the handler do something very simple as we did in lab, like toggle
    an LED or increment a counter. Enable global interrupts in
    `main.c` and test that this handler is executing and does not
    crash. Commit your code so you have a known working point.

4.  **Read PS/2 bytes.** Modify your interrupt handler so interrupts feed in
    data bits that the handler interprets into a PS/2 scan code. 
    This should be a basic adaptation of the
    `keyboard_read_scancode` code from assignment 6, except you will be receiving
    one bit per interrupt. Because you are receiving one bit at a time, you
    will need to store the bits as they come until you've received a full byte.
    Be sure to synchronize on the start bit and check the parity and stop bits.

    Test this code by writing received bytes to an array (e.g. a 16 byte array)
    and printing the contents of this array on the screen in `test.c`.
    Once this code is working, commit your code so you have another known
    working point.

    ![PS/2 Packet Format]

5.  **Create a circular buffer.** Write the code for an interrupt-safe
    circular buffer (like the one from lecture) in `circular.c`. Fill
    in functions to check if the buffer is empty or full and to
    enqueue and dequeue elements onto the circular buffer.

    As in lecture, `head` should be the index in the array where you
    will next dequeue (remove) an element, and `tail` should be the
    index where you will next enqueue (insert).  Remember that all
    head and tail increments should be modulo `CAPACITY` so that the
    indices are always within the buffer.

    You may want to write simple tests for your circular buffer in
    `test.c` -- for example, you might enqueue a few times and then
    dequeue.

6.  **Push keyboard scancodes onto circular buffer.** Declare and
    initialize a circular buffer in `keyboard.c`. Modify your
    interrupt handler there to enqueue a scancode into the circular buffer
    when it receives a full byte with valid parity and stop
    bits.

7.  **Process PS/2 scan codes.** Almost there! Modify your
    `keyboard_read_scancode` function to dequeue a byte from the
    circular buffer.  Test out typing on your keyboard. Use the
    routine in the starter `test.c`, which should still work, but
    notice that it will now queue up keys even while paused, so it
    never misses a key.

    Once you get this working,
    you should be able to run your shell program on the monitor just as in
    assignment 6, except this time you should never miss a key!

    You now have a fully operational console!

[PS/2 Packet Format]: images/ps2.png

### Handing in

Commit your code to your repository and make a pull request.

Make sure you add all the necessary source files to Git so that we can
clone your assignment from GitHub and build and run it -- source files
from previous assignments, libpi source files which we've given to
you, and so on. If you're not sure, you could push your submission,
then clone it again from GitHub in a separate `assign7-clone` folder,
then try to run it there.

## Using your libmypi

When you compile this assignment, all your work so far gets bundled
into a single self-contained library, `libmypi.a`. See it in your
assign7 folder?

You can copy this library around and use it to bootstrap future
projects. Here is
[a sample, bare-bones project template](https://github.com/cs107e/cs107e.github.io/tree/master/_assignments/assign7/libmypi-usage)
which builds with libmypi.

To start a new project, copy those template files into a folder, copy
your `libmypi.a` in, and point the `CS107E` in the Makefile to your
CS107e folder (to get the header files in `libpi/include`, not any
code or libraries). Then you should be able to `make install` right
away and see that the `main()` in `main.c` runs and prints "Hello,
world!" You can program your Pi almost like an Arduino with this
high-level library you wrote.

## Complete system bonus

If you use only your own libpi modules for this assignment (no use of
reference modules) and your interrupt-driven console works correctly, 
you will receive a full 5-point bonus. This is a big reward for a big 
accomplishment -- you have built the complete system yourself, from the ground up!

We will not retest all your modules to the extent that they were
tested when grading each assignment, but all shell commands should at
least work correctly. This means, for example, your printf must handle
printing padded hexadecimal numbers (which are needed for `peek`), but
need not necessarily handle negative values perfectly (since they are
not used in the full shell).

The assign7 Makefile contains an "info" target to report the
contents of libmypi.a. Use `make info` to see which of your 
modules are being used and which reference modules are used to
complete the set.

To be considered for the bonus, libmypi.a must use your own code
for all modules, with no use of the reference modules.

In addition to your own modules, libpi also contains a few support
modules (uart.c, gpioevent.c and so on) that we provided to you.  You can
[review those source files here](https://github.com/cs107e/cs107e.github.io/tree/master/libpi/src). 
You should have copied the source files into your assignment in step 1 above,
so they will be part of your `libmypi.a` as well.

If you fulfill this bonus, you've successfully built a complete
computer system, and every line of code for that system is sitting in
your assign7 folder. Congratulations!

## Extensions

Each of these counts as a separate extension. You can do neither, one, or both.

### Extension 1: Profiling

One extension is to add profiling support to your shell. Profiling allows you to 
understand which instructions your code spends the most time executing. This 
involves setting up periodic 
timer interrupts and recording where the current program counter is at the time
the interrupt occurs. 
For this part, you will handle timer interrupts, write profiling code,
and add an additional command to your shell.

The header file `gprof.h` in `cs107e.github.io/libpi/include` declares
the interface to the profiling functions.

The `gprof_init` function should allocate space for an array of
counters, one for each instruction address in the text (code) segment.

There is a known address where the text segment starts (what value is
that again?), but to know the extent, you will need to edit the linker
map to mark the end.  It may help to revisit [lab4](_labs/lab4) for
information on linker maps.

Open the project file `memmap` and, patterning after
how symbols are used to mark the bounds of the bss section, add a symbol to identify
the end of the text section. Use this symbol in `gprof_init` to compute the
correct amount of space needed to have a counter for each instruction in the text segment.
All of those counters should be initialized to zero at the start of profiling.

`gprof_init` should configure a timer interrupt scheduled for the
interval defined in `gprof.c` using the libpi `armtimer` module.  (See
the libpi header file
[`armtimer.h`](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/armtimer.h)).

When profiling is turned on, enable the timer interrupt.
`gprof_vector` is the interrupt handler function. It takes one
argument, the value of the PC at the time of the interrupt.  The
handler should increment the counter for that value of the PC.  Your
handler `gprof_vector` is to be called on a timer interrupt. To do so,
you will need to differentiate between GPIO and timer interrupts,
since both call `interrupt_vector` in `interrupt_handlers.c`.

`gprof_dump` should print the highest 10 counts to the console (in any
order) using the print format given in the comment.

Once this is working, add the command `profile [on | off | status | results]` to
your shell commands. `profile on` should initialize or zero-out all profile
counts and start profiling (enable timer interrupts). `profile off` should stop
the profiling (disable timer interrupts). `profile status` should print `Status:
on` or `Status: off`, depending on whether the profiler is on or off,
respectively. `profile results` should print current (if status is on) or most
recent (if status is off) counts to the debugger console using the `gprof_dump`
function.

You now have a profiler!

### Extension 2: PS/2 mouse and paint application

For this extension, you'll write a small paint application using your
`libmypi.a`.

Go to the `paint` subdirectory in your assign7 directory. We've
provided one starter file, `mouse.c`, but you'll add files around it
so that the `paint` directory is actually a complete standalone
application, with its own `Makefile` and everything.

Copy the starter project files in
`cs107e.github.io/_assignments/assign7/libmypi-usage` into `paint`,
and copy your `libmypi.a` in as well. Edit the CS107E path in the
Makefile.

Make sure you can build and run the "Hello, world" application right
now.

Let's start implementing mouse support. Read these pages on the
[PS/2 protocol](http://www.computer-engineering.org/ps2protocol/) and
[PS/2 mouse specifically](http://www.computer-engineering.org/ps2mouse/)
for details on how to talk to a mouse.

Connect your mouse clock to GPIO pin 25 and mouse data to GPIO
pin 26. Add `mouse.o` to the `OBJECTS` in your Makefile.

Start by writing `mouse_read_scancode`. For now, just poll pins 25 and
26 to read the next scancode; it should be almost identical to your
old polling `keyboard_read_scancode` from before this assignment. You
might want to bring `wait_for_falling_clock_edge` over as a helper,
but make it wait on the mouse clock instead.

Next, implement `mouse_write`, the other half of the PS/2 protocol:
sending a byte from the Pi to the mouse. We need to tell the mouse to
set up before it'll send us anything. See "Host-to-Device
Communication" on the PS/2 protocol page for the full write
process. Here are some notes:

- You need to reconfigure the mouse's GPIO pins temporarily here: set
mouse clock and mouse data pins as outputs so you can pull them low
when needed. 'Release' (set as input again) the clock line after you
delay 100 us and write the start bit, and release the data line after
you write the parity bit and see a falling clock edge.

- Over the course of a write, you should wait for a falling clock edge
11 times (before sending each of 8 data bits, before sending the
parity bit, before releasing the data line, and before reading the
acknowledgment bit from the mouse). After that last falling clock
edge, spin until the data line goes high (that's the end of the ack
bit transmission).

Now carry out the mouse initialization sequence (as specified on the
PS/2 mouse page) in `mouse_init`:

1. Write a Reset scancode to the mouse to put it in Reset mode.
2. Read the ACK scancode from the mouse (should be 0xFA).
3. Read the BAT Successful scancode from the mouse (should be 0xAA).
4. Read the Device ID scancode from the mouse (should be 0x00).
5. Write the Enable Data Reporting scancode to the mouse.
6. Read the ACK scancode from the mouse (should be 0xFA).

Run `mouse_init` from `main.c` and confirm that the mouse is sending
you the scancodes you expect during this sequence. After calling
`mouse_init`, you should be able to read and print movement scancodes
from the mouse in a loop.

Next, let's use interrupts to read scancodes from the mouse instead of
polling.

Copy the `cstart.c` and `interrupt_handlers.c` from your basic
assignment 7 into `paint`, since now we want interrupt support. Add
`interrupt_handlers.o` to the `OBJECTS` in your Makefile.

Rewrite `interrupt_vector` to just call the `mouse_vector` function,
then write the `mouse_vector` function, which should be an event
handler which builds up a bit of the scancode and eventually sticks it
in a circular buffer, just as with your keyboard handler.

Then make `mouse_read_scancode` pull a scancode out of the circular
buffer instead of polling. Make sure you can still read scancodes in a
loop.

Now implement the high-level `mouse_read_event` function on top, which
you will call from your paint program to read mouse-movement
events. See the `libpi/include/mouse.h` file for more details on the
`mouse_event_t` structure, and consult the PS/2 mouse page to find how
scancode bits map to event details. Be careful about the 9-bit two's
complement representation of distances! Test this function with a loop
in `main.c`.

Now you can read mouse events! Finally, implement a paint application
in `main.c`: initialize the graphics library in single-buffer mode,
then loop, reading mouse events and drawing on the screen in response
to them.

It should be possible to:

- draw stuff [like a smiley face :-)] by holding down the left mouse
button and moving the mouse
- when not holding down the button, move some mouse pointer-like shape around on
the screen without disrupting stuff that's been painted

Other than that, the details of the UI are up to you. Describe in your
README how we should use your paint program!
