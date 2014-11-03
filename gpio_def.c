#include "common.h"
#include "gpio_def.h"


void set_gpio_clk_dbg()
{
	set_reg_params(GPHCON,(CLKOUT1|CLKOUT0));
}

void set_gpio_uart_ch0()
{
    //Set nCTS0 GPH0
	set_reg_params(GPHCON,nCTS0|nRTS0|TXD0|RXD0);
}
