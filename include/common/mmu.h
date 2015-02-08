#ifndef MMU_H_

#define MMU_H_

#include "common.h"
#include "gpio_def.h"

/* The translation table base address should be @16kB boundary */
#define TRANSLATION_TABLE_BASE_ADDR (0x33000000U)

#define L1_TABLE_MAX_ENTRIES 		(4096U)

#define L1_MAX_PAGE_SIZE 			(0x100000U)

void mmu_init();

#define PG_TYPE_MASK       		(0x3)

/*
 * Level 1 Page table attributes 
 */

#define L1_PG_BASE_ADDR_MASK 	(0xFFF00000)
#define L1_PG_SBZ_MASK 	  		(0xFF000)
#define L1_PG_AP_MASK 		  	(0xC00)
#define L1_PG_DOMAIN_MASK    	(BIT8|BIT7|BIT6|BIT5)
#define L1_PG_BIT4 				(BIT4)
#define L1_PG_C_MASK         	(BIT3)
#define L1_PG_B_MASK         	(BIT2)
#define L1_PG_TYPE 				(0x2)

#define L1_PG_CACHEABLE         (BIT3)
/* 
 * There is a small write buffer FIFO between the cache
 * and RAM. This is present to manage the speed difference
 * between cache and RAM. As RAM is slower the write buffer
 * is used to ease the burst pressure from the cache.
 *
 * For more info see Chapter 12 Pg 416 of ARM System Developers
 * guide.
 */
#define L1_PG_BUFFERABLE        (BIT2)



#define L1_AP_RW_RW 	(BIT11|BIT10)
#define L1_AP_RW_RO 	(BIT11)
#define L1_AP_RW_NA 	(BIT10)
#define L1_AP_NA_NA 	(0x0)

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

#define DOMAIN_ACCESS_MANAGER   (0x3)
#define DOMAIN_ACCESS_RESERVED  (0x2)
#define DOMAIN_ACCESS_CLIENT    (0x1)
#define DOMAIN_ACCESS_NO_ACCESS (0x0)


#define ASYNC_CLOCK_SELECT  (BIT31)
#define notFASTBUS 			(BIT30)
#define RR_ENABLE 			(BIT14)
#define BASE_LOC_EXCEP_REG  (BIT13)
#define ICACHE_ENABLE 		(BIT12)
#define ROM_PROTECT 		(BIT9)
#define SYS_PROTECT 		(BIT8)
#define BIG_ENDIAN_ENABLE 	(BIT7)
#define DCACHE_ENABLE 		(BIT2)
#define ALIGN_ENABLE 		(BIT1)
#define MMU_ENABLE  		(BIT0)

#define FAST_BUS_MODE   	(0)
#define SYNCH_BUS_MODE  	(BIT30)
#define RESERVED_BUS_MODE  	(BIT31)
#define ASYNCH_BUS_MODE 	(BIT31|BIT30)

void blink_led_test() __attribute__((section(".handler")));

#endif

