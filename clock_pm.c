#include "clock_pm.h"


void enable_apb_clk(unsigned int peripheral_clk)
{
	unsigned int val = 0;

	readreg32(CLKCON,val);
	set_bits(val,CLK_UART0);
	writereg32(CLKCON,val);
}

