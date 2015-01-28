#ifndef CLOCK_PM_H_

#define CLOCK_PM_H_

#include "common.h"

#define CLOCK_REG_BA 	0x4C000000

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

#endif
