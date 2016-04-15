/* Functions for the Raspberry Pi status LED.
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Date: August 14 2014
 */
#include "memory.h"
#include "gpio.h"
#include "led.h"
#include "pi.h"

static int led_state_;

void led_init(void) {
    gpio_init();
    gpio_set_function(ACT, GPIO_FUNC_OUTPUT);
}

void led_write(int val) {
    gpio_write(ACT, val);
}

void led_on(void) {
    led_state_ = 1;
    led_write(led_state_);
}

void led_off(void) {
    led_state_ = 0;
    led_write(led_state_);
}

void led_toggle(void) {
    if (led_state_) {
        led_off();
    } else {
        led_on();
    }
}
