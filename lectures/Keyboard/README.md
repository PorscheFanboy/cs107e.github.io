See http://www.computer-engineering.org/ps2protocol/

https://www.pjrc.com/teensy/td_libs_PS2Keyboard.html

Power to the PS2 should be 5V.

DATA and CLK are open collector. That means there is not
danger of driving the GPIO lines with 5V.

The clock and should be held high/low for 30-50 microseconds.
