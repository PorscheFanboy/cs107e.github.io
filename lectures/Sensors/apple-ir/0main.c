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
	unsigned clk = GPIO_PIN2;
  	gpio_set_function(clk, GPIO_FUNC_INPUT);
  	gpio_set_pulldown(clk);

	for(int pushes = 0; pushes < 5; pushes++) {
		unsigned v = 1;
		unsigned time[40], val[40];
		for(int i = 0; i < 40; i++) {
			time[i] = timer_get_time();
			val[i] = v;
			while(gpio_read(clk) == v)
				;
			time[i] = timer_get_time() - time[i];
			v = 1 - v;
		}
		printf("--------------------------------------------\n");
		for(int i = 0; i < 40; i++)
			printf("time[%d] = time=%d, val=%d\n", i, time[i], val[i]);
		delay_ms(100);
	}
  	reboot();
}
