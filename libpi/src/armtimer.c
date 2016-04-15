#include "memory.h"

#define ARM_TIMER_LOD 0x2000B400
#define ARM_TIMER_VAL 0x2000B404
#define ARM_TIMER_CTL 0x2000B408
#define ARM_TIMER_DIV 0x2000B41C
#define ARM_TIMER_CNT 0x2000B420

void armtimer_init(void) {
    PUT32(ARM_TIMER_CTL, 0x00000000);
    PUT32(ARM_TIMER_CTL, 0x00000200);
}

unsigned armtimer_get_time(void) {
    return (GET32(ARM_TIMER_CNT));
}
