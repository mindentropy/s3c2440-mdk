#include "lcd.h"
#include "gpio_def.h"
#include "uart.h"
#include "uart_util.h"

/*
 * First configure GPIO to enable LCD controller functions
 * and disable the internal pull up resistors.
 */
void config_lcd_gpio()
{
	/* Disable internal pull up resistors */
	writereg32(GPUP_REG(GPC_BA),0xFFFFFFFFU);
	writereg32(GPUP_REG(GPD_BA),0xFFFFFFFFU);
	/* Set the control registers to LCD function */
	writereg32(GPCON_REG(GPC_BA),0xAAAAAAAAU);
	writereg32(GPCON_REG(GPD_BA),0xAAAAAAAAU);
	
}

unsigned char *lcd_frame_buff = (unsigned char *)LCD_START_ADDR;

void init_lcd()
{
	unsigned int i = 0;
//	unsigned char color = 0;

	config_lcd_gpio();
	disable_lcd_controller(LCD_BA);

	set_reg_bits(GPCON_REG(GPG_BA),LCD_PWR);
	set_reg_bits(GPUP_REG(GPG_BA),LCD_GPIO_PWR_PIN);
	clear_reg_bits(GPDAT_REG(GPG_BA),LCD_GPIO_PWR_PIN);

	/*print_hex_uart(UART0_BA,readreg32(GPCON_REG(GPG_BA)));
	print_hex_uart(UART0_BA,readreg32(GPDAT_REG(GPG_BA)));
	print_hex_uart(UART0_BA,readreg32(LCDCON5_REG(LCD_BA)));*/
	
	/*
	 * Note: There is a confusion between HCLK and LCD_HCLK
	 * S3C2440A HCLK --> 101Mhz
	 */

	//TODO: Calculate CLKVAL based on a formula.
	writereg32(LCDCON1_REG(LCD_BA),((CLKVAL<<8)|PNRMODE_TFT_LCD|TFT_16BPP));
	writereg32(LCDCON2_REG(LCD_BA),((VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|VSPW));
	writereg32(LCDCON3_REG(LCD_BA),((HBPD<<19)|(HOZVAL<<8)|(HFPD)));
	writereg32(LCDCON4_REG(LCD_BA),(HSPW));

	set_reg_bits(LCDCON5_REG(LCD_BA), FRM565_5_6_5_1_FRMT|PWREN);

	writereg32(LCDSADDR1_REG(LCD_BA),LCD_START_ADDR>>1);
	writereg32(LCDSADDR2_REG(LCD_BA),((LCD_START_ADDR+MEMBUFF_SIZE) & 0x1FFFFF)>>1);
	writereg32(LCDSADDR3_REG(LCD_BA),((HRES*BPP)>>4)&0x3F);
	writereg32(LCDINTMSK_REG(LCD_BA),FIWSEL|INT_FRAME_SYNC|INT_FIFO_CNT);

	clear_reg_bits(TCONSEL_REG(LCD_BA),LCC_SEL3|LPC_EN|LCC_EN);

	for(i = 0; i<(MEMBUFF_SIZE); i++) {
		lcd_frame_buff[i] = 0xAA;
	}

#ifdef TEST_LCD
	for(i = 0; i<(MEMBUFF_SIZE); i++) {
		lcd_frame_buff[i] = getc(UART0_BA);
		putc(UART0_BA,lcd_frame_buff[i]);
	}
#endif 

	enable_lcd_controller(LCD_BA);
	
}
