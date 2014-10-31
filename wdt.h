#ifndef WDT_H_

#define WDT_H_

#include "common.h"

#define WTCON 	0x53000000

#define PRESCALER_VAL 		(BIT15|BIT14|BIT13|BIT12|BIT11|BIT10|BIT9|BIT8)
#define WDT_EN 				(BIT5)

#define WDT_CLK_SEL         (BIT4|BIT3)

#define WDT_CLK_SEL16        (0)
#define WDT_CLK_SEL32        (BIT3)
#define WDT_CLK_SEL64        (BIT4)
#define WDT_CLK_SEL128       (BIT4|BIT3)
#define WDT_CLK_INT_EN 	     (BIT2)
#define WDT_CLK_RESET_EN     (BIT0)

#define WTDAT 	0x53000004

#define WTCNT 	0x53000008

void disable_watchdog();

#endif
