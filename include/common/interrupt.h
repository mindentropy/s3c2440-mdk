#ifndef INTERRUPT_H_

#define INTERRUPT_H_

#include "common.h"

#define INT_BA 			0x4A000000

#define SRCPND_OFF 		0x00
#define INTMOD_OFF  	0x04
#define INTMSK_OFF  	0x08
#define INTPRIORITY_OFF 0x0C
#define INTPND_OFF 		0x10
#define INTOFFSET_OFF   0x14
#define SUBSRCPND_OFF 	0x18
#define INTSUBMSK_OFF 	0x1C

#define SRCPND_REG(BA) \
		HW_REG(BA,SRCPND_OFF)

#define INTMOD_REG(BA) \
		HW_REG(BA,INTMOD_OFF)

#define INTMSK_REG(BA) \
		HW_REG(BA,INTMSK_OFF)

#define INTPRIORITY_REG(BA) \
		HW_REG(BA,INTPRIORITY_OFF)

#define INTPND_REG(BA) \
		HW_REG(BA,INTPND_OFF)

#define INTOFFSET_REG(BA) \
		HW_REG(BA,INTOFFSET_OFF)

#define SUBSRCPND_REG(BA) \
		HW_REG(BA,SUBSRCPND_OFF)

#define INTSUBMSK_REG(BA) \
		HW_REG(BA,INTSUBMSK_OFF)

#define SRCPND 		0x4A000000
#define INTMOD 		0x4A000004
#define INTMSK 		0x4A000008
#define INTPRIORITY 0x4A00000C
#define INTPND 		0x4A000010
#define INTOFFSET 	0x4A000014


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



#define SUBSRCPND 	0x4A000018
#define INTSUBMSK 	0x4A00001C

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

#define  disable_all_interrupts(BA) \
	writereg32(INTMSK_REG(BA),0xFFFFFFFF)
	
#define enable_all_interrupts(BA) \
	writereg32(INTMSK_REG(BA),0x0)


#define disable_all_interrupt_subservice(BA) \
	writereg32(INTSUBMSK_REG(BA),0xFFFF)
	
#define enable_all_interrupt_subservice(BA) \
	writereg32(INTSUBMSK_REG(BA),0)
	

#define enable_interrupt_sub_service(BA,mask) \
	clear_reg_params(INTSUBMSK_REG(BA),mask)

#define disable_interrupt_sub_service(BA,mask) \
	set_reg_params(INTSUBMSK_REG(BA),mask)


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


#endif
