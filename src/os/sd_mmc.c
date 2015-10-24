#include "sd_mmc.h"
#include "uart_util.h"
#include "gpio_def.h"
#include "reg_dump.h"

/****************************************/

#define SD_BLOCK_SIZE 	512U

/****************************************/

/************ CMD_INDEX *****************/


#define OPT_SEL_CARD 	1U
#define OPT_DESEL_CARD 	0U

#define BLK_READ_BYTE_SIZE 	512U

#define CMD0 	0U  //Go idle state.
#define CMD2 	2U  //All send CID.
#define CMD3 	3U  //Send relative address i.e. RCA.
#define CMD7 	7U  //Select/deselect card.
#define CMD8    8U  //Send interface condition.
#define CMD9 	9U  //Send CSD
#define CMD10 	10U //Send CID
#define CMD13 	13U //Send status
#define CMD15 	15U //Go inactive.
#define CMD17 	17U //Read single block.
#define CMD24 	24U //Write single block.
#define CMD55 	55U
#define ACMD41 	41U


#define SD_CARD_VOLTAGE_2_7  			(1U<<8)
#define SD_CARD_VOLTAGE_LOW_VOLTAGE  	(2U<<8)
#define SD_CHECK_PATTERN 				(0xAA)

#define SD_HCS_SDSC 					~(1U<<30)
#define SD_HCS_SDHC_SDXC 				(1U<<30)
#define SD_MAX_PERFORMANCE 		 		(1U<<28)
#define SD_VOLT_SWITCH_1_8 				(1U<<24)


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
#define SD_CUR_STATE_READY 				((1U)<<9)
#define SD_CUR_STATE_IDENT 				((2U)<<9) 
#define SD_CUR_STATE_STBY 				((3U)<<9)
#define SD_CUR_STATE_TRAN 				((4U)<<9)
#define SD_CUR_STATE_DATA 				((5U)<<9)
#define SD_CUR_STATE_RCV 				((6U)<<9)
#define SD_CUR_STATE_PRG 				((7U)<<9)
#define SD_CUR_STATE_DIS 				((8U)<<9)

#define SD_READY_FOR_DATA 				(BIT8)
#define SD_APP_CMD 						(BIT5)
#define SD_AKE_SEQ_ERR 					(BIT3)


#define get_R1_card_state(BA) \
	(readreg32(SDIRSP0_REG(BA)))

#define get_R1_card_current_state(BA) \
	((get_R1_card_state(BA)) & SD_CURRENT_STATE)

#define get_card_state(card_state) \
	((card_state) & (SD_CURRENT_STATE))

#define is_card_ready_for_data(BA) \
	((get_R1_card_state(BA)) & SD_READY_FOR_DATA)

/****************************************/

/**
 * Note on SD Card Responses in S3C2440 registers
 * ==============================================
 * The SD Response registers in S3C2440 is like a stream. If there is for eg
 * more than 32b needed for the response it spills over to the next set of
 * 32b registers.
 *
 * For eg for the R2 register response for the CID,CSD the total size of the
 * response is 135-0 i.e. 136 bits. In this the start bit, transmission bit and
 * reserved has to be ignored. The remaining 0-127 i.e. 128 bits are to be 
 * parsed. To parse this 128b/32b i.e. 4 registers are needed.
 *
 */

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
	if((get_R7_rsp_chk_pattern(BA) == SD_CHECK_PATTERN) && 
		(get_R7_rsp_volt_accepted(BA) == SD_CARD_VOLTAGE_2_7)) {
		return 1;
	} else {
		return 0;
	}
}

void parse_r6_response(uint32_t BA,uint32_t *rca)
{
	*rca = get_R6_rsp_RCA(BA);
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
}

