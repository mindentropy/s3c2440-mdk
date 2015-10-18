#ifndef SD_MMC_H_

#define SD_MMC_H_

#include "common.h"

#define SD_MMC_BA 		(0x5A000000U)

#define SDICON_OFF 		(0x00)
#define SDICON_REG(BA) \
	HW_REG(BA,SDICON_OFF)

#define SDMMC_RESET 	(BIT8)
#define CLK_TYPE_MSK	(BIT5)
#define CLK_TYPE_MMC	(BIT5)
#define BYTE_ORDER_A 	~(BIT4)
#define BYTE_ORDER_B 	(BIT4)
#define RCV_IO_INT 		(BIT3)
#define READ_WAIT_EN	(BIT2)
#define CLK_OUT_EN 		(BIT0)

#define reset_sdmmc(BA) \
	set_reg_params(SDICON_REG(BA),SDMMC_RESET)

#define set_clk_out_en(BA) \
	set_reg_params(SDICON_REG(SD_MMC_BA),CLK_OUT_EN)
	

#define SDIPRE_OFF 		(0x04)
#define SDIPRE_REG(BA) \
	HW_REG(BA,SDIPRE_OFF)

#define PRESCALER_MASK (BYTE_MASK)

#define set_sd_clk_prescale(BA,prescaler_value)	\
	set_reg_params(SDIPRE_REG(BA),prescaler_value)

#define SDI_CMD_ARG_OFF	(0x08)
#define SDI_CMD_ARG_REG(BA) \
	HW_REG(BA,SDI_CMD_ARG_OFF)


#define set_sd_mmc_cmd_arg(BA,arg) \
	writereg32(SDI_CMD_ARG_REG(BA),arg)


#define CMD_ARG_MASK  (WORD_MASK)

#define SDI_CMD_CON_OFF	(0x0C)
#define SDI_CMD_CON_REG(BA) \
	HW_REG(BA,SDI_CMD_CON_OFF)

#define ABORT_CMD 			(BIT12)
#define CMD_WITH_DATA 		(BIT11)
#define LONG_RSP 			(BIT10)
#define WAIT_RSP 			(BIT9)
#define CMD_START       	(BIT8)
#define CMD_TRANSMISSION 	(BIT6)
#define CMD_INDEX_MASK 		set_bit_range(5,0)

#define set_sd_mmc_cmd_con(BA,cmd_con_options) \
	writereg32(SDI_CMD_CON_REG(BA),cmd_con_options)


#define SDI_CMD_STATUS_OFF 	(0x10)
#define SDI_CMD_STATUS_REG(BA) \
	HW_REG(BA,SDI_CMD_STATUS_OFF)

#define RSP_CRC 		(BIT12)
#define CMD_SENT 		(BIT11)
#define CMD_TIMEOUT 	(BIT10)
#define RESP_RECV_END 	(BIT9)
#define CMD_PROGRESS_ON (BIT8)


#define RSP_INDEX_MASK  (BYTE_MASK)

#define ack_cmd_sent(BA) \
	do {\
		set_reg_params(SDI_CMD_STATUS_REG(BA),CMD_SENT); \
		while(readreg32(SDI_CMD_STATUS_REG(BA)) & CMD_SENT); \
	} while(0)
	


#define chk_cmd_resp(BA) \
	(readreg32(SDI_CMD_STATUS_REG(BA)) & CMD_TIMEOUT)

#define ack_cmd_resp(BA) \
	set_reg_params(SDI_CMD_STATUS_REG(BA),RESP_RECV_END)

#define get_cmd_progress_status(BA) \
	((readreg32(SDI_CMD_STATUS_REG(BA))) & CMD_PROGRESS_ON)

#define get_cmd_sent_status(BA) \
	((readreg32(SDI_CMD_STATUS_REG(BA))) & CMD_SENT)

#define SDIRSP0_OFF 	(0x14)
#define SDIRSP0_REG(BA) \
	HW_REG(BA,SDIRSP0_OFF)

#define SDIRSP0_MASK 	(WORD_MASK)

#define SDIRSP1_OFF 	(0x18)
#define SDIRSP1_REG(BA) \
	HW_REG(BA,SDIRSP1_OFF)

