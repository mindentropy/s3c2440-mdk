#ifndef CLOCK_PM_H_

#define CLOCK_PM_H_

#define REG_LOCKTIME	0x4C000000

#define U_LTIME_MASK	(0xFFFF << 16)
#define M_LTIME_MASK	(0xFFFF)


#define MPLLCON		0x4C000004
#define UPLLCON		0x4C000008

#define MDIV_MASK	0xFF000
#define PDIV_MASK	0x3F0
#define SDIV_MASK	0x1

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


#define CLKSLOW	0x4C000010

#define UCLK_ON		BIT7
#define MPLL_OFF	BIT5
#define SLOW_BIT	BIT4
#define SLOW_VAL	(BIT2|BIT1|BIT0)

#define CLKDIVN	0x4C000014

#define DIVN_UPLL	BIT3
#define HDIVN		(BIT2|BIT1)
#define PDIVN		BIT0

#define CAMDIVN	0x4C000018

#define DVS_EN		BIT12
#define HCLK4_HALF	BIT9
#define HCLK3_HALF	BIT8
#define CAMCLK_SEL	BIT4
#define CAMCLK_DIV	(BIT3|BIT2|BIT1|BIT0)




#endif
