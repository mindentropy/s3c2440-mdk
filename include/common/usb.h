#ifndef USB_H_

#define USB_H_

#include <stdint.h>

#define REQ_TYPE_CLEAR_FEATURE1  	(0x0U)
#define REQ_TYPE_CLEAR_FEATURE2  	(0x1U)
#define REQ_TYPE_CLEAR_FEATURE3  	(0x2U)

#define REQ_TYPE_GET_CONFIGURATION  (0x80U)
#define REQ_TYPE_GET_DESCRIPTOR 	(0x80U)

#define REQ_TYPE_GET_INTERFACE 		(0x81U)

#define REQ_TYPE_GET_STATUS1 		(0x80U)
#define REQ_TYPE_GET_STATUS2 		(0x81U)
#define REQ_TYPE_GET_STATUS3 		(0x82U)

#define REQ_TYPE_SET_ADDRESS 		(0x0U)
#define REQ_TYPE_SET_CONFIGURATION  (0x0U)

#define REQ_TYPE_SET_DESCRIPTOR 	(0x0U)

#define REQ_TYPE_SET_FEATURE1 		(0x0U)
#define REQ_TYPE_SET_FEATURE2 		(0x1U)
#define REQ_TYPE_SET_FEATURE3 		(0x2U)

#define REQ_TYPE_SET_INTERFACE 		(0x1U)
#define REQ_TYPE_SYNCH_FRAME 		(0x82U)

#define USB_REQ_TYPE_SIZE	(1U)
#define USB_REQ_SIZE		(1U)
#define USB_VALUE_SIZE		(2U)
#define USB_INDEX_SIZE		(2U)
#define USB_LENGTH_SIZE		(2U)

#define USB_REQ_TYPE_OFFSET	(0U)
#define USB_REQ_OFFSET		(USB_REQ_TYPE_OFFSET + USB_REQ_TYPE_SIZE)
#define USB_VALUE_OFFSET	(USB_REQ_OFFSET + USB_REQ_SIZE)
#define USB_INDEX_OFFSET	(USB_VALUE_OFFSET + USB_VALUE_SIZE)
#define USB_LENGTH_OFFSET	(USB_INDEX_OFFSET + USB_INDEX_SIZE)

#define USB_DESC_SIZE		(USB_LENGTH_OFFSET + USB_LENGTH_SIZE)

struct __attribute__((packed)) usb_request
{
	uint8_t bmRequestType;
	uint8_t bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
};

enum Request {
	REQ_GET_STATUS = 0,
	REQ_CLEAR_FEATURE,
	REQ_RESERVED1,
	REQ_SET_FEATURE,
	REQ_RESERVED2,
	REQ_SET_ADDRESS,
	REQ_GET_DESCRIPTOR,
	REQ_SET_DESCRIPTOR,
	REQ_GET_CONFIGURATION,
	REQ_SET_CONFIGURATION,
	REQ_GET_INTERFACE,
	REQ_SET_INTERFACE,
	REQ_SYNCH_FRAME
};

enum DescriptorType {
	DESC_DEVICE = 1,
	DESC_CONFIGURATION,
	DESC_STRING,
	DESC_INTERFACE,
	DESC_ENDPOINT
};

#define FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP 	1
#define FEATURE_SELECTOR_ENDPOINT_HALT 			0

#define frmt_get_desc_wvalue(desc_type,desc_index) \
			((desc_type)<<8) | ((desc_index))

#define set_usb_req_parameters(usb_req_ptr, \
		RequestType, \
		Request, \
		Value, \
		Index, \
		Length) \
	do { \
		usb_req_ptr->bmRequestType = RequestType; 	\
		usb_req_ptr->bRequest = Request; 	\
		usb_req_ptr->wValue = Value; 	\
		usb_req_ptr->wIndex = Index; 	\
		usb_req_ptr->wLength = Length; 	\
	} while(0)


#define usb_get_descriptor(usb_req_ptr, \
				desc_type_idx, \
				wIndex, \
				desc_len) \
	set_usb_req_parameters(usb_req_ptr, \
			REQ_TYPE_GET_DESCRIPTOR, \
			REQ_GET_DESCRIPTOR, \
			desc_type_idx, \
			wIndex, \
			desc_len)


#define usb_clear_feature(usb_req_ptr,feature_selector) \
	set_usb_req_parameters(usb_req_ptr,\
							REQ_TYPE_CLEAR_FEATURE1,\
							REQ_CLEAR_FEATURE,\
							feature_selector,\
							0, \
							0)

#define usb_get_configuration(usb_req_ptr) \
	set_usb_req_parameters(usb_req_ptr,\
						REQ_TYPE_GET_CONFIGURATION,\
						REQ_GET_CONFIGURATION,\
						0,\
						0,\
						1)


#define usb_get_interface(usb_req_ptr,interface) \
	set_usb_req_parameters(usb_req_ptr,\
					REQ_TYPE_GET_INTERFACE,\
					REQ_GET_INTERFACE,\
					0,\
					interface,\
					1)

#define usb_get_status(usb_req_ptr) \
	set_usb_req_parameters(usb_req_ptr,\
				REQ_TYPE_GET_STATUS1,\
				REQ_GET_STATUS,\
				0,\
				0,\
				2)

#define usb_set_address(usb_req_ptr,dev_addr) \
	set_usb_req_parameters(usb_req_ptr,\
				REQ_TYPE_SET_ADDRESS,\
				REQ_SET_ADDRESS,\
				dev_addr,\
				0,\
				0)

#define usb_set_configuration(usb_req_ptr,config_value) \
	set_usb_req_parameters(usb_req_ptr,\
				REQ_TYPE_SET_CONFIGURATION,\
				REQ_SET_CONFIGURATION,\
				config_value,\
				0,\
				0)

#define usb_set_descriptor(usb_req_ptr,desc_type_idx,wIndex,desc_len) \
	set_usb_req_parameters(usb_req_ptr,\
				REQ_TYPE_SET_DESCRIPTOR,\
				REQ_SET_DESCRIPTOR,\
				desc_type_idx,\
				wIndex,\
				desc_len)

#define usb_set_feature(usb_req_ptr,feature_selector) \
	set_usb_req_parameters(usb_req_ptr,\
							REQ_TYPE_SET_FEATURE1,\
							REQ_SET_FEATURE,\
							feature_selector,\
							0,\
							0)

#define usb_set_interface(usb_req_ptr,alt_setting,interface) \
	set_usb_req_parameters(usb_req_ptr,\
						REQ_TYPE_SET_INTERFACE,\
						REQ_SET_INTERFACE,\
						alt_setting,\
						interface,\
						0)

#define usb_synch_frame(usb_req_ptr,endpoint) \
	set_usb_req_parameters(usb_req_ptr,\
						REQ_TYPE_SYNCH_FRAME,\
						REQ_SYNCH_FRAME,\
						0,\
						endpoint,\
						2)

void init_usb();

#endif
