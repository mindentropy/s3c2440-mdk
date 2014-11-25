#include "cpu.h"
#include "gpio_def.h"
#include "common.h"


unsigned int get_cpu_id()
{
	unsigned cpuid = 0;

	__asm__ __volatile__(
		"mrc p15,0,%[cpuid],c0,c0,0\n\t"
		:[cpuid]"=r"(cpuid) /*cpu id return value */
		: /* No input */
		: /* No clobbers */
	);

	return cpuid;
}
