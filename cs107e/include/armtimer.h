#ifndef ARMTIMER_H
#define ARMTIMER_H

/*
 * Functions for Raspberry Pi ARM Timer.
 * 
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 *         Dawson Engler <engler@cs.stanford.edu>
 *    
 * Date: April 20, 2016
 */ 

void armtimer_init(unsigned ticks);

void armtimer_set_prescalar(unsigned divisor);

void armtimer_set_load(unsigned ticks);
void armtimer_set_reload(unsigned ticks);

unsigned armtimer_get_time(void);

void armtimer_enable(void);
void armtimer_disable(void);

unsigned armtimer_check_overflow(void);

void armtimer_enable_interrupt(void);
void armtimer_disable_interrupt(void);
unsigned armtimer_check_interrupt(void);
void armtimer_clear_interrupt(void);

#endif
