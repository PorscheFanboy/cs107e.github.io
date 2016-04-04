#ifndef KEYBOARD_H
#define KEYBOARD_H


/*
 * High-level interface to reading ASCII bytes from a keyboard.
 * You implement this interface in assignments 6 and 7.
 
 * Author: Philip Levis <pal@cs.stanford.edu>
 *         
 * Date: Feb 15, 2016
 */

void keyboard_init(void);

// Blocks until a key is pressed, return the ASCII code of the key.
// In assignment 6, this will read directly from PS/2 pins.
// In assignment 7, key presses will put characters into a circular
// buffer in interrupts and function will read from the circular buffer.
char keyboard_read(void);

// Read a raw PS/2 scancode.
int keyboard_read_scancode(void);

#endif
