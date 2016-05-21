/*
 * The output of these devices (pin 3) switches low when the magnetic
 * field at the Hall element exceeds the operate point threshold (BOP). At
 * this point, the output voltage is VOUT(SAT). When the magnetic field
 * is reduced to below the release point threshold (BRP), the device
 * output goes high. The difference in the magnetic operate and release
 * points is called the hysteresis (Bhys) of the device. This built-in
 * hysteresis allows clean switching of the output even in the presence
 * of external mechanical vibration and electrical noise.
 */
#include "uart.h"
#include "timer.h"
#include "printf.h"
#include "reboot.h"

#include "gpio.h"
#include "gpioextra.h"

void main(void) {
	uart_init();
	const unsigned vout= GPIO_PIN2;

	// XXX how to setup pin?
	gpio_set_function(vout, GPIO_FUNC_INPUT);
	// gpio_set_pulldown(vout);

	for(int i = 0; i < 10; i++) {
		// XXX: how to tell when magnet close or far?
		while(gpio_read(vout) == 1) { }
		printf("magnet close\n");
		while(gpio_read(vout) == 0) { }
		printf("magnet far\n");
	}

  	reboot();
}
