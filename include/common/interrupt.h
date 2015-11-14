#ifndef INTERRUPT_H_

#define INTERRUPT_H_

#include "common.h"

#define INT_BA 					0x4A000000U

#define SRCPND_OFF 				0x00U
#define INTMOD_OFF  			0x04U
#define INTMSK_OFF  			0x08U
#define INTPRIORITY_OFF 		0x0CU
#define INTPND_OFF 				0x10U
#define INTOFFSET_OFF   		0x14U
#define SUBSRCPND_OFF 			0x18U
#define INTSUBMSK_OFF 			0x1CU

#define SRCPND_REG(BA) \
		HW_REG((BA),SRCPND_OFF)

#define INTMOD_REG(BA) \
		HW_REG((BA),INTMOD_OFF)

#define INTMSK_REG(BA) \
		HW_REG((BA),INTMSK_OFF)

#define INTPRIORITY_REG(BA) \
		HW_REG((BA),INTPRIORITY_OFF)

#define INTPND_REG(BA) \
		HW_REG((BA),INTPND_OFF)

#define INTOFFSET_REG(BA) \
		HW_REG((BA),INTOFFSET_OFF)

#define SUBSRCPND_REG(BA) \
		HW_REG((BA),SUBSRCPND_OFF)

#define INTSUBMSK_REG(BA) \
		HW_REG((BA),INTSUBMSK_OFF)


#define EINT0 			BIT0
#define EINT1   		BIT1
#define EINT2 			BIT2
#define EINT3 			BIT3
#define EINT4_7 		BIT4
#define EINT8_23 		BIT5
#define INT_CAM 		BIT6
#define nBATT_FLT   	BIT7
#define INT_TICK 		BIT8
#define INT_WDT_AC97 	BIT9
#define INT_TIMER0 		BIT10
#define INT_TIMER1 		BIT11
#define INT_TIMER2 		BIT12
#define INT_TIMER3 		BIT13
#define INT_TIMER4 		BIT14
#define INT_UART2 		BIT15
#define INT_LCD 		BIT16
#define INT_DMA0 		BIT17
#define INT_DMA1 		BIT18
#define INT_DMA2 		BIT19
#define INT_DMA3 		BIT20
#define INT_SDI 		BIT21
#define INT_SPI0 		BIT22
#define INT_UART1 		BIT23
#define INT_NFCON 		BIT24
#define INT_USBD 		BIT25
#define INT_USBH 		BIT26
#define INT_IIC 		BIT27
#define INT_UART0 		BIT28
#define INT_SPI1 		BIT29
#define INT_RTC         BIT30
#define INT_ADC 		BIT31


#define INT_AC97 	BIT14
#define INT_WDT 	BIT13
#define INT_CAM_P 	BIT12
#define INT_CAM_C 	BIT11
#define INT_ADC_S 	BIT10
#define INT_TC 		BIT9
#define INT_ERR2 	BIT8
#define INT_TXD2 	BIT7
#define INT_RXD2 	BIT6
#define INT_ERR1 	BIT5
#define INT_TXD1 	BIT4
#define INT_RXD1 	BIT3
#define INT_ERR0 	BIT2
#define INT_TXD0 	BIT1
#define INT_RXD0 	BIT0

enum int_offset
{
	INT_EINT0_OFFSET = 0,
	INT_EINT1_OFFSET,
	INT_EINT2_OFFSET,
	INT_EINT3_OFFSET,
	INT_EINT4_7_OFFSET,
	INT_EINT8_23_OFFSET,
	INT_CAM_OFFSET,
	INT_nBATT_FLT_OFFSET,
	INT_TICK_OFFSET,
	INT_WDT_AC97_OFFSET,
	INT_TIMER0_OFFSET,
	INT_TIMER1_OFFSET,
	INT_TIMER2_OFFSET,
	INT_TIMER3_OFFSET,
	INT_TIMER4_OFFSET,
	INT_UART2_OFFSET,
	INT_LCD_OFFSET,
	INT_DMA0_OFFSET,
	INT_DMA1_OFFSET,
	INT_DMA2_OFFSET,
	INT_DMA3_OFFSET,
	INT_SDI_OFFSET,
	INT_SPI0_OFFSET,
	INT_UART1_OFFSET,
	INT_NFCON_OFFSET,
	INT_USBD_OFFSET,
	INT_USBH_OFFSET,
	INT_IIC_OFFSET,
	INT_UART0_OFFSET,
	INT_SPI1_OFFSET,
	INT_RTC_OFFSET,
	INT_ADC_OFFSET,
};

