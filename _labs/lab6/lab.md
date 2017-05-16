---
layout: page
title: 'Lab 6: Drawing into the Framebuffer'
permalink: /labs/lab6/
released: true
---

*Lab written by Philip Levis and Pat Hanrahan*

### Goals

The goal of the lab is understand everything you need for assignment 6.
In that assignment, you will add double-buffering
to the framebuffer initialization code, build a basic graphics
library, and create a text console.

During this lab you will:

1. Connect your Raspberry Pi to a monitor and generate video
2. Read and understand the mailbox and framebuffer code
3. Learn a bit more about pointers to multi-dimensional arrays
4. Read and understand fonts and the representation of characters

To complete the lab, you must complete the [checklist](checklist) and
show the results to the TA.

### Lab exercises

To start this lab, pull from `cs107e.github.io` and go into
the directory `_labs/lab6`. 

#### 1. Set up the Raspberry Pi to output video to a monitor (30 min)

You need an HDMI cable and an HDMI to DVI adapter, which we will
provide in lab. Attach the HDMI to DVI adapter to one end of HDMI
cable. Then attach the DVI connector to the monitor. The monitors we
are using are older and do not have HDMI connectors. Next, attach
the HDMI cable to the HDMI connector on the Raspberry Pi. Power your 
Raspberry Pi, and you should see the following.

![Raspberry Pi video](images/pifb.png)

Now test the GPU on the Raspberry Pi.
Go into the directory `code/grid`.

     $ make

Reset your Pi, and then type

     $ make install

Once it reboots, you should see a grid on the monitor.

Modify the `grid.c` file in the following two ways:

1. Change the video resolution to 1024 by 768, and redraw the grid.

2. Change the grid code to draw a checkerboard pattern (alternating
   black and white squares).

#### 2. Read and understand the fb and mailbox code (40 min)

##### The GPU mailbox

Recall from [lecture](/lectures/framebuffer/framebuffer.pdf) that the
CPU communicates with the GPU by sending messages using a *mailbox*.
The mailbox contains a single message stored as a pointer.
If the mailbox has a message,
it is full. If it has no message, it is empty.
Briefly, this is the communication pattern we'll be using: 

First, the CPU puts a message in the mailbox
for the GPU to read.
The CPU starts this exchange by creating a message and putting a
pointer to that message in the mailbox.
When this happens, the hardware alerts
the GPU, which reads the message and empties the mailbox.
After processing this message, the GPU responds
by putting another message in the mailbox (filling it again) for the CPU to read.
Meanwhile, the CPU waits until the mailbox is full; once it is full the CPU reads the reply message from the GPU.

##### Using the mailbox to configure the framebuffer

To configure the framebuffer, we use the mailbox to send a _framebuffer
configuration message_ to the GPU.

This message contains the physical
and virtual sizes of the framebuffer, as well as the depth of the
pixels. The physical size describes the size of the screen. The
virtual size describes the drawable area, which can be larger than
the physical size. The GPU's reply message includes a pointer to the
start of the framebuffer, the total size in bytes allocated to the
framebuffer, and the length of each scanline or row of the framebuffer
(this is called *pitch*).  Your code should check that the framebuffer
was configured properly by checking that the GPU's reply message has
the same physical and virtual sizes that you sent. Otherwise, you might
have specified a size that the GPU doesn't support, and your graphics
won't work properly.

If the framebuffer is configured correctly, the GPU's reply message
will include a pointer to a *framebuffer*. This is a
contiguous block of memory that you can read and write to read and
write pixels.  The GPU continually refreshes the display based on
the contents of the framebuffer. If you change the framebuffer,
the display will be updated automatically. 

Now let's take a look at some code that does this!
Change into the directory `code/fb`. That directory contains the files:

    $ ls 
    Makefile	fb-main.c	fb.h		mailbox.h	start.s
    cstart.c	fb.c		mailbox.c	memmap

The `fb.c` contains the function `fb_init()` that was shown in class. This
function configures the `fb_config_t` structure (the framebuffer configuration
message), and sends it to the GPU using `mailbox_write` and `mailbox_read`.
These mailbox functions are defined in `mailbox.c`.

