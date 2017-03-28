.globl _start
_start: 
    mov sp, #0x8000
    mov fp, #0
    bl main
hang:
    b hang
