#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdbool.h>

/*
 * Module to configure interrupts for Raspberry Pi.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Date:   Februrary 2018
 */


/*
 * `interrupts_global_enable`
 *
 * Turns on all enabled interrupts system-wide. 
 * Typical use is to configure all interrupt handlers while
 * global interrupts are not yet enabled, then call this function
 * to turn on interrupts when ready.
 */
void interrupts_global_enable(void);

/*
 * `interrupts_global_disable`
 *
 * Turns off all interrupts system-wide.
 */
void interrupts_global_disable(void);


void interrupts_enable_basic(unsigned int n);
void interrupts_enable_source(unsigned int n);
void interrupts_disable_basic(unsigned int n);
void interrupts_disable_source(unsigned int n);

/* 
 * `interrupts_attach_handler`
 *
 * Attach a handler function to be called when an interrupt is generated.
 * Multiple handlers can be attached. It is the responsibility of each 
 * handler function to check whether this particular interrupt is intended 
 * for this handler and if so, the handler should process and clear 
 * the interrupt.
 *
 * Returns true if successfully attached handler, false otherwise. The
 * handler will not be attached if the interrupt vectors were not
 * configured by cstart.c
 */
bool interrupts_attach_handler(void (*handler)(unsigned int pc));



enum interrupt_source {
   INTERRUPTS_AUX             = 29,
   INTERRUPTS_I2CSPISLV       = 43,
   INTERRUPTS_PWA0            = 45,
   INTERRUPTS_PWA1            = 46,
   INTERRUPTS_CPR             = 47,
   INTERRUPTS_SMI             = 48,
   INTERRUPTS_GPIO0           = 49,
   INTERRUPTS_GPIO1           = 50,
   INTERRUPTS_GPIO2           = 51,
   INTERRUPTS_GPIO3           = 52,
   INTERRUPTS_VC_I2C          = 53,
   INTERRUPTS_VC_SPI          = 54,
   INTERRUPTS_VC_I2SPCM       = 55,
   INTERRUPTS_VC_UART         = 57,
};
/* Interrupt sources below taken from table in BCM2835 Sec 7.5
 * I quote: "The table above has many empty entries.
 * These should not be enabled as they will interfere with the GPU operation."
 */

enum interrupt_basic {
    INTERRUPTS_BASIC_ARM_TIMER_IRQ        = 0,
    INTERRUPTS_BASIC_ARM_MAILBOX_IRQ      = 1,
    INTERRUPTS_BASIC_ARM_DOORBELL_0_IRQ   = 2,
    INTERRUPTS_BASIC_ARM_DOORBELL_1_IRQ   = 3,
    INTERRUPTS_BASIC_GPU_0_HALTED_IRQ     = 4,
    INTERRUPTS_BASIC_GPU_1_HALTED_IRQ     = 5,
    INTERRUPTS_BASIC_ACCESS_ERROR_1_IRQ   = 6,
    INTERRUPTS_BASIC_ACCESS_ERROR_0_IRQ   = 7,
};

void interrupt_vector(unsigned int pc);
void reset_vector(unsigned int pc);
void undefined_instruction_vector(unsigned int pc);
void software_interrupt_vector(unsigned int pc);
void prefetch_abort_vector(unsigned int pc);
void data_abort_vector(unsigned int pc);
void fast_interrupt_vector(unsigned int pc);

#endif
