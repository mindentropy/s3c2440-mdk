#ifndef GPIO_DEF_H_

#define GPIO_DEF_H_

#include "common.h"

#define GPACON	0x56000000
#define GPADAT	0x56000004


#define GPBCON	0x56000010
#define GPBDAT	0x56000014
#define GPBUP	0x56000018

#define GPCCON	0x56000020
#define GPCDAT	0x56000024
#define GPCUP	0x56000028


#define GPDCON	0x56000030
#define GPDDAT	0x56000034
#define GDPUP	0x56000038

#define GPECON	0x56000040
#define	GPEDAT	0x56000044
#define GPEUP	0x56000048

#define GPFCON	0x56000050
#define	GPFDAT	0x56000054
#define GPFUP	0x56000058

#define GPGCON	0x56000060
#define GPGDAT	0x56000064
#define GPGUP	0x56000068

#define GPHCON	0x56000070
#define GPHDAT	0x56000074
#define GPHUP	0x56000078

#define GPJCON	0x560000d0
#define GPJDAT	0x560000d4
#define GPJUP	0x560000d8


#define MISCCR  0x56000080

#define CLK_SEL1 		(BIT10|BIT9|BIT8)
#define CLK_SEL1_MPLL  	(0)
#define CLK_SEL1_UPLL  	(BIT8)
#define CLK_SEL1_RTC 	(BIT9)
#define CLK_SEL1_HCLK 	(BIT9|BIT8)
#define CLK_SEL1_PCLK 	(BIT10)
#define CLK_SEL1_DCLK1 	(BIT10|BIT8)

#define CLK_SEL0_MPLL_INPUT_XTAL  	(0)
#define CLK_SEL0_UPLL_OUTPUT  		(BIT4)
#define CLK_SEL0_FCLK 				(BIT5)
#define CLK_SEL0_HCLK 				(BIT5|BIT4)
#define CLK_SEL0_PCLK 				(BIT6)
#define CLK_SEL0_DCLK0 				(BIT6|BIT4)

#define nCTS0 	((BIT1) & (~BIT0))
#define nRTS0 	((BIT3) & (~BIT2))
#define TXD0	((BIT5) & (~BIT4))
#define RXD0	((BIT7) & (~BIT6))

#define CLKOUT0 ((BIT19) & (~BIT18))
#define CLKOUT1 ((BIT21) & (~BIT20))


#define LED1_GPIO_OUT ((~BIT11) & (BIT10)) //GPB5
#define LED2_GPIO_OUT ((~BIT13) & (BIT12)) //GPB6
#define LED3_GPIO_OUT ((~BIT15) & (BIT14)) //GPB7
#define LED4_GPIO_OUT ((~BIT17) & (BIT16)) //GPB8

#define SPKR_GPIO_OUT ((~BIT1) & (BIT0)) //GPB0
#define SPKR_GPIO_PIN (BIT0)

#define disable_pull_up(port_reg,linemask) \
	set_reg_params(port_reg,linemask)

void set_gpio_clk_dbg();
void set_gpio_uart_ch0();

#endif
