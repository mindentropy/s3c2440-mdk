#include "interrupt.h"
#include "uart_util.h"
#include "exception_interrupt.h"

#define IRQ_FIQ_MASK 0xC0

static void enable_irq_fiq(void)
{
	uint32_t cpsr_val = 0;

	__asm__ __volatile__ (
		"mrs r0,cpsr\n\t" 		/* Copy CPSR to r0 */
		"bic r0,r0,#0xC0\n\t" 	/* Clear IRQ, FIQ */
		"msr cpsr,r0\n\t" 		/* Copy modified value to cpsr */
		"mov %0,r0\n\t"
		: [cpsr_val]"=r"(cpsr_val) /* No output */
		: /* No input */
		: "r0" /* r0 gets clobbered */
	);

	//print_hex_uart(UART0_BA,cpsr_val);
}

void init_interrupt_controller(void)
{
	clear_interrupt_source_pending(INT_BA,0xFFFFFFFFU);
	enable_irq_fiq();
	init_jmp_table();
}
