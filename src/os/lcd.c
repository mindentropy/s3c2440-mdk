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

#define CLKVAL 	(7)
#define BPP 	(16)

#define MEMBUFF_SIZE 		((HRES) * (VRES) * (BPP>>3))
#define LCD_START_ADDR 		(0x32000000U)

/* 
 * For testing will put the LCD memory at 0x32000000
 */

void init_lcd()
{
	unsigned int i = 0;
	unsigned char *buff = (unsigned char *)LCD_START_ADDR;
	disable_lcd_controller(LCD_BA);

	writereg32(LCDCON1_REG(LCD_BA),((CLKVAL<<8)|PNRMODE_TFT_LCD|TFT_16BPP));
	writereg32(LCDCON2_REG(LCD_BA),((VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|VSPW));
	writereg32(LCDCON3_REG(LCD_BA),((HBPD<<19)|(HOZVAL<<8)|(HFPD)));
	writereg32(LCDCON4_REG(LCD_BA),(HSPW));

	set_reg_params(LCDCON5_REG(LCD_BA),FRM565_5_6_5_1_FRMT|PWREN);

	writereg32(LCDSADDR1_REG(LCD_BA),LCD_START_ADDR>>1);
	writereg32(LCDSADDR2_REG(LCD_BA),((LCD_START_ADDR+MEMBUFF_SIZE) & 0x1FFFFF)>>1);
	writereg32(LCDSADDR3_REG(LCD_BA),((HRES*BPP)>>4)&0x3F);
	writereg32(LCDINTMSK_REG(LCD_BA),FIWSEL|INT_FRAME_SYNC|INT_FIFO_CNT);

	for(i = 0;i<MEMBUFF_SIZE; i++) {
		buff[i] = 0;
	}
	
	enable_lcd_controller(LCD_BA);

}
