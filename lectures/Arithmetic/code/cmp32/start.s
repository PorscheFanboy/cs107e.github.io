.globl _start
_start:
    mov sp,#0x08000000
    bl _cstart
hang: b hang

