#include "common.h"

void set_reg_params(unsigned int reg,
					unsigned int regmask
					)
{
	unsigned int val = 0;

	readreg32(reg,val);
	set_bits(val,regmask);
	writereg32(reg,val);
}

void clear_reg_params(unsigned int reg,
						unsigned int regmask)
{
	unsigned int val = 0;

	readreg32(reg,val);
	clear_bits(val,regmask);
	writereg32(reg,val);
}
