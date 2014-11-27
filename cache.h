#ifndef CACHE_H_

#define CACHE_H_

#define CACHE_TYPE_MASK 0x1E000000
#define CACHE_TYPE_SHIFT 25

#define S_BIT_MASK 0x1000000
#define S_BIT_SHIFT 24

#define D_SIZE_MASK 0xFFF000
#define D_SIZE_SHIFT 12

#define I_SIZE_MASK 0xC00FFF


#define get_cache_type(cache_info) \
	(((cache_info) & (CACHE_TYPE_MASK)) >> (CACHE_TYPE_SHIFT))

#define get_sbit(cache_info) \
	(((cache_info) & (S_BIT_MASK)) >> (S_BIT_SHIFT))

#define get_dsize_info(cache_info) \
	(((cache_info) & (D_SIZE_MASK)) >> (D_SIZE_SHIFT))

#define get_isize_info(cache_info) \
	((cache_info) & (I_SIZE_MASK))


#define SIZE_MASK 0x1C0
#define SIZE_SHIFT 6

#define ASSOC_MASK 0x38
#define ASSOC_SHIFT 3

#define M_BIT_MASK 0x4
#define M_BIT_SHIFT 2

#define LINE_LEN_MASK 0x3

#define get_size(size_info) \
	(((size_info) & (SIZE_MASK)) >> (SIZE_SHIFT))

#define get_assoc(size_info) \
	(((size_info) & (ASSOC_MASK)) >> (ASSOC_SHIFT))

#define get_mbit(size_info) \
	(((size_info) & (M_BIT_MASK)) >> (M_BIT_SHIFT))

#define get_line_len(size_info) \
	((size_info) & (LINE_LEN_MASK)) 



unsigned int get_cache_info();



#endif
