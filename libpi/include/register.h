#ifndef REGISTER_H
#define REGISTER_H


/*
 * Hardware abstractions for the ARM processor state registers
 * (CPSR and SPSR).
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date; Mar 20, 2016
 */

extern void SETCPSR(unsigned cpsr);
extern unsigned GETCPSR(void);

extern void SETSPSR(unsigned spsr);
extern unsigned GETSPSR(void);

extern void system_enable_interrupts(void);
extern void system_disable_interrupts(void);

#endif
