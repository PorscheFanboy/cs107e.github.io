.global _start

_start:

// configure GPIO 20 for output
ldr r0, =0x20200008
mov r1, #1
str r1, [r0]

mov r1, #(1<<20)

loop: 

// set GPIO 20 high
ldr r0, =0x2020001C
str r1, [r0] 

// delay
mov r2, #0x3F0000
wait1:
subs r2, #1
bne wait1

// set GPIO 20 low
ldr r0, =0x20200028
str r1, [r0] 

// delay
mov r2, #0x3F0000
wait2:
subs r2, #1
bne wait2

mov r0, #0xca000000
orr r0, #0x00110000
orr r0, #0x0000ab00
orr r0, #0x0000001e
bx lr
