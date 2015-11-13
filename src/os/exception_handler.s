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

	/* Disable IRQ and FIQ */
	mrs r0,cpsr
	orr r0,r0,#IRQ_FIQ_MASK
	msr cpsr,r0
	/**********************/
							
	bl handle_irq

	/*Enable IRQ and FIQ */
	mrs r0,cpsr
	bic r0,r0,#IRQ_FIQ_MASK
	msr cpsr,r0
	/**********************/
	
	ldmfd sp!, {r0-r12,pc}^ 	@Restore the stack values to r0 and r12. Next restore lr to pc.
							@The ^ indicates the spsr has to copied to cpsr. The cpsr was copied to spsr
							@when the interrupt was generated.
	

.globl do_handle_fiq
do_handle_fiq:
 	b do_handle_fiq


GPBDAT: .word 		0x56000014

.end
