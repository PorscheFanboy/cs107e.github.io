// C program that turns on GPIO 20

void main(void)
{
        // configure GPIO 20 as output
    *(unsigned int *)0x20200008 = 1;

        // set GPIO 20 high
    *(unsigned int *)0x2020001C = 1 << 20;
}
