#ifndef CLOCK_PM_H_

#define CLOCK_PM_H_

#include "common.h"

/***********************************/

#define CLK_BASE_ADDR	0x4C000000U

#define LOCKTIME_OFF    0x00U
#define MPLLCON_OFF 	0x04U
#define UPLLCON_OFF 	0x08U
#define CLKCON_OFF 		0x0CU
#define CLKSLOW_OFF 	0x10U
#define CLKDIVN_OFF 	0x14U
#define CAMDIVN_OFF		0x18U

#define LOCKTIME_REG(BA) \
	HW_REG(BA,LOCKTIME_OFF)


#define MPLLCON_REG(BA) \
	HW_REG(BA,MPLLCON_OFF)

#define UPLLCON_REG(BA) \
	HW_REG(BA,UPLLCON_OFF)

#define CLKCON_REG(BA) \
	HW_REG(BA,CLKCON_OFF)

#define CLKSLOW_REG(BA) \
	HW_REG(BA,CLKSLOW_OFF)

#define CLKDIVN_REG(BA) \
	HW_REG(BA,CLKDIVN_OFF)

#define CAMDIVN_REG(BA) \
	HW_REG(BA,CAMDIVN_OFF)

/***********************************/


#define U_LTIME_MASK	(SHORT_MASK_MSB)
#define M_LTIME_MASK	(SHORT_MASK_LSB)


#define U_LTIME_SHIFT   (16U)
#define M_LTIME_SHIFT   (0U)

#define MDIV_MASK	(BIT19|BIT18|BIT17|BIT16|BIT15|BIT14|BIT13|BIT12)
#define PDIV_MASK	(BIT9|BIT8|BIT7|BIT6|BIT5|BIT4)
#define SDIV_MASK	(BIT1|BIT0)

#define MDIV_SHIFT  (12)
#define PDIV_SHIFT 	(4)
#define SDIV_SHIFT 	(0)


#define CLK_AC97				BIT20
#define CLK_CAMERA				BIT19
#define CLK_SPI					BIT18
#define CLK_IIS					BIT17
#define CLK_IIC					BIT16
#define CLK_ADC_TOUCH_SCREEN	BIT15
#define CLK_RTC					BIT14
#define CLK_GPIO				BIT13
#define CLK_UART2				BIT12
#define CLK_UART1				BIT11
#define CLK_UART0				BIT10
#define CLK_SDI					BIT9
#define CLK_PWMTIMER			BIT8
#define CLK_USB_DEV				BIT7
#define CLK_USB_HOST			BIT6
#define CLK_LCDC				BIT5
#define CLK_NAND_FLASH_CNTRL	BIT4
#define CLK_SLEEP				BIT3
#define CLK_IDLE				BIT2


#define apb_clk_enable(BA,CLK) \
	set_reg_params(CLKCON_REG(BA),CLK)


#define UCLK_ON		BIT7
#define MPLL_OFF	BIT5
#define SLOW_BIT	BIT4
#define SLOW_VAL	(BIT2|BIT1|BIT0)


#define DIVN_UPLL_MASK	BIT3

#define DIVN_UPLL_BY_1	0
#define DIVN_UPLL_BY_2  BIT3

#define HDIVN_MASK		(BIT2|BIT1)

#define HDIVN_FCLK_BY_1 0
#define HDIVN_FCLK_BY_2 (BIT1)
#define HDIVN_FCLK_BY_4 (BIT2)
#define HDIVN_FCLK_BY_3 (BIT2|BIT1)


#define PDIVN_MASK			BIT0
#define PDIVN_HCLK_BY_1		0
#define PDIVN_HCLK_BY_2		BIT0


#define DVS_EN		BIT12
#define HCLK4_HALF	BIT9
#define HCLK3_HALF	BIT8
#define CAMCLK_SEL	BIT4
#define CAMCLK_DIV	(BIT3|BIT2|BIT1|BIT0)

#define CLKOUT0_PIN BIT9
#define CLKOUT1_PIN BIT10

void init_clock();
void set_clk_dbg_port();
void enable_gpio_clk();
void enable_apb_clk(unsigned int peripheral_clk);

uint32_t get_mpll_clk(uint32_t BA);
uint32_t get_upll_clk(uint32_t BA);
uint32_t get_hclk(uint32_t BA);
uint32_t get_uclk(uint32_t BA);
uint32_t get_pclk(uint32_t BA);


#define set_clk_lock_time(BA,upll_lock_time,mpll_lock_time)\
		writereg32(LOCKTIME_REG(BA),((upll_lock_time)<<U_LTIME_SHIFT) | (mpll_lock_time))


#define set_clk_mpll(BA,mdiv,pdiv,sdiv) \
	writereg32(MPLLCON_REG(BA), \
							(((mdiv)<<MDIV_SHIFT)| \
							((pdiv)<<PDIV_SHIFT)| \
							((sdiv)<<SDIV_SHIFT)))

#define get_clk_pll_mdiv(PLL_REG) \
	(((readreg32(PLL_REG)) & MDIV_MASK) >> MDIV_SHIFT)

#define get_clk_pll_pdiv(PLL_REG) \
	(((readreg32(PLL_REG)) & PDIV_MASK) >> PDIV_SHIFT)

#define get_clk_pll_sdiv(PLL_REG) \
	(((readreg32(PLL_REG)) & SDIV_MASK) >> SDIV_SHIFT)

/*
 * Note:
 * ====
 *
 * FCLK -> To CPU.
 * HCLK -> AHB Peripherals.
 * PCLK -> USB Block.
 *
 */

/*
 * MPLL is fed to FCLK directly. 
 * Hence MPLL frequency equals FCLK
 */

#define get_fclk(BA) \
	(get_mpll_clk(BA))


#define set_clk_upll(BA,mdiv,pdiv,sdiv) \
	writereg32(UPLLCON_REG(BA), \
			(((mdiv)<<MDIV_SHIFT)| \
			((pdiv)<<PDIV_SHIFT)| \
			((sdiv)<<SDIV_SHIFT)))


#define set_clock_divn(BA,divn_upll,hdivn,pdivn) \
	writereg32(CLKDIVN_REG(BA), \
					(divn_upll) | (hdivn) | (pdivn))

#define get_clock_hdivn(BA) \
	(readreg32(CLKDIVN_REG(BA)) & HDIVN_MASK)

#define get_clock_pdivn(BA) \
	(readreg32(CLKDIVN_REG(BA)) & PDIVN_MASK)

#define get_clock_upll_divn(BA) \
	(readreg32(CLKDIVN_REG(BA)) & DIVN_UPLL_MASK)

#define clear_slow_clock(BA) do { \
	clear_reg_params(CLKSLOW_REG(BA),SLOW_BIT); \
	clear_reg_params(CLKSLOW_REG(BA),UCLK_ON); \
	clear_reg_params(CLKSLOW_REG(BA),MPLL_OFF); \
	} while(0)


#define set_gpio_clk_dbg() \
	set_reg_params(GPCON_REG(GPH_BA),(CLKOUT1|CLKOUT0))

#endif
