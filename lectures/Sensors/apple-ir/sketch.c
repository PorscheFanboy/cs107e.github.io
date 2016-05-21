/*
 * tsop 34838 IR sensor.
 *
 * simple program to pull off the timings after a button press.
 *
 */
#include "uart.h"
#include "timer.h"
#include "printf.h"
#include "reboot.h"

#include "gpio.h"
#include "gpioextra.h"

void main(void) {
	uart_init();
	unsigned input = GPIO_PIN2;

	// how to set?
	/* ... */

	for(int pushes = 0; pushes < 5; pushes++) {
		unsigned v = 1;
		unsigned time[32], val[32];

		// record the times each 0,1 is signaled.
		for(int i = 0; i < 32; i++) {
			/* .... */
		}
		printf("--------------------------------------------\n");
		for(int i = 0; i < 32; i++)
			printf("time[%d] = time=%d, val=%d\n", i, time[i], val[i]);
		delay_ms(100);
	}
  	reboot();
}
