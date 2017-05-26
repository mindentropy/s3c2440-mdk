#ifndef USB_DBG_DUMP_H_

#define USB_DBG_DUMP_H_

void dump_td(
			struct GEN_TRANSFER_DESCRIPTOR *hc_gen_td
		);

void dump_ed_desc(
			struct HC_ENDPOINT_DESCRIPTOR *hc_ed
		);
void dump_usb_port_status();
void dump_usb_controller_functional_state();
void dump_dev_desc(struct desc_dev *desc_dev);

#endif
