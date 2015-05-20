#include "lcd.h"
#include "gpio_def.h"
#include "uart.h"


/*
 * Parameters for clock value of 100MHz and Framerate of around 60-70Hz
 * for a 320 x 240 screen size.
 */

#define HRES 	320
#define VRES 	240

//#define VSPW 	(1)
#define VSPW 	(0)
#define VBPD 	(2)
#define LINEVAL (VRES-1)
#define VFPD 	(2)

//#define HSPW 	(5)
#define HSPW 	(0)
#define HBPD 	(8)
#define HFPD 	(8)
#define HOZVAL 	(HRES-1)

#define CLKVAL 	(7)
#define BPP 	(16)

#define MEMBUFF_SIZE 		((HRES) * (VRES) * (BPP>>3))
#define LCD_START_ADDR 		(0x32000000U)

/* 
 * For testing will put the LCD memory at 0x32000000
 */


void config_gpio()
{
	/* Disable internal pull up resistors */
	writereg32(GPUP_REG(GPC_BA),0xFFFFFFFFU);
	writereg32(GPUP_REG(GPD_BA),0xFFFFFFFFU);
	/* Set the control registers to LCD function */
	writereg32(GPCON_REG(GPC_BA),0xAAAAAAAAU);
	writereg32(GPCON_REG(GPD_BA),0xAAAAAAAAU);
	
}
void init_lcd()
{
	unsigned int i = 0;
	unsigned char *buff = (unsigned char *)LCD_START_ADDR;
	unsigned short val = 0;

	config_gpio();
	disable_lcd_controller(LCD_BA);

	set_reg_params(GPCON_REG(GPG_BA),LCD_PWRDN);
	set_reg_params(GPUP_REG(GPG_BA),LCD_GPIO_PWRDN);
	clear_reg_params(GPDAT_REG(GPG_BA),LCD_GPIO_PWRDN);

	print_hex_uart(UART0_BA,readreg32(GPCON_REG(GPG_BA)));
	print_hex_uart(UART0_BA,readreg32(GPDAT_REG(GPG_BA)));
	print_hex_uart(UART0_BA,readreg32(LCDCON5_REG(LCD_BA)));
	

	writereg32(LCDCON1_REG(LCD_BA),((CLKVAL<<8)|PNRMODE_TFT_LCD|TFT_16BPP));
	writereg32(LCDCON2_REG(LCD_BA),((VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|VSPW));
	writereg32(LCDCON3_REG(LCD_BA),((HBPD<<19)|(HOZVAL<<8)|(HFPD)));
	writereg32(LCDCON4_REG(LCD_BA),(HSPW));

	set_reg_params(LCDCON5_REG(LCD_BA), FRM565_5_6_5_1_FRMT|PWREN);

	writereg32(LCDSADDR1_REG(LCD_BA),LCD_START_ADDR>>1);
	writereg32(LCDSADDR2_REG(LCD_BA),((LCD_START_ADDR+MEMBUFF_SIZE) & 0x1FFFFF)>>1);
	writereg32(LCDSADDR3_REG(LCD_BA),((HRES*BPP)>>4)&0x3F);
	writereg32(LCDINTMSK_REG(LCD_BA),FIWSEL|INT_FRAME_SYNC|INT_FIFO_CNT);

	clear_reg_params(TCONSEL_REG(LCD_BA),LCC_SEL3|LPC_EN|LCC_EN);

	enable_lcd_controller(LCD_BA);

	while(1) {
		for(i = 0; i<(MEMBUFF_SIZE-1); i++) {
			buff[i]++;
		}
	}
}
