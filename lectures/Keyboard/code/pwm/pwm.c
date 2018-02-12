#include "gpio.h"
#include "pwm.h"

void main ( void )
{
    gpio_init();
    gpio_set_function( 40, GPIO_FUNC_ALT0 ); // Stereo left
    gpio_set_function( 45, GPIO_FUNC_ALT0 ); // Stereo right

    pwm_init();
    pwm_clock( 200000 ); // set clock to 200000 Hz

    // channel=0, enable=1, format=MARKSPACE, usefifo=0
    pwm_set_mode( 0, 1, PWM_MARKSPACE, 0 );

    pwm_set_range( 0, 200 ); // 200000 / 200 = 1Khz
    pwm_set_width( 0, 40 );  // 25% duty cycle
}

