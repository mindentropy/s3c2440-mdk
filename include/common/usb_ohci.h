#ifndef USB_OHCI_H_

#define USB_OHCI_H_

#include "common.h"

#define USB_OHCI_BA 			(0x49000000U)

#define HC_REVISION_OFF 				0x00
#define HC_REVISION_REG(BA) \
	HW_REG(BA,HC_REVISION_OFF)

#define REV_MASK 	set_bit_range(7,0)

#define HC_CONTROL_OFF 					0x04
#define HC_CONTROL_REG(BA) \
	HW_REG(BA,HC_CONTROL_OFF)

#define HC_CONTROL_MASK 	set_bit_range(10,0)

#define CBSR_0 	0
#define CBSR_1 	BIT0
#define CBSR_2 	BIT1
#define CBSR_3 	(BIT1|BIT0)

#define PLE 	BIT2
#define IE 	 	BIT3
#define CLE 	BIT4
#define BLE 	BIT5

#define HCFS_USB_RESET 			0
#define HCFS_USB_RESUME 		BIT6
#define HCFS_USB_OPERATIONAL 	BIT7
#define HCFS_USB_SUSPEND 		BIT7|BIT6
#define IR 						BIT8
#define RWC 					BIT9
#define RWE 					BIT10


#define HC_COMMAND_STATUS_OFF 			0x08
#define HC_COMMAND_STATUS_REG(BA) \
	HW_REG(BA,HC_COMMAND_STATUS_OFF)

#define HCR BIT0
#define CLF BIT1
#define BLF BIT2
#define OCR BIT3

#define SOC (BIT17|BIT16)

#define HC_INTERRUPT_STATUS_OFF 		0x0C
#define HC_INTERRUPT_STATUS_REG(BA) \
	HW_REG(BA,HC_INTERRUPT_STATUS_OFF)


#define HC_INTERRUPT_ENABLE_OFF 		0x10
#define HC_INTERRUPT_ENABLE_REG(BA) \
	HW_REG(BA,HC_INTERRUPT_ENABLE_OFF)


#define HC_INTERRUPT_DISABLE_OFF 		0x14
#define HC_INTERRUPT_DISABLE_REG(BA) \
	HW_REG(BA,HC_INTERRUPT_DISABLE_OFF)

#define SO 		BIT0
#define WDH 	BIT1
#define SF  	BIT2
#define RD 		BIT3
#define UE 		BIT4
#define FNO  	BIT5
#define RHSC 	BIT6
#define OC 		BIT30
#define MIE 	BIT31

#define HC_HCCA_OFF 					0x18
#define HC_HCCA_REG(BA) \
	HW_REG(BA,HC_HCCA_OFF)

struct __attribute__((packed)) HCCARegion {
	uint32_t HccaInterruptTable[32];
	uint16_t HccaFrameNumber;
	uint16_t HccaPad1;
	uint32_t HccaDoneHead;
	uint8_t  HccaReserved[116];
};

#define HC_PERIOD_CURRENT_ED_OFF 		0x1C
#define HC_PERIOD_CURRENT_ED_REG(BA) \
	HW_REG(BA,HC_PERIOD_CURRENT_ED_OFF)

#define PCED_MASK 	set_bit_range(31,4)

#define HC_CONTROL_HEAD_ED_OFF 			0x20
#define HC_CONTROL_HEAD_ED_REG(BA) \
	HW_REG(BA,HC_CONTROL_HEAD_ED_OFF)

#define CHED_MASK 	set_bit_range(31,4)

#define HC_CONTROL_CURRENT_ED_OFF 		0x24
#define HC_CONTROL_CURRENT_ED_REG(BA) \
	HW_REG(BA,HC_CONTROL_CURRENT_ED_OFF)

#define CCED_MASK 	set_bit_range(31,4)

#define HC_BULK_HEAD_ED_OFF 			0x28
#define HC_BULK_HEAD_ED_REG(BA) \
	HW_REG(BA,HC_BULK_HEAD_ED_OFF)

#define BHED_MASK 	set_bit_range(31,4)

#define HC_BULK_CURRENT_ED_OFF 			0x2C
#define HC_BULK_CURRENT_ED_REG(BA) \
	HW_REG(BA,HC_BULK_CURRENT_ED_OFF)

#define BCED_MASK 	set_bit_range(31,4)

#define HC_DONE_HEAD_OFF 				0x30
#define HC_DONE_HEAD_REG(BA) \
	HW_REG(BA,HC_DONE_HEAD_OFF)

#define DH_MASK 	set_bit_range(31,4)

#define HC_FM_INTERVAL_OFF 				0x34
#define HC_FM_INTERVAL_REG(BA) \
	HW_REG(BA,HC_FM_INTERVAL_OFF)

#define FI_MASK 	set_bit_range(13,0)
#define FSMPS_MASK 	set_bit_range(30,16)
#define FIT_MASK 	BIT31

#define HC_FM_REMAINING_OFF 			0x38
#define HC_FM_REMAINING_REG(BA) \
	HW_REG(BA,HC_FM_REMAINING_OFF)

#define FR_MASK 	set_bit_range(13,0)
#define FRT_MASK 	BIT31

#define HC_FM_NUMBER_OFF 				0x3C
#define HC_FM_NUMBER_REG(BA) \
	HW_REG(BA,HC_FM_NUMBER_OFF)

#define FN_MASK 	set_bit_range(15,0)

#define HC_PERIODIC_START_OFF 			0x40
#define HC_PERIODIC_START_REG(BA) \
	HW_REG(BA,HC_PERIODIC_START_OFF)

