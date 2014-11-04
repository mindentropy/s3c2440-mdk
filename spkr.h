#ifndef SPKR_H_

#define SPKR_H_

#include "common.h"
#include "gpio_def.h"

#define set_spkr_hi() \
	set_reg_params(GPBDAT,SPKR_GPIO_PIN)

#define set_spkr_lo() \
	clear_reg_params(GPBDAT,SPKR_GPIO_PIN)

void init_spkr();


#endif
