#ifndef WDT_CTRL_H_
#define WDT_CTRL_H_

struct watchdog_regs {
	unsigned int WTCON;
	unsigned int WTDAT;
	unsigned int WTCNT;
};

#endif
