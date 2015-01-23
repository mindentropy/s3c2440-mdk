#ifndef NAND_H_

#define NAND_H_

#define NFCONF 	0x4E000000

#define TACLS 	(BIT13|BIT12)
#define TWRPH0  (BIT10|BIT9|BIT8)
#define TWRPH1  (BIT6|BIT5|BIT4)

#define ADVFLASH 	(BIT3)
#define PAGESIZE 	(BIT2)
#define ADDRCYCLE 	(BIT1)
#define BUSWIDTH 	(BIT0)

#define NFCONT 	0x4E000004

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

#define NFCMMD 		0x4E000008

#define NFCMMD_MSK BYTE_MASK

#define NFADDR 		0x4E00000C
#define NFADDR_MSK BYTE_MASK

#define NFDATA 		0x4E000010
#define NFDATA_MSK  WORD_MASK

#define NFMECCD0 	0x4E000014
#define NFMECCD1 	0x4E000018

#define NFSECCD 	0x4E00001C

#define ECCDATA1_1 (BYTE_MASK<<24)
#define ECCDATA1_0 (BYTE_MASK<<16)

#define ECCDATA0_1 (BYTE_MASK<<8)
#define ECCDATA0_0 (BYTE_MASK)

#define ECCDATA3_1 (BYTE_MASK<<24)
#define ECCDATA3_0 (BYTE_MASK<<16)

#define ECCDATA2_1 (BYTE_MASK<<8)
#define ECCDATA2_0 (BYTE_MASK)

#define NFSTAT 		0x4E000020

#define ILLEGAL_ACC 	(BIT3)
#define RnB_TRANSDETECT (BIT2)
#define nCE 			(BIT1)
#define RnB 			(BIT0)

#define NFESTAT0 	0x4E000024
#define NFESTAT1 	0x4E000028

#define SErrorDataNo 	(BIT24|BIT23|BIT22|BIT21)
#define SErrorBitNo 	(BIT20|BIT19|BIT18)
#define MErrorDataNo 	(BIT17|BIT16|BIT15|BIT14|BIT13|BIT12|BIT11|BIT10|BIT9|BIT8|BIT7)
#define MErrorBitNo 	(BIT6|BIT5|BIT4)
#define SpareError 		(BIT3|BIT2)
#define MainError 		(BIT1|BIT0)

#define NFMECC0 	0x4E00002C
#define NFMECC1 	0x4E000030

#define MECC0_3 	(BYTE_MASK<<24)
#define MECC0_2 	(BYTE_MASK<<16)
#define MECC0_1 	(BYTE_MASK<<8)
#define MECC0_0 	(BYTE_MASK)

#define MECC1_3 	(BYTE_MASK<<24)
#define MECC1_2 	(BYTE_MASK<<16)
#define MECC1_1 	(BYTE_MASK<<8)
#define MECC1_0 	(BYTE_MASK)

#define NFSECC 		0x4E000034


#define SECC1_1 	(BYTE_MASK<<24)
#define SECC1_0 	(BYTE_MASK<<16)
#define SECC0_1 	(BYTE_MASK<<8)
#define SECC0_0 	(BYTE_MASK)

#define NFSBLK      0x4E000038
#define NFEBLK      0x4E00003C

#define SBLK_ADDR2  (BYTE_MASK<<16)
#define SBLK_ADDR1  (BYTE_MASK<<8)
#define SBLK_ADDR0  (BYTE_MASK)

#define EBLK_ADDR2  (BYTE_MASK<<16)
#define EBLK_ADDR1  (BYTE_MASK<<8)
#define EBLK_ADDR0  (BYTE_MASK)

#endif
