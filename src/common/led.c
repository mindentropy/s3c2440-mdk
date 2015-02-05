#include "led.h"
#include "gpio_def.h"

void init_led()
{
	//Set the port to output.
	
	
	set_reg_params(GPCON_REG(GPB_BA),LED1_GPIO_OUT); 
	set_reg_params(GPCON_REG(GPB_BA),LED2_GPIO_OUT); 
	set_reg_params(GPCON_REG(GPB_BA),LED3_GPIO_OUT); 
	set_reg_params(GPCON_REG(GPB_BA),LED4_GPIO_OUT); 
	
	
	//Disable pull up.
	set_reg_params(GPUP_REG(GPB_BA),LED1|LED2|LED3|LED4);
}

void led_off(unsigned led)
{
	set_reg_params(GPDAT_REG(GPB_BA),led);
}

void led_on(unsigned led)
{
	clear_reg_params(GPDAT_REG(GPB_BA),led);
}
