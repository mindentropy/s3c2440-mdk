#ifndef CPU_H_

#define CPU_H_


#define IMPLEMENTER_MASK 0xFF000000
#define IMPLEMENTER_SHIFT  24

#define CPU_SPEC_REV_MASK 0xF00000
#define CPU_SPEC_REV_SHIFT 20

#define CPU_ARCH_MASK 0xF0000
#define CPU_ARCH_SHIFT 16

#define CPU_PART_NUM_MASK 0xFFF0
#define CPU_PART_NUM_SHIFT 4

#define CPU_LAYOUT_REV 	0xF


unsigned int get_cpu_id();

#define get_cpu_implementer(cpuid) \
	(((cpuid) & (IMPLEMENTER_MASK)) >> IMPLEMENTER_SHIFT)

#define get_cpu_specific_rev(cpuid) \
	(((cpuid) & (CPU_SPEC_REV_MASK)) >> CPU_SPEC_REV_SHIFT)

#define get_cpu_arch(cpuid) \
	(((cpuid) & (CPU_ARCH_MASK)) >> CPU_ARCH_SHIFT)

#define get_cpu_part_num(cpuid) \
	(((cpuid) & (CPU_PART_NUM_MASK)) >> CPU_PART_NUM_SHIFT)

#define get_cpu_layout_rev(cpuid) \
	(((cpuid) & (CPU_LAYOUT_REV)))

#endif
