#ifndef ADC_TS_H_

#define ADC_TS_H_

#include "common.h"

#define ADC_BA 	(0x58000000)

#define ADCCON_OFF 		(0x00)
#define ADCCON_REG(BA) \
	HW_REG(BA,ADCCON_OFF)

#define ECFLAG 			(BIT15)
#define PRSCEN 			(BIT14)
#define PRSCVL_MSK 		set_bit_range(13,6)
#define SEL_MUX 		set_bit_range(5,3)
#define STDBM 			(BIT2)
#define READ_START 		(BIT1)
#define ENABLE_START 	(BIT0)

#define ADCTSC_OFF 		(0x04)
#define ADCTSC_REG(BA) \
	HW_REG(BA,ADCTSC_OFF)


#define UDSEN 					(BIT8)
#define YM_SEN 					(BIT7)
#define YP_SEN 					(BIT6)
#define XM_SEN 					(BIT5)
#define XP_SEN 					(BIT4)
#define PULL_UP 				(BIT3)
#define ADCTSC_AUTO_PST 		(BIT2)
#define XY_PST 					(BIT1|BIT0)

#define ADCDLY_OFF 		(0x08)
#define ADCDLY_REG(BA) \
	HW_REG(BA,ADCDLY_OFF)

#define DELAY_MSK   (SHORT_MASK_LSB)


#define ADCDAT0_OFF 	(0x0C)
#define ADCDAT0_REG(BA) \
	HW_REG(BA,ADCDAT0_OFF)

#define ADCDAT1_OFF 	(0x10)
#define ADCDAT1_REG(BA) \
	HW_REG(BA,ADCDAT1_OFF)

#define UPDOWN  			BIT15
#define ADCDAT1_AUTO_PST  	BIT14
#define XY_PST_MASK  		(BIT13|BIT12)

#define X_POS_MEASUREMENT (BIT12)
#define Y_POS_MEASUREMENT (BIT13)
#define WAIT_FOR_INT_MODE (BIT13|BIT12)

#define YPDATA 		set_bit_range(9,0)
#define XPDATA 		set_bit_range(9,0)


#define ADCUPDN_OFF 	(0x14)
#define ADCUPDN_REG(BA) \
	HW_REG(BA,ADCUPDN_OFF)

#define TSC_UP 	BIT1
#define TSC_DN 	BIT0


#endif
