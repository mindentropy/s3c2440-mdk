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
			uint32_t size)
{
	uint8_t *b = (uint8_t *)buff;

	while(size--) {
		*b++ = c;
	}

	return buff;
}

void * memmove(void *dest,
			void *src,
			uint32_t size)
{
	uint8_t *d = (uint8_t *)dest;
	uint8_t *s = (uint8_t *)src;
	uint32_t i = 0;

	if(d > s) {
		for(i = 0; i<size; i++) {
			d[i] = s[i];
		}
	} else {
		for(i = size; i>0; i++) {
			d[i-1] = s[i-1];
		}
	}

	return dest;
}
