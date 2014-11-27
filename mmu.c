#include "mmu.h"

#include "uart.h"

static unsigned int *ttb; //Translation table base address.

void setup_section_table()
{
	unsigned int i = 0, j = 0;

	for(i = 0;i<L1_TABLE_MAX_ENTRIES;i++,j+=L1_MAX_PAGE_SIZE)
	{
		ttb[i] = 0x30000000 + j;
	}
}

void mmu_init()
{
	//unsigned int dbgval = 0;

	unsigned int domain_access = DOMAIN_ACCESS_MANAGER;

	ttb = (unsigned int *)TRANSLATION_TABLE_BASE_ADDR;
	

	/* 
	 * Set translation table base address.
	 */
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

	/*
	 * Set domain access control register to Manager
	 */

	__asm__ __volatile__ (
		"mcr p15,0,%[domain_access],c3,c0,0\n\t"
		: /*No return value */
		:[domain_access]"r"(domain_access) /* domain_access input value */
		: /* No clobbers */
	);



}
