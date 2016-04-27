#ifndef KEYBOARD_H
#define KEYBOARD_H

/*
 * High-level interface to reading ASCII bytes from a keyboard.
 * You implement this interface in assignments 5 and 7.

 * Author: Philip Levis <pal@cs.stanford.edu>
 *
 * Date: April 5, 2016
 */

void keyboard_init(void);

// Top-level keyboard interface. Read (blocking) a character from
// the keyboard. Handles shift, caps lock, etc. Should not return
// non-text characters unless they are translated into the text stream
// (e..g, control-G is \f). For example, keyboard_read_char should not
// return arrow key presses.
//

#define KEYBOARD_DOWN 0x82
#define KEYBOARD_UP   0x88
char keyboard_read_char(void);

// You do not have to implement right control or right alt: these keys
// are in the extended (0xE0) key set; they're included here for
// completeness, or if you are adventurous.
enum {
    KEY_MOD_NONE        = 0x0,  // No modifiers on

    KEY_MOD_LEFT_SHIFT  = 0x1,  // Left shift is down
    KEY_MOD_RIGHT_SHIFT = 0x2,  // Right shift is down
    KEY_MOD_SHIFT       = 0x3,  // Bitmask for testing either shift

    KEY_MOD_LEFT_CTRL   = 0x4,  // Left control
    KEY_MOD_RIGHT_CTRL  = 0x8,  // Right control (not required)
    KEY_MOD_CTRL        = 0xC,  // Bit mask for testing either control

    KEY_MOD_LEFT_ALT    = 0x10, // Left alt
    KEY_MOD_RIGHT_ALT   = 0x20, // Right alt (not required)
    KEY_MOD_ALT         = 0x30, // Bit mask for testing either alt

    KEY_MOD_CAPS        = 0x40, // Caps lock is active
};

typedef struct {
    unsigned char modifiers; // From KEY_MOD above
    unsigned char code;      // PS/2 code of key
} key_press_t;

// Third level keyboard interface. Returns (blocking) which
// key has been pressed. Modifiers keys (CTRL, ALT. SHIFT, CAPS) are
// not passed as key presses, instead their state is reported
// in the modifiers field of press. Control keys (arrows) are returned
// as their
key_press_t keyboard_read_press();

typedef struct {
    unsigned char down; // up = 0, down = 1,
    unsigned char code; // PS/2 code of key
} key_event_t;

// Second-level keyboard interface. Returns (blocking) the result of
// a full PS2 event, which key and whether it is up or down.
key_event_t keyboard_read_event();

// Bottom level keyboard interface. Read (blocking) a single scan code
// byte from the PS/2 keyboard.
int keyboard_read_scancode(void);

#endif
