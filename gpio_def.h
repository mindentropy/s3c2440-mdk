#ifndef GPIO_DEF_H_

#define GPIO_DEF_H_

#define GPACON	0x56000000
#define GPADAT	0x56000004


#define GPBCON	0x56000010
#define GPBDAT	0x56000014
#define GPBUP	0x56000018

#define GPCCON	0x56000020
#define GPCDAT	0x56000024
#define GPCUP	0x56000028


#define GPDCON	0x56000030
#define GPDDAT	0x56000034
#define GDPUP	0x56000038

#define GPECON	0x56000040
#define	GPEDAT	0x56000044
#define GPEUP	0x56000048

#define GPFCON	0x56000050
#define	GPFDAT	0x56000054
#define GPFUP	0x56000058

#define GPGCON	0x56000060
#define GPGDAT	0x56000064
#define GPGUP	0x56000068

#define GPHCON	0x56000070
#define GPHDAT	0x56000074
#define GPHUP	0x56000078

#define GPJCON	0x560000d0
#define GPJDAT	0x560000d4
#define GPJUP	0x560000d8


#define writeregw(addr,value) \
	*((volatile unsigned int *) (addr) ) = (value)

#define writeregh(addr,value) \
	*((volatile unsigned short *) (addr) ) = (value)

#define writeregb(addr,value) \
	*((volatile unsigned char *) (addr) ) = (value)

#endif
