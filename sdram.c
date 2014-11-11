#include "sdram.h"


void sdram_init()
{

	/* Configure BWSCON */
	writereg32(BWSCON,
			DW7_RESERVED|DW6_32b|DW5_RESERVED|DW4_RESERVED|
			DW3_RESERVED|DW2_RESERVED|DW1_RESERVED);

	/* Configure BANKCON6/BANKCON7 */

	/* Configure SDRAM Refresh settings */

	/* Configure Banksize setting */
}
