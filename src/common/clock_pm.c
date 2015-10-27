#include "common.h"
#include "clock_pm.h"
#include "gpio_def.h"
#include "board_config.h"

							
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


uint32_t get_mpll_clk(uint32_t BA)
{
	uint32_t m,p,s;
	
	m = get_clk_pll_mdiv(MPLLCON_REG(BA)) + 8;
	p = get_clk_pll_pdiv(MPLLCON_REG(BA)) + 2;
	s = get_clk_pll_sdiv(MPLLCON_REG(BA));

	return ((m * S3C_CLOCK_REFERENCE) * 2)/(p * (1<<s));
}


uint32_t get_upll_clk(uint32_t BA)
{
	
	uint32_t m,p,s;
	
	m = get_clk_pll_mdiv(UPLLCON_REG(BA)) + 8;
	p = get_clk_pll_pdiv(UPLLCON_REG(BA)) + 2;
	s = get_clk_pll_sdiv(UPLLCON_REG(BA));

	return (m * S3C_CLOCK_REFERENCE)/(p * (1<<s));
}

/*
 * Note:
 * ====
 *
 * FCLK -> To CPU.
 * HCLK -> AHB Peripherals.
 * PCLK -> USB Block.
 *
 */

uint32_t get_hclk(uint32_t BA)
{
	uint32_t fclk = get_fclk(BA);

	switch(get_clock_hdivn(BA)) {
		case HDIVN_FCLK_BY_1:
			return fclk;
		case HDIVN_FCLK_BY_2:
			return (fclk >> 1);
		case HDIVN_FCLK_BY_4:
			//TODO: CAMDIVN conditon check pending.
			return (fclk >> 2);
		case HDIVN_FCLK_BY_3:
			//TODO: CAMDIVN conditon check pending.
			return (fclk / 3);
	}

	return fclk;
}

uint32_t get_pclk(uint32_t BA)
{
	uint32_t fclk = get_fclk(BA);

	switch(get_clock_pdivn(BA)) {
		case PDIVN_HCLK_BY_1:
			return fclk;
		case PDIVN_HCLK_BY_2:
			return fclk >> 1;
	}

	return fclk;
}

uint32_t get_uclk(uint32_t BA)
{
	uint32_t uclk = get_upll_clk(BA);

	switch(get_clock_upll_divn(BA)) {
		case DIVN_UPLL_BY_1:
			return uclk;
		case DIVN_UPLL_BY_2:
			return uclk >> 2;
	}

	return uclk;
}

/*
 * Clock Source Selection
 * ======================
 *
 * Combination mode control pins OM3 and OM2 OM[3:2] provide the selection of the clock source
 * for S3C2440. Please see pg 7-2 Table 7-1 for more details.
 *
 * The clock selection for the friendlyARM board is OM[3:2] = 00. This shown in the schematic 
 * as both grounded. The setting indicates that both Main clock source and USB clock source are
 * driven from the crystal.
 *
 * The main clock source comes from an external crystal XTIpll or EXTCLK. The clock generator is
 * connected to an external crystal, and has 2 PLL's which generate high frequency clock for the
 * S3C2440.
 *
 * In the schematic of friendlyARM the crystal is a 12Mhz crystal connected to XTIpll and XTOpll.
 *
 */

void init_clock()
{
	//unsigned int i = 0, j = 0;

	//disable_pull_up(GPHUP,CLKOUT0_PIN|CLKOUT1_PIN);
	disable_pull_up(GPUP_REG(GPH_BA),CLKOUT0_PIN|CLKOUT1_PIN);

	set_clk_lock_time(CLK_BASE_ADDR,
						0xFFFFU,0xFFFFU);

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
