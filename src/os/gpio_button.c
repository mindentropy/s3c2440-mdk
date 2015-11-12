#include "gpio_button.h"
#include "interrupt.h"
#include "uart_util.h"
#include "exception_interrupt.h"

/* MINI2440 Button Diagram 
 * -----------------------
 *
 * K6 K4 K5    Battery Holder.
 * K3 K2 K1 
 * 
 * K1 -> GPG0 -> EINT8
 * K2 -> GPG3 -> EINT11
 * K3 -> GPG5 -> EINT13
 * K4 -> GPG6 -> EINT14
 * K5 -> GPG7 -> EINT15
 * K6 -> GPG11 -> EINT19
 *
 */


void EINT8_23_handler(void)
{
	clear_external_pending_interrupts(GPIO_BA,EINT8);
	test_blink_led();
}

void init_gpio_button()
{
	//TODO: Do a clear_reg_params just to be safe.

	//Disable pull up.	
	set_reg_params(GPUP_REG(GPG_BA),
			K1_GPIO_BTN_PIN
			|K2_GPIO_BTN_PIN
			|K3_GPIO_BTN_PIN
			|K4_GPIO_BTN_PIN
			|K5_GPIO_BTN_PIN
			|K6_GPIO_BTN_PIN
			);

	set_gpio_con(GPG_BA,set_gpio_function(GPIO_EINT_FN,K1_GPIO_PIN_POS)
						| set_gpio_function(GPIO_EINT_FN,K2_GPIO_PIN_POS)  
						| set_gpio_function(GPIO_EINT_FN,K3_GPIO_PIN_POS)
						| set_gpio_function(GPIO_EINT_FN,K4_GPIO_PIN_POS)
						| set_gpio_function(GPIO_EINT_FN,K5_GPIO_PIN_POS)
						| set_gpio_function(GPIO_EINT_FN,K6_GPIO_PIN_POS) 
						);
			

	//Enable interrupts.
	
	//Enable EINT19 falling edge.
	writereg32(EXTINT2_REG(GPIO_BA),TRIGGER_FALLING_EDGE<<12);

	//Enable EINT15,14,13,11,8.
	writereg32(EXTINT1_REG(GPIO_BA),
								(TRIGGER_FALLING_EDGE<<28)
								|(TRIGGER_FALLING_EDGE<<24)
								|(TRIGGER_FALLING_EDGE<<20)
								|(TRIGGER_FALLING_EDGE<<12)
								|(TRIGGER_FALLING_EDGE<<0));
	
	enable_external_interrupt((GPIO_BA),
								K1_GPIO_EINT
								|K2_GPIO_EINT
								|K3_GPIO_EINT
								|K4_GPIO_EINT
								|K5_GPIO_EINT
								|K6_GPIO_EINT);
	
	print_hex_uart(UART0_BA,readreg32(EINTMASK_REG(GPIO_BA)));
	enable_interrupt_service(INT_BA,EINT8_23);


	add_irq_handler(INT_EINT8_23_OFFSET,EINT8_23_handler);
}

