#include "usb_ohci.h"
#include "uart_util.h"
#include "usb.h"

/* 
 * hcca_region should be 256 byte boundary attached. 
 * Hence should move the poiner so that the address is
 * 256 byte boundary aligned.
 */

uint8_t hcca_region[512];
struct HCCARegion *hccaregion_reg;

uint8_t ed_list[MAX_ED_DESCRIPTORS << ED_SIZE_SHIFT];
uint8_t td_list[MAX_TD_DESCRIPTORS << TD_SIZE_SHIFT];
uint8_t iso_td_list[MAX_ISO_TD_DESCRIPTORS << ISO_TD_SIZE_SHIFT];

uint8_t usb_buffer_pool[512];

struct ed_info ed_info;
struct td_info td_info;
uint32_t HcFmInterval = 0;

static void usb_delay()
{
	volatile int i = 0;
	volatile int j = 0;

	for(i = 0; i< 10000; i++) {
		for(j = 0; j<100;j++)
		{
			;
		}
	}
}

static void dump_td(
		struct GEN_TRANSFER_DESCRIPTOR *hc_gen_td)
{
	uart_puts(UART0_BA,"TD dump\n");

	uart_puts(UART0_BA,"TDCTRL : ");
	print_hex_uart(UART0_BA,(uintptr_t)hc_gen_td->
td_control);
	uart_puts(UART0_BA,"NXT_TD : ");
	print_hex_uart(UART0_BA,(uintptr_t)hc_gen_td->next_td);

	uart_puts(UART0_BA,"buffer_end: ");
	print_hex_uart(UART0_BA,(uintptr_t)hc_gen_td->buffer_end);

/*	while(hc_gen_td != 0) {
		uart_puts(UART0_BA,"\t->");
		print_hex_uart(UART0_BA,
						(uint32_t) hc_gen_td);
		hc_gen_td =
			(struct GEN_TRANSFER_DESCRIPTOR *)(hc_gen_td->next_td);
	}*/
}



static void dump_ed(
				struct ed_info *edp_info
				)
{
	struct HC_ENDPOINT_DESCRIPTOR *hc_ed = edp_info->hc_ed;

	print_hex_uart(UART0_BA,(uintptr_t)edp_info->hc_ed[0].HeadP);

/*	uart_puts(UART0_BA,"ED size : ");
	print_hex_uart(UART0_BA,edp_info->size);

	while(hc_ed != 0) {
		uart_puts(UART0_BA,"->");
		print_hex_uart(UART0_BA, (uintptr_t)hc_ed);

		uart_puts(UART0_BA,"\tED Ctrl :");
		print_hex_uart(UART0_BA, hc_ed->endpoint_ctrl);

		//dump_td((struct GEN_TRANSFER_DESCRIPTOR *) hc_ed->HeadP);
		print_hex_uart(UART0_BA,(uintptr_t)hc_ed->HeadP);

		hc_ed = (struct HC_ENDPOINT_DESCRIPTOR *)hc_ed->NextED;
	}*/
}

static void dump_currentED_reg(void)
{

/*	uart_puts(UART0_BA,"PCED :");
	print_hex_uart(UART0_BA,
			readreg32(HC_PERIOD_CURRENT_ED_REG(USB_OHCI_BA)));
*/

	uart_puts(UART0_BA,"CCED :");
	print_hex_uart(UART0_BA,
			readreg32(HC_CONTROL_CURRENT_ED_REG(USB_OHCI_BA)));

/*
	uart_puts(UART0_BA,"BCED :");
	print_hex_uart(UART0_BA,
			readreg32(HC_BULK_CURRENT_ED_REG(USB_OHCI_BA)));
*/

}

