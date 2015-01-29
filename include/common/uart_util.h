#ifndef UART_UTIL_H_

#define UART_UTIL_H_

#include "uart.h"

/**************************************/

#define uart_writel_ch(UART_BA,ch) \
	writereg32(UTXH_L_REG(UART_BA),ch)

#define uart_writeb_ch(UART_BA,ch) \
	writereg32(UTXH_B_REG(UART_BA),ch)

#define uart_readl_ch(UART_BA) \
	readreg32(URXH_L_REG(UART_BA))

#define uart_readb_ch(UART_BA) \
	readreg32(URXH_B_REG(UART_BA))

/*************************************/

#define uart_writel_ch0(ch) \
		writereg32(UTXH0_L,ch)

#define uart_writel_ch1(ch) \
		writereg32(UTXH1_L,ch)

#define uart_writel_ch2(ch) \
		writereg32(UTXH2_L,ch)

#define uart_writeb_ch0(ch) \
		writereg32(UTXH0_B,ch)

#define uart_writeb_ch1(ch) \
		writereg32(UTXH0_B,ch)

#define uart_writeb_ch2(ch) \
		writereg32(UTXH0_B,ch)

#define uart_readl_ch0() \
		readreg32(URXH0_L)

#define uart_readl_ch1() \
		readreg32(URXH1_L)

#define uart_readl_ch2() \
		readreg32(URXH2_L)

#define uart_readb_ch0() \
		readreg32(URXH0_B)

#define uart_readb_ch1() \
		readreg32(URXH1_B)

#define uart_readb_ch2() \
		readreg32(URXH2_B)
/*
#define uart_set_ulcon(uart,val) \
		writereg32(uart+ULCON,val)

#define uart_set_ucon(uart,val) \
	writereg32(uart+UCON,val)

#define uart_set_ufcon(uart,val) \
	writereg32(uart+UFCON,val)

#define uart_set_umcon(uart,val) \
	writereg32(uart+UMCON,val)

#define uart_get_ulcon(uart,val) \
	readreg32(uart+ULCON)

#define uart_get_ucon(uart,val) \
	readreg32(uart+UCON)

#define uart_get_ufcon(uart,val) \
	readreg32(uart+UFCON)

#define uart_get_umcon(uart,val) \
	readreg32(uart+UMCON)
*/


void init_uart(uint32_t UART_BA);
char getc(uint32_t UART_BA);
void uart_puts(uint32_t UART_BA,const char *str);

//void putc_ch0(char ch);
//char getc_ch0();
//void puts(const char *str);
//void print_hex(uint32_t num);
void print_hex_uart(uint32_t UART_BA,uint32_t num);
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
	

//Bit will be set if buffer is full.
/*uint32_t isRxBuffFull(uint32_t channel);

uint32_t isTxEmpty(uint32_t channel);*/

#define putc(UART_BA,ch) \
{ \
	uart_writel_ch(UART_BA,ch); \
	while(!uart_is_tx_empty(UART_BA)) \
		; \
}


#endif
