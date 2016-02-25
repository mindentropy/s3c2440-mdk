#include "memctl.h"
#include "clock_pm.h"
#include "gpio_def.h"

void sdram_init()
{

	/* Configure BWSCON */
	writereg32(BWSCON_REG(MEM_BA),
			DW7_RESERVED|DW6_32b|DW5_RESERVED|DW4_RESERVED|
			DW3_RESERVED|DW2_RESERVED|DW1_RESERVED);

	/* Configure BANKCON6/BANKCON7 */
	writereg32(BANKCON6_REG(MEM_BA),MT_SYNC_DRAM|SCAN_9BIT);

	/* 
	 * Set BANKCON7 to ROM/SRAM i.e 00 and not SYNC_DRAM.
	 * Rest of the values should not be used as they are reserved
	 * Default value is SYNC_DRAM which should not be used.
	 */
	writereg32(BANKCON7_REG(MEM_BA),MT_ROM_SRAM);

	/* Disable clock to BANK7 */
	//set_reg_bits(MISCCR_REG(),nEN_SCLK1);

	/* Configure SDRAM Refresh settings */
	writereg32(REFRESHCTL_REG(MEM_BA),REFEN|Tsrc_5|1269);

	/* Configure Banksize setting */
	writereg32(BANKSIZE_REG(MEM_BA),BURST_EN|SCKE_EN|SCLK_EN|BK76MAP_64MB);

	/* Configure mode set register for BANK6 */
	writereg32(MRSRB6_REG(MEM_BA),CAS_LATENCY_2CLK);

	return;
}
