#include "printf.h"
#include "keyboard.h"

void main(void) {
    printf_init();
    keyboard_init();
    while (1) {
        int scancode = keyboard_read_scancode();
        printf("%02x\n", scancode);
    }
}

