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
.globl vectors

vectors:
	b reset 	/* Reset */
	b .			/* Undefined instruction */
	b .			/* Software Interrupt */
	b .			/* Abort prefetch */
	b .			/* Abort data */
	b .			/* Reserved */
	b .			/* IRQ */
	b .			/* FIQ */


/*
	nLED_1 -> GPB5
	nLED_2 -> GPB6
	nLED_3 -> GPB7
	nLED_4 -> GPB8
*/

reset:
/*	ldr r3,GPBCON
	ldr	r4,GPBDAT
	ldr r5,GPBUP

	ldr r6,=0x15400
	str r6,[r3]  @Set to output
	ldr r6,=0x00
	str r6,[r4]  @Set the led
	ldr r6,=0x1E0
	str r6,[r5]	 @Disable pullup */


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

	b vectors


stack_pointer: .word __stack_top__
bss_start : .word __bss_start__
bss_end : .word __bss_end__

/*
GPBCON:	.word	0x56000010
GPBDAT:	.word	0x56000014
GPBUP:	.word	0x56000018
*/

	.end
