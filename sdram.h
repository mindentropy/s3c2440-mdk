#ifndef SDRAM_H_

#define SDRAM_H_


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

#define Tacp_CLK_2	0x0
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

#define Trcd_CLK_2	0x0
#define Trcd_CLK_3	0x1
#define Trcd_CLK_4	0x2

#define SCAN_8BIT		0x0
#define SCAN_9BIT		0x1
#define SCAN_10BIT		0x2

#define REFRESHCON		0x48000024

#define REFEN				0x01
#define TREFMD_SELF_REFRESH	0x01

#define Trp_2	0x00
#define Trp_3	0x01
#define Trp_4	0x02
#define Trp_NS	0x03

#define Tsrc_4	0x00
#define Tsrc_5	0x01
#define Tsrc_6	0x02
#define Tsrc_7	0x03


#define BANKSIZE	0x48000028

#define BURST_EN	0x01
#define SCKE_EN		0x01
#define SCLK_EN		0x01

#define BK76MAP_128MB	0x02
#define BK76MAP_64MB	0x01
#define BK76MAP_32MB	0x00
#define BK76MAP_16MB	0x07
#define BK76MAP_8MB		0x06
#define BK76MAP_4MB		0x05
#define BK76MAP_2MB		0x04

#define MRSRB6		0x4800002C
#define MRSRB7		0x48000030


#endif