Read and discuss the code in `fb.c` , `mailbox.h`, and `mailbox.c`
with your lab neighbors. Discuss each of these questions as a group,
and have one person in your group record your answers to each question
on your checklist, and then turn in the checklist to the CA at the end
of the lab.

   1. Why does the code need each of the checks for whether the mailbox is `EMPTY`
      or `FULL`? What might go wrong if these checks weren't there?

   2. What might happen if `fb_config_t fb` is not tagged as `volatile`?
      Can you imagine an optimization the compiler might make that would
      cause this code to run incorrectly?

   3. What happens if `mailbox_t mailbox` is not tagged as volatile?
      Can you imagine an optimization the compiler might make that would cause
      this code to run incorrectly?

   4. Why can we add the `addr` and `channel` in `mailbox_write`?
      Could we also `|` them together?
      What bit positions are used for the `addr` and what for the `channel`?

   5. Who owns the addresses/memory where `fb`, `mailbox`, and the framebuffer itself
      sit, respectively? The CPU, like any other variable? The GPU? Which of these
      data structures can we choose where to allocate, and which are given to us?
      Draw a memory map diagram of where these entities live and how they interact with each
      other; clearly mark where the CPU's memory and GPU's memory are, as well as
      non-RAM device registers.

   6. Suppose the code did not use `GPU_NOCACHE` -- what might go wrong?
      This [question](http://superuser.com/questions/292302/what-is-a-processor-cache)
      and this [Wikipedia article on caches](https://en.wikipedia.org/wiki/Cache_(computing))
      may help if you're not sure what a 'cache' is.

   7. Go to the directory `code/volatile`. This contains a slightly
      modified version of the code from the `fb` directory. The Makefile is modified to
      create two versions of `mailbox.c` each: a version that marks the mailbox
      as volatile, and another version that does not make them volatile.
      Compare the assembly for the two implementations of mailbox.c. 
      How do they differ? What happens if the first branch in
      the read or write operations isn't taken? Why?

#### 3. Multidimensional pointers (30 min)

Pointers are one of the hardest concepts in C. The goal of this part
of the lab is to review basic pointer declarations, in particular,
pointers to multidimensional arrays. One convenient way to represent
images is with a multidimensional array. The framebuffer memory region
can be managed as a multidimensional array, which can be much easier
than explicitly calculating offsets into a one-dimensional array.

To start, here is a quick quiz:

* What is the difference between the following two lines of code?
  Think about what operations you can do to one versus the other.

      char *a = "Hello, world\n";
      char a[]= "Hello, world\n":

* What is the difference between the following two declarations?

      int (*c)[2];
      int *p[2];

  You may find **[this website](http://cdecl.org/)** helpful in demystifying
  the meaning of various C declarations.

* Inspect the code in `code/pointers/pointers.c`.
  Compile this code using `make`, run it on your Pi, and interpret the results.

  Now uncomment the following code to the above example. What happens?

      int (*e)[2] = { {0, 1}, {2, 3}};
      printf("e = %08x\n", (unsigned)e );
      printf("e[0] = %08x\n", (unsigned)e[0] );
      printf("e[1] = %08x\n", (unsigned)e[1] );

  What happens in the next two lines?

      printf("e[0][0] = %08x\n", (unsigned)e[0][0] );
      printf("e[1][0] = %08x\n", (unsigned)e[1][0] );


#### 4. Fonts (20 min)

A major part of your assignment will be to draw text on the screen.
In order to do this, you need a *font*.

![Font](images/Apple2e.bmp)

This is a very famous font: can you identify what computer it's from?
In the provided font library, the characters are stored in a single
image that's a little different from the image above. The characters
are stored in a single line (not 3). The first character stored on
the left is '!', whose ASCII value is 33 (0x21). The last character
is '~' (tilde), whose ASCII value is 126 (0x7e). There are 94
characters in total. The characters are all the same size, 14 pixels wide
and 16 pixels tall. This is
termed a *fixed-width* font. The character `' '` (space) is ASCII
value 32 (0x20) and is handled specially (since it draws nothing).

Take a look at the files `font.h` and `font.c` in `code/font`.

The file `font.c` contains the above image as a C struct.

    /* GIMP RGBA C-Source image dump */
    static const struct {
        unsigned int          width;
        unsigned int          height;
        unsigned int          bits_per_pixel;
        unsigned char         pixel_data[1330 * 16 / 8]; 
    } font = { 
      1330, 16, 1, 
      "\014\000\314\003\060\003\000\360\000\300\000\300\003\000\014\000"
      "\060\000\000\000\000\000\000\000\000\000\017\300\014\000\374\017"
      ...
      "\000\000\000\000",
    };

This format stores the characters as a bitmap: each pixel is either a
background or a foreground color. It stores them as a bitmap rather
than RGBA because it is much (32 times) smaller. This makes programs
much smaller and faster to upload to your Raspberry Pi. Each line of
the image is 1330 pixels (95 characters * 14 pixels wide), so 1330
bits.

The data of the image is represented in octal notation, where each
digit represents 3 bits. Using this format, each byte is written as
three digits.  The first digit represents the 1st and 2nd bits (most
significant); the second digit represents the next 3 bits; the third
digit represents the last 3 bits.  For example: \014 is a single byte,
whose bits are 00001100 (`00 001 100`). These are the first 8 bits of
the top line of the exclamation point: you can see it is two pixels
wide.

* Talk with your neighbor: why does pixel_data have size `1330 * 16 / 8`?

The key function is `font_get_char()` which copies a single character
from the font image into a buffer. It transforms the bits into
pixels of the specified color. Read this function carefully,
since you will use it in the next assignment.

### Extension: Exploring Type Conversions

In this exploratory extension,
you will be inspecting various integer types within `gdb`.
You may want to review some slides from Monday's lecture.

To start, `cd` into `code/types` and `make` the contents.

Before we get started, here are the `gdb` commands you'll need to know:

* `ptype i8` prints the type of a variable
* `whatis i8 + u8` prints the resulting type of an expression
* `source i8.gdb` runs all the gdb commands in the named file
    * `source -v i8.gdb` ensures all commands, along with their results, are printed

If you see warnings that say `Python Exception <type
'exceptions.ImportError'> No module named gdb.types:` when you use
these commands, you can ignore it. It's looking for some scripting
support (you can script gdb in Python!) and can't find it. Since we're
not using Python we don't care.


Outside of `gdb`, you can type in either of the following commands
to run `gdb` commands from the get-go:

    $ arm-none-eabi-gdb -x start.gdb types.elf
    --OR--
    $ arm-none-eabi-gdb --command=start.gdb types.elf

Inspect each of the `*.gdb` files.  This shouldn't take too long; once
you're done, start up `gdb` with the above command.  Use `source` to
run `gdb` commands for each of the integer types.  Remember that on
the arm 32-bit architecture a `char` is 8-bits, a `short` is 16-bits,
an `int` (same as `long`) is 32-bits, and a `long long` is 64-bits.

The type of the result of a binary operational involving two types is
summarized in the following table.  The headers show the two operand
types, and the cells show the resulting type.

![Binary Conversion](images/binary-conversion.png)

Do these type conversions make sense?

* Why is the result of combining an `int16_t` and an `int8_t` an `int32_t`?

* Why is the result of combining an `int32_t` and an `int64_t` an `int64_t`?

* Why is the result of combining an `uint32_t` and an `int64_t` 
also an `int64_t`?

* Why is the result of a comparison operator like `<` or `==` an `int`?
For example, `whatis u8<u32` is an `int`.

* Any ideas why C defines the result of 
combining an `uint32_t` and an `int32_t` to be a `uint32_t`?

Now try this:

    (gdb) source -v uhoh.gdb

What in the world happened here?!

## Check off with TA

At the end of the lab period, check off with a lab TA so you are
properly credited for your work.
