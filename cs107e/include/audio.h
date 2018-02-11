#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

void audio_init(void);

/*
   These functions transmits a waveform over the Raspberry Pi audio jack
   as a pulse-width-modulated signal.
  
   The waveform table should contain 256 entries.

   dphase is the increment from sample to sample. The upper 8 bits
   of the 32-bit unsigned select one of the 256 samples.

   Setting dphase=(1<<24) will output one sample per interval.
   Setting dphase=(2<<24) will skip one sample per interval.

   Running the pwm at 9600000 / 256 samples / 256 range = 146.484375 Hz

   This function does not return.
*/

/*
 * Waveform table is 256 uint8 values.
 */
void audio_write_u8 (const uint8_t  waveform[], unsigned dphase);

/*
 * Waveform table is 256 uint16 values.
 */
void audio_write_u16(const uint16_t waveform[], unsigned dphase);

/*
 * Waveform table is 256 int16 values.
 */
void audio_write_i16(const  int16_t waveform[], unsigned dphase);

#endif
