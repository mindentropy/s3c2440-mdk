#ifndef UART_H_

#define UART_H_

#include "common.h"

/* UART Line Control Register Base Address*/
#define ULCON0 	0x50000000
#define ULCON1 	0x50004000
#define ULCON2  0x50008000

/* Parity Mask */
#define INFRARED_MODE BIT6
#define PARITY_MODE  (BIT5|BIT4|BIT3)
#define STOP_BIT (BIT2)
#define WORD_LENGTH (BIT1|BIT0)

#define PARITY_POS 				3

#define NO_PARITY 				(0)
#define ODD_PARITY 				(BIT5)
#define EVEN_PARITY 			(BIT5|BIT3)
#define PARITY_FORCED_CHECK1 	(BIT5|BIT4)
#define PARITY_FORCED_CHECK0 	(BIT5|BIT4|BIT3)

/* UART Control Register Base Address */
#define UCON0 	0x50000004
#define UCON1 	0x50004004
#define UCON2  	0x50008004

#define FCLK_DIVIDER 				(BIT15|BIT14|BIT13|BIT12)
#define CLOCK_SELECTION 			(BIT11|BIT10)

#define PCLK_SELECT      			(BIT11)
#define UEXTCLK_SELECT   			(BIT10)
#define FCLK_BY_N_SELECT 			(BIT11|BIT10)

#define Tx_INTR_TYPE 				(BIT9)
#define Tx_INTR_TYPE_LVL 			(BIT9)
#define Tx_INTR_TYPE_PULSE 			(0)

#define Rx_INTR_TYPE 				(BIT8)
#define Rx_INTR_TYPE_LVL			(BIT8)
#define Rx_INTR_TYPE_PULSE			(0)

#define Rx_TIMEOUT_ENABLE 			(BIT7)
#define Rx_ERROR_STATUS_INTR_ENABLE (BIT6)
#define LOOPBACK_MODE 				(BIT5)
#define SEND_BREAK_SIGNAL 			(BIT4)

#define TRANSMIT_MODE (BIT3|BIT2)

#define TRANSMIT_MODE_POS (2)

#define TRANSMIT_MODE_DISABLE 		(0)
#define TRANSMIT_MODE_INTR_REQ 		(BIT2)
#define TRANSMIT_MODE_DMA0_DMA3_REQ (BIT3)
#define TRANSMIT_MODE_DMA1_REQ 		(BIT3|BIT2)


/*#define TRANSMIT_MODE_INTR_REQ 		set_bitval_pos((BIT0),TRANSMIT_MODE_POS)
#define TRANSMIT_MODE_DMA0_DMA3_REQ set_bitval_pos((BIT1),TRANSMIT_MODE_POS)
#define TRANSMIT_MODE_DMA1_REQ 		set_bitval_pos((BIT1|BIT0),TRANSMIT_MODE_POS)*/


#define RECEIVE_MODE 				(BIT1|BIT0)

#define RECEIVE_MODE_DISABLE 		(0)
#define RECEIVE_MODE_INTR_REQ 		(BIT0)
#define RECEIVE_MODE_DMA0_DMA3_REQ 	(BIT1)
#define RECEIVE_MODE_DMA1_REQ 		(BIT1|BIT0)


/* UART FIFO Control Register Base Address */
#define UFCON0 	0x50000008
#define UFCON1 	0x50004008
#define UFCON2 	0x50008008

#define Tx_FIFO_TRIGGER_LVL 	(BIT7|BIT6)

#define Tx_FIFO_EMPTY           (0)
#define Tx_FIFO_16B             (BIT6)
#define Tx_FIFO_32B             (BIT7)
#define Tx_FIFO_64B             (BIT7|BIT6)

#define Rx_FIFO_TRIGGER_LVL 	(BIT5|BIT4)

#define Rx_FIFO_EMPTY           (0)
#define Rx_FIFO_16B             (BIT4)
#define Rx_FIFO_32B             (BIT5)
#define Rx_FIFO_64B             (BIT5|BIT4)

#define Tx_FIFO_RESET 			(BIT2)

#define Rx_FIFO_RESET 			(BIT1)

#define FIFO_ENABLE 			(BIT0)


