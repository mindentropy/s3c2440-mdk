#include "mmu.h"

#include "uart.h"

static unsigned int *ttb; //Translation table base address.


void mmu_init()
{
	//unsigned int dbgval = 0;

	ttb = (unsigned int *)TRANSLATION_TABLE_BASE_ADDR;
	
	__asm__ __volatile__ (
		"mcr p15,0,%[ttb],c2,c0,0\n\t"
		: /*No return value */
		:[ttb]"r"(ttb) /* ttb input value */
		:/* No clobbers */
	);

/*
	__asm__ __volatile__(
		"mrc p15,0,%[dbgval],c2,c0,0\n\t"
		:[dbgval]"=r"(dbgval)
		:
		:
		);

	print_hex(dbgval);
*/


}
