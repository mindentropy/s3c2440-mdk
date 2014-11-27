#include "mmu.h"
#include "uart.h"
#include "board_config.h"
#include "led.h"

static unsigned int *ttb; //Translation table base address.

static void setup_section_table(unsigned int flags)
{
	unsigned int i = 0;
	unsigned int base = PHYS_START ;
	base >>= 20;

	puts("Section table dump \r\n");
	for(i = 0;i<64;i++) { //64MB RAM
		ttb[i] = ((base + i)<<20) | flags;

		print_hex(ttb[i]);
		puts("\r\n");
	}
}

extern void blink_leds(unsigned int leds);
void turn_mmu_on()
{

	__asm__ __volatile__ (
		"mov r0,#0\n\t" //Clear register r0
		"mcr p15,0,r0,c7,c10,4\n\t" //Drain write buffer
		"mcr p15,0,r0,c8,c7,0\n\t" //Flush I,D and TLBS
		"mrc p15,0,r0,c1,c0,0\n\t" //Read control register.
		"orr r0,r0,#0x1\n\t" //Set the MMU enable bit to 1.
		"mcr p15,0,r0,c1,c0,0\n\t" //Write to control register.
		"mov r0,#0\n\t" //Clear register r0
		"mcr p15,0,r0,c8,c7,0\n\t" //Flush I,D and TLBS
		: /* No output */
		: /* No input */
		: "r0" /* r0 gets clobbered */
	);


}

#if 0
static void turn_mmu_on()
{
	unsigned int cache_control_reg = 0;

	__asm__ __volatile__(
		"mrc p15,0,%[cache_control_reg],c1,c0,0\n\t"
		:[cache_control_reg]"=r"(cache_control_reg) /* control reg return value */
		: /* No input */
		: /* No clobbers */
	);


	cache_control_reg |= MMU_ENABLE;

	/* Do you need to flush the pipeline? */
	__asm__ __volatile__(
		"mcr p15,0,%[cache_control_reg],c1,c0,0\n\t"
		: /*No return value */
		:[cache_control_reg]"r"(cache_control_reg) /* Control reg input value */
		: /* No clobbers */
	);

	/*puts("Cache control reg : ");
	print_hex(cache_control_reg);
	puts("\r\n");*/
}

#endif


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

	setup_section_table(L1_AP_RW_RW|L1_PG_TYPE|L1_PG_BIT4);

	turn_mmu_on();

}
