.equ LED_MASK, 0x1E0
.equ LED_BLINK_DELAY, 8000

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

/*  
	LED1 BIT5
	LED2 BIT6
	LED3 BIT7
	LED4 BIT8
*/

.globl do_handle_irq
do_handle_irq:
	sub lr,lr,#4 @Subtract r14(lr) by 4.
	stmfd sp!, {r0-r12,lr} @Save r0-r12 and lr

looper:
	bl test_blink_led
	b looper




.globl do_handle_fiq
do_handle_fiq:
 	b do_handle_fiq


GPBDAT: .word 	0x56000014

.end
