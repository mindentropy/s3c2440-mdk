#include "gpio_def.h"
#include "led.h"
#include "clock_pm.h"
#include "uart.h"
#include "wdt.h"
#include "spkr.h"
#include "interrupt.h"
#include "sdram.h"
#include "board_config.h"
#include "cpu.h"
#include "cache.h"


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


void dump_clk()
{
	unsigned int reg_dbg_val = 0;

	puts("************************\r\n");
	puts("reg_locktime: ");
	readreg32(REG_LOCKTIME,reg_dbg_val);
	print_hex(reg_dbg_val);
	puts("\r\n");
	puts("mpllcon : ");
	readreg32(MPLLCON,reg_dbg_val);
	print_hex(reg_dbg_val);
	puts("\r\n");
	puts("upllcon : ");
	readreg32(UPLLCON,reg_dbg_val);
	print_hex(reg_dbg_val);
	puts("\r\n");
	puts("clkdivn: ");
	readreg32(CLKDIVN,reg_dbg_val);
	print_hex(reg_dbg_val);
	puts("\r\n");
	puts("clkslow: ");
	readreg32(CLKSLOW,reg_dbg_val);
	print_hex(reg_dbg_val);
	puts("\r\n");
	puts("clkcon: ");
	readreg32(CLKCON,reg_dbg_val);
	print_hex(reg_dbg_val);
	puts("\r\n");

	puts("************************\r\n");
}

void dump_cpu_info()
{
	print_hex(get_cpu_id());
}

void dump_cache_info()
{
	print_hex(get_cache_info());

	puts("cache type:");
	print_hex(get_cache_type(get_cache_info()));
	puts("\r\n");

	puts("sbit:");
	print_hex(get_sbit(get_cache_info()));
	puts("\r\n");
	
	puts("dsize info:");
	print_hex(get_dsize_info(get_cache_info()));
	puts("\r\n");

	puts("isize info:");
	print_hex(get_isize_info(get_cache_info()));
	puts("\r\n");

	puts("size:");
	print_hex(get_size(get_dsize_info(get_cache_info())));
	puts("\r\n");

	puts("assoc:");
	print_hex(get_assoc(get_dsize_info(get_cache_info())));
	puts("\r\n");

	puts("mbit:");
	print_hex(get_mbit(get_dsize_info(get_cache_info())));
	puts("\r\n");
	
	puts("line len:");
	print_hex(get_line_len(get_dsize_info(get_cache_info())));
	puts("\r\n");
}

int main(void) {
	/* Note : Do not put any operations above this */
	/* Disable watchdog.*/
//	unsigned char *sram_loc;

	disable_watchdog(); 

	disable_all_interrupts();
	disable_all_interrupt_subservice();

	set_clk_dbg_port();
	init_clock();
	init_uart0();

	//puts("TB\r\n");

	apb_clk_enable_gpio();
	init_spkr();
	init_led();
	led_off(LED4|LED3|LED2|LED1);

	//sram_loc = 0;
	
	dump_clk();
	dump_cpu_info();
	dump_cache_info();

/* Without delay the led blink rate is 2MHz. */
	while(1) {
		led_on(LED4);
		test_delay();
		led_off(LED4);
		test_delay();

//		puts("TB\r\n");

	/*	putc_ch0(*sram_loc);
		sram_loc++;

		if(sram_loc == 0x1000)
			sram_loc = 0;*/

	}
}
