#include "common.h"
#include "clock_pm.h"
#include "gpio_def.h"

void enable_apb_clk(unsigned int peripheral_clk)
{
	set_reg_params(CLKCON,peripheral_clk);
}

void enable_gpio_clk()
{
	set_reg_params(CLKCON,CLK_GPIO);
}

void set_mpll(unsigned int mdiv,
				unsigned int pdiv,
				unsigned int sdiv) 
{

	writereg32(MPLLCON,0x0007f021);
	/*writereg32(MPLLCON,
				(mdiv<<MDIV_SHIFT) | 
				(pdiv<<PDIV_SHIFT) | 
				(sdiv<<SDIV_SHIFT));*/

}


void set_upll(unsigned int mdiv,
				unsigned int pdiv,
				unsigned int sdiv) 
{
	
	writereg32(UPLLCON,
				(mdiv<<MDIV_SHIFT) | 
				(pdiv<<PDIV_SHIFT) | 
				(sdiv<<SDIV_SHIFT));
}


void set_clk_divn(unsigned int divn_upll,
							unsigned int hdivn,
							unsigned int pdivn)
{
	
	writereg32(CLKDIVN,0x00000005);
	//writereg32(CLKDIVN,divn_upll|hdivn|pdivn);
}


void set_clock_lock_time(unsigned short upll_lock_time,
					unsigned short mpll_lock_time)
{
	writereg32(REG_LOCKTIME,
		((upll_lock_time << U_LTIME_SHIFT)|(mpll_lock_time)));
}
							
void set_clk_dbg_port()
{
	set_reg_params(MISCCR,(CLK_SEL1_PCLK));
}

void init_clock()
{
	unsigned int i = 0, j = 0;

//	set_clock_lock_time(1000,1000);

	disable_pull_up(GPHUP,BIT10|BIT9);

	/* Set upll first, use 7 "nops" delay and then set mpll */
	set_upll(56,2,2); //48 Mhz.

	for(j = 0; j<10; j++) 
		for(i = 0; i<10;i++)
			;

	/*__asm__(
			"mov r0,r0\n\t"
			"mov r0,r0\n\t"
			"mov r0,r0\n\t"
			"mov r0,r0\n\t"
			"mov r0,r0\n\t"
			"mov r0,r0\n\t"
			"mov r0,r0\n\t"
			);*/

	
	//set_mpll(127,2,1); //405 Mhz

	set_clk_divn(DIVN_UPLL_BY_1,
				HDIVN_FCLK_BY_4,
				PDIVN_HCLK_BY_2);
}
