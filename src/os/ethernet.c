#include "common.h"
#include "ethernet.h"
#include "memctl.h"

void init_ethernet()
{
	//config ethernet bank.
	writereg32(BWSCON_REG(MEM_BA),
			(readreg32(BWSCON_REG(MEM_BA)) & ~(BANK4_CONFIG_MASK))
								| (DW4_16b|ST4|WS4));

}
