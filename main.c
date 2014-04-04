#define GPBCON	0x56000010
#define GPBDAT	0x56000014
#define GPBUP	0x56000018


#define writeregw(addr,value) \
	*((volatile unsigned int *) (addr) ) = (value)

#define writeregh(addr,value) \
	*((volatile unsigned short *) (addr) ) = (value)

#define writeregb(addr,value) \
	*((volatile unsigned char *) (addr) ) = (value)

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

		writeregw(GPBDAT,0x1E0);

		/*for(j = 0; j<3; j++) 
			for(i = 0; i<100000;i++)
				;*/


		writeregw(GPBDAT,0x0);

/*		for(j = 0; j<3; j++)
			for(i = 0; i<100000;i++)
				;*/
	}
}