#define RCRC7_MASK 		((0xFF)<<(24))
#define RESPONSE1_MASK 	(0xFFFFFF)

#define SDIRSP2_OFF 	(0x1C)
#define SDIRSP2_REG(BA) \
	HW_REG(BA,SDIRSP2_OFF)

#define RESPONSE2_MASK 	(WORD_MASK)

#define SDIRSP3_OFF 	(0x20)
#define SDIRSP3_REG(BA) \
	HW_REG(BA,SDIRSP3_OFF)

#define RESPONSE3_MASK 	(WORD_MASK)

#define SDID_TIMER_OFF 	(0x24)
#define SDID_TIMER_REG(BA) \
	HW_REG(BA,SDID_TIMER_OFF)


#define set_data_timeout_period(BA,timeout_period) \
	writereg32(SDID_TIMER_REG(BA),timeout_period)
	

#define DATA_TIMER_MASK (0xFFFFFFU)

#define SDIB_SIZE_OFF 	(0x28)
#define SDIB_SIZE_REG(BA) \
	HW_REG(BA,SDIB_SIZE_OFF)

#define BLK_SIZE_MASK (0xFFFU)

#define set_sdi_block_size(BA,block_size) 	\
	writereg32(SDIB_SIZE_REG(BA),((block_size) & (BLK_SIZE_MASK)) )

#define SDID_DATA_CON_OFF 	(0x2C)
#define SDID_DATA_CON_REG(BA) \
	HW_REG(BA,SDID_DATA_CON_OFF)

#define BURST4_EN 				(BIT24)

#define DATA_SIZE_MASK 			(BIT23|BIT22)
#define DATA_SIZE_BYTE_TRANSFER 0x00
#define DATA_SIZE_HW_TRANSFER 	(BIT22)
#define DATA_SIZE_WORD_TRANSFER (BIT23)
#define DATA_SIZE_RESERVED 		(BIT23|BIT22)

#define SDI_PRD_TYPE 			(BIT21)
#define TRANSMIT_AFTER_RESPONSE (BIT20)
#define RECEIVE_AFTER_CMD  		(BIT19)
#define BUSY_AFTER_CMD  		(BIT18)
#define BLOCK_MODE 				(BIT17)
#define WIDE_BUS_EN 			(BIT16)
#define DMA_EN 					(BIT15)
#define DATA_TRANSFER_START 	(BIT14)

#define DATA_TRANS_MODE_MASK 		(BIT13|BIT12)
#define DATA_NO_OPERATION 			(0)
#define DATA_ONLY_BUSY_CHECK_MODE 	(BIT12)
#define DATA_RECEIVE_MODE 			(BIT13)
#define DATA_TRANSMIT_MODE 			(BIT13|BIT12)

#define BLK_NUM_MASK 			(0xFFF)

#define SDI_DAT_CNT_OFF 		(0x30)
#define SDI_DAT_CNT_REG(BA) \
	HW_REG(BA,SDI_DAT_CNT_OFF)

#define BLK_NUM_CNT 			(0xFFF000)
#define BLK_CNT 				(0xFFF)

#define SDI_DATA_STATUS_OFF 	(0x34)
#define SDI_DATA_STATUS_REG(BA) \
	HW_REG(BA,SDI_DATA_STATUS_OFF)

#define NO_BUSY 				(BIT11)
#define READ_WAIT_REQ 			(BIT10)
#define SDIO_INT_DETECT 		(BIT9)
#define CRC_STATUS 				(BIT7)
#define DATA_RCV_CRC_FAIL 		(BIT6)
#define DATA_TIMEOUT 			(BIT5)
#define DATA_TRANSFER_FINISH 	(BIT4)
#define BUSY_FINISH 			(BIT3)
#define Tx_DATA_PROGRESS_ON 	(BIT1)
#define Rx_DATA_PROGRESS_ON 	(BIT0)


#define SDIFSTA_OFF 			(0x38)
#define SDIFSTA_REG(BA) \
	HW_REG(BA,SDIFSTA_OFF)

