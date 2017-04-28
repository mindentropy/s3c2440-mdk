#ifndef USB_OHCI_H_

#define USB_OHCI_H_

#include "common.h"

#define MAX_ED_DESCRIPTORS 	(10)
#define ED_SIZE 			(16)
#define ED_SIZE_SHIFT 		(4)
#define ED_TOTAL_SIZE  		(MAX_ED_DESCRIPTORS << ED_SIZE_SHIFT)

#define MAX_TD_DESCRIPTORS 	(10)
#define TD_SIZE 			(16)
#define TD_SIZE_SHIFT 		(4)
#define TD_TOTAL_SIZE 		(MAX_TD_DESCRIPTORS << TD_SIZE_SHIFT)

#define MAX_ISO_TD_DESCRIPTORS 	(10)
#define ISO_TD_SIZE 			(32)
#define ISO_TD_SIZE_SHIFT 		(5)
#define ISO_TD_TOTAL_SIZE  		(MAX_ISO_TD_DESCRIPTORS << ISO_TD_SIZE_SHIFT)

#define USB_OHCI_BA 			(0x49000000U)

#define HC_REVISION_OFF 				0x00
#define HC_REVISION_REG(BA) \
	HW_REG(BA,HC_REVISION_OFF)

#define REV_MASK 	set_bit_range(7,0)

#define HC_CONTROL_OFF 					0x04U
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
#define HCFS_USB_RESUME 		BIT0
#define HCFS_USB_OPERATIONAL 	BIT1
#define HCFS_USB_SUSPEND 		BIT1|BIT0

#define HCFS_MASK 				(BIT7|BIT6)
#define HCFS_SHIFT 				6

#define IR 						BIT8
#define RWC 					BIT9
#define RWE 					BIT10


#define HC_COMMAND_STATUS_OFF 			0x08U
#define HC_COMMAND_STATUS_REG(BA) \
	HW_REG(BA,HC_COMMAND_STATUS_OFF)

#define HCR BIT0
#define CLF BIT1
#define BLF BIT2
#define OCR BIT3

#define SOC (BIT17|BIT16)

#define HC_INTERRUPT_STATUS_OFF 		0x0CU
#define HC_INTERRUPT_STATUS_REG(BA) \
	HW_REG(BA,HC_INTERRUPT_STATUS_OFF)

#define HC_INTERRUPT_ENABLE_OFF 		0x10U
#define HC_INTERRUPT_ENABLE_REG(BA) \
	HW_REG(BA,HC_INTERRUPT_ENABLE_OFF)


#define HC_INTERRUPT_DISABLE_OFF 		0x14U
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

#define HC_HCCA_OFF 					0x18U
#define HC_HCCA_REG(BA) \
	HW_REG(BA,HC_HCCA_OFF)

struct __attribute__((packed)) HCCARegion {
	uint32_t HccaInterruptTable[32];
	uint16_t HccaFrameNumber;
	uint16_t HccaPad1;
	uint32_t HccaDoneHead;
	uint8_t  HccaReserved[116];
};

#define HC_PERIOD_CURRENT_ED_OFF 		0x1CU
#define HC_PERIOD_CURRENT_ED_REG(BA) \
	HW_REG(BA,HC_PERIOD_CURRENT_ED_OFF)

#define PCED_MASK 	set_bit_range(31,4)

#define HC_CONTROL_HEAD_ED_OFF 			0x20U
#define HC_CONTROL_HEAD_ED_REG(BA) \
	HW_REG(BA,HC_CONTROL_HEAD_ED_OFF)

#define CHED_MASK 	set_bit_range(31,4)

#define HC_CONTROL_CURRENT_ED_OFF 		0x24U
#define HC_CONTROL_CURRENT_ED_REG(BA) \
	HW_REG(BA,HC_CONTROL_CURRENT_ED_OFF)

#define CCED_MASK 	set_bit_range(31,4)

#define HC_BULK_HEAD_ED_OFF 			0x28U
#define HC_BULK_HEAD_ED_REG(BA) \
	HW_REG(BA,HC_BULK_HEAD_ED_OFF)

#define BHED_MASK 	set_bit_range(31,4)

