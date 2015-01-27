#ifndef UART_CTRL_H_
#define UART_CTRL_H_

#include <stdint.h>

struct uart_hw_regs {
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

struct uart_hw_resource {
	struct uart_hw_regs *regs;
};

struct uart_cntrl
{
	int32_t (*init_gpio)(struct uart_hw_resource *uart_resource); //Initialize gpio pins

	int32_t (*deinit_gpio)(struct uart_hw_resource *uart_resource); //Deinitialize gpio pins
	int32_t (*clk_enable)(struct uart_hw_resource *uart_resource);
	int32_t (*clk_disable)(struct uart_hw_resource *uart_resource);
	int32_t (*send) (struct uart_hw_resource  *uart_resource);
	int32_t (*receive) (struct uart_hw_resource  *uart_resource);
	uint32_t (*get_tx_count) (struct uart_hw_resource *uart_resource);
	uint32_t (*get_rx_count) (struct uart_hw_resource *uart_resource);

};

#endif
