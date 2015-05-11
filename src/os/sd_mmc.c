#include "sd_mmc.h"

/* PCLK set to 50Mhz */
void set_sd_mmc_clk(uint8_t prescaler_value)
{
	set_reg_params(SDIPRE_REG(SD_MMC_BA),prescaler_value);
}


void send_cmd(uint32_t cmd_arg)
{
	set_reg_params(SDICON_REG(SD_MMC_BA),CLK_OUT_EN);
	
	send_sd_mmc_cmd(cmd_arg);
	
	clear_reg_params(SDICON_REG(SD_MMC_BA),CLK_OUT_EN);
}

void init_sd_controller()
{
	set_reg_params(SDICON_REG(SD_MMC_BA),SDMMC_RESET);
	set_sd_mmc_clk(1); //Setting the clock to max i.e. 25 Mhz.
}
