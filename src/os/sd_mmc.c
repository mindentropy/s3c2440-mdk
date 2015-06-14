#include "sd_mmc.h"
#include "uart_util.h"
#include "gpio_def.h"

/************ CMD_INDEX *****************/

#define CMD0 	0
#define CMD2 	2
#define CMD3 	3
#define CMD7 	7
#define CMD8    8
#define CMD9 	9
#define CMD55 	55
#define ACMD41 	41



#define SD_CARD_VOLTAGE_2_7  			(1<<8)
#define SD_CARD_VOLTAGE_LOW_VOLTAGE  	(2<<8)
#define SD_CHECK_PATTERN 				(0xAA)

#define SD_HCS_SDSC 					~(1<<30)
#define SD_HCS_SDHC_SDXC 				(1<<30)
#define SD_MAX_PERFORMANCE 		 		(1<<28)
#define SD_VOLT_SWITCH_1_8 				(1<<24)


/********* SD CARD error status *********/

#define SD_OUT_OF_RANGE 				(BIT31)
#define SD_ADDR_ERR 					(BIT30)
#define SD_BLK_LEN_ERR 					(BIT29)
#define SD_ERASE_SEQ_ERR 				(BIT28)
#define SD_ERASE_PARAM_ERR 				(BIT27)
#define SD_WP_VIOLATION_ERR 			(BIT26)
#define SD_CARD_IS_LOCKED_ERR 			(BIT25)
#define SD_LOCK_UNLOCK_FAILED 			(BIT24)
#define SD_COM_CRC_ERR 					(BIT23)
#define SD_ILLEGAL_CMD 					(BIT22)
#define SD_CARD_ECC_FAILED 				(BIT21)
#define SD_CC_ERR 						(BIT20)
#define SD_ERR 							(BIT19)
#define SD_CSD_OVERWRITE 				(BIT16)
#define SD_WP_ERASE_SKIP 				(BIT15)
#define SD_CARD_ECC_DISABLED 			(BIT14)
#define SD_ERASE_RESET 					(BIT13)
#define SD_CURRENT_STATE 				set_bit_range(12,9)

#define SD_CUR_STATE_IDLE 				((0)<<9)
#define SD_CUR_STATE_READY 				((1)<<9)
#define SD_CUR_STATE_IDENT 				((2)<<9) 
#define SD_CUR_STATE_STBY 				((3)<<9)
#define SD_CUR_STATE_TRAN 				((4)<<9)
#define SD_CUR_STATE_DATA 				((5)<<9)
#define SD_CUR_STATE_RCV 				((6)<<9)
#define SD_CUR_STATE_PRG 				((7)<<9)
#define SD_CUR_STATE_DIS 				((8)<<9)

#define SD_READY_FOR_DATA 				(BIT8)
#define SD_APP_CMD 						(BIT5)
#define SD_AKE_SEQ_ERR 					(BIT3)


#define get_R1_card_state(BA) \
	(readreg32(SDIRSP0_REG(BA)))

#define get_card_current_state(BA) \
	((get_R1_card_state(BA)) & SD_CURRENT_STATE)

#define is_card_ready_for_data(BA) \
	((get_R1_card_state(BA)) & SD_READY_FOR_DATA)

/****************************************/


struct sd_card_info sd0_card_info;

void send_cmd(uint32_t BA,uint32_t cmd_con,uint32_t cmd_arg)
{
	set_sd_mmc_cmd_arg(BA,cmd_arg);
	set_sd_mmc_cmd_con(BA,cmd_con);
}

void wait_for_cmd_complete(uint32_t BA)
{
	/* Wait until command transfer in progress */
	while(get_cmd_progress_status(BA))
		;

	/* Wait until command is sent */
	while(!(get_cmd_sent_status(BA)))
		;

	/* Acknowledge the command sent */
	ack_cmd_sent(BA);

	//print_hex_uart(UART0_BA,readreg32(SDI_CMD_STATUS_REG(BA)));
}

void sd_delay()
{
	unsigned int i =  0;
	for(i = 0;i<0x100000;i++) { //Wait for 74 SD clock cycles.
		//TODO: Calculate the end condition based on the SD Clock cycles.
		;
	}
}

