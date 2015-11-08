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

#define GSTATUS_REG(STATUS_OFF) \
	HW_REG(GPIO_BA,STATUS_OFF)

#define GPCON_REG(BA) \
		HW_REG((BA),GPCON)

#define GPDAT_REG(BA) \
		HW_REG((BA),GPDAT)

#define GPUP_REG(BA) \
		HW_REG((BA),GPUP)


#define MISCCR_REG() \
		((GPIO_BA) + MISCCR_OFF)

/***** Clock GPIO Settings *****/
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
/*******************************/

//TODO: Suffix below with CONF.
/***** UART0 GPIO Settings *****/
#define nCTS0 	((BIT1) & (~BIT0))
#define nRTS0 	((BIT3) & (~BIT2))
#define TXD0	((BIT5) & (~BIT4))
#define RXD0	((BIT7) & (~BIT6))

#define CLKOUT0 ((BIT19) & (~BIT18))
#define CLKOUT1 ((BIT21) & (~BIT20))
/*******************************/

//TODO: Suffix below with CONF.
/***** LED GPIO Settings *****/
#define LED1_GPIO_OUT ((~BIT11) & (BIT10)) //GPB5
#define LED2_GPIO_OUT ((~BIT13) & (BIT12)) //GPB6
#define LED3_GPIO_OUT ((~BIT15) & (BIT14)) //GPB7
#define LED4_GPIO_OUT ((~BIT17) & (BIT16)) //GPB8
/****************************/

/***** LCD GPIO Settings *****/
#define LCD_PWR 		((BIT9|BIT8)) //GPG4

#ifdef MINI2440
#define LCD_GPIO_PWR_PIN 	(BIT4)
#endif //MINI2440
/*****************************/


/***** Speaker GPIO Settings *****/
#define SPKR_GPIO_OUT ((~BIT1) & (BIT0)) //GPB0

#ifdef MINI2440
#define SPKR_GPIO_PIN (BIT0)
#endif //MINI2440
/*********************************/

/***** SDIO GPIO Settings *****/

#define SDCLK_GPIO_CONF		((BIT11) & (~BIT10)) //GPE5
#define SDCMD_GPIO_CONF		((BIT13) & (~BIT12)) //GPE6
#define SDDAT0_GPIO_CONF 	((BIT15) & (~BIT14)) //GPE7
#define SDDAT1_GPIO_CONF 	((BIT17) & (~BIT16)) //GPE8
#define SDDAT2_GPIO_CONF 	((BIT19) & (~BIT18)) //GPE9
#define SDDAT3_GPIO_CONF  	((BIT21) & (~BIT20)) //GPE10

#ifdef MINI2440
#define SDCLK_GPIO_PIN 		(BIT5) //GPE5
#define SDCMD_GPIO_PIN		(BIT6) //GPE6
#define SDDAT0_GPIO_PIN 	(BIT7) //GPE7
#define SDDAT1_GPIO_PIN 	(BIT8) //GPE8
#define SDDAT2_GPIO_PIN 	(BIT9) //GPE9
#define SDDAT3_GPIO_PIN  	(BIT10) //GPE10
#endif //MINI2440
/******************************/


#define EINT4 				(BIT4)
#define EINT5 				(BIT5)
#define EINT6 				(BIT6)
#define EINT7 				(BIT7)
#define EINT8 				(BIT8)
#define EINT9 				(BIT9)
#define EINT10 				(BIT10)
#define EINT11 				(BIT11)
#define EINT12 				(BIT12)
#define EINT13 				(BIT13)
#define EINT14 				(BIT14)
#define EINT15 				(BIT15)
#define EINT16 				(BIT16)
#define EINT17 				(BIT17)
#define EINT18 				(BIT18)
#define EINT19 				(BIT19)
#define EINT20 				(BIT20)
#define EINT21 				(BIT21)
#define EINT22 				(BIT22)
#define EINT23 				(BIT23)


/******** GPIO Button **********/
#ifdef MINI2440

