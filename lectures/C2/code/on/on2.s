// configure GPIO 20 for output
ldr r3, GPIO

mov r1, #1
mov r2, #(1<<20)

str r1, [r3, #0x08]
str r2, [r3, #0x1C] 

bx lr

GPIO: .int 0x20200000

