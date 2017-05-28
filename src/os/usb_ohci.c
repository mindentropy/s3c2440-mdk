#include "usb_ohci.h"
#include "uart_util.h"
#include "usb.h"
#include "usb_dbg_dump.h"
#include "string.h"

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

uint8_t usb_req_header[USB_DESC_SIZE];
uint8_t desc_dev_buff[sizeof(struct desc_dev)];

/*
static void usb_delay()
{
	volatile int i = 0;
	volatile int j = 0;

	for(i = 0; i< 10000; i++) {
		for(j = 0; j< 100; j++) {
			;
		}
	}
}
*/
/*
static void usb_short_delay()
{
	volatile int i = 0;

	for(i = 0; i< 10000; i++) {

	}
}
*/


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

		//print_hex_uart(UART0_BA,(uintptr_t)(&(td_info->hc_gen_td[i])));
	}

//	print_hex_uart(UART0_BA,(uintptr_t)((td_info->hc_gen_td)+i));
//	print_hex_uart(UART0_BA,(uintptr_t)((td_info->hc_gen_td)+i-1));
//	print_hex_uart(UART0_BA,(uintptr_t)(td_ll+TD_TOTAL_SIZE));
}

static int16_t get_free_ed_index(
			struct ed_info *ed_info)
{
	int16_t idx = 0;

	while(1)
	{
		if((ed_info->hc_ed[idx].HeadP == 0) &&
				(ed_info->hc_ed[idx].TailP == 0)) {
			/*
			 * If the HeadP and TailP equals fixed physical address 0 then the
			 * controller has stopped processing and the data is processed by
			 * the HCD. This means that the ED is free for reuse.
			 */
			return idx;
		}

		if(idx == (ed_info->size)) {
			/* We have reached the end of the ED and there is no more EDs.*/
			return -1;
		}

		idx++;
	}

	// We should not reach here.
	return -1;
}


static void set_ed_descriptor(
		struct ed_info *ed_info,
		uint8_t fa,
		uint8_t en,
		int16_t idx,
		enum Ports port
		)
{

	/* Set the function address and endpoint address */
	writereg32(&(ed_info->hc_ed[0].endpoint_ctrl),
				(fa<<FA_SHIFT)
				|(en<<EN_SHIFT)
				);
	/*
	 * Set the direction. Currently take the direction from TD
	 * and not ED.
	 */
	set_hc_ed_D(
			&(ed_info->hc_ed[0].endpoint_ctrl),
			GET_DIR_FROM_TD
		);

	/* Set the speed */
	if(readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,port)) & LSDA) {
		set_hc_ed_speed(
				&(ed_info->hc_ed[0].endpoint_ctrl),
				SLOW_SPEED
			);

		set_hc_ed_mps(
				&(ed_info->hc_ed[0].endpoint_ctrl),
				SLOW_SPEED_MAXIMUM_PACKET_SIZE
			);
	} else {
		set_hc_ed_speed(
				&(ed_info->hc_ed[0].endpoint_ctrl),
				FULL_SPEED
			);

		set_hc_ed_mps(
				&(ed_info->hc_ed[0].endpoint_ctrl),
				FULL_SPEED_MAXIMUM_PACKET_SIZE
			);
	}

	ed_info->hc_ed[0].HeadP = 0; //Init to 0.
	ed_info->hc_ed[0].NextED = 0; //Zero since this is the only descriptor.
}

static void
	set_usb_desc_req_buffer(
		uint8_t *usb_req_header,
		enum Request request,
		uint8_t requestType,
		uint16_t wValue,
		uint16_t wIndex,
		uint16_t wLength
	)
{

	writereg8(
			(usb_req_header + USB_REQ_TYPE_OFFSET),
			requestType);
	writereg8(
			(usb_req_header + USB_REQ_OFFSET),
			request);
	writereg16(
			(usb_req_header + USB_VALUE_OFFSET),
			wValue);
	writereg16(
			(usb_req_header + USB_INDEX_OFFSET),
			wIndex);
	writereg16(
			(usb_req_header + USB_LENGTH_OFFSET),
			wLength);
}

/*
 * Idea of the below function is take in different types of descriptors.
 * Based on the descriptors the TD chain will be setup for a request.
 * This is only for setup and enumeration of the USB and NOT for data
 * transfer.
 *
 */
