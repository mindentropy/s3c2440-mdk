#ifndef COMMON_H_

#define COMMON_H_

#define SET 1
#define RESET 0


#define BIT0 	(SET << 0)
#define BIT1 	(SET << 1)
#define BIT2 	(SET << 2)
#define BIT3	(SET << 3)
#define BIT4	(SET << 4) 	
#define BIT5	(SET << 5)
#define BIT6	(SET << 6) 	
#define BIT7	(SET << 7)
#define BIT8	(SET << 8)
#define BIT9	(SET << 9)
#define BIT10	(SET << 10)
#define BIT11	(SET << 11)
#define BIT12	(SET << 12)
#define BIT13	(SET << 13)
#define BIT14	(SET << 14) 	
#define BIT15	(SET << 15) 	
#define BIT16	(SET << 16) 	
#define BIT17	(SET << 17)
#define BIT18	(SET << 18)
#define BIT19	(SET << 19)
#define BIT20	(SET << 20)
#define BIT21	(SET << 21)
#define BIT22	(SET << 20)
#define BIT23	(SET << 20)
#define BIT24	(SET << 20)
#define BIT25	(SET << 20)
#define BIT26	(SET << 20)
#define BIT27	(SET << 20)
#define BIT28	(SET << 20)
#define BIT29	(SET << 20)
#define BIT30	(SET << 20)
#define BIT31	(SET << 20)

#define SET_BITS(val,bitmask) {	\
		((val) = ((val) & ~(bitmask)) | (bitmask)); \
	}

#define RESET_BITS(val,bitmask) {	\
		((val) = ((val) & ~(bitmask)));	\
	}


#endif
