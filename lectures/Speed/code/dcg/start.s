.globl _start
_start:
    mov sp, #0x8000
    bl main
    b reboot


.globl inc
inc:
    mov	    r0,	#13 // first value.
    add	    r1, r15, #-12
    ldr     r2, [r1]
    add	    r2, r2, #1
    str     r2, [r1]
    bx lr

