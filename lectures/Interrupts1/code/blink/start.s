.globl _start
_start:
    mov sp, #0x800000  @ Set SVC stack pointer
    bl _cstart
hang: b reboot

/*
 * Interrupt vectors.
 */
.globl _vectors
.globl _vectors_end
        
_vectors:
  ldr pc, _reset_asm
  ldr pc, _undefined_instruction_asm
  ldr pc, _software_interrupt_asm
  ldr pc, _prefetch_abort_asm
  ldr pc, _data_abort_asm
  ldr pc, _reset_asm
  ldr pc, _interrupt_asm
fast_interrupt_asm:
  ldr pc, _fast_asm

_reset_asm:                   .word impossible_asm
_undefined_instruction_asm:   .word impossible_asm
_software_interrupt_asm:      .word impossible_asm
_prefetch_abort_asm:          .word impossible_asm
_data_abort_asm:              .word impossible_asm
_interrupt_asm:               .word interrupt_asm
_fast_asm:                    .word impossible_asm

_vectors_end:

interrupt_asm:
	mov sp, #0x8000 @ Set interrupt stack pointer
        sub lr, lr, #4

        push {r0-r12,lr}

        mov  r0, lr
        bl  interrupt_handler

        pop {r0-r12, lr}

        // jump back
        //subs    pc, lr, #0
        movs    pc, lr

impossible_asm:
  mov sp, #0x7000  @ Set interrupt stack pointer
  sub   lr, lr, #4
  bl    impossible_handler    @ C function
  b     reboot

