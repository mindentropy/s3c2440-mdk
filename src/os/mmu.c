#include "mmu.h"
#include "uart.h"
#include "board_config.h"
#include "uart_util.h"
#include "led.h"

static unsigned int *ttb; //Translation table base address.


/* 
 * How is the MMU setup?
 * =====================
 *
 * (Before modification on anything related to MMU please go through MMU section
 * 	please go through the ARM920T reference manual Chapter 3).
 * 
 * The setup_l1_section_table sets up level-1 page tables. This has 4096 entries.
 * This means that each page size is equal to 1MB. So totally the memory space 
 * covered is 4096 entries x 1048576 Bytes = 4GB.
 *
 * The ttb is the translation table base. 
 * -This holds the translation table base address(TRANSLATION_TABLE_BASE_ADDR). 
 * -This starts at 0x33000000 and ends at 0x33004096 (L1 Page table has a maximum of 4096 entries)
 * -This ttb is stored in CP15 register. The ttb - translation table base address is a pointer 
 *  pointer to the address of the master L1 table.
 *  The processor will know where the MMU table is by accessing the register CP15:c2.
 *  
 *  -Now for 32 bit ttb entries the top 31-20 (12 bits) contain the addresses 0-4095.
 *  -The remainings bits are used as flags. For a single level l1 table to address translation
 *  the flag is a L1_PG_TYPE (10b)
 *  -Next if the table is a section page table see Fig3-4 in page 3-9 of the reference manual.
 *  -In this there is always a Bit4 set bit present. The global domain access is the 
 *  domain manager.
 *  -The access permissions AP is the L1_AP_RW_RW.
 *  -The section pages are set to (00b) non-cached and non-buffered.
 *
 *  When an MMU wants to fetch the data for a virtual address it walks the translation table 
 *  and dereferences the array to find the starting base address[e.g. ttb[i] ]. Next it uses the
 *  remaining address bit [19-0] as an offset into the section [Section size being 1MB].
 *
 */

/*
 * TODO: 
 * Test by putting the vector table at 0x34000000 - 0x100000 = 0x33F00000
 * and mapping 0 to that address.
 *
 * Also map 0x34000000 - 0x100000 = 0x33F00000 to the same.
 * To test set up an exception to see there is jump to that location.
 *
 */

extern char __exception_vector_reloc_start__[];
extern char __exception_vector_reloc_end__[];

extern char __exception_handler_start__[];
extern char __exception_handler_end__[];
extern char __svc_stack_top__[];

extern char __exception_vector_reloc_loadaddr__[];

static void setup_interrupt_vector_table()
{
/*
 * TODO: Optimize it to remove the extra index variables. Unoptimized only for test purposes.
 *
 */

	char *vector_table = (char *)VECTOR_TABLE_START;

	/* 
	 * Need to get the lma of the code.
	 * The __svc_stack_top__ is the lma i.e. the generated address in the file.
	 * I need to use this as the start address for the later vectors
	 * and handlers.
	 * 
	 */

	char *src = (char *)__svc_stack_top__; 
						
	uint32_t i = 0;

	for(i = (uint32_t)__exception_vector_reloc_start__; 
					i<(uint32_t)__exception_vector_reloc_end__; 
					i++) {
		*vector_table = *src;
		vector_table++;
		src++;
	//	print_hex_uart(UART0_BA,vector_table[j]);
	}

	uart_puts(UART0_BA,"svc stack top:");
	print_hex_uart(UART0_BA,(uint32_t)__svc_stack_top__);

	uart_puts(UART0_BA,"vector reloc loadaddr:");
	print_hex_uart(UART0_BA,(uint32_t)__exception_vector_reloc_loadaddr__);

	/* Continue with the same place for handler source  */
	for(i = (uint32_t)__exception_handler_start__; 
					i<(uint32_t)__exception_handler_end__;
					i++) {
		*vector_table = *src;
		vector_table++;
		src++;
	//	print_hex_uart(UART0_BA,vector_table[j]);
	}

}


static void setup_l1_section_table(unsigned int flags)
{
	unsigned int i = 0;
	unsigned int base = 0; //Map RAM and i/o address range.

	base >>= 20;

	/* Map complete 4GB address space */
	for(i = 0;i<4096;i++) { //Complete 4096 entries.
		ttb[i] = ((base + i)<<20) | flags;
	}
	
	ttb[0] = (0x33F00000) | flags; /* Make the first 0-1MB point 
									  to 0x33F00000 i.e. location of 
									  the IVT.
									  */
	setup_interrupt_vector_table();
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

/*	while(1) {
		blink_leds(LED2|LED3);
	}
*/

}

void blink_led_test()
{
	while(1)
		blink_leds(LED2|LED3);
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

	
	setup_l1_section_table(L1_AP_RW_RW|L1_PG_TYPE|L1_PG_BIT4);

	/* 
	 * Set translation table base address.
	 * ==================================
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


	turn_mmu_on();

}
