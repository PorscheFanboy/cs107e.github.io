#define DELAY 0x3F0000

#define FSEL2 0x20200008
#define SET0  0x2020001C
#define CLR0  0x20200028

void main()
{
    // configure GPIO 20 as output
    *(volatile int *)FSEL2 = 1;

    while(1) {
    	// set GPIO 20 high
        *(volatile int *)SET0 = 1 << 20;

    	volatile int delay = DELAY;
    	while (--delay != 0) ;

   		// clear GPIO 20
    	*(volatile int *)CLR0 = 1 << 20;

    	delay = DELAY;
    	while (--delay != 0) ;
	}
}
