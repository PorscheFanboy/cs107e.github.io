.globl _start
_start:
    mov sp, #0x8000  @ Set SVC stack pointer
    bl _cstart
hang: b .

