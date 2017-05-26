---
layout: page
title: 'Assignment 3: Implement a String Formatting Library'
permalink: /assignments/assign3/
released: true
---

*Written by Pat Hanrahan; edited by Isabel Bush*

**Due: Tuesday, May 2, 2017 at 5:00 PM**

Space is often at a premium when we program embedded computers.
Many of the C standard libraries are surprisingly large,
and it's useful to have simpler versions of standard functions.

`printf` is particularly useful,
since printing is the most basic form of debugging.

After you finish this assignment, you should

- understand C strings and characters,

- understand how to convert basic C types (`int`, `int*`, ...) to a string,

- know how to reuse your GPIO and timer code from the previous assignment, and

- be able to use the UART library shown in class to communicate with your laptop.

This can be a difficult assignment, so start early and practice good
development and debugging techniques, just like you learned in lab.

Students who struggled in the past generally wrote too much code
before testing it. Try to implement this assignment in little
increments, making a small, testable improvement each time. If it
doesn't work, you'll at least know exactly where to find the mistake.

Remember to decompose your code into simple, clearly-defined
functions. Your code will be easier for you to debug and easier for
your graders to understand.  There are no length requirements, but as
a guideline, the cleanest versions from previous years have included
10-15 functions and 200-300 lines of code.

### Set up your assignment

Clone your `assign3` repository branch as you have done in previous assignments.
You will find `printf.c`, where you will be writing most of your code. There is
also `strtol.c`, which is for the extension, and `main.c`, `test.c`, and
`assert.h`, which may all be used to test out functions in your `printf` and
`strtol` modules.

Assuming you are using your own module versions, you will need to copy in your
`gpio.c` and `timer.c` files from `assign2` into the `assign3` directory. See
the `Makefile` for more information on reusing code from previous assignments.

In this assignment, you will be filling in the functions in `printf.c`. You
should also be adding tests to `test.c` to test your
final `printf` implementation.

Please avoid modifying `main.c` in this and future assignments so
that we can be sure that your assignment solution obeys the same
interface we expect.

### Requirements

For the basic part of this assignment, you must implement functions
in just one file, `printf.c`.

- `printf.c`
  ([header file: printf.h](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/printf.h))
    - Not in the header file, but expected to be part of your implementation:
      - `unsigned_to_base`
      - `signed_to_base`
    - `snprintf`
    - `vsnprintf`
    - `printf`

For the extension, you should implement `strtoul` in `strtol.c`.

### Basic part: basic formatting functions

In this section, you're going to implement several functions that generate
strings from an input format. To start you'll convert numbers to strings in a
given base, and then use this to create a general-purpose routine that can mix
strings and numbers into the same format. Two things to note before we start:
- One strategy for these functions is to allocate a buffer up front and
  write the full string into that buffer, then copy what you need into the
  final destination. For simplicity, you can assume a function will never
  be asked to generate a string of length greater than 1024 characters
  (regardless of the size of the destination buffer), so your up-front
  allocation can be a fixed size of 1024 characters.
- For every function you have to implement, we define rules for what inputs
  are valid and invalid. Your functions are not expected to check for or handle
  any invalid inputs, e.g. a negative base or a malformed format string.
  The specifications are long, so please read them carefully, but
  ask on Piazza or in office hours if you have any questions.

