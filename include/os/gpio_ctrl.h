#ifndef GPIO_CTRL_H_
#define GPIO_CTRL_H_

struct gpio_regs {
	unsigned int GPCON;
	unsigned int GPDAT;
	unsigned int GPUP;
};

struct gpio_misc_regs {
	unsigned int MISCCR;
	unsigned int DCLKCON;
};

struct gpio_ext_int_regs {
	unsigned int EXTINT0;
	unsigned int EXTINT1;
	unsigned int EXTINT2;
};

struct gpio_ext_int_filter_regs {
	unsigned int EINTFLT0;
	unsigned int EINTFLT1;
	unsigned int EINTFLT2;
	unsigned int EINTFLT3;
};

#endif