void parse_CSD_response(uint32_t BA, struct csd_info *csd_info)
{
	csd_info->rsp0 = readreg32(SDIRSP0_REG(BA));
	csd_info->rsp1 = readreg32(SDIRSP1_REG(BA));
	csd_info->rsp2 = readreg32(SDIRSP2_REG(BA));
	csd_info->rsp3 = readreg32(SDIRSP3_REG(BA));
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


static void print_current_state(uint32_t CURRENT_STATE)
{
	switch(CURRENT_STATE) {
		case SD_CUR_STATE_IDLE:
			uart_puts(UART0_BA,"IDLE\n");
			break;
		case SD_CUR_STATE_READY:
			uart_puts(UART0_BA,"READY\n");
			break;
		case SD_CUR_STATE_IDENT:
			uart_puts(UART0_BA,"IDENT\n");
			break;
		case SD_CUR_STATE_STBY:
			uart_puts(UART0_BA,"STBY\n");
			break;
		case SD_CUR_STATE_TRAN:
			uart_puts(UART0_BA,"TRAN\n");
			break;
		case SD_CUR_STATE_DATA:
			uart_puts(UART0_BA,"DATA\n");
			break;
		case SD_CUR_STATE_RCV:
			uart_puts(UART0_BA,"RCV\n");
			break;
		case SD_CUR_STATE_PRG:
			uart_puts(UART0_BA,"PRG\n");
			break;
		case SD_CUR_STATE_DIS:
			uart_puts(UART0_BA,"DIS\n");
			break;
		default:
			uart_puts(UART0_BA,"Unknown Status\n");
			break;
	}
}

uint32_t sd_read_single_block(
							uint32_t BA,
							uint32_t block_addr,
							uint32_t RCA
							)
{
	uint32_t current_state = 0;

	reset_fifo(BA);
	uart_puts(UART0_BA,"Read single block\n");

	/* Send CMD17 i.e. READ_SINGLE_BLOCK */
	send_cmd(
		BA,
		CMD_WITH_DATA|WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD17,
		block_addr
			);

	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd17 timedout\n");
		return current_state;
	}

	ack_cmd_resp(BA);
	
 	current_state = get_R1_card_state(BA);

	return current_state;
}

int sd_read_data(
				uint32_t BA, 
				uint32_t num_blocks,
				char * const sd_buff,
				int size
				)
{
	int i = 0;
//	int count = 0;

	//NOTE: SDID_DATA_CON address has a problem
	//with address 0.
	writereg32(
				SDID_DATA_CON_REG(BA),
					DATA_RECEIVE_MODE|
					BLOCK_MODE|
					(num_blocks & BLK_NUM_MASK)
			); //Set data receive mode.

	sd_start_data_transfer(BA);

/*
	uart_puts(UART0_BA,"Waiting");

	while(!is_fifo_rx_available(BA))
		uart_puts(UART0_BA,".");
	
	uart_puts(UART0_BA,"\n");

	uart_puts(UART0_BA,"DATA_CON:");
	print_hex_uart(UART0_BA,readreg32(SDID_DATA_CON_REG(BA)));

	uart_puts(UART0_BA,"SDI_FIFO_STA:");
	print_hex_uart(UART0_BA,readreg32(SDIFSTA_REG(BA)));

	uart_puts(UART0_BA,"SDIDATCnt:");
	print_hex_uart(UART0_BA,readreg32(SDI_DAT_CNT_REG(BA)));

	uart_puts(UART0_BA,"SDIDATSta:");
	print_hex_uart(UART0_BA,readreg32(SDI_DATA_STATUS_REG(BA)));
	count = get_fifo_cnt(BA);
*/

	for(i = 0; i<size;) {
		if(is_fifo_rx_available(BA)) {

			sd_buff[i] = readreg8(SDI_DATA_LI_B_REG(BA));
		/*	print_hex_uart(
				UART0_BA,
				readreg8(SDI_DATA_LI_B_REG(BA))
				);*/

			i++;
		}
	}

	/* Discard the remaining data out */


	return size;
}


int sd_read(
			uint32_t BA,
			struct sd_card_info * const sd_card_info,
			const uint32_t addr,
			char * const buff, 
			const uint32_t size
			)
{
	const uint32_t block_num = get_block_num(addr,
				get_R2_rsp_var_CSD_READ_BLK_LEN(sd_card_info->csd_info.rsp1)
				);

	sd_read_single_block(
						BA,
						block_num,
						sd_card_info->RCA
						);

	return sd_read_data(BA,1,buff,size);
}


int sd_write_data(
				uint32_t BA, 
				uint32_t num_blocks,
				char * const sd_buff,
				int size
				)
{
	int i = 0;

	writereg32(
				SDID_DATA_CON_REG(BA),
					DATA_TRANSMIT_MODE|
					BLOCK_MODE|
					(num_blocks & BLK_NUM_MASK)
			); //Set data receive mode.

	sd_start_data_transfer(BA);

	for(i = 0; i<size;) {
		if(is_fifo_tx_available(BA)) {
			writereg8(SDI_DATA_LI_B_REG(BA),sd_buff[i]);
			i++;
		}
	}
	
	return size;
}

uint32_t sd_write_single_block(
						uint32_t BA,
						uint32_t block_addr,
						uint32_t RCA
						)
{
	uint32_t current_state = 0;

	reset_fifo(BA);

	uart_puts(UART0_BA,"Write single block\n");

	send_cmd(
		BA,
		CMD_WITH_DATA|WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD24, 
		block_addr);

	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd24 timedout\n");
		return current_state;
	}

	ack_cmd_resp(BA);

 	current_state = get_R1_card_state(BA);

	return current_state;
}


