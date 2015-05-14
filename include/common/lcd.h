#ifndef LCD_H_

#define LCD_H_

#include "common.h"

#define LCD_BA 0x4D000000U


#define LCDCON1_OFF 	0x00
#define LCDCON1_REG(BA) \
	HW_REG(BA,LCDCON1_OFF)

#define LINECNT_MSK 	set_bit_range(27,18)
#define CLKVAL_MSK 		set_bit_range(17,8)

#define MMMODE 			BIT7

#define PNRMODE 		(BIT6|BIT5)

#define PNRMODE_STN_4b_DUAL  	(0)
#define PNRMODE_STN_4b_SINGLE  	(BIT5)
#define PNRMODE_STN_8b_SINGLE  	(BIT6)
#define PNRMODE_TFT_LCD  		(BIT6|BIT5)

#define BPPMODE_MSK 	set_bit_range(4,1)

#define STN_1BPP 			(0)
#define STN_2BPP 			(BIT1)
#define STN_4BPP 			(BIT2)
#define STN_8BPP 			(BIT2|BIT1)
#define STN_UNPACK_12BPP 	(BIT3)
#define STN_PACK_12BPP 		(BIT3|BIT1)
#define STN_16BPP 			(BIT3|BIT2)

#define TFT_1BPP 		(BIT4)
#define TFT_2BPP 		(BIT4|BIT1)
#define TFT_4BPP 		(BIT4|BIT2)
#define TFT_8BPP 		(BIT4|BIT2|BIT1)
#define TFT_16BPP 		(BIT4|BIT3)
#define TFT_24BPP 		(BIT4|BIT3|BIT1)

#define ENVID 			BIT0

#define LCDCON2_OFF 	0x04
#define LCDCON2_REG(BA) \
	HW_REG(BA,LCDCON2_OFF)

#define VBPD_MSK 			set_bit_range(31,24)
#define LINEVAL_MSK 		set_bit_range(23,14)
#define VFPD_MSK 			set_bit_range(13,6)
#define VSPW_MSK 			set_bit_range(5,0)

#define LCDCON3_OFF 	0x08
#define LCDCON3_REG(BA) \
	HW_REG(BA,LCDCON3_OFF)

#define HBPD_MSK 			set_bit_range(25,19)
#define WDLY_MSK 			set_bit_range(25,19)
#define HOZVAL_MSK 			set_bit_range(18,8)
#define HFPD_MSK 			set_bit_range(7,0)
#define LINEBLANK_MSK 		set_bit_range(7,0)

#define LCDCON4_OFF 	0x0C
#define LCDCON4_REG(BA) \
	HW_REG(BA,LCDCON4_OFF)

#define MVAL_MSK 	set_bit_range(15,8)
#define HSPW_MSK  	set_bit_range(7,0)
#define WLH_MSK  	set_bit_range(7,0)

#define LCDCON5_OFF 	0x10
#define LCDCON5_REG(BA) \
	HW_REG(BA,LCDCON5_OFF)

#define VSTATUS_MSK 	(BIT16|BIT15)
#define VSYNC 			(0)
#define VBACKPORCH 		(BIT15)
#define VACTIVE 		(BIT16)
#define VFRONTPORCH 	(BIT16|BIT15)

#define HSTATUS_MSK 	(BIT14|BIT13)
#define HSYNC 			(0)
#define HBACKPORCH 		(BIT13)
#define HACTIVE 		(BIT14)
#define HFRONTPORCH 	(BIT14|BIT13)


#define BPP24BL_MSK 		(BIT12)
#define BPP24BL_MSB_VALID 	(BIT12)
#define BPP24BL_LSB_VALID 	(0)

#define FRM565_MSK 				(BIT11)
#define FRM565_5_5_5_1_FRMT  	(0)
#define FRM565_5_6_5_1_FRMT  	(BIT11)

#define INVVCLK 		(BIT10)
#define INVVLINE 		(BIT9)
#define INVVFRAME 		(BIT8)
#define INVVD 			(BIT7)
#define INVVDEN 		(BIT6)
#define INVPWREN 		(BIT5)
#define INVLEND 		(BIT4)
#define PWREN 			(BIT3)
#define ENLEND 			(BIT2)
#define BSWP 			(BIT1)
#define HWSWP 			(BIT0)

#define LCDSADDR1_OFF	0x14
#define LCDSADDR1_REG(BA) \
	HW_REG(BA,LCDSADDR1_OFF)

#define LCDBANK_MSK 	set_bit_range(29,21)
#define LCDBASEU_MSK 	set_bit_range(20,0)

#define LCDSADDR2_OFF	0x18
#define LCDSADDR2_REG(BA) \
	HW_REG(BA,LCDSADDR2_OFF)

#define LCDBASEL_MSK 	set_bit_range(20,0)

#define LCDSADDR3_OFF	0x1C
#define LCDSADDR3_REG(BA) \
	HW_REG(BA,LCDSADDR3_OFF)

#define OFFSIZE_MSK 	set_bit_range(21,11)
#define PAGEWIDTH_MSK 	set_bit_range(10,0)

#define REDLUT_OFF		0x20
#define REDLUT_REG(BA) \
	HW_REG(BA,REDLUT_OFF)

#define GREENLUT_OFF	0x24
#define GREENLUT_REG(BA) \
	HW_REG(BA,GREENLUT_OFF)

#define BLUELUT_OFF		0x28
#define BLUELUT_REG(BA) \
	HW_REG(BA,BLUELUT_OFF)

#define DITHMODE_OFF	0x4C
#define DITHMODE_REG(BA) \
	HW_REG(BA,DITHMODE_OFF)

#define DITHMODE_MSK 	set_bit_range(18,0)

#define TPAL_OFF 		0x50
#define TPAL_REG(BA) \
	HW_REG(BA,TPAL_OFF)

#define TPALEN 			BIT24
#define TPALVAL 		set_bit_range(23,0)

#define LCDINTPND_OFF 	0x54
#define LCDINTPND_REG(BA) \
	HW_REG(BA,LCDINTPND_OFF)

#define LCDSRCPND_OFF 	0x58
#define LCDSRCPND_REG(BA) \
	HW_REG(BA,LCDSRCPND_OFF)

#define INT_FRAME_SYNC 	BIT1
#define INT_FIFO_CNT 	BIT0

#define LCDINTMSK_OFF 	0x5C
#define LCDINTMSK_REG(BA) \
	HW_REG(BA,LCDINTMSK_OFF)

#define FIWSEL 			BIT2

#define TCONSEL_OFF 	0x60
#define TCONSEL_REG(BA) \
	HW_REG(BA,TCONSEL_OFF)


#define LCC_TEST2 		BIT11
#define LCC_TEST1 		BIT10

#define LCC_SEL5 		BIT9
#define LCC_SEL4 		BIT8
#define LCC_SEL3 		BIT7
#define LCC_SEL2 		BIT6
#define LCC_SEL1 		BIT5

#define LCC_EN 			BIT4
#define CPV_SEL 		BIT3
#define MODE_SEL 		BIT2
#define RES_SEL 		BIT1
#define LPC_EN 			BIT0


#define enable_lcd_controller(BA) \
	set_reg_params(LCDCON1_REG(BA),ENVID)

#define disable_lcd_controller(BA) \
	clear_reg_params(LCDCON1_REG(BA),ENVID)

void init_lcd();
#endif
