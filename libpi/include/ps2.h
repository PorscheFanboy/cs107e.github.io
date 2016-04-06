#ifndef PS2_H
#define PS2_H

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

int is_char[] = {
    0, // 00
    0, // 01, F9
    0, // 02
    0, // 03, F5
    0, // 04, F3
    0, // 05, F1
    0, // 06, F2
    0, // 07, F12
    0, // 08
    0, // 09, F10
    0, // 0A, F8
    0, // 0B, F6
    0, // 0C, F4
    1, // 0D, 	,
    1, // 0E, `, ~
    0, // 0F
    0, // 10
    0, // 11, LEFT_ALT
    0, // 12, LEFT_SHIFT
    0, // 13
    0, // 14, LEFT_CONTROL
    1, // 15, q, Q
    1, // 16, 1, !
    0, // 17
    0, // 18
    0, // 19
    1, // 1A, z, Z
    1, // 1B, s, S
    1, // 1C, a, A
    1, // 1D, w, W
    1, // 1E, 2, @
    0, // 1F
    0, // 20
    1, // 21, c, C
    1, // 22, x, X
    1, // 23, d, D
    1, // 24, e, E
    1, // 25, 4, $
    1, // 26, 3, #
    0, // 27
    0, // 28
    1, // 29, SPACE
    1, // 2A, v, V
    1, // 2B, f, F
    1, // 2C, t, T
    1, // 2D, r, R
    1, // 2E, 5, %
    0, // 2F
    0, // 30
    1, // 31, n, N
    1, // 32, b, B
    1, // 33, h, H
    1, // 34, g, G
    1, // 35, y, Y
    1, // 36, 6, ^
    0, // 37
    0, // 38
    0, // 39
    1, // 3A, m, M
    1, // 3B, j, J
    1, // 3C, u, U
    1, // 3D, 7, &
    1, // 3E, 8, *
    0, // 3F
    0, // 40
    1, // 41, ,, <
    1, // 42, k, K
    1, // 43, i, I
    1, // 44, o, O
    1, // 45, 0, )
    1, // 46, 9, (
    0, // 47
    0, // 48
    1, // 49, ., >
    1, // 4A, /, ?
    1, // 4B, l, L
    1, // 4C, ;, :
    1, // 4D, p, P
    1, // 4E, -, _
    0, // 4F
    0, // 50
    0, // 51
    1, // 52, ', "
    0, // 53
    1, // 54, [, {
    1, // 55, =, +
    0, // 56
    0, // 57
    0, // 58, CAPS
    0, // 59, RIGHT_SHIFT
    1, // 5A,
    1, // 5B, ], }
    0, // 5C
    1, // 5D, \, |
    0, // 5E
    0, // 5F
    0, // 60
    0, // 61
    0, // 62
    0, // 63
    0, // 64
    0, // 65
    1, // 66, , 
    0, // 67
    0, // 68
    0, // 69, KEYPAD_1
    0, // 6A
    0, // 6B, KEYPAD_4
    0, // 6C, KEYPAD_7
    0, // 6D
    0, // 6E
    0, // 6F
    0, // 70, KEYPAD_0
    0, // 71, KEYPAD_PERIOD
    0, // 72, KEYPAD_2
    0, // 73, KEYPAD_5
    0, // 74, KEYPAD_6
    0, // 75, KEYPAD_8
    1, // 76, ESC
    0, // 77, NUM
    0, // 78, F11
    0, // 79, KEYPAD_PLUS
    0, // 7A, KEYPAD_3
    0, // 7B, KEYPAD_MINUS
    0, // 7C, KEYPAD_TIMES
    0, // 7D, KEYPAD_9
    0, // 7E, SCROLL
    0, // 7F
};


static const char shift_char_from_scan[] = {
    ' ', // 0x00
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ', // 0x08
    ' ',
    ' ',
    ' ',
    ' ',
    '\t',
    '~',
    ' ',
    ' ', // 0x10
    ' ',
    ' ',
    ' ',
    ' ',
    'Q',
    '!',
    ' ',
    ' ', // 0x18
    ' ',
    'Z',
    'S',
    'A',
    'W',
    '@',
    ' ',
    ' ', // 0x20
    'C',
    'X',
    'D',
    'E',
    '$',
    '#',
    ' ',
    ' ', // 0x28
    ' ',
    'V',
    'F',
    'T',
    'R',
    '%',
    ' ',
    ' ', // 0x30
    'N',
    'B',
    'H',
    'G',
    'Y',
    '^',
    ' ',
    ' ', // 0x38
    ' ',
    'M',
    'J',
    'U',
    '&',
    '*',
    ' ',
    ' ', // 0x40
    '<',
    'K',
    'I',
    'O',
    ')',
    '(',
    ' ',
    ' ', // 0x48
    '>',
    '?',
    'L',
    ':',
    'P',
    '_',
    ' ',
    ' ', // 0x50
    ' ',
    '\"',
    ' ',
    '{',
    '+',
    ' ',
    ' ',
    ' ', // 0x58
    ' ',
    '\n',
    '}',
    ' ',
    '|',
    ' ',
    ' ',
    ' ', // 0x60
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    '\b',
    ' ',
    ' ', // 0x68
    '1',
    ' ',
    '4',
    '7',
    ' ',
    ' ',
    ' ',
    '0', // 0x70
    '.',
    '2',
    '5',
    '6',
    '8',
    ' ',
    ' ',
    ' ', // 0x78
    '+',
    '3',
    '-',
    '*',
    '9',
    ' ',
    ' '
};

static const char char_from_scan[] = {
    ' ', // 0x00
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ', // 0x08
    ' ',
    ' ',
    ' ',
    ' ',
    '\t',
    '`',
    ' ',
    ' ', // 0x10
    ' ',
    ' ',
    ' ',
    ' ',
    'q',
    '1',
    ' ',
    ' ', // 0x18
    ' ',
    'z',
    's',
    'a',
    'w',
    '2',
    ' ',
    ' ', // 0x20
    'c',
    'x',
    'd',
    'e',
    '4',
    '3',
    ' ',
    ' ', // 0x28
    ' ',
    'v',
    'f',
    't',
    'r',
    '5',
    ' ',
    ' ', // 0x30
    'n',
    'b',
    'h',
    'g',
    'y',
    '6',
    ' ',
    ' ', // 0x38
    ' ',
    'm',
    'j',
    'u',
    '7',
    '8',
    ' ',
    ' ', // 0x40
    ',',
    'k',
    'i',
    'o',
    '0',
    '9',
    ' ',
    ' ', // 0x48
    '.',
    '/',
    'l',
    ';',
    'p',
    '-',
    ' ',
    ' ', // 0x50
    ' ',
    '\'',
    ' ',
    '[',
    '=',
    ' ',
    ' ',
    ' ', // 0x58
    ' ',
    '\n',
    ']',
    ' ',
    '\\',
    ' ',
    ' ',
    ' ', // 0x60
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    '\b',
    ' ',
    ' ', // 0x68
    '1',
    ' ',
    '4',
    '7',
    ' ',
    ' ',
    ' ',
    '0', // 0x70
    '.',
    '2',
    '5',
    '6',
    '8',
    ' ',
    ' ',
    ' ', // 0x78
    '+',
    '3',
    '-',
    '*',
    '9',
    ' ',
    ' '
};

#endif
