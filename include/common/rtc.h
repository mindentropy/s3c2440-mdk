#ifndef RTC_H_

#define RTC_H_

#define RTC_BA 	(0x57000000)

#define RTCCON_L_OFF 	(0x40)
#define RTCCON_B_OFF 	(0x43)

#define RTCCON_L_REG(BA) \
	HW_REG(BA,RTCCON_L_OFF)

#define RTCCON_B_REG(BA) \
	HW_REG(BA,RTCCON_B_OFF)

#define CLKRST 		(BIT3)
#define CNTSEL 		(BIT2)
#define CLKSEL 		(BIT1)
#define RTCEN 		(BIT0)

#define TICNT_L_OFF 	(0x44)
#define TICNT_B_OFF 	(0x47)

#define TICNT_L_REG(BA) \
	HW_REG(BA,TICNT_L_OFF)

#define TICNT_B_REG(BA) \
	HW_REG(BA,TICNT_B_OFF)

#define TICK_INT_EN 		(BIT7)
#define TICK_TIME_CNT 		set_bit_range(6,0)

#define RTCALM_L_OFF 	(0x50)
#define RTCALM_B_OFF 	(0x53)

#define RTCALM_L_REG(BA) \
	HW_REG(BA,RTCALM_L_OFF)

#define RTCALM_B_REG(BA) \
	HW_REG(BA,RTCALM_B_OFF)


#define ALMEN 	BIT6
#define YEAREN 	BIT5
#define MONEN 	BIT4
#define DATEEN 	BIT3
#define HOUREN 	BIT2
#define MINEN 	BIT1
#define SECEN 	BIT0


#define ALMSEC_L_OFF 	(0x54)
#define ALMSEC_B_OFF 	(0x57)

#define ALMSEC_L_REG(BA) \
	HW_REG(BA,ALMSEC_L_OFF)

#define ALMSEC_B_REG(BA) \
	HW_REG(BA,ALMSEC_B_OFF)

#define SECDATA_MSK 		set_bit_range(6,0)
#define SECDATA_BCD_MSK 	set_bit_range(6,4)
#define SECDATA_VAL_MSK 	set_bit_range(3,0)

#define ALMMIN_L_OFF 	(0x58)
#define ALMMIN_B_OFF 	(0x5B)

#define ALMMIN_L_REG(BA) \
	HW_REG(BA,ALMMIN_L_OFF)

#define ALMMIN_B_REG(BA) \
	HW_REG(BA,ALMMIN_B_OFF)

#define MINDATA_MSK 		set_bit_range(6,0)
#define MINDATA_BCD_MSK 	set_bit_range(6,4)
#define MINDATA_VAL_MSK 	set_bit_range(3,0)

#define ALMHOUR_L_OFF 	(0x5C)
#define ALMHOUR_B_OFF 	(0x5F)

#define ALMHOUR_L_REG(BA) \
	HW_REG(BA,ALMHOUR_L_OFF)

#define ALMHOUR_B_REG(BA) \
	HW_REG(BA,ALMHOUR_B_OFF)

#define HOURDATA_MSK 		set_bit_range(5,0)
#define HOURDATA_BCD_MSK 	set_bit_range(5,4)
#define HOURDATA_VAL_MSK 	set_bit_range(3,0)

#define ALMDATE_L_OFF 	(0x60)
#define ALMDATE_B_OFF 	(0x63)

#define ALMDATE_L_REG(BA) \
	HW_REG(BA,ALMDATE_L_OFF)

#define ALMDATE_B_REG(BA) \
	HW_REG(BA,ALMDATE_B_OFF)

#define DATEDATA_MSK 		set_bit_range(5,0)
#define DATEDATA_BCD_MSK 	set_bit_range(5,4)
#define DATEDATA_VAL_MSK 	set_bit_range(3,0)


#define ALMMON_L_OFF 	(0x64)
#define ALMMON_B_OFF 	(0x67)

#define ALMMON_L_REG(BA) \
	HW_REG(BA,ALMMON_L_OFF)

