#include "gpio.h"

/*
 * initializes gpio - does not need to anything
 */
void gpio_init(void) {
}

/*
 * Set GPIO pin number `pin` to the GPIO function `function`. Does not affect
 * other pins.
 *
 * @param pin the pin number to initialize
 * @param function the GPIO function to set for the pin
 */
void gpio_set_function(unsigned int pin, unsigned int function) {
  // TODO: Your code goes here.
}

/*
 * Get the function for GPIO pin number `pin`. Should not affect
 * any registers.
 *
 * @param pin the pin number to initialize
 */
unsigned int gpio_get_function(unsigned int pin) {
  // TODO: Your code goes here.
  return 0; // temporary
}

/*
 * Sets GPIO pin number `pin` to the value `value`. The GPIO pin should be set
 * the output mode for this call to function correctly.
 *
 * @param pin the pin number to set or clear
 * @param value 1 if the pin should be set, 0 otherwise
 */
void gpio_write(unsigned int pin, unsigned int value) {
  // TODO: Your code goes here.
}

/*
 * Read GPIO pin number `pin`. 
 *
 * @param pin the pin number to be read
 */
unsigned int gpio_read(unsigned int pin) {
  // TODO: Your code goes here.
  return 0; // temporary
}
