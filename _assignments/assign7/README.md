---
layout: page
title: 'Assignment 7: System Monitor with Interrupts'
permalink: /assignments/assign7/
---

**Due: Tuesday, May 24, 2016 at 6:00PM**

![Google Console](images/google.png)

In this assignment, you'll complete your console. After this assignment, you
will be able to type with a PS/2 keyboard without any worry of characters being
lost because you type too quickly.

### Learning goals

In this assignment, you will

1.  Handle interrupts from your PS/2 keyboard and use them to read scan codes
    into a circular buffer.

2.  Modify your keyboard implementation to read scan codes from the circular
    buffer rather than directly from GPIO.

### Final project

This assignment is easier than previous assignments because we want you to also
be planning your final project this week. In particular, you will need to decide
on your team members (1-3 people) and fill out a 
[Google form](http://goo.gl/forms/sGdJ1dirG1dm9GRb2) by Sunday night
(May 22). We will set up a repository on GitHub for your team.

Also note that next week, you will need to submit a project proposal by Thursday
night (May 26). We'll talk more about this in class and in lab. Details about
the final project may be found [here](/assignments/project).


### Bonus

As a reminder, if you use only your own modules for this assignment
(this means not switching any of the modules listed in the Makefile
under LIBPI_STUDENT_MODULES to LIBPI_REFERENCE_MODULES) and your shell
works correctly, you will receive a 5-point bonus, equivalent to one
extra extension. This is meant to reward you for building a complete
system yourself!

Your Makefile should have at least these modules in
LIBPI_STUDENT_MODULES:

```
LIBPI_STUDENT_MODULES = printf.o gpio.o timer.o fb.o malloc.o gl.o console.o
```

If you do have all these modules there, then we will automatically consider your
submission for the bonus.

We will not retest all your modules to the extent that they were
tested originally for each assignment, but the functionality of each
must be sufficient that all shell commands work correctly. This means,
for example, your printf must handle printing padded hexadecimal
numbers (which are needed for `peek`), but need not necessarily handle
negative values perfectly (since they are not used in the full shell).

Notice that for all the libpi modules besides those above, you can [check out
their source
code](https://github.com/cs107e/cs107e.github.io/tree/master/libpi/src). So if
you fulfill this bonus, you've successfully built a complete computer system,
using code that you either wrote yourself or can see at that link.
Congratulations!

### Fully operational battle station

1.  **Pull the assignment 7 project.**

    As always, clone your assignment branch to get the
    starter code. This project is a merge of the assignment 6 and lab 7 code.
    You will need to copy in `keyboard.c` and `shell.c` from assignment 6,
    as well as any other needed modules listed in the Makefile that you don't 
    plan to pull from the reference libpi.
    
    Once you have copied in the files you plan to use, ensure that `make` 
    compiles your code successfully.

2.  **Set up PS/2 clock interrupts.** Modify `keyboard.c` so that
    `keyboard_init` sets up your system to trigger interrupts when there is a
    falling edge on GPIO pin 23. This is essentially the code you wrote for
    lab 7.

3.  **Handle PS/2 clock interrupts.** Add a new `keyboard_vector` function
    in your keyboard driver, `keyboard.c`. This will be the keyboard's
    interrupt handler.

    In `interrupt-handlers.c`, fill in the `interrupt_vector` function so that it calls the
    `keyboard_vector` function. Back in the handler, ensure that you clear
    events after you receive them or the event will keep on triggering forever.
    Make the handler do something very simple as we did in lab, like toggle an
    LED or increment a counter. Enable global interrupts in `main.c` and test
    that this handler is executing and does not crash. Commit your code so you
    have a known working point.

4.  **Read PS/2 bytes.** Modify your interrupt handler so interrupts feed in
    data bits that the handler interprets into a PS/2 scan code. 
    This should be a basic adaptation of the
    `keyboard_read_scancode` code from assignment 6 except you will be receiving
    one bit per interrupt. Because you are receiving one bit at a time, you
    will need to store the bits as they come until you've received a full byte.
    Be sure to synchronize on the start bit and check the parity and stop bits.

    Test this code by writing received bytes to an array (e.g. a 16 byte array)
    and printing the contents of this array on the screen in your main loop.
    Once this code is working, commit your code so you have another known
    working point.

    ![PS/2 Packet Format]

5.  **Create a circular buffer.** Write the code for a circular buffer
    in `circular.c`. Fill in functions to check
    if the buffer is empty or full and to enqueue and dequeue elements onto 
    the circular buffer.
    Remember that all head and tail increments should be modulo `CAPACITY` so
    that the indices are always within the buffer.

6.  **Push keyboard scancodes onto circular buffer.** Modify your interrupt handler
    to push a scancode into the circular buffer when it receives a full byte with
    valid parity and stop bits. Adapt your prior test program so that it
    removes scancodes from the circular buffer and displays them on the screen.

7.  **Process PS/2 scan codes.** Almost there! Modify your `keyboard_read_scancode`
    function to pop bytes from the circular buffer until it removes a
    full scancode. Test out typing on your keyboard. Once you get this working,
    you should be able to run your shell program on the monitor just as in
    assignment 6, except this time you should never miss a key!

    You now have a fully operational console!

[PS/2 Packet Format]: images/ps2.png

### Handing in

Commit your code to your repository and make a pull request.

## Extensions

Each of these counts as a separate extension. You can do neither, one, or both.

### Extension 1: Profiling

One extension is to add profiling support to your shell. Profiling allows you to 
understand which instructions your code spends the most time executing. This 
involves setting up periodic 
timer interrupts and recording the current program counter when an interrupt occurs. 
For this part, you will handle timer interrupts, write profiling code,
and add an additional command to your shell.

`gprof.h` includes the profiling function that you will need to implement in 
`gprof.c`.
The interface and implementation to set up timer interrupts is provided in the 
libpi `armtimer` module. You can set up a timer interrupt to fire at the interval
defined in `gprof.h`.
You will need to implement a timer interrupt handler that records the current PC
in the profiler. Call this handler when there is a timer interrupt. To do
so, you will need to differentiate between GPIO and timer interrupts in
`interrupt_vector` in `interrupt_handlers.c`.

The `gprof_init` function from `grof.c` should allocate space to store counts for each
address in the text (code) segment. Each time there is a timer interrupt, the count 
for the current program counter should be incremented.
`gprof_dump` should print the counts to the console using the print format given 
in the comment.

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

We've provided a file `mouse.c` in your starter code. You should implement the
`mouse_write` and `mouse_vector` functions. See these pages on the [PS/2
protocol](http://www.computer-engineering.org/ps2protocol/) and [PS/2 mouse
specifically](http://www.computer-engineering.org/ps2mouse/) for details on how
to talk to a mouse.

Connect your mouse clock to GPIO pin 25 and mouse data to GPIO pin 26.

`mouse_write` should implement the other half of the PS/2 protocol: PS/2 write
from the Pi to the mouse ("Host-to-Device Communication" on the PS/2 protocol
page). You might need to reconfigure the mouse's GPIO pins temporarily here.

`mouse_vector` should be an event handler which builds up a bit of the scancode
and eventually sticks it in a circular buffer, just as with your keyboard
handler.

Make sure your `keyboard_vector` function checks that there was a falling edge
event on the keyboard clock, and your `mouse_vector` function checks that there
was a falling edge event on the mouse clock (otherwise, they should ignore the
event). Now call both vectors in sequence from your `interrupt_vector`.

Then implement `mouse_read_scancode`. You should now be able to carry out the
mouse initialization sequence (as specified on the PS/2 mouse page):

1. Write a Reset scancode to the mouse to put it in Reset mode.
2. Read the ACK scancode from the mouse.
3. Read the BAT Successful scancode from the mouse.
4. Read the Device ID scancode from the mouse.
5. Write the Enable Data Reporting scancode to the mouse.

Make sure the mouse is sending you the scancodes you expect during that
sequence. After this sequence, you should be able to read movement
scancodes from the mouse in a loop.

Next, implement the high-level `mouse_read_event` function on top, which you
will call from your paint program to read mouse-movement events. See the
`libpi/include/mouse.h` file for more details on the `mouse_event_t` structure.

Now you can read mouse events! Finally, add a new command to your shell,
`paint`, with a handler named `cmd_paint`.

It should be possible to:
- run the `paint` command
- draw stuff [like a smiley face :-)] by holding down the left mouse button and moving the mouse
- when not holding down the button, move some mouse pointer-like shape around on
the screen without disrupting stuff that's been painted
- exit to the original shell somehow (by right-clicking, for example)

We recommend that you rerun `gl_init` to enter single-buffer mode when painting
starts, then rerun `gl_init` again to go back to double-buffer mode when the
user exits the paint program.

Other than that, the details of the UI are up to you. Describe in your README
how we should use your paint program!
