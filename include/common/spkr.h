#ifndef SPKR_H_

#define SPKR_H_

#include "common.h"
#include "gpio_def.h"

#define set_spkr_hi() \
	set_reg_bits(GPDAT_REG(GPB_BA),SPKR_GPIO_PIN)

#define set_spkr_lo() \
	clear_reg_bits(GPDAT_REG(GPB_BA),SPKR_GPIO_PIN)

//void init_spkr();

#define init_spkr() \
	do { \
		disable_pull_up(GPUP_REG(GPB_BA),SPKR_GPIO_PIN); \
		set_reg_bits(GPCON_REG(GPB_BA),SPKR_GPIO_OUT); \
	} while(0)


#endif
