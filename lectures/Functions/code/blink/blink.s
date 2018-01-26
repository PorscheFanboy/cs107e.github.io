
// configure GPIO 20 for output
ldr r0, = 0x20200008
mov r1, #(1<<0)
str r1, [r0]

mov r1, #(1<<20)

loop: 

	ldr r0, =0x2020001C   // set pin
	str r1, [r0] 

	mov r2, #0x3F0000    // delay loop
	wait1:				
		subs r2, #1
		bne wait1

	ldr r0, =0x20200028	 // clear pin
	str r1, [r0] 

	mov r2, #0x3F0000    // delay loop
	wait2:
		subs r2, #1
		bne wait2

b loop