static
	void
	set_setup_descriptor(
				struct td_info *td_info,
				uint8_t *usb_req_header,
				uint8_t *usb_buff_pool,
				enum Request request,
				uint8_t requestType,
				uint16_t wValue,
				uint16_t wIndex,
				uint16_t wLength
		)
{
	uint32_t i = 0, idx = 0;
	uint8_t max_packets = 0;
	uint8_t data_toggle = 0;


	set_usb_desc_req_buffer(
					usb_req_header,
					request,
					requestType,
					wValue,
					wIndex,
					wLength);

/* 	writereg8(
			(usb_req_header + USB_REQ_OFFSET),
			request);
	writereg16(
			(usb_req_header + USB_VALUE_OFFSET),
			wValue);
	writereg16(
			(usb_req_header + USB_INDEX_OFFSET),
			wIndex);
	writereg16(
			(usb_req_header + USB_LENGTH_OFFSET),
			wLength);*/


/**** SETUP Request TD ****/
	writereg32(
			&(td_info->hc_gen_td[0].td_control),
			DP_SETUP
			|NO_DELAY_INTERRUPT
			|DATA_TOGGLE(2)/*
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

	writereg32(
			&(td_info->hc_gen_td[0].current_buffer_pointer),
			(uintptr_t)usb_req_header
			);

	writereg32(
			&(td_info->hc_gen_td[0].buffer_end),
			(uintptr_t) (usb_req_header + MPS_8 - 1)
			);

	writereg32(&(td_info->hc_gen_td[0].next_td),
			(uintptr_t)(&(td_info->hc_gen_td[0+1])));

	/* Write RequestType */
	switch(request) {
		case REQ_SET_ADDRESS:

			writereg8(
				(usb_req_header + USB_REQ_TYPE_OFFSET),
				REQ_TYPE_SET_ADDRESS);

			/*
			 * Initialize 2 td's, the first td to send the request,
			 * the second td being the 'terminator' td with
			 * all 0's
			 */
			/*
			 * Disabled Buffer rounding as the MPS is initially
			 * set to 8 bytes. This is a safe value as we would
			 * not have queried the supported MPS.
			 */
			writereg32(
					&(td_info->hc_gen_td[0].td_control),
					DP_SETUP
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

			writereg32(
					&(td_info->hc_gen_td[1].td_control),
					DP_IN
					/*|NO_DELAY_INTERRUPT*/ /* No Delay interrupt for status TD */
					|DATA_TOGGLE(3) /*
									 * Status packet should have MSB of dataToggle = 1 and
					                 * LSB of dataToggle = 1. See pg24(39) of the spec
									 */
					|CC(NotAccessed)
					);

			/*
			 * Set the current buffer pointer for td0 to get device
			 * descriptor
			 */
			writereg32(
						&(td_info->hc_gen_td[0].current_buffer_pointer),
						(uintptr_t)usb_buff_pool
					);

			/* buffer_end is the last byte to send. Hence subtract by 1 */
			writereg32(
						&(td_info->hc_gen_td[0].buffer_end),
						(uintptr_t)(usb_buff_pool + MPS_8 - 1)
					);

			/* Set the td0 next_td to td1 */
			writereg32(&(td_info->hc_gen_td[0].next_td),
						(uintptr_t)(&(td_info->hc_gen_td[1])));

			break;
		case REQ_GET_DESCRIPTOR:

			max_packets = get_max_packets(wLength,MPS_8) + 1;

/*			writereg8(
				(usb_req_header + USB_REQ_TYPE_OFFSET),
				REQ_TYPE_GET_DESCRIPTOR
				);*/


			/**** Data TD's ****/

			/*
			 * Note: The DP_IN and DP_OUT settings are according to the USB1.1 spec
			 * Pg 165 (181) Figure 8-12.
			 *
			 * Since we do a "control read" the status stage should have DP_OUT.
			 * If we do a control write the status stage should have  DP_IN.
			 * Failure to do this will cause a STALL error.
			 */

			data_toggle = 3;

			for(i = 1; i<max_packets; i++) {
				writereg32(
						&(td_info->hc_gen_td[i].td_control),
						DP_IN
						|DATA_TOGGLE(data_toggle)
						|CC(NotAccessed)
					);
				data_toggle = TOGGLE_DATA(data_toggle);
			}

			/*
			 * If the final data packet is not modulo 0 of the MPS then buffer is not
			 * rounded. Set the BUFFER_ROUND option.
			 */
			if(mod_power_of_two(wLength,MPS_8) && (i > 1)) {
				set_reg_bits(
							&(td_info->hc_gen_td[i-1].td_control),
							BUFFER_ROUND);
			}

/**************** Set Status packet **********************/

			writereg32(
					&(td_info->hc_gen_td[i].td_control),
					DP_OUT
					|DATA_TOGGLE(3)
					|CC(NotAccessed)
			);

/*****************************************************/

			/* Setup the buffer pointers and chain the TDs */
			for(i = 1; i<max_packets; i++) {

				writereg32(
							&(td_info->hc_gen_td[i].current_buffer_pointer),
							(uintptr_t)usb_buff_pool + idx
						);

				/* buffer_end is the last byte to send. Hence subtract by 1 */
				writereg32(
							&(td_info->hc_gen_td[i].buffer_end),
							(uintptr_t)(usb_buff_pool + idx + MPS_8 - 1)
						);

				writereg32(&(td_info->hc_gen_td[i].next_td),
						(uintptr_t)(&(td_info->hc_gen_td[i+1])));

				idx = idx + MPS_8;
			}

			break;
		default:
			break;
	}

}

static int16_t
		get_dev_descriptor(
				struct ed_info *ed_info,
				struct td_info *td_info,
				void *usb_buff_pool,
				enum Ports port
				)
{
	int16_t ed_idx = 0;

	if((ed_idx = get_free_ed_index(ed_info)) == -1) {
		return -1;
	}

	set_ed_descriptor(ed_info,0U,0U,ed_idx,port);

	//Setup the td for the ed. I will setup a single td at index 0.

	/*set_setup_descriptor(
						td_info,
						usb_buff_pool,
						REQ_SET_ADDRESS,
						USB_PORT1_ADDRESS,
						0U,
						0U
						);*/

	set_setup_descriptor(
			td_info,
			usb_req_header,
			usb_buff_pool,
			REQ_GET_DESCRIPTOR,
			REQ_TYPE_GET_DESCRIPTOR,
			frmt_get_desc_wvalue(DESC_DEVICE,0),
			0U,
			sizeof(struct desc_dev)
		);

	/* Setup the head and tail pointers of ED to point to the TD's. */
	writereg32(&(ed_info->hc_ed[0].HeadP),
						(uintptr_t)(&(td_info->hc_gen_td[0])));

	/* Set the TailP to 0. When HeadP == TailP the OHCI stops processing */
	writereg32(&(ed_info->hc_ed[0].TailP),0);
	
	//Dump the endpoint_ctrl for verification.
	dump_ed_desc(&(ed_info->hc_ed[0]));

	//Dump the tds.
	dump_td(&(td_info->hc_gen_td[0]));
	dump_td(&(td_info->hc_gen_td[1]));
	dump_td(&(td_info->hc_gen_td[2]));
	dump_td(&(td_info->hc_gen_td[3]));
	dump_td(&(td_info->hc_gen_td[4]));

	return 0;
}


/*
 * Setting up USB for getting initial config data.
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

	/*
	 * Note: HC_COMMAND_STATUS register is a write to set register by the HCD.
	 * It is cleared by the HC register. Any 0 written to the register by the HCD
	 * does not get affected. --> Need to be verified.
	 */

	writereg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA),HCR);

	/* Host controller sets itself to 0 after 10ms */
	while(readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA)) & HCR)
		;

	/*usb_short_delay();*/
	/*dump_usb_port_status();*/

	/* Clear the interrupt status register */
	writereg32(
			HC_INTERRUPT_STATUS_REG(USB_OHCI_BA),
			OC|RHSC|FNO|UE|RD|SF|WDH|SO
			);