#define PS_MASK 	set_bit_range(13,0)

#define HC_LS_THRESHOLD_OFF 			0x44
#define HC_LS_THRESHOLD_REG(BA) \
	HW_REG(BA,HC_LS_THRESHOLD_OFF)

#define LST_MASK 	set_bit_range(11,0)

#define HC_RH_DESCRIPTOR_A_OFF 			0x48
#define HC_RH_DESCRIPTOR_A_REG(BA) \
	HW_REG(BA,HC_RH_DESCRIPTOR_A_OFF)

#define NDP_MASK 	set_bit_range(7,0)
#define PSM 		BIT8
#define NPS 		BIT9
#define DT 			BIT10
#define OCPM 		BIT11
#define NOCP 		BIT12
#define POTPGT 		set_bit_range(31,24)

#define HC_RH_DESCRIPTOR_B_OFF 			0x4C
#define HC_RH_DESCRIPTOR_B_REG(BA) \
	HW_REG(BA,HC_RH_DESCRIPTOR_B_OFF)

#define DR_MASK 	set_bit_range(15,0)
#define PPCM_MASK 	set_bit_range(31,16)

#define HC_RH_STATUS_OFF 				0x50
#define HC_RH_STATUS_REG(BA) \
	HW_REG(BA,HC_RH_STATUS_OFF)

#define LPS 			BIT0
#define OCI 			BIT1
#define DRWE 			BIT15
#define LPSC 			BIT16
#define OCIC_RH 		BIT17
#define CRWE 			BIT31

#define HC_RH_PORT_STATUS1_OFF 			0x54
#define HC_RH_PORT_STATUS1_REG(BA) \
	HW_REG(BA,HC_RH_PORT_STATUS1_OFF)


#define HC_RH_PORT_STATUS2_OFF 			0x58
#define HC_RH_PORT_STATUS2_REG(BA) \
	HW_REG(BA,HC_RH_PORT_STATUS2_OFF)

#define CCS 	BIT0
#define PES 	BIT1
#define PSS 	BIT2
#define POCI 	BIT3
#define PRS 	BIT4
#define PPS 	BIT8
#define LSDA 	BIT9
#define CSC 	BIT16
#define PESC 	BIT17
#define PSSC 	BIT18
#define OCIC 	BIT19
#define PRSC 	BIT20

/**** OHCI functionality ****/

struct  __attribute__((packed)) HC_ENDPOINT_DESCRIPTOR
{
	uint32_t endpoint_ctrl;
	uint32_t TailP;
	uint32_t HeadP;
	uint32_t NextED;
};

#define FA_MASK 		set_bit_range(6,0)
#define EN_MASK 		set_bit_range(10,7)
#define DIR_MASK  		BIT12|BIT11
#define SPEED_MASK  	BIT13
#define SKIP_MASK 		BIT14
#define FORMAT_MASK 	BIT15
#define MPS_MASK  		set_bit_range(26,16)

#define TailP_MASK  	set_bit_range(31,4)
#define HeadP_MASK  	set_bit_range(31,4)
#define Halted 			BIT1
#define TOGGLE_CARRY 	BIT0
#define NextED_MASK 	set_bit_range(31,4)

struct __attribute__((packed)) GENERAL_TRANSFER_DESCRIPTOR
{
	uint32_t td_control;
	uint32_t current_buffer_pointer;
	uint32_t next_td;
	uint32_t buffer_end;
};

#define BUFFER_ROUNDING 	BIT18
#define DP_SETUP 			(0)
#define DP_OUT 				(BIT19)
#define DP_IN 				(BIT20)
#define DP_RESERVED 		(BIT20|BIT19)
#define DP_MASK  			(BIT20|BIT19)
#define DELAY_INTERRUPT 	(BIT23|BIT22|BIT21)
#define DATA_TOGGLE 		(BIT25|BIT24)
#define ERROR_COUNT 		(BIT27|BIT26)
#define CONDITION_CODE 		set_bit_range(31,28)
#define NEXT_TD_MASK 		set_bit_range(31,4)


struct __attribute__((packed)) ISOCHRONOUS_TRANSFER_DESCRIPTOR
{
	uint32_t dword0;
	uint32_t dword1;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
	uint32_t dword7;
};


#define SF_MASK  		set_bit_range(15,0)
#define DI_MASK 		set_bit_range(23,21)
#define FC_MASK 		set_bit_range(26,24)
#define CC_MASK 		set_bit_range(31,28)

#define BP0_MASK 		set_bit_range(31,12)
#define ISO_NEXT_TD_MASK 	set_bit_range(31,5)

#define OFF0_PSW0_MASK 	set_bit_range(15,0)
#define OFF1_PSW1_MASK 	set_bit_range(31,16)
#define OFF2_PSW2_MASK 	set_bit_range(15,0)
#define OFF3_PSW3_MASK 	set_bit_range(31,16)
#define OFF4_PSW4_MASK 	set_bit_range(15,0)
#define OFF5_PSW5_MASK 	set_bit_range(31,16)
#define OFF6_PSW6_MASK 	set_bit_range(15,0)
#define OFF7_PSW7_MASK 	set_bit_range(31,16)

struct __attribute__((packed)) PACKET_STATUS_WORD
{
	uint16_t PSW;
};



#define PSW_SIZE_MASK 	set_bit_range(10,0)
#define PSW_CC 			set_bit_range(15,12)

void init_ohci();

#endif
