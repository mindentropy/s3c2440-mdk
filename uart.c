#include "uart.h"
#include "clock_pm.h"


static void set_uart_line_control()
{
	unsigned int val = 0;

	readreg32(ULCON0,val);

	writereg32(ULCON0,0);

	set_bits(val,WORD_LENGTH);
	writereg32(ULCON0,val);
}


static void set_uclk_select()
{
	unsigned int val = 0;

	readreg32(UCON0,val);

	writereg32(UCON0,0);

	set_bits(val,
				PCLK_SELECT|Tx_INTR_TYPE_LVL|Rx_INTR_TYPE_LVL|
				TRANSMIT_MODE_INTR_REQ|RECEIVE_MODE_INTR_REQ);
	writereg32(UCON0,val);
}


static void set_uart0_baud_gen ()
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


void init_uart0()
{

	init_uart0_registers();
	//Enable the UART0 in CLKCON register.
	enable_uart0_clk();

	//Set UART Line register to 8N1. 8 bits, No parity and 1 stop bit.
	set_uart_line_control();

	// Need to set only word length to 8 bits. Rest remain as defaults.
	set_uclk_select();

	set_uart0_baud_gen();
}