#define FIFO_RESET 					(BIT16)
#define FIFO_FAIL_ERR_MASK 			(BIT15|BIT14)
#define FIFO_FAIL_NOT_DETECT    	(0)
#define FIFO_FAIL 					(BIT14)
#define FIFO_FAIL_IN_LAST_TRANSFER 	(BIT15)
#define FIFO_FAIL_TFDET 			(BIT13)
#define FIFO_FAIL_RFDET 			(BIT12)
#define SD_Tx_FIFO_HALF_FULL 		(BIT11)
#define SD_Tx_FIFO_EMPTY 			(BIT10)
#define SD_Rx_FIFO_LAST_DATA_READY	(BIT9)
#define SD_Rx_FIFO_FULL 			(BIT8)
#define SD_Rx_FIFO_HALF_FULL		(BIT7)
#define FFCNT_MASK					(BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)

#define reset_fifo(BA) \
	set_reg_params(SDIFSTA_REG(BA),FIFO_RESET)
	

#define SDI_INT_MASK_OFF 			(0x3C)
#define SDI_INT_MASK_REG(BA) \
	HW_REG(BA,SDI_INT_MASK_OFF)

#define NO_BUSY_INT 				(BIT18)
#define RSP_CRC_INT_EN 				(BIT17)
#define CMD_SENT_INT_EN 			(BIT16)
#define CMD_TIMEOUT_INT_EN 			(BIT15)
#define RSP_END_INT_EN 				(BIT14)
#define RWAIT_REQ_INT_EN 			(BIT13)
#define IO_INT_DET_INT_EN 			(BIT12)
#define FF_FAIL_INT_EN 				(BIT11)
#define CRC_STATUS_INT_EN 			(BIT10)
#define DATA_CRC_INT_EN 			(BIT9)
#define DATA_TIMEOUT_INT_EN 		(BIT8)
#define DATA_FIN_INT_EN 			(BIT7)
#define BUSY_FIN_INT_EN 			(BIT6)
#define TF_HALF_INT_EN 				(BIT4)
#define TF_EMPTY_INT_EN 			(BIT3)
#define RF_LAST_INT_EN 				(BIT2)
#define RF_FULL_INT_EN 				(BIT1)
#define RF_HALF_INT_EN 				(BIT0)

#define SDI_DATA_LI_W_OFF 				(0x40)
#define SDI_DATA_LI_W_REG(BA) \
	HW_REG(BA,SDI_DATA_LI_W_OFF)

#define SDI_DATA_LI_HW_OFF 				(0x44)
#define SDI_DATA_LI_HW_REG(BA) \
	HW_REG(BA,SDI_DATA_LI_HW_OFF)

#define SDI_DATA_LI_B_OFF 				(0x48)
#define SDI_DATA_LI_B_REG(BA) \
	HW_REG(BA,SDI_DATA_LI_B_OFF)

#define SDI_DATA_BI_W_OFF 				(0x4C)
#define SDI_DATA_BI_W_REG(BA) \
	HW_REG(BA,SDI_DATA_BI_W_OFF)


#define SDI_DATA_BI_HW_OFF 				(0x41)
#define SDI_DATA_BI_HW_REG(BA) \
	HW_REG(BA,SDI_DATA_BI_HW_OFF)

#define SDI_DATA_BI_B_OFF 				(0x43)
#define SDI_DATA_BI_B_REG(BA) \
	HW_REG(BA,SDI_DATA_BI_B_OFF)

#define R1_CARD_STATUS_MASK 		(0xFFFFFFFF)


#define R3_CARD_BUSY 						(1<<31)
#define R3_CARD_CAPACITY_STATUS_SDHC_SDXC 	(1<<30)
#define R3_UHS_2_CARD 						(1<<29)
#define R3_READY_FOR_SWITCHING 				(1<<24)

#define R7_RSP_CHK_PATTERN_MASK 	(0xFF)
#define R7_RSP_VOLT_ACCEPTED_MASK 	((0xF)<<8)
#define R7_RSP_RESERVED_BITS_MASK 	((0xFFFFF)<<12)

