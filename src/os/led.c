#include "led.h"
#include "gpio_def.h"

void init_led()
{
	//Set the port to output.
	
	
	set_reg_bits(GPCON_REG(GPB_BA),LED1_GPIO_OUT); 
	set_reg_bits(GPCON_REG(GPB_BA),LED2_GPIO_OUT); 
	set_reg_bits(GPCON_REG(GPB_BA),LED3_GPIO_OUT); 
	set_reg_bits(GPCON_REG(GPB_BA),LED4_GPIO_OUT); 
	
	
	//Disable pull up.
	set_reg_bits(GPUP_REG(GPB_BA),LED1|LED2|LED3|LED4);
}

void led_off(unsigned led)
{
	set_reg_bits(GPDAT_REG(GPB_BA),led);
}

void led_on(unsigned led)
{
	clear_reg_bits(GPDAT_REG(GPB_BA),led);
}


void toggle_led(unsigned led)
{
	writereg32( GPDAT_REG(GPB_BA),
			((readreg32(GPDAT_REG(GPB_BA))) ^ (led)) );
					
}

