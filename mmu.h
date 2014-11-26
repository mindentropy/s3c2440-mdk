#ifndef MMU_H_

#define MMU_H_

#include "common.h"
#include "gpio_def.h"

/* The translation table base address should be @16kB boundary */
#define TRANSLATION_TABLE_BASE_ADDR (0x32000000U)

#define L1_TABLE_MAX_ENTRIES 		(4096U)

void mmu_init();

#define PG_TYPE_MASK       		(0x3)
/*
 * Level 1 Page table attributes 
 */

#define L1_PG_BASE_ADDR_MASK 	(0xFFF00000)
#define L1_PG_SBZ_MASK 	  		(0xFF000)
#define L1_PG_AP_MASK 		  	(0xC00)
#define L1_PG_DOMAIN_MASK    	(0x1E0)
#define L1_PG_C_MASK         	(1<<3)
#define L1_PG_B_MASK         	(1<<2)
#define L1_PG_TYPE 				(0x2)

/*
 * Level 2 Coarse Page table attributes
 *
 */

#define L2_PG_BASE_ADDR_MASK 	(0xFFFFFC00)
#define L2_PG_SBZ_MASK 			(0xC)
#define L2_PG_TYPE 				(0x1)

/*
 * Level 3 Fine Page table attributes
 *
 */
#define L3_PG_BASE_ADDR_MASK    (0xFFFFF000)
#define L3_PG_SBZ_MASK 			(0xE0C)
#define L3_PG_TYPE 				(0x3)

#define PG_FAULT_TYPE 			(0x00)



#endif

