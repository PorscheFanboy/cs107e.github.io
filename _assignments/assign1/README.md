---
layout: page
title: 'Assignment 1: Implement a Larson Scanner'
permalink: /assignments/assign1/
unreleased: true
---

**Due: Tuesday, April 18, 2017 at 6:00 PM**

[Glen A. Larson](http://en.wikipedia.org/wiki/Glen_A._Larson), 
the man responsible for producing 
the original 
[Battlestar Galactica](http://en.wikipedia.org/wiki/Battlestar_Galactica)
and 
[Knight Rider](http://en.wikipedia.org/wiki/Knight_Rider_%281982_TV_series%29)
television series,
often used simple lighting effects in his shows.
One famous example is a scanner 
that consists of a set of red LEDs that scan back and forth.
The front of the Knight Rider car had a scanner.

![Knight Rider Car](images/knightrider.jpg)

Check out this short 
[video tribute](https://www.youtube.com/watch?v=hDUoyeMLxqM)
to Glen Larson. 
How many times does the scanner pattern appear?

Check out the [Larson Scanner Kit Demo](https://www.youtube.com/watch?v=yYawDGDsmjk) from evilmadscientist.com.

The goals of this assignment are

- To understand ARM assembly language.

- To become fluent with the ARM cross-development tools.

- To know how to use breadboards and use LEDs.

- To program general-purpose input/output (GPIO) pins.

### Basic Part: Simple Scan Pattern

This assignment involves modifying the blink program showed in class.
`blink.s` is an ARM assembly language program that blinks a single LED.
To implement a scanner, you will need to control at least 4 LEDs.

1 Wire up your breadboard with 4 LEDs. 
If you feel ambitious, 
and want to make more interesting patterns,
wire up 8 LEDs.
Make sure all the LEDs on your breadboard work.

2 Connect the LEDs to GPIO 20-23 (or GPIO 20-27, if you use 8
LEDs). The leftmost LED in your scanner should be connected to GPIO
20, the second from the left to GPIO 21, and so on, such that the
rightmost LED in your scanner is connected to GPIO 23 (or 27 if using
8 LEDs).

3 To get the starter code, clone the `assign1` branch from your 107e 
Github assignment repo as you did for `assign0`:

```
git clone -b assign1 https://github.com/cs107e/[YOUR-GITHUB-USERNAME]-assignments assign1
```

4 Currently `larson.s` in the starter code is simply a copy of `blink.s` 
from lab. Add code to scan back and forth from pin 20 LED to 23 (or 27).
You will first need to initialize all the GPIO pins.
Then you will need to sequentially turn LEDs on and off.
Make sure you handle the left and right sides properly
(that is,
the left-most and right-most LED should be on for only one cycle).
You should write the program without any function calls
(because we haven't taught you how to create and call functions 
in assembly language yet). Although you cannot use functions, you can still 
strive for simplicity by using some clever loops.

5 Generate the scanner pattern. 
Enjoy watching it late at night in your room.
Impress your friends.

### Extension (You should do at least 3 of these during the quarter for an A)

**(See the [assignment policy](/assignments/) page for more about our grade expectations)**

The basic part of this assignment should not take too long. 
If you want to explore further, extend the program.
The extension is more challenging, and
may involve using additional ARM assembly instructions.

<!---
1 Program up 4 more patterns. 
If you want ideas,
check out some of these 
[patterns](https://www.youtube.com/watch?v=uUlkumlkryo#t=17).
-->

If you watch the Larson scanner carefully,
several LEDs are turned on at once.
The center one is at full brightness,
and the ones on the edge are dimmer.
How would you dim an LED?
Implement a scanner with LEDs dimmed 
in a way that would please Glen Larson.
It should look very similar to the
[Larson Scanner Kit Demo](https://www.youtube.com/watch?v=yYawDGDsmjk).

### Checks

The automated check here is more likely to fail than in assignment 0,
since there are more things that can go wrong. In this assignment, the
automated checker is seeing
that:

- you have a Makefile (which we've included in the starter code, so
you should be fine if you keep that as is)
- you haven't checked larson.bin in (you should only be checking in
  your source code, and then we'll build larson.bin from it on our
  end)
- `make` runs successfully on the clean testing virtual machine
- `make` generates a `larson.bin` file

When we actually grade your submission, the human grader will assemble
the `larson.bin` file again, then test it on a physical Raspberry Pi
with the LEDs plugged in.

As stated on the [assignment policy](/assignments/) page, if you
submit an assignment solution that does not compile on CI, **we will
deduct 1 point from your basic grade**.

See the [automated checker guide](/guides/ci/) for more information
about the system, and details on how to see what went wrong.
