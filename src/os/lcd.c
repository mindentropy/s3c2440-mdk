#include "lcd.h"


/*
 * Parameters for clock value of 100MHz and Framerate of around 60-70Hz
 * for a 320 x 240 screen size.
 */

#define HRES 	240
#define VRES 	320

#define VSPW 	(2)
#define VBPD 	(2)
#define LINEVAL (VRES-1)
#define VFPD 	(2)

#define HSPW 	(10)
#define HBPD 	(20)
#define HOZVAL 	(HRES-1)
#define HFPD 	(10)

#define CLKVAL 	7



void init_lcd()
{
	disable_lcd_controller(LCD_BA);

/*	writereg32(LCDCON1_REG(LCD_BA),((CLKVAL<<8)|PNRMODE_TFT_LCD|TFT_16BPP));
	writereg32(LCDCON2_REG(LCD_BA),((VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|VSPW));
	writereg32(LCDCON3_REG(LCD_BA),((HBPD<<19)|(HOZVAL<<8)|(HFPD)));
	writereg32(LCDCON4_REG(LCD_BA),(HSPW));*/

	set_reg_params(LCDCON5_REG(LCD_BA),FRM565_5_6_5_1_FRMT|PWREN);
}
