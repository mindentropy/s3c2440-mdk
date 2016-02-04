#include "common.h"
#include "ethernet.h"
#include "memctl.h"

void init_ethernet()
{
	//config ethernet bank.
	//WS4 Wait state is enabled in the schematic. Turned on high.
	//Also connected to nWAIT.
	writereg32(BWSCON_REG(MEM_BA),
		(readreg32(BWSCON_REG(MEM_BA)) & ~(BANK4_CONFIG_MASK))
							| (DW4_16b|ST4|WS4));


/*
 * HCLK -> 101Mhz.
 *
 * Tacs (Address setup time before nGCSn) -> 0 clock. 
 * 			(Should it be 1 clock/10 ns? margin?)
 * Tcos (Chip selection setup time before nOE) -> 1 clock. (10 ns). 
 * 				DM9000 datasheet I find it is T1 = 5ns.
 * Tacc (Access cycle) -> 4 clocks (40 ns). DM9000 datasheet 
 * 		I find it is T2 = 22ns but if nWait is present Tacc >= 4 clocks 
 * 		according to S3C2440 data sheet.
 * Tcoh (Chip selction hold time after nOE) -> 1 clock (10 ns).  
 * 			DM9000 datasheet I find it is T5 = 5ns.
 * Tcah (Address hold time after nGCSn) -> 0 ns (Should it be 1 clock/10 ns? margin?)
 * Tacp (Page mode access cycle) -> 00
 * PMC (Page moe configuration) -> 00 (normal).
 *
 * LnOE -> IOR# (nOE)
 * LnWE -> IOW# (nWE)
 * nGCSn nLANCS -> AE (Address enable)
 * 				-> nCS
 * AEN to IOR#
 * nCS to LnOE.
 * 
 * Assuming with margins the values:
 * 
 *  Tacs 01  	[14:13]
 *  Tcos 01 	[12:11]
 *  Tacc 011 	[10:8]
 *  Tcoh 01  	[7:6]
 *  Tcah 01     [5:4]
 *  Tacp 00     [3:2]
 *  PMC  00     [1:0]
 *  
 * 010101101010000 == 0x2B50.
 * 
 * Tune up goal 0x2E50.
 */
 

}
