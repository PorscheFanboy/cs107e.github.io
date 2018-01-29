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
 * These enumerated values establish symbolic names for each of 
 * possible GPIO pin pull-up/down states.
 */
enum {
    GPIO_PUD_DISABLE  = 0,
    GPIO_PUD_PULLDOWN = 1,
    GPIO_PUD_PULLUP   = 2,
};

/*
 * Set the pull-up/down state for GPIO pin number `pin`.
 *
 * @param pin      the GPIO pin number to enable pull-up/down
 * @param pud      the pull-up/down state to set for the pin
 *
 * If `pin` or `pud` is invalid, does nothing.
 */
void gpio_set_pud(unsigned int pin, unsigned int pud);

/*
 * Convenience functions for setting a pin to GPIO_PUD_PULLUP or
 * GPIO_PUD_PULLDOWN. The implementation calls `gpio_set_pud`.
 *
 * @param pin the GPIO pin number to set the pull-up/down state
 */
void gpio_set_pullup(unsigned int pin);
void gpio_set_pulldown(unsigned int pin);

#endif
