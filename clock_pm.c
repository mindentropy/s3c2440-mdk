#include "common.h"
#include "clock_pm.h"


void enable_apb_clk(unsigned int peripheral_clk)
{
	set_reg_params(CLKCON,CLK_UART0);
}


void set_mpll(unsigned int mdiv,
				unsigned int pdiv,
				unsigned int sdiv) 
{

	set_reg_params(MPLLCON,
					(mdiv<<MDIV_SHIFT) | 
					(pdiv<<PDIV_SHIFT) | 
					(sdiv<<SDIV_SHIFT));

}


void set_upll(unsigned int mdiv,
				unsigned int pdiv,
				unsigned int sdiv) 
{
	
	set_reg_params(UPLLCON,
					(mdiv<<MDIV_SHIFT) | 
					(pdiv<<PDIV_SHIFT) | 
					(sdiv<<SDIV_SHIFT));
}



void set_clk_divn(unsigned int divn_upll,
							unsigned int hdivn,
							unsigned int pdivn)
{
	set_reg_params(CLKDIVN,divn_upll|hdivn|pdivn);
}


void init_clock()
{
	
}
