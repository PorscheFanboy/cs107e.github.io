---
layout: page
title: 'Assignment 4: Backtrace and Heap Allocator'
permalink: /assignments/assign4/
released: true
---

*Written by Julie Zelenski and Omar Rizwan*

**Due: Tuesday, May 9, 2017 at 5:00 PM**

For this week's assignment, you'll again be playing the role of
library implementer to add a debugging aid (`backtrace.c`)
and a simple heap allocator (`malloc.c`) to your growing
collection of foundational routines.

The global and local variables we have been using thus far serve the
needs of many programs, but more sophisticated applications necessitate
dynamic allocation.  Dynamic allocation offers the programmer explicit,
direct control over sizing and lifetime of storage, but this
power calls for the responsibility to carefully allocate and
deallocate that memory. Using dynamic memory correctly and safely is a
challenge for the client; implementing a heap allocator correctly
and efficiently is a challenge for the implementer.

After you finish this assignment, you should

- be able to dissect the runtime stack and display information about an executing program

- further understand C data structures and memory layout

- appreciate the complexity and tradeoffs in implementing a heap allocator

## Overview

This assignment consists of two parts and an extension.

Note that the second part is significantly longer than the
first. Although this assignment has fewer special cases and details
than `printf()`, it is harder to thoroughly test. Think about how to test your
code as you go along.

1. **Implement backtrace.**

   First, you'll implement the `backtrace` module, which lets the
   caller gather and print a backtrace. This backtrace will resemble
   what you see in `gdb` or an error in a language like Java or Python.

   For example, suppose `main()` calls `strndup()`, and then
   `strndup()` calls `malloc()`. If `malloc()` prints a backtrace --
   maybe because you're writing `malloc()` and you want to debug it!
   -- the backtrace would look something like:

         #0 0x85f8 at malloc+132
         #1 0x8868 at strndup+28
         #2 0x8784 at main+24

   The current function is stack frame `#0`. The numbers like `0x85f8`
   are saved link register values; they are where each function will
   resume execution after its callee returns. The `+132` represents
   the distance from the address of the first instruction in `malloc`
   to `0x85f8`; `+132` would be 33 instructions into `malloc`, which
   might correspond to the fifth line of the C source.

   You'll implement three functions in `backtrace.c`:
   `backtrace()`, `print_frames()`, and `print_backtrace()`.

2. **Implement a heap allocator.**

   We've shown heap allocation in class and lab, and you've likely
   used `new` in C++ and Java. Now you'll implement the `malloc`
   module: your very own heap allocator.

   The `malloc.c` module consists of the functions
    `malloc_init()`, `malloc()`, and `free()`. 
    You'll implement these three functions.

Finally, for the extension, you will implement a leak detector which runs after
a program completes. The leak detector should report any allocations
which the program neglected to free (that is, memory leaks).

## Set up your assignment

Clone the `assign4` branch that was pushed to your repository, as you
did in prior assignments.

Assuming you are using your own module versions, you will want to copy
your best `gpio.c`, `timer.c`, and `printf.c` into your new `assign4`
directory. You can also supply your `strtol.c` if you completed the assign3 
extension, or leave it off to use our library version. 

Consult the `Makefile` for more information on reusing code from
previous assignments. Also, notice that we have enabled the `-Werror`
flag in the `Makefile`, so any compiler warnings will halt the
build with an error.  We want you to commit to the habit of
always keeping your code compiling cleanly. 
If you're not sure of the proper way to 
resolve a particular warning, please ask! We're happy to help. 

Read `main.c`, which contains some very simple client code that
uses backtrace and malloc, and `test.c`, which contains more rigorous
tests for your code.

Feel free to add tests of your own to these
files to get additional testing coverage, but also
make sure your final submission works correctly with the 
original code from `main.c` and `test.c`, as we will use
code similar to that when testing your submission.

## Part 1: backtrace

Open the [backtrace.h header file](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/backtrace.h)
in libpi/include for details about this module. You should implement
all this functionality in the file `backtrace.c`.

