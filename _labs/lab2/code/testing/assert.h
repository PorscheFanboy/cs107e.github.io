#ifndef ASSERT_H
#define ASSERT_H

// abort runs an infinite loop that flashes the red power LED on the
// Pi board.
extern void abort();

// success turns the green ACT LED on permanently. Meant to be run
// when your program completes, so you can tell 'completion' apart
// from your program just freezing somewhere.
extern void success();

// You call assert on an expression that you expect to be true. If x
// actually evaluates to false, then assert calls abort, which stops
// your program and flashes the red light of doom.
#define assert(x) if(!(x)) abort()

#endif
