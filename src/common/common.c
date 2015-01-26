#include "common.h"

void set_reg_params(unsigned int reg,
					unsigned int regmask
					)
{

	writereg32(reg,setbits(readreg32(reg),regmask));
}

void clear_reg_params(unsigned int reg,
						unsigned int regmask)
{
	writereg32(reg,clearbits(readreg32(reg),regmask));
}
