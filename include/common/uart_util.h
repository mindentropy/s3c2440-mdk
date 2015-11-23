#ifndef UART_UTIL_H_

#define UART_UTIL_H_

#include "uart.h"


#define uart_writel_ch(UART_BA,ch) \
	writereg8(UTXH_L_REG(UART_BA),ch)

#define uart_writeb_ch(UART_BA,ch) \
	writereg8(UTXH_B_REG(UART_BA),ch)

#define uart_readl_ch(UART_BA) \
	readreg8(URXH_L_REG(UART_BA))

#define uart_readb_ch(UART_BA) \
	readreg8(URXH_B_REG(UART_BA))


void init_uart(uint32_t UART_BA);
char getc(uint32_t UART_BA);
void uart_puts(uint32_t UART_BA,const char *str);
int uart_getbuff(char *ch,int length);

void uart0_interrupt_handler(void);

void print_hex_uart(uint32_t UART_BA,uint32_t num);
void print_hex_uart_ch(uint32_t UART_BA,uint8_t num);

//Bit will be set if buffer is empty.
uint32_t isTxBuffEmpty(uint32_t channel);

//Bit will be set if buffer is empty.
#define uart_is_tx_buff_empty(UART_BA) \
	((readreg32(UTRSTAT_REG(UART_BA)) & Tx_BUFF_EMPTY) == (Tx_BUFF_EMPTY))

#define uart_is_tx_empty(UART_BA) \
	((readreg32(UTRSTAT_REG(UART_BA)) & Tx_EMPTY) == (Tx_EMPTY))

//Bit will be set if buffer is full.
#define uart_is_rx_buff_full(UART_BA) \
	((readreg32(UTRSTAT_REG(UART_BA)) & Rx_BUFF_DATA_RDY) == (Rx_BUFF_DATA_RDY))
	

#define putc(UART_BA,ch) \
{ \
	uart_writel_ch(UART_BA,ch); \
	while(!uart_is_tx_empty(UART_BA)) \
		; \
}


#endif
