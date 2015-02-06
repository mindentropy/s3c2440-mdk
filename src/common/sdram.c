#include "sdram.h"


void sdram_init()
{

	/* Configure BWSCON */
/*	writereg32(BWSCON,
			DW7_RESERVED|DW6_32b|DW5_RESERVED|DW4_RESERVED|
			DW3_RESERVED|DW2_RESERVED|DW1_RESERVED);*/
	writereg32(BWSCON_REG(MEM_BA),
			DW7_RESERVED|DW6_32b|DW5_RESERVED|DW4_RESERVED|
			DW3_RESERVED|DW2_RESERVED|DW1_RESERVED);

	/* Configure BANKCON6/BANKCON7 */
/*	writereg32(BANKCON6,MT_SYNC_DRAM|SCAN_9BIT);*/
	writereg32(BANKCON6_REG(MEM_BA),MT_SYNC_DRAM|SCAN_9BIT);


	/* Set BANKCON7 to ROM/SRAM */
/*	writereg32(BANKCON7,MT_ROM_SRAM);*/
	writereg32(BANKCON7_REG(MEM_BA),MT_ROM_SRAM);

	/* Configure SDRAM Refresh settings */
	writereg32(REFRESHCTL_REG(MEM_BA),REFEN|Tsrc_5|1269);

	/* Configure Banksize setting */
	writereg32(BANKSIZE_REG(MEM_BA),BURST_EN|SCKE_EN|SCLK_EN|BK76MAP_64MB);

	/* Configure mode set register for BANK6 */
	//writereg32(MRSRB6,CAS_LATENCY_2CLK);
	writereg32(MRSRB6_REG(MEM_BA),CAS_LATENCY_2CLK);

	return;
}