#define HC_BULK_CURRENT_ED_OFF 			0x2C
#define HC_BULK_CURRENT_ED_REG(BA) \
	HW_REG(BA,HC_BULK_CURRENT_ED_OFF)

#define BCED_MASK 	set_bit_range(31,4)

#define HC_DONE_HEAD_OFF 				0x30U
#define HC_DONE_HEAD_REG(BA) \
	HW_REG(BA,HC_DONE_HEAD_OFF)

#define DH_MASK 	set_bit_range(31,4)

#define HC_FM_INTERVAL_OFF 				0x34U
#define HC_FM_INTERVAL_REG(BA) \
	HW_REG(BA,HC_FM_INTERVAL_OFF)

#define FI_MASK 	set_bit_range(13,0)
#define FSMPS_MASK 	set_bit_range(30,16)
#define FIT_MASK 	BIT31

#define HC_FM_REMAINING_OFF 			0x38U
#define HC_FM_REMAINING_REG(BA) \
	HW_REG(BA,HC_FM_REMAINING_OFF)

#define FR_MASK 	set_bit_range(13,0)
#define FRT_MASK 	BIT31

#define HC_FM_NUMBER_OFF 				0x3CU
#define HC_FM_NUMBER_REG(BA) \
	HW_REG(BA,HC_FM_NUMBER_OFF)

#define FN_MASK 	set_bit_range(15,0)

#define HC_PERIODIC_START_OFF 			0x40U
#define HC_PERIODIC_START_REG(BA) \
	HW_REG(BA,HC_PERIODIC_START_OFF)

#define PS_MASK 	set_bit_range(13,0)

#define HC_LS_THRESHOLD_OFF 			0x44U
#define HC_LS_THRESHOLD_REG(BA) \
	HW_REG(BA,HC_LS_THRESHOLD_OFF)

#define LST_MASK 	set_bit_range(11,0)

#define HC_RH_DESCRIPTOR_A_OFF 			0x48U
#define HC_RH_DESCRIPTOR_A_REG(BA) \
	HW_REG(BA,HC_RH_DESCRIPTOR_A_OFF)

#define NDP_MASK 	0xFFU
#define PSM 		BIT8
#define NPS 		BIT9
#define DT 			BIT10
#define OCPM 		BIT11
#define NOCP 		BIT12
#define POTPGT 		0xFF000000U

#define hc_rh_a_clear_nps(BA) \
	clear_reg_bits(HC_RH_DESCRIPTOR_A_REG(BA),NPS);

#define hc_rh_a_set_nps(BA) \
	set_reg_bits(HC_RH_DESCRIPTOR_A_REG(BA),NPS);

#define HC_RH_DESCRIPTOR_B_OFF 			0x4CU
#define HC_RH_DESCRIPTOR_B_REG(BA) \
	HW_REG(BA,HC_RH_DESCRIPTOR_B_OFF)

#define DR_MASK 	(0xFFU)
#define PPCM_MASK 	(0xFF000000U)

#define HC_RH_STATUS_OFF 				0x50U
#define HC_RH_STATUS_REG(BA) \
	HW_REG(BA,HC_RH_STATUS_OFF)

#define LPS 			BIT0
#define OCI 			BIT1
#define DRWE 			BIT15
#define LPSC 			BIT16
#define OCIC_RH 		BIT17
#define CRWE 			BIT31

#define hc_rh_clear_global_power(BA) 	\
	writereg32(HC_RH_STATUS_REG(BA),LPS)

#define hc_rh_set_global_power(BA)	\
	writereg32(HC_RH_STATUS_REG(BA),LPSC)

enum Ports {
	PORT1 = 0,
	PORT2,
	PORT3,
	PORT4,
	PORT5,
	PORT6,
	PORT7,
	PORT8,
	PORT9,
	PORT10,
	PORT11,
	PORT12,
	PORT13,
	PORT14,
	PORT15,
};

#define HC_RH_PORT_STATUS_OFF 			0x54U
#define HC_RH_PORT_STATUS_REG(BA,PORTNUM) \
	(HW_REG(BA,(HC_RH_PORT_STATUS_OFF + ((PORTNUM)<<2))))

