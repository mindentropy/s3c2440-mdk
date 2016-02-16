#include "usb_ohci.h"
#include "uart_util.h"

/* 
 * hcca_region should be 256 byte boundary attached. 
 * Hence should move the poiner so that the address is
 * 256 byte boundary aligned.
 */

uint8_t hcca_region[512];

void init_ohci()
{
	
	uint32_t HcFmInterval = 0;

	uart_puts(UART0_BA,"HcRevision :");
	print_hex_uart(UART0_BA,
			readreg32(HC_REVISION_REG(USB_OHCI_BA)));

	HcFmInterval = readreg32(HC_FM_INTERVAL_REG(USB_OHCI_BA));
	
	/* Reset the Host controller */
	writereg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA),
		readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA)) | HCR);

	/* Host controller sets itself to 0 after 10s */
	while(readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA)) & HCR)
		;

	/* Write the HcFmInterval register back after reset */
	writereg32(HC_FM_INTERVAL_REG(USB_OHCI_BA),HcFmInterval);

	uart_puts(UART0_BA,"USB Reset\r\n");

	print_hex_uart(UART0_BA,
						(uintptr_t)hcca_region);
	print_hex_uart(UART0_BA,
		nbyte_align(((uintptr_t) hcca_region),256));
}
