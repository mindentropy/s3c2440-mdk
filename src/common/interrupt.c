#include "interrupt.h"


void set_interrupt_mode(unsigned int_line)
{
	set_reg_params(INTMOD,int_line);
}

void set_fiq_mode(unsigned int_line)
{
	clear_reg_params(INTMOD,int_line);
}

void enable_interrupt_service(unsigned int_mask)
{
	clear_reg_params(INTMSK,int_mask);
}

void disable_interrupt_service(unsigned int_mask)
{
	set_reg_params(INTMSK,int_mask);
}

unsigned get_interrupt_pending_status(unsigned interrupt_line)
{
	return (readreg32(INTPND) & interrupt_line);
}

unsigned get_interrupt_subservice_pending_status(unsigned interrupt_line)
{
	return (readreg32(SUBSRCPND) & interrupt_line);
}

void enable_interrupt_sub_service(unsigned int_mask)
{
	clear_reg_params(INTSUBMSK,int_mask);
}

void disable_interrupt_sub_service(unsigned int_mask)
{
	set_reg_params(INTSUBMSK,int_mask);
}

