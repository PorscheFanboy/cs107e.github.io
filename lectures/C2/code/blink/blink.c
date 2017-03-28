#include "gpio.h"
#include "timer.h"

const int pin = GPIO_PIN20; 

void main(void)
{
    gpio_init();
    timer_init();

    gpio_set_function(pin, GPIO_FUNC_OUTPUT);
    while (1) {
        gpio_write(pin, 1);
        delay(1); // 1s
        gpio_write(pin, 0);
        delay(1);
    }
}

