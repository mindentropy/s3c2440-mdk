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
#include "gpio_button.h"


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

void blink_leds(uint32_t leds)
{
	led_on(leds);
	test_delay();
	led_off(leds);
	test_delay();
}

void dump_chip_id()
{
	uart_puts(UART0_BA,"chipid : ");
	print_hex_uart(UART0_BA,get_gstatus_chipid());
	uart_puts(UART0_BA,"\r\n");
}

/*
char buff[20];
uint8_t result,i;
*/

int main(void) {
	/* Note : Do not put any operations above this */
	/* Disable watchdog.*/
//	unsigned char *sram_loc;

	disable_watchdog(WT_BA); 

	mask_all_interrupts(INT_BA);
	mask_all_interrupt_subservice(INT_BA);

	init_clock();
	mmu_init();
	apb_clk_enable(CLK_BASE_ADDR,CLK_GPIO);
	set_clk_dbg_port();
	init_interrupt_controller();
	//init_uart0();

	//puts("TB\r\n");

	//apb_clk_enable_gpio();

	nand_init();
	init_uart(UART0_BA);

	init_spkr();
	init_led();
	init_gpio_button();

	led_off(LED4|LED3|LED2|LED1);

	//sram_loc = 0;
	
/*	
	dump_clk();
	dump_cpu_info();
	dump_cache_info();


	dump_nand_dbg();
	dump_chip_id();
	last_boot_cause();
*/

	//init_lcd();
/*	uart_puts(UART0_BA,"BRDIV:");
	print_hex_uart(UART0_BA,get_uart_brdiv(UART0_BA,BAUD_115200));
*/

	//init_sd_controller();

/* Without delay the led blink rate is 2MHz. */

	//putc(UART0_BA,'c');
	//dump_interrupt_reg();
	

	while(1) {

/*		if(is_btn_K1_pressed(GPG_BA)) {
			print_hex_uart(UART0_BA,readreg32(EINTPEND_REG(GPIO_BA)));
		}*/

		blink_leds(LED1|LED4);

/*
		mask_interrupt_service(INT_BA,INT_UART0);
		uart_int_puts(UART0_BA,"test\r\n",6);
		unmask_interrupt_service(INT_BA,INT_UART0);
*/

/*
		mask_interrupt_service(INT_BA,INT_UART0);
		result = uart_getbuff(buff,20);
		unmask_interrupt_service(INT_BA,INT_UART0);


		for(i = 0;i<result;i++) 
			putc(UART0_BA,buff[i]);
*/
		

//
		//Test for interrupt --> Passed as it jumps to the interrupt handler.
		
 		/*__asm__ __volatile__ (
			"swi 0x123456\n\t"
		);*/


	//	uart_puts(UART0_BA,"TB\r\n");

	/*	putc_ch0(*sram_loc);
		sram_loc++;

		if(sram_loc == 0x1000)
			sram_loc = 0;*/

	}
}
