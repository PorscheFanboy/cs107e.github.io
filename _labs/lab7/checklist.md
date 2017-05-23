---
layout: page
title: 'Lab 7: Interrupts Checklist'
permalink: /labs/lab7/checklist/
---

# PS2 Keyboard Lab Checklist

1. What is the function that the IRQ handler invokes? What file
   can this C function be found in?

2. Name two disadvantages, and one advantage, that the spin-loop implementation
   of detecting button presses has or would have over an interrupt based
   implementation.

3. What happens if the interrupt event is not cleared before returning from the
   handler?

4. Why might you want to enqueue/dequeue and then return instead of just doing
   arbitrary logic (like drawing on the screen) in the interrupt handler?

5. Show the TA that pressing and releasing buttons causes your counters to
   increase and suggest a reason why it might not match up with how many times
   you press or release the buttons.

6. How many ticks did your fastest optimized `strcpy` take? Show the TA!
