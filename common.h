#ifndef COMMON_H_

#define COMMON_H_

#define SET 1
#define RESET 0

/* Set the exact bit positions rather than shifting */

#define BIT(n)  (SET<<(n))

#define BIT0 	BIT(0)
#define BIT1 	BIT(1)
#define BIT2 	BIT(2)
#define BIT3	BIT(3)
#define BIT4	BIT(4) 	
#define BIT5	BIT(5)
#define BIT6	BIT(6) 	
#define BIT7	BIT(7)
#define BIT8	BIT(8)
#define BIT9	BIT(9)
#define BIT10	BIT(10)
#define BIT11	BIT(11)
#define BIT12	BIT(12)
#define BIT13	BIT(13)
#define BIT14	BIT(14)	
#define BIT15	BIT(15) 	
#define BIT16	BIT(16) 	
#define BIT17	BIT(17)
#define BIT18	BIT(18)
#define BIT19	BIT(19)
#define BIT20	BIT(20)
#define BIT21	BIT(21)
#define BIT22	BIT(22)
#define BIT23	BIT(23)
#define BIT24	BIT(24)
#define BIT25	BIT(25)
#define BIT26	BIT(26)
#define BIT27	BIT(27)
#define BIT28	BIT(28)
#define BIT29	BIT(29)
#define BIT30	BIT(30)
#define BIT31	BIT(31)

#define WORD_MASK  (0xFFFFFFFF)

#define SHORT_MASK_MSB ((0xFFFF) << 16)
#define SHORT_MASK_LSB ((0xFFFF))


#define BYTE_MASK (0xFF)


#define set_bits(val,bitmask) {	\
		((val) = ((val) & ~(bitmask)) | (bitmask)); \
	}

#define clear_bits(val,bitmask) {	\
		((val) = ((val) & ~(bitmask)));	\
	}

/*
 * For more info on problems associated with volatile casting see.
 * http://infocenter.arm.com/help/topic/com.arm.doc.faqs/ka3750.html
 */
#define writereg32(addr,value) \
	*((volatile unsigned int *) (addr) ) = ((value) & (0xFFFFFFFF))

#define writereg16(addr,value) \
	*((volatile unsigned short *) (addr) ) = ((value) & (0xFFFF))

#define writereg8(addr,value) \
	*((volatile unsigned char *) (addr) ) = ((value) & (0xFF))

#define readreg32(addr,value) \
	value = ((*((volatile unsigned int *)(addr))) & (0xFFFFFFFF))

#define readreg16(addr,value) \
	value = ((*((volatile unsigned int *)(addr))) & (0xFFFF))

#define readreg8(addr,value) \
	value = ((*((volatile unsigned int *)(addr))) & (0xFF))


#define set_bitval_pos(value,shift) \
	((value)<<(shift))


void set_reg_params(
					unsigned int reg,
					unsigned int regmask
					);
#endif
