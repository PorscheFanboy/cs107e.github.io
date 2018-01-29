#ifndef GPIOEVENT_H
#define GPIOEVENT_H

/*
 * Functions for controlling event detection for Raspberry Pi GPIO.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 *         Philip Levis <pal@cs.stanford.edu>
 *         Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Last edited: Jan 2018
 */

#include "gpio.h"



/*
 * Sets detection of falling edge events for GPIO pin number `pin` 
 * to `state`.
 *
 * @param pin      the GPIO pin number to set detection for
 * @param state    if 0 disables detection, otherwise enables
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_detect_falling_edge(unsigned int pin, unsigned int state);

/*
 * Sets detection of rising edge events for GPIO pin number `pin` 
 * to `state`. 
 *
 * @param pin      the GPIO pin number to set detection for
 * @param state    if 0 disables detection, otherwise enables
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_detect_rising_edge(unsigned int pin, unsigned int state);

/*
 * Sets detection of high level for GPIO pin number `pin` 
 * to `state`.
 *
 * @param pin      the GPIO pin number to set detection for
 * @param state    if 0 disables detection, otherwise enables
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_detect_high_level(unsigned int pin, unsigned int state);

/*
 * Sets detection of low level for GPIO pin number `pin` 
 * to `state`.
 *
 * @param pin      the GPIO pin number to set detection for
 * @param state    if 0 disables detection, otherwise enables
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_detect_low_level(unsigned int pin, unsigned int state);

/*
 * Sets detection of asynchronous falling edge events for GPIO pin 
 * number `pin` to `state`.
 *
 * @param pin      the GPIO pin number to set detection for
 * @param state    if 0 disables detection, otherwise enables
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_detect_async_falling_edge(unsigned int pin, unsigned int state);

/*
 * Sets detection of asynchronous rising edge events for GPIO pin 
 * number `pin` to `state`.
 *
 * @param pin      the GPIO pin number to set detection for
 * @param state    if 0 disables detection, otherwise enables
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_detect_async_rising_edge(unsigned int pin, unsigned int state);

/*
 * Disables detection of all event types for GPIO pin number `pin`. 
 *
 * @param pin      the GPIO pin number to disable detection for
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_disable_event_detection(unsigned int pin);

/*
 * Returns event status for GPIO pin number `pin`. 
 * The event status is 1 if an event has been detected for this pin 
 * and the event has not been cleared, status is 0 otherwise.
 *
 * @param pin      the GPIO pin number to return event status
 * @return         the event status of the specified pin
 *
 * If `pin` is invalid, returns GPIO_INVALID_REQUEST.
 */
unsigned int gpio_check_event(unsigned int pin);

/*
 * Clears the event status for GPIO pin number `pin`. Note that if
 * the event was high or low level detect and the level is still 
 * high/low, the clear operation has no effect.
 *
 * @param pin      the GPIO pin number to clear event status
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_clear_event(unsigned int pin);

/*
 * Returns event status for GPIO pin number `pin` and clears 
 * event status.
 *
 * @param pin      the GPIO pin number to check and clear event status
 * @return         the event status of the specified pin before clearing
 *
 * If `pin` is invalid, does nothing and returns GPIO_INVALID_REQUEST.
 */
unsigned int gpio_check_and_clear_event(unsigned int pin);

#endif