void sd_low_delay()
{
	unsigned int i =  0;
	for(i = 0;i<100;i++) { //Wait for 74 SD clock cycles.
		//TODO: Calculate the end condition based on the SD Clock cycles.
		;
	}
}

uint8_t parse_r7_response(uint32_t BA)
{
	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd8 timedout\n");
		return 0;
	} 

	ack_cmd_resp(BA);

	if((get_R7_rsp_chk_pattern(BA) == SD_CHECK_PATTERN) && 
		(get_R7_rsp_volt_accepted(BA) == SD_CARD_VOLTAGE_2_7)) {
			return 1;
	} else {
		return 0;
	}
}

void parse_r6_response(uint32_t BA,uint16_t *rca)
{
	*rca = get_R6_rsp_RCA(BA);
	ack_cmd_resp(BA);
}



void parse_CID_response(uint32_t BA, struct cid_info *cid_info)
{
	
	cid_info->MID = get_R2_rsp_CID_MID(BA);
	cid_info->CID = get_R2_rsp_CID_OID(BA);


	cid_info->PNM[0] = get_R2_rsp_CID_PNM_P1(BA);
	cid_info->PNM[1] = get_R2_rsp_CID_PNM_P2_pos(BA,24);
	cid_info->PNM[2] = get_R2_rsp_CID_PNM_P2_pos(BA,16);
	cid_info->PNM[3] = get_R2_rsp_CID_PNM_P2_pos(BA,8);
	cid_info->PNM[4] = get_R2_rsp_CID_PNM_P2_pos(BA,0);
	cid_info->PNM[5] = '\0';


	cid_info->PRV = get_R2_rsp_CID_PRV(BA);
	cid_info->PSN = get_R2_rsp_CID_PSN(BA);
	cid_info->MDT = get_R2_rsp_CID_MDT(BA);
	cid_info->CRC = get_R2_rsp_CID_CRC(BA);

	ack_cmd_resp(BA);
}

void parse_CSD_response(uint32_t BA, struct csd_info *csd_info)
{
	csd_info->rsp0 = readreg32(SDIRSP0_REG(BA));
	csd_info->rsp1 = readreg32(SDIRSP1_REG(BA));
	csd_info->rsp2 = readreg32(SDIRSP2_REG(BA));
	csd_info->rsp3 = readreg32(SDIRSP3_REG(BA));

	ack_cmd_resp(BA);
}

