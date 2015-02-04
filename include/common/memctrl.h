#ifndef MEMCTRL_H_

#define MEMCTRL_H_

#include "common.h"


#define MEM_BA  0x48000000

#define BWSCON_OFF 0x0
#define BWSCON 	0x48000000

#define BWSCON_REG (BA) \
	HW_REG(BA,BWSCON_OFF)
	

#define ST7 	BIT31
#define WS7 	BIT30
#define DW7 	(BIT29|BIT28)


#define ST6 	BIT27
#define WS6 	BIT26
#define DW6 	(BIT25|BIT24)

#define ST5 	BIT23
#define WS5 	BIT22
#define DW5 	(BIT21|BIT20)

#define ST4 	BIT19
#define WS4 	BIT18
#define DW4 	(BIT17|BIT16)

#define ST3 	BIT15
#define WS3 	BIT14
#define DW3 	(BIT13|BIT12)

#define ST2 	BIT11
#define WS2 	BIT10
#define DW2 	(BIT9|BIT8)

#define ST1 	BIT7
#define WS1 	BIT6
#define DW1 	(BIT5|BIT4)

#define DW0 	(BIT2|BIT1) //Read only determined by OM[[1:0] pins.

#define BANKCON0_OFF 	0x04
#define BANKCON1_OFF	0x08
#define BANKCON2_OFF	0x0C
#define BANKCON3_OFF	0x10
#define BANKCON4_OFF	0x14
#define BANKCON5_OFF	0x18
#define BANKCON6_OFF	0x1C
#define BANKCON7_OFF	0x20

#define BANKCON0 	0x48000004
#define BANKCON1 	0x48000008
#define BANKCON2 	0x4800000C
#define BANKCON3 	0x48000010
#define BANKCON4 	0x48000014
#define BANKCON5 	0x48000018
#define BANKCON6 	0x4800001C
#define BANKCON7 	0x48000020

#define BANKCON0_REG(BA) \
	HW_REG(BA,BANKCON0_OFF)

#define BANKCON1_REG(BA) \
	HW_REG(BA,BANKCON1_OFF)
	
#define BANKCON2_REG(BA) \
	HW_REG(BA,BANKCON2_OFF)

#define BANKCON3_REG(BA) \
	HW_REG(BA,BANKCON3_OFF)

#define BANKCON4_REG(BA) \
	HW_REG(BA,BANKCON4_OFF)

#define BANKCON5_REG(BA) \
	HW_REG(BA,BANKCON5_OFF)

#define BANKCON6_REG(BA) \
	HW_REG(BA,BANKCON6_OFF)

#define BANKCON7_REG(BA) \
	HW_REG(BA,BANKCON7_OFF)


#define Tacs 		(BIT14|BIT13)
#define Tacs_0CLK   (0)
#define Tacs_1CLK   (BIT13)
#define Tacs_2CLK   (BIT14)
#define Tacs_4CLK   (BIT14|BIT13)

#define Tcos 		(BIT12|BIT11)
#define Tcos_0CLK   (0)
#define Tcos_1CLK   (BIT11)
#define Tcos_2CLK   (BIT12)
#define Tcos_4CLK   (BIT12|BIT11)

#define Tacc 		(BIT10|BIT9|BIT8)
#define Tacc_1CLK   (0)
#define Tacc_2CLK   (BIT8)
#define Tacc_3CLK   (BIT9)
#define Tacc_4CLK   (BIT9|BIT8)
#define Tacc_6CLK   (BIT10)
#define Tacc_8CLK   (BIT10|BIT8)
#define Tacc_10CLK  (BIT10|BIT9)
#define Tacc_14CLK  (BIT10|BIT9|BIT8)

#define Tcoh 		(BIT7|BIT6)
#define Tcoh_0CLK   (0)
#define Tcoh_1CLK   (BIT6)
#define Tcoh_2CLK   (BIT7)
#define Tcoh_4CLK   (BIT7|BIT6)

#define Tcah 		(BIT5|BIT4)
#define Tcah_0CLK   (0)
#define Tcah_1CLK   (BIT4)
#define Tcah_2CLK   (BIT5)
#define Tcah_4CLK   (BIT5|BIT4)

#define Tacp 		(BIT3|BIT2)
#define Tacp_0CLK   (0)
#define Tacp_1CLK   (BIT2)
#define Tacp_2CLK   (BIT3)
#define Tacp_4CLK   (BIT3|BIT2)

#define PMC 		(BIT1|BIT0)
#define PMC_NORMAL   (0)
#define PMC_4   	(BIT0)
#define PMC_8   	(BIT1)
#define PMC_16   	(BIT1|BIT0)


#define MT 				(BIT16|BIT15)
#define MT_ROM_SRAM 	(0)
#define MT_SYNC_DRAM 	(BIT16|BIT15)

#define SDRAM_Trcd 		(BIT3|BIT2)
#define SDRAM_Trcd_2CLK	(0)
#define SDRAM_Trcd_3CLK	(BIT2)
#define SDRAM_Trcd_4CLK	(BIT3)

#define SDRAM_SCAN 			(BIT1|BIT0)
#define SDRAM_SCAN_8BIT 	(0)
#define SDRAM_SCAN_9BIT 	(BIT0)
#define SDRAM_SCAN_10BIT 	(BIT1)

#define REFRESH 	0x48000024

#define REFRESH_OFF 0x24

#define REFRESH_REG(BA) \
	HW_REG(BA,REFRESH_OFF)

#define REFEN 							(BIT23)
#define TREFMD  						(BIT22)
#define Trp_SDRAM_RAS_PRECHARGE_TIME 	(BIT21|BIT20)
#define Trp_2CLK 						(0)
#define Trp_3CLK 						(BIT20)
#define Trp_4CLK 						(BIT21)

#define Tsrc 		(BIT19|BIT18)
#define Tsrc_4CLK 	(0)
#define Tsrc_5CLK 	(BIT18)
#define Tsrc_6CLK 	(BIT19)
#define Tsrc_7CLK 	(BIT19|BIT18)

#define BANKSIZE    (0x48000028)

#define BANKSIZE_OFF (0x28)

#define BANKSIZE_REG(BA) \
	HW_REG(BA,BANKSIZE_OFF)

#define BURST_EN    (BIT7)

#define SCKE_EN 	(BIT5)
#define SCLK_EN 	(BIT4)

#define BK76MAP 		(BIT2|BIT1|BIT0)
#define BK76MAP_128MB 	(BIT1)
#define BK76MAP_64MB 	(BIT0)
#define BK76MAP_32MB 	(0)
#define BK76MAP_16MB 	(BIT2|BIT1|BIT0)
#define BK76MAP_8MB 	(BIT2|BIT1)
#define BK76MAP_4MB 	(BIT2|BIT0)
#define BK76MAP_2MB 	(BIT2)

#define MRSRB6 		(0x4800002C)
#define MRSRB7 		(0x48000030)

#define MRSRB6_OFF  (0x2C)
#define MRSRB7_OFF  (0x30)

#define MRSRB6_REG(BA) \
	HW_REG(BA,MRSRB6_OFF)

#define MRSRB7_REG(BA) \
	HW_REG(BA,MRSRB7_OFF)

#define WBL 		(BIT9)
#define TM 			(BIT8|BIT7)
#define CL 			(BIT6|BIT5|BIT4)
#define BT 			(BIT3)
#define BL 			(BIT2|BIT1|BIT0)

#endif