//TODO: Need to return an error statue if not able to read state.
uint32_t get_cmd13_current_state(uint32_t BA,uint32_t RCA)
{
	
	/* Get card status */
	uint32_t current_state = 0;

	send_cmd(
			BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD13,
			(((RCA)<<16) | 0xFFFF)
			);

	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd13 timedout\n");
	} 
	
	current_state = get_R1_card_state(BA);

	/*
	  uart_puts(UART0_BA,"CMD13 Status:");
	  print_hex_uart(UART0_BA,current_state);
	 */
	ack_cmd_resp(BA);


//TODO: When returning AND with the SD_CURRENT_STATE mask 
	return current_state;
}

//TODO:Return error value if not successful.
uint32_t select_deselect_card(uint32_t BA,uint32_t RCA,uint8_t sel_desel)
{
	uint32_t card_state = 0;
	
	/* Select card */
	uart_puts(UART0_BA,"Select Card:");
	print_hex_uart(UART0_BA,(RCA)<<16);

	if(sel_desel == OPT_SEL_CARD) {
		send_cmd(BA,
				WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD7,
				(((RCA)<<16)|0xFFFFU)
				);
	} else if(sel_desel == OPT_DESEL_CARD) {
		send_cmd(BA,
				WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD7,
				0x00000000
				);
	} else {
		return card_state;
	}

	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd7 timedout\n");
		return card_state;
	}

	card_state = get_R1_card_current_state(BA);
	ack_cmd_resp(BA);

	return card_state;
}

uint32_t get_sd_card_CSD_info(
			uint32_t BA,
			uint32_t RCA,
			struct csd_info *sd_csd_info) 
{

/**** Send CMD9 ****/

	send_cmd(
			BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|LONG_RSP|CMD9,
			((RCA<<16)|0xFFFF)
			);

	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd9 timedout\n");
		return 0;
	}

	parse_CSD_response(BA,sd_csd_info);
	ack_cmd_resp(BA);
	return 0;
}

uint32_t get_sd_card_CID_info(
						uint32_t BA,
						uint32_t RCA,
						struct cid_info *sd_cid_info
						)
{

	/**** Send CMD10 ****/

	send_cmd(
		BA,
		WAIT_RSP|CMD_START|CMD_TRANSMISSION|LONG_RSP|CMD10,
		((RCA<<16)|0xFFFF)
		);

	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd10 timedout\n");
		return 0;
	}

	parse_CID_response(BA,sd_cid_info);
	ack_cmd_resp(BA);

	return 0;
}


uint32_t get_sd_card_RCA(uint32_t BA,uint32_t *RCA)
{

/**** Send CMD3 ****/

	send_cmd(
			BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD3, 
			0xFFFFFFFFU
			);


	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd3 timedout\n");
		return 0;
	}
		
	set_sd_clk_prescale(BA,1); //Setting the clock to max i.e. 25MHz

	parse_r6_response(BA,RCA);

	ack_cmd_resp(BA);

	uart_puts(UART0_BA,"RCA:");
	print_hex_uart(UART0_BA,*RCA);

	return 0;
/****************************************************/
}


//TODO: Return values has to be modified.
uint32_t send_if_cond(uint32_t BA)
{
	
	/*** Send CMD8 ***/
	send_cmd(BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD8,
			SD_CARD_VOLTAGE_2_7|SD_CHECK_PATTERN
			); //Send cmd8

	sd_low_delay();

	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd8 timedout\n");
		return 0;
	} 

	if(parse_r7_response(BA)) {
		uart_puts(UART0_BA,"voltage and chk pattern accepted\n");
		return 1;
	} else {
		return 0;
	}

	ack_cmd_resp(BA);
}

//TODO: Handle error condition response.
uint32_t make_sd_card_inactive(
							uint32_t BA,
							uint32_t RCA
							)
{
	
	uint32_t card_response = 0;

	send_cmd(
			BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD15,
			(((RCA)<<16) | 0xFFFF)
			);

	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd15 timedout\n");
		return card_response;
	}

	card_response = get_R1_card_state(BA);
	ack_cmd_resp(BA);

	return card_response;
}

