#include "memory.h"
#include "timer.h"
#include "gpio.h"
#include "pwm.h"


// Nominal clock frequencies
#define F_OSC   19200000
#define F_PLLD 500000000

#define BM_PASSWORD 0x5A000000

#define CM_PWMCTL 0x201010A0
#define CM_PWMDIV 0x201010A4

#define CM_ENABLE  (1 << 4)
#define CM_FLIP    (1 << 6)
#define CM_BUSY    (1 << 7)
#define CM_MASH0   (0 << 9)
#define CM_MASH1   (1 << 9)
#define CM_MASH2   (2 << 9)
#define CM_MASH3   (3 << 9)

#define PWM_CTL    0x2020C000
#define PWM_STATUS 0x2020C004
#define PWM_DMAC   0x2020C008
#define PWM_FIFO   0x2020C018

#define PWM0_RANGE 0x2020C010
#define PWM0_DATA  0x2020C014

#define PWM1_RANGE 0x2020C020
#define PWM1_DATA  0x2020C024

#define PWM0_ENABLE      0x0001
#define PWM0_SERIAL      0x0002
#define PWM0_REPEATFF    0x0004
#define PWM0_OFFSTATE    0x0008
#define PWM0_REVPOLARITY 0x0010
#define PWM0_USEFIFO     0x0020
#define PWM0_MARKSPACE   0x0080

#define PWM1_ENABLE      0x0100
#define PWM1_SERIAL      0x0200
#define PWM1_REPEATFF    0x0400
#define PWM1_OFFSTATE    0x0800
#define PWM1_REVPOLARITY 0x1000
#define PWM1_USEFIFO     0x2000
#define PWM1_MARKSPACE   0x8000

void pwm_init(void) {
}

void pwm_clock(int freq) {
    int timer = F_OSC;
    int source;

    if (timer == F_OSC) { // 19 200 000 = 2^11 x 3 * 5^5
        source = 1;
    } else if (timer == F_PLLD) {
        source = 6;
    } else {
        source = 1;
        timer = F_OSC;
    }

    int divisor  = timer / freq;
    int fraction = (timer % freq) * 4096 / freq;

    if (divisor < 2) {
        divisor = 2;
    }
    if (divisor > 4095) {
        divisor = 4095;
    }

    if (fraction > 4095) {
        fraction = 4095;
    }

    // turn off pwm before changing the clock
    volatile int* reg_pwm = (volatile int*)PWM_CTL;
    volatile int* reg_cm_pwmctl = (volatile int*)CM_PWMCTL;
    volatile int* reg_cm_pwmdiv = (volatile int*)CM_PWMDIV;
    int pwm = *reg_pwm;
    *reg_pwm = 0;

    *reg_cm_pwmctl = BM_PASSWORD;          // turn off clock
    while (*reg_cm_pwmctl & CM_BUSY) ;     // Wait for clock to stop

    *reg_cm_pwmdiv = BM_PASSWORD | (divisor << 12) | fraction;

    int mash = fraction ? CM_MASH1 : CM_MASH0;

    *reg_cm_pwmctl = BM_PASSWORD | CM_ENABLE | mash | source;
    *reg_pwm = pwm;
}


void pwm_set_mode(int chan, int enable, int markspace, int usefifo) {
    volatile int* reg_pwm = (volatile int*)PWM_CTL;
    int ra = *reg_pwm;

    if (chan == 0) {
        if (enable) {
            ra |=  PWM0_ENABLE;
        } else {
            ra &= ~PWM0_ENABLE;
        }

        if (markspace) {
            ra |=  PWM0_MARKSPACE;
        } else {
            ra &= ~PWM0_MARKSPACE;
        }

        if (usefifo) {
            ra |=  PWM0_USEFIFO;
        } else {
            ra &= ~PWM0_USEFIFO;
        }
    }

    if (chan == 1) {
        if (enable) {
            ra |=  PWM1_ENABLE;
        } else {
            ra &= ~PWM1_ENABLE;
        }

        if (markspace) {
            ra |=  PWM1_MARKSPACE;
        } else {
            ra &= ~PWM1_MARKSPACE;
        }

        if (usefifo) {
            ra |=  PWM1_USEFIFO;
        } else {
            ra &= ~PWM1_USEFIFO;
        }
    }

    *reg_pwm = ra;
}

void pwm_set_range(int chan, int range) {
    volatile int* reg_pwm0_range = (volatile int*)PWM0_RANGE;
    volatile int* reg_pwm1_range = (volatile int*)PWM1_RANGE;
    if (chan == 0) {
        *reg_pwm0_range = range;
    }
    if (chan == 1) {
        *reg_pwm1_range = range;
    }
}

void pwm_set_width(int chan, int width) {
    volatile int* reg_pwm0_data = (volatile int*)PWM0_DATA;
    volatile int* reg_pwm1_data = (volatile int*)PWM1_DATA;
    if (chan == 0) {
	*reg_pwm0_data = width;
    }
    if (chan == 1) {
	*reg_pwm1_data = width;
    }
}

int pwm_get_status(void) {
    volatile int* reg_pwm_status = (volatile int*)PWM_STATUS;
    return *reg_pwm_status;
}

void pwm_write(int value) {
    volatile int* reg_pwm_fifo = (volatile int*)PWM_FIFO;
    *reg_pwm_fifo = value;
}
