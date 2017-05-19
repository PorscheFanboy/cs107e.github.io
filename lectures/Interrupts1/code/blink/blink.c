#include "printf.h"
#include "register.h"
#include "interrupts.h"
#include "reboot.h"
#include "armtimer.h"
#include "gpio.h"
#include "uart.h"
#include "pi.h"

// should not get called.
void impossible_handler(unsigned pc) {
	printf("impossible exception at pc=0x%x\n", pc);
	reboot();
}

volatile int counter = 0;

/* 
 * we have only enabled timer interrupts
 */
void interrupt_handler(unsigned pc) {
#if 0
        printf("pc = %x\n", pc);
        printf("cpsr=%b\n", GETCPSR());
        printf("spsr=%b\n", GETSPSR());
#endif
    armtimer_clear_interrupt();
    counter++;
}

void main(void) {
  int lit = 0;
  
  gpio_init();
  gpio_set_output(ACT);
  printf_init();
  
  armtimer_init(2000000); // 1s
  armtimer_set_prescalar(125);
  armtimer_enable();
  
  armtimer_enable_interrupt();
  interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ); 
  system_enable_interrupts(); 
  
  printf("cpsr=0x%x\n", GETCPSR());
  int last = 0;
  while(1) {
    if(last != counter) {
      last = counter;
      gpio_write( ACT, lit );
      lit = !lit;
      printf("received %d interrupts\n", last);
    }
  }
  reboot();
}
