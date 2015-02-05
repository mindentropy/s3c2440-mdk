#include "spkr.h"

void init_spkr()
{
	disable_pull_up(GPUP_REG(GPB_BA),SPKR_GPIO_PIN);
	set_reg_params(GPCON_REG(GPB_BA),SPKR_GPIO_OUT);
}
