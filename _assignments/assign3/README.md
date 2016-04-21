---
layout: page
title: 'Assignment 3: Implementing a string formatting library'
permalink: /assignments/assign3/
---

**Due: Tuesday, April 26, 2016 at 6:00PM**

Often when programming embedded computers,
space is at a premium.
Many of the C standard libraries are surprisingly large,
and it is useful to have simpler versions of standard functions available.

`printf` is particularly useful,
since printing is the most basic form of debugging.

The goals of this assignment are

- Understand C strings and characters.

- Understand how to convert basic C types (`int`, `int*`, ...) to a string.

- Use your gpio and timer code from the previous assignment.

- Use the uart library shown in class to communicate with your laptop.

This can be a difficult assignment, so start early and practice good development 
and debugging techniques like you learned in lab.

Students who have struggled in the past wrote too much code before
testing it. Try to implement this assignment in little increments,
making the smallest change each time so if it doesn't work, you know
exactly where to find the mistake.

Remember to decompose your code into simple, clearly-defined functions. This will 
make your code easier for you to debug and easier for your graders to understand. 
There are no length requirements, but as a guideline, the cleanest versions from 
previous years have included 10-15 functions and 200-300 lines of code.

### Set up your assignment

Clone your `assign3` repository branch as you have done in previous assignments.
You will find `printf.c`, where you will be writing most of your code. There is 
also `strtol.c`, which is for the extension, and `main.c`, `test.c`, and
`assert.h`, which may all be used to test out functions in your `printf` and
`strtol` modules.

Assuming you are using your own module versions, you will need to copy in your 
`gpio.c` and `timer.c` files from `assign2` into the `assign3` directory.

In this assignment, you will be filling in the functions in `printf.c`. You 
should also be adding tests to `test.c` to test your
final `printf` implementation.

Please avoid modifying `main.c` in this and future assignments so
that we can be sure that your assignment solution obeys the same
interface we expect.   

### Reusing your modules and using reference modules

Take a look at the Makefile in this assignment. You will see that there are
variables LIBPI_STUDENT_MODULES and LIBPI_REFERENCE_MODULES. Throughout the 
assignments in this
course, you will build up your own Raspberry Pi library called libpi. Each
assignment, you will have more files to add to the library (modifying the list in 
LIBPI_STUDENT_MODULES). Notice that in this 
assignment, we include the `gpio` and `timer` modules from `assign2` as well as 
new `printf` and `strtol` modules which you will create in this assignment. 

The LIBPI_REFERENCE_MODULES is a list of modules that you are
grabbing from our reference solutions. For example, the `uart`
module is the
[UART code](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/src/uart.c)
that was shown in lecture, which you will need to implement
`printf`.

