/**
 *  Uses GPIO events to detect falling edges on GPIO
 *  pin 23 (PS/2 clock line) and toggle the activity
 *  LED as well as GPIO2. Visual demonstration of 
 *  using GPIO event hardware support.
 *
 *  Author: Philip Levis <pal@cs.stanford.edu>
 *  Date: 4/26/16
 */

#include "gpio.h"
#include "gpioevent.h"
#include "gpioextra.h"
#include "led.h"

#define CLOCK_PIN GPIO_PIN23
#define DISPLAY_PIN GPIO_PIN2

void wait_for_clock() {
  while(gpio_check_event(CLOCK_PIN) == 0) {}
  gpio_clear_event(CLOCK_PIN);
}

void main(void) {
    gpio_init();
    led_init();

    gpio_set_output(DISPLAY_PIN);
    gpio_set_input(CLOCK_PIN);
    gpio_set_pullup(CLOCK_PIN);
    gpio_detect_falling_edge(CLOCK_PIN);
    while (1) {
        wait_for_clock();
	led_toggle();
	gpio_read(DISPLAY_PIN)? gpio_write(DISPLAY_PIN, 0) : gpio_write(DISPLAY_PIN, 1);
    }
}
