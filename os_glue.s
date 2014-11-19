/*
 * Problems related to linker script addresses.
 * --------------------------------------------
 *
 * If the address of the code is setup such that the .text
 * section is put in sdram say 0x32000000. Next if the program
 * is loaded to the address 0x30000000 then we expect that the
 * program should not work properly because the address generated
 * in the code is different. This is not the case as the branch
 * instruction is pc(program counter) relative. Hence the b reset
 * would be b <pc+offset>. The branch instructions create position
 * independent code which makes the above scenario work. Of course
 * if the code becomes somehow position dependent then the above 
 * condition would fail.
 */

.section .text
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

	/* load r13 i.e. stack pointer with stack_pointer */
	ldr r13,stack_pointer

	bl main

	b start_os


stack_pointer: .word __stack_top__
bss_start : .word __bss_start__
bss_end : .word __bss_end__

WTCON: 	.word 	0x53000000

	.end
