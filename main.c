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


unsigned int test_val = 0;

int main(void) {
	disable_watchdog();

	disable_all_interrupts();
	disable_all_interrupt_subservice();

	set_clk_dbg_port();
	init_clock();

	init_uart0();

	apb_clk_enable_gpio();

	//init_spkr();

	init_led();
	//led_on(LED4|LED3|LED2|LED1);

	//set_spkr_hi();
	//test_delay();
	//set_spkr_lo();
	led_off(LED4|LED3|LED2|LED1);

	readreg32(CLKSLOW,test_val);
	print_hex(test_val);
	
/* Without delay the led blink rate is 2MHz. */
	while(1) {
	//	uart_writel_ch0('a'); //Write to uart ch0
	//	set_spkr_hi();
		test_delay();
		led_on(LED4);
		test_delay();
	//	set_spkr_lo();
		led_off(LED4);
		//putc_ch0('a');

	}
}
