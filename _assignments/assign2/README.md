---
layout: page
title: 'Assignment 2: Implementing a Clock'
permalink: /assignments/assign2/
released: true
---

**Due: Tuesday, April 25, 2017 at 5:00 PM**

This assignment involves building a 'clock' using a 4-digit 7-segment
display.

The goals of this assignment are:

- Understand bare metal programming in C on the Raspberry Pi.
- Build a simple, modular library of useful functions.
- Learn how to write and use automated test cases to validate your program's behavior.
- Learn how to use the timer peripheral on the Pi.
- Understand how to refresh a 4-digit 7-segment display.

### Set up your assignment

1. For this assignment, we are introducing `libpi`, which contains header files and (binary) 
reference implementations of the code you will be writing throughout the quarter.
You will be creating your own `libpi` library through the course assignments.
Go to the folder where your cloned `cs107e.github.io` repo resides and run `git pull`.
This should give you a `libpi` directory with the relevant files.

2. From there, go to the parent directory (if you `ls`, you should see the `cs107e.github.io` folder) 
and then clone the `assign2` branch from your 107e assignment repo to get the starter code:

   ```
   $ git clone -b assign2 https://github.com/cs107e/[YOUR-GITHUB-USERNAME]-assignments assign2
   ```

   For this and future assignments, it will be important that you clone this branch at this location.
   This means if you are in your `assign2` directory, the new `libpi` folder should live at `../cs107e.github.io/libpi/`.
   To check, cd into the `assign2` folder and try:

   ```
   $ ls ../cs107e.github.io/libpi/
   ```

   Note: If the response is `../cs107e.github.io/libpi/: No such file or directory` then something is wrong.

