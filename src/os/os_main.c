#include "gpio_def.h"
#include "led.h"
#include "clock_pm.h"
#include "uart_util.h"
#include "wdt.h"
#include "spkr.h"
#include "interrupt.h"
#include "sdram.h"
#include "board_config.h"
#include "cpu.h"
#include "cache.h"
#include "mmu.h"

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


void dump_clk()
{
	uart_puts(UART0_BA,"************************\r\n");
	uart_puts(UART0_BA,"reg_locktime: ");
	print_hex_uart(UART0_BA,readreg32(REG_LOCKTIME));
	uart_puts(UART0_BA,"\r\n");
	uart_puts(UART0_BA,"mpllcon : ");
	print_hex_uart(UART0_BA,readreg32(MPLLCON));
	uart_puts(UART0_BA,"\r\n");
	uart_puts(UART0_BA,"upllcon : ");
	print_hex_uart(UART0_BA,readreg32(UPLLCON));
	uart_puts(UART0_BA,"\r\n");
	uart_puts(UART0_BA,"clkdivn: ");
	print_hex_uart(UART0_BA,readreg32(CLKDIVN));
	uart_puts(UART0_BA,"\r\n");
	uart_puts(UART0_BA,"clkslow: ");
	print_hex_uart(UART0_BA,readreg32(CLKSLOW));
	uart_puts(UART0_BA,"\r\n");
	uart_puts(UART0_BA,"clkcon: ");
	print_hex_uart(UART0_BA,readreg32(CLKCON));
	uart_puts(UART0_BA,"\r\n");

	uart_puts(UART0_BA,"************************\r\n");
}

void dump_cpu_info()
{
	print_hex_uart(UART0_BA,get_cpu_id());
}

void dump_cache_info()
{
	print_hex_uart(UART0_BA,get_cache_info());

	uart_puts(UART0_BA,"cache type:");
	print_hex_uart(UART0_BA,get_cache_type(get_cache_info()));
	uart_puts(UART0_BA,"\r\n");

	uart_puts(UART0_BA,"sbit:");
	print_hex_uart(UART0_BA,get_sbit(get_cache_info()));
	uart_puts(UART0_BA,"\r\n");
	
	uart_puts(UART0_BA,"dsize info:");
	print_hex_uart(UART0_BA,get_dsize_info(get_cache_info()));
	uart_puts(UART0_BA,"\r\n");

	uart_puts(UART0_BA,"isize info:");
	print_hex_uart(UART0_BA,get_isize_info(get_cache_info()));
	uart_puts(UART0_BA,"\r\n");

	uart_puts(UART0_BA,"size:");
	print_hex_uart(UART0_BA,get_size(get_dsize_info(get_cache_info())));
	uart_puts(UART0_BA,"\r\n");

	uart_puts(UART0_BA,"assoc:");
	print_hex_uart(UART0_BA,get_assoc(get_dsize_info(get_cache_info())));
	uart_puts(UART0_BA,"\r\n");

	uart_puts(UART0_BA,"mbit:");
	print_hex_uart(UART0_BA,get_mbit(get_dsize_info(get_cache_info())));
	uart_puts(UART0_BA,"\r\n");
	
	uart_puts(UART0_BA,"line len:");
	print_hex_uart(UART0_BA,get_line_len(get_dsize_info(get_cache_info())));
	uart_puts(UART0_BA,"\r\n");
}

void blink_leds(uint32_t leds) {
	led_on(leds);
	test_delay();
	led_off(leds);
	test_delay();
}

int main(void) {
	/* Note : Do not put any operations above this */
	/* Disable watchdog.*/
//	unsigned char *sram_loc;

	disable_watchdog(WT_BA); 

	disable_all_interrupts();
	disable_all_interrupt_subservice();

	set_clk_dbg_port();
	init_clock();
	//init_uart0();
	init_uart(UART0_BA);

	//puts("TB\r\n");

	//apb_clk_enable_gpio();
	apb_clk_enable(CLK_BA,CLK_GPIO);

	init_spkr();
	init_led();
	led_off(LED4|LED3|LED2|LED1);

	//sram_loc = 0;
	
	dump_clk();
	dump_cpu_info();
	dump_cache_info();
	mmu_init();
/* Without delay the led blink rate is 2MHz. */
	while(1) {
		blink_leds(LED1|LED4);
//		puts("TB\r\n");

	/*	putc_ch0(*sram_loc);
		sram_loc++;

		if(sram_loc == 0x1000)
			sram_loc = 0;*/

	}
}
