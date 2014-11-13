#ifndef SDRAM_H_

#define SDRAM_H_

#include "common.h"

#define BWSCON 		0x48000000

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


#define Tacs_CLK_0	0x0
#define Tacs_CLK_1	0x1
#define Tacs_CLK_2	0x2
#define Tacs_CLK_4	0x3

#define Tcos_CLK_0	0x0
#define Tcos_CLK_1	0x1
#define Tcos_CLK_2	0x2
#define Tcos_CLK_4	0x3

#define Tcoh_CLK_0	0x0
#define Tcoh_CLK_1	0x1
#define Tcoh_CLK_2	0x2
#define Tcoh_CLK_4	0x3

#define Tcoh_CLK_0	0x0
#define Tcoh_CLK_1	0x1
#define Tcoh_CLK_2	0x2
#define Tcoh_CLK_4	0x3

#define Tcah_CLK_0	0x0
#define Tcah_CLK_1	0x1
#define Tcah_CLK_2	0x2
#define Tcah_CLK_4	0x3

#define Tacp_CLK_2	((0x0)<<2)
#define Tacp_CLK_3	0x1
#define Tacp_CLK_4	0x2
#define Tacp_CLK_6	0x3

#define PMC_0		0x00
#define PMC_4		0x01
#define PMC_8		0x02
#define PMC_16		0x03

#define Tacc_CLK_1	0x00
#define Tacc_CLK_2	0x01
#define Tacc_CLK_3	0x02
#define Tacc_CLK_4	0x03
#define Tacc_CLK_6	0x04
#define Tacc_CLK_8	0x05
#define Tacc_CLK_10	0x06
#define Tacc_CLK_14	0x07


#define BANKCON6	0x4800001C
#define BANKCON7	0x48000020

#define MT_ROM_SRAM			0x0
#define MT_RESERVED_01		0x1
#define MT_RESERVED_02		0x2
#define MT_SYNC_DRAM		0x3

#define Trcd_CLK_2	((0x0)<<2)
#define Trcd_CLK_3	0x1
#define Trcd_CLK_4	0x2

#define SCAN_8BIT		0x0
#define SCAN_9BIT		0x1
#define SCAN_10BIT		0x2

#define REFRESHCTL		0x48000024

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


#define BANKSIZE	0x48000028

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


#endif

