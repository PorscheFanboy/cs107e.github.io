/*
 */
#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "uart.h"
#include "printf.h"
#include "assert.h"

const unsigned signal = GPIO_PIN2;
const unsigned discharge = GPIO_PIN3;

unsigned get_time(void) {

    // discharge the capacitor
    gpio_write(discharge, 1);
    delay_ms(1);
    gpio_write(discharge, 0);

    // time how long it takes for the capacitor to charge.
	unsigned start = timer_get_time();
	while(!gpio_read(signal))
		;
	unsigned end = timer_get_time();

	return (end - start);
}

void main(void) {
    gpio_init();
	uart_init();

    gpio_set_output(discharge);
    gpio_set_input(signal);
    gpio_set_pud(signal, GPIO_PUD_DISABLE);

  	while(1) {
		unsigned time = get_time();
		printf("time = %d\n", time);
	}
}
