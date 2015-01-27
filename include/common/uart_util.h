#ifndef UART_UTIL_H_

#define UART_UTIL_H_

#include "uart.h"

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

void init_uart0();
void putc_ch0(char ch);
char getc_ch0();
void puts(const char *str);
void print_hex(uint32_t num);

//Bit will be set if buffer is empty.
uint32_t isTxBuffEmpty(uint32_t channel);

//Bit will be set if buffer is full.
uint32_t isRxBuffFull(uint32_t channel);

uint32_t isTxEmpty(uint32_t channel);

#endif
