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
    sub lr, lr, #4  @ Calculate pc to return to

    push {r0-r12,lr} @ Save all registers

    mov r0, lr       @ Call C interrupt handler with arg=pc
    bl interrupt_handler

    pop {r0-r12, lr} @ Restore registers
    movs pc, lr      @ Special return from interrupt
    @ movs restores processor mode 

impossible_asm:
    mov sp, #0x7000  @ Set interrupt stack pointer
    sub lr, lr, #4
    bl impossible_handler    @ C function
    movs pc, lr

