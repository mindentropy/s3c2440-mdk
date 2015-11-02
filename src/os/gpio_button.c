#include "gpio_button.h"

/* MINI2440 Button Diagram 
 * -----------------------
 *
 * K6 K4 K5    Battery Holder.
 * K3 K2 K1 
 *
 */


void init_gpio_button()
{
	//TODO: Do a clear_reg_params just to be safe.

	//Disable pull up.	
	set_reg_params(GPUP_REG(GPG_BA),
			K1_GPIO_BTN
			|K2_GPIO_BTN
			|K3_GPIO_BTN
			|K4_GPIO_BTN
			|K5_GPIO_BTN
			|K6_GPIO_BTN);
}