#define R2_RSP0_MID_MASK 			(0xFFU<<24)
#define R2_RSP0_OID_MASK  			(0xFFFFU<<8)
#define R2_RSP0_PNM_MASK_P1  		(0xFFU)
#define R2_RSP1_PNM_MASK_P2  		(0xFFFFFFFFU)
#define R2_RSP2_PRV_MASK 			(0xFFU<<24)
#define R2_RSP2_PSN_MASK_P1 		(0xFFFFFFU)
#define R2_RSP3_PSN_MASK_P2  		(0xFFU<<24)
#define R2_RSP3_MDT_MASK     		(0xFFFU<<8)
#define R2_RSP3_CRC_MASK 			(0x7FFU<<1)
#define R2_RSP3_UNUSED_MASK  		(0x1U)

#define get_R2_rsp_CID_MID(BA) \
	(((readreg32(SDIRSP0_REG(BA))) & R2_RSP0_MID_MASK) >> 24)
	
#define get_R2_rsp_CID_OID(BA) \
	(((readreg32(SDIRSP0_REG(BA))) & R2_RSP0_OID_MASK) >> 8)

#define get_R2_rsp_CID_PNM_P1(BA) \
	((readreg32(SDIRSP0_REG(BA))) & R2_RSP0_PNM_MASK_P1)

#define get_R2_rsp_CID_PNM_P2_pos(BA,pos) \
	((((readreg32(SDIRSP1_REG(BA))) & R2_RSP1_PNM_MASK_P2) \
		& (0xFF << pos)) >> pos)

#define get_R2_rsp_CID_PRV(BA) \
	(((readreg32(SDIRSP2_REG(BA))) & R2_RSP2_PRV_MASK) >> 24)
	
#define get_R2_rsp_CID_PSN(BA) \
	((((readreg32(SDIRSP2_REG(BA))) & R2_RSP2_PSN_MASK_P1) << 8) \
		| (((readreg32(SDIRSP3_REG(BA))) & R2_RSP3_PSN_MASK_P2) >> 24))

#define get_R2_rsp_CID_MDT(BA) \
	(((readreg32(SDIRSP3_REG(BA))) & R2_RSP3_MDT_MASK) >> 8)

#define get_R2_rsp_CID_CRC(BA) \
	(((readreg32(SDIRSP3_REG(BA))) & R2_RSP3_CRC_MASK) >> 1)

#define R2_RSP0_STRUCT_MASK  				(0x3U<<30)
#define R2_RSP0_TAAC_MASK 					(0xFFU<<16)
#define R2_RSP0_NSAC_MASK 					(0xFFU<<8)
#define R2_RSP0_TRAN_MASK 					(0xFFU)

#define get_R2_rsp_CSD_STRUCT(BA) \
	((readreg32(SDIRSP0_REG(BA)) & (R2_RSP0_STRUCT_MASK)) >> 30)

#define get_R2_rsp_CSD_TAAC(BA) \
	((readreg32(SDIRSP0_REG(BA)) & (R2_RSP0_TAAC_MASK)) >> 16)

#define get_R2_rsp_CSD_NSAC(BA) \
	((readreg32(SDIRSP0_REG(BA)) & (R2_RSP0_NSAC_MASK)) >> 8)

#define get_R2_rsp_CSD_TRAN(BA) \
	(readreg32(SDIRSP0_REG(BA)) & (R2_RSP0_TRAN_MASK))

#define get_R2_rsp_var_CSD_STRUCT(rsp0) \
	(((rsp0) & (R2_RSP0_STRUCT_MASK)) >> 30)

#define get_R2_rsp_var_CSD_TAAC(rsp0) \
	(((rsp0) & (R2_RSP0_TAAC_MASK)) >> 16)

#define get_R2_rsp_var_CSD_NSAC(rsp0) \
	(((rsp0) & (R2_RSP0_NSAC_MASK)) >> 8)

#define get_R2_rsp_var_CSD_TRAN(rsp0) \
	((rsp0) & (R2_RSP0_TRAN_MASK))


/*** Ver 2.0 ***/

#define R2_RSP1_CCC_MASK 	 				(0xFFFU<<20)
#define R2_RSP1_READ_BLK_LEN_MASK 			(0xFU<<16)
#define R2_RSP1_READ_BLK_PARTIAL_MASK 		(0x1U<<15)
#define R2_RSP1_WRITE_BLK_MISALIGN_MASK 	(0x1U<<14)
#define R2_RSP1_READ_BLK_MISALIGN_MASK 		(0x1U<<13)
#define R2_RSP1_DSR_IMP_MASK 				(0x1U<<12)
/* Reserved 2 bits */

