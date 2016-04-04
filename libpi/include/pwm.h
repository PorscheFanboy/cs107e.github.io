#ifndef PWM_H
#define PWM_H


/*
 * Hardware abstractions for pulse width modulation (PWM) of
 * digital signals.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date: Feb 15, 2016
 */

extern void pwm_clock(int frequency);

#define PWM_SIGMADELTA 0
#define PWM_MARKSPACE  1
extern void pwm_set_mode(int chan, int enable, int markspace, int usefifo);

extern void pwm_set_range(int chan, int range);
extern void pwm_set_width(int chan, int width);
extern int pwm_set_status(void);
extern void pwm_write(int value);

#endif
