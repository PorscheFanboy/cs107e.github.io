Despite being conceptually not that deep, interrupt handling (and
exception handling in general) tends to be ugly, complicated, and
poorly-documented.  The ARM is better than most, but far from ideal.
I found these two documents useful:
	http://www.valvers.com/open-software/raspberry-pi/step04-bare-metal-programming-in-c-pt4/

	http://xinu.mscs.mu.edu/BCM2835_Interrupt_Controller


	r0-r3 are the argument and scratch registers; r0-r1 are also the result registers


what is the problem?

---------------------------------------------------------------------
Why does your phone have a ringer?
	Stare at it til something happens (polling)
	Do do your thing and get interrupted (interrupts)

	if you didn't have interrupts what would you have to do?
		- constantly check if there was something there.
		- how would you do multi-processing?
			would have to yield.  if you didn't?
		- more and more devices is a problem.

		- if work can arrive faster than you can process it when
		  you will drop.
			keyboard example.

interrupts:
	[always ugly, always different] 
	high level when an interrupt occurs:
		the hardware:
			disables interrupts [if not?]
			saves some amount of the current state [if not?]
			jumps to a special location (either hardwired
			or specified using a register)

			the interrupt code then starts running.

		the interrupt handler 
			figures out what interrupt it was
			handles it.
			clears the interrupt [if not?]

			often: restores the original state and jumps 
			back.

			but sometimes: restores a different state and
			jumps there instead.

		on resumption:
			restore interrupts.

-------------------------------------------------------------------
main useful exercise you can do: just walk through the  code.
	find all the similar parts --- these we can ignore.
	focus on differences.


	first part starts similar.  we load 0x7000 instead of 0x8000
	[why?]

	cstart looks the same for bss

	what's going on with the vector copy?
		- it is copying to address 0x0???

	hardware jumps to the following offsets for each of the
	possible exceptions / interrupts:
		exception name  		offset
		reset 				0
		undefined inst 			4
		software int			8
		prefetch abort			12
		data abort			16
		<unassigned>			20
		irq				24
		fiq				28

	- uart init just like before.
	- setupt timer init:
		- we set random values.
		- this you can find in the broadcom document.

		Interrupts on a processor are enabled per interrupt
		source and then globally enabled and disabled.

		enable timer.
		enable basic IRQs

		what if we did this before copying the vector table?
	
	- interrupt handler
		what's going on with sp?
		what happens if we don't have shadow?
		how would you start?

		subs <--- will restore cpsr from spsr
		so will movs
		and ldm with a ^

   		recall from arm manual:
	   		r4-r8 are callee-save registers

			r9 might be a callee-save register or not (on
			some variants of AAPCS it is a special register)

			r10-r11 are callee-save registers r12-r15 are
			special registers


		for safety we should maybe save all registers (as Phil's
		code does) but here we save what we believe to be the
		caller saved ones.

	- for disable/enable interrupt:
		cpsr_c --- _c modifies just the lower bits


different errors:
   1- for the vectors:
	change the instruction to just branch where we want.
		--- what happens?

	if we put the interrupt handler at offset 24?
		- bad practice, but will work as long as we don't
		take any other exceptions.

		point: there is nothing special about these addresses.

   2 - interrupt handler itself:
	if we don't change lr?
	if we just jump back without subs/movs?
	if we jump somewhere else besides lr?
	if we do not setup the stack pointer?

	if we set it to the same stack pointer as the user?
		i think often will work.

	if we use the current stack pointer?
		- how do we access it?
		[use the instructions]

	if we delete the interrupt clear?
	if we disable interrupts and jump back?

   3 switching modes.
	what happens if we switch the current cspr?
	what happens if we use the original stack?
	what happens if we share the stack?

	other ways to jump back?
        	movs    pc, lr
        	ldm   sp!, {pc}^


they need to know 
	cpsr layout
	spsr layout

  instructions
	mrs
	msr
	bic 
	orr

	r12 --- maybe have to save.

	r13 --- stack
	r14 --- link registers
	r15 --- pc

	messing

	* print out interrupt status

exceptions:

on interupt:
	set:
		spsr = cpsr
		cpsr = ?
	switch to using
		lr.int
		sp.int
	pc = 0x18

--------------------------------------------------------------------
summary:  ARM interrupt handling.
	messy, but actually better than most.

	- copy the interrupt table.
		this has to be position independent code.
	- write interrupt handler
		this must load a stack (*)
		save at least any caller saved registers (can save everything)
		clear interrupts in some device specific way (if not?)
		jump back to original, restoring the cspr
		
	- to use interrupts
		generally: have to flip some device specific bits.
		plus: enable interrupts in the cpsr


if you uncomment the code, it will print cspr and sspr.  the low 
bits:
	mode:
	10011   supervisor
	10010   IRQ
