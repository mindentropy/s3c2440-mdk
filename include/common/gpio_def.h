#ifndef GPIO_DEF_H_

#define GPIO_DEF_H_

#include "common.h"

#define GPIO_BA 	0x56000000

#define GPA_OFF 	0x00
#define GPB_OFF 	0x10
#define GPC_OFF 	0x20
#define GPD_OFF 	0x30
#define GPE_OFF 	0x40
#define GPF_OFF 	0x50
#define GPG_OFF 	0x60
#define GPH_OFF 	0x70
#define GPJ_OFF 	0xD0

#define GPA_BA  HW_REG(GPIO_BA,GPA_OFF)
#define GPB_BA  HW_REG(GPIO_BA,GPB_OFF)
#define GPC_BA  HW_REG(GPIO_BA,GPC_OFF)
#define GPD_BA  HW_REG(GPIO_BA,GPD_OFF)
#define GPE_BA  HW_REG(GPIO_BA,GPE_OFF)
#define GPF_BA  HW_REG(GPIO_BA,GPF_OFF)
#define GPG_BA  HW_REG(GPIO_BA,GPG_OFF)
#define GPH_BA  HW_REG(GPIO_BA,GPH_OFF)
#define GPJ_BA  HW_REG(GPIO_BA,GPJ_OFF)

#define GPCON   	0x00
#define GPDAT   	0x04
#define GPUP    	0x08
#define MISCCR_OFF 	0x80

#define GSTATUS0 	0xAC
#define GSTATUS1 	0xB0
#define GSTATUS2 	0xB4
#define GSTATUS3 	0xB8
#define GSTATUS4 	0xBC

#define GSTATUS_REG(STATUS_OFF)\
	HW_REG(GPIO_BA,STATUS_OFF)

#define GPCON_REG(BA) \
		HW_REG((BA),GPCON)

#define GPDAT_REG(BA) \
		HW_REG((BA),GPDAT)

#define GPUP_REG(BA) \
		HW_REG((BA),GPUP)


#define MISCCR_REG() \
		((GPIO_BA) + MISCCR_OFF)


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

/* GSTATUS0 */
#define nWAIT_PIN 		(BIT3)
#define NCON_PIN		(BIT2)
#define RnB_PIN			(BIT1)
#define BATT_FLT_PIN 	(BIT0)

#define get_gstatus_nwait() \
	((readreg32(GSTATUS_REG(GSTATUS0)))&nWAIT_PIN)

#define get_gstatus_ncon() \
	((readreg32(GSTATUS_REG(GSTATUS0)))&NCON_PIN)

#define get_gstatus_rnb() \
	((readreg32(GSTATUS_REG(GSTATUS0)))&RnB_PIN)

#define get_gstatus_batt_flt() \
	((readreg32(GSTATUS_REG(GSTATUS0)))&BATT_FLT_PIN)

/* GSTATUS1 */
#define CHIP_ID     (BIT0) //TODO: Correction needed in the datasheet.


#define get_gstatus_chipid() \
	(readreg32(GSTATUS_REG(GSTATUS1)))

/* GSTATUS2 */
#define WDTRST 		(BIT2)
#define SLEEPRST 	(BIT1)
#define PWRST 		(BIT0)

#define LAST_BOOT_MASK (BIT2|BIT1|BIT0)


#define get_last_boot_status() \
	((readreg32(GSTATUS_REG(GSTATUS2))) & LAST_BOOT_MASK)

#define get_boot_reset_status_wdt() \
	((readreg32(GSTATUS_REG(GSTATUS2))) & WDTRST)

#define get_boot_reset_status_sleep() \
	((readreg32(GSTATUS_REG(GSTATUS2))) & SLEEPRST)

#define get_boot_reset_status_power() \
	((readreg32(GSTATUS_REG(GSTATUS2))) & PWRST)

#define disable_pull_up(port_reg,linemask) \
	set_reg_params(port_reg,linemask)

//void set_gpio_clk_dbg();
//void set_gpio_uart_ch0();

#define set_gpio_con(BA,param) \
	set_reg_params(GPCON_REG(BA),param)

#endif
