#include "nand.h"
#include "gpio_def.h"
#include "clock_pm.h"
#include "uart_util.h"

/*
 * NAND driver will be written for Samsung K9F2G08U0B -> 256MB NAND Flash (Old mini2440) 0xECDA109544 ID 0x9510DAEC
 * NAND driver will be written for Samsung K9K8G08U0D SCB0 -> 1GB NAND Flash (New mini2440) ID 0x9551D3EC
 */

void set_nand_gpio_config_pins()
{
	clear_reg_params(GPCON_REG(GPG_BA),NAND_GPG13_INPUT);
	clear_reg_params(GPCON_REG(GPG_BA),NAND_GPG14_INPUT);
	clear_reg_params(GPCON_REG(GPG_BA),NAND_GPG15_INPUT);

	/* Clear pull up */
	set_reg_params(GPUP_REG(GPG_BA),
								NAND_MEM_PG_CAP_SEL_PIN
								|NAND_MEM_ADDR_CYCL_SEL_PIN
								|NAND_MEM_BUS_WIDTH_SEL_PIN);
}


void wait_until_free()
{
	while(!get_RnB_status())
	{
		uart_puts(UART0_BA,"NAND Busy\n");
	}
}

uint32_t read_nand_id()
{
	send_nand_cmd(CMD_READ_ID);

	wait_until_free();

	send_nand_addr(0x00);

	wait_until_free();

	return read_nand_data();
}


void nand_page_read(uint32_t addr)
{
	send_nand_cmd(CMD_READ_PAGE);

	wait_until_free();

	send_nand_addr(0x00);
	send_nand_addr(0x00);
	send_nand_addr(0x00);
	send_nand_addr(0x00);
	send_nand_addr(0x01);
	
	wait_until_free();

	send_nand_cmd(CMD_READ_START);
}

uint32_t read_nand_page_data()
{
	wait_until_free();
	return read_nand_data();
}

/*
 * NAND Init timing calculation explanation:
 * =========================================
 *
 * All credits go to Juergen Borleis of Pengutronix for the below explanation.
 *
 * Twrph0 is the "setup time", Twrph1 is the "hold time" for the data, command and address. 
 * Tacls is the additional time prior a command or address cycle.
 * Your NAND needs 12 ns for Tacls (they call it "CLE Setup Time" and "ALE Setup Time"), 
 * and 12 ns for Twrph0 (they call it "Data Setup Time") and 5 ns for 
 * Twrph1 (they call it "Data Hold Time") [1].
 * The S3C2440 manual shows an example[2]. To get 12 ns setup time you need to 
 * set Twrph0 to 1 which means two clocks at 100 MHz (= 20 ns), to get the 5 ns 
 * for Twrph1 you set it 0 which means one clock at 100 MHz (= 10 ns). For the 
 * Tacls your need to set it to two to get two clocks at 100 MHz (= 20 ns).  
 * For a read or write cycle this will result into 30 ns per byte which matches 
 * the 25 ns cycle time your NAND needs.
 *
 * [1] K9F2G08x0B.pdf, page 10, "AC Timing Characteristics for Command/Address/Data Input"
 * [2] Page 216, section 6-4, Figure 6-3 and Figure 6-4
 *
 * Source:
 * -------
 *   http://article.gmane.org/gmane.comp.embedded.ptxdist.oselas.community/2080 
 *
 */

void nand_init()
{
	int i = 0;
	set_nand_gpio_config_pins();
	apb_clk_enable(CLK_BASE_ADDR,CLK_NAND_FLASH_CNTRL);

	/* 
	 * Tacls = 3
	 * Twrph0 = 7
	 * Twrph1 = 7
	 */

	set_tacls_twrph(3,7,7);

	enable_nand_flash_controller();
	
	nand_reset();
	
	uart_puts(UART0_BA,"NAND ID:");
	print_hex_uart(UART0_BA,read_nand_id());
	print_hex_uart(UART0_BA,read_nand_data());

	nand_page_read(10);

	
	for(i = 0;i<8;i++) {
		print_hex_uart(UART0_BA,read_nand_page_data());
	}

}
