#include "uart.h"
#include "timer.h"
#include "printf.h"
#include "reboot.h"

#include "gpio.h"
#include "gpioextra.h"

const unsigned trigger = GPIO_PIN2;
const unsigned echo = GPIO_PIN3;

unsigned get_distance(void) {

	/* XXX: how to trigger device and listen for signal? */
	/* ... */
	gpio_write(trigger, 1);
	delay_us(10);
	gpio_write(trigger, 0);

	unsigned start = timer_get_time();
	delay_us(149);
	while(gpio_read(echo) == 0);
	while(gpio_read(echo) == 1);

	unsigned end = timer_get_time();

	// ((340M/S / 2) * 39.37inch / meter) / 10^6 = inch/usec
	return (end - start) / 149;
}

void main(void) {
	uart_init();
	// XXX: setup trigger, echo?
	gpio_set_function(trigger, GPIO_FUNC_OUTPUT);
	gpio_set_function(echo, GPIO_FUNC_INPUT);

	// wait til device settles.
	delay_ms(40);
  	for(int i = 0;  i < 100; i++) {
		unsigned distance = get_distance();
		printf("distance = %d inches\n", distance);
		delay_ms(1000);
	}
  	reboot();
}
