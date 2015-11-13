#include "mmu.h"
#include "uart.h"
#include "board_config.h"
#include "uart_util.h"
#include "led.h"
#include "exception_interrupt.h"
#include "interrupt.h"

extern void test_delay();

void (*interrupt_handler_jmp_table[32])(void);

void test_blink_led(void)
{
	led_on(LED1|LED2|LED3|LED4);
	test_delay();
	led_off(LED1|LED2|LED3|LED4);
	test_delay();
}


static void dummy_handler(void)
{

}

void init_jmp_table(void)
{
	uint8_t i = 0;

	for(i = 0; i<NUM_OF_INTERRUPT_SRCS; i++) {
		interrupt_handler_jmp_table[i] = dummy_handler;
	}
}

void add_irq_handler(enum int_offset INT_OFFSET,
						void (*interrupt_handler)(void))
{
	interrupt_handler_jmp_table[INT_OFFSET] = interrupt_handler;
}


void handle_irq(void)
{
	uint8_t offset = 0;

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


	
	offset = readreg32(INTOFFSET_REG(INT_BA));
	interrupt_handler_jmp_table[offset]();

	/*
	 * NOTE: Clear the interrupt source pending before interrupt pending. See pg.14-14 of S3C2440 manual
	 */
	clear_interrupt_source_pending(INT_BA,BIT(offset));


	clear_interrupt_pending(INT_BA,BIT(offset));
	print_hex_uart(UART0_BA,readreg32(INTPND_REG(INT_BA)));


/*	print_hex_uart(UART0_BA,readreg32(EINTPEND_REG(GPIO_BA)));
	print_hex_uart(UART0_BA,readreg32(SRCPND_REG(INT_BA)));
	print_hex_uart(UART0_BA,readreg32(INTOFFSET_REG(INT_BA)));*/
}



