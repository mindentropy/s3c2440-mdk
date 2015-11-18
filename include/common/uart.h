#ifndef UART_H_

#define UART_H_

#include "common.h"
#include <stdint.h>


#define UART0_BA 0x50000000U
#define UART1_BA 0x50004000U
#define UART2_BA 0x50008000U

/* UART Line Control Register Base Address*/
#define ULCON   0x00

#define ULCON_REG(UART_BA) \
	HW_REG(UART_BA,ULCON)

#define set_ulcon_reg(UART_BA,param_mask) \
	set_reg_params(ULCON_REG(UART_BA),param_mask)

#define write_ulcon_reg(UART_BA,param_mask) \
	writereg32(ULCON_REG(UART_BA),param_mask)

/* Parity Mask */
#define INFRARED_MODE 		(BIT6)
#define PARITY_MODE  		(BIT5|BIT4|BIT3)
#define STOP_BIT 			(BIT2)
#define WORD_LENGTH_MASK 	(BIT1|BIT0)
#define WORD_LENGTH_5BITS 	(0)
#define WORD_LENGTH_6BITS 	(BIT0)
#define WORD_LENGTH_7BITS 	(BIT1)
#define WORD_LENGTH_8BITS 	(BIT1|BIT0)


#define PARITY_POS 				3

#define NO_PARITY 				(0)
#define ODD_PARITY 				(BIT5)
#define EVEN_PARITY 			(BIT5|BIT3)
#define PARITY_FORCED_CHECK1 	(BIT5|BIT4)
#define PARITY_FORCED_CHECK0 	(BIT5|BIT4|BIT3)

/* UART Control Register Base Address */
#define UCON 	0x04

#define UCON_REG(UART_BA) \
	HW_REG(UART_BA,UCON)

#define set_ucon_reg(UART_BA,param_mask) \
	set_reg_params(UCON_REG(UART_BA),param_mask)

#define write_ucon_reg(UART_BA,param_mask) \
	writereg32(UCON_REG(UART_BA),param_mask)

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

#define TRANSMIT_MODE_DISABLE 				(0)
#define TRANSMIT_MODE_INTR_REQ_OR_POLLING 	(BIT2)
#define TRANSMIT_MODE_DMA0_DMA3_REQ 		(BIT3)
#define TRANSMIT_MODE_DMA1_REQ 				(BIT3|BIT2)

#define RECEIVE_MODE 				(BIT1|BIT0)

#define RECEIVE_MODE_DISABLE 				(0)
#define RECEIVE_MODE_INTR_REQ_OR_POLLING 	(BIT0)
#define RECEIVE_MODE_DMA0_DMA3_REQ 			(BIT1)
#define RECEIVE_MODE_DMA1_REQ 				(BIT1|BIT0)


/* UART FIFO Control Register Base Address */
#define UFCON 	0x08

#define UFCON_REG(UART_BA) \
	HW_REG(UART_BA,UFCON)

#define set_ufcon_reg(UART_BA,param_mask) \
	set_reg_params(UFCON_REG(UART_BA),param_mask)

#define write_ufcon_reg(UART_BA,param_mask) \
	writereg32(UFCON_REG(UART_BA),param_mask)

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
#define UMCON 	0x0C

#define UMCON_REG(UART_BA) \
	HW_REG(UART_BA,UMCON)


#define AFC     (BIT4)
#define RTS     (BIT0)

/* UART Tx/Rx Status Register Base Address */
#define UTRSTAT   0x10

#define UTRSTAT_REG(UART_BA) \
	HW_REG(UART_BA,UTRSTAT)


#define Tx_EMPTY 			(BIT2)
#define Tx_BUFF_EMPTY   	(BIT1)
#define Rx_BUFF_DATA_RDY    (BIT0)


/* UART Error Status Register Base Address */
#define UERSTAT   0x14

#define UERSTAT_REG(UART_BA) \
	HW_REG(UART_BA,UERSTAT)


#define ERROR_MASK      (0xFU)
#define BREAK_DETECT 	(BIT3)
#define FRAME_ERROR 	(BIT2)
#define PARITY_ERROR 	(BIT1)
#define OVERRUN_ERROR 	(BIT0)


#define get_uart_error_state(UART_BA) \
	(readreg32(UERSTAT_REG(UART_BA)) & ERROR_MASK)

/* UART FIFO Status Register Base Address */
#define UFSTAT 	0x18

#define UFSTAT_REG(UART_BA) \
	HW_REG(UART_BA,UFSTAT)


#define Tx_FIFO_FULL 	(BIT14)
#define Tx_FIFO_COUNT   (BIT13|BIT12|BIT11|BIT10|BIT9|BIT8)
#define Rx_FIFO_FULL 	(BIT6)
#define Rx_FIFO_COUNT   (BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)


/* UART Modem Status Register Base Address */
#define UMSTAT 	0x1C

#define UMSTAT_REG(UART_BA) \
	HW_REG(UART_BA,UMSTAT)


#define DELTA_CTS 		(BIT4)
#define CTS 			(BIT0)

/* UART Transmit Buffer Register Base Address */
#define UTXH_L 		0x20
#define UTXH_B 		0x23

#define UTXH_L_REG(UART_BA) \
	HW_REG(UART_BA,UTXH_L)

#define UTXH_B_REG(UART_BA) \
	HW_REG(UART_BA,UTXH_B)


#define TxDATAn 	(BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)


/* UART Receive Buffer Register Base Address */
#define URXH_L  	0x24
#define URXH_B  	0x27

#define URXH_L_REG(UART_BA) \
	HW_REG(UART_BA,URXH_L)

#define URXH_B_REG(UART_BA) \
	HW_REG(UART_BA,URXH_B)


#define RxDATAn 	(BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)

/* UART Baud Rate Divisor Register Base Address */
#define UBRDIV 		0x28

#define UBRDIV_REG(UART_BA) \
	HW_REG(UART_BA,UBRDIV)

#define set_uart_brdiv(UART_BA,value) \
	writereg32(UBRDIV_REG(UART_BA),value)

#define UBRDIVn     (SHORT_MASK)

#define BAUD_115200 	115200U

#define get_uart_brdiv(BA,baud_rate) \
	((get_pclk(CLK_BASE_ADDR)/((baud_rate)<<4)) - 1)

#endif
