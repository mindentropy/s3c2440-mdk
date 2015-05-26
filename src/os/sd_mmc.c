#include "sd_mmc.h"
#include "uart_util.h"


/************ CMD_INDEX *****************/

#define CMD0 	0
#define CMD8    8



#define SD_CARD_VOLTAGE_2_7  			(1<<8)
#define SD_CARD_VOLTAGE_LOW_VOLTAGE  	(2<<8)

#define SD_CHECK_PATTERN 				(0x00)

/****************************************/


void send_cmd0()
{
	set_sd_mmc_cmd_arg(SD_MMC_BA,0x00);
	set_sd_mmc_cmd_con(SD_MMC_BA,CMD_START|CMD_TRANSMISSION|CMD0);
}

void send_cmd8()
{
	set_sd_mmc_cmd_arg(SD_MMC_BA,SD_CARD_VOLTAGE_2_7|SD_CHECK_PATTERN);
	set_sd_mmc_cmd_con(SD_MMC_BA,WAIT_RSP|CMD_START|CMD_TRANSMISSION|CMD8);
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
	set_reg_params(SDI_CMD_STATUS_REG(SD_MMC_BA),CMD_SENT);
}

void init_sd_controller()
{
	unsigned int i =  0;
	reset_sdmmc();

	/* PCLK set to 50MHz */

	set_sd_clk_prescale(SD_MMC_BA,499); //Setting the clock to max i.e. 100kHz.
	writereg32(SDICON_REG(SD_MMC_BA),RCV_IO_INT|BYTE_ORDER_B);
	writereg32(SDID_TIMER_REG(SD_MMC_BA),0x7FFFFF);

	set_reg_params(SDIFSTA_REG(SD_MMC_BA),FIFO_RESET);
	set_reg_params(SDICON_REG(SD_MMC_BA),CLK_OUT_EN);

	for(i = 0;i<0x1000;i++) { //Wait for 74 SD clock cycles.
		//TODO: Calculate the end condition based on the SD Clock cycles.
		;
	}
	

	print_hex_uart(UART0_BA,readreg32(SDI_CMD_STATUS_REG(SD_MMC_BA)));
	send_cmd0();
	wait_for_cmd_complete();
	send_cmd8();
	print_hex_uart(UART0_BA,readreg32(SDI_CMD_STATUS_REG(SD_MMC_BA)));
	wait_for_cmd_complete();
}

