#include "gpio.h"
#include "pwm.h"
#include "tone.h"
#include "pitch.h"

void main ( void )
{
    gpio_init();
    gpio_set_function( 40, GPIO_FUNC_ALT0 ); // PWM0
    gpio_set_function( 45, GPIO_FUNC_ALT0 ); // PWM1

    pwm_init();
    pwm_clock( F_AUDIO );

    tone( NOTE_A4 );
}
