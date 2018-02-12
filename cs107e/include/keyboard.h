#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ps2.h"

/*
 * Module to read key events from a PS/2 keyboard.
 *
 * You implement this module in assignments 5 and 7.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Date:   Februrary 2018
 */

/* 
 * These bit flags are used for the state of the various modifiers
 * on the keyboard.
 */
enum keyboard_modifiers {
    KEYBOARD_MOD_SCROLL_LOCK = 1 << 0,
    KEYBOARD_MOD_NUM_LOCK = 1 << 1,
    KEYBOARD_MOD_CAPS_LOCK = 1 << 2,
    KEYBOARD_MOD_SHIFT = 1 << 3,
    KEYBOARD_MOD_ALT = 1 << 4,
    KEYBOARD_MOD_CTRL = 1 << 5,
};

enum keyboard_action {
    KEYBOARD_ACTION_DOWN,
    KEYBOARD_ACTION_UP
};

typedef struct {
    unsigned char seq[3];   // sequence of raw scan code bytes
    int seq_len;            // number of bytes in sequence
    ps2_key_t key;          // which key on keyboard (see ps2.h for table)
    unsigned int action;    // either KEYBOARD_ACTION_UP or KEYBOARD_ACTION_DOWN
    unsigned int modifiers; // modifiers in effect, composed of above bit flags
} key_event_t;


/*
 * `keyboard_init`: Required initialization for keyboard
 *
 * The keyboard must first be initialized before any key events can be read.
 */
void keyboard_init(void);


/*
 * `keyboard_read_next`: Top level keyboard interface.
 *
 * This function reads (blocking) the next key typed on the keyboard.
 * The character returned reflects the current keyboard modifier settings
 * for shift and caps lock.
 *
 * Characters returned that have value <= 0x7f '~' are printable ascii
 * characters. Character values >= 0x80 are used for the keys, such as
 * arrow and function keys, that are not associated with an ascii character.
 * See the ps2_codes defined in ps2.h for constants used for those keys.
 * This function calls `keyboard_read_event`.
 */
unsigned char keyboard_read_next(void);


/*
 * `keyboard_read_event`: Mid level keyboard interface.
 *
 * The function reads (blocking) the next key action from the keyboard.
 * Returns a `key_event_t` struct that represents the key event.  The
 * struct includes the raw scan code sequence, the action (up or down),
 * the keyboard key, and the state of the modifier flags in effect.
 * Note that a press or release of a modifier key (CTRL, ALT. SHIFT, etc)
 * is not returned as a key event. Instead those press/releases change
 * the state of the modifiers reported with subsequent key events.
 * This function calls `keyboard_read_sequence`.
 */
key_event_t keyboard_read_event(void);


/*
 * `keyboard_read_sequence`: Bottom level keyboard interface.
 *
 * Reads the sequence of scan codes corresponding to next key action.
 * A key action is either a key down or key up. A sequence can
 * 1, 2, or 3 bytes, as follows:
 *    1 byte:  key down for a simple key
 *    2 bytes: key up for a simple key or key down for an extended key
 *    3 bytes: key up for an extended key
 * The function stores the scan code bytes into the `seq` array and
 * returns the number of bytes written to the array. This function
 * calls `keyboard_read_scancode` to read each scan code.
 */
int keyboard_read_sequence(unsigned char seq[]);


/*
 * `keyboard_read_scancode`: Bottom level keyboard interface.
 *
 * Read (blocking) a single scan code byte from the PS/2 keyboard.
 * Bits are read on the falling edge of the clock.
 *
 * Trys to read 11 bits: 1 start bit, 8 data bits, 1 parity bit, and 1 stop bit
 *
 * Restarts the scan code if:
 *   (lab5) The start bit is incorrect
 *   (assign5) or parity check fails or stop bit is incorrect
 *
 * Returns the 8 data bits of a correctly received PS/2 message containing a
 * keyboard scan code. Will not return until it reads a valid scan code.
 */
unsigned char keyboard_read_scancode(void);

#endif
