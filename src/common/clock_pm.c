#include "common.h"
#include "clock_pm.h"
#include "gpio_def.h"

							
void set_clk_dbg_port()
{
	set_gpio_clk_dbg();
	//set_reg_params(MISCCR,(CLK_SEL1_HCLK|CLK_SEL0_MPLL_INPUT_XTAL));
	
	/*set_reg_params(MISCCR,BIT8);
	clear_reg_params(MISCCR,BIT10|BIT9);*/
	//set_reg_params(MISCCR,BIT5|BIT4);
	set_reg_params(MISCCR_REG(),(BIT5|BIT4));
	clear_reg_params(MISCCR_REG(),(BIT6));
}

void init_clock()
{
	//unsigned int i = 0, j = 0;

	//disable_pull_up(GPHUP,CLKOUT0_PIN|CLKOUT1_PIN);
	disable_pull_up(GPUP_REG(GPH_BA),CLKOUT0_PIN|CLKOUT1_PIN);

	set_clk_lock_time(CLK_BASE_ADDR,
						0xFFFF,0xFFFF);

	/* 
	 *------
	 * NOTE
	 *------
	 *
	 * Set the divider register first. Example code from
	 * myled 2440init.s
	 *
	 */

	/* 	
	 *  FCLK = 405 MHz.
	 *  HCLK = 405/4 = 101MHz
	 *  PCLK = 405/8 = 50 Mhz
	 */

	set_clock_divn(CLK_BASE_ADDR,
					DIVN_UPLL_BY_1,
					HDIVN_FCLK_BY_4,
					PDIVN_HCLK_BY_2);

	/* 
	 * Set CPU to asynchronous mode.
	 * See Pg 2-11 of ARM920T Reference and Chapter 5.
	 * 
	 * Also see page 7-9. S3C2440 does not support 
	 * synchronous bus mode.
	 */
	__asm__ __volatile__(
		"mrc p15,0,r1,c1,c0,0\n\t"
		"orr r1,r1,#0xC0000000\n\t"
		"mcr p15,0,r1,c1,c0,0\n\t"
		: /* No output */
		: /* No input */
		: "r1" /* r1 clobbered */
		);

	/* Set upll first, use 7 "nops" delay and then set mpll */

	set_clk_upll(CLK_BASE_ADDR,0x38,0x2,0x2); //48 Mhz.
    
	__asm__ __volatile__(
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

	
	set_clk_mpll(CLK_BASE_ADDR,0x7f,0x2,0x1); //405 Mhz

	__asm__ __volatile__(
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

	clear_slow_clock(CLK_BASE_ADDR);
}
