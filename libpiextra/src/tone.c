#include "pwm.h"
#include "tone.h"

/*
 * this version is fragile. because divisor is 12-bits
 * we need to change the pwm clock depending on the input
 * frequency. but the current version of pwm clock doesn't
 * work properly. it can only ba called once.
 */
void tone(int freq) {
    if (freq == 0) {
        pwm_set_mode(0, 0, 1, 0);
        pwm_set_mode(1, 0, 1, 0);
        return;
    }
    pwm_set_mode(0, 1, 1, 0);
    pwm_set_mode(1, 1, 1, 0);

    int divisor = F_AUDIO / freq;
    int divisor2 = divisor / 2;

    pwm_set_range(0,  divisor);
    pwm_set_width(0,  divisor2);

    pwm_set_range(1,  divisor);
    pwm_set_width(1,  divisor2);

}
