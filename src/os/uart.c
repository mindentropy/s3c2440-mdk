#include "common.h"
#include "uart_util.h"
#include "gpio_def.h"
#include "clock_pm.h"
#include "interrupt.h"
#include "exception_interrupt.h"
#include "led.h"

#include "cq.h"

struct cq tx_q;
struct cq rx_q;

uint8_t txbuff[UART_Tx_BUFF_SIZE];
uint8_t rxbuff[UART_Rx_BUFF_SIZE];

const char hexchar[] = 
	{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

char getc(uint32_t UART_BA)
{
	while(!uart_is_rx_buff_full(UART_BA))
		;

	return uart_readl_ch(UART_BA);
}


int uart_getbuff(char *buff,int length)
{
	int i;
	for(i = 0;i<length;i++) {
		if(!cq_is_empty(&rx_q)) {
			buff[i] = cq_del(&rx_q);
		} else {
			break;
		}
	}
	return i;
}


#ifdef UART_INT
/*
 * NOTE: uart_puts and putc still blocks until the buffer sent to it is drained completely.
 * TODO: Return the data written so that user space can decide to further drain the buffer.
 * TODO: Use the UART FIFO to create an additional buffer and reduce the costly per character
 * 		interrupts.
 */
void uart_puts(uint32_t UART_BA,const char *str)
{
	//Trigger the first interrupt if the buffer is empty.

//	mask_interrupt_service(INT_BA,INT_UART0);
	while((*str) != '\0') {

		mask_interrupt_service(INT_BA,INT_UART0);
		if(cq_is_empty(&tx_q) && uart_is_tx_buff_empty(UART_BA)) {
			uart_writel_ch(UART_BA,*str);
			unmask_interrupt_service(INT_BA,INT_UART0);
			str++;
			continue;
		}

		if(!cq_is_full(&tx_q)) {
			cq_add(&tx_q,*str);
			unmask_interrupt_service(INT_BA,INT_UART0);
			str++;
		} else {
			led_on(LED3);
			unmask_interrupt_service(INT_BA,INT_UART0);
			continue;
		}
	}
//	unmask_interrupt_service(INT_BA,INT_UART0);
}


void putc(uint32_t UART_BA, const char ch)
{

	while(1) {
		mask_interrupt_service(INT_BA,INT_UART0);
		if(cq_is_empty(&tx_q) && uart_is_tx_buff_empty(UART_BA)) {
			uart_writel_ch(UART_BA,ch);
			break;
		} else {
			if(!cq_is_full(&tx_q)) {
				cq_add(&tx_q,ch);
				break;
			} else {
				unmask_interrupt_service(INT_BA,INT_UART0);
				continue;
			}
		}
	}
	unmask_interrupt_service(INT_BA,INT_UART0);
}

#endif




#ifdef UART_NO_INT
void uart_puts(uint32_t UART_BA,const char *str)
{
	while((*str) != '\0') {
		putc(UART_BA,*str); /* Do not increment for the macro. Do it in the next line */
		str++;
	}
}
#endif

void print_hex_uart(uint32_t UART_BA,uint32_t num) 
{
	unsigned int i = 0;

	uart_puts(UART_BA,"0x");

	for(i = 0; i<8; i++) {
		putc(UART_BA,hexchar[(num & 0xF0000000)>>28]);
		num<<=4;
	}

	uart_puts(UART_BA,"\r\n");
}

void print_hex_uart_short(uint32_t UART_BA, uint16_t num)
{
	unsigned int i = 0;

	uart_puts(UART_BA,"0x");

	for(i = 0; i<4; i++) {
		putc(UART_BA,hexchar[(num & 0xF000) >> 12]);
		num<<=4;
	}
}

void print_hex_uart_ch(uint32_t UART_BA, uint8_t num)
{
	uart_puts(UART_BA,"0x");

	putc(UART_BA,hexchar[(num & 0xF0) >> 4]);
	num <<= 4;
	putc(UART_BA,hexchar[(num & 0xF0) >> 4]);
}


void uart0_interrupt_handler(void)
{
	/* Check if the interrupt is a Tx,Rx or Err. */
	char ch = 0;
	uint32_t error_status = 0;


	if(get_interrupt_sub_source_pending_status(INT_BA,SUBSRC_INT_RXD0)) {
		
		ch = uart_readl_ch(UART0_BA);
		if(!cq_is_full(&tx_q)) {
			cq_add(&tx_q,ch);
		}

		//Trigger an interrupt with a first write.
		if(uart_is_tx_empty(UART0_BA) && !cq_is_empty(&tx_q)) {
			uart_writel_ch(UART0_BA,cq_del(&tx_q));
		}
		
		clear_interrupt_sub_source_pending(INT_BA,SUBSRC_INT_RXD0);
	}

	if(get_interrupt_sub_source_pending_status(INT_BA,SUBSRC_INT_TXD0)) {
		if(!cq_is_empty(&tx_q)) {
			uart_writel_ch(UART0_BA,cq_del(&tx_q));
		}

		/* 
		 * Clear the sub source pending. After the character
		 * is transmitted and the buffer is empty an interrupt is
		 * again generated.
		 */
		clear_interrupt_sub_source_pending(INT_BA,SUBSRC_INT_TXD0);
	}

	if(get_interrupt_sub_source_pending_status(INT_BA,SUBSRC_INT_ERR0)) {
		error_status = get_uart_error_state(UART0_BA);
													

		if(error_status & BREAK_DETECT) {
			uart_puts(UART0_BA,"Break detect\n");
		}

		if(error_status & FRAME_ERROR) {
			uart_puts(UART0_BA,"Frame error\n");
		}

		if(error_status & PARITY_ERROR) {
			uart_puts(UART0_BA,"Parity error\n");
		}

		if(error_status & OVERRUN_ERROR) {
			uart_puts(UART0_BA,"Overrun error\n");
		}
	}

}

void init_uart(uint32_t UART_BA)
{

	apb_clk_enable(CLK_BASE_ADDR,CLK_UART0); //Enable the clock for UART block.
	set_gpio_con(GPH_BA,nCTS0|nRTS0|TXD0|RXD0); //Set the GPIO pins to UART function.

	set_ulcon_reg(UART_BA,WORD_LENGTH_8BITS);
	//writereg32(ULCON_REG(UART_BA),WORD_LENGTH); //Set line control.
	
	write_ucon_reg(UART_BA,
				(PCLK_SELECT
				|Rx_TIMEOUT_ENABLE
				|TRANSMIT_MODE_INTR_REQ_OR_POLLING
				|RECEIVE_MODE_INTR_REQ_OR_POLLING
				|Rx_ERROR_STATUS_INTR_ENABLE
				)
				);
	

	/* NOTE: PCLK set to 50MHz. Baud rate set to 26 for 115200*/
	set_uart_brdiv(UART_BA,get_uart_brdiv(UART_BA,BAUD_115200));

	write_ufcon_reg(UART_BA,Tx_FIFO_RESET|Rx_FIFO_RESET);
	write_ufcon_reg(UART_BA,FIFO_ENABLE);

	// Initialize Tx and Rx circular queue 
	cq_init(&tx_q,txbuff,UART_Tx_BUFF_SIZE);
	cq_init(&rx_q,rxbuff,UART_Rx_BUFF_SIZE);

	add_irq_handler(INT_UART0_OFFSET,uart0_interrupt_handler);
	
	clear_interrupt_sub_source_pending(INT_BA,
		(SUBSRC_INT_TXD0|SUBSRC_INT_RXD0|SUBSRC_INT_ERR0));
	clear_interrupt_source_pending(INT_BA,INT_UART0);
	clear_interrupt_pending(INT_BA,INT_UART0);


/*
 * Note on Tx Interrupt:
 * Tx interrupt happens when the Tx buffer is empty. This does not end there. There is
 * one more constraint. From the documentation: 
 * "In the Non-FIFO mode, transferring data from the transmit holding register to the transmit 
 *  shifter will cause Tx interrupt under the Interrupt request and polling mode."
 *
 * So to kick start the interrupt we need to place a byte initially into the buffer. When
 * this byte moves from the transmit holding register to the transmit shifter a Tx interrupt
 * will signalled.
 */
	unmask_interrupt_subservice(INT_BA,(SUBSRC_INT_TXD0|SUBSRC_INT_RXD0|SUBSRC_INT_ERR0));
	unmask_interrupt_service(INT_BA,INT_UART0);
}