#define get_R2_rsp_CSD_CCC(BA) \
	((readreg32(SDIRSP1_REG(BA)) & (R2_RSP1_CCC_MASK)) >> 20)

#define get_R2_rsp_CSD_READ_BLK_LEN(BA) \
	((readreg32(SDIRSP1_REG(BA)) & (R2_RSP1_READ_BLK_LEN_MASK)) >> 16)

#define get_R2_rsp_CSD_READ_BLK_PARTIAL(BA) \
	((readreg32(SDIRSP1_REG(BA)) & (R2_RSP1_READ_BLK_PARTIAL_MASK)) >> 15)

#define get_R2_rsp_CSD_WRITE_BLK_MISALIGN(BA) \
	((readreg32(SDIRSP1_REG(BA)) & (R2_RSP1_WRITE_BLK_MISALIGN_MASK)) >> 14)

#define get_R2_rsp_CSD_READ_BLK_MISALIGN(BA) \
	((readreg32(SDIRSP1_REG(BA)) & (R2_RSP1_READ_BLK_MISALIGN_MASK)) >> 13)

#define get_R2_rsp_CSD_DSR_IMP(BA) \
	((readreg32(SDIRSP1_REG(BA)) & (R2_RSP1_DSR_IMP_MASK)) >> 12)

#define get_R2_rsp_var_CSD_CCC(rsp1) \
	(((rsp1) & (R2_RSP1_CCC_MASK)) >> 20)

#define get_R2_rsp_var_CSD_READ_BLK_LEN(rsp1) \
	(((rsp1) & (R2_RSP1_READ_BLK_LEN_MASK)) >> 16)

#define get_R2_rsp_var_CSD_READ_BLK_PARTIAL(rsp1) \
	(((rsp1) & (R2_RSP1_READ_BLK_PARTIAL_MASK)) >> 15)

#define get_R2_rsp_var_CSD_WRITE_BLK_MISALIGN(rsp1) \
	(((rsp1) & (R2_RSP1_WRITE_BLK_MISALIGN_MASK)) >> 14)

#define get_R2_rsp_var_CSD_READ_BLK_MISALIGN(rsp1) \
	(((rsp1) & (R2_RSP1_READ_BLK_MISALIGN_MASK)) >> 13)

#define get_R2_rsp_var_CSD_DSR_IMP(rsp1) \
	(((rsp1) & (R2_RSP1_DSR_IMP_MASK)) >> 12)

/* 6 bits reserved */
#define R2_RSP1_C_SIZE 						(0x3FU)
#define R2_RSP2_C_SIZE 						(0xFFFF<<16)

#define get_R2_rsp_CSD_C_SIZE(BA) \
	(((readreg32(SDIRSP1_REG(BA)) & (R2_RSP1_C_SIZE)) << 16) | \
		((readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_C_SIZE))>>16))

#define get_R2_rsp_var_CSD_C_SIZE(rsp1,rsp2) \
	((((rsp1) & (R2_RSP1_C_SIZE)) << 16) | \
		(((rsp2) & (R2_RSP2_C_SIZE))>>16))

/* 1 bit reserved */

/*#define R2_RSP2_VDD_R_CURR_MIN_MASK 		(0x7U<<27)
#define R2_RSP2_VDD_R_CURR_MAX_MASK 		(0x7U<<24)
#define R2_RSP2_VDD_W_CURR_MIN_MASK 		(0x7U<<21)
#define R2_RSP2_VDD_W_CURR_MAX_MASK 		(0x7U<<18)
#define R2_RSP2_C_SIZE_MULT_MASK 			(0x7U<<15)*/

#define R2_RSP2_ERASE_BLK_EN_MASK 			(0x1U<<14)
#define R2_RSP2_SECTOR_SIZE_MASK 			(0x7FU<<7)
#define R2_RSP2_WP_GRP_SIZE_MASK 			(0x7FU)

