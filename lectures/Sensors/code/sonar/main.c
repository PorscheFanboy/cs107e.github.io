/*
 * HC-SR04


   http://www.modmypi.com/blog/hc-sr04-ultrasonic-range-sensor-on-the-raspberry-pi
   IMPORTANT. The sensor output signal (ECHO) on the HC-SR04 is rated
   at 5V. However, the input pin on the Raspberry Pi GPIO is rated at
   3.3V. Sending a 5V signal into that unprotected 3.3V input port could
   damage your GPIO pins, which is something we want to avoid! We’ll
   need to use a small voltage divider circuit, consisting of two
   resistors, to lower the sensor output voltage to something our
   Raspberry Pi can handle.

   http://www.bytecreation.com/blog/2013/10/13/raspberry-pi-ultrasonic-sensor-hc-sr04
 */
#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"

const unsigned trigger = GPIO_PIN3;
const unsigned echo = GPIO_PIN2;

unsigned get_distance(void) {
	// write hi for 10usec
	gpio_write(trigger, 1);
	delay_us(10);
	gpio_write(trigger, 0);

	unsigned start = timer_get_time();
	delay_us(149); // wait til device settles: 148 = time to go one inch
	while(!gpio_read(echo))
		;

	unsigned end;
	while(gpio_read(echo) == 1)
		;
	end = timer_get_time();

	// ((340M/S / 2) * 39.37inch / meter) / 10^6 = inch/usec
	return (end - start) / 149;
}

void main(void) {
	printf_init();

  	gpio_set_output(trigger);
  	gpio_set_input(echo);
  	gpio_set_pulldown(echo);
	delay_ms(40);

  	while(1) {
		unsigned distance = get_distance();
		printf("distance = %d inches\n", distance);
		delay_ms(1000);
	}
}
