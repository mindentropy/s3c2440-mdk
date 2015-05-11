#ifndef WDT_H_

#define WDT_H_

#include "common.h"


#define WT_BA 		0x53000000

#define WTCON_OFF 	0x00
#define WTDAT_OFF 	0x04
#define WTCNT_OFF 	0x08

#define WTCON_REG(BA) \
	HW_REG((BA),WTCON_OFF)

#define WTDAT_REG(BA) \
	HW_REG((BA),WTDAT_OFF)

#define WTCNT_REG(BA) \
	HW_REG((BA),WTCNT_OFF)


#define PRESCALER_VAL 		set_bit_range(15,8)
#define WDT_EN 				(BIT5)

#define WDT_CLK_SEL         (BIT4|BIT3)

#define WDT_CLK_SEL16        (0)
#define WDT_CLK_SEL32        (BIT3)
#define WDT_CLK_SEL64        (BIT4)
#define WDT_CLK_SEL128       (BIT4|BIT3)
#define WDT_CLK_INT_EN 	     (BIT2)
#define WDT_CLK_RESET_EN     (BIT0)

/*
#define WTCON 	0x53000000
#define WTDAT 	0x53000004
#define WTCNT 	0x53000008
*/

#define disable_watchdog(BA) \
	writereg32(WTCON_REG(BA),0)


#endif
