#include "usb_ohci.h"
#include "uart_util.h"

/* 
 * hcca_region should be 256 byte boundary attached. 
 * Hence should move the poiner so that the address is
 * 256 byte boundary aligned.
 */

uint8_t hcca_region[512];

uint8_t ed_list[MAX_ED_DESCRIPTORS << ED_SIZE_SHIFT];
uint8_t td_list[MAX_TD_DESCRIPTORS << TD_SIZE_SHIFT];
uint8_t iso_td_list[MAX_ISO_TD_DESCRIPTORS << ISO_TD_SIZE_SHIFT];

struct ed_info ed_info;
struct td_info td_info;


static void init_ed(struct ed_info *ed_info, 
						uint8_t *ed_ll)
{
	uint32_t i = 0;
	ed_info->hc_ed = 0;
	ed_info->size = 0;


	ed_info->hc_ed = (struct HC_ENDPOINT_DESCRIPTOR *)
						nbyte_align(
							(uintptr_t)ed_ll,
							HC_ED_ALIGNMENT
							);


//	print_hex_uart(UART0_BA,(uintptr_t)ed_ll);
//	print_hex_uart(UART0_BA,(uintptr_t)ed_info->hc_ed);




	for(i = 0; ; i++,ed_info->size++) {
		//If the index + 1 i.e. sizeof the structure crosses the pool size.
		if(((uintptr_t)((ed_info->hc_ed) + (i+1))) > 
			((uintptr_t)(ed_ll + ED_TOTAL_SIZE))) {
			break;
		}
		ed_info->hc_ed[i].endpoint_ctrl = 0;
		ed_info->hc_ed[i].TailP = 0;
		ed_info->hc_ed[i].HeadP = 0;
		ed_info->hc_ed[i].NextED = 0;
	}



//	print_hex_uart(UART0_BA,(uintptr_t)(ed_ll+ED_TOTAL_SIZE));
//	print_hex_uart(UART0_BA,(uintptr_t)(ed_info->hc_ed+i));
//	print_hex_uart(UART0_BA,(uintptr_t)(ed_info->hc_ed+(i-1)));

}


static void init_td(struct td_info *td_info, 
						uint8_t *td_ll)
{
	uint32_t i = 0;

	td_info->hc_gen_td = 0;
	td_info->size = 0;

	td_info->hc_gen_td = (struct GEN_TRANSFER_DESCRIPTOR *)
							nbyte_align(
								(uintptr_t)td_ll,
								HC_GEN_TD_ALIGNMENT
								);


//	print_hex_uart(UART0_BA,(uintptr_t)td_ll);
//	print_hex_uart(UART0_BA,(uintptr_t)td_info->hc_gen_td);


	for(i = 0; ; i++,td_info->size++) {
		//If the index + 1 i.e. sizeof the structure crosses the pool size.
		if(((uintptr_t)((td_info->hc_gen_td) + (i+1)))  > 
					((uintptr_t)(td_ll+TD_TOTAL_SIZE)))
		{
			break;
		}

		td_info->hc_gen_td[i].td_control = 0;
		td_info->hc_gen_td[i].current_buffer_pointer = 0;
		td_info->hc_gen_td[i].next_td = 0;
		td_info->hc_gen_td[i].buffer_end = 0;
	}

//	print_hex_uart(UART0_BA,(uintptr_t)((td_info->hc_gen_td)+i));
//	print_hex_uart(UART0_BA,(uintptr_t)((td_info->hc_gen_td)+i-1));
//	print_hex_uart(UART0_BA,(uintptr_t)(td_ll+TD_TOTAL_SIZE));
}
						

static void config_ep0(struct ed_info *ed_info,struct td_info *td_info)
{
	//Set the function address to 0 initially.
	set_hc_ed_fa(&(ed_info->hc_ed[0].endpoint_ctrl),0);
	//Set the endpoint to 0.
	set_hc_ed_en(&(ed_info->hc_ed[0].endpoint_ctrl),0);
	set_hc_ed_dir(&(ed_info->hc_ed[0].endpoint_ctrl),GET_DIR_FROM_TD);
	set_hc_ed_speed(&(ed_info->hc_ed[0].endpoint_ctrl),
									HIGH_SPEED);
	set_hc_ed_mps(&(ed_info->hc_ed[0].endpoint_ctrl),64);

	ed_info->hc_ed[0].HeadP = 0;
	ed_info->hc_ed[0].NextED = 0;

	//Setup the td for the ed. I will setup a single td at index 0.
	/*writereg32(&(td_info->hc_gen_td[0].td_control),
				BUFFER_ROUND|DP_SETUP|*/
	
}

void set_end_point_config(struct ed_info *ed_info,
								uint32_t ed_idx)
{
}

void init_ohci()
{
	
	struct HCCARegion *hccaregion = 0;

	//Check alignment. Verified it as 256 bytes.
/*	
	writereg32(HC_HCCA_REG(USB_OHCI_BA),0xFFFFFFFF);
	print_hex_uart(UART0_BA,readreg32(HC_HCCA_REG(USB_OHCI_BA)));
*/
	uint32_t HcFmInterval = 0;

	init_ed(&ed_info,ed_list);
	init_td(&td_info,td_list);
	config_ep0(&ed_info,&td_info);

	uart_puts(UART0_BA,"HcRevision :");
	print_hex_uart(UART0_BA,
			readreg32(HC_REVISION_REG(USB_OHCI_BA)));

	HcFmInterval = readreg32(HC_FM_INTERVAL_REG(USB_OHCI_BA));
	
	// Reset the Host controller
	writereg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA),
		readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA)) | HCR);

	// Host controller sets itself to 0 after 10s
	while(readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA)) & HCR)
		;

	// Write the HcFmInterval register back after reset
	writereg32(HC_FM_INTERVAL_REG(USB_OHCI_BA),HcFmInterval);

	uart_puts(UART0_BA,"USB Reset\r\n");

	hccaregion = (struct HCCARegion *)nbyte_align(((uintptr_t)hcca_region),256);
	
/*
	print_hex_uart(UART0_BA,
						(uintptr_t)hcca_region);
	print_hex_uart(UART0_BA,
		nbyte_align(((uintptr_t) hcca_region),256));
*/

	//Write the HCCA register.
	writereg32(HC_HCCA_REG(USB_OHCI_BA),
		nbyte_align(((uintptr_t) hcca_region),256));

	//Enable all interrupts except Start of frame (SOF) 
	//in HcInterruptEnable register.
	writereg32(HC_INTERRUPT_ENABLE_REG(USB_OHCI_BA),0xC000007B);

	//Set to 90% of HcFmInterval.
	writereg32(HC_PERIODIC_START_REG(USB_OHCI_BA),((uint32_t)(0.9 * HcFmInterval)));
	//print_hex_uart(UART0_BA,readreg32(HC_CONTROL_REG(USB_OHCI_BA)));
	
	//Setup control registers.
	set_reg_params(HC_CONTROL_REG(USB_OHCI_BA),
					PLE|IE|CLE|BLE
					);

}
