#ifndef CLOCK_POWER_CTRL_H_
#define CLOCK_POWER_CTRL_H_

struct clock_regs {
	unsigned int LOCKTIME;
	unsigned int MPLLCON;
	unsigned int UPLLCON;
	unsigned int CLKCON;
	unsigned int CLKSLOW;
	unsigned int CLKDIVN;
	unsigned int CAMDIVN;
};

#endif
