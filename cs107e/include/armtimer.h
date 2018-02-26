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

void armtimer_init(unsigned int ticks);

void armtimer_enable(void);
void armtimer_disable(void);

void armtimer_enable_interrupts(void);
void armtimer_disable_interrupts(void);

unsigned int armtimer_check_overflow(void);
unsigned int armtimer_check_interrupt(void);
void armtimer_clear_interrupt(void);
unsigned int armtimer_check_and_clear_interrupt(void);

#endif
