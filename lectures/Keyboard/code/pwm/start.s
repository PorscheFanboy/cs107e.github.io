.globl _start
.func _start, _start
_start:
    mov sp, #0x8000000
    mov fp, #0
    bl _cstart
hang:
    b hang
