#include "common.h"
#include "clock_pm.h"
#include "gpio_def.h"

void enable_apb_clk(unsigned int peripheral_clk)
{
	set_reg_params(CLKCON,peripheral_clk);
}

void set_mpll(unsigned int mdiv,
				unsigned int pdiv,
				unsigned int sdiv) 
{
	unsigned val = 0;
	//readreg32(MPLLCON,val);
	//writereg32(MPLLCON,val);
	
	
	//writereg32(MPLLCON,0x00096030);
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
/*	writereg32(REG_LOCKTIME,
		((upll_lock_time << U_LTIME_SHIFT)|(mpll_lock_time)));*/
	writereg32(REG_LOCKTIME,0xFFFFFFFF);
}

void clear_slow_clk()
{
	clear_reg_params(CLKSLOW,BIT4);
}
							
void set_clk_dbg_port()
{
	set_gpio_clk_dbg();
	//set_reg_params(MISCCR,(CLK_SEL1_HCLK|CLK_SEL0_MPLL_INPUT_XTAL));
	
	/*set_reg_params(MISCCR,BIT8);
	clear_reg_params(MISCCR,BIT10|BIT9);*/
	//set_reg_params(MISCCR,BIT5|BIT4);
	set_reg_params(MISCCR,(BIT5|BIT4));
	clear_reg_params(MISCCR,(BIT6));
}

void init_clock()
{
	unsigned int i = 0, j = 0;


	disable_pull_up(GPHUP,CLKOUT0_PIN|CLKOUT1_PIN);

	set_clock_lock_time(0xFFFF,0xFFFF);


	/* 
	 * Set the divider register first. Example code from
	 * myled 2440init.s
	 */

	set_clk_divn(DIVN_UPLL_BY_1,
				HDIVN_FCLK_BY_4,
				PDIVN_HCLK_BY_2);

	/* Set upll first, use 7 "nops" delay and then set mpll */
	set_upll(56,2,2); //48 Mhz.

    
	//for(i = 0;i<50;i++) {
		__asm__(
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				"mov r0,r0\n\t"
				);
	//}

	
	set_mpll(127,2,1); //405 Mhz

	clear_slow_clk();

}
