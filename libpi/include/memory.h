#ifndef MEMORY_H
#define MEMORY_H

/*
 * Macros for explicit memory reads and writes.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 *         
 * Date: Jan 24, 2016
 */
extern unsigned GET32(unsigned addr);
extern void PUT32(unsigned addr, unsigned word);

extern unsigned GET16(unsigned addr);
extern void PUT16(unsigned addr, unsigned word);

extern unsigned GET8(unsigned addr);
extern void PUT8(unsigned addr, unsigned word);

#endif
