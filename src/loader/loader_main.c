#include "gpio_def.h"
#include "led.h"
#include "clock_pm.h"
#include "uart.h"
#include "wdt.h"
#include "spkr.h"
#include "interrupt.h"
#include "sdram.h"
#include "board_config.h"
#include "uart_util.h"

#include <stdint.h>

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

	register uint32_t i = 0, j = 0;

	for(j = 0; j<3; j++) {
		for(i = 0; i<100000;i++) {
			;
		}
	}
}


//uint32_t test_val = 0;

//RAM addr space 0x30000000 - 0x34000000
volatile unsigned char *ram_ptr = (unsigned char *)PHYS_START;

static int read_size()
{
	uint32_t size = 0;

	size = getc(UART0_BA);
	size |= getc(UART0_BA)<<8;
	size |= getc(UART0_BA)<<16;
	size |= getc(UART0_BA)<<24;

	return size;
}

char load_ch = 0;
uint32_t i = 0,load_size = 0;

void main(void) {
	/* Note : Do not put any operations above this */
	/* Disable watchdog.*/

	disable_watchdog(WT_BA); 

	disable_all_interrupts(INT_BA);
	disable_all_interrupt_subservice(INT_BA);

	set_clk_dbg_port();
	init_clock();
	//init_uart0();
	init_uart(UART0_BA);

	uart_puts(UART0_BA,"ldr\r\n");

	//apb_clk_enable_gpio();
	apb_clk_enable(CLK_BASE_ADDR,CLK_GPIO);
	init_spkr();
//	init_led();
//	led_off(LED4|LED3|LED2|LED1);

	sdram_init();

	//print_hex(readreg32(BANKCON6));
/* Without delay the led blink rate is 2MHz. */

	//print_hex(read_size());
	//print_hex(load_size = read_size());

	
	load_size = read_size();

	for(i = 0; i<load_size; i++)
	{
		//load_ch = getc_ch0();
		load_ch = getc(UART0_BA);
		ram_ptr[i] = load_ch;
		set_spkr_hi();
		led_on(LED4);
		//putc_ch0(ram_ptr[i]);
		putc(UART0_BA,ram_ptr[i]);
		led_off(LED4);
		set_spkr_lo();
	}

	__asm__ __volatile__(
		"mov pc,#0x30000000\n\t"
	);

	__asm__ __volatile__(
		"b .\n\t"
	);

}
