#include "cache.h"


unsigned int get_cache_info()
{
	unsigned int cache_info;

	__asm__ __volatile__(
		"mrc p15,0,%[cache_info],c0,c0,1\n\t"
		:[cache_info] "=r" (cache_info) /* cache_info return value */
		: /* No input */
		: /* No clobbers */
	);

	return cache_info;
}
