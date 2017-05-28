#include "string.h"

void memcpy(uint8_t *dest,
				uint8_t *src,
				unsigned int len
				)
{
	while(len--) {
		*dest++ = *src++;
	}
}
