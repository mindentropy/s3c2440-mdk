#include "gpio_def.h"
#include "led.h"
#include "clock_pm.h"
#include "uart.h"

/*
 *  LED Orientation
 *
 *  <- Interfaces side -- GPIO Headers side  ->
 *   _   _   _   _
 *  |_| |_| |_| |_|
 *   1   2   3   4
 *
 *  nLED_1 -> GPB5
 *	nLED_2 -> GPB6
 *	nLED_3 -> GPB7
 *  nLED_4 -> GPB8
 *
 */



int main(void) {

	writereg32(GPBCON,0x15400);
	writereg32(GPBUP,0x1E0);

	register unsigned int i = 0, j = 0;
	

	init_uart0();

	
/* Without delay the led blink rate is 2MHz. */
	while(1) {

		writereg32(GPBDAT,LED2|LED3);

		uart_writel_ch0('a');

		for(j = 0; j<3; j++) 
			for(i = 0; i<100000;i++)
				;


		writereg32(GPBDAT,0x0);

		for(j = 0; j<3; j++)
			for(i = 0; i<100000;i++)
				;


	}
}
