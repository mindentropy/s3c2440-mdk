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

	/* GPC5 bit control for USB device */

	set_regs_value(GPCON_REG(GPC_BA),
					(3U<<10),
					(1U<<10));

    /* Set GPC5 pull-up bit for disabling */
	set_reg_bits(GPUP_REG(GPC_BA),USB_EN_GPIO);

	/* Clear GPC bit5 DAT for disabling USB_EN */
	clear_reg_bits(GPDAT_REG(GPC_BA),USB_EN_GPIO);
}
