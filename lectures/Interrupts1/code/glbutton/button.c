#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "debounce.h"
#include "uart.h"
#include "gl.h"

int npresses = 0;
int BUTTON_PIN = GPIO_PIN25;

unsigned gread(unsigned pin) {
  return gpio_read(BUTTON_PIN);
}

void wait_for_press(void) {
  while (gread(BUTTON_PIN) == 0) {}
  while (gread(BUTTON_PIN) == 1) {}
  npresses++;
}

void main(void) {
  gpio_init();
  timer_init();
  
  gpio_set_input(BUTTON_PIN);
  gpio_set_pullup(BUTTON_PIN);
  debounce_init(BUTTON_PIN);

  gl_init(1280,960,GL_DOUBLEBUFFER);
  
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