/* UART Modem Control Register Base Address */
#define UMCON0  0x5000000C
#define UMCON1 	0x5000400C
#define UMCON2 	0x5000800C

#define AFC     (BIT4)
#define RTS     (BIT0)

/* UART Tx/Rx Status Register Base Address */
#define UTRSTAT0  0x50000010
#define UTRSTAT1  0x50004010
#define UTRSTAT2  0x50008010

#define Tx_EMPTY 			(BIT2)
#define Tx_BUFF_EMPTY   	(BIT1)
#define Rx_BUFF_DATA_RDY    (BIT0)

//Bit will be set if buffer is empty.
unsigned int isTxBuffEmpty(unsigned int channel);

//Bit will be set if buffer is full.
unsigned int isRxBuffFull(unsigned int channel);

unsigned int isTxEmpty(unsigned int channel);
/*#define is_tx_buff_empty_uart0() \
	isTxBuffEmpty(UTRSTAT0)

#define is_tx_buff_empty_uart1() \
	isTxBuffEmpty(UTRSTAT1)

#define is_tx_buff_empty_uart2() \
	isTxBuffEmpty(UTRSTAT2)

#define is_rx_buff_full_uart0() \
	isRxBuffFull(UTRSTAT0)

#define is_rx_buff_full_uart1() \
	isRxBuffFull(UTRSTAT1)

#define is_rx_buff_full_uart2() \
	isRxBuffFull(UTRSTAT2)*/

/* UART Error Status Register Base Address */
#define UERSTAT0  0x50000014
#define UERSTAT1  0x50004014
#define UERSTAT2  0x50008014

#define BREAK_DETECT 	(BIT3)
#define FRAME_ERROR 	(BIT2)
#define PARITY_ERROR 	(BIT1)
#define OVERRUN_ERROR 	(BIT0)

/* UART FIFO Status Register Base Address */
#define UFSTAT0  0x50000018
#define UFSTAT1  0x50004018
#define UFSTAT2  0x50008018


#define Tx_FIFO_FULL 	(BIT14)
#define Tx_FIFO_COUNT   (BIT13|BIT12|BIT11|BIT10|BIT9|BIT8)
#define Rx_FIFO_FULL 	(BIT6)
#define Rx_FIFO_COUNT   (BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)


/* UART Modem Status Register Base Address */
#define UMSTAT0  			0x5000001C
#define UMSTAT1  			0x5000401C
#define UMSTAT2_RESERVED  	0x5000801C

#define DELTA_CTS 		(BIT4)
#define CTS 			(BIT0)

/* UART Transmit Buffer Register Base Address */
#define UTXH0_L 	0x50000020
#define UTXH0_B 	0x50000023


#define UTXH1_L 	0x50004020
#define UTXH1_B 	0x50004023

#define UTXH2_L 	0x50008020
#define UTXH2_B 	0x50008023

#define TxDATAn 	(BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)


/* UART Receive Buffer Register Base Address */
#define URXH0_L 	0x50000024
#define URXH0_B 	0x50000027

#define URXH1_L 	0x50004024
#define URXH1_B 	0x50004027

#define URXH2_L 	0x50008024
#define URXH2_B 	0x50008027

#define RxDATAn 	(BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)

/* UART Baud Rate Divisor Register Base Address */
#define UBRDIV0 	0x50000028
#define UBRDIV1 	0x50004028
#define UBRDIV2 	0x50008028

#define UBRDIVn     (SHORT_MASK)


void init_uart0();


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

#define uart_readl_ch0(ch) \
		readreg32(URXH0_L,ch)

#define uart_readl_ch1(ch) \
		readreg32(URXH1_L,ch)

#define uart_readl_ch2(ch) \
		readreg32(URXH2_L,ch)

#define uart_readb_ch0(ch) \
		readreg32(URXH0_B,ch)

#define uart_readb_ch1(ch) \
		readreg32(URXH1_B,ch)

#define uart_readb_ch2(ch) \
		readreg32(URXH2_B,ch)


void putc_ch0(char ch);
//void putc_ch1(char ch)
//void putc_ch2(char ch)

char getc_ch0();
//char getc_ch1();
//char getc_ch2();


void puts(const char *str);
void print_hex(unsigned int num);

#endif