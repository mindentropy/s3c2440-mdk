#include "common.h"
#include "gpio_def.h"
#include "board_config.h"
#include "usb.h"

void init_usb()
{
	set_reg_bits(MISCCR_REG(),BIT3);
}
