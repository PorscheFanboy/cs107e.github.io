---
layout: page
title: 'Lab 1: Setup the Raspberry Pi'
permalink: /labs/lab1/
---

*Lab written by Pat Hanrahan*

### Goals

During this lab you will:

1.  Learn how to cross-develop on your computer for the Raspberry Pi's ARM processor.
2.  Learn how to use a breadboard with LEDs and buttons.
3.  Learn how to download and run bare metal programs on the Raspberry Pi.

##### How does lab work?

Before beginning,
you should find a partner and introduce yourself to one another.
Together you can tackle the exercises outlined below.
Along the way,
you are encouraged to chat with your neighbors 
to share insights and offer each other useful tips.
The instructors and TAs will circulate the room
to offer advice and answers 
so as to keep everyone progressing smoothly.

Lab is a time to experiment and explore. It follows up on the topics from
recent readings/lectures with guided exercises ensuring you comprehend the
material, putting your knowledge into practice, trying out the tools in a
supported environment, and preparing you to succeed at the assignment to come.

Bare metal programming requires precision. It is easy to get stuck by the most
trivial error, which is often almost impossible to see yourself. Our goal in
the lab is to get you past these bumps in the road as fast as possible. We
don't want you to feel frustrated because something doesn't work.

To record lab participation,
we use an checklist form that you fill out as you work.
These questions are deliberately simple.
We use them merely to record your participation 
and get a read on how far you got.
To get the most out of lab,
you should not do the minimal required of you 
in the shortest possible time.
Even if you think you understand the material,
you should use the lab time to dive into the nooks and crannies.
You should also get to know the instructors.
They are masters of the craft,
and you will learn a lot by talking to them and asking them questions.
Any topic is fair game.

The combination of hands-on experimentation,
give and take with your peers,
and the expert guidance of the TA 
is what makes lab time truly special.
Your sincere participation can really accelerate your learning!

### Prelab preparation

To prepare for this lab, you should do the following.

- If you are using a Windows laptop, download and install a virtual machine
  running Linux. We have written [instructions] on how to install this
  software. The virtual machine will have the arm cross-development tools (all
  starting with the prefix `arm-none-eabi-`) installed. (You should
  have done this for assignment 0 anyway.)

- If you are using a Mac laptop, download and [install the arm
  cross-development tools, console drivers, and uploader
  script](/guides/mac_toolchain/) from the course github repository.
  You do not have to install a virtual machine running Linux on a Mac,
  since OS X is already based on UNIX.

- Make sure you have installed and learned how to use Git. (You should have
  completed this in [assignment 0].)

You should come to lab with working versions of the cross-development
tools (all beginning with `arm-none-eabi-`) and a running version of
git.

