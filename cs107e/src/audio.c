#include <stdint.h>

#include "timer.h"
#include "gpio.h"
#include "pwm.h"
#include "audio.h"

void audio_init(void) 
{
  // turn on GPIO pins 40 and 45 which are used for audio on the Pi
  gpio_set_function( 40, GPIO_FUNC_ALT0 );
  gpio_set_function( 45, GPIO_FUNC_ALT0 );
  timer_delay_ms(2);

  // Set the PWM clock to 9600000 Hz
  pwm_clock( 19200000/2 ); // 9600000 Hz
  timer_delay_ms(2);

  // Enable PWM, use SIGMADELTA mode, and use the FIFOs
  pwm_set_mode( 0, 1, PWM_SIGMADELTA, 1 ); 
  pwm_set_mode( 1, 1, PWM_SIGMADELTA, 1 );

  // pwm range is 256 cycles
  pwm_set_range( 0, 0x100 );
  pwm_set_range( 1, 0x100 );
  timer_delay_ms(2);
}

/* 
   This function transmits a sinusoid tone over the RPi audio jack 
   as a pulse-width-modulated signal.
   
   The waveform should have values in the range 0 to 255

   The waveform table should contain 256 entries.

   dphase is the increment from sample to sample. The upper 8 bits
   of the 32-bit unsigned select one of the 256 samples.

   Setting dphase=(1<<24) will output one sample per interval. 
   Setting dphase=(2<<24) will skip one sample per interval. 

   Running the pwm at 9600000 / 256 samples / 256 range = 146.484375 Hz
   
   This function does not return.
*/

void audio_write_u8(const uint8_t waveform[], unsigned dphase) 
{
  unsigned phase = 0;
  while(1) {
    unsigned status = pwm_get_status();
    if (!(status & PWM_FULL1)) {
      unsigned angle = phase >> 24;
      uint8_t pcm = waveform[angle];
      pwm_write( pcm ); // output to channel 0
      pwm_write( pcm ); // output to channel 1
      phase += dphase; 
    }
  }
}

void audio_write_u16(const uint16_t waveform[], unsigned dphase) 
{
  unsigned phase = 0;
  while(1) {
    unsigned status = pwm_get_status();
    if (!(status & PWM_FULL1)) {
      unsigned angle = phase >> 24;
      uint8_t pcm = waveform[angle] >> 8;
      pwm_write( pcm ); // output to channel 0
      pwm_write( pcm ); // output to channel 1
      phase += dphase; 
    }
  }
}

void audio_write_i16(const int16_t waveform[], unsigned dphase) 
{
  unsigned phase = 0;
  while(1) {
    unsigned status = pwm_get_status();
    if (!(status & PWM_FULL1)) {
      unsigned angle = phase >> 24;
      uint8_t pcm = (waveform[angle]-INT16_MIN)>>8;
      pwm_write( pcm ); // output to channel 0
      pwm_write( pcm ); // output to channel 1
      phase += dphase; 
    }
  }
}
