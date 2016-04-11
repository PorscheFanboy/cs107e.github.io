#ifndef REGISTER_H
#define REGISTER_H


/*
 * Hardware abstractions for the ARM processor state registers
 * (CPSR and SPSR).
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date; Mar 20, 2016
 */

void SETCPSR(unsigned cpsr);
unsigned GETCPSR(void);

void SETSPSR(unsigned spsr);
unsigned GETSPSR(void);

void system_enable_interrupts(void);
void system_disable_interrupts(void);

#endif
