#ifndef SDRAM_H_

#define SDRAM_H_

#include "common.h"
#include "gpio_def.h"
#include "clock_pm.h"

#define MEM_BA  	0x48000000

#define BWSCON_OFF 	0x0
#define BWSCON 		0x48000000

#define BWSCON_REG(BA) \
	HW_REG(BA,BWSCON_OFF)

#define ST7 			(BIT31)
#define WS7     		(BIT30)
#define DW7        		(BIT29|BIT28)

#define DW7_8b     		(0)
#define DW7_16b    		(BIT28)
#define DW7_32b    		(BIT29)
#define DW7_RESERVED   	(BIT29|BIT28)

#define ST6 			(BIT27)
#define WS6         	(BIT26)
#define DW6         	(BIT25|BIT24)

#define DW6_8b     		(0)
#define DW6_16b    		(BIT24)
#define DW6_32b    		(BIT25)
#define DW6_RESERVED   	(BIT25|BIT24)


#define ST5 			(BIT23)
#define WS5         	(BIT22)
#define DW5         	(BIT21|BIT20)

#define DW5_8b     		(0)
#define DW5_16b    		(BIT20)
#define DW5_32b    		(BIT21)
#define DW5_RESERVED   	(BIT21|BIT20)

#define ST4 			(BIT19)
#define WS4         	(BIT18)
#define DW4         	(BIT17|BIT16)

#define DW4_8b     		(0)
#define DW4_16b    		(BIT16)
#define DW4_32b    		(BIT17)
#define DW4_RESERVED   	(BIT17|BIT16)

#define ST3 			(BIT15)
#define WS3        	 	(BIT14)
#define DW3         	(BIT13|BIT12)

#define DW3_8b     		(0)
#define DW3_16b    		(BIT12)
#define DW3_32b    		(BIT13)
#define DW3_RESERVED   	(BIT13|BIT12)

#define ST2 			(BIT11)
#define WS2         	(BIT10)
#define DW2         	(BIT9|BIT8)

#define DW2_8b     		(0)
#define DW2_16b    		(BIT8)
#define DW2_32b    		(BIT9)
#define DW2_RESERVED   	(BIT9|BIT8)

#define ST1 			(BIT7)
#define WS1         	(BIT6)
#define DW1 			(BIT5|BIT4)

#define DW1_8b     		(0)
#define DW1_16b    		(BIT4)
#define DW1_32b    		(BIT5)
#define DW1_RESERVED   	(BIT5|BIT4)

#define DW0 			(BIT2|BIT1)
#define DW0_16b 		(BIT1)
#define DW0_32b 		(BIT2)


#define BANKCON0	0x48000004
#define BANKCON1	0x48000008
#define BANKCON2	0x4800000C
#define BANKCON3	0x48000010
#define BANKCON4	0x48000014
#define BANKCON5	0x48000018

#define BANKCON0_OFF 	0x04
#define BANKCON1_OFF	0x08
#define BANKCON2_OFF	0x0C
#define BANKCON3_OFF	0x10
#define BANKCON4_OFF	0x14
#define BANKCON5_OFF	0x18

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

#define Tacs        (BIT14|BIT13)
#define Tacs_CLK_0	0x0
#define Tacs_CLK_1	(BIT13)
#define Tacs_CLK_2	(BIT14)
#define Tacs_CLK_4	(BIT14|BIT13)

#define Tcos        (BIT12|BIT11)
#define Tcos_CLK_0	0x0
#define Tcos_CLK_1	(BIT11)
#define Tcos_CLK_2	(BIT12)
#define Tcos_CLK_4	(BIT12|BIT11)

#define Tcoh        (BIT7|BIT6)
#define Tcoh_CLK_0	0x0
#define Tcoh_CLK_1	(BIT6)
#define Tcoh_CLK_2	(BIT7)
#define Tcoh_CLK_4	(BIT7|BIT6)

#define Tcah     	(BIT5|BIT4)
#define Tcah_CLK_0	0x0
#define Tcah_CLK_1	(BIT4)
#define Tcah_CLK_2	(BIT5)
#define Tcah_CLK_4	(BIT5|BIT4)