static void init_ed(struct ed_info *edp_info,
						uint8_t *ed_ll)
{
	uint32_t i = 0;
	edp_info->hc_ed = 0;
	edp_info->size = 0;


	edp_info->hc_ed = (struct HC_ENDPOINT_DESCRIPTOR *)
						nbyte_align(
							(uintptr_t)ed_ll,
							HC_ED_ALIGNMENT
							);


//	print_hex_uart(UART0_BA,(uintptr_t)ed_ll);
//	print_hex_uart(UART0_BA,(uintptr_t)edp_info->hc_ed);


	for(i = 0; ; i++,edp_info->size++) {
		//If the index + 1 i.e. sizeof the structure crosses the pool size.
		if(((uintptr_t)((edp_info->hc_ed) + (i+1))) >
			((uintptr_t)(ed_ll + ED_TOTAL_SIZE))) {
			break;
		}
		edp_info->hc_ed[i].endpoint_ctrl = 0;
		edp_info->hc_ed[i].TailP = 0;
		edp_info->hc_ed[i].HeadP = 0;
		edp_info->hc_ed[i].NextED = 0;
	}


//	print_hex_uart(UART0_BA,(uintptr_t)(ed_ll+ED_TOTAL_SIZE));
//	print_hex_uart(UART0_BA,(uintptr_t)(edp_info->hc_ed+i));
//	print_hex_uart(UART0_BA,(uintptr_t)(edp_info->hc_ed+(i-1)));

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

		print_hex_uart(UART0_BA,(uintptr_t)(&(td_info->hc_gen_td[i])));
	}

//	print_hex_uart(UART0_BA,(uintptr_t)((td_info->hc_gen_td)+i));
//	print_hex_uart(UART0_BA,(uintptr_t)((td_info->hc_gen_td)+i-1));
//	print_hex_uart(UART0_BA,(uintptr_t)(td_ll+TD_TOTAL_SIZE));
}
						

static void 
		get_dev_descriptor(
				struct ed_info *ed_info,
				struct td_info *td_info,
				void *usb_buff_pool
				)
{
	struct usb_request *usb_req;

	//Set the function address to 0 initially.
	set_hc_ed_fa(
			&(ed_info->hc_ed[0].endpoint_ctrl),
			0
		);

	//Set the endpoint to 0.
	set_hc_ed_en(
			&(ed_info->hc_ed[0].endpoint_ctrl),
			0
		);

	//Get the direction from td and not from ed.
	set_hc_ed_dir(
			&(ed_info->hc_ed[0].endpoint_ctrl),
			GET_DIR_FROM_TD
		);

	set_hc_ed_speed(
			&(ed_info->hc_ed[0].endpoint_ctrl),
			HIGH_SPEED //Set to high speed.
		);

	set_hc_ed_mps(
			&(ed_info->hc_ed[0].endpoint_ctrl),
			64U //Set max pkt size to 64.
		);

	//Dump the endpoint_ctrl for verification.
	/*uart_puts(UART0_BA,"Endpt ctrl : ");
	print_hex_uart(UART0_BA,ed_info->hc_ed[0].endpoint_ctrl);*/

	ed_info->hc_ed[0].HeadP = 0; //Init to 0.
	ed_info->hc_ed[0].NextED = 0; //Zero since this is the only descriptor.

	//Setup the td for the ed. I will setup a single td at index 0.

	/* 
	 * Initialize 3 td's,the first td to send the request,
	 * the second td to receive the response and 
	 * the last td being the 'terminator' td with
	 * all 0's
	 */

	writereg32(
				&(td_info->hc_gen_td[0].td_control),
					BUFFER_ROUND
					|DP_SETUP
					|NO_DELAY_INTERRUPT
					|DATA_TOGGLE(2) /* 
									 * See pg24(39) of spec. 
									 * DATA0 data PID for setup packet, 
									 * MSB of dataToggle = 1 for setup
									 * and LSB of dataToggle = 0 for setup.
									 */
					|CC(NotAccessed) /* 
					                  * See pg35(50) of spec.
					                  * 
									  */
			);

/*	uart_puts(UART0_BA,"TD0 control :");
	print_hex_uart(UART0_BA,td_info->hc_gen_td[0].td_control);*/
	
	writereg32(
				&(td_info->hc_gen_td[1].td_control),
					BUFFER_ROUND
					|IN
					|NO_DELAY_INTERRUPT
					|DATA_TOGGLE(3) /* 
									 * See pg24(39) of spec.
									 * DATA0 data PID for setup packet, 
									 * MSB of dataToggle = 1 for status 
									 * and LSB of dataToggle = 1 for setup.
									 */
					|CC(NotAccessed) /* 
					                  * See pg35(50) of spec.
					                  * 
									  */
			);
	
/*	uart_puts(UART0_BA,"TD1 control :");
	print_hex_uart(UART0_BA,td_info->hc_gen_td[1].td_control);*/

	writereg32(
				&(td_info->hc_gen_td[0].current_buffer_pointer),
				(uintptr_t)usb_buff_pool
			);

	writereg32(
				&(td_info->hc_gen_td[0].buffer_end),
				(uintptr_t)(usb_buff_pool+31)
			);

	usb_req = (struct usb_request *)(
				&(td_info->hc_gen_td[0].current_buffer_pointer));

	/* 
	 * Set the current buffer pointer for td0 to get device
	 * descriptor
	 */ 
	usb_get_descriptor( 
			usb_req,
			DESC_DEVICE,
			0,
			18);


	/*
	 * Set the second buffer to 32 bytes from the initial 
	 * buffer pool 
	 */
	writereg32(&(td_info->hc_gen_td[1].current_buffer_pointer),
				(uintptr_t)usb_buff_pool+32);

	writereg32(&(td_info->hc_gen_td[1].buffer_end),
				(uintptr_t)usb_buff_pool+63);
	
	/* Set the td0 next_td to td1 */
	writereg32(&(td_info->hc_gen_td[0].next_td),
				(uintptr_t)(&(td_info->hc_gen_td[1])));

	/* Set the td1 next_td to td2 */
	writereg32(&(td_info->hc_gen_td[1].next_td),
				(uintptr_t)(&(td_info->hc_gen_td[2])));


	// Setup the head and tail pointers of ED to point to the TD's.
	ed_info->hc_ed[0].HeadP = (uintptr_t)(&(td_info->hc_gen_td[0]));
	ed_info->hc_ed[0].TailP = (uintptr_t)(&(td_info->hc_gen_td[2]));
	
}

