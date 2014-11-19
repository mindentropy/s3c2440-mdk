#include "gpio_def.h"
#include "led.h"
#include "clock_pm.h"
#include "uart.h"
#include "wdt.h"
#include "spkr.h"
#include "interrupt.h"
#include "sdram.h"


#define PHYS_START   0x30000000U
#define MAX_RAM_SIZE 0x4000000U
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


//unsigned int test_val = 0;

//RAM addr space 0x30000000 - 0x34000000
volatile unsigned char *ram_ptr = PHYS_START;

char load_ch = 0;
unsigned int i = 0,load_size = 0;


int main(void) {
	/* Note : Do not put any operations above this */
	/* Disable watchdog.*/

	disable_watchdog(); 

	disable_all_interrupts();
	disable_all_interrupt_subservice();

	set_clk_dbg_port();
	init_clock();
	init_uart0();

	puts("TB\r\n");

	apb_clk_enable_gpio();
	//init_spkr();
	init_led();
	//led_on(LED4|LED3|LED2|LED1);
	led_off(LED4|LED3|LED2|LED1);


/* Without delay the led blink rate is 2MHz. */
	while(1) {
		led_on(LED4);
		test_delay();
		led_off(LED4);
		test_delay();
		puts("TB\r\n");
	}
}
