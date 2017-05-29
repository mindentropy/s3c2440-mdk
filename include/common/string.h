#ifndef STRING_H_
#define STRING_H_

#include "common.h"

void * memcpy(void *dest,
				void *src,
				uint32_t len
				);

void * memset(void *buff,
			uint8_t c,
			uint32_t n
			);

#endif 
