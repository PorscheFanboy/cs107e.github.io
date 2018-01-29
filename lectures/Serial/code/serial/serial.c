#include "gpio.h"
#include "timer.h"

const int pin = 20;

#define ONE_SECOND 1000000
#define BAUD 9600
#define DELAY_US (1000000/BAUD)


void main(void)
{
    gpio_init();
    gpio_set_output(pin);

    int val = 0;
    while (1) {
        gpio_write(pin, val);
        delay_us(DELAY_US);
        val = !val;
    }
}
