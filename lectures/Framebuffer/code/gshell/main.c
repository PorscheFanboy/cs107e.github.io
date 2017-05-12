#include "gl.h"
#include "console.h"
#include "timer.h"
#include "keyboard.h"
#include "mouse.h"
#include "interrupts.h"
#include "led.h"
#include "shell.h"

/*
 * This creates a shell over the serial line and turns on graphics.
 * The shell can draw lines and boxes, as well as directly poke
 * frame buffer memory. 
 */

void main() {
    gl_init(640, 480, GL_SINGLEBUFFER);
    keyboard_init();
    shell_init(0);
    gl_draw_rect(10, 470, 630, 5, GL_RED);
    gl_draw_line(10, 10, 630, 480, GL_GREEN);
    delay(1);
    system_enable_interrupts();
    shell_run();
}
