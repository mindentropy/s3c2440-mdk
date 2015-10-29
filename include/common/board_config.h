#ifndef BOARD_CONFIG_H_

#define BOARD_CONFIG_H_

#define PHYS_START   0x30000000U
#define MAX_RAM_SIZE 0x4000000U

#define SRAM_PHYS_START 0x0U
#define MAX_SRAM_SIZE 	0x1000U

#ifdef MINI2440
/* All MINI2440 Specific definitions go here. */
#define S3C_CLOCK_REFERENCE 12000000U


#endif

#ifdef MINI2410

#endif

#ifdef MINI2451

#endif

#ifdef MINI210

#endif

#ifdef MICRO2440
#endif


/* 
 * Samsung K9K8G08U0D SCB0 -> 1GB NAND Flash
 *         (New mini2440) ID 0x9551D3EC
 */


#ifdef NAND_FLASH_K9K8G08U0D

#define TACLS 	2
#define TWRPH0  7 //TODO: Need to be changed.
#define TWRPH1 	7 //TODO: Need to be changed.

#endif

/*
 * Samsung K9F2G08U0B -> 256MB NAND Flash 
 * 		(Old mini2440) 0xECDA109544 ID 0x9510DAEC
 */

#ifdef NAND_FLASH_K9F2G08U0B

#define TACLS 	3
#define TWRPH0  7
#define TWRPH1 	7

#endif


/*
 * Parameters for clock value of 100MHz and Framerate of around 60-70Hz
 * for a 320 x 240 screen size.
 */


#ifdef LCD_P35

#define HRES 	320
#define VRES 	240

#define VSPW 	(1) //VSYNC Pulse width TODO: How?
#define VBPD 	(12) //Works
#define LINEVAL (VRES-1)
#define VFPD 	(2)

//#define HSPW 	(5)
//#define HSPW 	(0)
#define HSPW 	(1) //HSYNC Pulse width TODO: How?
#define HBPD 	(8) //Works
#define HFPD 	(8)
#define HOZVAL 	(HRES-1)

#define CLKVAL 	(7)
#define BPP 	(16)

/* Datasheet Sony ACX502BMU  */
#elif LCD_X35


#endif


#endif