void set_end_point_config(struct ed_info *ed_info,
								uint32_t ed_idx)
{
}

static void dump_usb_controller_functional_state(const uint8_t control_state)
{
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

static void dump_control_command_status()
{
	uart_puts(UART0_BA,"Command Status Reg: ");
	print_hex_uart(UART0_BA,
					readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA))
					);

	uart_puts(UART0_BA,"Control Reg: ");
	print_hex_uart(UART0_BA,
					readreg32(HC_CONTROL_REG(USB_OHCI_BA))
					);

	dump_usb_controller_functional_state(readreg32(HC_CONTROL_REG(USB_OHCI_BA)));

}

static void dump_usb_port_status()
{
	
	uart_puts(UART0_BA,"Port1 status :");
	print_hex_uart(UART0_BA,
		readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,PORT1)));

	uart_puts(UART0_BA,"Port2 status :");
	print_hex_uart(UART0_BA,
		readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,PORT2)));
}

static void dump_interrupt_register_status()
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

/*
 * Setting up USB for getting intial config data.
 * ==============================================
 * 
 * 1) Initialize ed.
 * 2) Initialize td.
 * 3) Save the HcFmInterval register for later setup.
 * 4) Reset the host controller.
 * 5) Wait until the host controller sets itself to 0 after 10s.
 * 6) Write back the save HcFmInterval register.
 */

static void reset_ohci_controller()
{

	/* Clear the control register */
	writereg32(HC_CONTROL_REG(USB_OHCI_BA),
					0x0U);
	/* Disable all interrupts */
	writereg32(
			HC_INTERRUPT_DISABLE_REG(USB_OHCI_BA),
			MIE|OC|RHSC|FNO|UE|RD|SF|WDH|SO
			);

	/* Reset the Host controller */
	writereg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA),
				(readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA)))
				|HCR
				);

	/* Host controller sets itself to 0 after 10ms */
	while(readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA)) & HCR)
		;

	/* Clear the interrupt status register */
	writereg32(
			HC_INTERRUPT_STATUS_REG(USB_OHCI_BA),
			OC|RHSC|FNO|UE|RD|SF|WDH|SO
			);

	/*
	 * Host controller will be in suspend state. See Pg 116(131)
	 */
	//dump_control_command_status();
	//dump_interrupt_register_status();

}

