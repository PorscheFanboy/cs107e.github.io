#include "keyboard.h"
#include "console.h"
#include "interrupts.h"
#include "gl.h"
#include "timer.h"

void main(void) {
    console_init(20, 40);
    keyboard_init();
    gl_draw_rect(10, 470, 630, 5, GL_RED);
    gl_draw_line(10, 10, 630, 480, GL_GREEN);
    gl_swap_buffer();
    delay(1);
    console_printf("Keyboard test.\n");
    system_enable_interrupts();
    while (1) {
        int key = keyboard_read_scancode();
        console_printf("scancode: %02x\n", key);
    }
}
