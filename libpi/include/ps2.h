#ifndef PS2_H
#define PS2_H

/* Useful constants and lookup tables for PS/2 scan codes. This
 * file allows you to refer to scan codes by their associated character
 * (e.g., KEY_C) as well as provides three tables that specify whether
 * a scan code is associated with a printable character (e.g., 'c') rather
 * than control keys (e.g., shift).
 * 
 * You will use this interface in assignment 5 to implement a keyboard
 * driver.
 *
 * Author: Philip Levis
 * Date:   6/20/17
 */ 


 
extern const int is_char[];
extern const char shift_char_from_scan[];
extern const char char_from_scan[];



#define MAX_KEYS 128

#define PS2_CODE_RELEASE     0xF0
#define PS2_CODE_EXTEND      0xE0

#define KEY_A                0x1C
#define KEY_B                0x32
#define KEY_C                0x21
#define KEY_D                0x23
#define KEY_E                0x24
#define KEY_F                0x2B
#define KEY_G                0x34
#define KEY_H                0x33
#define KEY_I                0x43
#define KEY_J                0x3B
#define KEY_K                0x42
#define KEY_L                0x4B
#define KEY_M                0x3A
#define KEY_N                0x31
#define KEY_O                0x44
#define KEY_P                0x4D
#define KEY_Q                0x15
#define KEY_R                0x2D
#define KEY_S                0x1B
#define KEY_T                0x2C
#define KEY_U                0x3C
#define KEY_V                0x2A
#define KEY_W                0x1D
#define KEY_X                0x22
#define KEY_Y                0x35
#define KEY_Z                0x1A
#define KEY_0                0x45
#define KEY_1                0x16
#define KEY_2                0x1E
#define KEY_3                0x26
#define KEY_4                0x25
#define KEY_5                0x2E
#define KEY_6                0x36
#define KEY_7                0x3D
#define KEY_8                0x3E
#define KEY_9                0x46
#define KEY_BACKQUOTE        0x0E
#define KEY_MINUS            0x4E
#define KEY_EQUAL            0x55
#define KEY_BACKSLASH        0x5D
#define KEY_BACKSPACE        0x66
#define KEY_SPACE            0x29
#define KEY_TAB              0x0D
#define KEY_CAPS             0x58
#define KEY_LEFT_SHIFT       0x12
#define KEY_LEFT_CONTROL     0x14
#define KEY_LEFT_ALT         0x11
#define KEY_RIGHT_SHIFT      0x59
#define KEY_ENTER            0x5A
#define KEY_ESC              0x76
#define KEY_F1               0x05
#define KEY_F2               0x06
#define KEY_F3               0x04
#define KEY_F4               0x0C
#define KEY_F5               0x03
#define KEY_F6               0x0B
#define KEY_F8               0x0A
#define KEY_F9               0x01
#define KEY_F10              0x09
#define KEY_F11              0x78
#define KEY_F12              0x07
#define KEY_SCROLL           0x7E
#define KEY_LEFT_BRACKET     0x54
#define KEY_NUM              0x77
#define KEY_KEYPAD_TIMES     0x7C
#define KEY_KEYPAD_MINUS     0x7B
#define KEY_KEYPAD_PLUS      0x79
#define KEY_KEYPAD_PERIOD    0x71
#define KEY_KEYPAD_0         0x70
#define KEY_KEYPAD_1         0x69
#define KEY_KEYPAD_2         0x72
#define KEY_KEYPAD_3         0x7A
#define KEY_KEYPAD_4         0x6B
#define KEY_KEYPAD_5         0x73
#define KEY_KEYPAD_6         0x74
#define KEY_KEYPAD_7         0x6C
#define KEY_KEYPAD_8         0x75
#define KEY_KEYPAD_9         0x7D
#define KEY_RIGHT_BRACKET    0x5B
#define KEY_SEMICOLON        0x4C
#define KEY_QUOTE            0x52
#define KEY_COMMA            0x41
#define KEY_PERIOD           0x49
#define KEY_DIVIDE           0x4A

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
