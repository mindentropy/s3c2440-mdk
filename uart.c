#include "common.h"
#include "uart.h"
#include "gpio_def.h"
#include "clock_pm.h"


static void set_uart_line_control()
{
	set_reg_params(ULCON0,WORD_LENGTH);
}


static void set_uart_uclk_select(unsigned int channel)
{
	set_reg_params(channel,
					PCLK_SELECT|Tx_INTR_TYPE_LVL|Rx_INTR_TYPE_LVL|
					TRANSMIT_MODE_INTR_REQ|RECEIVE_MODE_INTR_REQ
					);
}


static void set_uart0_baud_gen()
{
	writereg32(UBRDIV0,26);
}

static void init_uart0_registers()
{
	writereg32(ULCON0,0);
	writereg32(UCON0,0);
	writereg32(UFCON0,0);
	writereg32(UMCON0,0);
}


unsigned int isTxBuffEmpty(unsigned int channel)
{
	unsigned int val = 0;

	readreg32(channel,val);
	return ((val & Tx_BUFF_EMPTY) == (Tx_BUFF_EMPTY));
}

unsigned int isRxBuffFull(unsigned int channel)
{
	unsigned int val = 0;

	readreg32(channel,val);
	return ((val & Rx_BUFF_DATA_RDY) == (Rx_BUFF_DATA_RDY));
}

void putc_ch0(char ch)
{
	uart_writel_ch0(ch);

	while(!isTxBuffEmpty(UTRSTAT0))
		;
}

char getc_ch0()
{
	char ch;

	while(!isRxBuffFull(UTRSTAT0))
		;
	
	uart_readl_ch0(ch);

	return ch;
}

void puts(const char *str)
{
	while((*str) != '\0') {
		putc_ch0(*str++);
	}
}

const char hexchar[] = 
	{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void print_hex(unsigned int num) 
{
	unsigned int i = 0;

	puts("0x");
	for(i = 0; i<8; i++) {
		putc_ch0(hexchar[(num & 0xF0000000) >> 28]);
		num<<=4;
	}
	puts("\r\n");
}

void init_uart0()
{

	init_uart0_registers();
	//Enable the UART0 in CLKCON register.
	apb_clk_enable_uart0();

	set_gpio_uart_ch0();

	//Set UART Line register to 8N1. 8 bits, No parity and 1 stop bit.
	set_uart_line_control();

	// Need to set only word length to 8 bits. Rest remain as defaults.
	set_uart_uclk_select(UCON0);

	set_uart0_baud_gen();
}