1.   **Implement integer formatting functions.**

     ```c
     int unsigned_to_base(char *buf, int n, unsigned int val, int base, int width);
     int signed_to_base(char *buf, int n, int val, int base, int width);
     ```

     These functions will take a number and write it as a string to a buffer
     subject to several constraints.

     In these functions, `buf` is a character array to store
     the string representing the number.

     The size of the buffer is `n`. It is always nonnegative.
     Do not write past the end of the buffer!

     `val` parameter is the integer value to be converted to a string.
     In the `signed` function, if the value is negative, you will
     need to include a minus sign in the string.

     The string representation of the number should be in the given `base`, so
     if `base` is 2 then binary, 10 is decimal, and 16 is hexadecimal. You can
     assume `2 <= base <= 16`, but you should not write a
     different case/function for each possible base! You should also not
     copy/paste code between the two functions&mdash;try using the
     `unsigned` function in the `signed` function.

     The `width` is the minimum number of characters the caller wants written into `buf`.
     If `width` is more characters than needed to fit the formatted value, pad the
     string with zeros on the left so that it has length `width`. If `width` is
     fewer characters than needed to hold the formatted value, ignore the `width`
     parameter. The minus sign should precede the zero padding and is included
     in the `width`. `width` is always nonnegative.

     You should null-terminate what you write into `buf`; all valid C
     strings are null-terminated, and there is no other way for the
     caller to know where your output stops.

     `n` is a hard upper limit on how much room you have; if `n` is
     too small to fit your output, even if `width` says you should go
     past it, you must cut your output off and make `buf[n - 1]` (your
     n-th character output) a null terminator. (Otherwise, you would be
     trashing some other memory past the end of the buffer.) Note that `n` can
     be zero, and if so, you should not write a null terminator.

     These functions should return the number of characters written to
     `buf` if there is room to fit them all. If not, it should return
     the number of characters that would have been written if there
     were room. This count excludes the null terminator.

     For example, if you call `signed_to_base(buf, 5, -1234, 10, 6)` then
     it should put `"-012\0"` (`'\0'` being the null terminator) as the
     first 5 bytes of `buf`, and return `6`.

     Remember that it is easier to debug small steps than large changes,
     so make sure these functions are working before you move on.

     (You could test these functions locally on your laptop by
     compiling using gcc and printing the values written by your
     functions using `printf` from the standard C library
     [[see the guide](/guides/native)], by using the gdb simulator from lab to
     examine the strings, or by adding assertion tests.)

     Take a look at the tests in `test.c`. We've given you an example test case
     in `test_to_base`. Write other similar tests for negative numbers and other
     unusual inputs. Test thoroughly by thinking about what are edge cases that
     might fail given your implementation. With *test-driven development*, you
     write many tests like this before implementing the functions. Each fix you
     make to the code should just try to pass one more test. If your tests are
     well-designed, once you are passing all tests, you know your code is
     working correctly!

     Once you have this part working, it would be a good time to commit your code
     (using `git add` and `git commit` commands).
     Then if something breaks later on, you can always return to this known-good state.