/*********** Repeat reset starts ***********/

	/* Reset the Host controller */
	/*writereg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA),HCR);*/

	/* Host controller sets itself to 0 after 10ms */
	/*while(readreg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA)) & HCR)
		;*/

/*********** Repeat reset ends ***********/

	/*
	 * Host controller will be in suspend state. See Pg 116(131)
	 */
	//dump_control_command_status();
	//dump_interrupt_register_status();

}

/*
static void toggle_usb_global_power()
{

	hc_rh_a_clear_nps(USB_OHCI_BA);

	hc_rh_clear_global_power(USB_OHCI_BA); //Power OFF all the ports.
	usb_short_delay();
	hc_rh_set_global_power(USB_OHCI_BA); //Power ON all the ports.
	usb_short_delay();

	dump_usb_port_status();
}
*/

static void reset_usb_port(enum Ports port)
{


/*	hc_rh_port_set_power(USB_OHCI_BA,port);
	usb_short_delay();*/

/*	if((readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,port))) & CSC) {
		hc_rh_clear_connect_status_change(USB_OHCI_BA,port);
	}*/

	/* Reset port */
	hc_rh_set_port_reset(USB_OHCI_BA,port);

	/* port enable bit will be set once the port is reset */

	/* Wait until the port reset status change bit is set to 1 */
	while(!(readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,port)) & PRSC)) {
		;
	}

	/* Clear the PRSC bit */
	hc_rh_set_port_reset_status_change(USB_OHCI_BA, port);

	/* Wait until the port reset signal bit state is set to 0 */
	while(readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,port)) & PRS) {
		;
	}

	/*
	 * Clear connect status change to clear the notification of the status change
	 */
	if(readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,port)) & CSC) {
		hc_rh_clear_connect_status_change(USB_OHCI_BA,port);
	}

	/*
	 * If there is a device attached the port only then enable the port.
	 * The port anyway cannot be set if the CCS (CurrentConnectStatus) bit is
	 * cleared.
	 */
	if(readreg32(HC_RH_PORT_STATUS_REG(USB_OHCI_BA,port)) & CCS) {
		hc_rh_set_port_enable(USB_OHCI_BA, port);
	}

	/*usb_short_delay();*/

	dump_usb_port_status();
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
     * Write default value to lsthreshold.
     * See section 7.3.5 of spec
     */
	writereg32(HC_LS_THRESHOLD_REG(USB_OHCI_BA),
					0x628U);

	/* Setup device descriptor buffer pool */
	get_dev_descriptor(&ed_info,&td_info,usb_buffer_pool,PORT1);
	
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
	writereg32(HC_INTERRUPT_ENABLE_REG(USB_OHCI_BA),
					SO|WDH|SF|RD|UE|FNO|RHSC|OC|MIE);

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

	/*uart_puts(UART0_BA,"HcFmInterval : ");
	print_hex_uart(UART0_BA,HcFmInterval);*/
}

