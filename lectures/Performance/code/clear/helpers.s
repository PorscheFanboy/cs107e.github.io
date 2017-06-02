// void assign8(void *dst, unsigned val, unsigned n);
.globl assign8
assign8:
  // We'll use r4-r11, which are callee-saved:
  // we need to save them to the stack first.
  sub sp, sp, #36
  stm sp, { r4, r5, r6, r7, r8, r10, r11 }

  // Fill each of 8 registers, r3-r11, with the
  // 4-byte val argument in r1.
  mov r3, r1
  mov r4, r1
  mov r5, r1
  mov r6, r1
  mov r7, r1
  mov r8, r1
  mov r10, r1
  mov r11, r1

loop:
  // Store 64 bytes at once to dst, then move dst.
  stm r0!, { r3, r4, r5, r6, r7, r8, r10, r11 }

  // Loop.
  sub r2, r2, #1
  cmp r2, #0
  bne loop

  // Restore callee-saved registers.
  ldm sp, { r4, r5, r6, r7, r8, r10, r11 }
  add sp, sp, #36

  bx lr