#define ALMMON_B_REG(BA) \
	HW_REG(BA,ALMMON_B_OFF)

#define MONDATA_BCD_MSK  (BIT4)
#define MONDATA_VAL_MSK  set_bit_range(3,0)


#define ALMYEAR_L_OFF 	(0x68)
#define ALMYEAR_B_OFF 	(0x6B)

#define ALMYEAR_L_REG(BA) \
	HW_REG(BA,ALMYEAR_L_OFF)

#define ALMYEAR_B_REG(BA) \
	HW_REG(BA,ALMYEAR_B_OFF)

#define YEARDATA_MSK 	(BYTE_MASK)

#define BCDSEC_L_OFF 	(0x70)
#define BCDSEC_B_OFF 	(0x73)

#define BCDSEC_L_REG(BA) \
	HW_REG(BA,BCDSEC_L_OFF)

#define BCDSEC_B_REG(BA) \
	HW_REG(BA,BCDSEC_B_OFF)

#define SECDATA_MSK 			set_bit_range(6,0)
#define SECDATA_BCD_MSK 		set_bit_range(6,4)
#define SECDATA_VAL_MSK 		set_bit_range(3,0)

#define BCDMIN_L_OFF 	(0x74)
#define BCDMIN_B_OFF 	(0x77)

#define BCDMIN_L_REG(BA) \
	HW_REG(BA,BCDMIN_L_OFF)
#define BCDMIN_B_REG(BA) \
	HW_REG(BA,BCDMIN_B_OFF)

#define MINDATA_MSK 		set_bit_range(6,0)
#define MINDATA_BCD_MSK 	set_bit_range(6,4)
#define MINDATA_VAL_MSK 	set_bit_range(3,0)

#define BCDHOUR_L_OFF 	(0x78)
#define BCDHOUR_B_OFF 	(0x7B)

#define BCDHOUR_L_REG(BA) \
	HW_REG(BA,BCDHOUR_L_OFF)

#define BCDHOUR_B_REG(BA) \
	HW_REG(BA,BCDHOUR_B_OFF)

#define HOURDATA_MSK 		set_bit_range(5,0)
#define HOURDATA_BCD_MSK 	set_bit_range(5,4)
#define HOURDATA_VAL_MSK 	set_bit_range(3,0)


#define BCDDATE_L_OFF 	(0x7C)
#define BCDDATE_B_OFF 	(0x7F)

#define BCDDATE_L_REG(BA) \
	HW_REG(BA,BCDDATE_L_OFF)

#define BCDDATE_B_REG(BA) \
	HW_REG(BA,BCDDATE_B_OFF)

#define DATEDATA_MSK 	set_bit_range(5,0)
#define DATEDATA_BCD_MSK set_bit_range(5,4)
#define DATEDATA_VAL_MSK set_bit_range(3,0)


#define BCDDAY_L_OFF 	(0x80)
#define BCDDAY_B_OFF 	(0x83)

#define BCDDAY_L_REG(BA) \
	HW_REG(BA,BCDDAY_L_OFF)
#define BCDDAY_B_REG(BA) \
	HW_REG(BA,BCDDAY_B_OFF)

#define DAYDATA_MSK 	set_bit_range(2,0)

#define BCDMON_L_OFF 	(0x84)
#define BCDMON_B_OFF 	(0x87)

#define BCDMON_L_REG(BA) \
	HW_REG(BA,BCDMON_L_OFF)

#define BCDMON_B_REG(BA) \
	HW_REG(BA,BCDMON_B_OFF)

#define MONDATA_MSK 	set_bit_range(4,0)
#define MONDATA_IS_BCD_VAL (BIT4)

#define BCDYEAR_L_OFF 	(0x88)
#define BCDYEAR_B_OFF 	(0x8B)

#define BCDYEAR_L_REG(BA) \
	HW_REG(BA,BCDYEAR_L_OFF)

#define BCDYEAR_B_REG(BA) \
	HW_REG(BA,BCDYEAR_B_OFF)

#define YEARDATA_MSK 	(BYTE_MASK)

#endif
