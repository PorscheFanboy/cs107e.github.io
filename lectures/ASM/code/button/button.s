.globl start
start:

#define FSEL2 0x20200008
#define SET0  0x2020001C
#define CLR0  0x20200028
#define LEV0  0x20200034

// GPIO 10 is configured to INPUT by default

// configure GPIO 20 for OUTPUT
ldr r0, =FSEL2 
mov r1, #1
str r1, [r0]

// set bit 10
mov r2, #(1<<10)

// set bit 20
mov r3, #(1<<20)

loop: 

    // read GPIO 10 
    ldr r0, =LEV0
    ldr r1, [r0] 
    tst r1, r2 // turn LED on when button is pressed (goes LOW)
    bne off

// set GPIO 20 high
on:
    ldr r0, =SET0
    str r3, [r0] 
    b loop

// set GPIO 20 low
off:
    ldr r0, =CLR0
    str r3, [r0] 
    b loop


