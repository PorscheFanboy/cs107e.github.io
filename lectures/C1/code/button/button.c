// The initial version of this program waits until a
// button is pressed (GPIO 10) and turns on GPIO 20, then
// waits until the button is released and turns off GPI0 20
// Later we will modify it to blink GPIO 20 in a loop.

#define DELAY 0x3F0000

#define FSEL2 (unsigned int *)0x20200008
#define SET0  (unsigned int *)0x2020001C
#define CLR0  (unsigned int *)0x20200028
#define LEV0  (unsigned int *)0x20200034

void main(void)
{
    // configure GPIO 20 as output
    *FSEL2 = 1;

    // wait until GPIO 10 is low (button press)
    while ((*LEV0 & (1 << 10)) != 0) ;

    // set GPIO 20 high
    *SET0 = 1 << 20;

    // wait until GPIO 10 is high (button release)
    while ((*LEV0 & (1 << 10)) == 0) ;

    // clear GPIO 20
    *CLR0 = 1 << 20;

/*    int delay;
    while (1) {

        // set GPIO 20 high
        *SET0 = 1 << 20;

        delay = DELAY;
        while (--delay != 0) ;

        // clear GPIO 20
        *CLR0 = 1 << 20;

        delay = DELAY;
        while (--delay != 0) ;
    }
    */
}
