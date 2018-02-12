#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ps2.h"

/*
 * High-level interface to reading ASCII bytes from a keyboard.
 * You implement this interface in assignments 5 and 7.

 * Author: Philip Levis <pal@cs.stanford.edu>
 *
 * Date: April 5, 2016
 */

enum keyboard_modifiers {
    KEYBOARD_MOD_SCROLL_LOCK = 1 << 0,
    KEYBOARD_MOD_NUM_LOCK = 1 << 1,
    KEYBOARD_MOD_CAPS_LOCK = 1 << 2,
    KEYBOARD_MOD_SHIFT = 1 << 3,
    KEYBOARD_MOD_ALT = 1 << 4,
    KEYBOARD_MOD_CTRL = 1 << 5,
};

void keyboard_init(void);

// Top-level keyboard interface. Read (blocking) next key down from
// the keyboard. Handles shift, caps lock, etc. If you need to return
// non-text characters, you can use values > 0x7f (e.g., the
// keyboard codes defined in ps2.h).

unsigned char keyboard_read_next(void);


typedef struct {
    unsigned char seq[3];   // contains sequence of raw scan code bytes
    int seq_len;            // number of bytes in raw sequence
    ps2_key_t key;          // which key on keyboard (see ps2.h for table)
    unsigned int action;    // either KEYBOARD_ACTION_UP or KEYBOARD_ACTION_DOWN
    unsigned int modifiers; // modifiers in effect for event
} key_event_t;

/*
 * Middle-level keyboard interface. Returns (blocking) the result of
 * a full PS2 event, which key and whether it is up or down.
 * key has been pressed. Modifiers keys (CTRL, ALT. SHIFT, CAPS) are
 * not passed as key presses, instead their state is reported
 * in the modifiers field. This function calls keyboard_read_sequence.
 */
key_event_t keyboard_read_event(void);


/* Bottom level keyboard interface, part 2. Reads sequence of
 * scan codes corresponding to a key action (i.e. either an key
 * down or key up. The sequence may be a single byte (action was a 
 * simple key down), could be two bytes (action was a key up
 * or key down for extended scan code), or three bytes (action was a
 * key up for an extended scan code). The function stores the scan 
 * code bytes into the array and returns the number of bytes 
 * written to the array. This function calls keyboard_read_scancode.
 */
int keyboard_read_sequence(unsigned char seq[]);

/* Bottom level keyboard interface. Read (blocking) a single scan code
 * byte from the PS/2 keyboard.
 */
unsigned char keyboard_read_scancode(void);

#endif
