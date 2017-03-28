#include "gpio.h"
#include "gpioextra.h"
#include "gl.h"
#include "led.h"

#define LINE_SIZE 59

void gl_clear_slow(color c);

void wait_for_press() {
    while (gpio_read(GPIO_PIN21) == 0) {
        led_on();
    }
    while (gpio_read(GPIO_PIN21) == 1) {
        led_toggle();
    }
}

void main() {
    gpio_init();
    led_init();
    gl_init(640, 480, GL_DOUBLEBUFFER);

    unsigned int index = 0;
    char line[60];
    line[0] = 0;

    gpio_set_input(GPIO_PIN21);
    gpio_set_pullup(GPIO_PIN21);

    while (1) {
        gl_clear_slow(GL_BLACK);
        gl_draw_string(20, 20, "Button pushes: ", GL_WHITE);
        gl_draw_string(230, 20, line, GL_WHITE);
        gl_swap_buffer();
        wait_for_press();
        line[index] = '+';
        line[++index] = 0;
        if (index == 60) {
            index = 0;
        }
    }
}
