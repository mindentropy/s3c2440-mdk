#include "sd_mmc.h"
#include "uart_util.h"
#include "gpio_def.h"

/************ CMD_INDEX *****************/

#define CMD0 	0
#define CMD8    8
#define CMD55 	55
#define ACMD41 	41



#define SD_CARD_VOLTAGE_2_7  			(1<<8)
#define SD_CARD_VOLTAGE_LOW_VOLTAGE  	(2<<8)
#define SD_CHECK_PATTERN 				(0xAA)


/*** SD CARD error status ***/

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



/****************************************/


void send_cmd0()
{
	set_sd_mmc_cmd_arg(SD_MMC_BA,0x00000000);
	set_sd_mmc_cmd_con(SD_MMC_BA,CMD_START|CMD_TRANSMISSION|CMD0);
}

void send_cmd8()
{
	set_sd_mmc_cmd_arg(SD_MMC_BA,SD_CARD_VOLTAGE_2_7|SD_CHECK_PATTERN);
	set_sd_mmc_cmd_con(SD_MMC_BA,WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD8);
}

void send_cmd55()
{
	set_sd_mmc_cmd_arg(SD_MMC_BA,0x00000000);
	set_sd_mmc_cmd_con(SD_MMC_BA,WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD55);
}

void send_acmd41()
{
}

void wait_for_cmd_complete()
{
	/* Wait until command transfer in progress */
	while((readreg32(SDI_CMD_STATUS_REG(SD_MMC_BA))) & CMD_PROGRESS_ON)
		;

	/* Wait until command is sent */
	while(!(readreg32(SDI_CMD_STATUS_REG(SD_MMC_BA)) & CMD_SENT))
		;

	print_hex_uart(UART0_BA,readreg32(SDI_CMD_STATUS_REG(SD_MMC_BA)));
}

void sd_delay()
{
	unsigned int i =  0;
	for(i = 0;i<0x100000;i++) { //Wait for 74 SD clock cycles.
		//TODO: Calculate the end condition based on the SD Clock cycles.
		;
	}
}

uint8_t parse_r7_response()
{
	if((get_R7_rsp_chk_pattern(SD_MMC_BA) == SD_CHECK_PATTERN) && 
		(get_R7_rsp_volt_accepted(SD_MMC_BA) == SD_CARD_VOLTAGE_2_7)) {
			return 1;
	} else {
		return 0;
	}
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
	config_sd_gpio();
	reset_sdmmc();

	/* PCLK set to 50MHz */

	set_sd_clk_prescale(SD_MMC_BA,499); //Setting the clock to max i.e. 100kHz.
	//set_sd_clk_prescale(SD_MMC_BA,124); //Setting the clock to max i.e. 400kHz.
	//set_sd_clk_prescale(SD_MMC_BA,1); //Setting the clock to max i.e. 400kHz.
	writereg32(SDICON_REG(SD_MMC_BA),RCV_IO_INT|BYTE_ORDER_B);
	writereg32(SDID_TIMER_REG(SD_MMC_BA),0x7FFFFF);

	set_reg_params(SDIFSTA_REG(SD_MMC_BA),FIFO_RESET);
	set_reg_params(SDICON_REG(SD_MMC_BA),CLK_OUT_EN);

	sd_delay();

	send_cmd0();
	sd_delay();
	wait_for_cmd_complete();
	ack_cmd_sent(SD_MMC_BA);
	print_hex_uart(UART0_BA,readreg32(SDI_CMD_STATUS_REG(SD_MMC_BA)));

	send_cmd8();
	sd_delay();
	wait_for_cmd_complete();

	if(chk_cmd_resp(SD_MMC_BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd8 timedout\n");
	} else {
		if(parse_r7_response()) {
			uart_puts(UART0_BA,"voltage and chk pattern accepted\n");
		}
		ack_cmd_resp(SD_MMC_BA);
	}

	ack_cmd_sent(SD_MMC_BA);

	send_cmd55();
	sd_delay();
	wait_for_cmd_complete();
	if(chk_cmd_resp(SD_MMC_BA) == CMD_TIMEOUT) {
		uart_puts(UART0_BA,"cmd55 timedout\n");
	} else {
		if(get_r1_rsp_card_status(SD_MMC_BA) & SD_APP_CMD) {
			uart_puts(UART0_BA, "Ready for app cmd\n");
			print_hex_uart(UART0_BA,readreg32(SDIRSP0_REG(SD_MMC_BA)));
		}
		ack_cmd_resp(SD_MMC_BA);
	}
	ack_cmd_sent(SD_MMC_BA);

}

