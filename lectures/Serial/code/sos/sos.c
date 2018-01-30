#include "gpio.h"
#include "timer.h"

const int pin = 20;

#define ONE_SECOND 1000
#define DELAY_MS (ONE_SECOND/6)


void main(void)
{
	gpio_init();
	gpio_set_output(pin);
	
	while (1) {
		gpio_write(pin, 1);
		timer_delay_ms(DELAY_MS);
		gpio_write(pin, 0);
		timer_delay_ms(DELAY_MS);
	}
}