static void setup_ohci(void)
{
	uint16_t i = 0;
	
	/* Clear the hcca_region */
	for(i = 0; i<512; i++) {
		hcca_region[i] = 0x0U;
	}

	/* Write the HCCA register. */
	writereg32(HC_HCCA_REG(USB_OHCI_BA),
		nbyte_align(((uintptr_t) hcca_region),256));

	hccaregion_reg = (struct HCCARegion *)readreg32(HC_HCCA_REG(USB_OHCI_BA));
/*
	hccaregion = (struct HCCARegion *)
						nbyte_align(((uintptr_t)hcca_region),256);
	
	print_hex_uart(UART0_BA,
						(uintptr_t)hcca_region);
	print_hex_uart(UART0_BA,
		nbyte_align(((uintptr_t) hcca_region),256));
*/

	/*
     * Write default value to lsthreshold.
     * See section 7.3.5 of spec
     */
	writereg32(HC_LS_THRESHOLD_REG(USB_OHCI_BA),
					0x628U);
	
	/*** Write the ControlED to the HcControlHeadED register. ***/
	writereg32(
				HC_CONTROL_HEAD_ED_REG(USB_OHCI_BA),
				(uintptr_t)ed_info.hc_ed
			);
	/*
	 * Init the HcControlCurrentED register to 0 to indicate
	 * the end of the control list.
	 * TODO: Check if 0 is a valid value. In addition make sure
	 * ControlListEnable (CLE) is cleared.
	 *
	 */
	writereg32(HC_CONTROL_CURRENT_ED_REG(USB_OHCI_BA),0);

	//TODO:Set the ControlBulkED to an ED.
	
	/*
	 * Enable all interrupts except Start of frame (SOF) 
	 * in HcInterruptEnable register.
	 */
	/*writereg32(HC_INTERRUPT_ENABLE_REG(USB_OHCI_BA),0xC000007B);*/
	writereg32(HC_INTERRUPT_ENABLE_REG(USB_OHCI_BA),
					SO|WDH|RD|UE|FNO|RHSC|OC|MIE);
	/* Set control registers to enable control queue. */
	set_reg_bits(
				HC_CONTROL_REG(USB_OHCI_BA),
				CLE
				);

	/* Set to 90% of HcFmInterval. */
	writereg32(HC_PERIODIC_START_REG(USB_OHCI_BA),((uint32_t)(0.9 * HcFmInterval)));

	/*
	 * Write the HcFmInterval register back after reset with the FSMPS value
	 * calculated as below.
     */
	HcFmInterval |= (((HcFmInterval - MAXIMUM_OVERHEAD) * 6)/7) << 16;
	writereg32(HC_FM_INTERVAL_REG(USB_OHCI_BA),HcFmInterval);
	uart_puts(UART0_BA,"HcFmInterval : ");
	print_hex_uart(UART0_BA,HcFmInterval);
}

void init_ohci()
{
	
/*	struct HCCARegion *hccaregion = 0; */

	/* Check alignment. Verified it as 256 bytes. */
/*
	writereg32(HC_HCCA_REG(USB_OHCI_BA),0xFFFFFFFF);
	print_hex_uart(UART0_BA,readreg32(HC_HCCA_REG(USB_OHCI_BA)));
*/

	init_usb();

	init_ed(&ed_info,ed_list);
	init_td(&td_info,td_list);

	get_dev_descriptor(&ed_info,&td_info,usb_buffer_pool);

	uart_puts(UART0_BA,"HcRevision :");
	print_hex_uart(UART0_BA,
				readreg32(HC_REVISION_REG(USB_OHCI_BA))
				);

	/* Save the HcFmInterval register for later set up. */
	HcFmInterval = readreg32(HC_FM_INTERVAL_REG(USB_OHCI_BA));

	/* Reset the OHCI controller */
	reset_ohci_controller();

	setup_ohci();
	
	dump_ed(&ed_info);

	/* Set the control list filled. */
	set_reg_bits(HC_COMMAND_STATUS_REG(USB_OHCI_BA),CLF);

	hc_rh_set_port_enable(USB_OHCI_BA,PORT1);

	/* Set to USB_OPERATIONAL to start sending SOF. */
	set_regs_value(HC_CONTROL_REG(USB_OHCI_BA),
					HCFS_MASK,
					HCFS_USB_OPERATIONAL<<HCFS_SHIFT
					);
	/*
	 * Test Poll for data.
	 */


	while(!(readreg32(HC_INTERRUPT_STATUS_REG(USB_OHCI_BA)) & WDH)) {
		;
	}

	dump_ed(&ed_info);

	uart_puts(UART0_BA,"HccaDoneHead: ");
	print_hex_uart(UART0_BA,
				((hccaregion_reg->HccaDoneHead) & 0xFFFFFFF0));
	dump_td((struct GEN_TRANSFER_DESCRIPTOR *)((hccaregion_reg->HccaDoneHead & 0xFFFFFFF0)));
	//dump_currentED_reg();
	//dump_interrupt_register_status();

	//dump_usb_port_status();
	//dump_usb_controller_functional_state(readreg32(HC_CONTROL_REG(USB_OHCI_BA)));
}
