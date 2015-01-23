#ifndef UART_CTRL_H_
#define UART_CTRL_H_

struct UART_regs {
	unsigned int ULCON; /* Line control register */
	unsigned int UCON;  /* Control register */
	unsigned int UFCON; /* FIFO Control register */
	unsigned int UMCON; /* UART Modem Control Register */
	unsigned int UTRSTAT; /* UART Tx/Rx registers */
	unsigned int UERSTAT; /* UART Error Status registers */
	unsigned int UFSTAT;  /* UART FIFO Status registers */
	unsigned int UMSTAT; /* UART Modem status registers */
	unsigned int UTXH_L; /* UART Transmit buffer register (Holding register & FIFO register) */
	unsigned int UTXH_B; /* UART Transmit buffer register (Holding register & FIFO register) */
	unsigned int URXH_L; /* UART Receive buffer register (Holding register & FIFO register) */
	unsigned int URXH_B; /* UART Receive buffer register (Holding register & FIFO register) */
	unsigned int UBRDIV; /* UART Baud rate divisor register */

};


#endif
