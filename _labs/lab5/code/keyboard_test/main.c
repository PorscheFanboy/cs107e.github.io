#include "printf.h"
#include "keyboard.h"
#include "interrupts.h"

void main(void) {
    printf_init();
    keyboard_init();
    system_enable_interrupts();
    printf("Test\n");
    while (1) {
        int scancode = keyboard_read_scancode();
        if (scancode) {
            printf("%02x\n", scancode);
        }
    }
}

