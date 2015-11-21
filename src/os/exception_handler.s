.equ LED_MASK, 0x1E0
.equ LED_BLINK_DELAY, 20
.equ IRQ_FIQ_MASK, 0xC0


.section .isrhandler,"ax"


.code 32


.globl do_handle_reset
do_handle_reset:
	b do_handle_reset

.globl do_handle_undef
do_handle_undef:
	b do_handle_undef

.globl do_handle_swi
do_handle_swi:
	b do_handle_swi

.globl do_handle_pabt
do_handle_pabt:
	b do_handle_pabt

.globl do_handle_dabt
do_handle_dabt:
	b do_handle_dabt

.globl do_handle_reserved
do_handle_reserved:
	b do_handle_reserved


.globl do_handle_irq
do_handle_irq:
	sub lr,lr,#4 @Subtract r14(lr) by 4.
	stmfd sp!, {r0-r12,lr} @Save r0-r12 and lr. 
							@sp! indicates sp will be subtracted by the sizes of the registers saved.
							@Instruction details can be read in ARM System Developers guide book at Pg 65.
	/*
	 * Note on disabling and enabling CPU IRQ.
	 * ======================================
	 * There is no need to disable IRQ when in IRQ mode. When there is 
	 * an interrupt the processor switches to IRQ mode with the I bit 
	 * enabled which means it is masked.
	 *
	 * It was tested by printing the cpsr_irq which had the value
	 * 0x60000092. The 7th bit is set which means the IRQ flag is set.
	 *
	 * This is the same case with the FIQ.
	 */
	
	ldr r2,INTOFFSET    @Load the INTOFFSET value into r2
	ldr r2,[r2]    		@Load the value in the address to r2
	

	ldr r3,=interrupt_handler_jmp_table @Load the address of the interrupt handler jump table.

	mov lr,pc
	ldr pc,[r3,r2,LSL #2] @Load the value which is the interrupt handler jmp table.


//	bl handle_irq

	//Clear interrupt source pending

	ldr r2,INTOFFSET    @Load the INTOFFSET value into r2
	ldr r2,[r2]    		@Load the value in the address to r2

	mov r3,#1 			@move 1 to r3.
	mov r3,r3, LSL r2   @Shift left by INTOFFSET and store it in r3
	
	ldr r4,SRCPND
	str r3,[r4] 		@Store the value of r3 in r4 address

	ldr r4,INTPND
	str r3,[r4] 		@Store the value of r3 in r4 address

	
	
	ldmfd sp!, {r0-r12,pc}^ 	@Restore the stack values to r0 and r12. Next restore lr to pc.
							@The ^ indicates the spsr has to copied to cpsr. The cpsr was copied to spsr
							@when the interrupt was generated.
	

.globl do_handle_fiq
do_handle_fiq:
 	b do_handle_fiq

GPBDAT: 	.word 		0x56000014

SRCPND:     .word 		0x4A000000
INTPND: 	.word  		0x4A000010
INTOFFSET: 	.word 		0x4A000014

.end
