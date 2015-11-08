#include "mmu.h"
#include "uart.h"
#include "board_config.h"
#include "uart_util.h"
#include "led.h"
#include "exception_interrupt.h"

extern void blink_leds(unsigned int leds);


void blink_led_test()
{
	while(1)
		blink_leds(LED2|LED3);
}


void do_handle_undef()
{

}

void do_handle_swi()
{
	while(1) {
		blink_leds(LED2|LED3);
	}
}

void do_handle_pabt()
{
	
}

void do_handle_dabt()
{

}


void do_handle_irq()
{
	while(1) {
		blink_leds(LED2|LED3);
	}
}

void do_handle_fiq()
{
	
}
