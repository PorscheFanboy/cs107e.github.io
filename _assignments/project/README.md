---
layout: page
title: 'Project Suggestions and Guides'
permalink: /assignments/project/
---

The final assignment is a project of your own choosing. 
The goal of the project is to consolidate 
your knowledge of the key concepts in CS107e,
and to do something creative with your Raspberry Pi.

You have two weeks to complete the project. 
There are a few important deliverables:

1. *Project team formation: due Sun May 22*

  Form a team of 1 to 3 people. In our experience, 2 is best.
  Add the Github usernames of your team members to this 
  [Google form](http://goo.gl/forms/sGdJ1dirG1dm9GRb2) so that we can 
  create a repository for your team.

2. *Project description: due Thu May 26*

  We will email you after making a repository for your team; that
  repository will be empty at first. Follow the GitHub instructions on
  its page to 'create a new repository on the command line' and push
  to there.

  Now add a markdown file PROPOSAL.md in that repo.
  This file is for your project proposal.
  Edit that file and push it to github.

  The project proposal should include:

  - Name of the project
  - Team members and their responsibilities
  - Goal of the project
  - Milestone for T-1 week
  - Resources needed

  We have a small budget for hardware, 
  so we can reimburse you for parts (within reason).
  If you want to buy stuff,
  please send us email.
  Be aware that if you need to mail order parts, it can take time,
  so figure out what you need ASAP and place the order.
  You should first check the list of sensors we already have 
  on hand (see below).

  Each team member should be responsible for a clearly
  identifiable part of the project.

3. *Project labs*

  We will still have labs the two weeks leading up to the
  project demonstration.
  These labs will be a good time to check-in with the
  course staff; they are eager to help you create a great project.
  In the second lab, we will check whether you have made
  your milestone.
  Please don't wait until the last minute to get started on your project.

4. *Project demonstration: Tue June 7, 3:30-6:30 pm, Gates 325*

  We will have a class demo day for all projects.
  The demos are scheduled during the final exam period.
  Each group should prepare a short demonstration of the project.

5. *Project code and writeup: due Wed June 8 at 11:59 pm*

  You should be using the github repository for coordinating the
  work amongst your team.
  As such, you should be regularly checking in and out code.
  Do the final check-in by 11:59 pm on Wed June 8.

  Create a short writeup about your project
  and place it in README.md.
  If you have used code or ideas from other people,
  please attribute their work.
  It's fine to use code from online,
  but you must reference where you got the code,
  and what changes you made.
  It should be clear what you did, and what others did.

  The writeup should also include a short description of what
  work was performed by each member of the team.

## Extra materials

Beyond what you've seen in the course, we have some additional
materials which you can use in the final project.

### Sensors

We have
[a number of different hardware sensors](https://docs.google.com/document/d/16D0wGRi7qUQamM8YR5XpcijSIifN1kzOvFWOoB_UHyk/pub)
which you could use for your project; they're available for you to
check out in lab. Let us know if you'd like to use one of them.

### Support code

The Raspberry Pi has on-board SPI and I2C controllers, which you can use to
communicate with many kinds of sensors and devices that speak those protocols.
For example, if you want to have analog input, we have an analog-to-digital
converter, the MCP3008, which would communicate over a SPI interface with your Pi.

libpi contains a
[SPI driver](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/src/spi.c)
([header file](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/spi.h))
and an
[I2C driver](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/src/i2c.c)
([header file](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/i2c.h))
providing a high-level C interface to the device registers for those
controllers. Feel free to use these for your project.

libpi also contains an experimental
[filesystem interface](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/src/fs.c)
([header file](https://github.com/cs107e/cs107e.github.io/blob/master/libpi/include/fs.h))
which you can use to interact with the files on the SD card. This enables you to
do operating-system-like things, like maybe run programs off the card,
or store large data files without having to copy them over the
bootloader every time, or save documents.

## Project suggestions

The best projects are ones that you think of yourself.
Feel free to browse the internet in search of cool things to do.
Some good sources are [hackaday.com](http://hackaday.com) and 
[adafruit.com/blog](https://blog.adafruit.com).

### Game

You have the start of a graphics and input library.
Extend your graphics library to draw additional types of objects,
and your input library to handle a game controller.

Some examples of input devices that you could use to control your game:

- A homebrew game pad made of buttons. Most game pads have
two buttons (A and B) for game control,
and 4 buttons used as a d-pad (left, right, up, down).

- Your PS/2 keyboard and/or mouse.

- Atari 2600 paddle controllers (or other paddle controllers).

- Old-school NES, SNES, or other simple gamepads with simple digital protocols.

Once you have better input, you are all set to build a game.
Build a simple game such as Pong or Tetris,
or even better a game of your own design.

Another cool thing you can do is communicate with old game cartridges, since you
can connect the pins on the cartridge to the GPIO pins on the Pi.

### Music

We described how to generate notes on the Raspberry Pi.
With that knowledge, you can 

- Create a simple music player that allows the user 
to choose from a list of simple melodies.
Add buttons on a breadboard for control (skip, pause, play, volume?)

- Turn your keyboard into a music keyboard,
so that keys play individual notes and pressing multiple keys 
at the same time combines the notes.
Use a combination of timers and low-level keyboard access 
to enable you to record and then loop tracks.

- Take a music synthesizer such as the Korg Monotron 
and hack it to add MIDI support with one Pi,
then have a second Pi control it over MIDI.
Alternatively, build your own music synthesizer.

## System components

Your project should be about building a working system that does something cool.

However, if you build some support infrastructure,
then you can build a more impressive system.
A good sub-project for a team member
is to build a component of the system.

### Analog input

Up to now, we have only read digital values using GPIO.
The Raspberry Pi, unlike a microcontroller like an Arduino,
cannot read analog values.

Many sensors are analog:
  - Photodetectors
  - Potentiometers
  - Temperature sensors
  - Joysticks

In order to read analog values, you will need to interface an analog
to digitial convertor (ADC) to the Raspberry Pi.  An example of an ADC
is the MCP3008, which can be controlled from the PI using the Serial
Peripheral Interface (SPI) protocol.

Write a program that uses some
analog inputs to produce an interesting result, such as a screen
visualization or sound.

### Network (Ambitious)

Build a simple network that allows multiple raspberry pis to communicate
over a shared medium (only one Pi can transmit at a time).
One way to do this is to connect TX and RX pins to a
shared line.

It is also possible to communicate by other means.
For example, you could use sound, light, or radio waves.

Finally, you've seen in class how "digital" lines aren't purely digital.
You could design your circuit to make bits as sharp as possible to see how
fast you can transmit and receive. You might find that sending bits faster
means you'll have to send smaller packets, so optimize for overall data
transfer, not just the bit rate.

### GPU (Ambitous)

The raspberry pi has a very powerful GPU.
In fact, the GPU is much faster than the CPU.
The GPU assembly language is similar to,
but different,
than the CPU assembly language.
It is possible to download code to the GPU using a mailbox,
and then call that code.
Learn about the GPU and build a library for programming the GPU.

Can you think of a computationally intensive task 
that could be off-loaded to the GPU? At the very least, you can clear your
screen buffer faster!
