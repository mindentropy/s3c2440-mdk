#include "mmu.h"
#include "uart.h"
#include "board_config.h"
#include "uart_util.h"
#include "led.h"
#include "exception_interrupt.h"
#include "interrupt.h"

extern void blink_leds(unsigned int leds);
extern void test_delay();

void (*interrupt_handler_jmp_table[32])(void);

void test_blink_led(void)
{
	led_on(LED1|LED2|LED3|LED4);
	test_delay();
	led_off(LED1|LED2|LED3|LED4);
	test_delay();
}


void add_irq_handler(enum int_offset INT_OFFSET,
						void (*interrupt_handler)(void))
{
	interrupt_handler_jmp_table[INT_OFFSET] = interrupt_handler;
}

void handle_irq(void)
{

/*
 * Handling of interrupts
 * ======================
 * We have 2 registers to take care of in the interrupt controller.
 * SRCPND and INTPND register.
 *
 * To service the interrupt:
 * 1) Clear the SRCPND register.
 * 2) Clear the interrupt pending register. --> Only 1 bit will be set.
 *
 * If the interrupt is a GPIO then clear the EINT field in EINTPEND register.
 *
 */
	
	//print_hex_uart(UART0_BA,readreg32(EINTPEND_REG(GPIO_BA)));
	//print_hex_uart(UART0_BA,readreg32(SRCPND_REG(INT_BA)));
	//print_hex_uart(UART0_BA,readreg32(INTPND_REG(INT_BA)));
	print_hex_uart(UART0_BA,readreg32(INTOFFSET_REG(INT_BA)));
}
