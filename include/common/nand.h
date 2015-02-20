#ifndef NAND_H_

#define NAND_H_

#include "common.h"

#define NAND_BA 0x4E000000

//#define NFCONF 	0x4E000000
#define NFCONF_OFF 0x00
#define NFCONF_REG(BA) \
	HW_REG(BA,NFCONF_OFF)

#define TACLS 	(BIT13|BIT12)
#define TWRPH0  (BIT10|BIT9|BIT8)
#define TWRPH1  (BIT6|BIT5|BIT4)

#define ADVFLASH 	(BIT3)
#define PAGESIZE 	(BIT2)
#define ADDRCYCLE 	(BIT1)
#define BUSWIDTH 	(BIT0)

//#define NFCONT 	0x4E000004
#define NFCONT_OFF 	0x04
#define NFCONT_REG(BA) \
	HW_REG(BA,NFCONT_OFF)

#define LOCKTIGHT 			(BIT13)
#define SOFTLOCK 			(BIT12)
#define EN_ILLEGAL_ACC_INT 	(BIT10)
#define EN_RnB_INT 			(BIT9)
#define RnB_TRANSMODE 		(BIT8)
#define SPARE_ECC_LOCK 		(BIT6)
#define MAIN_ECC_LOCK 		(BIT5)
#define INIT_ECC 			(BIT4)
#define REG_nCE 			(BIT1)
#define MODE 				(BIT0)

//#define NFCMMD 			0x4E000008
#define NFCMMD_OFF 		0x08

#define NFCMMD_REG(BA) \
	HW_REG(BA,NFCMMD_OFF)

#define NFCMMD_MSK BYTE_MASK

//#define NFADDR 		0x4E00000C
#define NFADDR_OFF 	0x0C

#define NFADDR_REG(BA) \
	HW_REG(BA,NFADDR_OFF)

#define NFADDR_MSK BYTE_MASK

//#define NFDATA 		0x4E000010
#define NFDATA_OFF 	0x10

#define NFDATA_REG(BA) \
	HW_REG(BA,NFDATA_OFF)

#define NFDATA_MSK  WORD_MASK

/*
#define NFMECCD0 	0x4E000014
#define NFMECCD1 	0x4E000018
#define NFSECCD 	0x4E00001C
*/

#define NFMECCD0_OFF 0x14
#define NFMECCD1_OFF 0x18
#define NFSECCD_OFF	 0x1C

#define NFMECCD0_REG(BA) \
	HW_REG(BA,NFMECCD0_OFF)

#define NFMECCD1_REG(BA) \
	HW_REG(BA,NFMECCD1_OFF)

#define NFSECCD_REG(BA) \
	HW_REG(BA,NFSECCD_OFF)

#define ECCDATA1_1 (BYTE_MASK<<24)
#define ECCDATA1_0 (BYTE_MASK<<16)

#define ECCDATA0_1 (BYTE_MASK<<8)
#define ECCDATA0_0 (BYTE_MASK)

#define ECCDATA3_1 (BYTE_MASK<<24)
#define ECCDATA3_0 (BYTE_MASK<<16)

#define ECCDATA2_1 (BYTE_MASK<<8)
#define ECCDATA2_0 (BYTE_MASK)

//#define NFSTAT 			0x4E000020
#define NFSTAT_OFF 		0x20
#define NFSTAT_REG(BA) \
	HW_REG(BA,NFSTAT_OFF)

#define ILLEGAL_ACC 	(BIT3)
#define RnB_TRANSDETECT (BIT2)
#define nCE_STATUS		(BIT1)
#define RnB_STATUS		(BIT0)

/*
#define NFESTAT0 	0x4E000024
#define NFESTAT1 	0x4E000028
*/

#define NFESTAT0_OFF 	0x24
#define NFESTAT1_OFF 	0x28

#define NFESTAT0_REG(BA) \
	HW_REG(BA,NFESTAT0_OFF)

#define NFESTAT1_REG(BA) \
	HW_REG(BA,NFESTAT1_OFF)

#define SErrorDataNo 	(BIT24|BIT23|BIT22|BIT21)
#define SErrorBitNo 	(BIT20|BIT19|BIT18)
#define MErrorDataNo 	(BIT17|BIT16|BIT15|BIT14|BIT13|BIT12|BIT11|BIT10|BIT9|BIT8|BIT7)
#define MErrorBitNo 	(BIT6|BIT5|BIT4)
#define SpareError 		(BIT3|BIT2)
#define MainError 		(BIT1|BIT0)

/*
#define NFMECC0 	0x4E00002C
#define NFMECC1 	0x4E000030
*/

#define NFMECC0_OFF	0x2C
#define NFMECC1_OFF	0x30

#define NFMECC0_REG(BA) \
	HW_REG(BA,NFMECC0_OFF)

#define NFMECC1_REG(BA) \
	HW_REG(BA,NFMECC1_OFF)

#define MECC0_3 	(BYTE_MASK<<24)
#define MECC0_2 	(BYTE_MASK<<16)
#define MECC0_1 	(BYTE_MASK<<8)
#define MECC0_0 	(BYTE_MASK)

#define MECC1_3 	(BYTE_MASK<<24)
#define MECC1_2 	(BYTE_MASK<<16)
#define MECC1_1 	(BYTE_MASK<<8)
#define MECC1_0 	(BYTE_MASK)

//#define NFSECC 		0x4E000034
#define NFSECC_OFF 	0x34

#define NFSECC_REG(BA) \
	HW_REG(BA,NFSECC_OFF)


#define SECC1_1 	(BYTE_MASK<<24)
#define SECC1_0 	(BYTE_MASK<<16)
#define SECC0_1 	(BYTE_MASK<<8)
#define SECC0_0 	(BYTE_MASK)

/*
#define NFSBLK      0x4E000038
#define NFEBLK      0x4E00003C
*/

#define NFSBLK_OFF  0x38
#define NFEBLK_OFF  0x3C

#define NFSBLK_REG(BA) \
	HW_REG(BA,NFSBLK_OFF)

#define NFEBLK_REG(BA) \
	HW_REG(BA,NFEBLK_OFF)

#define SBLK_ADDR2  (BYTE_MASK<<16)
#define SBLK_ADDR1  (BYTE_MASK<<8)
#define SBLK_ADDR0  (BYTE_MASK)

#define EBLK_ADDR2  (BYTE_MASK<<16)
#define EBLK_ADDR1  (BYTE_MASK<<8)
#define EBLK_ADDR0  (BYTE_MASK)


/** NAND GPIO configuration pins **/

#define NAND_MEM_PG_CAP_SEL_PIN 	(BIT13)
#define NAND_MEM_ADDR_CYCL_SEL_PIN 	(BIT14)
#define NAND_MEM_BUS_WIDTH_SEL_PIN 	(BIT15)

#define NAND_GPG13_INPUT ((BIT27|BIT26)) //GPG13
#define NAND_GPG14_INPUT ((BIT29|BIT28)) //GPG14
#define NAND_GPG15_INPUT ((BIT31|BIT30)) //GPG15

#define get_nand_flash_mem_bus_width_status() \
	((readreg32(GPDAT_REG(GPG_BA))) & NAND_MEM_BUS_WIDTH_SEL_PIN)
	
#define get_nand_flash_mem_addr_cycle_status() \
	((readreg32(GPDAT_REG(GPG_BA))) & NAND_MEM_ADDR_CYCL_SEL_PIN)

#define get_nand_flash_mem_page_cap_status() \
	((readreg32(GPDAT_REG(GPG_BA))) & NAND_MEM_PG_CAP_SEL_PIN)


	
void nand_init();

#endif
