#include "gpio_def.h"
#include "led.h"
#include "clock_pm.h"
#include "uart.h"
#include "wdt.h"
#include "spkr.h"
#include "interrupt.h"

/*
 *  LED Orientation
 *
 *  <- Interfaces side -- GPIO Headers side  ->
 *   _   _   _   _
 *  |_| |_| |_| |_|
 *   1   2   3   4
 *
 *  nLED_1 -> GPB5
 *	nLED_2 -> GPB6
 *	nLED_3 -> GPB7
 *  nLED_4 -> GPB8
 *
 */


void test_delay() {

	register unsigned int i = 0, j = 0;

	for(j = 0; j<3; j++) {
		for(i = 0; i<100000;i++) {
			;
		}
	}
}

int main(void) {
	disable_watchdog();

	disable_all_interrupts();
	disable_all_interrupt_subservice();

	init_clock();
	test_delay();
	//init_uart0();
	//init_spkr();

	apb_clk_enable_gpio();
	//set_clk_dbg_port();

	init_led();
	led_on(LED4|LED3|LED2|LED1);

	set_spkr_hi();
	test_delay();
	set_spkr_lo();

	led_off(LED4|LED3|LED2|LED1);
/* Without delay the led blink rate is 2MHz. */
	while(1) {
		
	//	uart_writel_ch0('a'); //Write to uart ch0
		
		test_delay();
		led_on(LED4);
		test_delay();
		led_off(LED4);

	}
}