/*
#define get_R2_rsp_CSD_VDD_R_CURR_MIN(BA) \
	((readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_VDD_R_CURR_MIN_MASK)) >> 27)
	
#define get_R2_rsp_CSD_VDD_R_CURR_MAX(BA) \
	((readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_VDD_R_CURR_MAX_MASK)) >> 24)

#define get_R2_rsp_CSD_VDD_W_CURR_MIN(BA) \
	((readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_VDD_W_CURR_MIN_MASK)) >> 21)

#define get_R2_rsp_CSD_VDD_W_CURR_MAX(BA) \
	((readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_VDD_W_CURR_MAX_MASK)) >> 18)

#define get_R2_rsp_CSD_C_SIZE_MULT(BA) \
	((readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_C_SIZE_MULT_MASK)) >> 15)
*/

#define get_R2_rsp_CSD_ERASE_BLK_EN(BA) \
	((readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_ERASE_BLK_EN_MASK)) >> 14)

#define get_R2_rsp_CSD_SECTOR_SIZE(BA) \
	((readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_SECTOR_SIZE_MASK)) >> 7)

#define get_R2_rsp_CSD_WP_GRP_SIZE(BA) \
	(readreg32(SDIRSP2_REG(BA)) & (R2_RSP2_WP_GRP_SIZE_MASK))

#define get_R2_rsp_var_CSD_ERASE_BLK_EN(rsp2) \
	(((rsp2) & (R2_RSP2_ERASE_BLK_EN_MASK)) >> 14)

#define get_R2_rsp_var_CSD_SECTOR_SIZE(rsp2) \
	(((rsp2) & (R2_RSP2_SECTOR_SIZE_MASK)) >> 7)

#define get_R2_rsp_var_CSD_WP_GRP_SIZE(rsp2) \
	((rsp2) & (R2_RSP2_WP_GRP_SIZE_MASK))

#define R2_RSP3_WP_GRP_ENABLE_MASK 				(0x1U<<31)
/* Reserverd 2 bits */
#define R2_RSP3_R2W_FACTOR_MASK 				(0x7U<<26)
#define R2_RSP3_WRITE_BL_LEN_MASK 				(0xFU<<22)
#define R2_RSP3_WRITE_BL_PARTIAL_MASK 			(0x1U<<21)
/* Reserved 5 bits */
#define R2_RSP3_FILE_FORMAT_GRP_MASK 			(0x1U<<15)
#define R2_RSP3_COPY_MASK 						(0x1U<<14)
#define R2_RSP3_PERM_WRITE_PROTECT_MASK 		(0x1U<<13)
#define R2_RSP3_TMP_WRITE_PROTECT_MASK 			(0x1U<<12)
#define R2_RSP3_FILE_FORMAT_MASK 				(0x3U<<10)
/* Reserved 2 bits */
/* 7 bit CRC mask. Reuse above MACRO */

#define get_R2_rsp_CSD_WP_GRP_ENABLE(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_WP_GRP_ENABLE_MASK)) >> 31)

#define get_R2_rsp_CSD_R2W_FACTOR(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_R2W_FACTOR_MASK)) >> 26)

#define get_R2_rsp_CSD_WRITE_BL_LEN(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_WRITE_BL_LEN_MASK)) >> 22)

#define get_R2_rsp_CSD_WRITE_BL_PARTIAL(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_WRITE_BL_PARTIAL_MASK)) >> 21)

#define get_R2_rsp_CSD_FILE_FORMAT_GRP(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_FILE_FORMAT_GRP_MASK)) >> 15)

#define get_R2_rsp_CSD_COPY(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_COPY_MASK)) >> 14)

#define get_R2_rsp_CSD_PERM_WRITE_PROTECT(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_PERM_WRITE_PROTECT_MASK)) >> 13)

#define get_R2_rsp_CSD_TMP_WRITE_PROTECT(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_TMP_WRITE_PROTECT_MASK)) >> 12)

#define get_R2_rsp_CSD_FILE_FORMAT(BA) \
	((readreg32(SDIRSP3_REG(BA)) & (R2_RSP3_FILE_FORMAT_MASK)) >> 10)

#define get_R2_rsp_var_CSD_WP_GRP_ENABLE(rsp3) \
	(((rsp3) & (R2_RSP3_WP_GRP_ENABLE_MASK)) >> 31)

