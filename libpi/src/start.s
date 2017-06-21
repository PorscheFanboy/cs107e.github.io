// The deference full assembly start sequence for CS107E.
// This sets up the stack and other execution context for
// interrupt mode, fast interrupt mode, and supervisor mode
// before branching to _cstart (in cstart.c). It sets up the
// frame pointer in fast interrupt mode in case someone wants
// to backtrace in that mode.
//
// If _cstart() returns, _start hangs in an infinite loop.
//
// Author: Philip Levis
// Date: 6/20/2017
        
.globl _start
_start:
    mov r0, #0xD2  // Interrupts
    msr cpsr_c, r0
    mov sp, #0x8000
    mov r0, #0xD1  // Fast interrupts
    msr cpsr_c, r0       
    mov sp, #0x4000       
    mov fp, #0     // FIQ has fp
    mov r0, #0xD3  // Supervisor
    msr cpsr_c, r0      
    mov sp, #0x8000000
    mov fp, #0
    bl _cstart

hang: b hang

// Copyright (c) 2017 Stanford University.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
// - Neither the name of the Stanford University nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL STANFORD
// UNIVERSITY OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
