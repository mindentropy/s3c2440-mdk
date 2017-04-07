#include "common.h"
#include "gpio_def.h"
#include "board_config.h"
#include "clock_pm.h"
#include "usb.h"

void init_usb()
{
	clear_reg_bits(
			CLKCON_REG(CLK_BASE_ADDR),
			BIT6);
	
	set_reg_bits(
			CLKCON_REG(CLK_BASE_ADDR),
			BIT6);

	set_reg_bits(MISCCR_REG(),BIT3);
}
