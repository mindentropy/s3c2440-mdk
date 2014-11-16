#include "gpio_def.h"
#include "led.h"
#include "clock_pm.h"
#include "uart.h"
#include "wdt.h"
#include "spkr.h"
#include "interrupt.h"
#include "sdram.h"

#define PHYS_START   0x30000000
#define MAX_RAM_SIZE 0x4000000
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

//RAM addr space 0x30000000 - 0x34000000
unsigned char *ram_ptr = 0x33000000;

int main(void) {
	/* Note : Do not put any operations above this */
	/* Disable watchdog.*/
	disable_watchdog(); 

	disable_all_interrupts();
	disable_all_interrupt_subservice();

	set_clk_dbg_port();
	init_clock();

	init_uart0();

	apb_clk_enable_gpio();

	init_spkr();

	init_led();
	//led_on(LED4|LED3|LED2|LED1);

	//set_spkr_hi();
	//test_delay();
	//set_spkr_lo();
	led_off(LED4|LED3|LED2|LED1);

	
	/*puts("\r\nEnter your choice:\r\n");
	puts("1 - Jump to RAM\r\n");
	puts("2 - Load from flash to RAM\r\n");*/

	sdram_init();

	readreg32(BANKCON6,test_val);
	print_hex(test_val);
/* Without delay the led blink rate is 2MHz. */

	
	/*for(;ram_ptr < ((unsigned)(PHYS_START+0x100));ram_ptr++)
		*ram_ptr = test_val++;*/


	while(1) {
		led_on(LED4);

		*ram_ptr = test_val;
		//print_hex(*ram_ptr);

		if((test_val & 0xFF) != *ram_ptr) {
			set_spkr_hi();

			while(1)
				;
		}

		test_val++;
		ram_ptr++;
		led_off(LED4);

		if(ram_ptr >= (PHYS_START + MAX_RAM_SIZE -1)) {
			set_spkr_hi();
			ram_ptr = 0x30000000;
			test_delay();
			set_spkr_lo();
		}
		//test_delay();
	}
}
