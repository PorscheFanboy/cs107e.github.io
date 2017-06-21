/*
 * Reference full implementation of C start sequence for CS107E. This
 * function is called from start.s. _cstart() zeroes out the BSS
 * (assignment 4) and installs interrupt vectors (assignment 7). It
 * also calls malloc_init(), but also defines a weak symbol so if the
 * program does not use malloc then this call does nothing. If main()
 * returns, it turns on the green ACT LED on the Raspberry Pi board.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Date: 6/20/17
 */

#define GPIO_FSEL4  ((unsigned int *)0x20200010)
#define GPIO_SET1   ((unsigned int *)0x20200020)
#define GPIO_CLR1   ((unsigned int *)0x2020002c)

// Green ACT LED is GPIO 47.
#define SUCCESS_OUTPUT (1 << (3*7))
#define SUCCESS_BIT    (1 << (47-32))

extern int __bss_start__;
extern int __bss_end__;

#define RPI_INTERRUPT_VECTOR_BASE 0x0
extern int _vectors;
extern int _vectors_end;

extern void main();
extern void malloc_init(unsigned);


// Zeroes out the BSS and installs the interrupt handler
// table before calling main.
// Turns on the green ACT LED when done, to show successful completion.
// This function is called from start.s.
void _cstart() {
    int *bss = &__bss_start__;
    int *bss_end = &__bss_end__;

    while (bss < bss_end) {
        *bss++ = 0;
    }

    /* Copy in interrupt vector table and FIQ handler at end of table. */
    /* _vector and _vector_end are symbols defined in the interrupt
     assembly file, at the beginning and end of the vector and
     its embedded constants.*/
    int* vectorsdst = (int*)RPI_INTERRUPT_VECTOR_BASE;
    int* vectors = &_vectors;
    int* vectors_end = &_vectors_end;
    while (vectors < vectors_end) {
        *vectorsdst++ = *vectors++;
    }

    malloc_init(0x4000000);
    main();

    // Turn the green ACT LED (GPIO 47).
    *GPIO_FSEL4 = SUCCESS_OUTPUT;
    *GPIO_SET1 = SUCCESS_BIT;
}

void __attribute__ ((weak)) malloc_init(unsigned size) {}

/* Copyright (c) 2017 Stanford University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the Stanford University nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL STANFORD
 * UNIVERSITY OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
