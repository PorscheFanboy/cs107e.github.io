---
layout: page
title: 'Lab 6: Framebuffer Checklist'
permalink: /labs/lab6/checklist/
---

1. What happens if `mailbox_t mailbox` is not tagged as `volatile`?

2. Why could we `|` the `addr` and `channel` in `mailbox_write`?

3. Show off your memory map diagram! Where does the stack sit, relative to the
   framebuffer? Where do the GPIO registers sit relative to the mailbox?

4. What is the difference between the following two lines of code?

   		char *a = "Hello, world\n";
   		char a[]= "Hello, world\n";

5. What is the difference between the following two declarations?

      int (*c)[2];
      int *p[2];

6. Why does pixel_data have size `1330 * 16 / 8`?
