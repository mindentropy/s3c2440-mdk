#include "gpio_def.h"


/*
	nLED_1 -> GPB5
	nLED_2 -> GPB6
	nLED_3 -> GPB7
	nLED_4 -> GPB8
*/


int main(void) {

	writeregw(GPBCON,0x15400);
	writeregw(GPBUP,0x1E0);

	register unsigned int i = 0, j = 0;

/* Without delay the led blink rate is 2MHz. */

	while(1) {

		writeregw(GPBDAT,LED1|LED2|LED3|LED4);

		for(j = 0; j<3; j++) 
			for(i = 0; i<100000;i++)
				;


		writeregw(GPBDAT,0x0);

		for(j = 0; j<3; j++)
			for(i = 0; i<100000;i++)
				;
	}
}
