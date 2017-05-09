#include <stdio.h>
#include "gpio.h"
#include "ps2.h"
#include "gpioextra.h"
#include "keyboard.h"
#include "uart.h"

const unsigned CLK  = GPIO_PIN23;
const unsigned DATA = GPIO_PIN24; 

void wait_for_falling_clock_edge() {
  while(gpio_read(CLK) == 0) {}
  while(gpio_read(CLK) == 1) {}
}

void keyboard_init(void) {
  gpio_set_function(CLK, GPIO_FUNC_INPUT); 
  gpio_set_pullup(CLK); 
 
  gpio_set_function(DATA, GPIO_FUNC_INPUT); 
  gpio_set_pullup(DATA); 
}

int keyboard_read_scancode(void) {
  // FIXME: Implement this function during lab5.
  return 0xa0;
}

key_event_t keyboard_read_event(void) {
  key_event_t event;
  return event;
}


key_press_t keyboard_read_press(void) {
  key_press_t press;
  return press;
}

char keyboard_read_char(void) {
  return 'x';
}

