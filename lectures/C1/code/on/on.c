#define FSEL2 0x20200008
#define SET0  0x2020001C

main()
{
    int *r0;
    int r1;

    // configure GPIO 20 for OUTPUT
    r0 = (int*)FSEL2;
    r1 = 1;
    *r0 = r1;

    // set GPIO 20 to 3.3V
    r0 = (int*)SET0;
    r1 = 1 << 20;
    *r0 = r1;

loop: goto loop;
}