void init_ohci()
{

	init_usb();

	init_ed(&ed_info,ed_list);
	init_td(&td_info,td_list);

	uart_puts(UART0_BA,"HcRevision :");
	print_hex_uart(UART0_BA,
				readreg32(HC_REVISION_REG(USB_OHCI_BA))
				);


	/* Save the HcFmInterval register for later set up. */
	HcFmInterval = readreg32(HC_FM_INTERVAL_REG(USB_OHCI_BA));


	/* Reset the OHCI controller */
	reset_ohci_controller();

	/* Reset USB port */
	reset_usb_port(PORT1);

	//usb_delay();

	setup_ohci();

	/* Set to USB_OPERATIONAL to start sending SOF. */
	set_regs_value(HC_CONTROL_REG(USB_OHCI_BA),
					HCFS_MASK,
					HCFS_USB_OPERATIONAL<<HCFS_SHIFT
					);

	dump_usb_controller_functional_state();

	/* Verify is SF generation has started */
	while(!(readreg32(HC_INTERRUPT_STATUS_REG(USB_OHCI_BA)) & SF)) {
		;
	}

	/* Set the control list filled. */
	writereg32(HC_COMMAND_STATUS_REG(USB_OHCI_BA),CLF);

	/* Poll for data */
	while(!(readreg32(HC_INTERRUPT_STATUS_REG(USB_OHCI_BA)) & WDH)) {
		;
	}

	/* usb_delay(); */

	uart_puts(UART0_BA,"HccaDoneHead: ");
	print_hex_uart(UART0_BA,
					(hccaregion_reg->HccaDoneHead));

	dump_td((struct GEN_TRANSFER_DESCRIPTOR *)
				((hccaregion_reg->HccaDoneHead & 0xFFFFFFF0)));

	memcpy(desc_dev_buff, usb_buffer_pool, sizeof(struct desc_dev));

	dump_dev_desc((struct desc_dev *)desc_dev_buff);

	/*dump_buff(desc_dev_buff,18);
	dump_buff(usb_buffer_pool+MPS_8, 18);*/

//	dump_ed_desc(&ed_info.hc_ed[0]);

/*	dump_rh_desc_ab();
	dump_currentED_reg();
	dump_interrupt_register_status();
	dump_usb_port_status();
	dump_usb_controller_functional_state(); 
	dump_rh_status();*/
}
