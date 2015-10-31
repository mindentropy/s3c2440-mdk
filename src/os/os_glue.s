/*
 * Approaches to overwrite the exception vector table of the bootloader.
 * --------------------------------------------------------------------
 * 1) Enable MMU and use virtual addresses.
 * 2) Overwrite the exception vector table by copying the vectors from the OS section
 *    to the sram section.
 *
 * Steps involved for approach (2)
 * 1) Create a section in assembly and the ld script variables which identifies 
 * 	  the start_vector_section and end_vector section.
 * 2) Export the variables in C and use it to copy the section contents to the 
 *    SRAM.
 * 3) Test by running an exception and blinking an LED.
 *
 * References: 
 * 1) https://balau82.wordpress.com/2012/04/15/arm926-interrupts-in-qemu/
 * 2) ARM Baremetal programming: http://www.state-machine.com/arm/Building_bare-metal_ARM_with_GNU.pdf
 *    and http://www.state-machine.com/resources/articles.php#ARM
 */

.section .text

.equ ABORT_MODE, 	 0x17
.equ FIQ_MODE,		 0x11
.equ IRQ_MODE,		 0x12
.equ SVC_MODE,		 0x13
.equ SYS_MODE,		 0x1F
.equ UNDEF_MODE,	 0x1B
.equ USR_MODE,		 0x10
.equ CPSR_MODE_MASK, 0x1F
.equ NoInt, 		 0xC0

.code 32
.globl start_os

start_os:
	ldr r3,WTCON
	ldr r6,=0x00
	str r6,[r3]

	/* Start by clearing bss section */
	ldr r1, bss_start
	ldr r2, bss_end
	ldr r3, =0

clear_bss:
	cmp r1,r2
	str r3,[r1],#4
	bne clear_bss

stack_setup:
	/* We are in the supervisor (svc) mode. Setup up the stack */
	/* load r13 i.e. svc stack pointer with svc_stack_pointer */
	ldr r13,svc_stack_pointer

	/*** Setup stack for irq mode ***/
	/* See example in s3c2440 Pg 3-20 for setup */

	mrs r0,cpsr 				/* Take a copy of the register */
	bic r0,r0,#CPSR_MODE_MASK 	/* Clear the mode bits */
	orr r0,r0,#IRQ_MODE 		/* Set the mode to irq */
	orr r0,r0,#NoInt 			/* Disable irq,fiq interrupt */
	msr cpsr,r0     			/* Write the modified value back to CPSR */
	ldr r13,irq_stack_pointer 	/* Load the stack with the irq stack */

	/*** Setup stack for fiq mode ***/
	mrs r0,cpsr 				/* Take a copy of the register */
	bic r0,r0,#CPSR_MODE_MASK 	/* Clear the mode bits */
	orr r0,r0,#FIQ_MODE         /* Setup fiq_mode */
	orr r0,r0,#NoInt 			/* Disable irq,fiq interrupt */
	msr cpsr,r0
	
	/* 
	 * r8-r14 are shadow registers for fiq. Here r8-r12 are general purpose.
	 * Hence setting it to 0
	 */

	ldr r8,=0
	ldr r9,=0
	ldr r10,=0
	ldr r11,=0
	ldr r12,=0
	ldr r13,fiq_stack_pointer

	/*** Setup stack for usr and sys mode ***/
	/* Usr and system mode share the same stack */
	/* 
	 * I cannot be in the user mode as there is no way to change the cpsr
	 * in user mode. Hence the stack has to be changed in system mode as the
	 * stack for system and user mode are the same.
	 */

	mrs r0,cpsr
	bic r0,r0,#CPSR_MODE_MASK 	/* Clear the mode bits */
	orr r0,r0,#SYS_MODE         /* Setup sys_mode */
	orr r0,r0,#NoInt 			/* Disable irq,fiq interrupt */
	msr cpsr,r0
	ldr r13,usr_sys_stack_pointer

	/* Set it back to SVC mode for further setup */
	mrs r0,cpsr
	bic r0,r0,#CPSR_MODE_MASK 	/* Clear the mode bits */
	orr r0,r0,#SVC_MODE         /* Setup svc_mode */
	orr r0,r0,#NoInt 			/* Disable irq,fiq interrupt */
	msr cpsr,r0
	
	bl main

	b start_os



svc_stack_pointer: .word __svc_stack_top__
irq_stack_pointer: .word __irq_stack_top__
fiq_stack_pointer: .word __fiq_stack_top__
usr_sys_stack_pointer: .word __usr_sys_stack_top__

bss_start : .word __bss_start__
bss_end : .word __bss_end__

WTCON: 	.word 	0x53000000

	.end