The source code for certain libpi modules, those which you don't
implement in assignments, is
[available in the cs107e.github.io repository](https://github.com/cs107e/cs107e.github.io/tree/master/libpi/src)
if you're curious.

Going forward, you can also add to this list if an assignment
uses a module from a previous assignment that you did not
successfully implement. By adding that module to the
LIBPI_REFERENCE_MODULES, you will be using our reference version
instead of your own.

For example, if your `gpio` code from assignment 2 is not working, you
could move `gpio.o` from the LIBPI_STUDENT_MODULES list to
LIBPI_REFERENCE_MODULES and use our reference version of the gpio
functions. However, remember that to get the bonus 5 points at the end
of the class, you need to use all of your own modules in your final
assignment.

### Requirements

For the basic part of this assignment, you must implement functions
in just one file, `printf.c`.

- `printf.c`
  ([header file: printf.h](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/printf.h))
    - Not in the header file, but expected to be part of your implementation:
        - `inttobin`
        - `inttodec`
        - `inttohex`
    - `snprintf`
    - `vsnprintf`
    - `printf`

For the extension, you should implement `strtoul` in `strtol.c`.

### Basic part: basic formatting functions

1.   **Implement integer formatting functions.**

     ```
     int inttobin( char *buf, int n, unsigned val, int width); 
     int inttodec( char *buf, int n, int val, int width); 
     int inttohex( char *buf, int n, unsigned val, int width); 
     ```

     In these functions, `buf` is a character array to store 
     the string representing the number. 

     The size of the buffer is `n`.
     Do not write past the end of the buffer!

     `val` parameter is the integer value to be converted to a string. When converting to 
     a decimal string, treat the integer `val` as a signed two's complement value 
     (this is how integers are stored in C). If the value is negative, you will 
     need to include a minus sign in the decimal string. When
     converting to a binary or hexadecimal string, treat the value as
     unsigned.

     In your conversions, you will likely need to do some
     division. The starter Makefile links the `libgcc` library into your
     compiled program, which includes the division routine that you
     were missing in lab. (Check out the `main.bin` and `test.bin` targets
     in the Makefile.)

     The `width` is the minimum number of characters the caller wants written into `buf`. 
     If `width` is more characters than needed to fit the formatted value, pad the 
     string with zeros on the left so that it has length `width`. If `width` is 
     fewer characters than needed to hold the formatted value, ignore the `width` 
     parameter. The minus sign, for a negative signed decimal, should
     precede the zero padding.

     `n` is a hard upper limit on how much room you have; if `n` is
     too small to fit your output, even if `width` says you should go
     past it, you must cut your output off. (Otherwise, you would be
     trashing some other memory past the end of the buffer.)

     You should null-terminate what you write into `buf`; all valid C
     strings are null-terminated, and there is no other way for the
     caller to know where your output stops. The null terminator, like
     all your other output, is subject to the `n` upper bound.

     These functions should return the number of characters written to
     `buf` if there is room to fit them all. If not, it should return
     the number of characters that would have been written if there
     were room. This count excludes the null terminator.

     You may assume, when writing your functions, that no caller will
     ask for a value and width that require you to print more than
     1000 characters.

     Remember that it is easier to debug small steps than large changes, 
     so make sure these functions are working before you move on.

     (You could test these functions locally on your laptop by
     compiling using gcc and printing the values written by your
     functions using `printf` from the standard C library, by using
     the gdb simulator from lab to examine the strings, or by adding
     assertion tests.)
     
     Take a look at the tests in `test.c`. These tests are for `snprintf`, but you
     could write similar tests for these helper functions.
     For example, one test might look like 

     ```
     int size = inttodec(buf, BUF_SIZE, 5, 4);
     assert(strcmp(buf, "0005") == 0);
     assert(size == 4);
     ```

     The assertion will fail until you correctly implement `inttodec`.      
     Write other similar tests for negative numbers and other unusual inputs.
     Test thoroughly by thinking about what are edge cases that might fail given your implementation.
     With *test-driven development*, you write many tests like this before implementing
     the functions. Each fix you make to the code 
     should just try to pass one more test. If your tests are well-designed, once you 
     are passing all tests, you know your code is working correctly!

     Once you have this part working, it would be a good time to commit your code 
     (using `git add` and `git commit` commands). 
     Then if something breaks later on, you can always return to this known-good state.

2.  **Implement basic `snprintf`.**

    ```
    int snprintf(char *s, int n, const char *format, ... );
    ```

    If you are unfamiliar with this function,
    take a look at its man pages: `man snprintf`.

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
    This lines up with how you should have written your `inttodec`, 
    `inttohex`, and `inttobin` functions above -- so use your helper functions!

    The formatting codes for integers should optionally contain a
    width: as well as supporting `%[c, s, d, x, or b]`, support formatting codes of the form
    `%0[WIDTH][c, s, d, x, or b]`.
    For example, `"%014x"` would be a string of at least 14 characters (padded 
    with zeros on the left as necessary) which is the hexadecimal representation
    of some value.

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

    ```
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

4.  **Implement `printf`.**

    Use your `vsnprintf` to implement `printf`,
    which should output characters to the mini uart using `uart_putc` from the
    `uart` module. You may again assume a maximum string length of 1000 characters.

    ```
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

    ```
    printf("%d = -5\n", -5);
    printf("%b = 101\n", 5);
    printf("%04x = 00ab\n", 0xab);
    ```

    Also make sure you add tests for unusual cases. What happens if you try 
    `printf("")`? What about `printf("\n")`? If you are ever unsure of what 
    should be printed, compile the test with the standard library `printf` 
    implementation and compare the output to your `printf` output.

<!---
5.  Implement `assert`, which should test if the given condition is true. 
    If not, it should print a useful error message (using your `printf`) 
    that includes the file and line number where the assert failed, and the 
    condition that failed. Also turn on the ACT LED on your 
    raspberry pi so that you can detect the failure even if your printf is 
    not working. After printing an error message and turning on 
    the LED, it should go into an infinite loop to effectively terminate 
    the running program.

    To get the file and line number, you will need to 
    use \_\_FILE\_\_ and \_\_LINE\_\_. These will print the file and line number of 
    the currently executing code. Unfortunately, if you put these macros 
    inside an `assert` function, they will print a line number inside the 
    `assert` function rather than the line where the assert was called. To 
    remedy this, you will need to implement `assert` as a macro so that the 
    preprocessor will replace the call to `assert` with its implementation.

    To print out the condition, look into
    [stringification](https://gcc.gnu.org/onlinedocs/cpp/Stringification.html).
--->

#### Using variable numbers of arguments

`printf` is a function that takes a variable number of arguments.
C has standardized the way to access variadic functions 
using the `stdarg.h` interface. 
Here is an example.

    
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
        printf("%d\n", sum(3,  1,2,3) );
        return 0;
    }
    

Note how to declare a function with a variable number
of arguments using `...`.
The function `sum` has one required argument `n`,
and then a variable number of additional arguments.
This function should be called with `n` additional arguments.
For example, we call it from main as `sum(3, 1, 2, 3)`.
In general, functions require one argument.
It should be possible to determine the number of arguments
from the first argument.

The function `sum` shows how to use the `stdarg.h`.
First, we declare a variable `ap` as type `va_list`.
This variable is initialized using `va_start`.
Then we loop over the `n` arguments.
We fetch the next argument using `va_arg(ap, type)`.
The types can be different for each argument.
You need to know the type for this to compile correctly.
In this case, we assume all the arguments are of type `int`.
When we are done, we call `va_end(ap)` to clean up after ourselves.

For more details about `stdarg`, 
read the [Wikipedia Page stdarg.h](http://en.wikipedia.org/wiki/Stdarg.h).

### Extension

Implement a version of `strtoul`. 

```
unsigned long strtoul(const char *nptr, char **endptr, register int base);
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
numerical value. You should store unconverted sections of the string in `endptr` 
(if `endptr` is not 0).

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
