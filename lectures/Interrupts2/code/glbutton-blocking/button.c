#include "gpio.h"
#include "gpioextra.h"
#include "gl.h"

int npresses = 0;
int BUTTON_PIN = GPIO_PIN25;

void wait_for_press(void) {
    while (gpio_read(BUTTON_PIN) == 0) {}
    while (gpio_read(BUTTON_PIN) == 1) {}
    npresses++;
}

void main(void) {
    gpio_init();
    gl_init(640,480,GL_DOUBLEBUFFER);
  
    gpio_set_input(BUTTON_PIN);
    gpio_set_pullup(BUTTON_PIN);
  
    gl_clear(GL_BLACK);
    gl_swap_buffer();
    while (1) {
        wait_for_press();
        gl_clear(GL_BLACK);
        int x = 0;
        for( int i = 0; i < npresses; i++, x+=2 ) {
            gl_draw_char( x, 20, '+', GL_WHITE );
            x += gl_get_char_width();;
        }
        gl_swap_buffer();
    }
}