#define HC_RH_PORT1_STATUS_OFF 			0x54
#define HC_RH_PORT1_STATUS_REG(BA) \
	(HW_REG(BA,HC_RH_PORT1_STATUS_OFF))


#define HC_RH_PORT2_STATUS_OFF 			0x58
#define HC_RH_PORT2_STATUS_REG(BA) \
	(HW_REG(BA,HC_RH_PORT2_STATUS_OFF))

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

#define hc_rh_set_port_enable(BA,PORTNUM) \
	writereg32((HC_RH_PORT_STATUS_REG(BA,PORTNUM)), \
				PES)

#define hc_rh_set_port_suspend(BA,PORTNUM) \
	writereg32(HC_RH_PORT_STATUS_REG(BA,PORTNUM), \
				PSS)

#define hc_rh_clear_port_suspend(BA,PORTNUM) \
	writereg32(HC_RH_PORT_STATUS_REG(BA,PORTNUM), \
				PSSC)
					
#define hc_rh_set_port_reset(BA,PORTNUM) \
	writereg32((HC_RH_PORT_STATUS_REG(BA,PORTNUM)), \
				PRS)

#define hc_rh_port_clear_power(BA,PORTNUM) \
	writereg32(HC_RH_PORT_STATUS_REG(BA,PORTNUM),\
				LSDA);

#define hc_rh_port_set_power(BA,PORTNUM) \
	writereg32(HC_RH_PORT_STATUS_REG(BA,PORTNUM),\
				PPS);

#define hc_rh_set_port_reset_status_change(BA,PORTNUM)	\
	writereg32((HC_RH_PORT_STATUS_REG(BA,PORTNUM)), \
				PRSC)

#define hc_rh_clear_connect_status_change(BA,PORTNUM)	\
	writereg32((HC_RH_PORT_STATUS_REG(BA,PORTNUM)),	\
				CSC)

/**** OHCI functionality ****/

#define HC_ED_ALIGNMENT 	16

struct  __attribute__((packed)) HC_ENDPOINT_DESCRIPTOR
{
	uint32_t endpoint_ctrl;
	uint32_t TailP;
	uint32_t HeadP;
	uint32_t NextED;
};

struct ed_info {
	struct HC_ENDPOINT_DESCRIPTOR *hc_ed;
	uint32_t size;
};

#define FA_SHIFT  		0
#define FA_MASK 		0x3F

#define set_hc_ed_FA(reg,value) \
	set_regs_value(reg,FA_MASK,(value<<FA_SHIFT))

#define EN_MASK 		0xF
#define EN_SHIFT  		7

#define set_hc_ed_EN(reg,value) \
	set_regs_value(reg,EN_MASK,(value<<EN_SHIFT))

#define DIR_MASK  		(BIT12|BIT11)
#define DIR_SHIFT 		11

#define GET_DIR_FROM_TD 	(0<<DIR_SHIFT)
#define OUT 				(1<<DIR_SHIFT)
#define IN 					(2<<DIR_SHIFT)
#define GET_DIR_FROM_TD1 	(3<<DIR_SHIFT)

#define set_hc_ed_D(reg,value) \
	set_regs_value(reg,DIR_MASK,(value))

#define SPEED_MASK  	BIT13
#define SPEED_SHIFT 	(13U)

#define SLOW_SPEED 		(1<<SPEED_SHIFT)
#define FULL_SPEED 		(0<<SPEED_SHIFT)

#define set_hc_ed_speed(reg,value) \
	set_regs_value(reg,SPEED_MASK,value)

#define SKIP_MASK 		BIT14
#define SKIP_SHIFT 		14

#define set_hc_ed_skip(reg,value) \
	set_regs_value(reg,SKIP_MASK,(value<<SKIP_SHIFT))

#define FORMAT_MASK 	BIT15
#define FORMAT_SHIFT 	15

#define set_hc_ed_format(reg,value) \
	set_regs_value(reg,FORMAT_MASK,(value<<FORMAT_SHIFT))

#define MPS_MASK  		(0x7FF0000U)
#define MPS_SHIFT 		(16U)

#define set_hc_ed_mps(reg,value) \
	set_regs_value(reg,MPS_MASK,((value)<<(MPS_SHIFT)))

#define TAILP_MASK  	(0xFFFFFFFU)
#define TAILP_SHIFT 	(4U)

