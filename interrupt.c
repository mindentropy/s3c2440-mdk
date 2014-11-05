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

void disable_all_interrupts()
{
	writereg32(INTMSK,0xFFFFFFFF);
}

void enable_all_interrupts()
{
	writereg32(INTMSK,0x0);
}

unsigned get_interrupt_pending_status(unsigned interrupt_line)
{
	unsigned int val = 0;

	readreg32(INTPND,val);

	return (val & interrupt_line);
}

unsigned get_interrupt_subservice_pending_status(unsigned interrupt_line)
{
	unsigned int val = 0;
	readreg32(SUBSRCPND,val);

	return (val & interrupt_line);
}

void enable_interrupt_sub_service(unsigned int_mask)
{
	clear_reg_params(INTSUBMSK,int_mask);
}

void disable_interrupt_sub_service(unsigned int_mask)
{
	set_reg_params(INTSUBMSK,int_mask);
}

void disable_all_interrupt_subservice()
{
	writereg32(INTSUBMSK,0xFFFF);
}

void enable_all_interrupt_subservice()
{
	writereg32(INTSUBMSK,0);
}

