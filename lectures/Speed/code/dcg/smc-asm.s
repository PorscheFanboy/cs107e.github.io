    mov	    r0, 	#0
    add	    r1, r15, #-12
    ldr     r2, [r1]
    add	    r2, r2, #1
    str     r2, [r1]
    bx lr
