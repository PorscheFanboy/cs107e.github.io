#ifndef KEYBOARD_EMULATOR_H
#define KEYBOARD_EMULATOR_H

void keyboard_emulator_init();

void keyboard_write(char *char_seq);

void keyboard_write_char(char ch);

void keyboard_hold_key(unsigned scancode, unsigned time_us);

void keyboard_press_extended_key(unsigned scancode);

void keyboard_write_event(unsigned scancode, int down);

void keyboard_write_scancode(unsigned scancode);

#endif
