#include "common.h"
#include "uart_util.h"
#include "gpio_def.h"
#include "clock_pm.h"

const char hexchar[] = 
	{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

char getc(uint32_t UART_BA)
{
	while(!uart_is_rx_buff_full(UART_BA))
		;

	return uart_readl_ch(UART_BA);
}


void uart_puts(uint32_t UART_BA,const char *str)
{
	while((*str) != '\0') {
		putc(UART_BA,*str); /* Do not increment for the macro. Do it in the next line */
		str++;
	}
}



void print_hex_uart(uint32_t UART_BA,uint32_t num) 
{
	unsigned int i = 0;

	uart_puts(UART_BA,"0x");

	for(i = 0; i<8; i++) {
		putc(UART_BA,hexchar[(num & 0xF0000000)>>28]);
		num<<=4;
	}

	uart_puts(UART_BA,"\r\n");
}


void print_hex_uart_ch(uint32_t UART_BA, uint8_t num)
{
	uart_puts(UART_BA,"0x");

	putc(UART_BA,hexchar[(num & 0xF0) >> 4]);
	num <<= 4;
	putc(UART_BA,hexchar[(num & 0xF0) >> 4]);
}

void init_uart(uint32_t UART_BA)
{

	apb_clk_enable(CLK_BASE_ADDR,CLK_UART0); //Enable the clock for UART block.
	set_gpio_con(GPH_BA,nCTS0|nRTS0|TXD0|RXD0); //Set the GPIO pins to UART function.

	set_ulcon_reg(UART_BA,WORD_LENGTH_8BITS);
	//writereg32(ULCON_REG(UART_BA),WORD_LENGTH); //Set line control.
	
	set_ucon_reg(UART_BA,
				(
				PCLK_SELECT|Tx_INTR_TYPE_LVL|Rx_INTR_TYPE_LVL
				|TRANSMIT_MODE_INTR_REQ_OR_POLLING
				|RECEIVE_MODE_INTR_REQ_OR_POLLING
				)
			);
	
/*	writereg32(UCON_REG(UART_BA),
			(PCLK_SELECT|Tx_INTR_TYPE_LVL|Rx_INTR_TYPE_LVL|
			TRANSMIT_MODE_INTR_REQ|RECEIVE_MODE_INTR_REQ));*/

	/* NOTE: PCLK set to 50MHz. Baud rate set to 26 for 115200*/
//	writereg32(UBRDIV_REG(UART_BA),get_uart_brdiv(UART_BA,BAUD_115200));
	set_uart_brdiv(UART_BA,get_uart_brdiv(UART_BA,BAUD_115200));
}

