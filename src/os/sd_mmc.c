#include "sd_mmc.h"

/* PCLK set to 50Mhz */
void set_sd_mmc_clk(unsigned prescaler_value)
{
	
}

void init_sd_controller()
{
	set_reg_params(SDICON_REG(SD_MMC_BA),ENCLK|RCV_IO_INT);
}
