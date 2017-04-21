.globl _start
_start:
    mov sp, #0x8000000
    mov fp, #0x0
    bl _cstart
hang: b hang
