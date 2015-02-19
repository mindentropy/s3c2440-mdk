#include "nand.h"
#include "gpio_def.h"

/*
 * NAND driver will be written for Samsung K9F2G08U0B -> 256MB NAND Flash (Old mini2440)
 * NAND driver will be written for Samsung K9K8G08U0D SCB0 -> 1GB NAND Flash (New mini2440)
 */

void set_nand_gpio_config_pins()
{
	clear_reg_params(GPCON_REG(GPG_BA),NAND1_GPG13_INPUT);
	clear_reg_params(GPCON_REG(GPG_BA),NAND2_GPG14_INPUT);
	clear_reg_params(GPCON_REG(GPG_BA),NAND3_GPG15_INPUT);
}


