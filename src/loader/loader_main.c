#include "gpio_def.h"
#include "led.h"
#include "clock_pm.h"
#include "uart.h"
#include "wdt.h"
#include "spkr.h"
#include "interrupt.h"
#include "sdram.h"
#include "board_config.h"

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
volatile unsigned char *ram_ptr = (unsigned char *)PHYS_START;

static int read_size()
{
	unsigned int size = 0;

	size = getc_ch0();
	size |= getc_ch0()<<8;
	size |= getc_ch0()<<16;
	size |= getc_ch0()<<24;

	return size;
}

char load_ch = 0;
unsigned int i = 0,load_size = 0;

void main(void) {
	/* Note : Do not put any operations above this */
	/* Disable watchdog.*/

	disable_watchdog(); 

	disable_all_interrupts();
	disable_all_interrupt_subservice();

	set_clk_dbg_port();
	init_clock();
	init_uart0();

	puts("ldr\r\n");

	apb_clk_enable_gpio();
	//init_spkr();
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
		load_ch = getc_ch0();
		ram_ptr[i] = load_ch;
		led_on(LED4);
		putc_ch0(ram_ptr[i]);
		led_off(LED4);
	}

	__asm__ __volatile__(
		"mov pc,#0x30000000\n\t"
	);

	__asm__ __volatile__(
		"b .\n\t"
	);

}