#define K1_GPIO_PIN_POS		0
#define K2_GPIO_PIN_POS		3
#define K3_GPIO_PIN_POS		5
#define K4_GPIO_PIN_POS		6
#define K5_GPIO_PIN_POS		7
#define K6_GPIO_PIN_POS		11

#define K1_GPIO_BTN_PIN 		BIT(K1_GPIO_PIN_POS)
#define K2_GPIO_BTN_PIN 		BIT(K2_GPIO_PIN_POS)
#define K3_GPIO_BTN_PIN 		BIT(K3_GPIO_PIN_POS)
#define K4_GPIO_BTN_PIN 		BIT(K4_GPIO_PIN_POS)
#define K5_GPIO_BTN_PIN 		BIT(K5_GPIO_PIN_POS)
#define K6_GPIO_BTN_PIN 		BIT(K6_GPIO_PIN_POS)

#define K1_GPIO_EINT 		(EINT8)
#define K2_GPIO_EINT 		(EINT11)
#define K3_GPIO_EINT 		(EINT13)
#define K4_GPIO_EINT 		(EINT14)
#define K5_GPIO_EINT 		(EINT15)
#define K6_GPIO_EINT 		(EINT19)

#endif //MINI2440


/*******************************/


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


#define GPIO_INPUT_FN 		0x0U
#define GPIO_OUTPUT_FN  	0x1U
#define GPIO_EINT_FN  		0x2U
#define GPIO_EXTERNAL_FN    0x3U

#define set_gpio_function(GPIO_FN,GPIO_PIN) \
	(GPIO_FN)<<(GPIO_PIN<<1)

#define set_gpio_con(BA,param) \
	set_reg_params(GPCON_REG(BA),param)


#define EXTINT0_OFF 	(0x88)
#define EXTINT1_OFF 	(0x8C)
#define EXTINT2_OFF 	(0x90)

#define EXTINT0_REG(BA) 	\
		HW_REG((BA),EXTINT0_OFF)

#define EXTINT1_REG(BA) 	\
		HW_REG((BA),EXTINT1_OFF)

#define EXTINT2_REG(BA) 	\
		HW_REG((BA),EXTINT2_OFF)

#define TRIGGER_MASK  			(0x7)
#define TRIGGER_LOW_LEVEL 		(0x0)
#define TRIGGER_HIGH_LEVEL 		(0x1)
#define TRIGGER_FALLING_EDGE 	(0x2)
#define TRIGGER_RISING_EDGE 	(0x4)
#define TRIGGER_BOTH_EDGE 		(0x6)

#define FILTER_ENABLE 			(0x1)
#define FILTER_DISABLE 			(0x0)
#define FILTER_MASK 	 		(0x1)

#define EINTFLT0_OFF  	(0x94)
#define EINTFLT1_OFF  	(0x98)
#define EINTFLT2_OFF  	(0x9C)
#define EINTFLT3_OFF  	(0xA0)

#define EINTFLT0_REG(BA) \
		HW_REG((BA),EINTFLT0_OFF)
	
#define EINTFLT1_REG(BA) \
		HW_REG((BA),EINTFLT1_OFF)

#define EINTFLT2_REG(BA) \
		HW_REG((BA),EINTFLT2_OFF)

#define EINTFLT3_REG(BA) \
		HW_REG((BA),EINTFLT3_OFF)

#define EINTMASK_OFF 	(0xA4)
#define EINTMASK_REG(BA) \
	HW_REG((BA),EINTMASK_OFF)

#define EINTPEND_OFF 	(0xA8)
#define EINTPEND_REG(BA) \
	HW_REG((BA),EINTPEND_OFF)


#define enable_external_interrupt(BA,mask) \
	clear_reg_params((EINTMASK_REG(BA)),mask)

#define clear_external_interrupts(BA,mask) \
	set_reg_params((EINTMASK_REG(BA)),mask)

#define clear_pending_interrupts(BA,mask) \
	set_reg_params((EINTPEND_REG(BA)),mask)

#define get_pending_interrupts(BA,mask) \
	((readreg32(EINTPEND_REG(BA))) & mask)

#endif
