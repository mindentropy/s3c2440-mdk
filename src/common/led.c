#include "led.h"
#include "gpio_def.h"

void init_led()
{
	//Set the port to output.
	set_reg_params(GPBCON,LED1_GPIO_OUT); 
	set_reg_params(GPBCON,LED2_GPIO_OUT); 
	set_reg_params(GPBCON,LED3_GPIO_OUT); 
	set_reg_params(GPBCON,LED4_GPIO_OUT); 
	
	
	//Disable pull up.
	set_reg_params(GPBUP,LED1|LED2|LED3|LED4);
}

void led_off(unsigned led)
{
	set_reg_params(GPBDAT,led);
}

void led_on(unsigned led)
{
	clear_reg_params(GPBDAT,led);
}