3. Familiarize yourself with the starter code. Take a look at the provided Makefile. 
   You'll notice that the include depends on the relative path described above. The project
   also includes a few new [magic files](#magic) (`memmap`, `start.s`, and `cstart.c`) that are necessary for C programming.
   We will be explaining their purpose in the upcoming lectures.

### Modules

For the basic part of this assignment, you must implement functions
across three different C files: `gpio.c`, `timer.c`, and `clock.c`.

In the starter code, we have given you stubs for functions you will need to implement. We
have also given you the header files (in
`cs107e.github.io/libpi/include/`) which have prototypes for all these functions.

- `gpio.c` ([header file: gpio.h](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/gpio.h))
    - `gpio_init`
    - `gpio_set_function`
    - `gpio_set_input`
    - `gpio_set_output`
    - `gpio_get_function`
    - `gpio_write`
    - `gpio_read`
- `timer.c` ([header file: timer.h](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/timer.h))
    - `timer_init`
    - `timer_get_time`
    - `delay_us`
- `clock.c` ([header file: clock.h](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/clock.h))
    - `clock_init`
    - `clock_run`

Later in this writeup, we will go into detail about the order in which
we recommend you implement these functions, what they should do, and
how exactly they build on each other.

In general, assignments will follow this kind of structure: we will
give you some function prototypes to implement in some C files.

Each C file is meant to serve as a discrete module in a library of
reusable Raspberry Pi functions that you will build up during the
quarter.

Some of the functions you implement will take parameters, like a GPIO
pin number or a GPIO function type. In those functions, you should
check that the arguments are valid; if they are not, your function
should just return without doing anything.  For example, if someone
tries to turn on GPIO pin 300, catch that and ignore the request;
don't blunder on and do something broken. If the function is expected
to return a value, simply return 0. (This practice of returning 0 on
error isn't great, but at least we've defined the behavior. The C
language has no facility for exceptions.)

We have given you the file `main.c` which has a `main()` that calls
`clock_init()` and `clock_run()`. When you `make` and boot your
program on the Pi normally (as opposed to `make test`), it will call
`main()` in `main.c`, which then calls into the `clock` module.

You should not modify `main.c` at all, because you will
implement all functionality in the `clock` module.

You should not modify any header files in `libpi/include/`;
all your modules should provide exactly the public interface we've
defined. You shouldn't expose extra `gpio_`, `timer_`, or `clock_`
functions, for instance. If you want to declare 'private' (`static`)
helper functions to use within a module, declare them at the top of
that C file.

### Testing <a name="testing"></a>

Now that you're writing larger programs, we want to introduce you to
more sophisticated ways to test your program than in assignment 1. We
hope these ideas will serve you well throughout your programming life.

The starter code for this assignment includes a file `test.c`. The file
defines an alternate `main()` function. Instead of initializing and
running the clock, this `main()` function makes a series of calls to
`assert()` in order to validate the basic operation of the functions
you have implemented in `gpio.c` and `timer.c`. You can run the tests by running `make test`.

Recall from lab2 how `assert()` uses the red and green LEDs
on the Pi as a simple status indicator. If a test fails, the program
halts and blinks the red LED of doom. If there are no failures and the program runs to completion,
the green LED of happiness will light up.  By the time you're done
with this assignment, all the tests should pass. Make that little green light shine!

You can add your own tests here as well. Just make sure that your changes to
`test.c` are not needed for the current tests to pass (in other words, all 
functional code should live in the modules).

### Basic part: a simple clock

1.  **Wire up your breadboard with a 4-digit 7-segment display.**

    Hopefully you finished setting it up in [lab](/labs/lab2). Test it with jumper cables so that
    you know the wiring is correct before you connect it to the Raspberry Pi.

2.  **Connect your Pi so that you can control the display.**

    Connect the Raspberry Pi GPIO pins 20-27 to the 1K current limiting
    resistors that drive the anodes A, B, C, D, E, F, G on your breadboard.

    The 8th pin controls the decimal point, which is optional. Connect
    GPIO pins 10-13 to the base of the transistors controlling digits
    1-4. At this point if you output 3.3V on GPIO 20, and 3.3V on GPIO
    10, you should turn on segment A of digit 1.

3.  **Implement C functions to set a GPIO pin's mode.**

    First, implement this extremely useful function in `gpio.c` to set
    whether a pin is input, output, or some other mode:

        void gpio_set_function(unsigned int pin, unsigned int function);

    You can find a description of the functions and their parameters just above
    their declarations in `gpio.c`.

    When implementing `gpio_set_function`, refer to the various functions
    defined in the documentation for the function select registers. In this
    assignment, we will be using only INPUT and OUTPUT, but make sure
    `gpio_set_function` works for other GPIO functions. Finally, make sure
    these functions can be called multiple times with different pins. Each call
    to `gpio_set_function` should change the function of only the pin passed
    in as an argument; the function of all other pins should be unchanged.

    You should also implement `gpio_set_input` and `gpio_set_output`,
    which are simple wrappers around `gpio_set_function` to set a pin
    as an input or output pin.

    Then you will implement `gpio_get_function`. This is used by
    the [testing framework](#testing) to
    automatically test whether your `gpio_set_function` works.

        unsigned int gpio_get_function(unsigned int pin);

    Now let's test these gpio operations. Review `main()` in `test.c` and comment out
    the calls to `test_timer()` and `test_gpio_read_write()` (you will
    implement the code to make those tests work soon, but not yet).
    Now run `make test`.

    If the green LED on the Pi turns on, all tests ran
    successfully -- hooray! If you see the red LED blinking, this means
    you are failing a test.  If neither LED lights, your program may be freezing or
    crashing somewhere during the tests.

    If you don't get the green light, comment out all tests and then
    add them back one by one to determine which specific test is
    failing. Use that information to narrow in on your bug, and fix
    and re-test until you achieve green light nirvana for all tests in
    `test_gpio_set_function()`.

    Now review the test cases we gave you and consider what **isn't**
    covered. For example, what about testing alternate GPIO functions
    or GPIO pins across the full range of 54? Add tests of your own to
    validate these options. Re-run to verify that you also pass
    your new tests before moving on.

3.  **Implement C functions to turn a GPIO pin on and off.**

    Next, implement another extremely useful function in `gpio.c` for
    controlling GPIO pins, `gpio_write`:

        void gpio_write(unsigned int pin, unsigned int value);

    As in the last step, this function is described in detail above
    its declarations in `gpio.c`.

    Implement this function and add tests to `test.c` to check if `gpio_write` works properly
    (along with the `gpio_set_function` from your last part) by turning 
    on and off various segments on different digits on your display.

    Then you will implement another function, `gpio_read`. This is
    used by the testing framework to test whether your `gpio_write`
    works.

        unsigned int gpio_read(unsigned int pin);

    Now uncomment the call to `test_gpio_read_write()` in
    `test.c`. Rerun the tests. You should be passing the read/write
    tests now! Supplement the starter tests with some test cases
    of your own to make sure these functions work on a variety of the
    other GPIO pins.

4.  **Implement the logic for displaying a numerical digit on a 7-segment
    display.**

    Create an array with 16 entries, one for each hexadecimal value between 0
    and 15. Each entry in the array should be a byte (8-bits). Bit 0 (the least significant) will
    represent segment A, bit 1 segment B, and so on. If a bit is set, then that
    segment should be lit. For example, the bit pattern for `0` is:
    `0b00111111`. (`0b` is what you put in front of a binary number literal,
    just as you'd put `0x` in front of a hexadecimal literal.)

    Bit 7 (the most significant) will be used to represent `DP`, the dot. Since we won't be
    using the dot in this assignment, bit 7 should always be 0.

    Create patterns for all the digits 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C,
    D, E, F. You won't need A-F for this assignment, but they may be useful in
    the future. Test this part by writing a program that displays a number on
    the display.

5.  **Implement a C library to access the Pi's system timer.**

    In order to implement a clock, we'll need some way to determine the passage 
    of time. Thankfully, the Raspberry Pi includes a "system timer", an on-board
    peripheral that is initialized to zero when the Pi powers up and then is 
    continuously incremented once every microsecond behind the scenes.

    Implement the `timer_get_time` function in `timer.c` that fetches the
    current system time from the Raspberry Pi. Chapter 12 of the [Broadcom
    BCM2835 Peripherals
    Manual](http://www.raspberrypi.org/wp-content/uploads/2012/02/BCM2835-ARM-Peripherals.pdf)
    contains the documentation for the system timer peripheral, and the
    function's description is in `timer.c` above its declaration. Note that,
    for this assignment, we only care about the lower 32-bits of the system
    timer.

    Now you can uncomment the call `test_timer()` in `test.c`. You
    should be passing all our library tests now -- super! Now you're ready to implement the clock.

6.  **Write the display refresh loop.**

    Only one set of GPIO pins drives the 7 segments for all of the four digits.
    These pins are _shared_ by the four digits, and we use another, different
    set of pins to control which digit is currently active.

    We are going to drive all four digits by continuously looping over the
    digits one-by-one. In the inner loop, we will turn on a digit, wait a short
    length of time, and then turn off the digit. You might think that turning a
    digit on and off would cause it to flicker. The key is to sequence through
    the digits so fast that our eyes cannot see them changing. Good thing
    computers are fast!

    In order to refresh the display, we will use the `timer_get_time` function
    you implemented in the previous step. We have also provided a function
    `delay_us` that uses `timer_get_time` to wait for the desired number of
    microseconds.

    Implement the display refresh loop. Loop though all four digits, turning
    each on for 2500 microseconds (2.5 milliseconds). Do you see any flicker?

7.  **Finally, implement the clock.**

    In the basic assignment, the clock should display the minutes and
    seconds that have passed since the program began.

    The current time should show as zero when the program
    begins. The inner loop in `clock_run` should perform one refresh
    cycle of the 4-digit display using the current time, and then
    increment the time by the length of time needed to perform the
    refresh. Make sure to test that the timer is calibrated correctly
    so the clock is running at the right rate.

### Extension

One challenge with a clock is setting the time.

Add two buttons to your clock breadboard and connect them to GPIO pins 2 and 3.
Build a user interface that allows you to set the time.

Try to design an interface that is easy to use
and that works even after the clock starts running. It can be
challenging to build an interface with just a few buttons!

Make sure to document your interface in a README.md file so that your grader
can test it out!

### Magic files <a name="magic"></a>

The starter code contains additional code files `start.s` and `cstart.c`. These
files provide the bare minimum of startup needed to set up a C program to run in the
bare metal environment. A bit later in the course, we will discuss what this code
does and why is necessary. In the meantime, sit tight, and don't think about it too much. 
The starter project also includes a file `memmap`, which is used by the linker. We will also
cover why that file is needed soon.
