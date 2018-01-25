#ifndef TIMER_H
#define TIMER_H

/*
 * Hardware abstractions for a Raspberry Pi timer.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 *         Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date: Jan 24, 2016
 * Edited by Mark Miller, Anna Zeng, Jan 21, 2018
 */

/*
 * Initialize the timer. Does not do anything in assignment 2.
 * However, all libpi peripheral modules require an init, so it is included
 * for consistency's sake.
 */
void timer_init(void);

/*
 * Returns the current system time in microseconds. This is set to zero 
 * at startup and increases through the duration of program execution.
 *
 * @return system time in microseconds
 */
unsigned int timer_get_time(void);

/*
 * A simple busy loop that delays the program for `usec` microseconds.
 *
 * @param usec the number of microseconds to busy loop for
 */
void delay_us(unsigned int usec);

/*
 * Busy loop delay for `msec` milliseconds.
 *
 * @param msec the number of milliseconds to busy loop for
 */
void delay_ms(unsigned int msec);

/*
 * Busy loop delay for `sec` seconds.
 *
 * @param sec the number of seconds to busy loop for
 */
void delay(unsigned int sec);

/*
 * Immediate busy loop delay until system time is equal to `end_time` microseconds.
 *
 * @param end_time the system time in microseconds at which the delay will end
 */
void until_us(unsigned int end_time);

#endif
