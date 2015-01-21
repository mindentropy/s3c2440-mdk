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
.code 32
.globl start_os

/*
os_vector_jmp:
	b start_os
	b .
	b os_software_intr
	b .
	b .
	b .
	b .
	b .
*/

/*	b start_os
	b os_undef_instr
	b os_software_intr
	b os_abrt_prefetch
	b os_abrt_data
	b os_reserved
	b os_irq
	b os_fiq
*/

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

	/* load r13 i.e. stack pointer with stack_pointer */
	ldr r13,stack_pointer

	bl main

	b start_os


stack_pointer: .word __stack_top__
bss_start : .word __bss_start__
bss_end : .word __bss_end__

WTCON: 	.word 	0x53000000

	.end
