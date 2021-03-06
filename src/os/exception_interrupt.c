#include "mmu.h"
#include "uart.h"
#include "board_config.h"
#include "uart_util.h"
#include "led.h"
#include "exception_interrupt.h"
#include "interrupt.h"

extern void test_delay();

void (*interrupt_handler_jmp_table[NUM_OF_INTERRUPT_SRCS])(void);
void (*external_interrupt_handler_jmp_table[NUM_OF_EXTERNAL_INTERRUPT_SRCS])(void);

void test_blink_led(void)
{
	led_on(LED1|LED2|LED3|LED4);
	test_delay();
	led_off(LED1|LED2|LED3|LED4);
	test_delay();
}


void dummy_handler(void) 
{

}

void init_jmp_table(void)
{
	uint8_t i = 0;

	for(i = 0; i<NUM_OF_INTERRUPT_SRCS; i++) {
		interrupt_handler_jmp_table[i] = dummy_handler;
	}

	for(i = 0; i<NUM_OF_EXTERNAL_INTERRUPT_SRCS; i++) {
		external_interrupt_handler_jmp_table[i] = dummy_handler;
	}
}

void add_irq_handler(enum int_offset INT_OFFSET,
						void (*interrupt_handler)(void))
{
	interrupt_handler_jmp_table[INT_OFFSET] = interrupt_handler;
}

void add_external_irq_handler(enum eint_offset EINT_OFFSET,
								void (*external_interrupt_handler)(void))
{
	external_interrupt_handler_jmp_table[EINT_OFFSET] = external_interrupt_handler;
}


/* 
 * TODO: Handle irq can be handled in the exception_handler.s in assembly
 * itself. Presently the following function is inefficient because of the
 * wasted jump from handle_irq to the interrupt handler.
 */

//void handle_irq(void)
//{
//	uint32_t int_ptr = 0;
	//uint32_t cpsr_val = 0;

/*
 * Handling of interrupts
 * ======================
 * We have 2 registers to take care of in the interrupt controller.
 * SRCPND and INTPND register.
 *
 * To service the interrupt:
 * 1) Clear the SRCPND register. See pg.14-14 of S3C2440 manual.
 * 2) Clear the interrupt pending register. --> Only 1 bit will be set.
 *
 * If the interrupt is a GPIO then clear the EINT field in EINTPEND register.
 *
 */


//	__asm__ __volatile__ (
//		"mrs r0,cpsr\n\t" 		/* Copy CPSR to r0 */
//		"mov %0,r0\n\t"
//		: [cpsr_val]"=r"(cpsr_val) /* No output */
//		: /* No input */
//		: "r0" /* r0 gets clobbered */
//	);
	
/*
	__asm__ __volatile__ (
		"ldr r3,=interrupt_handler_jmp_table\n\t"
		"mov r1,#5\n\t"
		"ldr r3,[r3,r1,LSL #2]\n\t"
		"mov %0,r3\n\t"
		:[int_ptr]"=r"(int_ptr)
		:
		:"r3"
	);
*/



/*	__asm__ __volatile__ (
		"mov %0,r2\n\t"
		:[int_ptr]"=r"(int_ptr)
		:
		:"r2"
	);*/


/*	print_hex_uart(UART0_BA,int_ptr);
	print_hex_uart(UART0_BA,
				(uint32_t)interrupt_handler_jmp_table[readreg32(INTOFFSET_REG(INT_BA))]);
	print_hex_uart(UART0_BA,(uint32_t)interrupt_handler_jmp_table);
	print_hex_uart(UART0_BA,(uint32_t)&dummy_handler);

	interrupt_handler_jmp_table[readreg32(INTOFFSET_REG(INT_BA))]();*/
	/*
	 * NOTE: Clear the interrupt source pending before interrupt pending. See pg.14-14 of S3C2440 manual
	 */

	/*** Common interrupt handling procedure ***/
//	clear_interrupt_source_pending(INT_BA,BIT(readreg32(INTOFFSET_REG(INT_BA))));
//	clear_interrupt_pending(INT_BA,BIT(readreg32(INTOFFSET_REG(INT_BA))));


//	uart_puts(UART0_BA,"----\n");

//	print_hex_uart(UART0_BA,readreg32(EINTPEND_REG(GPIO_BA)));
	/*print_hex_uart(UART0_BA,readreg32(INTPND_REG(INT_BA)));
	print_hex_uart(UART0_BA,readreg32(SRCPND_REG(INT_BA)));
	print_hex_uart(UART0_BA,readreg32(SUBSRCPND_REG(INT_BA)));
	print_hex_uart(UART0_BA,readreg32(INTOFFSET_REG(INT_BA)));
	print_hex_uart(UART0_BA,readreg32(INTMSK_REG(INT_BA)));*/


//	print_hex_uart(UART0_BA,cpsr_val);
//}