uint32_t do_all_send_CID(uint32_t BA,struct cid_info *cid_info)
{

	/**** Send CMD2 ****/
	send_cmd(
			BA,
			WAIT_RSP|CMD_START|CMD_TRANSMISSION|LONG_RSP|CMD2,
			0xFFFFFFFFU
			);

	sd_low_delay();
	wait_for_cmd_complete(BA);

	if(chk_cmd_resp(BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd2 timedout\n");
		return 0;
	}

	parse_CID_response(BA,cid_info);
	ack_cmd_resp(BA);

	return 1;
}

/*
 * Note on Card Responses:
 * -----------------------
 *
 * All card R1 responses which contain the current SD Current State.
 * for a particular command contain states of previous commands.
 *
 * From the Spec: 
 * The state of the card when receiving the command. If the command execution causes a state change, 
 * it will be visible to the host in the response to the next command.  The four bits are interpreted 
 * as a binary coded number between 0 and 15.
 *
 */


void init_sd_controller()
{
	int retry = 0;
	uint32_t i = 0;
	uint32_t current_state = 0;
	char sd_buff[SD_BLOCK_SIZE];


	config_sd_gpio();
	reset_sdmmc(SD_MMC_BA);


	/* PCLK set to 50MHz */

	set_sd_clk_prescale(SD_MMC_BA,499); //Setting the clock to max i.e. 100kHz.
	//set_sd_clk_prescale(SD_MMC_BA,124); //Setting the clock to max i.e. 400kHz.
	//set_sd_clk_prescale(SD_MMC_BA,1); //Setting the clock to max i.e. 25MHz
	
	writereg32(SDICON_REG(SD_MMC_BA),RCV_IO_INT|BYTE_ORDER_B);

	set_data_timeout_period(SD_MMC_BA,0x7FFFFF);
	//set_reg_params(SDIFSTA_REG(SD_MMC_BA),FIFO_RESET);
	reset_fifo(SD_MMC_BA);
	set_clk_out_en(SD_MMC_BA);

	sd_delay();


/****************** Send CMD0 ******************/
	send_cmd(SD_MMC_BA,CMD_START|CMD_TRANSMISSION|CMD0,0x00000000); //Send cmd0
	wait_for_cmd_complete(SD_MMC_BA);

	//Delay below for atleast *some* cycles
	sd_low_delay();
/***********************************************/


/****************** Send CMD8 ******************/

	if(send_if_cond(SD_MMC_BA) == 0)
		return;

/***********************************************/

	for(retry = 0; retry < 50; /*retry++*/) {

/****************** Send CMD55 ******************/

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
/***********************************************/

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

/****************** Send ACMD41 ******************/
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
/**************************************************/
	
/******************* Send CMD2 ********************/

	do_all_send_CID(SD_MMC_BA,&sd0_card_info.cid_info);

/****************************************************/

/******************* Send CMD3 ********************/

SD_CMD3:
	get_sd_card_RCA(SD_MMC_BA,&sd0_card_info.RCA);

	current_state = get_card_state(
						get_cmd13_current_state(SD_MMC_BA,sd0_card_info.RCA)
					);

	print_current_state(current_state);

	if((current_state) != SD_CUR_STATE_STBY) {
		goto SD_CMD3;
	}


/****************************************************/

/******************* Send CMD9 ********************/

	get_sd_card_CSD_info(
					SD_MMC_BA,
					sd0_card_info.RCA,
					&sd0_card_info.csd_info
					);

	dump_sd_card_info(&sd0_card_info);


/****************************************************/

/* Make card inactive CMD15 for testing */

#ifdef INACTIVE_TEST
/******************* Send CMD15 ********************/

	make_sd_card_inactive(
						SD_MMC_BA,
						sd0_card_info.RCA);
/****************************************************/
#endif



/********************* Send CMD7 ********************/
	
	select_deselect_card(SD_MMC_BA,sd0_card_info.RCA,OPT_SEL_CARD);


/******************* Send CMD13 ********************/
/* Get card status */
	
	print_current_state(
			get_card_state(
				get_cmd13_current_state(SD_MMC_BA,
				sd0_card_info.RCA)));

/****************************************************/


	/* Write and Read Block size  = 2^WR_BL_LEN and 2^RD_BL_LEN */
	set_sdi_block_size(SD_MMC_BA,
		(1<<(get_R2_rsp_var_CSD_READ_BLK_LEN(sd0_card_info.csd_info.rsp1))) );


	
	/* Send CMD17 to read a block */
	/*sd_read_single_block(SD_MMC_BA,0,sd0_card_info.RCA);
	sd_read_data(SD_MMC_BA,1,sd_buff,512);*/

	sd_read(SD_MMC_BA,&sd0_card_info,0,sd_buff,SD_BLOCK_SIZE);

	uart_puts(UART0_BA,"Data dump:\n");
	for(i = 0; i<512; i++) {
		print_hex_uart(UART0_BA,sd_buff[i]);
	}
	uart_puts(UART0_BA,"\n");


	sd_write_single_block(
						SD_MMC_BA,
						0,
						sd0_card_info.RCA
						);

}