#define get_R2_rsp_var_CSD_R2W_FACTOR(rsp3) \
	(((rsp3) & (R2_RSP3_R2W_FACTOR_MASK)) >> 26)

#define get_R2_rsp_var_CSD_WRITE_BL_LEN(rsp3) \
	(((rsp3) & (R2_RSP3_WRITE_BL_LEN_MASK)) >> 22)

#define get_R2_rsp_var_CSD_WRITE_BL_PARTIAL(rsp3) \
	(((rsp3) & (R2_RSP3_WRITE_BL_PARTIAL_MASK)) >> 21)

#define get_R2_rsp_var_CSD_FILE_FORMAT_GRP(rsp3) \
	(((rsp3) & (R2_RSP3_FILE_FORMAT_GRP_MASK)) >> 15)

#define get_R2_rsp_var_CSD_COPY(rsp3) \
	(((rsp3) & (R2_RSP3_COPY_MASK)) >> 14)

#define get_R2_rsp_var_CSD_PERM_WRITE_PROTECT(rsp3) \
	(((rsp3) & (R2_RSP3_PERM_WRITE_PROTECT_MASK)) >> 13)

#define get_R2_rsp_var_CSD_TMP_WRITE_PROTECT(rsp3) \
	(((rsp3) & (R2_RSP3_TMP_WRITE_PROTECT_MASK)) >> 12)

#define get_R2_rsp_var_CSD_FILE_FORMAT(rsp3) \
	(((rsp3) & (R2_RSP3_FILE_FORMAT_MASK)) >> 10)

#define R6_RSP_RCA_MASK 				(0xFFFF0000U)
#define R6_RSP_CARD_STATUS_MASK 		(0xFFFFU)

#define get_R7_rsp_chk_pattern(BA) \
	(readreg32(SDIRSP0_REG(BA)) & (R7_RSP_CHK_PATTERN_MASK))

#define get_R7_rsp_volt_accepted(BA) \
	(readreg32(SDIRSP0_REG(BA)) & (R7_RSP_VOLT_ACCEPTED_MASK))

#define get_R1_rsp_card_status(BA) \
	(readreg32(SDIRSP0_REG(BA)) & (R1_CARD_STATUS_MASK))

#define get_R3_rsp_busy_status(BA) \
	(readreg32(SDIRSP0_REG(BA)) & (R3_CARD_BUSY))

#define get_R3_rsp_card_capacity_status(BA) \
	(readreg32(SDIRSP0_REG(BA)) & (R3_CARD_CAPACITY_STATUS_SDHC_SDXC))

#define get_R3_rsp_card_ready_for_switching(BA) \
	(readreg32(SDIRSP0_REG(BA)) & (R3_READY_FOR_SWITCHING))
	

#define get_R3_rsp_uhs_2_card_status(BA) \
	(readreg32(SDIRSP0_REG(BA)) & (R3_UHS_2_CARD))


#define get_R6_rsp_RCA(BA) \
	(((readreg32(SDIRSP0_REG(BA))) & R6_RSP_RCA_MASK) >> 16)

#define get_R6_rsp_RAW(BA) \
	((readreg32(SDIRSP0_REG(BA))) & R6_RSP_RCA_MASK)

#define get_R6_rsp_CARD_STATUS(BA) \
	(((readreg32(SDIRSP0_REG(BA)))  &  R6_RSP_CARD_STATUS_MASK))

	
struct cid_info {
	uint8_t MID;
	uint16_t CID;
	char PNM[6];
	uint8_t PRV;
	uint32_t PSN;
	uint16_t MDT;
	uint8_t CRC;
};

struct csd_info {
	uint32_t rsp0;
	uint32_t rsp1;
	uint32_t rsp2;
	uint32_t rsp3;
};

struct sd_card_info {
	struct cid_info cid_info;
	//struct csd_info csd_info;
	struct csd_info csd_info;
	uint32_t RCA;

	/* Below variable status can be a bitmap */
	uint8_t is_high_capacity;
	uint8_t is_ready_for_switching;
};

void init_sd_controller();
uint32_t get_cmd13_current_state(uint32_t BA,uint32_t RCA);



#endif
