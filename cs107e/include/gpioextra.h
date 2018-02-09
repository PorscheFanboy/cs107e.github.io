#ifndef GPIOEXTRA_H
#define GPIOEXTRA_H

/*
 * Functions for controlling the internal pull-up/down 
 * for Raspberry Pi GPIO pins.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 *         Philip Levis <pal@cs.stanford.edu>
 *         Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Last edited: Jan 2018
 */


/*
 * Set pull state of GPIO pin number `pin` to pull-up.
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_pullup(unsigned int pin);

/*
 * Set pull state of GPIO pin number `pin` to pull-down.
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_pulldown(unsigned int pin);

/*
 * Set pull state of GPIO pin number `pin` to none (will float).
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_pullnone(unsigned int pin);

#endif
