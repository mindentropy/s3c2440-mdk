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

#define ILLEGAL_ACCESS 	(BIT3)
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

#define set_tacls_twrph(TACLS,TWRPH1,TWRPH0) \
	(writereg32(NFCONF_REG(NAND_BA),(TACLS<<13) | (TWRPH1<<6) | (TWRPH0<<10)))


#define nand_set_spare_ecc_lock() \
	set_reg_params(NFCONT_REG(NAND_BA),SPARE_ECC_LOCK)

#define nand_clear_spare_ecc_lock() \
	clear_reg_params(NFCONT_REG(NAND_BA),SPARE_ECC_LOCK)

#define nand_set_main_ecc_lock() \
	set_reg_params(NFCONT_REG(NAND_BA),MAIN_ECC_LOCK)

#define nand_clear_main_ecc_lock() \
	clear_reg_params(NFCONT_REG(NAND_BA),MAIN_ECC_LOCK)

#define nand_init_ecc() \
	set_reg_params(NFCONT_REG(NAND_BA),INIT_ECC)

#define nand_deinit_ecc() \
	clear_reg_params(NFCONT_REG(NAND_BA),INIT_ECC)

//Chip select disable
#define set_nand_nfce_high() \
	set_reg_params(NFCONT_REG(NAND_BA),REG_nCE)

//Chip select enable
#define set_nand_nfce_low() \
	clear_reg_params(NFCONT_REG(NAND_BA),REG_nCE)

#define set_nand_flash_mode() \
	set_reg_params(NFCONT_REG(NAND_BA),MODE)

#define disable_nand_flash_mode() \
	clear_reg_params(NFCONT_REG(NAND_BA),MODE)

#define enable_nand_soft_lock() \
	set_reg_params(NFCONT_REG(NAND_BA),SOFTLOCK)

#define disable_nand_soft_lock() \
	clear_reg_params(NFCONT_REG(NAND_BA),SOFTLOCK)

#define enable_nand_flash_controller() do {\
		set_nand_flash_mode();\
		set_nand_nfce_low();\
	} while(0)


#define get_nCE_status() \
	(readreg32(NFSTAT_REG(NAND_BA)) & nCE_STATUS)

#define get_RnB_status() \
	(readreg32(NFSTAT_REG(NAND_BA)) & RnB_STATUS)

#define get_RnB_Transdetect_status() \
	(readreg32(NFSTAT_REG(NAND_BA)) & RnB_TRANSDETECT)

#define get_illegal_access_status() \
	(readreg32(NFSTAT_REG(NAND_BA)) & ILLEGAL_ACCESS)

#define send_nand_cmd(cmd) \
	(writereg16(NFCMMD_REG(NAND_BA),cmd))

#define send_nand_addr(addr) \
	(writereg8(NFADDR_REG(NAND_BA),addr))

#define send_nand_data(data) \
	(writereg32(NFDATA_REG(NAND_BA),data))

#define read_nand_data() \
	(readreg32(NFDATA_REG(NAND_BA)))

/**** NAND Commands ****/

#define CMD_READ_PAGE_START					0x00
#define CMD_READ_PAGE_END  					0x30
#define CMD_READ_PAGE_CACHE_SEQUENTIAL 		0x31
#define CMD_READ_PAGE_CACHE_SEQUENTIAL_LAST 0x3F
#define CMD_READ_FOR_INTERNAL_DATA_MOVE 	0x00
#define CMD_RANDOM_DATA_READ 				0x05
#define CMD_READ_ID 						0x90
#define CMD_READ_STATUS 					0x70
#define CMD_PROGRAM_PAGE 					0x80
#define CMD_PROGRAM_PAGE_CACHE 				0x80
#define CMD_PROGRAM_PAGE_CONFIRM 			0x10
#define CMD_PROGRAM_FOR_INTERNAL_DATA_MOVE  0x85
#define CMD_RANDOM_DATA_INPUT 				0x85
#define CMD_ERASE_BLOCK 					0x60
#define CMD_ERASE_CONFIRM 					0xD0
#define CMD_RESET 							0xFF

/************************/

#define NAND_DATA_SIZE (2048u)
#define NAND_SPARE_SIZE (64u)

#define NAND_PAGE_SIZE ((NAND_DATA_SIZE) + (NAND_SPARE_SIZE))


#define get_nand_page_offset(nand_addr) \
	((nand_addr) & (NAND_DATA_SIZE-1))

#define nand_reset() \
	send_nand_cmd(CMD_RESET)

struct nand_page_cache_info {
	int8_t cache_flag;
	uint8_t page_cache[NAND_DATA_SIZE];
	uint32_t addr_cache;
};

void nand_init();
int nand_page_program(uint32_t addr,const char data[],uint16_t len);
int nand_block_erase(uint32_t addr);

#endif
