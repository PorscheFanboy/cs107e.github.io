// File: testing.c
// ---------------
// Unit testing example

#include "assert.h"

// The is_odd function is intended to return a true/false value
// that reports whether its argument is odd. But oops-- the code as 
// written below is buggy!  Something this simple we could validate
// "by inspection" but we are going to use this as an opportunity
// to try out our support for simple unittests. The assert() function
// can be used to run a test case against a function and validate
// whether the result is as expected.  It uses the LEDs on the Pi 
// to give a simple status indication. If the test fails, it will 
// blink the red LED. If all tests passed, when the program finishes
// executing, it turns on the green LED. If you get the red LED of doom, 
// you then know you are failing at least one test.

int is_odd(int n)
{
    return (n & 0x1) != 0;  // OOPS buggy!
}

void main(void) {
	assert(is_odd(0));
	assert(is_odd(107));
	assert(is_odd(5));
	assert(!is_odd(4));
	assert(!is_odd(10));
	// See cstart.c to find out what happens when main() returns.
}
