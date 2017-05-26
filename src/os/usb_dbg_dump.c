#include "usb_ohci.h"
#include "uart_util.h"
#include "usb.h"
#include "usb_dbg_dump.h"

void dump_buff(uint8_t *buff, uint8_t len)
{
	uint8_t i =  0;

	uart_puts(UART0_BA, "D:");
	for(i = 0; i<len; i++) {
		print_hex_uart_ch(UART0_BA,buff[i]);
		uart_puts(UART0_BA," ");
	}
	uart_puts(UART0_BA, "\n");
}

void dump_dev_desc(struct desc_dev *desc_dev)
{
	uart_puts(UART0_BA, "Len: ");
	print_hex_uart_ch(UART0_BA, desc_dev->bLength);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "DT: ");
	print_hex_uart_ch(UART0_BA, desc_dev->bDescriptorType);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "USB: ");
	print_hex_uart_short(UART0_BA, desc_dev->bcdUsb);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "DC: ");
	print_hex_uart_ch(UART0_BA, desc_dev->bDeviceClass);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "SC: ");
	print_hex_uart_ch(UART0_BA, desc_dev->bDeviceSubClass);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "DP: ");
	print_hex_uart_ch(UART0_BA, desc_dev->bDeviceProtocol);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "MPS: ");
	print_hex_uart_ch(UART0_BA, desc_dev->bMaxPacketSize0);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "idV: ");
	print_hex_uart_short(UART0_BA, desc_dev->idVendor);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "idP: ");
	print_hex_uart_short(UART0_BA, desc_dev->idProduct);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "MF: ");
	print_hex_uart_ch(UART0_BA, desc_dev->iManufacturer);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "PD: ");
	print_hex_uart_ch(UART0_BA, desc_dev->iProduct);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "SN: ");
	print_hex_uart_ch(UART0_BA, desc_dev->iSerialNumber);
	uart_puts(UART0_BA, "\n");

	uart_puts(UART0_BA, "NC: ");
	print_hex_uart_ch(UART0_BA, desc_dev->bNumConfigurations);
	uart_puts(UART0_BA, "\n");
}

void dump_error_str(const uint8_t condition_code)
{
	uart_puts(UART0_BA, "ERROR Status-> ");
	switch(condition_code) {
		case NoError:
			uart_puts(UART0_BA, "No Err\n");
			break;
		case CRC:
			uart_puts(UART0_BA, "Crc Err\n");
			break;
		case DataToggleMismatch:
			uart_puts(UART0_BA, "DataToggleMismatch\n");
			break;
		case Stall:
			uart_puts(UART0_BA, "Stall\n");
			break;
		case DeviceNotResponding:
			uart_puts(UART0_BA, "Device not responding \n");
			break;
		case PIDCheckFailure:
			uart_puts(UART0_BA, "PID Chk failure\n");
			break;
		case UnexpectedPID:
			uart_puts(UART0_BA, "Unexpected PID\n");
			break;
		case DataOverrun:
			uart_puts(UART0_BA, "Data Overrun\n");
			break;
		case DataUnderrun:
			uart_puts(UART0_BA, "Data Underrun\n");
			break;
		case BufferOverrun:
			uart_puts(UART0_BA, "Buffer Overrun\n");
			break;
		case BufferUnderrun:
			uart_puts(UART0_BA, "Buffer Underrun\n");
			break;
		case NotAccessed:
			uart_puts(UART0_BA, "Not Accessed\n");
			break;
	}
}

void dump_td(
		struct GEN_TRANSFER_DESCRIPTOR *hc_gen_td)
{
	uart_puts(UART0_BA,"TD addr:");
	print_hex_uart(UART0_BA,(uintptr_t)hc_gen_td);

	uart_puts(UART0_BA,"TDCTRL : ");
	print_hex_uart(UART0_BA,
			(uintptr_t)hc_gen_td->td_control);

	uart_puts(UART0_BA,"CBP : ");
	print_hex_uart(UART0_BA,
			(uintptr_t)hc_gen_td->current_buffer_pointer);

	uart_puts(UART0_BA,"NXT_TD : ");
	print_hex_uart(UART0_BA,
			(uintptr_t)hc_gen_td->next_td);

	uart_puts(UART0_BA,"buffer_end: ");
	print_hex_uart(UART0_BA,
			(uintptr_t)hc_gen_td->buffer_end);
	
	dump_error_str(((hc_gen_td->td_control) & (CC_MASK)) >> (CC_SHIFT));

	if(hc_gen_td->current_buffer_pointer) {
		dump_buff((uint8_t *)hc_gen_td->current_buffer_pointer, MPS_8);
	}

	uart_puts(UART0_BA,"\n");
/*	while(hc_gen_td != 0) {
		uart_puts(UART0_BA,"\t->");
		print_hex_uart(UART0_BA,
						(uint32_t) hc_gen_td);
		hc_gen_td =
			(struct GEN_TRANSFER_DESCRIPTOR *)(hc_gen_td->next_td);
	}*/
}

void dump_ed_desc(struct HC_ENDPOINT_DESCRIPTOR *hc_ed)
{
	uart_puts(UART0_BA,"Endpt ctrl: ");
	print_hex_uart(UART0_BA,hc_ed->endpoint_ctrl);

	uart_puts(UART0_BA,"TailP: ");
	print_hex_uart(UART0_BA,hc_ed->TailP);

	uart_puts(UART0_BA,"HeadP: ");
	print_hex_uart(UART0_BA,hc_ed->HeadP);

	uart_puts(UART0_BA,"NextED: ");
	print_hex_uart(UART0_BA,hc_ed->NextED);
	uart_puts(UART0_BA,"\n");
}