1. **Implement `backtrace()`**.

   The function `backtrace()` should not print anything itself: it
   should harvest backtrace information from the stack, which may get
   printed later. Read the comment above its function prototype in
   backtrace.h.

   See the `test_backtrace()` function in `test.c` for an example of
   how this function gets invoked.

   You may find the
   [memory diagram](https://cs107e.github.io/labs/lab3/images/winky-stack.pdf)
   from lab 3 helpful when implementing this function.

   <a href="/labs/lab3/images/winky-stack.pdf"><img src="/labs/lab3/images/winky-stack.png"
   width="300" /></a>

   Read the comments in `backtrace.h` above the type definition of `struct frame` to
   understand the intent of the two fields `fn_resume` and `fn_first`. You are
   going to harvest the information for these two fields
   by digging around in the stack memory. Consider filling in the `struct frame`
   for `winky`, who is the caller of `binky`. If the executing 
   function is `binky()` and you have the current value of the `fp` register, 
   where/how can you get the information to set the `fn_resume` field for `winky`? What
   about the `fn_first` field?

   Figure out how to walk up the stack and harvest `struct frame`s for
   the entire stack of function calls. Note that `backtrace()` should
   make `f[0]` contain its caller's information, rather than its own.

   Handy tip: gcc allows you to embed assembly into
   your C code. You can use this to retrieve the current value of a register
   into a C variable, such as this snippet that accesses the value of `r0`:

   ```
   unsigned reg_value;
   __asm__("mov %0, r0" : "=r" (reg_value));
   ```

   After this code runs, the value of register `r0` will be in the
   `reg_value` variable. Substitute for `r0` in the snippet above to 
   retrieve the value
   of any numbered register or register alias, such as `ip`.  If you're 
   curious to learn more about gcc support for inline assembly,
   check out the [gcc documentation.](https://gcc.gnu.org/onlinedocs/gcc/Using-Assembly-Language-with-C.html)

2. **Implement `print_frames()`.**

   Next, implement the `print_frames()` routine, which takes
   an array of `struct frame`s and prints a backtrace like:

   ```
   #0 0x85f8 at malloc+132
   #1 0x8868 at strndup+28
   #2 0x8784 at main+24
   ```

   The hex address shown for each frame is the value of its `fn_resume` field.
   You will use the `fn_first` field of the frame to get the name and offset
   for the function. 

   The approach for obtaining the function name is to leverage an ARM
   gcc option intended to support developers (such as yourself)
   writing debugging tools. If you compile your code `-mpoke-function-name`,
   gcc will embed each function's name into the text section, at a
   location preceding the function's first instruction!
   Let's quote the [gcc documentation](https://gcc.gnu.org/onlinedocs/gcc-4.8.3/gcc/ARM-Options.html#index-mpoke-function-name-1139))

   > `-mpoke-function-name`
   >
   > Write the name of each function into the text section, directly
   > preceding the function prologue. The generated code is similar to
   > this:
   >
   > ```
   > t0
   >     .ascii "arm_poke_function_name", 0
   >     .align
   > t1
   >     .word 0xff000000 + (t1 - t0)
   > arm_poke_function_name
   >     mov     ip, sp
   >     stmfd   sp!, {fp, ip, lr, pc}
   >     sub     fp, ip, #4
   > ```
   >
   > When performing a stack backtrace, code can inspect the value of
   > `pc` stored at `fp + 0`. If the trace function then looks at location
   > `pc - 12` and the top 8 bits are set, then we know that there is a
   > function name embedded immediately preceding this location and has
   > length `((pc[-3]) & 0xff000000)`.

   How cool! Look at the assign4 `Makefile` and see that we've added
   `-mpoke-function-name` to the `CFLAGS` for you, with one
   exception, the `nameless` module.

   Looking backwards from a frame's `f[i].fn_first`, you can dig out 
   the name of the associated function, then pass that name to
   `printf()` to print. If you don't have a name for some function in
   the backtrace, because that code was compiled without
   `-mpoke-function-name`, then print `???` as the name.

   Here is a [memory diagram](images/diagram_with_poke.html) for the same 
   lab3 winky program as previous, but changed to compile with the
    `-mpoke-function-name` flag.  Take a look to see where the function 
    names have been inserted into the text section.

3. **Implement `print_backtrace()`.**

   The `print_backtrace()` function is a straightforward wrapper
   around the two functions you just implemented; it should get frames
   up to some reasonable limit, then print them out, excluding the
   frame for `print_backtrace()` itself.

   It's part of the backtrace interface so that you can conveniently
   print a backtrace with just one function call.

## Part 2: `malloc`

For this part of the assignment, you'll be implementing the functions
`malloc_init()`, `malloc()`, and `free()` in `malloc.c`.

Start by reviewing the
[header file: malloc.h](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/malloc.h).
Next, study the given code in the file `malloc.c`.

The starter code contains a 'bump' allocator, like the one we saw
in class. This starter code does provide a correct `malloc()`, but
it cannot free allocations after they've been made!

**Make sure you understand what every line in the starter malloc.c is
doing.** Your allocator will be significantly more complicated, so you
must understand the basics.

- Where is the heap located in memory? How big is it?
- If you request a 5-byte allocation, how much is actually allocated by the bump allocator?
- Why can't the bump allocator free a previous allocation?

### Tests

The code in `test.c` contains some basic quantitative tests to measure
the utilization and throughput (defined below) of the heap allocator. If you run these
tests on the bump allocator, you will observe that the bump 
allocator is very fast, but its naive design has no
ability to recycle memory and thus will quickly run out of heap space. 
We expect that your rewritten allocator will take a more balanced
approach that is able to achieve better utilization, but at the cost
of somewhat reduced throughput and added code complexity.

#### Heap operations

First consider the `heap_operations()` tests. 
When you run `make test` and execute these tests, the bump allocator 
produces these results:

```
------------- Test heap operations --------------
Total heap size 500000 was able to service 10 of 10 requests

------------- Test heap operations --------------
Total heap size 20000 was able to service 281 of 1000 requests
```

This test first reinitializes your heap allocator module 
(by calling `malloc_init()` for a certain total heap size), 
then makes `repeat` allocations of space for strings 
(around 40 bytes per allocation). Each time it does
a `malloc()`, it picks a random index in the 10-element array `arr` to
store the returned pointer. If there is already an allocation at
`arr[index]`, then that allocation is freed. It therefore randomly
interleaves allocations and deallocations to test your code. If
`heap_operations()` ever gets NULL back from `malloc()`,
indicating that the heap is full, then it stops.

The first `heap_operations` call made 10 small allocation
requests, which easily fit in the large 500,000-byte heap, so
all requests succeeded. Great!

But the second `heap_operations` call tried to make 1,000 requests on
a 20,000-byte heap, and it ran out of space after 281 of those
requests, even though it maintained at most 10 concurent 
live allocations at a time. The bump allocator can't actually 
free past allocations, so `heap_operations` calling `free()`
 didn't do anything!

When you write your allocator, you will rewrite `malloc()` and
implement `free()` accordingly, so that `heap_operations` can free
past allocations and recycle heap space. After that, all 1,000
requests should easily succeed in the second test.

#### Heap performance

The starter tests also print this 'heap performance' result:

```
------------- Test heap performance --------------
Starting from empty heap of total size 200000
200...400...600...800...1000...1200...1400...
1432 allocations completed
Throughput: 193069 requests/sec
Utilization: 31 percent (estimated)
```

The `heap_performance` test loops and randomly allocates and
deallocates on each iteration until the heap is exhausted. It uses a
queue data structure to track still-outstanding allocations.

It tracks these metrics:

- **Throughput** ('requests per second'): how many `malloc()` calls
  can be processed per second. Higher numbers are better throughput.

- **Utilization**: what percentage of heap bytes is actually storing
  live payload data instead of metadata or free space. Higher percent 
  utilization is better utilization.

In this assignment, we'll mainly focus on improving utilization, although we
will make a performance improvement at the end.

The starter code's utilization is pretty poor: there's no metadata
taking up heap space, but there is a lot of free space which the
bump allocator is unable to recycle.

Your allocator, which _should_ recycle freed memory, should get at
least 75 percent utilization.

The starter code's throughput, on the other hand, is excellent,
because `malloc()` just bumps a pointer.

Your allocator probably won't get the throughput of the bump
allocator, but we will optimize it to get close: you should be
able to achieve near 50,000 requests per second on your final allocator.

### Other notes and requirements

All pointers returned by `malloc()` should be aligned to 8 bytes,
which is the size of the largest primitive data type on our system
(`double`).

If your header is 8 bytes, and you receive an allocation request
`malloc(5)`, how much memory would you actually have to set aside?

Throughout this assignment, consult the `man` page for `malloc()` to
find out how to deal (or not deal) with edge cases -- what if
`malloc()` cannot fulfill a request, because it doesn't have a large
enough contiguous free block?  What if a caller runs `free()` on some
random pointer that it didn't actually get from `malloc()`?

Make sure you understand pointer arithmetic and the difference between
arithmetic on, say, an `int *`, a `char *`, a `struct some_struct *`,
and an `unsigned int`.

### Recommended implementation

We recommend that you use an _implicit free list_ design for your
allocator, and we'll walk through how to build one here. But you can
use any design you want, as long as you implement the `malloc` module
interface and satisfy all the above requirements (with the tests
unmodified).

These
[slides from CMU](https://www.cs.cmu.edu/~213/lectures/19-malloc-basic.pdf)
explain the implicit free list approach at a high level.

Once you understand the implicit free list concept, design the
metadata structure for your blocks. You will probably want a header
directly before each allocation (each pointer you have `malloc()`
return), which stores metadata that your `malloc()` and `free()` need
to manage the heap later. That metadata likely includes whether the
block is free or allocated, as well as the size of the block. Declare
a `struct` to represent this header.

We recommend that you implement basic first fit, then coalesce
adjacent free blocks, then next fit. You should maintain a correctly
working allocator through each of these three steps, and reap
incremental improvement with each upgrade.

#### First fit

First, we will make `malloc()` and `free()` use a 'first fit' policy
over the whole heap, with no coalescing, which will get poor
throughput but will improve utilization.

1. **Implement `malloc_init()`.**

   At first, you should treat the heap as one giant block. For
   example, if you have an 8-byte header struct, and
   `malloc_init(1024)` is called (so the heap is 1 KB), you'll
   initially have a single block with payload size 1016 and total size
   1024. The header, which contains the block length, takes up the
   first 8 bytes, and the payload of the block takes up the rest.

   In `malloc.c`, declare a static pointer `first` to your header
   struct type. Note that `first` will always point to the first block in
   the heap; that pointer will not change after
   `malloc_init()` has been called.

   In `malloc_init()`, point `first` to the start of the heap (end of
   BSS). Then fill in the fields of `*first` so that the first block
   initially covers the whole heap.

2. **Implement `malloc()`, including block splitting.**

   The main job of `malloc()` is to find an appropriately-sized free
   block to service the client's request.

   Start by rounding the requested size up to a multiple of 8, so as
   to section the heap into blocks that are properly aligned by default.

   As designed in step 1, the heap can be traversed by its
   'implicit list': given a pointer to a block header, you have just
   enough information to compute the location to the next block header, since
   you know how big the block is and you know the next block is
   immediately adjacent.

   In `malloc()`, walk over the entire heap, starting from the `first`
   block, until you find a large-enough free block to service the
   request. If you reach the end of the heap without finding one,
    `malloc` returns 0 (NULL) to indicate that request failed.

   If the chosen block is bigger than needed for the request, and
   there is enough left over for a new block, you should _split_
   it. Cut down the block into a right-sized piece to service this
   request and initialize a new block header for the remainder.

   Mark your found block's header as allocated. Finally, return a
   pointer to the payload part of your block. Don't accidentally 
   return a pointer to the header!

   Test your code and make sure that it can properly satisfy
   allocations. At this point, all the heap tests should still
   work. You still won't pass the second `heap_operations` test, since
   we're not recycling freed memory yet. Your utilization will be
   slightly worse than the starter code (because of the headers taking
   up space) and your throughput will be much worse (because of the
   repeated heap-walking).

   You may find it useful to use `printf` and gdb to examine the state
   of the heap over time if you have bugs.

3. **Implement `free()`.**

   Compared to `malloc()`, implementing `free()` is relatively simple
   for now: it should take a pointer to a block payload, step
   backward to the block header in memory, and mark that block as
   free.

   Now run the tests. The `heap_operations` test should pass, and you
   should have much higher utilization in the performance test!

   Can you see a looming problem? What happens if the client repeatedly
   allocates 8-byte chunks until the heap is full, frees all of them, 
   then tries to allocate 16 bytes? We'll address this problem next.

#### Coalescing

Modify `free()` so that it examines the block after the newly freed
block. If that forward neighbor is also free, then _coalesce_ the two
blocks into one big free block. Then look at the forward neighbor of
that bigger block and see if it's free in turn. Continue
forward-coalescing into your block until you have a forward neighbor
that is not free.

Run the tests: this change should make utilization go up by a 
small fraction, because now we can put previously small and 
fragmented blocks to
work for bigger allocations.

#### Next fit

The biggest throughput sink of a heap allocator is typically
in `malloc()` when searching to find an appropriately-sized free block.
The first fit approach scans the heap from start to end, 
examining every block in the heap. Both free and in-use blocks are examined. 
As the heap gets more full, this
technique degrades into quadratic-time: if I do `n`
allocations, the `n`-th allocation will need to walk past the `n -
1` previous allocations to find a free block. Ouch!

There is a simple optimization that can help a lot here. Instead
of always searching from the start of the heap, make each subsequent
search pick up where the previous search left off. In this way,
you avoid repeatedly re-scanning past long sequences of in-use blocks.
The strategy is called "next fit".

To implement next fit, you'll need to add a global variable `rover`
that is a pointer to the most recently allocated block.

Modify `malloc()` to start the search at `rover` instead of `first`.
The `malloc()` search starts at 'rover' (where the previous search
left off) and moves forward from there.

If the search hits the end of the heap without finding an appropriate
free block, the first fit strategy would report this as failed allocation
request and return NULL. However, if next fit reaches the end 
of the heap, it is an indication that it is time to wrap around and
search from the beginning of heap up to `rover`.  Under what conditions 
then does the next fit search return NULL? 

Be careful to consider edge cases in testing next fit. 
What happens if the `rover` block gets coalesced into a bigger block on a `free()`?

Do you expect changing to next fit to improve throughput, utilization, or both
under our tests? Run the performance tests and see.

You should now have a correctly working allocator with respectable
performance on both throughput and utilization. This is quite a milestone!
Congratulations -- now go celebrate with some chocolate, a Dish hike, or a nice nap in the sun!


## Extension: Leak detector

What happens if you `malloc()` something for temporary use, then
forget to `free()` it after you're done? You have a _memory leak_,
where that allocation sits there forever, taking up space you might
want for other data.

For this extension, you'll modify your allocator to report any such
leaks to you when your program finishes. You'll use your backtrace
module to put useful information about who allocated what in that
report.

Modify `malloc()` and your block header structure so that if the
program is compiled with `-DLEAK_DETECTOR` (which defines the
`LEAK_DETECTOR` macro), each block records a 3-frame snapshot of the
backtrace at the time of the
allocation. ([Read more](https://gcc.gnu.org/onlinedocs/cpp/Ifdef.html)
about the `#ifdef` preprocessor directive which you can use here, and
see how we conditionally define `leak_report()` in `malloc.c`.) This
mini-backtrace will be used to identify each leak by the context in
which `malloc()` was called.

Edit the `Makefile` to pass `-DLEAK_DETECTOR` as a C compiler flag to
turn leak detection on. Your allocator should continue to work as
before (with backtrace-less headers and performance) if
`LEAK_DETECTOR` is not defined. Note that your utilization should look
noticeably worse if leak detection is on, since you're storing a
mini-backtrace for _every_ allocation! You may need to `make clean`
and `make` again to build all modules with the changed compiler
options.

Implement the function `leak_report()` in `malloc.c`, which should
walk the heap and print the payload size and mini-backtrace for each block
that hasn't been freed, like this:

    [Leak report]

    8 bytes are lost, allocated by
    #0 0x8d80 at malloc+140
    #1 0x8464 at heap_extended+40
    #2 0x84f8 at main+68

    8 bytes are lost, allocated by
    #0 0x8d80 at malloc+140
    #1 0x865c at enqueue+28
    #2 0x8470 at heap_extended+52

    9 bytes are lost, allocated by
    #0 0x8d80 at malloc+140
    #1 0x8464 at heap_extended+40
    #2 0x84f8 at main+68

    8 bytes are lost, allocated by
    #0 0x8d80 at malloc+140
    #1 0x865c at enqueue+28
    #2 0x8470 at heap_extended+52

    Lost 33 total bytes in 4 blocks.

Where should you call `leak_report()` so that you can run any
application with leak detection, without modifying the application's
`main` or other application-specific files? Hint: think about how the
green LED gets turned on when your tests complete.
