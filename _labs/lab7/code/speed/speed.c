/* File main.c
 * -----------
 * Simple main program with timing code to measure
 * performance of different implementations of strcpy.
 */

#include "printf.h"
#include "memory.h"
#include "timer.h"
#include "assert.h"
#include "reboot.h"

// string of this length will be copied during time trial
#define COPYLEN (1 << 12)

unsigned strlen(const char *str)
{
    const char *cur = str;
    while (*cur) cur++;
    return cur - str;
}

int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}


char *strcpy1(char *dst, const char *src)
{
    for (int i = 0; i <= strlen(src); i++) {
        dst[i] = src[i];
    }
    return dst;
}


unsigned tickcount(void)
{
    return timer_get_time();
}

unsigned _time_trial(char *(*cpy)(char *dst, const char *src))
{
    char src[COPYLEN], dst[COPYLEN];

    // initialize source string
    for (int i = 0; i < COPYLEN-1; i++) src[i] = 'X';  
    src[COPYLEN-1] = '\0';

    // fill dest string with garbage
    for (int i = 0; i < COPYLEN; i++) dst[i] = (char) i + 1;

    unsigned start = tickcount();
    cpy(dst, src);
    unsigned ticks = tickcount() - start;

    assert(strcmp(src, dst) == 0);
    return ticks;
}

#define TIME_TRIAL(fn) do {           \
    printf("Running " #fn "... ");    \
    printf("took %d ticks\n", _time_trial(fn)); \
} while (0)

int main()
{
    timer_init();
    printf_init();
    delay(3);   // wait for uart/screen to catch up
    printf("Ready to start time trials!\n");

    TIME_TRIAL(strcpy1);
    // TODO: Add more TIME_TRIAL calls here for your sped-up
    // versions: TIME_TRIAL(strcpy2), TIME_TRIAL(strcpy3), etc.

    printf("Done. Rebooting.\n");
    reboot();

    return 0;
}