Before coming to lab, you should be able to open a Terminal, type
the following two lines, and check for responses like this example:

    $ arm-none-eabi-as --version
    GNU assembler (GNU Tools for ARM Embedded Processors) 2.24.0.20150604
    Copyright 2013 Free Software Foundation, Inc.
    This program is free software; you may redistribute it under the terms of
    the GNU General Public License version 3 or later.
    This program has absolutely no warranty.
    This assembler was configured for a target of `arm-none-eabi'.
    $ git --version
    git version 1.9.3

Note: After typing in `arm-none-eabi-as --version` and seeing the output be sure to press `Ctrl-C` or `Ctrl-D` to return to the shell.
If this doesn't work, don't worry. We will help you get set up in lab.

We will use the following hand tools during this lab:

![Tools]

We do not have enough tools for everyone, so you will have to share them.
If you own tools, bring them to lab.
We like people to use their own tools;
it is very empowering.
It also means you will be able to work outside of lab.
If you don't own these tools, don't worry.
If you want to buy tools and don't know what to buy,
talk to the instructors. They love tools!

During this first lab you will be using 
a wire strippers/cutter (yellow handled widget),
a needle-nose pliers (green-handled widget),
and a multimeter (the orange thing with a display).
Don't worry about wire and other supplies; we'll provide that.

### Lab exercises

#### 1. Assemble the blink program

All CS107e labs and assignments are distributed and managed as git repositories.
For assignments, your code will be in your own personal repository 
so that you can push your final code for grading.
For labs, you will not need to turn in your code,
so you will be able 
to simply pull the current courseware repo for the class 
and work off the lab code from there.

Clone the courseware repo: 

    $ git clone https://github.com/cs107e/cs107e.github.io

Pull up the [checklist form](checklist) and have it open in a browser
so you can jot things down as you go. Only one checklist needs to be
submitted for both you and your partner.

Now `cd cs107e.github.io/_labs/lab1/code/blink` and type the commands:

    $ arm-none-eabi-as blink.s -o blink.o
    $ arm-none-eabi-objcopy blink.o -O binary blink.bin

If this works, you are good to go.

#### 2. Inventory your Raspberry Pi kit

You will receive the official CS107e Raspberry Ki kit when you get to the lab.
The kit comes in a plastic sandwich box, and contains the following parts:

![Kit]

-   Raspberry Pi A+
-   4GB SDHC card
-   USB serial cable with jumpers
-   Breadboard
-   8 LEDs
-   4 pushbuttons and colored caps
-   4 10K resistors (for push buttons)
-   20 1K resistors (for leds, 4-digit display, transistors)
-   4 2n3904 bipolar-junction transistors (BJTs).
-   20 20cm female-male jumpers
-   10 10 cm (short) female-female jumpers
-   10 20 cm female-female jumpers
-   20 male-male jumpers in various sizes

(Recall that a [resistor](https://learn.sparkfun.com/tutorials/resistors)'s colors tell its resistance: in this case,
10K or 1K ohms. Check out this [chart and calculator](http://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-resistor-color-code-4-band).)

Take a moment to identify and inventory all the parts.
Make sure your kit is complete.

#### 3. Wire and power your breadboard

The next step is to wire up your breadboard.

![Breadboard][1]

It is a little hard to describe this process in writing.
You may want to find someone in the lab who has done it before
and watch what they do.
When wiring a breadboard cut your wires to the proper length,
and arrange them neatly.
Take your time and check your work.

To begin, make sure you understand how breadboards work.
What holes are connected to what holes?
How are the power and ground rails connected?

Note that LEDs are directional.
The longer lead is the anode and the shorter lead is the cathode.
The voltage from anode to the cathode should be positive.
If the polarity of voltages are switched, the LED will not light up.

A LED needs a 1K current limiting resistor
otherwise it will literally blow up (you may even see smoke).
Current will flow through this resistor and then through the LED.
There are various ways to wire up the LED (see below);
we connected the cathode of the LED to the resistor 
and then connected the other end of the resistor to GND 
(the blue bus).
Note how the LED crosses over the middle of the breadboard.
To light up the LED, we need to apply 3.3V or 5V to the anode
and complete the circuit by connecting the cathode to GND.

To check that the LEDs are working, you need a power source.
We will draw power from your laptop
using the *USB to Serial Cable*.
This is the small black breakout board with a USB connector
on one side and a 6-pin header on the other side.
The USB connector is inserted into a USB port on your laptop,
and the header has power and ground pins.

When wiring, electronics gurus use colored wires to indicate what type of
signal is being carried by that wire.
This makes debugging tangled wires much easier.
Generally, we will use the following conventions.

-   Black (GND)
-   Red (5V)
-   Orange (3.3V)
-   Yellow (output)
-   White (input)

For now, you will need just red and black jumpers.

To provide power to your breadboard,
do the following steps in precisely this order.

1. Find two 20cm female-male jumper cables, one red and one black.

2. Plug the female ends of the jumpers to the usb-serial breakout board.
Plug the red jumper to VCC and the black jumper to GND.

3. Plug the male end of the black jumper into the blue
ground rail of the breadboard. 
Then plug the male end of the red jumper to the anode of an LED.

4. Plug the USB connector into your laptop.
A small led should light up on the breakout board
showing that it has power.
The LED connected to the red jumper should also now be lit.
One by one, check that each LED is wired properly.
When you have finished, here is what it should look like.

![LED]

**Warning:
Don't have the usb serial breakout board plugged in 
while you are fiddling with the wiring.
This can cause a short circuit, which could fry your Pi.**

While the LED is lit, make the following measurements with the multimeter.

-   Measure and record the voltage across the resistor.
-   Measure and record the voltage across the LED.

Calculate the current flowing through the LED.
Enter the calculated current on your lab checklist.

#### 4. Powering your breadboard via the Pi

Now we will rewire things so that we power the Raspberry Pi,
and also have it provide power to the breadboard.

Note the GPIO header with 40 pins on the side of the Raspberry Pi A+.
The pin configurations along the outer edge of the board are

    2  5V
    4  5V
    6  GND

(Note that pins 2 and 4 are connected together.)

Here is a detailed diagram of all the GPIO pins.
Find all the GNDs and power pins (both 3.3V and 5V).

![GPIO](images/gpio.jpg)

In order to connect the usb-serial breakout board to the Raspberry Pi,
we will need female-female jumpers.
Replace the red and black female-male jumpers 
with red and black female-female jumpers.
Wire VCC on the usb-serial breakout to 5V on the Pi,
and GND on the breakout board to GND on the Pi.
Now connect the female-male jumpers that were originally connected
to the breakout board to the GPIO headers on the Pi.
Inspect the diagram above and find a pin that provides 5V,
and another pin that is GND.
Power is now flowing through the usb-serial breakout board
to the Raspberry Pi and then to the breadboard.

After finishing wiring things up,
insert the usb serial breakout board in your laptop - 
the LED should light up.
You should also see the POWER led on the Raspberry Pi lit up.

![Pi LED]

Replace your 1K resistor with a 10K resistor. Does the brightness of
the LED change? (You might want to coordinate with another group so
you can compare them side by side.) Why?

#### 5. Use the SD card

Your Raspberry Pi kit contains a Kingston SDHC card.
A secure digital (SD) card contains non-volatile memory for storage.
The HC in SDHC stands for high capacity.

<img title="Kingston SDHC Card" src="/images/kingston.sdhc.jpg" width="200">

The Raspberry Pi runs the software on the SDHC card 
inserted in the SD card holder on the bottom of the printed circuit board.

<img title="SDHC Card" src="/images/pi.sd.jpg" width="200">

Most laptops contain a SD slot.
To copy software to the SDHC card,
you need to mount it on your laptop.
First, insert the SDHC card into your laptop. 
In order to do this, you will need to insert the
SDHC card into the SD card holder,
and then insert the holder into your laptops SD card slot.

![SDHC holder](/images/mac.sd.jpg)

**Some laptops do not contain a SD card slot.
If your laptop does not contain an SD card slot,
we recommend you mount the SD card and copy files
using using your partner's laptop.**

When you insert the SDHC card it should mount automatically.
You should see it show up in your finder.

<img title="SD Finder" src="/images/mac.finder.jpg" width="500">

Another way to cerify that the card is mounted is to list 
the mounted Volumes.

    $ ls /Volumes
    Macintosh HD    NO NAME

By default, the SD card volume is named `NO NAME`.
You can change the name if you wish.

Now, we'll use the Raspberry Pi firmware, which is also in our 
[GitHub repository](https://github.com/cs107e/cs107e.github.io/tree/master/firmware).

There should be 5 files there.

    $ cd firmware
    $ ls
    blink-onboard.bin   bootloader.bin  start.elf
    bootcode.bin    config.txt

`bootcode.bin` is the code that boots GPU,
and `start.elf` is the GPU start up code. `config.txt` is some
configuration for when the Pi boots.

For the Pi to work, you need to put those three files on the SD card,
plus an additional file, named `kernel.img`. But notice that we don't
give you a `kernel.img` here!

Normally, `kernel.img` is the operating system kernel you want to run
on the Pi, like Linux or Windows. In this course, we will write our
own programs to take its place, and put one of them in under the name
`kernel.img` instead.

Now notice that we've given you two additional programs,
`blink-onboard.bin` and `bootloader.bin`. We will run
`blink-onboard.bin` first, which blinks the on-board activity (ACT)
LED.

Next, follow these steps in the following order:

1. Copy these files onto your SD card. (You can use either the Terminal
or the Finder for this.)

2. Once on your SD card, rename the copy
of `blink-onboard.bin` to `kernel.img`. Now the Pi should run our
blink-onboard program after we put the card in!

3. Go to the Finder and click on the Eject icon next to the file name.
You can now remove the SD card safely.

4. Insert the SD card into the Raspberry Pi.

5. Power it up. 
The on-board activity (ACT) LED on the Raspberry Pi board 
should start blinking.

Hoorah!

**If you have trouble,
check out the troubleshooting part of the
[working with sd cards] guide.
This part has been written assuming you have a Mac,
there are also instructions in this guide for 
how to do this process using linux.**

Keep this procedure in the back of your mind.
If you ever think your Pi is not working because of a hardware problem,
repeat these steps.
If the ACT LED doesn't blink after booting, 
then something is wrong and you may need to replace the Pi with a working one.

#### 6. Blink the breadboard LED

Now let's blink the LED on your breadboard.
Wire the LED on your breadboard to GPIO 20 (pin 38).

![GPIO 20 connected to LED]

Mount the SD card again. Delete the `kernel.img` we put there before.

This time, copy your assembled `blink.bin` file 
(the one you created in lab step 1)
to your SD card and rename it `kernel.img`.

You've basically replaced the `kernel.img` you put in there before (which
was a copy of `blink-onboard.bin`).

Eject the SD card and insert it into the raspberry pi.

It should now blink the LED on your breadboard.

Hoorah, hoorah!

#### 7. A better way: use the bootloader

Each time you change your code, you could repeat this process.
This would involve
powering down your Pi,
manually ejecting the SD card, 
inserting the SD card into your laptop,
copying the new version of your code to `kernel.img`,
unmounting and ejecting the SD card from your laptop,
inserting it into the Pi,
and then powering it up.
This quickly becomes tedious.
Even worse, the SD connectors are only designed to withstand
around 1000 insertions and deletions, after which they fail.

There is a better way: use a bootloader.
The bootloader avoids having 
to move your SD card back and forth 
between your laptop and the Raspberry Pi.
You will learn to love the bootloader.

To install the bootloader,
mount the SD card and copy `bootloader.bin` to the SD as `kernel.img`.
Now, when the Raspberry Pi powers up, the bootloader is run.

The bootloader listens on the serial port for commands 
to load a program into memory on the Pi. 
A program on your laptop sends the bytes 
contained in a binary (`.bin`) file to the bootloader 
and the bootloader copies them into the correct memory location.
After the program is loaded,
the bootloader jumps to the start address of the program,
and the program begins to run.
Much, much simpler.

In order to do this you need to establish a communication
channel between the Raspberry Pi and your laptop,
We will cover the details of serial communication 
latter in the course. For now let's just get everything setup.

We will be using a CP2102 usb-serial breakout board
that you are using to power your Pi also contains pins
to communicate with the Pi.

At the end of the breakout board is a 6 pin header.
Two other pins are used for transmitting (TX) and receiving (RX).
The Pi also has a TX and RX pin on the GPIO header.
These pins are on the outside of the header.
Starting at the top left corner, we have

     2 5V
     4 5V
     6 GND
     8 TX 
    10 RX

You have already connected 5V and GND.
Now connect the TX and RX pins on your Pi 
to the RX and TX pins on the USB breakout board.

**By convention, one device's TX should connect to the other's RX
, and vice versa.**

_Make sure you do **not** connect TX to TX and RX to RX!_

The proper connections are shown below.
Note that your USB breakout board may have pins in different positions.
Don't just follow the picture blindly!

![Console cable](/images/console.cable.zoom.jpg)

In this configuration, the yellow wire connects
the RX header pin on the usb serial breakout board
to the TX GPIO Pin 8 on the Pi's header.
The orange wire connects the TX header pin
to the RX GPIO Pin 10.

We have created a Python program that sends binary files to the bootloader.

Let's try the bootloader. In some Terminal shell, change back to the
directory where you assembled `blink.bin` in step 1. That's
`cs107e.github.io/_labs/lab1/code/blink/`.

Now to load and run `blink.bin`, simply type:

    $ rpi-install.py blink.bin
    Sent True
    $

After a few seconds, you should see the LED blinking.

**If you are on a Mac, make sure you installed the CP2102 drivers,
as described in the [Mac toolchain guide](/guides/mac_toolchain).
On Windows or Linux, you don't need to do anything special here.**

If you change your program and wish to reload it onto the Pi, 
you must power cycle the Pi.
One way to do this is to unplug the usb-serial breakout board
from the usb slot on your laptop,
and then plug it in again.
The Pi will reboot into the bootloader 
and which will be ready to load the new version of the program.
Retype the above `rpi-install.py` command, 
and the new version will be downloaded and run.

Hoorah, hoorah, hoorah!!

#### 8. Study the blink program

    // configure GPIO 20 for output
    ldr r0, =0x20200008
    mov r1, #1
    str r1, [r0]

    mov r1, #(1<<20)

    loop:

        // set GPIO 20 high
        ldr r0, =0x2020001C
        str r1, [r0]

        // delay
        mov r2, #0x3F0000
        wait1:
            subs r2, #1
            bne wait1

        // set GPIO 20 low
        ldr r0, =0x20200028
        str r1, [r0]

        // delay
        mov r2, #0x3F0000
        wait2:
            subs r2, #1
            bne wait2

    b loop

If there is anything you don't understand about this program,
ask questions of your partner and others.

Do the following exercises:

-   Do a `hexdump` on the `blink.bin` you assembled earlier.
    Find the first occurence in the file of `e3`. What is the byte offset of `e3`
    relative to the start of the file?

-   Change the program such that the blink rate slows down by a factor of 2.
    Now perform experiments to determine how many instructions per second the
    Raspberry Pi executes.

#### 9. Run `button` on your Raspberry Pi (optional)

This last part is optional.
You do not need to use a pushbutton for Assignment 1,
but you will need to use it for Assignment 2.
There are no questions on the checklist for this exercise.

Now let's turn to the pushbuttons.
Measure the resistance across the pushbutton legs using a 
multimeter and figure out which pins are always connected 
and which become connected when the button is pushed.
Use your measurements to position the button correctly on the breadboard. 
The pushbutton needs a 10K pull-up resistor to the red power rail.
Verify that the resistor is 10K Ohms using the multimeter.
Measure the voltage at the pin, and measure it again when you push the button.

Here is a program that reads a button and turns on or off the LED depending on
whether the button is pressed.

    // configure GPIO 20 for output
    ldr r0, =0x20200008
    mov r1, #1
    str r1, [r0]

    // set bit 10
    mov r2, #(1<<10)

    // set bit 20
    mov r3, #(1<<20)

    loop:

        // read GPIO 10
        ldr r0, =0x20200034
        ldr r1, [r0]
        tst r1, r2
        bne off

        // set GPIO 20 high
    on:
        ldr r0, =0x2020001C
        str r3, [r0]
        b loop

        // set GPIO 20 low
    off:
        ldr r0, =0x20200028
        str r3, [r0]

    b loop

To run this program, connect the button to GPIO 10 (pin 19). Make sure the jumper is
connected to the right pin on the Raspberry Pi.
Also, make sure the pull-up resistor is properly installed on the breadboard.

Study this program.

Here are a few questions to test your knowledge.
To answer these questions you will have to read the
Broadcom peripheral manual, or ask someone who knows the answer.

-   Why don't we need to configure GPIO 10?

-   Why does the input value go to 0 (LOW) when the button is pressed?

-   What does the peripheral register with the address 0x20200034 return?


### Hand in your checklist to a TA

[Checklist][checklist form]

At the end of the lab period, hand in your checklist to a TA. The TA will
approve your submission so that you are properly credited for your
work.

Note, again, that the goal of the lab is not just to complete the
checklist -- it's to understand the material. The checklist is a very
rudimentary test of that.

It's okay if you don't completely finish all of the exercises during
lab; your sincere participation for the full lab period is sufficient
for credit.  However, if you don't finish, we highly encourage you to
work those parts to solidify your knowledge of this material before
moving on! In particular, the first assignment assumes you have
successfully completed this lab.

  [instructions]: /guides/vmware/
  [assignment 0]: /assignments/assign0/
  [Tools]: images/tools.jpg
  [checklist form]: checklist
  [Kit]: images/kit.jpg
  [guide]: http://ch00ftech.com/2012/07/28/the-ch00ftech-guide-to-breadboarding/
  [video]: https://www.youtube.com/watch?v=Yzfk0t0HfZc#t=225
  [Breadboard]: images/ch00ftech.jpg
  [1]: images/breadboard.jpg
  [LED]: images/led.jpg
  [GPIO]: images/gpio.jpg
  [Pi LED]: images/piled.jpg
  [working with sd cards]: http://cs107e.github.io/guides/sd/
  [GPIO 20 connected to LED]: images/piled.gpio20.jpg
  [bootloader guide]: /guides/bootloader
