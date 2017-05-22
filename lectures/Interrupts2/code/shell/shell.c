#include "gl.h"
#include "console.h"
#include "timer.h"
#include "keyboard.h"
#include "interrupts.h"
#include "led.h"
#include "shell.h"

/* This program tests the keyboard using the console.
 * Characters read from the keyboard and printed to the console.
 * If the keyboard is blocking it drops events.
 */

void main() {
    console_init(40, 80);
    keyboard_init();
    shell_init(1);
    gl_draw_rect(10, 470, 630, 5, GL_RED);
    gl_draw_line(10, 10, 630, 480, GL_GREEN);
    gl_swap_buffer();
    delay(1);
    system_enable_interrupts();
    shell_run();
}
