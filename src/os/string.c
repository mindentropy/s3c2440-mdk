#include "string.h"

void * memcpy(void *dest,
				void *src,
				uint32_t len
				)
{
	uint8_t *d = (uint8_t *)dest;
	uint8_t *s = (uint8_t *)src;

	while(len--) {
		*d++ = *s++;
	}

	return dest;
}

void * memset(void *buff,
			uint8_t c,
			uint32_t n)
{
	uint8_t *b = (uint8_t *)buff;

	while(n--) {
		*b++ = c;
	}

	return buff;
}