#ifdef DEBUG_CSD_REG
void parse_CSD_response_reg(uint32_t BA)
{
	uart_puts(UART0_BA, "CSD dump : ");

	uart_puts(UART0_BA,"csd_ver ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_STRUCT(BA));

	uart_puts(UART0_BA,"TAAC ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_TAAC(BA));

	uart_puts(UART0_BA,"NSAC ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_NSAC(BA));

	uart_puts(UART0_BA,"TRAN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_TRAN(BA));

	uart_puts(UART0_BA,"CCC ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_CCC(BA));

	uart_puts(UART0_BA,"READ_BLK_LEN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_READ_BLK_LEN(BA));

	uart_puts(UART0_BA,"READ_BLK_PARTIAL ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_READ_BLK_PARTIAL(BA));

	uart_puts(UART0_BA,"WRITE_BLK_MISALIGN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WRITE_BLK_MISALIGN(BA));

	uart_puts(UART0_BA,"READ_BLK_MISALIGN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_READ_BLK_MISALIGN(BA));

	uart_puts(UART0_BA,"DSR_IMP ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_DSR_IMP(BA));

	uart_puts(UART0_BA,"C_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_C_SIZE(BA)); 

/*	csd_info->VDD_R_CURR_MIN = get_R2_rsp_CSD_VDD_R_CURR_MIN(BA);
	uart_puts(UART0_BA,"VDD_R_CURR_MIN ");
	print_hex_uart(UART0_BA,csd_info->VDD_R_CURR_MIN);

	csd_info->VDD_R_CURR_MAX = get_R2_rsp_CSD_VDD_R_CURR_MAX(BA);
	uart_puts(UART0_BA,"VDD_R_CURR_MAX ");
	print_hex_uart(UART0_BA,csd_info->VDD_R_CURR_MAX);

	csd_info->VDD_W_CURR_MIN = get_R2_rsp_CSD_VDD_W_CURR_MIN(BA);
	uart_puts(UART0_BA,"VDD_W_CURR_MIN ");
	print_hex_uart(UART0_BA,csd_info->VDD_W_CURR_MIN);

	csd_info->VDD_W_CURR_MAX = get_R2_rsp_CSD_VDD_W_CURR_MAX(BA);
	uart_puts(UART0_BA,"VDD_W_CURR_MAX ");
	print_hex_uart(UART0_BA,csd_info->VDD_W_CURR_MAX);

	csd_info->C_SIZE_MULT = get_R2_rsp_CSD_C_SIZE_MULT(BA);
	uart_puts(UART0_BA,"C_SIZE_MULT ");
	print_hex_uart(UART0_BA,csd_info->C_SIZE_MULT); */

	uart_puts(UART0_BA,"ERASE_BLK_EN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_ERASE_BLK_EN(BA)); 

	uart_puts(UART0_BA,"SECTOR_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_SECTOR_SIZE(BA)); 

	uart_puts(UART0_BA,"WP_GRP_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WP_GRP_SIZE(BA)); 

	uart_puts(UART0_BA,"WP_GRP_ENABLE ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WP_GRP_ENABLE(BA)); 

	uart_puts(UART0_BA,"R2W_FACTOR ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_R2W_FACTOR(BA)); 

	uart_puts(UART0_BA,"WRITE_BL_LEN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WRITE_BL_LEN(BA)); 

	uart_puts(UART0_BA,"WRITE_BL_PARTIAL ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WRITE_BL_PARTIAL(BA)); 

	uart_puts(UART0_BA,"FILE_FORMAT_GRP ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_FILE_FORMAT_GRP(BA)); 

	uart_puts(UART0_BA,"COPY ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_COPY(BA)); 

	uart_puts(UART0_BA,"PERM_WRITE_PROTECT ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_PERM_WRITE_PROTECT(BA)); 

	uart_puts(UART0_BA,"TMP_WRITE_PROTECT ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_TMP_WRITE_PROTECT(BA)); 

	uart_puts(UART0_BA,"FILE_FORMAT ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_FILE_FORMAT(BA)); 

	ack_cmd_resp(BA);
}
#endif

void dump_sd_card_info(const struct sd_card_info *sd_card_info)
{

	uart_puts(UART0_BA,"*** SD Card Info ***\n");

	
	if(sd_card_info->is_high_capacity) {
		uart_puts(UART0_BA,"High capacity or extended capacity card\n");
	} else {
		uart_puts(UART0_BA,"Standard capacity card\n");
	}
	
	if(sd_card_info->is_ready_for_switching) {
		uart_puts(UART0_BA,"Card ready for switching\n");
		//TODO: Send CMD11 here.
	} else {
		uart_puts(UART0_BA,"Card not ready for switching\n");
	}

	uart_puts(UART0_BA,"\nCID DUMP\n");

	uart_puts(UART0_BA,"MID : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.MID);

	uart_puts(UART0_BA,"OID : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.CID);

	uart_puts(UART0_BA,"PNM : ");
	uart_puts(UART0_BA,sd_card_info->cid_info.PNM);
	uart_puts(UART0_BA,"\n");

	uart_puts(UART0_BA,"PRV : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.PRV);

	uart_puts(UART0_BA,"PSN : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.PSN);

	uart_puts(UART0_BA,"MDT : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.MDT);

	uart_puts(UART0_BA,"CRC : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.CRC);

	uart_puts(UART0_BA,"RCA : ");
	print_hex_uart(UART0_BA,sd_card_info->RCA);

	uart_puts(UART0_BA,"\nCSD DUMP\n");

	uart_puts(UART0_BA,"csd_ver : ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_STRUCT(sd_card_info->csd_info.rsp0));

	uart_puts(UART0_BA,"TAAC ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_TAAC(sd_card_info->csd_info.rsp0));

	uart_puts(UART0_BA,"NSAC ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_NSAC(sd_card_info->csd_info.rsp0));

	uart_puts(UART0_BA,"TRAN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_TRAN(sd_card_info->csd_info.rsp0));

	uart_puts(UART0_BA,"CCC ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_CCC(sd_card_info->csd_info.rsp1));


	uart_puts(UART0_BA,"READ_BLK_LEN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_READ_BLK_LEN(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"READ_BLK_PARTIAL ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_READ_BLK_PARTIAL(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"WRITE_BLK_MISALIGN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WRITE_BLK_MISALIGN(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"READ_BLK_MISALIGN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_READ_BLK_MISALIGN(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"DSR_IMP ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_DSR_IMP(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"C_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_C_SIZE(sd_card_info->csd_info.rsp1,sd_card_info->csd_info.rsp2));

	uart_puts(UART0_BA,"ERASE_BLK_EN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_ERASE_BLK_EN(sd_card_info->csd_info.rsp2));

	uart_puts(UART0_BA,"SECTOR_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_SECTOR_SIZE(sd_card_info->csd_info.rsp2));

	uart_puts(UART0_BA,"WP_GRP_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WP_GRP_SIZE(sd_card_info->csd_info.rsp2));

	uart_puts(UART0_BA,"WP_GRP_ENABLE ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WP_GRP_ENABLE(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"R2W_FACTOR ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_R2W_FACTOR(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"WRITE_BL_LEN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WRITE_BL_LEN(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"WRITE_BL_PARTIAL ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WRITE_BL_PARTIAL(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"FILE_FORMAT_GRP ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_FILE_FORMAT_GRP(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"COPY ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_COPY(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"PERM_WRITE_PROTECT ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_PERM_WRITE_PROTECT(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"TMP_WRITE_PROTECT ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_TMP_WRITE_PROTECT(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"FILE_FORMAT ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_FILE_FORMAT(sd_card_info->csd_info.rsp3));


	uart_puts(UART0_BA,"****************\n");
}

void config_sd_gpio()
{
	//Enable SD Card controller block.
	set_reg_params(GPCON_REG(GPE_BA),
		(SDCLK_GPIO_CONF|SDCMD_GPIO_CONF|SDDAT3_GPIO_CONF|SDDAT2_GPIO_CONF|
		SDDAT1_GPIO_CONF|SDDAT0_GPIO_CONF)); 

	//Disable pull up resistors
/*	set_reg_params(GPUP_REG(GPE_BA),
		(SDCLK_GPIO_PIN|SDCMD_GPIO_PIN|SDDAT0_GPIO_PIN|
			SDDAT1_GPIO_PIN|SDDAT2_GPIO_PIN| SDDAT3_GPIO_PIN));*/

}

void init_sd_controller()
{
	int retry = 0;

	config_sd_gpio();
	reset_sdmmc(SD_MMC_BA);

	/* PCLK set to 50MHz */

	set_sd_clk_prescale(SD_MMC_BA,499); //Setting the clock to max i.e. 100kHz.
	//set_sd_clk_prescale(SD_MMC_BA,124); //Setting the clock to max i.e. 400kHz.
	//set_sd_clk_prescale(SD_MMC_BA,1); //Setting the clock to max i.e. 400kHz.
	writereg32(SDICON_REG(SD_MMC_BA),RCV_IO_INT|BYTE_ORDER_B);
	writereg32(SDID_TIMER_REG(SD_MMC_BA),0x7FFFFF);

	set_reg_params(SDIFSTA_REG(SD_MMC_BA),FIFO_RESET);
	set_reg_params(SDICON_REG(SD_MMC_BA),CLK_OUT_EN);

	sd_delay();

	send_cmd(SD_MMC_BA,CMD_START|CMD_TRANSMISSION|CMD0,0x00000000); //Send cmd0
	wait_for_cmd_complete(SD_MMC_BA);

	//Delay below for atleast *some* cycles
	sd_low_delay();

	send_cmd(SD_MMC_BA,
					WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD8,
					SD_CARD_VOLTAGE_2_7|SD_CHECK_PATTERN); //Send cmd8

	sd_low_delay();

	wait_for_cmd_complete(SD_MMC_BA);

	if(parse_r7_response(SD_MMC_BA)) {
		uart_puts(UART0_BA,"voltage and chk pattern accepted\n");
	}

	for(retry = 0; retry < 50; /*retry++*/) {

	 	/* Send cmd55 */
		send_cmd(SD_MMC_BA,WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD55,0x00000000); 
		sd_low_delay();
		wait_for_cmd_complete(SD_MMC_BA);

		if(chk_cmd_resp(SD_MMC_BA) == CMD_TIMEOUT) {
			uart_puts(UART0_BA,"cmd55 timedout\n");
		} else {
			if(get_R1_rsp_card_status(SD_MMC_BA) & SD_APP_CMD) {
				uart_puts(UART0_BA, "Ready for app cmd\n");
			}
			ack_cmd_resp(SD_MMC_BA);
		}

/*********************************************************************************
 * According to the spec(Page 29) during initialization of the card the voltage
 * window field(bits 23-0) in the arguement is set to non-zero at the first time,
 * The other field (bits 31-24) in the arguement is effective i.e. should be set
 * based on our preference.
 *
 * As per the OCR register definition(Page 112) bit 23-0 is the Vdd Voltage window.
 * In it bits 14-0 are reserved and can be set to 0. Bit 23-15 should be set to 1
 * when sending acmd41 for the first time. Hence the value would be 0x00FF8000 i.e.
 * Bit23 to Bit15 being 1.
 *
 * Now I want to set HCS, XPC and S18R switching voltage bits. So the final value 
 * would be 0x51FF8000.
 **********************************************************************************/

		send_cmd(SD_MMC_BA,
					WAIT_RSP|CMD_START|CMD_TRANSMISSION|ACMD41,
					SD_HCS_SDHC_SDXC|
					SD_MAX_PERFORMANCE|
					SD_VOLT_SWITCH_1_8|
					0xFF8000U);

		sd_delay();
		wait_for_cmd_complete(SD_MMC_BA);

/*
 * In the response to ACMD41 there will be CRC error. Please note that the 
 * CRC for the r3 response is just stuff bytes '11111111'.
 *
 * The CRC error can be ignored.
 */
		if(chk_cmd_resp(SD_MMC_BA) == CMD_TIMEOUT) {
			uart_puts(UART0_BA,"acmd41 timedout\n");
		} else {
			if(get_R3_rsp_busy_status(SD_MMC_BA)) { //If 1 not busy else busy
				break;
			} else {
				ack_cmd_resp(SD_MMC_BA);
			}
		}
	}

	sd0_card_info.is_high_capacity = get_R3_rsp_card_capacity_status(SD_MMC_BA);
	sd0_card_info.is_ready_for_switching = get_R3_rsp_card_ready_for_switching(SD_MMC_BA);

	ack_cmd_resp(SD_MMC_BA);
	
	/* Send CMD2 */
	send_cmd(
			SD_MMC_BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|LONG_RSP|CMD2,
			0xFFFFFFFFU
			);

	sd_low_delay();
	wait_for_cmd_complete(SD_MMC_BA);

	if(chk_cmd_resp(SD_MMC_BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd2 timedout\n");
	} else {
		parse_CID_response(SD_MMC_BA,&sd0_card_info.cid_info);
	}

	/* Send CMD3 */
	send_cmd(
			SD_MMC_BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD3, 
			0xFFFFFFFFU
			);


	sd_low_delay();
	wait_for_cmd_complete(SD_MMC_BA);

	if(chk_cmd_resp(SD_MMC_BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd3 timedout\n");
	} else {
		parse_r6_response(SD_MMC_BA,&sd0_card_info.RCA);
	}
	

	/* Send CMD9 */
	send_cmd(
			SD_MMC_BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|LONG_RSP|CMD9,
			((sd0_card_info.RCA)<<16|0xFFFF)
			);

	sd_low_delay();
	wait_for_cmd_complete(SD_MMC_BA);

	if(chk_cmd_resp(SD_MMC_BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd9 timedout\n");
	} else {
	//	parse_CSD_response_reg(SD_MMC_BA);
		parse_CSD_response(SD_MMC_BA,&sd0_card_info.csd_info);
	}
				
	dump_sd_card_info(&sd0_card_info);

	/* Send CMD7 i.e. Select Card */
	send_cmd(SD_MMC_BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD7,
			((sd0_card_info.RCA)<<16|0xFFFF)
			);

	sd_low_delay();
	wait_for_cmd_complete(SD_MMC_BA);

	if(chk_cmd_resp(SD_MMC_BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd7 timedout\n");
	} else {
		if(is_card_ready_for_data(SD_MMC_BA)) {
			uart_puts(UART0_BA,"Card ready for data\n");
		}
	}
}