2.  **Implement basic `snprintf`.**

    <img src="snprintf.png" width="200">

    ```c
    int snprintf(char *s, int n, const char *format, ... );
    ```

    The `printf` family of functions use what's called "formatting strings" to
    allow you to more easily combine together different kinds of values into
    a single string. Look at the [C++ reference](http://www.cplusplus.com/reference/cstdio/printf/)
    for some examples of using `printf`. By default `printf` prints to the screen
    (or standard out to be specific), but `snprintf` instead "prints" to a string.
    For more information about printf or other C functions, you can type `man snprintf`
    to bring up its manual.

    Your version need not have all the options of the standard version.
    We will implement a simple version that handles the most common use cases.

    ```
    "%c" - print a char
    "%s" - print a string
    "%d" - print an int in decimal
    "%x" - print an int in hexadecimal
    "%b" - print an int in binary
    ```

    When implementing these functions, note that `%d` should treat the argument
    as a signed number, and `%x` and `%b` should treat the argument as unsigned.
    This lines up with how you should have written your `unsigned_to_base` and
    `signed_to_base` functions above -- so use your helper functions!

    The formatting codes for integers should optionally contain a
    width: as well as supporting `%[c, s, d, x, or b]`, support formatting codes of the form
    `%0[WIDTH][d, x, or b]`.
    For example, `"%014x"` would be a string of at least 14 characters (padded
    with zeros on the left as necessary) which is the hexadecimal representation
    of some value. You do not need to support a width for the `c` or `s` codes.

    Just as with the helper functions, `snprintf` should return the number
    of characters written if they fit in the buffer, or the number of characters
    that would have been written if there were room. Again, `n` is the
    buffer size that you're allowed to write to, and you should
    null-terminate your output.

    And again, remember that incremental steps are the key to success. First,
    implement a version of snprintf that can handle string constants and
    test it with simple examples such as `snprintf(buf, BUF_SIZE, "Hello, World!")`.
    Make sure you can pass the simplest test in `test.c`. Then add functionality
    to handle the `%d` format and comment in tests in `test.c` to test this
    functionality. Also add your own tests as the example tests are not comprehensive.
    When you are satisfied it works, add `%x`, `%b`, etc., adding in the appropriate
    tests as you go.

    See the note below about how to create functions
    with variable numbers of arguments.

4.  **Extract `snprintf` code into `vsnprintf`.**

    ```c
    int vsnprintf(char *s, int n, const char *format, va_list args);
    ```

    In the next step, you will be writing `printf` using much of the same code needed
    for `snprintf`. However since `snprintf` requires a variable number of arguments,
    you cannot call it directly from `printf`.

    Thus you will need to create a helper function `vsnprintf` (that takes a
    `va_list` parameter), which you can then call from both `snprintf` and `printf`, once you
    have created the `va_list` arguments as shown in the example below.

    This should be a quick step involving moving most of your `snprintf` code into `vsnprintf`.
    Once you have completed this refactor, make sure you are still passing all of your
    `snprintf` tests.

    Note that because of obscure rules in the C standard about
    "[default argument promotions](http://stackoverflow.com/questions/1255775/default-argument-promotions-in-c-function-calls)",
    you cannot ask `va_arg` for the `char` type. Instead you must ask it for an `int` and then
    cast the `int` to a `char`.

4.  **Implement `printf`.**

    Use your `vsnprintf` to implement `printf`,
    which should output characters to the mini uart using `uart_putc` from the
    `uart` module. You may again assume a maximum string length of 1024 characters.

    ```c
    int printf(char *format, ... );
    ```

    By now, you should be familiar with testing your code step by step. Hopefully you
    have been writing mini-tests all along to verify your functions.
    To test `printf`, you can run the code in `main.c`, which should print some
    useful information to your screen.

    This only tests basic `printf` functionality,
    so make sure you should add your own tests to this as well.
    You should include at least one
    test for each type of `printf` argument (`%c`, `%s`, `%b`, `%d`, `%x`), with and without
    a width defined. For example, such tests might look like

    ```c
    printf("%d = -5\n", -5);
    printf("%b = 101\n", 5);
    printf("%04x = 00ab\n", 0xab);
    ```

    Also make sure you add tests for unusual cases. What happens if you try
    `printf("")`? What about `printf("\n")`? If you are ever unsure of what
    should be printed, compile the test with the standard library `printf`
    implementation and compare the output to your `printf` output.

#### Using variable numbers of arguments

`printf` is a function that takes a variable number of arguments.
C has standardized the way to access variadic functions
using the `stdarg.h` interface.
Here is an example.

```c
#include <stdarg.h>
#include <stdio.h>

int sum(int n, ...)
{
    int sum = 0;
    va_list ap;

    va_start(ap, n);
    for( int i=0; i<n; i++ )
        sum += va_arg(ap, int);
    va_end(ap);

    return sum;
}

int main(void)
{
    printf("%d\n", sum(3, 1, 2, 3) );
    return 0;
}
```

See how we declare a function with a variable number
of arguments using `...`?

The function `sum` has one required argument `n`,
followed by a variable number of additional arguments.
This function should be called with `n` additional arguments.
For example, we call it from main as `sum(3, 1, 2, 3)`.

In general, variable-argument functions still require at least
one named argument.
It should be possible to determine the number of arguments
from the first argument -- `n` in this case, or the format string in
the case of `printf`.

The function `sum` shows how to use `stdarg.h`.

First, we declare a variable `ap` as type `va_list`.
This variable is initialized using `va_start`, which is passed the
last named argument -- in this case, we tell `va_start` that `n` is
the last argument before the variable arguments begin.

Then we loop over the `n` arguments.
We fetch the next argument using `va_arg(ap, type)`.
The types can be different for each argument.
You need to know the type for this to compile correctly.
In this case, we assume all the arguments are of type `int`.
When we are done, we call `va_end(ap)` to clean up after ourselves.

For more details about `stdarg`,
read the [Wikipedia page on stdarg.h](http://en.wikipedia.org/wiki/Stdarg.h).

### Extension

Implement the function `strtoul`.

```c
unsigned long strtoul(const char *nptr, char **endptr, int base);
```

`strtoul` will convert string numbers to their unsigned long value.
You should implement this extension in the file `strtol.c`.
There is some documentation in the comment above the function, but you
should check out the man page (type `man strtoul`
on the command line) to learn more details about this function.
You only need to handle binary (base 2), decimal (base 10), and hexadecimal
(base 16) conversions, as well as handling decimal and hexadecimal values
when the provided base is 0.

You need not handle leading white space (you may assume that the first character
is part of the conversion). You also do not need to handle negation, so you
can stop the conversion if you see a '+' or '-' sign in the conversion string.
You should handle invalid
inputs in which the string (or parts of the string) cannot be converted to a
numerical value. If `endptr` is not NULL, you should assign it to point to
the remainder of the string after conversion, i.e. those characters in the
string that were not converted because they were invalid or the null terminator
of the string if all characters were valid and converted.

As always, make sure to add tests to `test.c` to test your `strtoul` implementation!

### Checks

The automated checks here, as always, make sure that we can run your C
code and test and grade it properly, including swapping your tests for
ours.

CI will automatically check that:

- `main.c` is unchanged

- `make` completes successfully

- `make test.bin` completes successfully using your `test.c`

- `make test.bin` completes successfully using the original `test.c` from
  the starter code (we will swap this in before running it)

Again, if CI fails on your final submission, we will automatically
deduct 1 point from your basic grade.
