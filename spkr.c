#include "spkr.h"

void init_spkr()
{
	disable_pull_up(GPBUP,SPKR_GPIO_PIN);
	set_reg_params(GPBCON,SPKR_GPIO_OUT);
}
