---
layout: page
title: 'Lab 6: Framebuffer Checklist'
permalink: /labs/lab6/checklist/
---

#### Mailbox

1. Why can we add the `addr` and `channel` in `mailbox_write`?
      Could we also `|` them together?
      What bit positions are used for the `addr` and what for the `channel`?

2. Who owns the addresses/memory where `fb`, `mailbox`, and the framebuffer itself sit,
      respectively? The CPU like any of our normal data structures? The GPU?
      Which of these can we move around, and which of these are given to us?
      Create a diagram of where these entities live and how they interact with each other;
      clearly mark where the CPU, GPU, and memory are.

3. Suppose the code did not use GPU_NOCACHE -- what might go wrong?

#### Pointers

1. What is the difference between the following two lines of code?

   		char *a = "Hello, world\n";

   		char a[]= "Hello, world\n";

2. What is going on in these lines of code?

        int (*e)[2] = { {0, 1}, {2, 3}};
        printf("e = %08x\n", (unsigned)e );
        printf("e[0] = %08x\n", (unsigned)e[0] );
        printf("e[1] = %08x\n", (unsigned)e[1] );

3. What is the difference between the following two declarations?

        int *p[2];

        int (*c)[2];

#### Fonts

1. Why does pixel_data have size `1330 * 16 / 8`?