#define Tacp        (BIT3|BIT2)
#define Tacp_CLK_2	((0x0)<<2)
#define Tacp_CLK_3	(BIT2)
#define Tacp_CLK_4	(BIT3)
#define Tacp_CLK_6	(BIT3|BIT2)

#define PMC 		(BIT1|BIT0)
#define PMC_0		0x00
#define PMC_4		(BIT0)
#define PMC_8		(BIT1)
#define PMC_16		(BIT1|BIT0)

#define Tacc        (BIT10|BIT9|BIT8)

#define Tacc_CLK_1	0x00
#define Tacc_CLK_2	(BIT8)
#define Tacc_CLK_3	(BIT9)
#define Tacc_CLK_4	(BIT9|BIT8)
#define Tacc_CLK_6	(BIT10)
#define Tacc_CLK_8	(BIT10|BIT8)
#define Tacc_CLK_10	(BIT10|BIT9)
#define Tacc_CLK_14	(BIT10|BIT9|BIT8)


#define BANKCON6	0x4800001C
#define BANKCON7	0x48000020

#define BANKCON6_OFF	0x1C
#define BANKCON7_OFF	0x20

#define BANKCON6_REG(BA) \
	HW_REG(BA,BANKCON6_OFF)

#define BANKCON7_REG(BA) \
	HW_REG(BA,BANKCON7_OFF)

#define MT_ROM_SRAM			0
#define MT_RESERVED_01		(BIT15)
#define MT_RESERVED_02		(BIT16)
#define MT_SYNC_DRAM		(BIT16|BIT15)

#define Trcd_CLK_2	((0x0)<<2)
#define Trcd_CLK_3	(BIT2)
#define Trcd_CLK_4	(BIT3)

#define SCAN_8BIT		0x0
#define SCAN_9BIT		BIT0
#define SCAN_10BIT		BIT1

#define REFRESHCTL		0x48000024
#define REFRESHCTL_OFF	0x24

#define REFRESHCTL_REG(BA) \
	HW_REG(BA,REFRESHCTL_OFF)

#define REFEN				BIT23
#define TREFMD_SELF_REFRESH	BIT22

#define Trp     (BIT21|BIT20)
#define Trp_2	0
#define Trp_3	(BIT20)
#define Trp_4	(BIT21)
#define Trp_NS	(BIT21|BIT20)

#define Tsrc    (BIT19|BIT18)

#define Tsrc_4	0x00
#define Tsrc_5	(BIT18)
#define Tsrc_6	(BIT19)
#define Tsrc_7	(BIT19|BIT18)


#define BANKSIZE		0x48000028
#define BANKSIZE_OFF	0x28

#define BANKSIZE_REG(BA) \
	HW_REG(BA,BANKSIZE_OFF)

#define BURST_EN	BIT7
#define SCKE_EN		BIT5
#define SCLK_EN		BIT4

#define BK76MAP_128MB	(BIT1)
#define BK76MAP_64MB	(BIT0)
#define BK76MAP_32MB	(0)
#define BK76MAP_16MB	(BIT2|BIT1|BIT0)
#define BK76MAP_8MB		(BIT2|BIT1)
#define BK76MAP_4MB		(BIT2|BIT0)
#define BK76MAP_2MB		(BIT2)

#define MRSRB6		0x4800002C
#define MRSRB7		0x48000030

#define MRSRB6_OFF  (0x2C)
#define MRSRB7_OFF  (0x30)

#define MRSRB6_REG(BA) \
	HW_REG(BA,MRSRB6_OFF)

#define MRSRB7_REG(BA) \
	HW_REG(BA,MRSRB7_OFF)

#define WBL 				BIT9
#define TM 					(BIT8|BIT7)
#define TM_MODE_REG_SET 	(0)
#define CAS_LATENCY         (BIT6|BIT5|BIT4)
#define CAS_LATENCY_1CLK    (0)
#define CAS_LATENCY_2CLK    (BIT5)
#define CAS_LATENCY_3CLK    (BIT5|BIT4)

#define BT 				(BIT3)
#define BT_SEQUENTIAL 	(0)

#define BL 				(BIT2|BIT1|BIT0)
#define BL_FIXED 		(0)

void sdram_init();

//TODO: Board dependent hence should be present in config.h


#endif
