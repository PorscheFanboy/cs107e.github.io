#include "armtimer.h"
#include "gpio.h"
#include "interrupts.h"
#include "pi.h"
#include "uart.h"
#include "printf.h"

// should not get called.
void impossible_handler(unsigned pc) 
{
	printf("impossible exception at pc=%x\n", pc);
	pi_reboot();
}

volatile int counter = 0;

/* 
 * we have only enabled timer interrupts
 */
void interrupt_handler(unsigned pc) 
{
    armtimer_clear_interrupt();
    counter++;
}

void main(void) 
{
    gpio_init();
    gpio_set_output(PI_ACT_LED);

	uart_init();
    printf("Executing program '%s'\n", __FILE__);

    // number of usecs between interrupts
	armtimer_init(1000000); // 1s
    armtimer_enable();      // enable timer

    armtimer_enable_interrupt();
    interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ); 
    system_enable_interrupts(); 

	int last = 0;
	while(1) {
		if (last != counter) {
			last = counter;
            pi_led_toggle(PI_ACT_LED);
			printf("received %d interrupts\n", last);
		}
	}

	pi_reboot();
}
