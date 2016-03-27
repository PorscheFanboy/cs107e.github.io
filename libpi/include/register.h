#ifndef REGISTER_H
#define REGISTER_H

extern void SETCPSR(unsigned cpsr);
extern unsigned GETCPSR(void);

extern void SETSPSR(unsigned spsr);
extern unsigned GETSPSR(void);

extern void system_enable_interrupts(void);
extern void system_disable_interrupts(void);

#endif
