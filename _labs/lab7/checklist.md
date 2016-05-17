---
layout: page
title: 'Lab 7: Interrupts Checklist'
permalink: /labs/lab7/checklist/
---

# PS2 Keyboard Lab Checklist

## Part 1 ##

1.  What assembly function (in `start.s`) does your Raspberry Pi boot into and
    what does it do?

2.  What is the name of the C function that the IRQ handler invokes? What file
    can this C function be found in?

## Part 2 ##

1. Name two disadvantages, and one advantage, that the spin-loop implementation
   of detecting button presses has or would have over an interrupt based
   implementation.

## Part 3 ##

1. What happens if the interrupt event is not cleared before returning from the
   handler?

2. Show the TA that your counter increments when you press the button.

## Part 4 ##

1. Why might you want to push/pop instead of using arbitrary logic in the interrupt
   handler?

## Part 5 ##

1. Show the TA that pressing and releasing buttons causes your counters to
   increase and suggest a reason why it might not match up with how many times
   you press or release the buttons.

## Optimization ##

1. How many ticks did your fastest optimized `strcpy` take? Show the TA!
