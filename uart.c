#ifndef UART_H_

#define UART_H_

#include "uart.h"
#include "clock_pm.h"

void init_uart0()
{
	//Enable the UART0 in CLKCON register.
	enable_uart0_clk();

	//Set UART Line register to 8N1. 8 bits, No parity and 1 stop bit.
	// Need to set only word length to 8 bits. Rest remain as defaults.

}



#endif
