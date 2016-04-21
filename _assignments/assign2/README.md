---
layout: page
title: 'Assignment 2: Implementing a Clock'
permalink: /assignments/assign2/
---

**Due: Tuesday, April 19, 2016 at 6:00PM**

This assignment involves building a 'clock' using a 4-digit 7-segment
display.

The goals of this assignment are:

- Understand bare metal programming in C on the Raspberry Pi.
- Learn how to automatically test programs while programming.
- Build a simple, modular library of useful functions.
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

   Note: If you see `-bash: cd: ../libpi/: No such file or directory` then something is wrong.

3. Familiarize yourself with the starter code. Take a look at the provided Makefile. 
   You'll notice that the include depends on the relative path described above.

### Modules

For the basic part of this assignment, you must implement functions
across three different C files.

We have given you stubs of these functions in the starter code. We
have also given you the header files (in
`cs107e.github.io/libpi/include`) which declare all these functions.

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

We have given you a file `main.c` which just calls `clock_init` and
`clock_run`. When you `make` and boot your program on the Pi normally
(as opposed to `make test`), it will enter `main()` in `main.c`, which
then calls into the `clock` module.

You should not have to modify `main.c` at all, because you will
implement all functionality in the `clock` module.

### Testing

Now that you're writing larger programs, we want to introduce you to
more sophisticated ways to test your program than in assignment 1. We
hope these ideas will serve you well throughout your programming life.

The starter code for this assignment includes a file `test.c`.

This file includes a series of basic tests which will not work until
you've implemented more of the assignment.

You can run the tests by running `make test`.

If a test fails, the red LED on the Pi will blink. By the time you're
done with this assignment, all the tests should pass.

You can add your own tests here as well. Just make sure that your changes to
`test.c` are not needed for the current tests to pass (in other words, all 
functional code should live in the modules).

### Basic part: a simple clock

1.  **Wire up your breadboard with a 4-digit 7-segment display.**

    Hopefully you finished setting it up in [lab](/labs/lab2). Test it so that
    you know the wiring is correct before you connect it to the Raspberry Pi.

2.  **Connect your Pi so that you can control the display.**

    Connect the Raspberry Pi GPIO pins 20-27 to the 1K current limiting
    resistors that drive the anodes A, B, C, D, E, F, G on your breadboard.

    The 8th pin controls the colon, which is optional. Connect GPIO pins 10-13
    to the base of the transistors controlling digits 1-4. At this point if you
    output 3.3V on GPIO 20, and 3.3V on GPIO 10, you should turn on segment A
    of digit 1.

3.  **Implement C functions to set a GPIO pin's mode.**

    First, implement this extremely useful function in `gpio.c` to set
    whether a pin is input, output, or some other mode:

        void gpio_set_function(unsigned int pin, unsigned int function);

    You can find a description of the functions and their parameters just above
    their declarations in `gpio.c`.

    When implementing `gpio_set_function`, refer to the various functions
    defined in the documentation for the function select registers. In this
    assignment, we will just be using INPUT and OUTPUT, but make sure
    `gpio_set_function` works for other GPIO functions. Finally, make sure
    these functions can be called multiple times with different pins. Each call
    to `gpio_set_function` should only change the function for the pin passed
    in as an argument; other pins should remain in the same mode.

    Then you will implement `gpio_get_function`. This is used by
    the testing framework (see the previous section of the writeup) to
    automatically test whether your `gpio_set_function` works.

        unsigned int gpio_get_function(unsigned int pin);

    Now look at `main()` in `test.c`. Comment out the calls to
    `test_timer()` and `test_gpio_read_write()` (you will implement
    the code to make those tests work soon, but not yet), do `make
    test`, and ensure the red LED on the 
    Pi is not blinking. If it is blinking, you are not passing a test. 
    You should comment out the tests and then add them back one by one to 
    determine what test is failing. Also add tests to make sure alternate
    GPIO functions also work. Make sure to test on a variety of the 54 GPIO pins.

    Make sure the Pi's red LED doesn't blink: you should be passing
    all the tests in `test_gpio_set_function()` at this point!

3.  **Implement C functions to turn a GPIO pin on and off.**

    Next, implement another extremely useful function in `gpio.c` for
    controlling GPIO pins, `gpio_write`:

        void gpio_write(unsigned int pin, unsigned int value);

    As in the last step, this function is described in detail above
    its declarations in `gpio.c`.

    Implement this function and add tests to `test.c` to manually test it 
    (along with the `gpio_set_function` from your last part) by turning 
    on and off various segments on different digits on your display.

    Then you will implement another function, `gpio_read`. This is
    used by the testing framework to test whether your `gpio_write`
    works.

        unsigned int gpio_read(unsigned int pin);

    Now uncomment the call to `test_gpio_read_write()` in
    `test.c`. Rerun the tests. You should be passing the read/write
    tests now! Now, add some assert tests to make sure this works on 
    a variety of the other GPIO pins.

4.  **Implement the logic for displaying a numerical digit on a 7-segment
    display.**

    Create an array with 16 entries, one for each hexadecimal value between 0
    and 15. Each entry in the array should be a byte (8-bits). Bit 0 will
    represent segment A, bit 1 segment B, and so on. If a bit is set, then that
    segment should be lit. For example, the bit pattern for `0` is:
    `0b00111111`.

    Typically, bit 7 is used to represent `DP`, the dot. Since we won't be
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
    should be passing all our library tests now, but that doesn't mean
    you're done!

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

    The clock will display the minutes and seconds that have passed since the 
    program began or the time was set (for the extension).

    The current time should be initialized to zero when the program
    begins. The inner loop in `clock_run` should perform one refresh
    cycle of the 4-digit display using the current time, and then
    increment the time by the length of time needed to perform the
    refresh. Make sure to test that the timer is calibrated correctly
    so the clock is running at the right rate.

### Extension

One challenge with a clock is how to set the time.

Add two buttons to your clock breadboard and connect them to GPIO pins 2 and 3.
Build a user interface that allows
you to set the time. Try to design an interface that is easy to use. It can be
challenging to build an interface with just a few buttons!

Make sure to document your interface in a README.md file so that your grader
can test it out!

### Magic Files

The starter code contains an extra file `start.s`. You must have this file if
you are calling functions in bare metal programs. This file sets up the stack
pointer. We will discuss why functions need a stack next Friday in class. In
the meantime, sit tight, and don't think about it too much. The starter code
also includes a file `memmap`, which is used by the linker. We will also
cover why that file is needed soon.
