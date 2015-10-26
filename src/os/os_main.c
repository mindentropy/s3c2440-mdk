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
#include "nand.h"
#include "sd_mmc.h"
#include "lcd.h"
#include "rtc.h"
#include "adc_ts.h"
#include "ac97.h"
#include "usb_host_controller.h"
#include "reg_dump.h"


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


void dump_cpu_info()
{
	uart_puts(UART0_BA,"CPU_ID:");
	print_hex_uart(UART0_BA,get_cpu_id());
}


void blink_leds(uint32_t leds) 
{
	led_on(leds);
	test_delay();
	led_off(leds);
	test_delay();
}


void last_boot_cause() 
{
	uart_puts(UART0_BA,"Last boot cause : ");
	switch(get_last_boot_status()) {
		case WDTRST:
			uart_puts(UART0_BA,"WDT reset\r\n");
			break;
		case SLEEPRST:
			uart_puts(UART0_BA,"Sleep reset\r\n");
			break;
		case PWRST:
			uart_puts(UART0_BA,"Power reset\r\n");
			break;
		default:
			uart_puts(UART0_BA,"Unknown cause of reset\r\n");
			break;
	}
}


int main(void) {
	/* Note : Do not put any operations above this */
	/* Disable watchdog.*/
//	unsigned char *sram_loc;

	disable_watchdog(WT_BA); 

	disable_all_interrupts(INT_BA);
	disable_all_interrupt_subservice(INT_BA);

	set_clk_dbg_port();
	init_clock();
	//init_uart0();
	init_uart(UART0_BA);

	//puts("TB\r\n");

	//apb_clk_enable_gpio();
	apb_clk_enable(CLK_BASE_ADDR,CLK_GPIO);

	init_spkr();
	init_led();
	led_off(LED4|LED3|LED2|LED1);

	//sram_loc = 0;
	
	dump_clk();
	dump_cpu_info();
	dump_cache_info();
	mmu_init();

	nand_init();

	dump_nand_dbg();
	uart_puts(UART0_BA,"chipid : ");
	print_hex_uart(UART0_BA,get_gstatus_chipid());
	uart_puts(UART0_BA,"\r\n");
	last_boot_cause();

	uart_puts(UART0_BA,"MPLL : ");
	print_hex_uart(UART0_BA,get_mpll_clk());
	//init_lcd();

	init_sd_controller();
/* Without delay the led blink rate is 2MHz. */
	while(1) {
		blink_leds(LED1|LED4);
		//Test for interrupt --> Passed as it jumps to the interrupt handler.
	/*	__asm__ __volatile__ (
			"swi 0x123456\n\t"
		);*/
	//	uart_puts(UART0_BA,"TB\r\n");

	/*	putc_ch0(*sram_loc);
		sram_loc++;

		if(sram_loc == 0x1000)
			sram_loc = 0;*/

	}
}