#define set_hc_ed_tailp(reg,value) \
	set_regs_value(reg,TAILP_MASK,(value<<TAILP_SHIFT))

#define HEADP_MASK  	(0xFFFFFFFU)
#define HEADP_SHIFT 	(4U)

#define set_hc_ed_headp(reg,value) \
	set_regs_value(reg,HEADP_MASK,(value<<HEADP_SHIFT))

#define HALT_ED_MASK 	BIT0
#define HALT_ED_SHIFT 	0

#define set_hc_ed_halted(reg,value) \
	set_regs_value(reg,HALT_ED_MASK,(value<<HALT_ED_SHIFT))

#define TOGGLE_CARRY_MASK 	BIT1
#define TOGGLE_SHIFT 		1U
#define TOGGLE 				1U

#define set_hc_ed_toggle_carry(reg,value) \
	set_regs_value(reg,TOGGLE_CARRY_MASK,(value<<TOGGLE_SHIFT))

#define NEXT_ED_MASK 	(0xFFFFFFFU)
#define NEXT_ED_SHIFT 	(4)

#define set_hc_ed_next_ed(reg,value) \
	set_regs_value(reg,NEXT_ED_MASK,(value<<NEXT_ED_SHIFT))

#define HC_GEN_TD_ALIGNMENT 	16


struct __attribute__((packed)) GEN_TRANSFER_DESCRIPTOR
{
	uint32_t td_control;
	uint32_t current_buffer_pointer;
	uint32_t next_td;
	uint32_t buffer_end;
};

struct td_info {
	struct GEN_TRANSFER_DESCRIPTOR *hc_gen_td;
	uint32_t size;
};

#define BUFFER_ROUNDING_MASK 	BIT18
#define BUFFER_ROUND 			BIT18
#define BUFFER_ROUNDING_SHIFT 	18 

#define DP_SETUP_SHIFT 			19

#define DP_SETUP 				(0)
#define DP_OUT 					(BIT19)
#define DP_IN 					(BIT20)
#define DP_RESERVED 			(BIT20|BIT19)

#define DP_MASK  				(BIT20|BIT19)

#define DELAY_INTERRUPT_MASK 	(BIT23|BIT22|BIT21)
#define DELAY_INTERRUPT_SHIFT 	(21U)

#define NO_DELAY_INTERRUPT 		(BIT23|BIT22|BIT21)

#define DATA_TOGGLE_MASK		(BIT25|BIT24)
#define DATA_TOGGLE_SHIFT 		(24U)
#define DATA_TOGGLE(TOGGLE_VAL) \
	((TOGGLE_VAL) << (DATA_TOGGLE_SHIFT))


#define ERROR_COUNT_MASK		(BIT27|BIT26)
#define ERROR_COUNT_SHIFT 		(26U)

#define CC_SHIFT 				(28U)
#define CC(CC_CODE) \
	((CC_CODE)<<(CC_SHIFT))

enum CONDITION_CODE
{
	NoError,
	CRC,
	BitStuffing,
	DataToggleMismatch,
	Stall,
	DeviceNotResponding,
	PIDCheckFailure,
	UnexpectedPID,
	DataOverrun,
	DataUnderrun,
	reserved1,
	reserved2,
	BufferOverrun,
	BufferUnderrun,
	NotAccessed
};


#define NEXT_TD_MASK 			set_bit_range(31,4)

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


//#define SF_MASK  		(set_bit_range(15,0))
//#define DI_MASK 		(set_bit_range(23,21))
//#define FC_MASK 		(set_bit_range(26,24))
//#define CC_MASK 		(set_bit_range(31,28))
#define CC_MASK 		((0xFU) << (CC_SHIFT))
#define CC_MASK 		((0xFU) << (CC_SHIFT))

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

/* Value as per the spec. See Section 5.4 */
#define MAXIMUM_OVERHEAD 	210

#define USB_PORT1_ADDRESS	0x1U
#define USB_PORT2_ADDRESS	0x2U

#define SLOW_SPEED_MAXIMUM_PACKET_SIZE 0x8U
#define FULL_SPEED_MAXIMUM_PACKET_SIZE 0x40U

void init_ohci();


#endif
