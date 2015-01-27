#ifndef CLOCK_POWER_CTRL_H_
#define CLOCK_POWER_CTRL_H_

#include <stdint.h>

struct clk_regs {
	uint32_t LOCKTIME;
	uint32_t MPLLCON;
	uint32_t UPLLCON;
	uint32_t CLKCON;
	uint32_t CLKSLOW;
	uint32_t CLKDIVN;
	uint32_t CAMDIVN;
};

#endif
