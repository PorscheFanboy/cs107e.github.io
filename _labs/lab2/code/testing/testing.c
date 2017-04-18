// File: testing.c
// ---------------
// Unit testing example

#include "assert.h"

// The is_prime function is buggy due to a missing initialization and furthermore
// it uses integer division/mod (not available in the ARM instruction set!). 
//
// Surprisingly, the code as-is builds without error, executes without
// incident, and always returns false, failing some of the test cases
// in main(). Let's look at the ARM to figure out why.
//
// The local variable has_factor is intended to track whether a divisor has
// been found. The value of a local is unreliable until set. The oh-so-clever
// compiler realizes that loop might set the value to 1 but otherwise, its
// value is left indeterminate. Use of an uninitialized value is an undefined
// behavior for C, so the compiler has latitude to handle in any way it chooses.
//
// In this case, the compiler chooses to pretend that the unset value would
// be a 1. This conveniently means that the value will be 1 before,
// during, and after the loop, no matter what happens in the loop at all!
//
// The function always returns 0; the compiler can eliminate the rest of the
// function body as it has no effect whatsoever. Wow -- what an optimization!
//
// Correct the code by making an initial assignment of has_factor to
// 0. Now try to rebuild.
//
// Explain what must be true for a division expression in C to compile
// and execute correctly, despite the lack of a ARM divide
// instruction. What is the result of attempting to compile a true
// division that cannot be so transformed, if we don't have libgcc?

 __attribute__((optimize("-O2")))    // GCC directive to ask for level 2 optimization
int is_prime(int n)
{
    int has_factor;     // BUG: missing initialization
    for (int i = n/2; i > 1; i--) {
        if ((n % i) == 0) has_factor = 1;
    }
    return !has_factor;
}


void main() {
    assert(is_prime(3));
    assert(!is_prime(4));
    assert(is_prime(97));

    // Turn the green ACT LED on when we get to the end. We want some
    // signal that the program _finished_ without failing an
    // assertion; otherwise, we can't tell the difference between the
    // program freezing and the program finishing successfully!
    success();
}
