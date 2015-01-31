#ifndef CLOCK_PM_H_

#define CLOCK_PM_H_

#include "common.h"

/***********************************/

#define CLK_BASE_ADDR	0x4C000000

#define LOCKTIME_OFF    0x00
#define MPLLCON_OFF 	0x04
#define UPLLCON_OFF 	0x08
#define CLKCON_OFF 		0x0C
#define CLKSLOW_OFF 	0x10
#define CLKDIVN_OFF 	0x14
#define CAMDIVN_OFF		0x18

#define LOCKTIME_REG(CLK_BA) \
	HW_REG(CLK_BA,LOCKTIME_OFF)


#define MPLLCON_REG(CLK_BA) \
	HW_REG(CLK_BA,MPLLCON_OFF)

#define UPLLCON_REG(CLK_BA) \
	HW_REG(CLK_BA,UPLLCON_OFF)

#define CLKCON_REG(CLK_BA) \
	HW_REG(CLK_BA,CLKCON_OFF)

#define CLKSLOW_REG(CLK_BA) \
	HW_REG(CLK_BA,CLKSLOW_OFF)

#define CLKDIVN_REG(CLK_BA) \
	HW_REG(CLK_BA,CLKDIVN_OFF)

#define CAMDIVN_REG(CLK_BA) \
	HW_REG(CLK_BA,CAMDIVN_OFF)

/***********************************/

#define REG_LOCKTIME	0x4C000000

#define U_LTIME_MASK	(SHORT_MASK_MSB)
#define M_LTIME_MASK	(SHORT_MASK_LSB)


#define U_LTIME_SHIFT   (16)
#define M_LTIME_SHIFT   (0)

#define MPLLCON		0x4C000004
#define UPLLCON		0x4C000008

#define MDIV_MASK	(BIT19|BIT18|BIT17|BIT16|BIT15|BIT14|BIT13|BIT12)
#define PDIV_MASK	(BIT9|BIT8|BIT7|BIT6|BIT4)
#define SDIV_MASK	(BIT1|BIT0)

#define MDIV_SHIFT  (12)
#define PDIV_SHIFT 	(4)
#define SDIV_SHIFT 	(0)

#define CLKCON	0x4C00000C

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


#define apb_clk_enable(CLK_BA,CLK) \
	set_reg_params(CLKCON_REG(CLK_BA),CLK)

#define apb_clk_enable_uart0() \
	enable_apb_clk(CLK_UART0)

#define apb_clk_enable_uart1() \
	enable_apb_clk(CLK_UART1)

#define apb_clk_enable_uart2() \
	enable_apb_clk(CLK_UART2)
	
#define apb_clk_enable_gpio() \
	enable_apb_clk(CLK_GPIO)

#define CLKSLOW	0x4C000010

#define UCLK_ON		BIT7
#define MPLL_OFF	BIT5
#define SLOW_BIT	BIT4
#define SLOW_VAL	(BIT2|BIT1|BIT0)

#define CLKDIVN	0x4C000014

#define DIVN_UPLL		BIT3

#define DIVN_UPLL_BY_1	0
#define DIVN_UPLL_BY_2  BIT3

#define HDIVN			(BIT2|BIT1)

#define HDIVN_FCLK_BY_1 0
#define HDIVN_FCLK_BY_2 (BIT1)
#define HDIVN_FCLK_BY_4 (BIT2)
#define HDIVN_FCLK_BY_3 (BIT2|BIT1)


#define PDIVN				BIT0
#define PDIVN_HCLK_BY_1		0
#define PDIVN_HCLK_BY_2		BIT0


#define CAMDIVN	0x4C000018

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


#define set_clk_lock_time(CLK_BA,upll_lock_time,mpll_lock_time)\
		writereg32(LOCKTIME_REG(CLK_BA),((upll_lock_time)<<U_LTIME_SHIFT) | (mpll_lock_time))


#define set_clk_mpll(CLK_BA,mdiv,pdiv,sdiv) \
	writereg32(MPLLCON_REG(CLK_BA), \
							(((mdiv)<<MDIV_SHIFT)| \
							((pdiv)<<PDIV_SHIFT)| \
							((sdiv)<<SDIV_SHIFT))

#define set_clk_upll(CLK_BA,mdiv,pdiv,sdiv) \
	writereg32(UPLLCON_REG(CLK_BA), \
					(((mdiv)<<MDIV_SHIFT)| \
					((pdiv)<<PDIV_SHIFT)| \
					((sdiv)<<SDIV_SHIFT))


#define set_clock_divn(CLK_BA,divn_upll,hdivn,pdivn) \
	writereg32(CLKDIVN_REG(CLK_BA), \
					(divn_upll) | (hdivn) | (pdivn))
				

#define clear_slow_clock(CLK_BA) do { \
	clear_reg_params(CLKSLOW_REG(CLK_BA),SLOW_BIT); \
	clear_reg_params(CLKSLOW_REG(CLK_BA),UCLK_ON); \
	clear_reg_params(CLKSLOW_REG(CLK_BA),MPLL_OFF); \
	} while(0)


#endif
