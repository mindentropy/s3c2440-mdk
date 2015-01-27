#include "uart.h"

#include "uart_ctrl.h"

struct uart_hw_resource uart0_resource = {
	.uart_hw_regs = (struct uart_hw_regs *)UART0_BA;
};

int32_t init_uart(struct uart_hw_resource *resource)
{
	
}
