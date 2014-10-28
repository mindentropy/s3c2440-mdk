#ifndef UART_H_

#define UART_H_

/* UART Line Control Register */
#define ULCON0 	0x50000000
#define ULCON1 	0x50004000
#define ULCON2  0x50008000

/* UART Control Register */
#define UCON0 	0x50000004
#define UCON1 	0x50004004
#define UCON2  	0x50008004

/* UART FIFO Control Register */
#define UFCON0 	0x50000008
#define UFCON1 	0x50004008
#define UFCON2 	0x50008008

/* UART Modem Control Register */
#define UMCON0  0x5000000C
#define UMCON1 	0x5000400C
#define UMCON2 	0x5000800C

/* UART Tx/Rx Status Register */
#define UTRSTAT0  0x50000010
#define UTRSTAT1  0x50004010
#define UTRSTAT2  0x50008010

/* UART Error Status Register */
#define UERSTAT0  0x50000014
#define UERSTAT1  0x50004014
#define UERSTAT2  0x50008014

/* UART FIFO Status Register */
#define UFSTAT0  0x50000018
#define UFSTAT1  0x50004018
#define UFSTAT2  0x50008018

/* UART Modem Status Register */
#define UMSTAT0  			0x5000001C
#define UMSTAT1  			0x5000401C
#define UFSTAT2_RESERVED  	0x5000801C

/* UART Transmit Buffer Register */
#define UTXH0_L 	0x50000020
#define UTXH0_B 	0x50000023

#define UTXH1_L 	0x50004020
#define UTXH1_B 	0x50004023

#define UTXH2_L 	0x50008020
#define UTXH2_B 	0x50008023

/* UART Receive Buffer Register */
#define URXH0_L 	0x50000024
#define URXH0_B 	0x50000027

#define URXH1_L 	0x50004024
#define URXH1_B 	0x50004027

#define URXH2_L 	0x50008024
#define URXH2_B 	0x50008027

/* UART Baud Rate Divisor Register */
#define UBRDIV0 	0x50000028
#define UBRDIV1 	0x50004028
#define UBRDIV2 	0x50008028

#endif
