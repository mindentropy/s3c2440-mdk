#include "gpio_button.h"
#include "interrupt.h"
#include "uart_util.h"

/* MINI2440 Button Diagram 
 * -----------------------
 *
 * K6 K4 K5    Battery Holder.
 * K3 K2 K1 
 *
 */


void init_gpio_button()
{
	//TODO: Do a clear_reg_params just to be safe.

	//Disable pull up.	
	set_reg_params(GPUP_REG(GPG_BA),
			K1_GPIO_BTN
			|K2_GPIO_BTN
			|K3_GPIO_BTN
			|K4_GPIO_BTN
			|K5_GPIO_BTN
			|K6_GPIO_BTN);

	//Enable interrupts.
	
	//Enable EINT19 falling edge.
	writereg32(EXTINT2_REG(GPIO_BA),TRIGGER_FALLING_EDGE<<12);

	//Enable EINT15,14,13,11,8.
	writereg32(EXTINT1_REG(GPIO_BA),
								(TRIGGER_FALLING_EDGE<<28)
								|(TRIGGER_FALLING_EDGE<<24)
								|(TRIGGER_FALLING_EDGE<<20)
								|(TRIGGER_FALLING_EDGE<<12)
								|(TRIGGER_BOTH_EDGE<<0)
								);

	print_hex_uart(UART0_BA,readreg32(EXTINT1_REG(GPIO_BA)));
	
	enable_external_interrupt((GPIO_BA),
								K1_GPIO_EINT
								|K2_GPIO_EINT
								|K3_GPIO_EINT
								|K4_GPIO_EINT
								|K5_GPIO_EINT
								|K6_GPIO_EINT);

	enable_interrupt_service(INT_BA,EINT8_23);

	print_hex_uart(UART0_BA,readreg32(INTMSK_REG(INT_BA)));
}
