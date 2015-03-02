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


uint32_t read_nand_id()
{
	send_nand_cmd(CMD_READ_ID);
	while(!get_RnB_status())
	{
		uart_puts(UART0_BA,"NAND Busy\n");
	}

	send_nand_addr(0x00);

	while(!get_RnB_status())
	{
		uart_puts(UART0_BA,"NAND Busy\n");
	}
	

	return read_nand_data();
}

void nand_init()
{
	set_nand_gpio_config_pins();
	apb_clk_enable(CLK_BASE_ADDR,CLK_NAND_FLASH_CNTRL);

	/* 
	 * TODO: Understand flash timing parameters
	 * Setting default to max.
	 *
	 * Tacls = 3
	 * Twrph0 = 7
	 * Twrph1 = 7
	 */

	set_tacls_twrph(3,7,7);

	enable_nand_flash_controller();
	
	nand_reset();
	
	uart_puts(UART0_BA,"NAND ID:");
	print_hex_uart(UART0_BA,read_nand_id());
}
