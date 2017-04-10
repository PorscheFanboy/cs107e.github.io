#define FSEL0 0x20200000
#define FSEL1 0x20200004
#define FSEL2 0x20200008
#define SET0  0x2020001C
#define SET1  0x20200020
#define CLR0  0x20200028
#define CLR1  0x2020002C

// configure GPIO 20 for output
ldr r0, =FSEL2 
mov r1, #(1<<0)
str r1, [r0]

// set GPIO 20 high
ldr r0, =SET0
mov r1, #(1<<20) 
str r1, [r0] 

loop: b loop

