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
// the keyboard. Handles shift, caps lock, etc. If you need to return
// non-text characters, you can use values > 0x7f (e.g., the
// keyboard codes below). Some non-text characters do have ASCII
// representaitons // (e.g., control-G is \f). 

#define KEYBOARD_DOWN  0x82
#define KEYBOARD_UP    0x88
#define KEYBOARD_LEFT  0x84
#define KEYBOARD_RIGHT 0x86
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


/*
 * Copyright (c) 2017 Stanford University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the Stanford University nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL STANFORD
 * UNIVERSITY OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#endif
