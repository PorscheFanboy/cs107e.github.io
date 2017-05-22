#include "console.h"
#include "interrupts.h"
#include "armtimer.h"
#include "timer.h"
#include "malloc.h"
#include "printf.h"

static volatile unsigned int n_timer_interrupts = 0;
static volatile unsigned int a = 0;
static volatile unsigned int b = 0;

void impossible_handler(int pc) {
  // Should never be called
  printf("ERROR: impossible handler called at 0x%x\n", (unsigned)pc);
}

void interrupt_handler(int pc) {
    armtimer_clear_interrupt();
    n_timer_interrupts++;
    a++;
    b++;
    if (a != b) {
        printf("VIOLATION (%06d): a=%d,b=%d\n", n_timer_interrupts, a, b);
        delay(3);
    }
}

void main() {
    printf_init();
   // malloc_init(0x4000000);
  //  console_init(20, 40);
    armtimer_init(2000);
    armtimer_set_prescalar(125);
    armtimer_enable();
    armtimer_enable_interrupt();
    timer_init();
    interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ);
    system_enable_interrupts();

    while (1) {
        a++;
        b++;
    }
}