enum eint_offset {
	INT_EINT4_OFFSET = 4,
	INT_EINT5_OFFSET,
	INT_EINT6_OFFSET,
	INT_EINT7_OFFSET,
	INT_EINT8_OFFSET,
	INT_EINT9_OFFSET,
	INT_EINT10_OFFSET,
	INT_EINT11_OFFSET,
	INT_EINT12_OFFSET,
	INT_EINT13_OFFSET,
	INT_EINT14_OFFSET,
	INT_EINT15_OFFSET,
	INT_EINT16_OFFSET,
	INT_EINT17_OFFSET,
	INT_EINT18_OFFSET,
	INT_EINT19_OFFSET,
	INT_EINT20_OFFSET,
	INT_EINT21_OFFSET,
	INT_EINT22_OFFSET,
	INT_EINT23_OFFSET,
};

#define NUM_OF_INTERRUPT_SRCS 			(INT_ADC_OFFSET+1)

#define EINT_OFFSET_START INT_EINT4_OFFSET
#define NUM_OF_EXTERNAL_INTERRUPT_SRCS 	(INT_EINT23_OFFSET+1)

#define  mask_all_interrupts(BA) \
	writereg32(INTMSK_REG(BA),0xFFFFFFFF)
	
#define unmask_all_interrupts(BA) \
	writereg32(INTMSK_REG(BA),0x0)

#define mask_interrupt(BA,mask) \
	set_reg_params(INTMSK_REG(BA),mask)

#define unmask_interrupt(BA,mask) \
	clear_reg_params(INTMSK_REG(BA),mask)

#define mask_all_interrupt_subservice(BA) \
	writereg32(INTSUBMSK_REG(BA),0xFFFF)
	
#define unmask_all_interrupt_subservice(BA) \
	writereg32(INTSUBMSK_REG(BA),0)

#define mask_interrupt_sub_service(BA,mask) \
	set_reg_params(INTSUBMSK_REG(BA),mask)

#define unmask_interrupt_sub_service(BA,mask) \
	clear_reg_params(INTSUBMSK_REG(BA),mask)

#define get_interrupt_pending_status(BA,interrupt_line) \
	(readreg32(INTPND_REG(BA)) & (interrupt_line))

#define get_interrupt_subservice_pending_status(BA,interrupt_line) \
	(readreg32(SUBSRCPND_REG(BA)) & (interrupt_line))

#define set_interrupt_mode(BA,interrupt_line) \
	set_reg_params(INTMOD_REG(BA),interrupt_line)

#define set_fiq_mode(BA,interrupt_line) \
	clear_reg_params(INTMOD_REG(BA),interrupt_line)

#define enable_interrupt_service(BA,interrupt_mask) \
	clear_reg_params(INTMSK_REG(BA),interrupt_mask)

#define disable_interrupt_service(BA,interrupt_mask) \
	set_reg_params(INTMSK_REG(BA),interrupt_mask)

#define clear_interrupt_source_pending(BA,src_pnd_mask) \
	set_reg_params(SRCPND_REG(BA),src_pnd_mask)

#define clear_interrupt_pending(BA,pnd_mask) \
	set_reg_params(INTPND_REG(BA),pnd_mask)

void init_interrupt_controller(void);

#endif