void dump_usb_controller_functional_state()
{
	const uint8_t control_state = readreg32(HC_CONTROL_REG(USB_OHCI_BA));

	uart_puts(UART0_BA, "USB State : ");

	switch((control_state & HCFS_MASK)>>HCFS_SHIFT){
		case 0:
			uart_puts(UART0_BA, "Reset\n");
			break;
		case 1:
			uart_puts(UART0_BA, "Resume\n");
			break;
		case 2:
			uart_puts(UART0_BA, "Operational\n");
			break;
		case 3:
			uart_puts(UART0_BA, "Suspend\n");
			break;
	}

	return;
}

void dump_usb_port_status()
{
	uint8_t num_ports = ((readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA))) & NDP_MASK);
	uint8_t i = 0;

	uart_puts(UART0_BA,"Port status :");
	for(i = 0; i<num_ports; i++) {
		print_hex_uart(UART0_BA,
			readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,i)));
	}
	uart_puts(UART0_BA,"\n");
/*
	uart_puts(UART0_BA,"Port1 status :");
	print_hex_uart(UART0_BA,
		readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,PORT1)));

	uart_puts(UART0_BA,"Port2 status :");
	print_hex_uart(UART0_BA,
		readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,PORT2)));
*/
}

/*
void dump_interrupt_register_status()
{
	uart_puts(UART0_BA,"Interrupt enable status reg :");
	print_hex_uart(UART0_BA,
			readreg32(HC_INTERRUPT_ENABLE_REG(USB_OHCI_BA)));

	uart_puts(UART0_BA,"Interrupt disable status reg :");
	print_hex_uart(UART0_BA,
			readreg32(HC_INTERRUPT_DISABLE_REG(USB_OHCI_BA)));

	uart_puts(UART0_BA,"Interrupt status reg :");
	print_hex_uart(UART0_BA,
			readreg32(HC_INTERRUPT_STATUS_REG(USB_OHCI_BA)));
}
*/

/*
void dump_control_command_status()
{
	uart_puts(UART0_BA,"Command Status Reg: ");
	print_hex_uart(UART0_BA,
					readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA))
					);

	uart_puts(UART0_BA,"Control Reg: ");
	print_hex_uart(UART0_BA,
					readreg32(HC_CONTROL_REG(USB_OHCI_BA))
					);

	dump_usb_controller_functional_state();

}
*/

/*
void dump_rh_desc_ab(void)
{
	uart_puts(UART0_BA,"RH_A:");
	print_hex_uart(UART0_BA,
		readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA)));*/
/*
	uart_puts(UART0_BA,"NDP:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA)) & NDP_MASK));

	uart_puts(UART0_BA,"PSM:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA)) & PSM)>>8);

	uart_puts(UART0_BA,"NPS:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA)) & NPS)>>9);

	uart_puts(UART0_BA,"DT:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA)) & DT)>>10);

	uart_puts(UART0_BA,"OCPM:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA)) & OCPM)>>11);

	uart_puts(UART0_BA,"NOCP:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA)) & NOCP)>>12);

	uart_puts(UART0_BA,"POTPGT:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_A_REG(USB_OHCI_BA)) & POTPGT)>>24);
*/
/*
	uart_puts(UART0_BA,"RH_B:");
	print_hex_uart(UART0_BA,
		readreg32(HC_RH_DESCRIPTOR_B_REG(USB_OHCI_BA)));
*/
/*
	uart_puts(UART0_BA,"PPCM:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_B_REG(USB_OHCI_BA)) & 	PPCM_MASK)>>16);

	uart_puts(UART0_BA,"DR:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_DESCRIPTOR_B_REG(USB_OHCI_BA)) & 	DR_MASK));
*/
/*
}*/

/*
static void dump_rh_status(void)
{
	//NOTE: The status is all '0' and does not have much significance.

	uart_puts(UART0_BA,"LPS:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_STATUS_REG(USB_OHCI_BA)) & LPS));

	uart_puts(UART0_BA,"OCI:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_STATUS_REG(USB_OHCI_BA)) & OCI)>>1);

	uart_puts(UART0_BA,"DRWE:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_STATUS_REG(USB_OHCI_BA)) & DRWE)>>15);

	uart_puts(UART0_BA,"LPSC:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_STATUS_REG(USB_OHCI_BA)) & LPSC)>>16);

	uart_puts(UART0_BA,"OCIC:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_STATUS_REG(USB_OHCI_BA)) & OCIC_RH)>>17);

	uart_puts(UART0_BA,"CRWE:");
	print_hex_uart(UART0_BA,
		(readreg32(HC_RH_STATUS_REG(USB_OHCI_BA)) & CRWE)>>31);
}
*/



/*
void dump_currentED_reg(void)
{*/

/*	uart_puts(UART0_BA,"PCED :");
	print_hex_uart(UART0_BA,
			readreg32(HC_PERIOD_CURRENT_ED_REG(USB_OHCI_BA)));
*/
/*
	uart_puts(UART0_BA,"CCED :");
	print_hex_uart(UART0_BA,
			readreg32(HC_CONTROL_CURRENT_ED_REG(USB_OHCI_BA)));
*/
/*
	uart_puts(UART0_BA,"BCED :");
	print_hex_uart(UART0_BA,
			readreg32(HC_BULK_CURRENT_ED_REG(USB_OHCI_BA)));
*/
/*
}*/

