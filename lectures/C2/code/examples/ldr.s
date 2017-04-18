 # are all of these mov's valid?
 # what if we changed them to ldr=?

    mov r0, #0x7e
    mov r0, #0x7e00000
    #mov r0, #0xfff00
    mov r0, #0xffffffff
    #mov r0, #0x107e

    ldr r0, =0x7e
    ldr r0, =0x7e00000
    ldr r0, =0xfff00
    ldr r0, =0xffffffff
    ldr r0, =0x107e
